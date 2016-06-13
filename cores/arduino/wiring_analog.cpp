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
 *  @brief Arduino-compatible ADC implementation.
 */

 /*
  * Arduino srl - www.arduino.org
  * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
  */

#include "memory.h"
#include "wiring.h"
#include "io.h"

/* Assumes that the ADC has been initialized and that the pin is set
 * to INPUT_ANALOG */
uint16 analogRead(uint8 pin) {
  if ((pin >= 0) && (pin <= 13))
  {
    pin = pin + 54;
  }
	gpio_set_mode(PIN_MAP[pin].gpio_device, PIN_MAP[pin].gpio_bit, GPIO_INPUT_ANALOG);
    const adc_dev *dev = PIN_MAP[pin].adc_device;
    if (dev == NULL) {
        return 0;
    }

    return adc_read(dev, PIN_MAP[pin].adc_channel);
}

/* ADC handler declaration */
ADC_HandleTypeDef    AdcHandle_ADC1;
ADC_HandleTypeDef    AdcHandle_ADC2;
ADC_HandleTypeDef    AdcHandle_ADC3;


void analogReadResolution(int resolution)
{

	/*##-1- Configure the ADC peripheral #######################################*/
  AdcHandle_ADC1.Instance          = HAL_ADC1;
  AdcHandle_ADC2.Instance          = HAL_ADC2;
  AdcHandle_ADC3.Instance          = HAL_ADC3;

  AdcHandle_ADC1.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4;
  AdcHandle_ADC2.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4;
  AdcHandle_ADC3.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4;

  if (resolution <= 6) {
    AdcHandle_ADC1.Init.Resolution            = ADC_RESOLUTION_6B;
    AdcHandle_ADC2.Init.Resolution            = ADC_RESOLUTION_6B;
    AdcHandle_ADC3.Init.Resolution            = ADC_RESOLUTION_6B;
   }

  if ((6 < resolution) && (resolution <=8)) {
    AdcHandle_ADC1.Init.Resolution            = ADC_RESOLUTION_8B;
    AdcHandle_ADC2.Init.Resolution            = ADC_RESOLUTION_8B;
    AdcHandle_ADC3.Init.Resolution            = ADC_RESOLUTION_8B;
   }

  if ((8 < resolution) && (resolution <=10)) {
    AdcHandle_ADC1.Init.Resolution            = ADC_RESOLUTION_10B;
    AdcHandle_ADC2.Init.Resolution            = ADC_RESOLUTION_10B;
    AdcHandle_ADC3.Init.Resolution            = ADC_RESOLUTION_10B;
   }

  if (10 < resolution) {
    AdcHandle_ADC1.Init.Resolution            = ADC_RESOLUTION_12B;
    AdcHandle_ADC2.Init.Resolution            = ADC_RESOLUTION_12B;
    AdcHandle_ADC3.Init.Resolution            = ADC_RESOLUTION_12B;
   }

  HAL_ADC_Init(&AdcHandle_ADC1);
  HAL_ADC_Init(&AdcHandle_ADC2);
  HAL_ADC_Init(&AdcHandle_ADC3);

}
