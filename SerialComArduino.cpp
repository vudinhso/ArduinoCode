float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void setup() {
  Serial.begin(9600);
  delay(100);
}

float angle;
unsigned long myTime;

void loop() {
  int sensorValue = analogRead(A0); //read the input on analog pin 0
  myTime = millis();
  angle = floatMap(sensorValue,0,1023,0,270);


  //Serial.print("angle:");
  Serial.print(myTime);
  Serial.print(",");
  Serial.print(angle);
  Serial.write(13);
  Serial.write(10);
  delay(10); 
}
