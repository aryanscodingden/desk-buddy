## Desk Buddy
A smart buddy that sits on your desk & can control your room. It can sense the temprature and turn on the AC or Fan depneding on how hot it is! 

<img width="1410" height="2000" alt="Desk Buddy A5" src="https://github.com/user-attachments/assets/522ffbf7-1623-4800-826a-5d327f14d4a7" />

<br>

# Schematic 
<img width="3507" height="2480" alt="image" src="https://github.com/user-attachments/assets/b7b033da-fc37-4949-ac74-0cc839fa95f3" />
It uses a ESP32-C3 as the main board, a BME680 as temp sensor paired with 2 IR diodes & a 0.96 OLED Screen!
This schematic was made in KiCAD

# PCB
<img width="642" height="586" alt="image" src="https://github.com/user-attachments/assets/5bbb45cc-a707-4ca4-859b-3bd8e0b073d4" />
<br>
A simple 2 layer PCB to accomadate all of the componets.

# Case
## RENDERS
This case was designed in Fusion 360. The case & PCB are held together by M3 Screws
<p align="center">
  <img src="https://github.com/user-attachments/assets/8d6316f9-9fa3-495d-8939-5f19f7fcdd6a" width="48%">
  <img src="https://github.com/user-attachments/assets/a3603446-90a9-4fdc-9b60-1676858dcf62" width="48%">
</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/a277eb8f-239a-4148-94eb-be29422dd069" width="70%">
</p>

</div>

# Firmware
The firmware is written in C++ and will be edited/deployed from Arduino IDE.

## Bill of Materials (BOM)

| Sr. No. | Item | Unit Price | Link |
|:------:|------|:----------:|------|
| 1 | ESP32-C3 | ₹383 ($4.06) | https://robocraze.com/products/nodemcu-32-wifi-bluetooth-esp32-development-board30-pin |
| 2 | 0.96" OLED Display | ₹159 ($1.69) | https://robocraze.com/products/0-96in-oled-display-module-4pin |
| 3 | IR Diodes | ₹26 ($0.28) | https://robu.in/product/5mm-940nm-infrared-receiver-led-ir-diode-led-pack-of-5/ |
| 4 | Tactile Push Button Switch Assorted Kit | ₹156 ($1.65) | https://robocraze.com/products/tactile-push-button-switch-assorted-kit-25-pieces-pack |
| 5 | LiPo Battery | ₹235 ($2.49) | https://robu.in/product/500mah-pcm-protected-micro-li-po-battery-2/ |
| 6 | BME680 Temperature Sensor | ₹749 ($7.64) | https://www.amazon.in/Panel-Mount-Momentary-Button-Switch/dp/B0B54XV8D2 |
| 7 | WS2812B RGB LED | ₹172 ($1.82) | https://robu.in/product/ws2812b-rgb-addressable-led-module/ |
| 8 | 3D Print | ₹1,376 ($14.08) | https://www.amazon.in/3IDEA-Bambu-Translucent-Printing-Filament/dp/B0GT9GW2H7 |
| 9 | PCB | ₹900.00 ($9.54) | robu.in |

TOTAL COST: ₹4,156 ($44.02)
