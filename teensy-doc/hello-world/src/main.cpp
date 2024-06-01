#include "Arduino.h"

#define LED_BUILTIN (13)  // LEDのピン

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  printf("Hello, World!\r\n");
  delay(100);
}


