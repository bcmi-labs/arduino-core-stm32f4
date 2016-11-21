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

#include <Arduino.h>
#include "Sd2Card.h"

uint8_t Sd2Card::init(void) {
	if (BSP_SD_Init() == MSD_OK) {
		BSP_SD_GetCardInfo(&_SdCardInfo);
		return TRUE;
	} else {
		return FALSE;
	}
}

uint8_t Sd2Card::init(uint8_t cspin) {
	if (BSP_SD_CSInit() == MSD_OK) {
		BSP_SD_GetCardInfo(&_SdCardInfo);
		return TRUE;
	} else {
		return FALSE;
	}
}


