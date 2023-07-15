#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>

//**********************************************
// Variable declaration
//**********************************************
const int chipSelect = BUILTIN_SDCARD;
String inputSerial1 = "";       // a string to hold incoming data
boolean IsReadySerial1 = false; // whether the string is complete
File mySensorData;              // Data object you will write your sesnor data to

//**********************************************
// Function declaration
//**********************************************
void SelectSentences();
void serialEvent1();

//**********************************************
// Setup
//**********************************************
void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ; // wait for serial port to connect.
  // GPS initialization
  Serial.println("Initializing GPS ...");
  Serial1.begin(9600);
  delay(100);
  SelectSentences();
  delay(100);
  Serial.println("GPS Initialized");

  // SD initialization
  Serial.println("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect))
  {
    Serial.println("Card failed, or not present");
    while (1)
    {
      // No SD card, so don't do anything more - stay stuck here
    }
  }
  Serial.println("SD card initialized.");

  // Serial.println("Press any key to start the main program.");
  // while (!Serial.available())
  //   ;
  // Serial.read();
  delay(100);
}

//**********************************************
// Main loop
//**********************************************
void loop()
{
  if (IsReadySerial1) // Does Seria11 have a new message?
  {
    mySensorData = SD.open("NMEA.txt", FILE_WRITE); // Open file on SD card for writing
    mySensorData.println(inputSerial1);             // Write first NMEA to SD card
    mySensorData.close();                           // Close the file
    Serial.print(inputSerial1);                     // Write on the serial monitor for debugging.
    inputSerial1 = "";                              // Clear the string:
    IsReadySerial1 = false;                         // Reset the serial flag
  }
}

//**********************************************
// Function definition
//**********************************************
void SelectSentences()
{
  // Select RMC and GGA sentences
  // Serial1.println("$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28");
  // Select RMC sentences
  Serial1.println("$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29");
}

void serialEvent1()
{
  // This event is called when Serial1 receives new bytes

  while (Serial1.available() && IsReadySerial1 == false)
  {
    char nextChar = (char)Serial1.read(); // Read the new byte:
    inputSerial1 += nextChar;             // Append to the inputSerial1 string
    // If a newline, then set flag so that the main loop will process the string
    if (nextChar == '\n')
    {
      IsReadySerial1 = true;
    }
  }
}
