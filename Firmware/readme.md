# CyberPet Firmware

Arduino IDE firmware for a desk pet built around a Seeed Studio XIAO ESP32-C3,
BME680 temperature/humidity/pressure/gas sensor, 0.96 inch I2C OLED, two
NeoPixels, buttons, and IR LEDs.

## Features

- OLED shows temperature, humidity, pressure, BME680 gas resistance, IR control
  state, and wiring status pages.
- SW1 toggles AC power using the IR LED.
- SW2 sends a configurable NEC code for another device.
- SW3 changes the NeoPixel mood color and sends a second configurable NEC code.
- SW4 changes the OLED page.
- Serial Monitor commands let you send IR commands and print sensor readings.
- Optional IR receiver support on GPIO21 prints captured IR codes to Serial
  Monitor so you can paste real remote codes back into the sketch.

## Arduino IDE Flashing Instructions

1. Install Arduino IDE 2.x.
2. Open Arduino IDE > Settings**.
3. Add this URL to Additional boards manager URLs:

   ```text
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```

4. Open Tools > Board > Boards Manager, search for `esp32`, and install
   esp32 by Espressif Systems.
5. Open **Tools > Manage Libraries** and install:

   - Adafruit BME680 Library
   - Adafruit SSD1306
   - Adafruit GFX Library
   - Adafruit NeoPixel
   - IRremoteESP8266
   - Adafruit Unified Sensor, if Arduino IDE does not install it automatically

## Notes

- Buttons are wired active-low in the schematic, so the firmware uses
  `INPUT_PULLUP`.
