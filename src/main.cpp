#include <Arduino.h>

uint32_t count = 0;

#define HWSERIAL Serial2
#define USBSERIAL Serial

void setup() {
  Serial.begin(9600);
  HWSERIAL.begin(9600);
}

void loop() {
  int incomingByte;
  if (USBSERIAL.available()) {
    incomingByte = USBSERIAL.read();
    USBSERIAL.print((char)incomingByte);
    HWSERIAL.print((char)incomingByte);
  }

  HWSERIAL.flush();
  USBSERIAL.flush();

  if (HWSERIAL.available()) {
    incomingByte = HWSERIAL.read();
    Serial.print("UART received: ");
    Serial.println(char(incomingByte));
  }
}
