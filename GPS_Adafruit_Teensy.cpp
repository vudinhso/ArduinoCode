#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>

// #include <SoftwareSerial.h>
// #include <Adafruit_GPS.h>

const int chipSelect = BUILTIN_SDCARD;

// put function declarations here:
void SelectSentences();
void serialEvent1();

String inputSerial1 = "";       // a string to hold incoming data
boolean IsReadySerial1 = false; // whether the string is complete

// String NMEA1; // We will use this variable to hold our first NMEA sentence
// char c;       // Used to read the characters spewing from the GPS module

File mySensorData; // Data object you will write your sesnor data to

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial)
    ; // wait for serial port to connect.
  Serial.println("Initializing GPS ...");
  Serial1.begin(9600);
  delay(100);
  SelectSentences();
  delay(100);
  Serial.println("GPS Initialized");

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

void loop()
{
  // Does Seria11 have a new message?
  if (IsReadySerial1)
  {
    // Print new message on a new line.
    // The last character of the inputSerial1 is a new line
    Serial.print(inputSerial1);
    mySensorData = SD.open("NMEA.txt", FILE_WRITE); // Open file on SD card for writing
    mySensorData.println(inputSerial1);             // Write first NMEA to SD card
    mySensorData.close();                           // Close the file
    // Serial.println("data logged");

    // clear the string:
    inputSerial1 = "";
    IsReadySerial1 = false;
  }
}

// put function definitions here:
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
    // Read the new byte:
    char nextChar = (char)Serial1.read();

    // Append to the inputSerial1 string
    inputSerial1 += nextChar;

    // If a newline, then set flag so that the main loop will process the string
    if (nextChar == '\n')
    {
      IsReadySerial1 = true;
    }
  }
}
