#include <Arduino.h>

// Stepper Motor X
const int stepPin = 2; //X.STEP
const int dirPin = 5; // X.DIR

void setup() {
   // Sets the two pins as Outputs
   pinMode(stepPin,OUTPUT); 
   pinMode(dirPin,OUTPUT);
}

void loop() {
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  // Reduction ratio is 30 --> 6000  
  for(int x = 0; x < 6000; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1000); 
    }
  delay(1000); // One second delay
 
  digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 400; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(1000);
  }
  delay(1000);
}
