/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 * @file systick.h
 *
 * @brief Various system timer definitions
 */

 /*
  * Arduino srl - www.arduino.org
  * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
  */

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f4xx.h"
#include "types.h"
#include "util.h"

#ifdef __cplusplus
extern "C"{
#endif

/** System elapsed time, in milliseconds */
extern volatile uint32 systick_uptime_millis;

/**
 * @brief Returns the system uptime, in milliseconds.
 */
static inline uint32 systick_uptime(void) {
    return systick_uptime_millis;
}


void systick_init(uint32 reload_val);
void systick_disable();
void systick_enable();

/**
 * @brief Returns the current value of the SysTick counter.
 */
static inline uint32 systick_get_count(void) {
    return SysTick->VAL;
}

/**
 * @brief Check for underflow.
 *
 * This function returns 1 if the SysTick timer has counted to 0 since
 * the last time it was called.  However, any reads of any part of the
 * SysTick Control and Status Register SysTick->CTRL will
 * interfere with this functionality.  See the ARM Cortex M3 Technical
 * Reference Manual for more details (e.g. Table 8-3 in revision r1p1).
 */
static inline uint32 systick_check_underflow(void) {
    return SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
