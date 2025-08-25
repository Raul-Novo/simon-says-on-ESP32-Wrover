# Simón dice en el ESP32 Wrover

Este proyecto implementa el clásico juego de **“Simón dice”** utilizando un **ESP32 Wrover** y el entorno de desarrollo **Arduino IDE**.

## Materiales necesarios

* 1 ESP32 Wrover
* 1 protoboard/breadboard
* Cables jumper
* 4 botones táctiles
* 4 LEDs
* 5 resistencias de 220 Ω (4 para LEDs y 1 para el buzzer)
* 1 potenciómetro
* 1 buzzer pasivo
* 1 pantalla LCD 16x2

## Conexiones

### Botones

Cada botón táctil tiene 4 pines, pero solo se utilizan **2 en diagonal**:

* Un pin a **GND**.
* El pin opuesto a un pin digital del ESP32.

Asignación en este proyecto:

* Botón 1 → pin **32**
* Botón 2 → pin **33**
* Botón 3 → pin **25**
* Botón 4 → pin **26**

### LEDs

Los LEDs tienen dos patas:

* **Ánodo (+)** → conectado a un pin del ESP32.
* **Cátodo (–)** → a **GND** mediante una resistencia de **220 Ω**.

Asignación en este proyecto:

* LED 1 → pin **23**
* LED 2 → pin **22**
* LED 3 → pin **21**
* LED 4 → pin **19**

### Pantalla LCD 16x2 (modo 4 bits)

* VSS → GND
* VDD → +3.3V
* V0 → cursor del potenciómetro (para contraste)
* RS → pin **14**
* RW → GND
* E → pin **12**
* D0–D3 → no conectados
* D4 → pin **13**
* D5 → pin **4**
* D6 → pin **5**
* D7 → pin **18**
* A (LED+) → +3.3V
* K (LED–) → GND a través de una resistencia

El potenciómetro se conecta con:

* Un extremo a +3.3V
* El otro extremo a GND
* El cursor (pin central) a **V0** del LCD

### Buzzer pasivo

* Pin positivo → pin **27** del ESP32
* Pin negativo → GND a través de una resistencia de **220 Ω**

## Funcionamiento

El juego funciona igual que la versión clásica de **Simón dice**:

1. La placa genera una secuencia aleatoria de LEDs acompañados por sonidos en el buzzer.
2. El jugador debe repetir la secuencia pulsando los botones correspondientes.
3. Si acierta, el nivel aumenta y la secuencia se hace más larga.
4. Si se equivoca, la pantalla muestra **Game Over** y los LEDs parpadean junto con un tono de error.

La pantalla LCD muestra el estado del juego (inicio, nivel actual y fin de partida).
