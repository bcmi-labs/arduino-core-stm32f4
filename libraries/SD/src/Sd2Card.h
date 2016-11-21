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
#ifndef Sd2Card_h
#define Sd2Card_h

/* otto includes component */
#include "BSP/OTTO/otto_sd.h"

#define   FALSE      ((uint8_t)0x00)
#define   TRUE       ((uint8_t)0x01)

// card types to match Arduino definition
/** Standard capacity V1 SD card */
#define SD_CARD_TYPE_SD1	STD_CAPACITY_SD_CARD_V1_1
/** Standard capacity V2 SD card */
#define SD_CARD_TYPE_SD2	STD_CAPACITY_SD_CARD_V2_0
/** High Capacity SD card */
#define SD_CARD_TYPE_SDHC	HIGH_CAPACITY_SD_CARD

class Sd2Card {
 public:

  uint8_t init(void);
  uint8_t init(uint8_t cspin);

  /** Return the card type: SD V1, SD V2 or SDHC */
  uint8_t type(void) const {return _SdCardInfo.CardType;}

private:
  SD_CardInfo _SdCardInfo;

};
#endif  // sd2Card_h
