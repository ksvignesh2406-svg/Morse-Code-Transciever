# Important Note

## Reference Disclaimer

The circuit diagram and setup diagram provided in this repository are for **reference purposes only**.

Due to variations in:

* Component availability
* Wiring layout on breadboard
* Environmental conditions (especially for LDR sensitivity)

The actual physical setup may differ slightly from the diagram.

---

## Implementation Note

This project was physically built and tested using a **custom breadboard setup**, and the wiring may not exactly match the schematic representation.

Users are advised to:

* Follow the **pin connections defined in the code**
* Use the diagram only as a **visual guide**
* Adjust connections based on practical setup

---

## Components Used

### Transmitter Module

* Arduino Nano
* 4x4 Matrix Keypad
* 128x64 OLED Display (SSD1306, I2C)
* Laser Module
* Breadboard
* Jumper Wires

---

### Receiver Module

* Arduino Nano
* LDR (Photoresistor)
* 128x64 OLED Display (SSD1306, I2C)
* LED
* Breadboard
* Jumper Wires

---

## Additional Notes

* LDR values depend on ambient light and may require **threshold tuning**
* Ensure proper alignment between the laser and LDR
* A stable power supply improves decoding accuracy

---

## Summary

This project demonstrates a **laser-based Morse code communication system**, and the diagrams are intended to assist understanding rather than enforce an exact implementation.

---
