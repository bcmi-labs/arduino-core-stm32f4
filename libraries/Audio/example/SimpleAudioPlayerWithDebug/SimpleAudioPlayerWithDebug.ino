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

int i2c_status;
int error_status;
int sd_status;
int audio_status;
int cb_error;

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
  i2c_status = 0;
  cb_error = 0;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Starting...");


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
  //delay(5000);        // delay for console

  File myFile = SD.open("test.wav");
  if (!myFile.available()) {
    // if the file didn't open, print an error and stop
    Serial.println("error opening .wav");
    while (true);
  } else {
    Serial.println(".wav open OK");
  }

  myFile.read((void*) &WaveFormat, sizeof(WaveFormat));
  Serial.print("Sample rate: ");
  Serial.print(WaveFormat.SampleRate);
  Serial.println(" Hz ");
  Serial.print("Byte rate: ");
  Serial.print(WaveFormat.ByteRate);
  Serial.println(" Hz");
  Serial.print("Bytes per sample: ");
  Serial.println(WaveFormat.ByteRate / WaveFormat.SampleRate);
  Serial.print("Channels number: ");
  Serial.println(WaveFormat.NbrChannels);
  duration = WaveFormat.FileSize / WaveFormat.ByteRate;
  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.println(" sec");
  Serial.print("File Size : ");
  Serial.print((int)(WaveFormat.FileSize/1024));
  Serial.println(" KB");

  //delay(1000);
  Serial.println("STARTUP AUDIO\r\n");
  //delay(1000);
  audio_status = Audio.begin(WaveFormat.SampleRate, 100);

 // delay(1000);

  if(audio_status > 0) {
    Serial.println("ERROR in AUDIO INIT");
  }

  Serial.println("Prepare Playing");

  // Prepare samples
  int volume = 100;
  Audio.prepare(NULL, S, volume);

  Serial.println("Playing");

  Serial.println(Audio.getBuffer());
  Serial.println(Audio.getHalf());
  Serial.println(Audio.getLast());
  Serial.println(Audio.getBufferSize());

  //delay(1000);

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
  Serial.println("");
  Serial.println("End of file. Thank you for listening!");
  Audio.end();
  myFile.close();

  Serial.println("Printing info");


  Serial.print("i2c_status: ");
  Serial.println(i2c_status);
  Serial.print("error_status: ");
  Serial.println(error_status);
  Serial.print("playedBytes: ");
  Serial.println(Audio.playedBytes());
  Serial.print("receivedBytes: ");
  Serial.println(Audio.receivedBytes());
  Serial.print("cb_error: ");
  Serial.println(cb_error);
  delay(5000);//delay in between reads for stability
  Serial.println("Restart Playing");

}
