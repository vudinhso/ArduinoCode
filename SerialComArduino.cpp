// This code is for the Arduino board. 
// First, it states the elapsed time. 
// Then, it states the potentiometer angle. 
// The elapsed time and the potentiometer angle are separated with a comma. 
// Serial.write(13);  Serial.write(10); --> Correspond to a line break (CR/LF: CR = Carriage Return and LF = Line Feed), 
// which is the delimiter, so that MATLAB knows where the data from the serial communication ends and starts. 

// Custom map function
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Pin declaration
int PotPin = A0;

void setup() {
  Serial.begin(9600);
  delay(100);
}

// Variable declaration
int PotVal; 
float PotAngle;
unsigned long myTime;

void loop() {
  PotVal = analogRead(PotPin); 
  PotAngle = floatMap(PotVal,0,1023,0,300);
  myTime = millis();

  Serial.print(myTime);
  Serial.print(",");
  Serial.print(PotAngle);
  Serial.write(13);
  Serial.write(10);
  delay(10); 
}
