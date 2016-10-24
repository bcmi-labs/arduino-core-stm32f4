/*

 SD - a slightly more friendly wrapper for sdfatlib

 This library aims to expose a subset of SD card functionality
 in the form of a higher level "wrapper" object.

 License: GNU General Public License V3
          (Because sdfatlib is licensed with this.)

 (C) Copyright 2010 SparkFun Electronics


 This library provides four key benefits:

   * Including `SD.h` automatically creates a global
     `SD` object which can be interacted with in a similar
     manner to other standard global objects like `Serial` and `Ethernet`.

   * Boilerplate initialisation code is contained in one method named
     `begin` and no further objects need to be created in order to access
     the SD card.

   * Calls to `open` can supply a full path name including parent
     directories which simplifies interacting with files in subdirectories.

   * Utility methods are provided to determine whether a file exists
     and to create a directory heirarchy.


  Note however that not all functionality provided by the underlying
  sdfatlib library is exposed.

 */

/*

  Implementation Notes

  In order to handle multi-directory path traversal, functionality that
  requires this ability is implemented as callback functions.

  Individual methods call the `walkPath` function which performs the actual
  directory traversal (swapping between two different directory/file handles
  along the way) and at each level calls the supplied callback function.

  Some types of functionality will take an action at each level (e.g. exists
  or make directory) which others will only take an action at the bottom
  level (e.g. open).

 */
extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
	#include "stm32f4xx_hal.h"
}

#include "SD.h"
SDClass SD;

FATFS SDFatFs;  /* File system object for SD disk logical drive */
char SDPath[4]; /* SD disk logical drive path */

/**
  * @brief  Link SD, register the file system object to the FatFs mode and configure
  *         relatives SD IOs except SD Detect Pin
  * @param  None
  * @retval TRUE or FALSE
  */
uint8_t SDClass::begin()
{
  /*##-1- Link the SD disk I/O driver ########################################*/
  if(FATFS_LinkDriver(&SD_Driver, SDPath) == 0)
  {
    /*##-2- Register the file system object to the FatFs module ##############*/
    if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) != FR_OK)
    {
      /* FatFs Initialization Error */
      return FALSE;
    }
    else
    {
      /*##-3- Initializes SD IOs #############################################*/
      if(BSP_SD_Init() != MSD_OK)
      {
       return FALSE;
      }
      else
      {
          return TRUE;
      }
    }
  }
  else
  {
    return FALSE;
  }
}

/**
  * @brief  Link SD, register the file system object to the FatFs mode and configure
  *         relatives SD IOs including SD Detect Pin
  * @param  None
  * @retval TRUE or FALSE
  */
uint8_t SDClass::begin(uint8_t cspin)
{
  /*##-1- Link the SD disk I/O driver ########################################*/
  if(FATFS_LinkDriver(&SD_Driver, SDPath) == 0)
  {
    /*##-2- Register the file system object to the FatFs module ##############*/
    if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 0) != FR_OK)
    {
      /* FatFs Initialization Error */
      return FALSE;
    }
    else
    {
      /*##-3- Initializes SD IOs #############################################*/
      if(BSP_SD_CSInit() != MSD_OK)
      {
       return FALSE;
      }
      else
      {
          return TRUE;
      }
    }
  }
  else
  {
    return FALSE;
  }
}

/**
  * @brief  Check if a file or folder exist on the SD disk
  * @param  filename: File name
  * @retval TRUE or FALSE
  */
uint8_t SDClass::exists(const char *filepath)
{
    FILINFO fno;

    if(f_stat(filepath, &fno) != FR_OK)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/**
  * @brief  Create directory on the SD disk
  * @param  filename: File name
  * @retval TRUE or FALSE
  */
uint8_t SDClass::mkdir(const char *filepath)
{
   if(f_mkdir(filepath) != FR_OK)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/**
  * @brief  Remove directory on the SD disk
  * @param  filename: File name
  * @retval TRUE or FALSE
  */
uint8_t SDClass::rmdir(const char *filepath)
{
    if(f_unlink(filepath) != FR_OK)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/**
  * @brief  Open a file on the SD disk, if not existing it's created
  * @param  filename: File name
  * @retval File object referring to the opened file
  */
File  SDClass::open(const char *filepath)
{
    File file = File();

     file.name = (char*)malloc(strlen(filepath) +1);
     sprintf(file.name, "%s", filepath);

    if(f_open(&file.Fil, filepath, FA_READ) == FR_OK)
    {
         return file;
    }
    else
    {
     return File();
    }
}

/**
  * @brief  Open a file on the SD disk, if not existing it's created
  * @param  filename: File name
  * @param  mode: the mode in which to open the file
  * @retval File object referring to the opened file
  */
File SDClass::open(const char *filepath, uint8_t mode)
{
    File file = File();
     file.name = (char*)malloc(strlen(filepath) +1);
     sprintf(file.name, "%s", filepath);

     if((mode == FILE_WRITE) && (SD.exists(filepath) != TRUE))
     {
        mode = mode | FA_CREATE_ALWAYS;
     }

    if(f_open(&file.Fil, filepath, mode) == FR_OK)
    {
        return file;
    }
    else
    {
     return File();
    }
}

/**
  * @brief  Remove a file on the SD disk
  * @param  filename: File name
  * @retval TRUE or FALSE
  */
uint8_t SDClass::remove(const char *filepath)
{
   if(f_unlink(filepath) != FR_OK)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/**
  * @brief  Read byte from the file
  * @retval Byte read
  */
int File::read()
{
    uint8_t byteread;
    int8_t data;
    f_read(&Fil, (void *)&data, 1, (UINT *)&byteread);
    return data;
}

/**
  * @brief  Read an amount of data from the file
  * @param  buf: an array to store the read data from the file
  * @param  len: the number of elements to read
  * @retval Number of bytes read
  */
int File::read(void* buf, size_t len)
{
    uint8_t bytesread;

    f_read(&Fil, buf, len, (UINT *)&bytesread);
    return bytesread;

}

/**
  * @brief  Close a file on the SD disk
  * @param  None
  * @retval None
  */
void File::close()
{
    /* Flush the file before close */
    f_sync(&Fil);

    /* Close the file */
    f_close(&Fil);
    if(name)
        free(name);
}


/**
  * @brief  Ensures that any bytes written to the file are physically saved to the SD card
  * @param  None
  * @retval None
  */
void File::flush()
{
    f_sync(&Fil);
}

/**
  * @brief  Read a byte from the file without advancing to the next one
  * @param  None
  * @retval read byte
  */
int File::peek()
{
    int data;
    data = read();
    seek(position() -1);
    return data;
}

/**
  * @brief  Get the current position within the file
  * @param  None
  * @retval position within file
  */
uint32_t File::position()
{
    uint32_t filepos = 0;
    filepos = f_tell(&Fil);
    return filepos;
}

/**
  * @brief  Seek to a new position in the file
  * @param  pos: The position to which to seek
  * @retval TRUE or FALSE
  */
uint8_t File::seek(uint32_t pos)
{
  if(pos > size())
  {
    return FALSE;
  }
  else
  {
    if(f_lseek(&Fil, pos) != FR_OK)
    {
      return FALSE;
    }
    else
    {
      return TRUE;
    }
  }
}

/**
  * @brief  Get the size of the file
  * @param  None
  * @retval file's size
  */
uint32_t File::size()
{
    uint32_t file_size = 0;

    file_size = f_size(&Fil);
    return(file_size);
}

/**
  * @brief  Write data to the file
  * @param  data: Data to write to the file
  * @retval Number of data written (1)
  */
size_t File::write(uint8_t data)
{
    size_t bytewritten;
    f_write(&Fil, (const void *)&data, 1, (UINT *)&bytewritten);
    return bytewritten;
}

/**
  * @brief  Write an array of data to the file
  * @param  buf: an array of characters or bytes to write to the file
  * @param  len: the number of elements in buf
  * @retval Number of data written
  */
size_t File::write(const uint8_t *buf, size_t size)
{
    size_t byteswritten;
    f_write(&Fil, (const void *)buf, size, (UINT *)&byteswritten);
    return byteswritten;
}

/**
  * @brief  Print data to the file
  * @param  data: Data to write to the file
  * @retval Number of data written (1)
  */
size_t File::print(const char* data)
{
    size_t bytewritten;
    f_write(&Fil, (const void *)data, strlen(data), (UINT *)&bytewritten);
    return bytewritten;
}

/**
  * @brief  Print data to the file
  * @param  data: Data to write to the file
  * @retval Number of data written (1)
  */
size_t File::println(const char* data)
{
    size_t bytewritten;
    size_t bytewritten1;
    f_write(&Fil, (const void *)data, strlen(data), (UINT *)&bytewritten);
    f_write(&Fil, "\r\n", 4, (UINT *)&bytewritten1);
    return bytewritten + bytewritten1;
}

/**
  * @brief  Print data to the file
  * @retval Number of data written (1)
  */
size_t File::println()
{
    size_t bytewritten;
    f_write(&Fil, "\r\n", 4, (UINT *)&bytewritten);
    return bytewritten;
}

/**
  * @brief  Check if there are any bytes available for reading from the file
  * @retval Number of bytes available
  */
int File::available()
{
    uint32_t n = size() - position();
    return n > 0x7FFF ? 0x7FFF : n;
}

/**
  * @brief  Check if the file is directory or normal file
  * @retval TRUE if directory else FALSE
  */
uint8_t File::isDirectory()
{
    FILINFO fno;
    f_stat(name, &fno);
    if(fno.fattrib & AM_DIR)
    {
        return TRUE;
    }
    else
    {
       return FALSE;
    }
}

