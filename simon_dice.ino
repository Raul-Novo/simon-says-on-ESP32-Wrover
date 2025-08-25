#include <Arduino.h>
#include <LiquidCrystal.h>

// Pines LEDs
const int ledPins[4] = {23, 22, 21, 19};
// Pines botones
const int buttonPins[4] = {32, 33, 25, 26};
// Passive buzzer
const int buzzerPin = 27;

// Tonos por LED
const int ledTones[4] = {262, 330, 392, 523}; // C4, E4, G4, C5

// Secuencia
const int MAX_LEVEL = 20;
int sequence[MAX_LEVEL];
int playerInput[MAX_LEVEL];
int level = 0;

// Timing
const int ledOnTime = 500;
const int ledOffTime = 200;
const int debounceDelay = 50;

bool gameStarted = false;

// LCD (modo 4 bits): RS, E, D4, D5, D6, D7
LiquidCrystal lcd(14, 12, 13, 4, 5, 18);

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Simon Dice!");
  lcd.setCursor(0,1);
  lcd.print("Pulsa boton");

  randomSeed(analogRead(0));
}

void loop() {
  if (!gameStarted) {
    // Espera primera pulsación para iniciar juego
    for (int b = 0; b < 4; b++) {
      if (digitalRead(buttonPins[b]) == LOW) {
        flashLed(b);
        sequence[0] = b;
        level = 1;
        gameStarted = true;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Nivel: 1");
        while (digitalRead(buttonPins[b]) == LOW); // espera soltar
        delay(500);
      }
    }
    return;
  }

  // Mostrar secuencia
  for (int i = 0; i < level; i++) {
    flashLed(sequence[i]);
    delay(ledOffTime);
  }

  // Leer input jugador
  for (int i = 0; i < level; i++) {
    int pressed = waitForButton();
    playerInput[i] = pressed;
    flashLed(pressed);

    if (playerInput[i] != sequence[i]) {
      gameOver();
      return;
    }
  }

  // Añadir nuevo paso
  sequence[level] = random(0, 4);
  level++;
  lcd.setCursor(0,0);
  lcd.print("Nivel: ");
  lcd.print(level);
  delay(500);
}

int waitForButton() {
  while (true) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {
        delay(debounceDelay);
        while (digitalRead(buttonPins[i]) == LOW) delay(10); // espera soltar
        return i;
      }
    }
  }
}

void flashLed(int led) {
  digitalWrite(ledPins[led], HIGH);
  tone(buzzerPin, ledTones[led]);
  delay(ledOnTime);
  digitalWrite(ledPins[led], LOW);
  noTone(buzzerPin);
}

void gameOver() {
  Serial.println("Fallo! Game Over");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Game Over!");
  lcd.setCursor(0,1);
  lcd.print("Pulsa boton");
  
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) digitalWrite(ledPins[j], HIGH);
    tone(buzzerPin, 200, 300);
    delay(300);
    for (int j = 0; j < 4; j++) digitalWrite(ledPins[j], LOW);
    noTone(buzzerPin);
    delay(300);
  }
  level = 0;
  gameStarted = false;
}
