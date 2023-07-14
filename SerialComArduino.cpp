#include <Arduino.h>
// ******************************************
// General Information
// ******************************************
// This code is for the Arduino board. 
// Data is sent to the serial port (USB port). The delimiter is a comma ","; 
// Serial.write(13);  Serial.write(10); --> Correspond to a line break (CR/LF: CR = Carriage Return and LF = Line Feed), 
// which is the end of data delimiter, so that MATLAB knows where the data from the serial communication starts and ends. 

// ******************************************
// Variable declaration
// ******************************************
int PotPin = A0;
unsigned long curr_time = 0, prev_time = 0, dt = 50000; // time interval in us

// ******************************************
// Function declaration
// ******************************************
float floatMap(float, float, float, float, float); // like the map function, but with float instead of integer
void SerialDataWrite();

// ******************************************
// void setup
// ******************************************
void setup() {
  Serial.begin(9600); delay(10);
  analogReadResolution(12); // Only for microctrl with 12bit ADC
}

// ******************************************
// void loop
// ******************************************
void loop() {
  // Data acquisition
  int PotVal = analogRead(PotPin);
  float Angle = floatMap(PotVal, 0, 4096, 0, 300);
  curr_time = micros();
  // Write on the COM each dt interval
  if (curr_time - prev_time >= dt)
  {
    prev_time += dt;
    SerialDataWrite();
  }
}

// ******************************************
// Function definition
// ******************************************
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void SerialDataWrite()
{
    Serial.print(curr_time / 1000);
    Serial.print(",");
    Serial.print(PotVal);
    Serial.print(",");
    Serial.print(Angle);
    // Serial.println("");
    Serial.write(13);
    Serial.write(10);
}
