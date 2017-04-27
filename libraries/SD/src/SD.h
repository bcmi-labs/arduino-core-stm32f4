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

#include "Sd2Card.h"
#include "SdFatFs.h"

// flags for ls()
/** ls() flag to print modify date */
uint8_t const LS_DATE = 1;
/** ls() flag to print file size */
uint8_t const LS_SIZE = 2;
/** ls() flag for recursive list of subdirectories */
uint8_t const LS_R = 4;

class File {
public:
  File(void);
  File(const char* name);
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buf, size_t size);
  virtual size_t write(const char *buf, size_t size);

  virtual int read();
  virtual int peek();
  virtual int available();
  virtual void flush();
  int read(void* buf, size_t len);
  uint8_t seek(uint32_t pos);
  uint32_t position();
  uint32_t size();
  void close();
  operator bool();

  char* name(void);
  char* fullname(void) {return _name;};
  uint8_t isDirectory();
  File openNextFile(uint8_t mode = FILE_READ);
  void rewindDirectory(void);

  virtual size_t print(const char* data);
  virtual size_t println();
  virtual size_t println(const char* data);
  virtual size_t println(String& data);

  // Print to Serial line
  void ls(uint8_t flags, uint8_t indent = 0);
  static void printFatDate(uint16_t fatDate);
  static void printFatTime(uint16_t fatTime);
  static void printTwoDigits(uint8_t v);


  char *_name = NULL; //file or dir name
  FIL _fil = {
#if !_FS_TINY
  { {0} }, //buf
#endif
  NULL, //	*fs
  0, // id
  0, // flag
  0, //	err
  0, //	fptr
  0, // fsize
  0, //	sclust
  0, //	clust
  0, //	dsect
#if !_FS_READONLY
  0, //	dir_sect
  NULL, //*dir_ptr
#endif
#if _USE_FASTSEEK
  NULL, // *cltbl
#endif
#if _FS_LOCK
  0, //	lockid
#endif
  }; // init all fields

  DIR _dir = {
#if !_FS_TINY
  { {0} }, //buf
#endif
  NULL, //	*fs
  0, // id
  0, // index
  0, // sclust
  0, // clust
  0, // sect
  NULL, // *dir
  NULL, // *fn
#if _FS_LOCK
  0, //	lockid
#endif
#if _USE_LFN
  NULL, // lfn
  0, //	lfn_idx
#endif
#if _USE_FIND
  NULL, // pat
#endif
  }; // init all fields

};

class SDClass {

public:

  /* Initialize the SD peripheral */
  uint8_t begin();
  uint8_t begin(uint8_t cspin);
  static File open(const char *filepath, uint8_t mode);
  static File open(const char *filepath);
  static uint8_t exists(const char *filepath);
  static uint8_t mkdir(const char *filepath);
  static uint8_t remove(const char *filepath);
  static uint8_t rmdir(const char *filepath);

  File openRoot(void);

  friend class File;

private:
  Sd2Card _card;
  SdFatFs _fatFs;

};

extern SDClass SD;

#endif
