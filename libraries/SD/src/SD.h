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
/* otto includes component */
#include "BSP/OTTO/otto_sd.h"

/* FatFs includes component */
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
  virtual int read();
  virtual int peek();
  virtual int available();
  virtual void flush();
  int read(void* buf, size_t len);
  uint8_t seek(uint32_t pos);
  uint32_t position();
  uint32_t size();
  void close();
  // alfran ----- begin -----
  operator bool();
  // alfran ----- end -----
  char *name;
  uint8_t isDirectory();


  virtual size_t print(const char* data);
  virtual size_t println();
  virtual size_t println(const char* data);

  FIL Fil;

};

class SDClass {

public:

  /* Initialize the SD peripheral */
  static uint8_t begin();
  static uint8_t begin(uint8_t cspin);
  static File open(const char *filepath, uint8_t mode);
  static File open(const char *filepath);
  static uint8_t exists(const char *filepath);
  static uint8_t mkdir(const char *filepath);
  static uint8_t remove(const char *filepath);
  static uint8_t rmdir(const char *filepath);

  friend class File;

};

extern SDClass SD;

#endif
