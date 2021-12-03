#include <Arduino.h>

int IN1 = 12;
int IN2 = 14;
int PWMA = 13;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:   
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // analogWrite(PWMA, 128);
  // increase the PWM
  for(int dutyCycle = 0; dutyCycle < 255; dutyCycle++){   
    analogWrite(PWMA, dutyCycle);
    delay(100);
  }
  // decrease the PWM
  for(int dutyCycle = 255; dutyCycle > 0; dutyCycle--){
    analogWrite(PWMA, dutyCycle);
    delay(100);
  }
}
