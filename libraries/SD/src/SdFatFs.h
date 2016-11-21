/*
 * <Description>
 *
 * Copyright (C) 2016, STMicroelectronics - All Rights Reserved
 * Author: YOUR NAME <> for STMicroelectronics.
 *
 * License type: GPLv2
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef SdFatFs_h
#define SdFatFs_h

#include "Sd2Card.h"

/* FatFs includes component */
#include "FatFs/src/ff_gen_drv.h"
#include "FatFs/src/drivers/sd_diskio.h"

// To match Arduino definition
#define   FILE_WRITE  FA_WRITE
#define   FILE_READ   FA_READ

class SdFatFs {
 public:

  uint8_t init(void);

  /** Return the FatFs type: 12, 16, 32 (0: unknown)*/
  uint8_t fatType(void);

  // inline functions that return volume info
  /** \return The volume's cluster size in blocks. */
  uint8_t blocksPerCluster(void) const {return _SDFatFs.csize;}
  /** \return The total number of clusters in the volume. */
  uint32_t clusterCount(void) const {return (_SDFatFs.n_fatent -2);}
 
private:
	FATFS _SDFatFs;  /* File system object for SD disk logical drive */
	char _SDPath[4]; /* SD disk logical drive path */
};
#endif  // sdFatFs_h
