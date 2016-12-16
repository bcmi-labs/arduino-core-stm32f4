/*
  Simple Audio Recorder

 Demonstrates the use of the Audio library for the Arduino OTTO

 Hardware required :
 * SD card in the Arduino OTTO slot
 * Only 48kHz supported for now

 Original by Frederic Pillon November 09, 2016

 This example code is in the public domain
 
 * A sound file named "record.wav" in the root directory of the SD card
 * will be created. Record duration is 30 seconds.

*/

#include <SD.h>
#include <Audio.h>

const char recFile[] = "record.wav";
#define AUDIO_IN_FREQUENCY           BSP_AUDIO_FREQUENCY_48K
#define DEFAULT_TIME_REC             30  // Recording time in second (default: 30s)
#define REC_SAMPLE_LENGTH   (DEFAULT_TIME_REC * AUDIO_IN_FREQUENCY * DEFAULT_AUDIO_IN_CHANNEL_NBR * 2)
#define RECORD_5PERCENT     ((5*REC_SAMPLE_LENGTH)/100)

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  delay(15000);

  while (SD.begin(SD_DETECT_PIN) != TRUE)
  {
    delay(10);
  }
}

void loop() {
  uint8_t status = 0;
  WAVE_FormatTypeDef WaveFormat;
  uint8_t pHeaderBuff[44];
  const int S = 1024; // Number of samples to read in block
  uint32_t byteswritten = 0;
  uint32_t count = 0;
  delay(4000);        // delay for console

  File myFile = SD.open(recFile, FILE_WRITE);
  if (!SD.exists(recFile)) {
    // If the file didn't open, print an error and stop
    Serial.print("Error: failed to create ");
    Serial.println(recFile);
    while (true);
  } else {
    Serial.print(recFile);
    Serial.println(" created succesfully.");
  }

  // Initialize header file
  status = WavProcess_EncInit(&WaveFormat, AUDIO_IN_FREQUENCY, pHeaderBuff);
  if( status != 0 ) {
    Serial.print("Error: could not encode wav header: ");
    Serial.println(status, DEC);
    while (true);      
  }
  if (myFile.write(pHeaderBuff, sizeof(pHeaderBuff)) != sizeof(pHeaderBuff)){
    Serial.print("Error: could not write header to ");
    Serial.println(recFile);
    while (true);
  }

  delay(1000);
  Serial.println("Start AUDIO record");
  delay(1000);
  status = Audio.begin(WaveFormat.SampleRate, 100, AUDIO_IN);
  if (status != 0) {
    Serial.print("Error: Audio could not begin: ");
    Serial.println(status, DEC);
    while (true);
  } else {
    Serial.println("Audio begin: OK");
  }

  delay(1000);

  // Prepare samples
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
      Serial.print(5*count, DEC);
      Serial.println("%");
    }
    
  }
  
  // Update wav header file
  if (myFile.seek(0) == TRUE)
  {
      // Update the wav file header and save it into wav file
      WavProcess_HeaderUpdate(pHeaderBuff, Audio.getSampleIn());
      if (myFile.write(pHeaderBuff, sizeof(pHeaderBuff)) != sizeof(pHeaderBuff)){
        Serial.print("Error: header not updated to ");
        Serial.println(recFile);
        while (true);
      }
  }
  else
  {
    Serial.println("Error: could not update wav header.");
    while (true);
  }

  Serial.println("End of recording. Thank you!");
  Audio.end();
  myFile.close();
  while(1);
  }
