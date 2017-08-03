/*
  SD card test

 This example shows how use the utility libraries on which the'
 SD library is based in order to get info about your SD card.
 Very useful for testing a card when you're not sure whether its working or not.

  * SD card attached

 */
// include the SD library:
#include <SD.h>

Sd2Card card;
SdFatFs fatFs;

void setup()
{
  bool disp = false;
  // Open SerialUSB communications and wait for port to open:
  SerialUSB.begin(115200);

  while (!SerialUSB);
  SerialUSB.print("\nInitializing SD card...");
  while(!card.init(SD_DETECT_PIN)) {
    if (!disp) {
      SerialUSB.println("initialization failed. Is a card inserted?");
      disp = true;
    }
    delay(10);
  }

  SerialUSB.println("A card is present.");

  // print the type of card
  SerialUSB.print("\nCard type: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      SerialUSB.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      SerialUSB.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      SerialUSB.println("SDHC");
      break;
    default:
      SerialUSB.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!fatFs.init()) {
    SerialUSB.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }

  // print the type and size of the first FAT-type volume
  uint64_t volumesize;
  SerialUSB.print("\nVolume type is FAT");
  SerialUSB.println(fatFs.fatType(), DEC);
  SerialUSB.println();

  volumesize = fatFs.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= fatFs.clusterCount();       // we'll have a lot of clusters
  volumesize *= 512;                        // SD card blocks are always 512 bytes
  SerialUSB.print("Volume size (bytes): ");
  SerialUSB.println(volumesize);
  SerialUSB.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  SerialUSB.println(volumesize);
  SerialUSB.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  SerialUSB.println(volumesize);


  SerialUSB.println("\nFiles found on the card (name, date and size in bytes): ");
  File root = SD.openRoot();

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  SerialUSB.println("###### End of the SD tests ######");
}

void loop(void) {
  // do nothing
}
