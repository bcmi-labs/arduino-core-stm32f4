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
 *  @file io.h
 *
 *  @brief Arduino-compatible digital pin I/O interface.
 */

 /*
 * Arduino srl - www.arduino.org
 * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
 */


#ifndef _IO_H_
#define _IO_H_

#include "gpio.h"
#include "adc.h"

#include "wiring_time.h"
#include "wiring_constants.h"

/**
 * Configure behavior of a GPIO pin.
 *
 * @param pin Number of pin to configure.
 * @param mode Mode corresponding to desired pin behavior.
 * @see PinMode
 */
void pinMode(uint8 pin, uint8 mode);

/**
 * Writes a (digital) value to a pin.  The pin must have its
 * mode set to OUTPUT or OUTPUT_OPEN_DRAIN.
 *
 * @param pin Pin to write to.
 * @param value Either LOW (write a 0) or HIGH (write a 1).
 * @see pinMode()
 */
void digitalWrite(uint8 pin, uint8 value);

/**
 * Read a digital value from a pin.  The pin must have its mode set to
 * one of INPUT, INPUT_PULLUP, and INPUT_PULLDOWN.
 *
 * @param pin Pin to read from.
 * @return LOW or HIGH.
 * @see pinMode()
 */
uint32 digitalRead(uint8 pin);

/**
 * Read an analog value from pin.  This function blocks during ADC
 * conversion, and has 12 bits of resolution.  The pin must have its
 * mode set to INPUT_ANALOG.
 *
 * @param pin Pin to read from.
 * @return Converted voltage, in the range 0--4095, (i.e. a 12-bit ADC
 *         conversion).
 * @see pinMode()
 */
uint16 analogRead(uint8 pin);

/**
 * Toggles the digital value at the given pin.
 *
 * The pin must have its mode set to OUTPUT.
 *
 * @param pin the pin to toggle.  If the pin is HIGH, set it LOW.  If
 * it is LOW, set it HIGH.
 *
 * @see pinMode()
 */
void togglePin(uint8 pin);

/**
 * Shift out a byte of data, one bit at a time.
 *
 * This function starts at either the most significant or least
 * significant bit in a byte value, and shifts out each byte in order
 * onto a data pin.  After each bit is written to the data pin, a
 * separate clock pin is pulsed to indicate that the new bit is
 * available.
 *
 * @param dataPin  Pin to shift data out on
 * @param clockPin Pin to pulse after each bit is shifted out
 * @param bitOrder Either MSBFIRST (big-endian) or LSBFIRST (little-endian).
 * @param value    Value to shift out
 */
void shiftOut(uint8 dataPin, uint8 clockPin, uint8 bitOrder, uint8 value);

/**
* This function is used to set the DAC operation
* @param DACChanne  Pin used by DAC
*/

void setDac(uint8 pin);

void analogReadResolution (int resolution);

uint32_t pulseIn( uint8 pin, uint32_t state, uint32_t timeout = 1000000);

#define microsecondsToClockCycles(a) ( (a) * (SystemCoreClock / 1000000L) )

#endif
