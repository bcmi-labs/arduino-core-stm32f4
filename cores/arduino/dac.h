/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Bryan Newbold.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file dac.h
 * @brief Digital to analog converter support.
 */

/* See notes/dac.txt for more info */

#ifndef _DAC_H_
#define _DAC_H_

#include "rcc.h"

#ifdef __cplusplus
extern "C"{
#endif

/*
 * Devices
 */

/** DAC device type. */
typedef struct dac_dev {
    DAC_TypeDef *regs; /**< Register map */
} dac_dev;

extern const dac_dev *DAC_dev;

/*
 * Convenience functions
 */

/* We take the dev argument in these convenience functions for
 * future-proofing */

#define DAC_CH1                         0x1
#define DAC_CH2                         0x2
void dac_init(const dac_dev *dev, uint32 flags);

void dac_write_channel(const dac_dev *dev, uint8 channel, uint16 val);
void dac_enable_channel(const dac_dev *dev, uint8 channel);
void dac_disable_channel(const dac_dev *dev, uint8 channel);
void dac_enable_buffer(const dac_dev *dev, uint32 flags, int status);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
