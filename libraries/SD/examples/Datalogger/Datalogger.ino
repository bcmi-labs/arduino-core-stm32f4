/*
  SD card datalogger

 This example shows how to log data from three analog sensors
 to an SD card using the SD library.

 The circuit:
 * analog sensors on analog ins A0, A1, and A2
 * SD card

 */

#include <SD.h>

uint32_t A[] = { A0, A1, A2};

void setup()
{
  // Open SerialUSB communications and wait for port to open:
  SerialUSB.begin(115200);
  while (!SerialUSB) {
    ; // wait for SerialUSB port to connect. Needed for Leonardo only
  }

  SerialUSB.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  while (SD.begin(SD_DETECT_PIN) != TRUE)
  {
    delay(10);
  }
  delay(100);
  SerialUSB.println("card initialized.");
}

void loop()
{
  // make a string for assembling the data to log:
  String dataString = "";

  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    int sensor = analogRead(A[analogPin]);
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ",";
    }
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.seek(dataFile.size());
    dataFile.println(dataString);
    dataFile.close();
    // print to the SerialUSB port too:
    SerialUSB.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    SerialUSB.println("error opening datalog.txt");
  }
  delay(100);
}
