/*
  Simple Audio Player With Debug

 Demonstrates the use of the Audio library for the Arduino OTTO

 Hardware required :
 * SD card in the Arduino OTTO slot
 * A sound file named "test.wav" in the root directory of the SD card
 *    Only 22MHz and 48MHz supported for now
 * A speaker to connect to the audio amplifier

 Original by Massimo Banzi September 20, 2012
 Modified by Scott Fitzgerald October 19, 2012
 Modified by Laurent Meunier 2016 - based with STM32 MCD Application examples support
 Modified by Francesco Alessi October 25, 2016

 This example code is in the public domain
*/

#include <SD.h>
#include <Audio.h>

typedef struct {
  uint32_t ChunkID;       /* 0 */
  uint32_t FileSize;      /* 4 */
  uint32_t FileFormat;    /* 8 */
  uint32_t SubChunk1ID;   /* 12 */
  uint32_t SubChunk1Size; /* 16*/
  uint16_t AudioFormat;   /* 20 */
  uint16_t NbrChannels;   /* 22 */
  uint32_t SampleRate;    /* 24 */

  uint32_t ByteRate;      /* 28 */
  uint16_t BlockAlign;    /* 32 */
  uint16_t BitPerSample;  /* 34 */
  uint32_t SubChunk2ID;   /* 36 */
  uint32_t SubChunk2Size; /* 40 */
}WAVE_FormatTypeDef;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  delay(15000);

  /* Test begin() method */
  while (SD.begin(SD_DETECT_PIN) != TRUE)
  {
    delay(10);
  }
}

void loop() {
  int count = 0;
  WAVE_FormatTypeDef WaveFormat;
  const int S = 1024; // Number of samples to read in block
  uint32_t buffer[S];
  int duration;
  delay(5000);        // delay for console

  File myFile = SD.open("test.wav");
  if (!myFile.available()) {
    // if the file didn't open, print an error and stop
    Serial.println("error opening test.wav");
    while (true);
  } else {
    Serial.println("test.wav open OK");
  }

  myFile.read((void*) &WaveFormat, sizeof(WaveFormat));

  delay(1000);
  Serial.println("STARTUP AUDIO\r\n");
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
      Serial.print(".");
      count = 0;
    }
    // read from the file into buffer
    myFile.read(buffer, sizeof(buffer));

    // Feed samples to audio
    Audio.write(buffer, sizeof(buffer));
  }
  /* reaching end of file */
  Serial.println("End of file. Thank you for listening!");
  Audio.end();
  myFile.close();

  delay(5000);
  Serial.println("Restart Playing");

  }
