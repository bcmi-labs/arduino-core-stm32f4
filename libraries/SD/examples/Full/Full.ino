#include <SD.h>

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
#define BUFFERSIZE                       (COUNTOF(wtext) -1)

uint32_t file_size = 0, seek_val = FALSE, peek_val = 0;
uint32_t byteswritten, bytesread = 0;
/* File write buffer */
uint8_t wtext[] =  "This is the Arduino SD Test working with FatFs.";
/* File read buffer */
uint8_t rtext[BUFFERSIZE];
uint32_t i = 0;
uint8_t isdir = FALSE;
File MyFile;

void setup()
{
  SerialUSB.begin(115200);
  while (!SerialUSB);

  /* Test begin() method */
  while (SD.begin(SD_DETECT_PIN) != TRUE)
  {
    delay(10);
  }
  delay(100);

  /* Test mkdir() method */
  SerialUSB.println("Creating 'STM32' directory");
  SD.mkdir("STM32");
  SerialUSB.println("Creating 'ARDUINO' directory");
  SD.mkdir("ARDUINO");
  SerialUSB.println("Creating 'ARDUINO/SD' directory");
  SD.mkdir("ARDUINO/SD");

  /* Test open() method */
  SerialUSB.println("Opening 'STM32/Toremove.txt' file");
  MyFile = SD.open("STM32/Toremove.txt", FILE_WRITE);
  if(MyFile) {
    SerialUSB.println("Closing 'STM32/Toremove.txt' file");
    MyFile.close();
  } else {
    SerialUSB.println("Error to open 'STM32/Toremove.txt' file");
  }
  SerialUSB.println("Opening 'ARDUINO/SD/ARDUINO_SD_TEXT.txt' file");
  MyFile = SD.open("ARDUINO/SD/ARDUINO_SD_TEXT.txt", FILE_WRITE);
  if(MyFile) {
    /* Test print() method */
    SerialUSB.print("writing \"");
    SerialUSB.print((const char*)wtext);
    SerialUSB.println("\" into ARDUINO_SD_TEXT.txt file");
    byteswritten = MyFile.print((const char*)wtext);
    byteswritten += MyFile.print("\n");
    SerialUSB.print(byteswritten, DEC);
    SerialUSB.println(" bytes written.");
    SerialUSB.println("Closing 'ARDUINO/SD/ARDUINO_SD_TEXT.txt' file");
    MyFile.close();
  } else {
    SerialUSB.println("Error to open 'ARDUINO/SD/ARDUINO_SD_TEXT.txt' file");
  }

  SerialUSB.println("Opening 'ARDUINO/SD/ARDUINO_SD_TEXT.txt' file");
  MyFile = SD.open("ARDUINO/SD/ARDUINO_SD_TEXT.txt");
  if(MyFile) {
    bytesread = MyFile.read(rtext, MyFile.size());
    SerialUSB.println("Closing 'ARDUINO/SD/ARDUINO_SD_TEXT.txt' file");
    MyFile.close();
  } else {
    SerialUSB.println("Error to open 'ARDUINO/SD/ARDUINO_SD_TEXT.txt' file");
  }

  SerialUSB.println("Opening 'ARDUINO/SD/TEXT.txt' file");
  MyFile = SD.open("ARDUINO/SD/TEXT.txt", FILE_WRITE);
  if(MyFile) {
    byteswritten = MyFile.print((const char*)rtext);
    MyFile.flush();
    SerialUSB.println("Closing 'ARDUINO/SD/TEXT.txt' file");
    MyFile.close();
  } else {
    SerialUSB.println("Error to open 'ARDUINO/SD/TEXT.txt' file");
  }

  SerialUSB.println("Opening 'ARDUINO/SD/TEXT.txt' file");
  MyFile = SD.open("ARDUINO/SD/TEXT.txt");
  if(MyFile) {
    /* Test size() method */
    file_size = MyFile.size();
    SerialUSB.print("TEXT.txt size: ");
    SerialUSB.println(file_size);

    /* Test position and seek method */
    SerialUSB.print("TEXT.txt position value: ");
    SerialUSB.println(MyFile.position());
    if(!MyFile.seek(MyFile.size()+1)) {
      SerialUSB.println("TEXT.txt seek value over size: OK");
    } else {
      SerialUSB.println("TEXT.txt seek value over size: KO");
    }
    if(MyFile.seek(MyFile.size())) {
      SerialUSB.println("TEXT.txt seek value to size: OK");
    } else {
      SerialUSB.println("TEXT.txt seek value to size: KO");
    }
    SerialUSB.print("TEXT.txt position value: ");
    SerialUSB.println(MyFile.position());

    if(MyFile.seek(0)) {
      SerialUSB.println("TEXT.txt seek value to 0: OK");
    } else {
      SerialUSB.println("TEXT.txt seek value to 0: KO");
    }
    SerialUSB.print("TEXT.txt position value: ");
    SerialUSB.println(MyFile.position());

    /* Test peek() method */
    SerialUSB.println("TEXT.txt peek (10 times): ");
    for(i = 0; i<10; i++)
    {
      peek_val = MyFile.peek();
      SerialUSB.print(peek_val);
      SerialUSB.print(" '");
      SerialUSB.write(peek_val);
      SerialUSB.println("'");
    }
    i = 0;

    /* Test available() and read() methods */
    SerialUSB.println("TEXT.txt content read byte per byte: ");
    while(MyFile.available())
    {
      rtext[i] = (uint8_t)MyFile.read();
      SerialUSB.print(rtext[i]);
      SerialUSB.print(" '");
      SerialUSB.write(rtext[i]);
      SerialUSB.println("'");
      i++;
    }
    /* Test close method */
    SerialUSB.println("Closing 'ARDUINO/SD/TEXT.txt' file");
    MyFile.close();
  } else {
    SerialUSB.println("Error to open 'ARDUINO/SD/TEXT.txt' file");
  }

  /* Test isDirectory() method */
  MyFile = File("STM32");
  if(MyFile) {
    SerialUSB.print("Is 'STM32' is a dir: ");
    if (MyFile.isDirectory())
      SerialUSB.println("OK");
    else
      SerialUSB.println("KO");
  } else {
    SerialUSB.println("Error to open 'STM32' dir");
  }

  SerialUSB.println("Opening 'STM32/Toremove.txt' file");
  MyFile = SD.open("STM32/Toremove.txt");
  if(MyFile) {
    SerialUSB.print("Is 'STM32/Toremove.txt' is a file: ");
    if (MyFile.isDirectory())
      SerialUSB.println("KO");
    else
      SerialUSB.println("OK");
    SerialUSB.println("Closing 'STM32/Toremove.txt' file");
    MyFile.close();
  } else {
    SerialUSB.println("Error to open 'STM32/Toremove.txt' file");
  }
  /* Test exists(), remove() and rmdir() methods */
  SerialUSB.print("Removing 'STM32/Toremove.txt' file...");
  while(SD.exists("STM32/Toremove.txt") == TRUE)
  {
    SD.remove("STM32/Toremove.txt");
   }
  SerialUSB.println("done");

  SerialUSB.print("Removing 'STM32' dir...");
  while(SD.exists("STM32") == TRUE)
  {
    SD.rmdir("STM32");
   }
  SerialUSB.println("done");

  /* Test println(), println(data) methods */
  SerialUSB.println("Opening 'ARDUINO/SD/PRINT.txt' file");
  MyFile = SD.open("ARDUINO/SD/PRINT.txt", FILE_WRITE);
  if(MyFile) {
    String str = String("This is a String object on line 7");
    SerialUSB.print("Printing to 'ARDUINO/SD/PRINT.txt' file...");
    MyFile.println("This should be line 1");
    MyFile.println();
    MyFile.println("This should be line 3");
    MyFile.println("This should be line 4");
    MyFile.println();
    MyFile.println("This should be line 6");
    MyFile.println(str);
    SerialUSB.println("done");
    SerialUSB.println("Closing 'ARDUINO/SD/PRINT.txt' file");
    MyFile.close();
  } else {
    SerialUSB.println("Error to open 'ARDUINO/SD/PRINT.txt' file");
  }

  /* Test write(buf, len) method */
  SerialUSB.println("Opening 'ARDUINO/SD/WRITE.txt' file");
  MyFile = SD.open("ARDUINO/SD/WRITE.txt", FILE_WRITE);
  if(MyFile) {
    SerialUSB.print("Writing 'ARDUINO/SD/WRITE.txt' file: ");
    byteswritten = MyFile.write(wtext, BUFFERSIZE);
    SerialUSB.print(byteswritten);
    SerialUSB.println(" bytes written");
    SerialUSB.println("Closing 'ARDUINO/SD/WRITE.txt' file");
    MyFile.close();
  } else {
    SerialUSB.println("Error to open 'ARDUINO/SD/WRITE.txt' file");
  }

  /* Test read(buf, len) method */
  SerialUSB.println("Opening 'ARDUINO/SD/WRITE.txt' file");
  MyFile = SD.open("ARDUINO/SD/WRITE.txt");
  if(MyFile) {
    SerialUSB.println("Reading 'ARDUINO/SD/WRITE.txt' file:");
    bytesread = MyFile.read(rtext, MyFile.size());
    SerialUSB.println((const char*)rtext);
    SerialUSB.println("Closing 'ARDUINO/SD/WRITE.txt' file");
    MyFile.close();
   } else {
    SerialUSB.println("Error to open 'ARDUINO/SD/WRITE.txt' file");
  }
  SerialUSB.println("###### End of the SD tests ######");
}

void loop()
{
 // do nothing
}
