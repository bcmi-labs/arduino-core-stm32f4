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
 *  @brief Arduino-style PWM implementation.
 */

 /*
 * Arduino srl - www.arduino.org
 * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
 */

#include "types.h"
#include "timer.h"

#include "boards.h"
#include "pwm.h"

#include "dac.h"
#include "Arduino.h"

// alfran TO DO: change this
extern bool ADC0_Status = false;
extern bool ADC1_Status = false;
extern uint16 MaxRes_val= 255;

void analogWrite(uint8 pin, uint16 passed_val)
{
	if ((pin == DAC0) | (pin == DAC1))
	{
        uint16 duty_cycle = passed_val;
		if ((!ADC0_Status) && (pin == DAC0)) setDac(pin);
		if ((!ADC1_Status) && (pin == DAC1)) setDac(pin);



		if (pin == DAC0) dac_write_channel(DAC,1,duty_cycle);

		if (pin == DAC1) dac_write_channel(DAC,2,duty_cycle);
	}
	else
	{
    	uint16 duty_cycle = map(passed_val, 0, MaxRes_val, 0, 65535);
        timer_dev *dev = PIN_MAP[pin].timer_device;
    	if (pin >= GPIO_PINS || dev == NULL || dev->type == TIMER_BASIC)
    	{
        	return;
    	}

		timer_set_compare(dev, PIN_MAP[pin].timer_channel, duty_cycle);
		timer_cc_enable(dev, PIN_MAP[pin].timer_channel);
		gpio_set_mode(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit, GPIO_AF_OUTPUT_PP);
	}
}

void setDac (uint8 pin)
{
    // enabling DAC
            if (pin == DAC0)
            {
                if (ADC1_Status)
                {
                    // Enablin all channel
                    ADC0_Status = true;
                    dac_init(DAC, DAC_CH1 | DAC_CH2);
                }
                else
                {
                    // Enabling DAC0 (port A4)
                    ADC0_Status = true;
                    dac_init(DAC, DAC_CH1);
                }
            }
            if (pin == DAC1)
            {
                if (ADC0_Status)
                {
                    // Enabling all channel
                    ADC1_Status = true;
                    dac_init(DAC, DAC_CH1 | DAC_CH2);
                }
                else
                {
                    // Enablink DAC1 (port A5)
                    ADC1_Status = true;
                    dac_init(DAC, DAC_CH2);
                }
            }
}

void analogWriteResolution(int resolution)
{

    MaxRes_val=1;
    for (int i = 1 ; i <= resolution ; i++)
    {
        MaxRes_val=(2*MaxRes_val);
    }
    MaxRes_val = MaxRes_val - 1;
}
