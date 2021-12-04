#include <Arduino.h>

// floatMap is like the built-in map function, but output a float
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int sensorPin = A2;

void setup() {
  Serial.begin(9600);
}
float angle0;
void loop() {
  int sensorValue0 = analogRead(sensorPin);
  angle0 = floatMap(sensorValue0,0,1023,0,300);
  // print out the value you read:
  Serial.print("bitvalue: ");
  Serial.print(sensorValue0);
  Serial.print("--- angle: ");
  Serial.print(angle0);
  Serial.print(" deg.");
  Serial.println("");
  delay(100);        // delay in between reads for stability
}
