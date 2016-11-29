#include <SD.h>

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
#define BUFFERSIZE                       (COUNTOF(wtext) -1)

uint32_t file_size = 0, seek_val = FALSE, peek_val = 0;
uint32_t byteswritten, bytesread = 0;
/* File write buffer */
uint8_t wtext[] =  "This is the OTTO SD Test working with FatFs.";
/* File read buffer */
uint8_t rtext[BUFFERSIZE];
uint32_t i = 0;
uint8_t isdir = FALSE;
File MyFile;

void setup()
{
  Serial.begin(9600);
  while (!Serial);

  /* Test begin() method */
  while (SD.begin(SD_DETECT_PIN) != TRUE)
  {
    delay(10);
  }
  delay(100);

  /* Test mkdir() method */
  Serial.println("Creating 'STM32F4' directory");
  SD.mkdir("STM32F4");
  Serial.println("Creating 'ARDUINO' directory");
  SD.mkdir("ARDUINO");
  Serial.println("Creating 'ARDUINO/OTTO' directory");
  SD.mkdir("ARDUINO/OTTO");

  /* Test open() method */
  Serial.println("Opening 'STM32F4/Toremove.txt' file");
  MyFile = SD.open("STM32F4/Toremove.txt", FILE_WRITE);
  if(MyFile) {
    Serial.println("Closing 'STM32F4/Toremove.txt' file");
    MyFile.close();
  } else {
    Serial.println("Error to open 'STM32F4/Toremove.txt' file");
  }
  Serial.println("Opening 'ARDUINO/OTTO/ARDUINO_OTTO_TEXT.txt' file");
  MyFile = SD.open("ARDUINO/OTTO/ARDUINO_OTTO_TEXT.txt", FILE_WRITE);
  if(MyFile) {
    /* Test print() method */
    Serial.print("writing \"");
    Serial.print((const char*)wtext);
    Serial.println("\" into ARDUINO_OTTO_TEXT.txt file");
    byteswritten = MyFile.print((const char*)wtext);
    byteswritten += MyFile.print("\n");
    Serial.print(byteswritten, DEC);
    Serial.println(" bytes written.");
    Serial.println("Closing 'ARDUINO/OTTO/ARDUINO_OTTO_TEXT.txt' file");
    MyFile.close();
  } else {
    Serial.println("Error to open 'ARDUINO/OTTO/ARDUINO_OTTO_TEXT.txt' file");
  }

  Serial.println("Opening 'ARDUINO/OTTO/ARDUINO_OTTO_TEXT.txt' file");
  MyFile = SD.open("ARDUINO/OTTO/ARDUINO_OTTO_TEXT.txt");
  if(MyFile) {
    bytesread = MyFile.read(rtext, MyFile.size());
    Serial.println("Closing 'ARDUINO/OTTO/ARDUINO_OTTO_TEXT.txt' file");
    MyFile.close();
  } else {
    Serial.println("Error to open 'ARDUINO/OTTO/ARDUINO_OTTO_TEXT.txt' file");
  }

  Serial.println("Opening 'ARDUINO/OTTO/TEXT.txt' file");
  MyFile = SD.open("ARDUINO/OTTO/TEXT.txt", FILE_WRITE);
  if(MyFile) {
    byteswritten = MyFile.print((const char*)rtext);
    MyFile.flush();
    Serial.println("Closing 'ARDUINO/OTTO/TEXT.txt' file");
    MyFile.close();
  } else {
    Serial.println("Error to open 'ARDUINO/OTTO/TEXT.txt' file");
  }

  Serial.println("Opening 'ARDUINO/OTTO/TEXT.txt' file");
  MyFile = SD.open("ARDUINO/OTTO/TEXT.txt");
  if(MyFile) {
    /* Test size() method */
    file_size = MyFile.size();
    Serial.print("TEXT.txt size: ");
    Serial.println(file_size);

    /* Test position and seek method */
    Serial.print("TEXT.txt position value: ");
    Serial.println(MyFile.position());
    if(!MyFile.seek(MyFile.size()+1)) {
      Serial.println("TEXT.txt seek value over size: OK");
    } else {
      Serial.println("TEXT.txt seek value over size: KO");
    }
    if(MyFile.seek(MyFile.size())) {
      Serial.println("TEXT.txt seek value to size: OK");
    } else {
      Serial.println("TEXT.txt seek value to size: KO");
    }
    Serial.print("TEXT.txt position value: ");
    Serial.println(MyFile.position());

    if(MyFile.seek(0)) {
      Serial.println("TEXT.txt seek value to 0: OK");
    } else {
      Serial.println("TEXT.txt seek value to 0: KO");
    }
    Serial.print("TEXT.txt position value: ");
    Serial.println(MyFile.position());

    /* Test peek() method */
    Serial.println("TEXT.txt peek (10 times): ");
    for(i = 0; i<10; i++)
    {
      peek_val = MyFile.peek();
      Serial.print(peek_val);
      Serial.print(" '");
      Serial.write(peek_val);
      Serial.println("'");
    }
    i = 0;

    /* Test available() and read() methods */
    Serial.println("TEXT.txt content read byte per byte: ");
    while(MyFile.available())
    {
      rtext[i] = (uint8)MyFile.read();
      Serial.print(rtext[i]);
      Serial.print(" '");
      Serial.write(rtext[i]);
      Serial.println("'");
      i++;
    }
    /* Test close method */
    Serial.println("Closing 'ARDUINO/OTTO/TEXT.txt' file");
    MyFile.close();
  } else {
    Serial.println("Error to open 'ARDUINO/OTTO/TEXT.txt' file");
  }

  /* Test isDirectory() method */
  MyFile = File("STM32F4");
  if(MyFile) {
    Serial.print("Is 'STM32F4' is a dir: ");
    if (MyFile.isDirectory())
      Serial.println("OK");
    else
      Serial.println("KO");
  } else {
    Serial.println("Error to open 'STM32F4' dir");
  }

  Serial.println("Opening 'STM32F4/Toremove.txt' file");
  MyFile = SD.open("STM32F4/Toremove.txt");
  if(MyFile) {
    Serial.print("Is 'STM32F4/Toremove.txt' is a file: ");
    if (MyFile.isDirectory())
      Serial.println("KO");
    else
      Serial.println("OK");
    Serial.println("Closing 'STM32F4/Toremove.txt' file");
    MyFile.close();
  } else {
    Serial.println("Error to open 'STM32F4/Toremove.txt' file");
  }
  /* Test exists(), remove() and rmdir() methods */
  Serial.print("Removing 'STM32F4/Toremove.txt' file...");
  while(SD.exists("STM32F4/Toremove.txt") == TRUE)
  {
    SD.remove("STM32F4/Toremove.txt");
   }
  Serial.println("done");

  Serial.print("Removing 'STM32F4' dir...");
  while(SD.exists("STM32F4") == TRUE)
  {
    SD.rmdir("STM32F4");
   }
  Serial.println("done");

  /* Test println(), println(data) methods */
  Serial.println("Opening 'ARDUINO/OTTO/PRINT.txt' file");
  MyFile = SD.open("ARDUINO/OTTO/PRINT.txt", FILE_WRITE);
  if(MyFile) {
    String str = String("This is a String object on line 7");
    Serial.print("Printing to 'ARDUINO/OTTO/PRINT.txt' file...");
    MyFile.println("This should be line 1");
    MyFile.println();
    MyFile.println("This should be line 3");
    MyFile.println("This should be line 4");
    MyFile.println();
    MyFile.println("This should be line 6");
    MyFile.println(str);
    Serial.println("done");
    Serial.println("Closing 'ARDUINO/OTTO/PRINT.txt' file");
    MyFile.close();
  } else {
    Serial.println("Error to open 'ARDUINO/OTTO/PRINT.txt' file");
  }

  /* Test write(buf, len) method */
  Serial.println("Opening 'ARDUINO/OTTO/WRITE.txt' file");
  MyFile = SD.open("ARDUINO/OTTO/WRITE.txt", FILE_WRITE);
  if(MyFile) {
    Serial.print("Writing 'ARDUINO/OTTO/WRITE.txt' file: ");
    byteswritten = MyFile.write(wtext, BUFFERSIZE);
    Serial.print(byteswritten);
    Serial.println(" bytes written");
    Serial.println("Closing 'ARDUINO/OTTO/WRITE.txt' file");
    MyFile.close();
  } else {
    Serial.println("Error to open 'ARDUINO/OTTO/WRITE.txt' file");
  }

  /* Test read(buf, len) method */
  Serial.println("Opening 'ARDUINO/OTTO/WRITE.txt' file");
  MyFile = SD.open("ARDUINO/OTTO/WRITE.txt");
  if(MyFile) {
    Serial.println("Reading 'ARDUINO/OTTO/WRITE.txt' file:");
    bytesread = MyFile.read(rtext, MyFile.size());
    Serial.println((const char*)rtext);
    Serial.println("Closing 'ARDUINO/OTTO/WRITE.txt' file");
    MyFile.close();
   } else {
    Serial.println("Error to open 'ARDUINO/OTTO/WRITE.txt' file");
  }
  Serial.println("###### End of the SD tests ######");
}

void loop()
{
 // do nothing
}
