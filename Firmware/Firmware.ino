#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME680.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>

constexpr uint8_t PIN_SW1 = 2;       // GPIO2_A0_D0
constexpr uint8_t PIN_SW2 = 3;       // GPIO3_A1_D1
constexpr uint8_t PIN_SW3 = 4;       // GPIO4_A2_D2
constexpr uint8_t PIN_SW4 = 5;       // GPIO5_A3_D3
constexpr uint8_t PIN_NEOPIXEL = 6;  // GPIO6_D4_SDA
constexpr uint8_t PIN_IR_TX = 7;     // GPIO7_D5_SCL
constexpr uint8_t PIN_I2C_SCL = 9;   // GPIO9_D9_MISO, schematic SCL
constexpr uint8_t PIN_I2C_SDA = 10;  // GPIO10_D10_MOSI, schematic SDA
constexpr uint8_t PIN_IR_RX = 21;    // GPIO21_D6_RX, optional IR receiver input

constexpr uint8_t OLED_WIDTH = 128;
constexpr uint8_t OLED_HEIGHT = 64;
constexpr int8_t OLED_RESET = -1;
constexpr uint8_t OLED_ADDR = 0x3C;

constexpr uint8_t BME680_ADDR_PRIMARY = 0x76;
constexpr uint8_t BME680_ADDR_SECONDARY = 0x77;

constexpr uint8_t NEOPIXEL_COUNT = 2;
constexpr uint16_t DEBOUNCE_MS = 35;
constexpr uint32_t SENSOR_PERIOD_MS = 2500;
constexpr uint32_t OLED_PERIOD_MS = 500;
constexpr uint32_t IR_STATUS_MS = 2500;

// Replace these with the codes for your AC/electronics.
// Use SW4 to learn and print codes from an attached IR receiver on GPIO21.
constexpr uint16_t NEC_BITS = 32;
constexpr uint32_t AC_POWER_NEC_CODE = 0x20DF10EF;
constexpr uint32_t DEVICE_1_NEC_CODE = 0x00FF02FD;
constexpr uint32_t DEVICE_2_NEC_CODE = 0x00FF9867;

uint16_t AC_ON_RAW[] = {
  9000, 4500, 560, 560, 560, 1690, 560, 560, 560, 560,
  560, 1690, 560, 560, 560, 1690, 560, 560, 560
};
uint16_t AC_OFF_RAW[] = {
  9000, 4500, 560, 560, 560, 1690, 560, 560, 560, 1690,
  560, 560, 560, 560, 560, 1690, 560, 560, 560
};

struct Button {
  uint8_t pin;
  bool stablePressed = false;
  bool lastReading = false;
  uint32_t changedAt = 0;
};

struct Environment {
  float tempC = NAN;
  float humidity = NAN;
  float pressureHpa = NAN;
  float gasKohms = NAN;
  bool valid = false;
  uint32_t lastRead = 0;
};

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);
Adafruit_BME680 bme;
Adafruit_NeoPixel pixels(NEOPIXEL_COUNT, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
IRsend irsend(PIN_IR_TX);
IRrecv irrecv(PIN_IR_RX);
decode_results irResults;

Button buttons[] = {
  { PIN_SW1 },
  { PIN_SW2 },
  { PIN_SW3 },
  { PIN_SW4 },
};

Environment env;
bool oledOk = false;
bool bmeOk = false;
bool receiverEnabled = true;
bool acOn = false;
uint8_t screenPage = 0;
uint8_t mood = 0;
String lastIrMessage = "Ready";
uint32_t lastIrAt = 0;
uint32_t lastOledAt = 0;

bool buttonPressed(Button &button) {
  const bool readingPressed = digitalRead(button.pin) == LOW;
  const uint32_t now = millis();

  if (readingPressed != button.lastReading) {
    button.lastReading = readingPressed;
    button.changedAt = now;
  }

  if ((now - button.changedAt) < DEBOUNCE_MS) {
    return false;
  }

  if (button.stablePressed != readingPressed) {
    button.stablePressed = readingPressed;
    return button.stablePressed;
  }

  return false;
}

void setStatusPixels(uint32_t color) {
  for (uint8_t i = 0; i < NEOPIXEL_COUNT; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}

void updateMoodPixels() {
  switch (mood) {
    case 0:
      setStatusPixels(pixels.Color(0, 24, 36));
      break;
    case 1:
      setStatusPixels(pixels.Color(36, 18, 0));
      break;
    case 2:
      setStatusPixels(pixels.Color(18, 0, 36));
      break;
    default:
      setStatusPixels(pixels.Color(0, 0, 0));
      break;
  }
}

void flashPixels(uint32_t color) {
  setStatusPixels(color);
  delay(80);
  updateMoodPixels();
}

void rememberIr(const String &message) {
  lastIrMessage = message;
  lastIrAt = millis();
  Serial.println(message);
  flashPixels(pixels.Color(0, 48, 0));
}

void sendNecCode(uint32_t code, const String &label) {
  irsend.sendNEC(code, NEC_BITS);
  rememberIr(label + " NEC 0x" + String(code, HEX));
}

void sendAcRaw(bool powerOn) {
  if (powerOn) {
    irsend.sendRaw(AC_ON_RAW, sizeof(AC_ON_RAW) / sizeof(AC_ON_RAW[0]), 38);
    rememberIr("AC ON raw frame sent");
  } else {
    irsend.sendRaw(AC_OFF_RAW, sizeof(AC_OFF_RAW) / sizeof(AC_OFF_RAW[0]), 38);
    rememberIr("AC OFF raw frame sent");
  }
}

void toggleAc() {
  acOn = !acOn;
  sendAcRaw(acOn); 
}

void configureBme680() {
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);
}

void readEnvironment() {
  if (!bmeOk || millis() - env.lastRead < SENSOR_PERIOD_MS) {
    return;
  }

  env.lastRead = millis();
  if (!bme.performReading()) {
    env.valid = false;
    return;
  }

  env.tempC = bme.temperature;
  env.humidity = bme.humidity;
  env.pressureHpa = bme.pressure / 100.0F;
  env.gasKohms = bme.gas_resistance / 1000.0F;
  env.valid = true;
}

void printEnvironmentToSerial() {
  if (!env.valid) {
    Serial.println("BME680 reading unavailable");
    return;
  }

  Serial.print("Temp C: ");
  Serial.print(env.tempC, 1);
  Serial.print(" | Humidity %: ");
  Serial.print(env.humidity, 1);
  Serial.print(" | Pressure hPa: ");
  Serial.print(env.pressureHpa, 1);
  Serial.print(" | Gas kOhm: ");
  Serial.println(env.gasKohms, 1);
}

void drawHeader(const __FlashStringHelper *title) {
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(title);
  display.drawLine(0, 10, OLED_WIDTH, 10, SSD1306_WHITE);
}

void drawEnvironmentPage() {
  drawHeader(F("CyberPet Environment"));
  display.setCursor(0, 16);

  if (!bmeOk) {
    display.println(F("BME680 not found"));
    display.println(F("Check SDA GPIO10"));
    display.println(F("Check SCL GPIO9"));
    return;
  }

  if (!env.valid) {
    display.println(F("Waiting for sensor"));
    return;
  }

  display.print(F("Temp: "));
  display.print(env.tempC, 1);
  display.println(F(" C"));

  display.print(F("Humidity: "));
  display.print(env.humidity, 1);
  display.println(F(" %"));

  display.print(F("Pressure: "));
  display.print(env.pressureHpa, 1);
  display.println(F(" hPa"));

  display.print(F("Gas: "));
  display.print(env.gasKohms, 1);
  display.println(F(" kOhm"));
}

void drawControlPage() {
  drawHeader(F("IR Controls"));
  display.setCursor(0, 16);
  display.print(F("AC: "));
  display.println(acOn ? F("ON") : F("OFF"));
  display.println(F("SW1 AC power"));
  display.println(F("SW2 Device 1"));
  display.println(F("SW3 Device 2"));
  display.println(F("SW4 Next page"));
}

void drawStatusPage() {
  drawHeader(F("System"));
  display.setCursor(0, 16);
  display.print(F("I2C SDA: GPIO"));
  display.println(PIN_I2C_SDA);
  display.print(F("I2C SCL: GPIO"));
  display.println(PIN_I2C_SCL);
  display.print(F("IR TX: GPIO"));
  display.println(PIN_IR_TX);
  display.print(F("NeoPixel: GPIO"));
  display.println(PIN_NEOPIXEL);
  display.print(F("Last: "));
  display.println(lastIrMessage.substring(0, 15));
}

void updateDisplay(bool force = false) {
  if (!oledOk || (!force && millis() - lastOledAt < OLED_PERIOD_MS)) {
    return;
  }

  lastOledAt = millis();
  display.clearDisplay();

  if (screenPage == 0) {
    drawEnvironmentPage();
  } else if (screenPage == 1) {
    drawControlPage();
  } else {
    drawStatusPage();
  }

  if (millis() - lastIrAt < IR_STATUS_MS) {
    display.fillRect(0, 55, OLED_WIDTH, 9, SSD1306_BLACK);
    display.setCursor(0, 56);
    display.print(lastIrMessage.substring(0, 21));
  }

  display.display();
}

void scanSerialCommands() {
  if (!Serial.available()) {
    return;
  }

  String command = Serial.readStringUntil('\n');
  command.trim();
  command.toLowerCase();

  if (command == "ac on") {
    acOn = false;
    toggleAc();
  } else if (command == "ac off") {
    acOn = true;
    toggleAc();
  } else if (command == "ac toggle") {
    toggleAc();
  } else if (command == "dev1") {
    sendNecCode(DEVICE_1_NEC_CODE, "Device 1");
  } else if (command == "dev2") {
    sendNecCode(DEVICE_2_NEC_CODE, "Device 2");
  } else if (command == "env") {
    printEnvironmentToSerial();
  } else if (command == "page") {
    screenPage = (screenPage + 1) % 3;
  } else {
    Serial.println("Commands: ac on, ac off, ac toggle, dev1, dev2, env, page");
  }
}

void readIrReceiver() {
  if (!receiverEnabled) {
    return;
  }

  if (irrecv.decode(&irResults)) {
    Serial.println(resultToHumanReadableBasic(&irResults));
    Serial.println(resultToSourceCode(&irResults));
    lastIrMessage = "IR learned";
    lastIrAt = millis();
    irrecv.resume();
  }
}

void handleButtons() {
  if (buttonPressed(buttons[0])) {
    toggleAc();
  }

  if (buttonPressed(buttons[1])) {
    sendNecCode(DEVICE_1_NEC_CODE, "Device 1");
  }

  if (buttonPressed(buttons[2])) {
    mood = (mood + 1) % 4;
    updateMoodPixels();
    sendNecCode(DEVICE_2_NEC_CODE, "Device 2");
  }

  if (buttonPressed(buttons[3])) {
    screenPage = (screenPage + 1) % 3;
    updateDisplay(true);
  }
}

void setup() {
  Serial.begin(115200);
  delay(250);

  pinMode(PIN_SW1, INPUT_PULLUP);
  pinMode(PIN_SW2, INPUT_PULLUP);
  pinMode(PIN_SW3, INPUT_PULLUP);
  pinMode(PIN_SW4, INPUT_PULLUP);
  pinMode(PIN_IR_TX, OUTPUT);
  pinMode(PIN_IR_RX, INPUT_PULLUP);

  pixels.begin();
  pixels.setBrightness(40);
  updateMoodPixels();

  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  Wire.setClock(400000);

  oledOk = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  if (oledOk) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("CyberPet booting"));
    display.display();
  }

  bmeOk = bme.begin(BME680_ADDR_PRIMARY, &Wire);
  if (!bmeOk) {
    bmeOk = bme.begin(BME680_ADDR_SECONDARY, &Wire);
  }
  if (bmeOk) {
    configureBme680();
  }

  irsend.begin();
  irrecv.enableIRIn();

  Serial.println();
  Serial.println("CyberPet firmware ready");
  Serial.println("Pins: SDA=GPIO10 SCL=GPIO9 IR_TX=GPIO7 NeoPixel=GPIO6 Buttons=GPIO2-5");
  Serial.println("Serial commands: ac on, ac off, ac toggle, dev1, dev2, env, page");
}

void loop() {
  readEnvironment();
  handleButtons();
  scanSerialCommands();
  readIrReceiver();
  updateDisplay();
}
