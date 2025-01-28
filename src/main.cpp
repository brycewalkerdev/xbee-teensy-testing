#include <Arduino.h>
#include <cstdint>

#define LOCALADDRESS 0x0013A2004238F702
#define REMOTEADDRESS 0x0013A2004238F708

uint32_t count = 0;

#define HWSERIAL Serial2
#define USBSERIAL Serial

char tx_buf[255];
char rx_buf[255];

uint8_t tx_idx = 0;
uint8_t rx_idx = 0;

void setup() {
  Serial.begin(9600);
  HWSERIAL.begin(9600);
}

void loop() {
  if (USBSERIAL.available()) {
    tx_buf[tx_idx] = (char)USBSERIAL.read();
    USBSERIAL.print(tx_buf[tx_idx]);
    if (tx_buf[tx_idx] == '\n' || tx_buf[tx_idx] == '\r') {
      USBSERIAL.println();
      USBSERIAL.println("Sending...");
      USBSERIAL.println();
      for (uint8_t i = 0; i < (tx_idx + 1); ++i) {
        HWSERIAL.print(tx_buf[i]);
      }
      tx_idx = 0;
    } else {
      ++tx_idx;
    }
  }

  if (HWSERIAL.available()) {
    rx_buf[rx_idx] = (char)HWSERIAL.read();
    if (rx_buf[rx_idx] == '\n' || rx_buf[rx_idx] == '\r') {
      Serial.println("MSG received: ");
      for (uint8_t i = 0; i < (rx_idx + 1); ++i) {
        USBSERIAL.print(rx_buf[i]);
      }
      USBSERIAL.println();
      USBSERIAL.println();
      rx_idx = 0;
    } else {
      ++rx_idx;
    }
  }
}
