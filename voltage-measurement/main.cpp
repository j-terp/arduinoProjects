#include <Arduino.h>

  int analogPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(analogPin);
  float voltage = 5.0 * val / 1024;
  Serial.println(voltage);
  delay(100);
}