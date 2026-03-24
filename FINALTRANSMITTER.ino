#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define LASER_PIN 12

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte ROW_NUM = 4;
const byte COLUMN_NUM = 4;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},  // '1' = Move forward, '2' = Move backward, '3' = Confirm letter, 'A' = Transmit cword
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}   
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int index = 0;
String cword = "";

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(LASER_PIN, OUTPUT);
  digitalWrite(LASER_PIN, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  display.clearDisplay();
  display.display();
  updateDisplay();
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 20);
  display.print(alphabet[index]);
  
  display.setTextSize(1);
  display.setCursor(10, 50);
  display.print("cword: ");
  display.print(cword);
  
  display.display();
}

void sendMorse(String text) {
  for (char c : text) {
    String morseCode = getMorse(c);
    Serial.print("Sending Morse for: ");
    Serial.println(c);
    for (char m : morseCode) {
      if (m == '.') {
        digitalWrite(LASER_PIN, HIGH);
        delay(300);  // Short dot duration (300ms)
      } else if (m == '-') {
        digitalWrite(LASER_PIN, HIGH);
        delay(1500); // Longer dash duration (1500ms)
      }
      digitalWrite(LASER_PIN, LOW);
      delay(500);  // Standard gap between symbols (500ms)
    }
    delay(3500);  // Gap between characters (2000ms, after each letter)
  }
}


String getMorse(char letter) {
  switch (letter) {
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";
    default: return "";
  }
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.print("Key Pressed: ");
    Serial.println(key);
    if (key == '1') {
      index = (index + 1) % 26;
      updateDisplay();
    }
    if (key == '2') {
      index = (index - 1 + 26) % 26;
      updateDisplay();
    }
    if (key == '3') {
      cword += alphabet[index];
      updateDisplay();
    }
    if (key == 'A') {
      sendMorse(cword);
      cword = "";
      updateDisplay();
    }
  }
}
