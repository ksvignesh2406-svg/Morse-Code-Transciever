# How to Run

## Prerequisites

* Arduino IDE installed
* Required libraries:

  * Adafruit GFX
  * Adafruit SSD1306
  * Keypad

Install libraries from **Arduino IDE → Library Manager**

---

## Hardware Setup

### Transmitter Module

* Connect keypad to digital pins D2–D9
* Connect OLED (I2C):

  * SDA → A4
  * SCL → A5
* Connect laser module:

  * Signal → D12
  * VCC → 5V
  * GND → GND

---

### Receiver Module

* Connect LDR to A0
* Connect OLED (I2C):

  * SDA → A4
  * SCL → A5
* Connect LED:

  * Signal → D13
  * GND → GND

---

## Upload Code

1. Connect **first Arduino Nano (Transmitter)** to PC

2. Select:

   * Board → Arduino Nano
   * Processor → ATmega328P
   * Correct COM Port

3. Upload **transmitter code**

4. Connect **second Arduino Nano (Receiver)**

5. Upload **receiver code**

---

## Execution Steps

1. Power both modules
2. Align the **laser (transmitter)** with the **LDR (receiver)**
3. Open Serial Monitor (9600 baud) for receiver (optional)

---

### Transmitter Controls

* `1` → Move forward through alphabets
* `2` → Move backward
* `3` → Select letter
* `A` → Transmit complete word

---

## Working

1. Select characters using keypad
2. Press `A` to transmit
3. Laser sends Morse code signals
4. Receiver detects signals using LDR
5. Morse code is decoded into text
6. Output is displayed on OLED and Serial Monitor

---

## Notes

* Ensure proper alignment between laser and LDR
* Adjust lighting conditions if detection is unstable
* Threshold values in code may need tuning based on environment

---
