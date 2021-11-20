#include <Arduino.h>
#include "NewPing.h"
 
// Maximum Distance is 400 cm
// The sensors are set in three-pin mode (echo and trig together)
// Define pins
#define TRIG_PIN_1  13
#define ECHO_PIN_1  13
#define TRIG_PIN_2  12
#define ECHO_PIN_2  12
#define TRIG_PIN_3  11
#define ECHO_PIN_3  11
#define MAX_DISTANCE 400

// NewPing is a library to use easily the ultrasonic sensor
// With NewPing, we can use 3-pins mode
NewPing sonar1(TRIG_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIG_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
NewPing sonar3(TRIG_PIN_3, ECHO_PIN_3, MAX_DISTANCE);
 
// Time of flight of the sound wave (s)
float duration1; 
float duration2; 
float duration3; 
// Distance (cm)
float distance1; 
float distance2;
float distance3;
// Speed of sound (cm/ms)
float soundcm = 0.0343;
// Iteration for average calculation
int iterations = 3;
// Time delay between soundwave of each sensor, to avoid cross talking
int timedelay  = 100; 
 
void setup() {
  Serial.begin (9600);
}
 
void loop() {
  // The function ping.median calculates an average of several measurements (iterations)
  duration1 = sonar1.ping_median(iterations);
  delay(timedelay);
  duration2 = sonar2.ping_median(iterations);
  delay(timedelay);
  duration3 = sonar3.ping_median(iterations);
  delay(timedelay);
  // Calculate the distances for both sensors
  distance1 = (duration1 / 2) * soundcm;
  distance2 = (duration2 / 2) * soundcm;
  distance3 = (duration3 / 2) * soundcm;
 
  // Send results to Serial Monitor
  Serial.print("Distance 1: ");
  if (distance1 >= 400 || distance1 <= 2) {
    Serial.print("Out of range ");
  }
  else {
    Serial.print(distance1);
    Serial.print(" cm ");
  }
  // Distance 2
  Serial.print("Distance 2: ");
  if (distance2 >= 400 || distance2 <= 2) {
    Serial.print("Out of range ");
  }
  else {
    Serial.print(distance2);
    Serial.print(" cm ");
  }  
  // Distance 3
  Serial.print("Distance 3: ");
  if (distance3 >= 400 || distance3 <= 2) {
    Serial.print("Out of range ");
  }
  else {
    Serial.print(distance3);
    Serial.print(" cm ");
  }  
  Serial.println(" ");
}
