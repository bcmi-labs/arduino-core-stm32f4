#include <SD.h>
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
#define BUFFERSIZE                       (COUNTOF(wtext) -1)
  uint32_t file_size = 0, seek_val = FALSE, peek_val = FALSE;
  uint32_t byteswritten, bytesread = 0;
  uint8_t wtext[] =  "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"
                     "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"
                     "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"
                     "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"
                     "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"
                     "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"
                     "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"
                     "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"
                     "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"
                     "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"
                     "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"
                     "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"
                     "This is STM32 working with FatFs. It is to test Arduino based on STM32 HAL. \n"; /* File write buffer */

  uint8_t rtext[BUFFERSIZE];
  uint32_t i = 0;
  uint8_t isdir = FALSE;
  File MyFile;

void setup()
{
  /* Test begin() method */
  while (SD.begin(SD_DETECT_PIN) != TRUE)
  {
    delay(10);
  }

  /* Test mkdir() method */
  SD.mkdir("STM32F4");
  SD.mkdir("ARDUINO");
  SD.mkdir("ARDUINO/OTTO");
  /* Test open() method */
  SD.open("STM32F4/Toremove.txt", FILE_WRITE);
  MyFile = SD.open("ARDUINO/OTTO/ARDUINO_OTTO_TEXT.txt", FILE_WRITE);

  /* Test print() method */
  byteswritten = MyFile.print((const char*)wtext);
  MyFile.close();

  MyFile = SD.open("ARDUINO/OTTO/TEXT.txt");
  /* Test peek() method */
  for(i = 0; i<10; i++)
  {
    peek_val = MyFile.peek();
  }

  /* Test size() method */
  file_size = MyFile.size();

  /* Test seek method */
  seek_val = MyFile.seek(100);

  for(i = 0; i<10; i++)
  {
    peek_val = MyFile.peek();
  }
  i = 0;

   /* Test available() and read() methods */
    while(MyFile.available())
    {
      rtext[i] = (uint8)MyFile.read();
      i++;
     }

  /* Test close method */
  MyFile.close();

  /* Test isDirectory() method */
  MyFile = SD.open("STM32F4");
  isdir = MyFile.isDirectory();
  if(isdir == TRUE)
  MyFile.close();

  /* Test exists(), remove() and rmdir() methods */
  while(SD.exists("STM32F4/Toremove.txt") == TRUE)
  {
    SD.remove("STM32F4/Toremove.txt");
   }

  while(SD.exists("STM32F4") == TRUE)
  {
    SD.remove("STM32F4");
   }

  /* Test println(), println(data) methods */
  MyFile = SD.open("ARDUINO/OTTO/PRINT.txt", FILE_WRITE);
  MyFile.println("This should be line 1");
  MyFile.println();
  MyFile.println("This should be line 3");
  MyFile.println("This should be line 4");
  MyFile.println();
  MyFile.println("This should be line 6");
  MyFile.close();

  /* Test write(buf, len) method */
  MyFile = SD.open("ARDUINO/OTTO/WRITE.txt", FILE_WRITE);
  byteswritten = MyFile.write(wtext, BUFFERSIZE);
  MyFile.close();

  /* Test read(buf, len) method */
  MyFile = SD.open("ARDUINO/OTTO/WRITE.txt");
  file_size = MyFile.size();
  bytesread = MyFile.read(rtext, file_size);
  MyFile.close();  
}

void loop()
{
 // do notting
}
