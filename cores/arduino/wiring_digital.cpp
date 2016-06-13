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

/*
 * Arduino-compatible digital I/O implementation.
 */

 /*
  * Arduino srl - www.arduino.org
  * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
  */

#include "wiring.h"
#include "io.h"
#include "Arduino.h"
#include "dac.h"

void pinMode(uint8 pin, WiringPinMode mode)
{
    gpio_pin_mode outputMode;
    boolean pwm = false;

    if (pin >= GPIO_PINS)
    {
        return;
    }

    switch(mode)
    {
    case OUTPUT:
        outputMode = GPIO_OUTPUT_PP;
        break;
    case OUTPUT_OPENDRAIN:
        outputMode = GPIO_OUTPUT_OD;
        break;
    case INPUT:
    case INPUT_PULLDOWN:
        outputMode = GPIO_INPUT_PD;
        break;
    case INPUT_FLOAT:
        outputMode = GPIO_INPUT_FLOATING;
        break;
    case INPUT_PULLUP:
        outputMode = GPIO_INPUT_PU;
        break;
    default:
        ASSERT(0);
        return;
    }

    gpio_set_mode(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit, outputMode);

    if (PIN_MAP[pin].timer_device != NULL)
    {
        /* Enable/disable timer channels if we're switching into or
         * out of PWM. */
        timer_set_mode(PIN_MAP[pin].timer_device, PIN_MAP[pin].timer_channel, pwm ? TIMER_PWM : TIMER_DISABLED);
    }
}


uint32 digitalRead(uint8 pin)
{
    if (pin >= GPIO_PINS)
    {
        return 0;
    }

    return gpio_read_bit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit) ? HIGH : LOW;
}

void digitalWrite(uint8 pin, uint8 val)
{
    if (pin >= GPIO_PINS)
    {
        return;
    }

    gpio_write_bit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit, val);
}

void togglePin(uint8 pin)
{
    if (pin >= GPIO_PINS)
    {
        return;
    }

    gpio_toggle_bit(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit);
}

uint32_t pulseIn( uint8 pin, uint32_t state, uint32_t timeout )
{
    while(digitalRead(pin) == state);
    while(digitalRead(pin) == !state);
    uint32_t start_time = micros();
    while(digitalRead(pin) == state);
    return (micros()-start_time);
}
