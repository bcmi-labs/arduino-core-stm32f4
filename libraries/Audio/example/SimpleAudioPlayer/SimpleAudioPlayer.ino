/*
  Simple Audio Player

 Demonstrates the use of the Audio library for the Arduino OTTO

 Hardware required :
 * SD card in the Arduino OTTO slot
 * A sound file named "test.wav" in the root directory of the SD card
 *    Only 22kHz and 48kHz supported for now
 * A speaker to connect to the audio amplifier

 Original by Massimo Banzi September 20, 2012
 Modified by Scott Fitzgerald October 19, 2012
 Modified by Laurent Meunier 2016 - based with STM32 MCD Application examples support
 Modified by Francesco Alessi October 25, 2016

 This example code is in the public domain
*/

#include <SD.h>
#include <Audio.h>

const char recFile[] = "record.wav";

void setup() {
  // initialize serial communication at 9600 bits per second:
  SerialUSB.begin(115200);
  while(!SerialUSB);
  SerialUSB.print("Detecting SD");
  int counter = 0;
  while (SD.begin(SD_DETECT_PIN) != TRUE)
  {
    SerialUSB.print(".");
    delay(500);
    if (counter == 10)
    {
      SerialUSB.println(".");
      SerialUSB.println("SD Card not detected!");
      SerialUSB.print("Detecting SD");
      counter = 0;
    }
    counter++;
  }
  SerialUSB.println("...done.");
}

void loop() {
  int count = 0;
  WAVE_FormatTypeDef WaveFormat;
  const int S = 1024; // Number of samples to read in block
  uint32_t buffer[S];
  int duration;
  delay(1000);        // delay for console

  File myFile = SD.open(recFile);
  if (!myFile.available()) {
    // if the file didn't open, print an error and stop
    SerialUSB.print("error opening ");
    SerialUSB.println(recFile);
    while (true);
  } else {
    SerialUSB.println(recFile);
    SerialUSB.println(" open OK");
  }

  myFile.read((void*) &WaveFormat, sizeof(WaveFormat));

  delay(1000);
  SerialUSB.println("Starting Playback");
  delay(1000);
  Audio.begin(WaveFormat.SampleRate, 100);

  delay(1000);

  // Prepare samples
  int volume = 50;
  Audio.prepare(NULL, S, volume);

  delay(1000);

  while (myFile.available()) {
    // Every 100 block print a '.'
    count++;
    if (count == 1000) {
      SerialUSB.print(".");
      count = 0;
    }
    // read from the file into buffer
    myFile.read(buffer, sizeof(buffer));

    // Feed samples to audio
    Audio.write(buffer, sizeof(buffer));
  }
  /* reaching end of file */
  SerialUSB.println("End of file. Thank you for listening!");
  Audio.end();
  myFile.close();

  delay(5000);
  SerialUSB.println("Restart Playing");

  }
