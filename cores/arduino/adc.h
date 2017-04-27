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
 *  @file adc.h
 *
 *  @brief Analog-to-Digital Conversion (ADC) header.
 */

 /*
  * Arduino srl - www.arduino.org
  * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
  */

#ifndef _ADC_H_
#define _ADC_H_

#include "memory.h"
#include "bitband.h"
#include "rcc.h"
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C"{
#endif

/** ADC device type. */
typedef struct adc_dev {
    ADC_TypeDef *regs; /**< Register map */
    rcc_clk_id clk_id; /**< RCC clock information */
} adc_dev;

extern const adc_dev *ADC1_dev;
extern const adc_dev *ADC2_dev;
extern const adc_dev *ADC3_dev;

void adc_init(const adc_dev *dev);

/**
 * @brief External event selector for regular group conversion.
 * @see adc_set_extsel
 */
typedef enum adc_extsel_event {
    ADC_ADC12_TIM1_CC1  = (0 << 17), // ADC1 and ADC2: Timer 1 CC1 event
    ADC_ADC12_TIM1_CC2  = (1 << 17), // ADC1 and ADC2: Timer 1 CC2 event
    ADC_ADC12_TIM1_CC3  = (2 << 17), // ADC1 and ADC2: Timer 1 CC3 event
    ADC_ADC12_TIM2_CC2  = (3 << 17), // ADC1 and ADC2: Timer 2 CC2 event
    ADC_ADC12_TIM3_TRGO = (4 << 17), // ADC1 and ADC2: Timer 3 TRGO event
    ADC_ADC12_TIM4_CC4  = (5 << 17), // ADC1 and ADC2: Timer 4 CC4 event
    ADC_ADC12_EXTI11    = (6 << 17), // ADC1 and ADC2: EXTI11 event
    ADC_ADC12_TIM8_TRGO = (6 << 17), // ADC1 and ADC2: Timer 8 TRGO event
    ADC_ADC12_SWSTART   = (7 << 17), // ADC1 and ADC2: Software start

    ADC_ADC3_TIM3_CC1   = (0 << 17), // ADC3: Timer 3 CC1 event
    ADC_ADC3_TIM2_CC3   = (1 << 17), // ADC3: Timer 2 CC3 event
    ADC_ADC3_TIM1_CC3   = (2 << 17), // ADC3: Timer 1 CC3 event
    ADC_ADC3_TIM8_CC1   = (3 << 17), // ADC3: Timer 8 CC1 event
    ADC_ADC3_TIM8_TRGO  = (4 << 17), // ADC3: Timer 8 TRGO event
    ADC_ADC3_TIM5_CC1   = (5 << 17), // ADC3: Timer 5 CC1 event
    ADC_ADC3_TIM5_CC3   = (6 << 17), // ADC3: Timer 5 CC3 event
    ADC_ADC3_SWSTART    = (7 << 17), // ADC3: Software start

    ADC_SWSTART         = (7 << 17)  // ADC1, ADC2, ADC3: Software start
} adc_extsel_event;

void adc_set_extsel(const adc_dev *dev, adc_extsel_event event);

void adc_foreach(void (*fn)(const adc_dev*));

/**
 * @brief ADC sample times, in ADC clock cycles
 *
 * These control the amount of time spent sampling the input voltage.
 */
typedef enum {
    ADC_SMPR_1_5,               // 1.5 ADC cycles
    ADC_SMPR_7_5,               // 7.5 ADC cycles
    ADC_SMPR_13_5,              // 13.5 ADC cycles
    ADC_SMPR_28_5,              // 28.5 ADC cycles
    ADC_SMPR_41_5,              // 41.5 ADC cycles
    ADC_SMPR_55_5,              // 55.5 ADC cycles
    ADC_SMPR_71_5,              // 71.5 ADC cycles
    ADC_SMPR_239_5              // 239.5 ADC cycles
} adc_smp_rate;

void adc_set_sample_rate(const adc_dev *dev, adc_smp_rate smp_rate);

void adc_calibrate(const adc_dev *dev);

uint16 adc_read(const adc_dev *dev, uint8 channel);

/**
 * @brief Set the regular channel sequence length.
 *
 * Defines the total number of conversions in the regular channel
 * conversion sequence.
 *
 * @param dev ADC device.
 * @param length Regular channel sequence length, from 1 to 16.
 */
static inline void adc_set_reg_seqlen(const adc_dev *dev, uint8 length)
{
    uint32 tmp = dev->regs->SQR1;
    tmp &= ~ADC_SQR1_L;
    tmp |= (length - 1) << 20;
    dev->regs->SQR1 = tmp;
}

/**
 * @brief Set external trigger conversion mode event for regular channels
 * @param dev    ADC device
 * @param enable If 1, conversion on external events is enabled; if 0,
 *               disabled.
 */
static inline void adc_set_exttrig(const adc_dev *dev, uint8 enable)
{
    *bb_perip(&dev->regs->CR2, ADC_CR2_JEXTEN_Pos) = !!enable;
}

/**
 * @brief Enable an adc peripheral
 * @param dev ADC device to enable
 */
static inline void adc_enable(const adc_dev *dev)
{
    *bb_perip(&dev->regs->CR2, ADC_CR2_ADON_Pos) = 1;
}

/**
 * @brief Disable an ADC peripheral
 * @param dev ADC device to disable
 */
static inline void adc_disable(const adc_dev *dev)
{
    *bb_perip(&dev->regs->CR2, ADC_CR2_ADON_Pos) = 0;
}

/**
 * @brief Disable all ADC peripherals.
 */
static inline void adc_disable_all(void)
{
    adc_foreach(adc_disable);
}

void setupADC();

#ifdef __cplusplus
} // extern "C"
#endif

#endif
