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
 * @file rcc.h
 * @brief reset and clock control definitions and prototypes
 */

 /*
 * Arduino srl - www.arduino.org
 * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
 */

#include "types.h"
#include "stm32f4xx_hal.h"

#ifndef _RCC_H_
#define _RCC_H_

#ifdef __cplusplus
extern "C"{
#endif

/*
 * Register bit definitions
 */

/*
RCC clock configuration register (RCC_CFGR)
Address offset: 0x08
Reset value: 0x0000 0000
Access: 0 ≤ wait state ≤ 2, word, half-word and byte access
1 or 2 wait states inserted only if the access occurs during a clock source switch.
*/

#define  RCC_CFGR_MCO1Source_HSI        ((uint32_t)0x00000000)
#define  RCC_CFGR_MCO1Source_LSE        ((uint32_t)0x00200000)
#define  RCC_CFGR_MCO1Source_HSE        ((uint32_t)0x00400000)
#define  RCC_CFGR_MCO1Source_PLLCLK     ((uint32_t)0x00600000)
#define  RCC_CFGR_MCO1Div_1             ((uint32_t)0x00000000)
#define  RCC_CFGR_MCO1Div_2             ((uint32_t)0x04000000)
#define  RCC_CFGR_MCO1Div_3             ((uint32_t)0x05000000)
#define  RCC_CFGR_MCO1Div_4             ((uint32_t)0x06000000)
#define  RCC_CFGR_MCO1Div_5             ((uint32_t)0x07000000)
#define  RCC_CFGR_MCO1_RESET_MASK       ((uint32_t)0xF89FFFFF)

/*
 * Convenience routines
 */

/**
 * SYSCLK sources
 * @see rcc_clk_init()
 */
typedef enum rcc_sysclk_src {
    RCC_CLKSRC_HSI = 0x0,
    RCC_CLKSRC_HSE = 0x1,
    RCC_CLKSRC_PLL = 0x2,
} rcc_sysclk_src;

/**
 * PLL entry clock source
 * @see rcc_clk_init()
 */
typedef enum rcc_pllsrc {
    RCC_PLLSRC_HSE = (0x1 << 16),
    RCC_PLLSRC_HSI_DIV_2 = (0x0 << 16)
} rcc_pllsrc;

/**
 * PLL multipliers
 * @see rcc_clk_init()
 */
typedef enum rcc_pll_multiplier {
    RCC_PLLMUL_2  = (0x0 << 18),
    RCC_PLLMUL_3  = (0x1 << 18),
    RCC_PLLMUL_4  = (0x2 << 18),
    RCC_PLLMUL_5  = (0x3 << 18),
    RCC_PLLMUL_6  = (0x4 << 18),
    RCC_PLLMUL_7  = (0x5 << 18),
    RCC_PLLMUL_8  = (0x6 << 18),
    RCC_PLLMUL_9  = (0x7 << 18),
    RCC_PLLMUL_10 = (0x8 << 18),
    RCC_PLLMUL_11 = (0x9 << 18),
    RCC_PLLMUL_12 = (0xA << 18),
    RCC_PLLMUL_13 = (0xB << 18),
    RCC_PLLMUL_14 = (0xC << 18),
    RCC_PLLMUL_15 = (0xD << 18),
    RCC_PLLMUL_16 = (0xE << 18),
} rcc_pll_multiplier;

/**
 * @brief Identifies bus and clock line for a peripheral.
 *
 * Also generally useful as a unique identifier for that peripheral
 * (or its corresponding device struct).
 */
typedef enum rcc_clk_id {

  // AHB3

  	  RCC_FMC,
  	  RCC_QSPI,

   // AHB2
      RCC_DCMI,

      RCC_CRYP,
      RCC_HASH,
      RCC_RNG,
      RCC_OTGFS,
      RCC_USBFS,    //for compatibility

  // AHB1
      RCC_GPIOA,
      RCC_GPIOB,
      RCC_GPIOC,
      RCC_GPIOD,
      RCC_GPIOE,
      RCC_GPIOF,
      RCC_GPIOG,
      RCC_GPIOH,
      RCC_GPIOI,
      RCC_GPIOJ,
      RCC_GPIOK,

      RCC_CRC,

      RCC_FLITFLP,
      RCC_SRAM1LP,
      RCC_SRAM2LP,

      RCC_BKP,
  	  RCC_SRAM3LP,
      RCC_CCDATARAM,
      RCC_DMA1,
      RCC_DMA2,
      RCC_DMA2D,

      RCC_ETH,
      RCC_ETHTX,
      RCC_ETHRX,
      RCC_ETHPTP,
      RCC_OTGHS,
      RCC_OTGHSULPI,

  // APB2

      RCC_TIMER1,
      RCC_TIMER8,

      RCC_USART1,
      RCC_USART6,

      RCC_ADC1,
      RCC_ADC2,
      RCC_ADC3,
      RCC_SDIO,
      RCC_SPI1,
      RCC_SPI4,
      RCC_SYSCFG,

      RCC_TIMER9,
      RCC_TIMER10,
      RCC_TIMER11,

      RCC_SPI5,
      RCC_SPI6,
      RCC_SAI1,

      RCC_LTDC,
      RCC_DSI,


  // APB1

      RCC_TIMER2,
      RCC_TIMER3,
      RCC_TIMER4,
      RCC_TIMER5,
      RCC_TIMER6,
      RCC_TIMER7,
      RCC_TIMER12,
      RCC_TIMER13,
      RCC_TIMER14,

      RCC_WWDG,

      RCC_SPI2,
      RCC_SPI3,

      RCC_USART2,
      RCC_USART3,
  	  RCC_UART4,
      RCC_UART5,
      RCC_I2C1,
      RCC_I2C2,
   	  RCC_I2C3,

   	  RCC_CAN1,
   	  RCC_CAN2,

      RCC_PWR,
      RCC_DAC,
  	  RCC_UART7,
      RCC_UART8
} rcc_clk_id;

void rcc_clk_init(rcc_sysclk_src sysclk_src,
                  rcc_pllsrc pll_src,
                  rcc_pll_multiplier pll_mul);
void rcc_clk_disable(rcc_clk_id device);
void rcc_clk_enable(rcc_clk_id device);
void rcc_reset_dev(rcc_clk_id device);

void SetupClock();

typedef enum rcc_clk_domain {
    RCC_APB1,
    RCC_APB2,
    RCC_AHB1,
    RCC_AHB2,
    RCC_AHB3
} rcc_clk_domain;

rcc_clk_domain rcc_dev_clk(rcc_clk_id device);

uint32 rcc_dev_clk_speed(rcc_clk_id id);
uint32 rcc_dev_timer_clk_speed(rcc_clk_id id);

/**
 * Prescaler identifiers
 * @see rcc_set_prescaler()
 */
typedef enum rcc_prescaler {
    RCC_PRESCALER_AHB,
    RCC_PRESCALER_APB1,
    RCC_PRESCALER_APB2,
    RCC_PRESCALER_USB,
    RCC_PRESCALER_ADC
} rcc_prescaler;

/**
 * ADC prescaler dividers
 * @see rcc_set_prescaler()
 */
typedef enum rcc_adc_divider {
    RCC_ADCPRE_PCLK_DIV_2 = 0x0 << 14,
    RCC_ADCPRE_PCLK_DIV_4 = 0x1 << 14,
    RCC_ADCPRE_PCLK_DIV_6 = 0x2 << 14,
    RCC_ADCPRE_PCLK_DIV_8 = 0x3 << 14,
} rcc_adc_divider;

/**
 * APB1 prescaler dividers
 * @see rcc_set_prescaler()
 */
typedef enum rcc_apb1_divider {
    RCC_APB1_HCLK_DIV_1 = 0x0 << 8,
    RCC_APB1_HCLK_DIV_2 = 0x4 << 8,
    RCC_APB1_HCLK_DIV_4 = 0x5 << 8,
    RCC_APB1_HCLK_DIV_8 = 0x6 << 8,
    RCC_APB1_HCLK_DIV_16 = 0x7 << 8,
} rcc_apb1_divider;

/**
 * APB2 prescaler dividers
 * @see rcc_set_prescaler()
 */
typedef enum rcc_apb2_divider {
    RCC_APB2_HCLK_DIV_1 = 0x0 << 11,
    RCC_APB2_HCLK_DIV_2 = 0x4 << 11,
    RCC_APB2_HCLK_DIV_4 = 0x5 << 11,
    RCC_APB2_HCLK_DIV_8 = 0x6 << 11,
    RCC_APB2_HCLK_DIV_16 = 0x7 << 11,
} rcc_apb2_divider;

/**
 * AHB prescaler dividers
 * @see rcc_set_prescaler()
 */
typedef enum rcc_ahb_divider {
    RCC_AHB_SYSCLK_DIV_1 = 0x0 << 4,
    RCC_AHB_SYSCLK_DIV_2 = 0x8 << 4,
    RCC_AHB_SYSCLK_DIV_4 = 0x9 << 4,
    RCC_AHB_SYSCLK_DIV_8 = 0xA << 4,
    RCC_AHB_SYSCLK_DIV_16 = 0xB << 4,
    RCC_AHB_SYSCLK_DIV_32 = 0xC << 4,
    RCC_AHB_SYSCLK_DIV_64 = 0xD << 4,
    RCC_AHB_SYSCLK_DIV_128 = 0xD << 4,
    RCC_AHB_SYSCLK_DIV_256 = 0xE << 4,
    RCC_AHB_SYSCLK_DIV_512 = 0xF << 4,
} rcc_ahb_divider;

void rcc_set_prescaler(rcc_prescaler prescaler, uint32 divider);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
