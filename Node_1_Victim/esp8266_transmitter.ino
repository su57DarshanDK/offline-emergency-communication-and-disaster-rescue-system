/*
  GHOSTLINK X
  ESP8266 #1
  VICTIM NODE TRANSMITTER

  Receives data from Arduino UNO
  and sends it wirelessly using ESP-NOW.
*/

#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
}

#define SERIAL_BAUD 9600

// Replace with ESP8266 #2 MAC address
uint8_t rescueMAC[] = {
  0xXX, 0xXX, 0xXX,
  0xXX, 0xXX, 0xXX
};

void setup() {

  Serial.begin(SERIAL_BAUD);

  WiFi.mode(WIFI_STA);

  Serial.println();
  Serial.print("Victim ESP MAC: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != 0) {

    Serial.println("ESP-NOW INIT FAILED");

    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

  esp_now_add_peer(
    rescueMAC,
    ESP_NOW_ROLE_SLAVE,
    1,
    NULL,
    0
  );

  Serial.println("ESP8266 TRANSMITTER READY");
}

void loop() {

  if (Serial.available()) {

    String message =
      Serial.readStringUntil('\n');

    message.trim();

    if (message.length() > 0) {

      Serial.print("Sending: ");
      Serial.println(message);

      uint8_t data[250];

      message.toCharArray(
        (char*)data,
        sizeof(data)
      );

      esp_now_send(
        rescueMAC,
        data,
        message.length()
      );
    }
  }
}
