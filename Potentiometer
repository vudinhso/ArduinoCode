float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  Serial.begin(9600);
}
float angle0;
float angle1;
float angle2;
void loop() {
  // read the input on analog pin 0:
  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  // angle = sensorValue*270/1024;
  // angle = map(sensorValue,0,1023,0,270);
  angle0 = floatMap(sensorValue0,0,1023,0,270);
  angle1 = floatMap(sensorValue1,0,1023,0,270);
  angle2 = floatMap(sensorValue2,0,1023,0,270);
  // print out the value you read:
  Serial.print("bitvalue: ");
  Serial.print(sensorValue0);
  Serial.print("--- angle: ");
  Serial.print(angle0);
  Serial.print(" deg. ");
  Serial.print("bitvalue: ");
  Serial.print(sensorValue1);
  Serial.print("--- angle: ");
  Serial.print(angle1);
  Serial.print(" deg.");
  Serial.print("bitvalue: ");
  Serial.print(sensorValue2);
  Serial.print("--- angle: ");
  Serial.print(angle2);
  Serial.println(" deg.");
  delay(100);        // delay in between reads for stability
}
