/*
  GHOSTLINK X
  NODE 1 - VICTIM NODE

  Hardware:
  - Arduino UNO
  - Analog Accelerometer
  - Push Button
  - OLED I2C
  - Active Buzzer Module
  - Green LED
  - Red LED
  - ESP8266 NodeMCU

  Functions:
  - Morse button input
  - Accelerometer vibration detection
  - SOS generation
  - OLED status
  - Sends emergency data to ESP8266
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

// ---------------- PIN DEFINITIONS ----------------

#define BUTTON_PIN 2

#define GREEN_LED 3
#define RED_LED 4
#define BUZZER_PIN 8

#define ACC_X A0
#define ACC_Y A1
#define ACC_Z A2

// ESP8266 serial
#define ESP_RX 10
#define ESP_TX 11

SoftwareSerial espSerial(ESP_RX, ESP_TX);

// ---------------- OLED ----------------

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// ---------------- MORSE ----------------

String morseCode = "";

unsigned long pressStart = 0;
bool buttonPressed = false;

const unsigned long DOT_TIME = 500;
const unsigned long CHAR_GAP = 1500;

// ---------------- VIBRATION ----------------

const int VIBRATION_THRESHOLD = 80;

int baseX;
int baseY;
int baseZ;

// ------------------------------------------------

void setup() {

  Serial.begin(9600);
  espSerial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED NOT FOUND");
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  showOLED(
    "GHOSTLINK X",
    "VICTIM NODE",
    "SYSTEM READY"
  );

  delay(2000);

  // Read accelerometer baseline
  baseX = analogRead(ACC_X);
  baseY = analogRead(ACC_Y);
  baseZ = analogRead(ACC_Z);

  Serial.println("NODE 1 READY");
}

// ------------------------------------------------

void loop() {

  readMorseButton();

  detectVibration();

  // If user leaves Morse input open,
  // process character after gap.
  if (
    morseCode.length() > 0 &&
    !buttonPressed &&
    millis() - pressStart > CHAR_GAP
  ) {

    sendMorseCharacter();

    morseCode = "";
  }
}

// =================================================
// MORSE BUTTON
// =================================================

void readMorseButton() {

  bool state = digitalRead(BUTTON_PIN) == LOW;

  if (state && !buttonPressed) {

    buttonPressed = true;

    pressStart = millis();

  }

  if (!state && buttonPressed) {

    buttonPressed = false;

    unsigned long duration =
      millis() - pressStart;

    if (duration < DOT_TIME) {

      morseCode += ".";

      showOLED(
        "MORSE INPUT",
        morseCode,
        "DOT"
      );

    } else {

      morseCode += "-";

      showOLED(
        "MORSE INPUT",
        morseCode,
        "DASH"
      );
    }
  }
}

// =================================================
// SEND MORSE CHARACTER
// =================================================

void sendMorseCharacter() {

  String decoded = decodeMorse(morseCode);

  Serial.print("Morse: ");
  Serial.print(morseCode);
  Serial.print(" -> ");
  Serial.println(decoded);

  showOLED(
    "MORSE MESSAGE",
    morseCode,
    decoded.c_str()
  );

  // Send to ESP8266
  espSerial.print("MORSE:");
  espSerial.print(morseCode);
  espSerial.print(":");
  espSerial.println(decoded);

  delay(1000);

  if (decoded == "SOS") {

    emergencyAlert();
  }
}

// =================================================
// VIBRATION DETECTION
// =================================================

void detectVibration() {

  int x = analogRead(ACC_X);
  int y = analogRead(ACC_Y);
  int z = analogRead(ACC_Z);

  int dx = abs(x - baseX);
  int dy = abs(y - baseY);
  int dz = abs(z - baseZ);

  int vibration = dx + dy + dz;

  if (vibration > VIBRATION_THRESHOLD) {

    Serial.print("VIBRATION: ");
    Serial.println(vibration);

    showOLED(
      "VIBRATION",
      "DETECTED",
      "POSSIBLE SURVIVOR"
    );

    digitalWrite(RED_LED, HIGH);

    // Send vibration alert
    espSerial.print("VIBRATION:");
    espSerial.println(vibration);

    delay(300);

    digitalWrite(RED_LED, LOW);
  }
}

// =================================================
// EMERGENCY ALERT
// =================================================

void emergencyAlert() {

  digitalWrite(RED_LED, HIGH);

  digitalWrite(BUZZER_PIN, HIGH);

  showOLED(
    "EMERGENCY",
    "SOS SENT",
    "HELP REQUESTED"
  );

  espSerial.println("ALERT:SOS");

  delay(2000);

  digitalWrite(BUZZER_PIN, LOW);

  digitalWrite(RED_LED, LOW);
}

// =================================================
// MORSE DECODER
// =================================================

String decodeMorse(String code) {

  if (code == ".-") return "A";
  if (code == "-...") return "B";
  if (code == "-.-.") return "C";
  if (code == "-..") return "D";
  if (code == ".") return "E";
  if (code == "..-.") return "F";
  if (code == "--.") return "G";
  if (code == "....") return "H";
  if (code == "..") return "I";
  if (code == ".---") return "J";
  if (code == "-.-") return "K";
  if (code == ".-..") return "L";
  if (code == "--") return "M";
  if (code == "-.") return "N";
  if (code == "---") return "O";
  if (code == ".--.") return "P";
  if (code == "--.-") return "Q";
  if (code == ".-.") return "R";
  if (code == "...") return "S";
  if (code == "-") return "T";
  if (code == "..-") return "U";
  if (code == "...-") return "V";
  if (code == ".--") return "W";
  if (code == "-..-") return "X";
  if (code == "-.--") return "Y";
  if (code == "--..") return "Z";

  if (code == "-----") return "0";
  if (code == ".----") return "1";
  if (code == "..---") return "2";
  if (code == "...--") return "3";
  if (code == "....-") return "4";
  if (code == ".....") return "5";
  if (code == "-....") return "6";
  if (code == "--...") return "7";
  if (code == "---..") return "8";
  if (code == "----.") return "9";

  return "?";
}

// =================================================
// OLED
// =================================================

void showOLED(
  String line1,
  String line2,
  String line3
) {

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println(line1);

  display.setTextSize(2);

  display.setCursor(0, 20);
  display.println(line2);

  display.setTextSize(1);

  display.setCursor(0, 50);
  display.println(line3);

  display.display();
}
