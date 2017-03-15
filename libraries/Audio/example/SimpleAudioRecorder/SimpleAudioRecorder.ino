/*
  Simple Audio Recorder

 Demonstrates the use of the Audio library for the Arduino OTTO

 Hardware required :
 * SD card in the Arduino OTTO slot
 * Only 48kHz supported for now

 Original by Frederic Pillon November 09, 2016
 Modified by Francesco Alessi March 15 2017

 This example code is in the public domain

 * A sound file named "record.wav" in the root directory of the SD card
 * will be created. Record duration is 30 seconds.

*/

#include <SD.h>
#include <Audio.h>

const char recFile[] = "test.wav";
#define AUDIO_IN_FREQUENCY           BSP_AUDIO_FREQUENCY_48K
#define DEFAULT_TIME_REC             30  // Recording time in second (default: 30s)
#define REC_SAMPLE_LENGTH   (DEFAULT_TIME_REC * AUDIO_IN_FREQUENCY * DEFAULT_AUDIO_IN_CHANNEL_NBR * 2)
#define RECORD_5PERCENT     ((5*REC_SAMPLE_LENGTH)/100)

void setup() {
  // initialize SerialUSB communication at 115200 bits per second:
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
  uint8_t status = 0;
  WAVE_FormatTypeDef WaveFormat;
  uint8_t pHeaderBuff[44];
  const int S = 1024; // Number of samples to read in block
  uint32_t byteswritten = 0;
  uint32_t count = 0;
  delay(1000);
  // removing old file
  while(SD.exists(recFile) == TRUE)
  {
    SerialUSB.print("Removing file ");
    SerialUSB.print(recFile);
    SerialUSB.print("...");
    SD.remove(recFile);
    SerialUSB.println("done");
  }


  File myFile = SD.open(recFile, FILE_WRITE);

  if (!SD.exists(recFile)) {

    // If the file didn't open, print an error and stop
    SerialUSB.print("Error: failed to create ");
    SerialUSB.println(recFile);
    while (true);
  } else {
    SerialUSB.print(recFile);
    SerialUSB.println(" created succesfully.");
  }

  // Initialize header file
  status = WavProcess_EncInit(&WaveFormat, AUDIO_IN_FREQUENCY, pHeaderBuff);
  if( status != 0 ) {
    SerialUSB.print("Error: could not encode wav header: ");
    SerialUSB.println(status, DEC);
    while (true);
  }
  if (myFile.write(pHeaderBuff, sizeof(pHeaderBuff)) != sizeof(pHeaderBuff)){
    SerialUSB.print("Error: could not write header to ");
    SerialUSB.println(recFile);
    while (true);
  }

  delay(1000);
  SerialUSB.println("Starting AUDIO recorder");
  delay(1000);
  status = Audio.begin(WaveFormat.SampleRate, 100, AUDIO_IN);
  if (status != 0) {
    SerialUSB.print("Error: Audio could not begin: ");
    SerialUSB.println(status, DEC);
    while (true);
  } else {
    SerialUSB.println("Audio begin: OK");
  }

  delay(1000);

  // Prepare samples
  SerialUSB.println("Recording...");
  int volume = 100;
  Audio.prepare(NULL, S, volume);
  delay(1000);

  // MAX Recording time reached, so stop audio interface and close file
  while ( Audio.getSampleIn() < REC_SAMPLE_LENGTH) {
    if ( Audio.isBufferInFull()) {
      byteswritten = myFile.write((uint8_t*)Audio.getBufferInWithOffset(), Audio.getBufferInSize());
      Audio.setBufferInEmpty(byteswritten);
    }

    // Display percent of recording every 5%
    if ( ((Audio.getSampleIn() / RECORD_5PERCENT) - count) == 1)
    {
      count++;
      SerialUSB.print(5*count, DEC);
      SerialUSB.println("%");
    }

  }

  // Update wav header file
  if (myFile.seek(0) == TRUE)
  {
      // Update the wav file header and save it into wav file
      WavProcess_HeaderUpdate(pHeaderBuff, Audio.getSampleIn());
      if (myFile.write(pHeaderBuff, sizeof(pHeaderBuff)) != sizeof(pHeaderBuff)){
        SerialUSB.print("Error: header not updated to ");
        SerialUSB.println(recFile);
        while (true);
      }
  }
  else
  {
    SerialUSB.println("Error: could not update wav header.");
    while (true);
  }

  SerialUSB.println("End of recording. Thank you!");
  Audio.end();
  myFile.close();
  while(1);
  }
