/*

 SD - a slightly more friendly wrapper for sdfatlib

 This library aims to expose a subset of SD card functionality
 in the form of a higher level "wrapper" object.

 License: GNU General Public License V3
          (Because sdfatlib is licensed with this.)

 (C) Copyright 2010 SparkFun Electronics

 */

#ifndef __SD_H__
#define __SD_H__

#include <Arduino.h>
/* DISCOVERY includes component */
//#include "libmaple/BSP/stm32469i_discovery_sd.h"
#include "BSP/stm32469i_discovery_sd.h"

/* FatFs includes component */
// #include "libmaple/FatFs/src/ff_gen_drv.h"
// #include "libmaple/FatFs/src/drivers/sd_diskio.h"
#include "FatFs/src/ff_gen_drv.h"
#include "FatFs/src/drivers/sd_diskio.h"

#define   FALSE      ((uint8_t)0x00)
#define   TRUE       ((uint8_t)0x01)

#define   FILE_WRITE  FA_WRITE
#define   FILE_READ   FA_READ

class File {
public:
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buf, size_t size);
  virtual size_t print(const char* data);
  virtual size_t println();
  virtual size_t println(const char* data);
  virtual int read();
  int read(void* buf, size_t len);
  virtual int peek();
  virtual int available();
  virtual void flush();
  uint8_t seek(uint32_t pos);
  uint32_t position();
  uint32_t size();
  void close();
  uint8_t isDirectory();

FIL Fil;
char *name;
};

class SDClass {
public:

  /* Initialize the SD peripheral */
  static uint8_t begin();
  static uint8_t begin(uint8_t cspin);
  static uint8_t exists(const char *filepath);
  static uint8_t mkdir(const char *filepath);
  static uint8_t rmdir(const char *filepath);
  static File open(const char *filepath);
  static File open(const char *filepath, uint8_t mode);
  static uint8_t remove(const char *filepath);

  friend class File;
};

extern SDClass SD;

#endif
