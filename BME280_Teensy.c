#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//**********************************************
// General Information
//**********************************************
// Teensy 4.1 has 3 I2C communication channel
// SDA 18, 17, 25
// SCL 19, 16, 24
// The SDA and SCL of the BME280 must be connected to one of these channel
// Define the channel used with https://www.pjrc.com/teensy/td_libs_Wire.html
// Moreover, our BME280 works on 3.3V. Others can work on 5V if there's a voltage regulator

//**********************************************
// Variable declaration
//**********************************************
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;

//**********************************************
// Function declaration
//**********************************************
void SerialDataWrite();

//**********************************************
// Void Setup
//**********************************************
void setup()
{
  Serial.begin(9600);

  if (!bme.begin(0x76)) // Check the address: it can be 0x77 as well
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1)
      ;
  }
}

//**********************************************
// Void Loop
//**********************************************
void loop()
{
  SerialDataWrite();
  delay(1000);
}

//**********************************************
// Function definition
//**********************************************
void SerialDataWrite()
{
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println("*C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println("hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println("m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println("%");

  Serial.println();
}
