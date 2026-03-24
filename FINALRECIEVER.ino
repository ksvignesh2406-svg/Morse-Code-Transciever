#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SSD1306_I2C_ADDRESS 0x3C

#define LDR_PIN A0
#define LED_PIN 13

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String morseChar = "";
String decodedText = "";

unsigned long signalStart = 0;
unsigned long signalEnd = 0;
bool receiving = false;
bool laserOn = false;

void setup() {
  Serial.begin(9600);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(2); // Larger font
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Ready...");
  display.display();
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  Serial.println(ldrValue);

  unsigned long currentTime = millis();

  if (ldrValue < 1000) { // Laser detected
    if (!laserOn) {
      laserOn = true;
      signalStart = currentTime;
      receiving = true;
      digitalWrite(LED_PIN, HIGH); // Blink LED while receiving
    }
  } else { // No laser
    if (laserOn) {
      laserOn = false;
      signalEnd = currentTime;
      unsigned long duration = signalEnd - signalStart;

      if (duration >= 200 && duration < 600) {
        morseChar += ".";  // Dot
      } else if (duration >= 1200 && duration < 1800) {
        morseChar += "-";  // Dash
      }

      signalStart = 0;
      digitalWrite(LED_PIN, LOW);
    }

    // Check for end of character
    if (receiving && (currentTime - signalEnd > 2500)) {
      if (morseChar.length() > 0) {
        char decoded = morseToChar(morseChar);
        decodedText += decoded;
        Serial.print("Decoded Char: ");
        Serial.println(decoded);
        updateDisplay(decodedText);
        morseChar = "";
      }
      receiving = false;
    }
  }
}

char morseToChar(String morse) {
  if (morse == ".-") return 'A';
  if (morse == "-...") return 'B';
  if (morse == "-.-.") return 'C';
  if (morse == "-..") return 'D';
  if (morse == ".") return 'E';
  if (morse == "..-.") return 'F';
  if (morse == "--.") return 'G';
  if (morse == "....") return 'H';
  if (morse == "..") return 'I';
  if (morse == ".---") return 'J';
  if (morse == "-.-") return 'K';
  if (morse == ".-..") return 'L';
  if (morse == "--") return 'M';
  if (morse == "-.") return 'N';
  if (morse == "---") return 'O';
  if (morse == ".--.") return 'P';
  if (morse == "--.-") return 'Q';
  if (morse == ".-.") return 'R';
  if (morse == "...") return 'S';
  if (morse == "-") return 'T';
  if (morse == "..-") return 'U';
  if (morse == "...-") return 'V';
  if (morse == ".--") return 'W';
  if (morse == "-..-") return 'X';
  if (morse == "-.--") return 'Y';
  if (morse == "--..") return 'Z';
  return '?';
}

void updateDisplay(String message) {
  display.clearDisplay();
  display.setTextSize(2); // Big font
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}
