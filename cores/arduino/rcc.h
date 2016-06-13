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
#include "HAL/inc/stm32f4xx_hal.h"

#ifndef _RCC_H_
#define _RCC_H_

#ifdef __cplusplus
extern "C"{
#endif

/** RCC register map type */
typedef struct
{
  __io uint32 CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
  __io uint32 PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
  __io uint32 CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
  __io uint32 CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
  __io uint32 AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
  __io uint32 AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
  __io uint32 AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
  uint32      RESERVED0;     /*!< Reserved, 0x1C                                                                    */
  __io uint32 APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
  __io uint32 APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
  uint32      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
  __io uint32 AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
  __io uint32 AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
  __io uint32 AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
  uint32      RESERVED2;     /*!< Reserved, 0x3C                                                                    */
  __io uint32 APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
  __io uint32 APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
  uint32      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
  __io uint32 AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  __io uint32 AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  __io uint32 AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  uint32      RESERVED4;     /*!< Reserved, 0x5C                                                                    */
  __io uint32 APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  __io uint32 APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  uint32      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
  __io uint32 BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
  __io uint32 CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
  uint32      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
  __io uint32 SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
  __io uint32 PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */

  __io uint32 PLLSAICFGR;    /*!< RCC PLLSAI clock output configuration,                       Address offset: 0x88 */
  __io uint32 DCKCFGR;       /*!< RCC PLLSAI PLLI2S clock and prescale configuration           Address offset: 0x8C */

} rcc_reg_map;

/** RCC register map base pointer */
#define RCC_BASE              ((rcc_reg_map*)0x40023800)
/*
 * Register bit definitions
 */

/*
PWR power control register (PWR_CR)
Address offset: 0x00
Reset value: 0x0000 C000 (reset by wakeup from Standby mode)
*/

#define PWR_CR_ODSWEN_BIT               17
#define PWR_CR_ODEN_BIT                 16
#define PWR_CR_ADCDC1_BIT               13
#define PWR_CR_MRUDS_BIT                11
#define PWR_CR_LPUDS_BIT                10
#define PWR_CR_FPDS_BIT                 9
#define PWR_CR_DBP_BIT                  8
#define PWR_CR_PVDE_BIT                 4
#define PWR_CR_CSBF_BIT                 3
#define PWR_CR_CWUF_BIT                 2
#define PWR_CR_PDDS_BIT                 1
#define PWR_CR_LPDS_BIT                 0

#define PWR_CR_UDEN                     (0b00 << 18)
#define PWR_CR_ODSWEN                   BIT(PWR_CR_ODSWEN_BIT)
#define PWR_CR_ODEN                     BIT(PWR_CR_ODEN_BIT)
#define PWR_CR_VOS                      (0b11 << 14)
#define PWR_CR_ADCDC1                   BIT(PWR_CR_ADCDC1_BIT)
#define PWR_CR_MRUDS                    BIT(PWR_CR_MRUDS_BIT)
#define PWR_CR_LPUDS                    BIT(PWR_CR_LPUDS_BIT)
#define PWR_CR_FPDS                     BIT(PWR_CR_FPDS_BIT)
#define PWR_CR_DBP                      BIT(PWR_CR_DBP_BIT)
#define PWR_CR_PLS                      (0b000 << 5)
#define PWR_CR_PVDE                     BIT(PWR_CR_PVDE_BIT)
#define PWR_CR_CSBF                     BIT(PWR_CR_CSBF_BIT)
#define PWR_CR_CWUF                     BIT(PWR_CR_CWUF_BIT)
#define PWR_CR_PDDS                     BIT(PWR_CR_PDDS_BIT)
#define PWR_CR_LPDS                     BIT(PWR_CR_LPDS_BIT)

/*
PWR power control/status register (PWR_CSR)
Address offset: 0x04
Reset value: 0x0000 0000 (not reset by wakeup from Standby mode)
Additional APB cycles are needed to read this register versus a standard APB read.
*/

#define PWR_CSR_ODSWRDY_BIT             17
#define PWR_CSR_ODRDY_BIT               16
#define PWR_CSR_VOSRDY_BIT              14
#define PWR_CSR_BRE_BIT                 9
#define PWR_CSR_EWUP_BIT                8
#define PWR_CSR_BRR_BIT                 3
#define PWR_CSR_PVDO_BIT                2
#define PWR_CSR_SBF_BIT                 1
#define PWR_CSR_WUPF_BIT                0

#define PWR_CSR_UDRDY                   (0b00 << 18)
#define PWR_CSR_ODSWRDY                 BIT(PWR_CSR_ODSWRDY_BIT)
#define PWR_CSR_ODRDY                   BIT(PWR_CSR_ODRDY_BIT)
#define PWR_CSR_VOSRDY                  BIT(PWR_CSR_VOSRDY_BIT)
#define PWR_CSR_BRE                     BIT(PWR_CSR_BRE_BIT)
#define PWR_CSR_EWUP                    BIT(PWR_CSR_EWUP_BIT)
#define PWR_CSR_BRR                     BIT(PWR_CSR_BRR_BIT)
#define PWR_CSR_PVDO                    BIT(PWR_CSR_PVDO_BIT)
#define PWR_CSR_SBF                     BIT(PWR_CSR_SBF_BIT)
#define PWR_CSR_WUPF                    BIT(PWR_CSR_WUPF_BIT)

/*
RCC clock control register (RCC_CR)
Address offset: 0x00
Reset value: 0x0000 XX83 where X is undefined.
Access: no wait state, word, half-word and byte access
*/

#define RCC_CR_PLLSAIRDY_BIT            29
#define RCC_CR_PLLSAION_BIT             28
#define RCC_CR_PLLI2SRDY_BIT            27
#define RCC_CR_PLLI2SON_BIT             26
#define RCC_CR_PLLRDY_BIT               25
#define RCC_CR_PLLON_BIT                24
#define RCC_CR_CSSON_BIT                19
#define RCC_CR_HSEBYP_BIT               18
#define RCC_CR_HSERDY_BIT               17
#define RCC_CR_HSEON_BIT                16
#define RCC_CR_HSIRDY_BIT               1
#define RCC_CR_HSION_BIT                0

#define RCC_CR_PLLSAIRDY                BIT(RCC_CR_PLLSAIRDY_BIT)
#define RCC_CR_PLLSAION                 BIT(RCC_CR_PLLSAION_BIT)
#define RCC_CR_PLLI2SRDY                BIT(RCC_CR_PLLI2SRDY_BIT)
#define RCC_CR_PLLI2SON                 BIT(RCC_CR_PLLI2SON_BIT)
#define RCC_CR_PLLRDY                   BIT(RCC_CR_PLLRDY_BIT)
#define RCC_CR_PLLON                    BIT(RCC_CR_PLLON_BIT)
#define RCC_CR_CSSON                    BIT(RCC_CR_CSSON_BIT)
#define RCC_CR_HSEBYP                   BIT(RCC_CR_HSEBYP_BIT)
#define RCC_CR_HSERDY                   BIT(RCC_CR_HSERDY_BIT)
#define RCC_CR_HSEON                    BIT(RCC_CR_HSEON_BIT)
#define RCC_CR_HSICAL                   (0xFF << 8)
#define RCC_CR_HSITRIM                  (0x1F << 3)
#define RCC_CR_HSIRDY                   BIT(RCC_CR_HSIRDY_BIT)
#define RCC_CR_HSION                    BIT(RCC_CR_HSION_BIT)

/*
RCC PLL configuration register (RCC_PLLCFGR)
Address offset: 0x04
Reset value: 0x2400 3010
Access: no wait state, word, half-word and byte access.
This register is used to configure the PLL clock outputs according to the formulas:
• f(VCO clock) = f(PLL clock input) × (PLLN / PLLM)
• f(PLL general clock output) = f(VCO clock) / PLLP
• f(USB OTG FS, SDMMC) = f(VCO clock) / PLLQ
• f(PLL DSI clock output) = f(VCO clock) / PLLR
*/

/*
#define RCC_PLLCFGR_PLLSCR_BIT          22

#define RCC_PLLCFGR_PLLR                (0x << 28) // to be configured according the paragraph 6.3.2 of Reference manual RM0386
#define RCC_PLLCFGR_PLLQ                (0x << 24) // to be configured according the paragraph 6.3.2 of Reference manual RM0386
#define RCC_PLLCFGR_PLLP                (0x << 16) // to be configured according the paragraph 6.3.2 of Reference manual RM0386
#define RCC_PLLCFGR_PLLN                (0x << 6)  // to be configured according the paragraph 6.3.2 of Reference manual RM0386
#define RCC_PLLCFGR_PLLM                (0x << 0)  // to be configured according the paragraph 6.3.2 of Reference manual RM0386
*/

/*
RCC clock configuration register (RCC_CFGR)
Address offset: 0x08
Reset value: 0x0000 0000
Access: 0 ≤ wait state ≤ 2, word, half-word and byte access
1 or 2 wait states inserted only if the access occurs during a clock source switch.
*/

#define RCC_CFGR_USBPRE_BIT             22
#define RCC_CFGR_PLLXTPRE_BIT           17
#define RCC_CFGR_PLLSRC_BIT             16

#define RCC_CFGR_MCO                    (0x3 << 24)
#define RCC_CFGR_USBPRE                 BIT(RCC_CFGR_USBPRE_BIT)
#define RCC_CFGR_PLLMUL                 (0xF << 18)
#define RCC_CFGR_PLLXTPRE               BIT(RCC_CFGR_PLLXTPRE_BIT)
#define RCC_CFGR_PLLSRC                 BIT(RCC_CFGR_PLLSRC_BIT)
#define RCC_CFGR_ADCPRE                 (0x3 << 14)
#define RCC_CFGR_PPRE2                  (0x7 << 11)
#define RCC_CFGR_PPRE1                  (0x7 << 8)
#define RCC_CFGR_HPRE                   (0xF << 4)
#define RCC_CFGR_SWS                    (0x3 << 2)
#define RCC_CFGR_SWS_PLL                (0x2 << 2)
#define RCC_CFGR_SWS_HSE                (0x1 << 2)
#define RCC_CFGR_SW                     0x3
#define RCC_CFGR_SW_PLL                 0x2
#define RCC_CFGR_SW_HSE                 0x1
#define RCC_CFGR_MCO1                   (0x2 << 22)

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
RCC clock interrupt register (RCC_CIR)
Address offset: 0x0C
Reset value: 0x0000 0000
Access: no wait state, word, half-word and byte access
*/

#define RCC_CIR_CSSC_BIT                23
#define RCC_CIR_PLLSAIRDYC_BIT          22
#define RCC_CIR_PLLI2S_RDYC_BIT         21
#define RCC_CIR_PLLRDYC_BIT             20
#define RCC_CIR_HSERDYC_BIT             19
#define RCC_CIR_HSIRDYC_BIT             18
#define RCC_CIR_LSERDYC_BIT             17
#define RCC_CIR_LSIRDYC_BIT             16
#define RCC_CIR_PLLRDYIE_BIT            12
#define RCC_CIR_PLLSAIRDYIE_BIT         14
#define RCC_CIR_PLLI2SRDYIE_BIT         13
#define RCC_CIR_HSERDYIE_BIT            11
#define RCC_CIR_HSIRDYIE_BIT            10
#define RCC_CIR_LSERDYIE_BIT            9
#define RCC_CIR_LSIRDYIE_BIT            8
#define RCC_CIR_CSSF_BIT                7
#define RCC_CIR_PLLSAIRDYF_BIT          6
#define RCC_CIR_PLLI2SRDYF_BIT          5
#define RCC_CIR_PLLRDYF_BIT             4
#define RCC_CIR_HSERDYF_BIT             3
#define RCC_CIR_HSIRDYF_BIT             2
#define RCC_CIR_LSERDYF_BIT             1
#define RCC_CIR_LSIRDYF_BIT             0

#define RCC_CIR_CSSC                    BIT(RCC_CIR_CSSC_BIT)
#define RCC_CIR_PLLSAIRDYC              BIT(RCC_CIR_PLLSAIRDYC_BIT)
#define RCC_CIR_PLLI2S_RDYC             BIT(RCC_CIR_PLLI2S_RDYC_BIT)
#define RCC_CIR_PLLRDYC                 BIT(RCC_CIR_PLLRDYC_BIT)
#define RCC_CIR_HSERDYC                 BIT(RCC_CIR_HSERDYC_BIT)
#define RCC_CIR_HSIRDYC                 BIT(RCC_CIR_HSIRDYC_BIT)
#define RCC_CIR_LSERDYC                 BIT(RCC_CIR_LSERDYC_BIT)
#define RCC_CIR_LSIRDYC                 BIT(RCC_CIR_LSIRDYC_BIT)
#define RCC_CIR_PLLRDYIE                BIT(RCC_CIR_PLLRDYIE_BIT)
#define RCC_CIR_PLLSAIRDYIE             BIT(RCC_CIR_PLLSAIRDYIE_BIT)
#define RCC_CIR_PLLI2SRDYIE             BIT(RCC_CIR_PLLSAIRDYIE_BIT)
#define RCC_CIR_HSERDYIE                BIT(RCC_CIR_HSERDYIE_BIT)
#define RCC_CIR_HSIRDYIE                BIT(RCC_CIR_HSIRDYIE_BIT)
#define RCC_CIR_LSERDYIE                BIT(RCC_CIR_LSERDYIE_BIT)
#define RCC_CIR_LSIRDYIE                BIT(RCC_CIR_LSIRDYIE_BIT)
#define RCC_CIR_CSSF                    BIT(RCC_CIR_CSSF_BIT)
#define RCC_CIR_PLLSAIRDYF              BIT(RCC_CIR_PLLSAIRDYF_BIT)
#define RCC_CIR_PLLI2SRDYF              BIT(RCC_CIR_PLLI2SRDYF_BIT)
#define RCC_CIR_PLLRDYF                 BIT(RCC_CIR_PLLRDYF_BIT)
#define RCC_CIR_HSERDYF                 BIT(RCC_CIR_HSERDYF_BIT)
#define RCC_CIR_HSIRDYF                 BIT(RCC_CIR_HSIRDYF_BIT)
#define RCC_CIR_LSERDYF                 BIT(RCC_CIR_LSERDYF_BIT)
#define RCC_CIR_LSIRDYF                 BIT(RCC_CIR_LSIRDYF_BIT)

/*
RCC AHB1 peripheral reset register (RCC_AHB1RSTR)
Address offset: 0x10
Reset value: 0x0000 0000
Access: no wait state, word, half-word and byte access.
*/

#define RCC_AHB1RSTR_OTGHSRST_BIT       29
#define RCC_AHB1RSTR_ETMACRST_BIT       25
#define RCC_AHB1RSTR_DMA2DRST_BIT       23
#define RCC_AHB1RSTR_DMA2RST_BIT        22
#define RCC_AHB1RSTR_DMA1RST_BIT        21
#define RCC_AHB1RSTR_CRCRST_BIT         12
#define RCC_AHB1RSTR_GPIOKRST_BIT       10
#define RCC_AHB1RSTR_GPIOJRST_BIT       9
#define RCC_AHB1RSTR_GPIOIRST_BIT       8
#define RCC_AHB1RSTR_GPIOHRST_BIT       7
#define RCC_AHB1RSTR_GPIOGRST_BIT       6
#define RCC_AHB1RSTR_GPIOFRST_BIT       5
#define RCC_AHB1RSTR_GPIOERST_BIT       4
#define RCC_AHB1RSTR_GPIODRST_BIT       3
#define RCC_AHB1RSTR_GPIOCRST_BIT       2
#define RCC_AHB1RSTR_GPIOBRST_BIT       1
#define RCC_AHB1RSTR_GPIOARST_BIT       0

/*
RCC AHB2 peripheral reset register (RCC_AHB2RSTR)
Address offset: 0x14
Reset value: 0x0000 0000
Access: no wait state, word, half-word and byte access
*/

#define RCC_AHB2RSTR_OTGFSRST_BIT       7
#define RCC_AHB1RSTR_RNGRST_BIT         6
#define RCC_AHB1RSTR_HASHRST_BIT        5
#define RCC_AHB1RSTR_CRYPRST_BIT        4
#define RCC_AHB1RSTR_DCMIRST_BIT        0

/*
RCC AHB3 peripheral reset register (RCC_AHB3RSTR)
Address offset: 0x18
Reset value: 0x0000 0000
Access: no wait state, word, half-word and byte access.
*/

#define RCC_AHB3RSTR_QSPIRST_BIT        1
#define RCC_AHB3RSTR_FMCRST_BIT         0

/*
RCC APB1 peripheral reset register (RCC_APB1RSTR)
Address offset: 0x20
Reset value: 0x0000 0000
Access: no wait state, word, half-word and byte access.
*/

#define RCC_APB1RSTR_UART8RST_BIT       31
#define RCC_APB1RSTR_UART7RST_BIT       30
#define RCC_APB1RSTR_DACRST_BIT         29
#define RCC_APB1RSTR_PWRRST_BIT         28
#define RCC_APB1RSTR_CAN2RST_BIT        26
#define RCC_APB1RSTR_CANR1ST_BIT        25
#define RCC_APB1RSTR_CANRST_BIT         25    // only for compatibility
#define RCC_APB1RSTR_I2C3RST_BIT        23
#define RCC_APB1RSTR_I2C2RST_BIT        22
#define RCC_APB1RSTR_I2C1RST_BIT        21
#define RCC_APB1RSTR_UART5RST_BIT       20
#define RCC_APB1RSTR_UART4RST_BIT       19
#define RCC_APB1RSTR_USART3RST_BIT      18
#define RCC_APB1RSTR_USART2RST_BIT      17
#define RCC_APB1RSTR_SPI3RST_BIT        15
#define RCC_APB1RSTR_SPI2RST_BIT        14
#define RCC_APB1RSTR_WWDGRST_BIT        11
#define RCC_APB1RSTR_TIM14RST_BIT       8
#define RCC_APB1RSTR_TIM13RST_BIT       7
#define RCC_APB1RSTR_TIM12RST_BIT       6
#define RCC_APB1RSTR_TIM7RST_BIT        5
#define RCC_APB1RSTR_TIM6RST_BIT        4
#define RCC_APB1RSTR_TIM5RST_BIT        3
#define RCC_APB1RSTR_TIM4RST_BIT        2
#define RCC_APB1RSTR_TIM3RST_BIT        1
#define RCC_APB1RSTR_TIM2RST_BIT        0

#define RCC_APB1RSTR_UART8RST           BIT(RCC_APB1RSTR_UART8RST_BIT)
#define RCC_APB1RSTR_UART7RST           BIT(RCC_APB1RSTR_UART7RST)
#define RCC_APB1RSTR_DACRST             BIT(RCC_APB1RSTR_DACRST_BIT)
#define RCC_APB1RSTR_PWRRST             BIT(RCC_APB1RSTR_PWRRST_BIT)

#define RCC_APB1RSTR_CAN2RST            BIT(RCC_APB1RSTR_CAN2RST_BIT)
#define RCC_APB1RSTR_CAN1RST            BIT(RCC_APB1RSTR_CAN1RST_BIT)
#define RCC_APB1RSTR_CANRST             BIT(RCC_APB1RSTR_CANRST_BIT)          //only for compatibility

#define RCC_APB1RSTR_I2C3RST            BIT(RCC_APB1RSTR_I2C2RST_BIT)
#define RCC_APB1RSTR_I2C2RST            BIT(RCC_APB1RSTR_I2C2RST_BIT)
#define RCC_APB1RSTR_I2C1RST            BIT(RCC_APB1RSTR_I2C1RST_BIT)
#define RCC_APB1RSTR_UART5RST           BIT(RCC_APB1RSTR_UART5RST_BIT)
#define RCC_APB1RSTR_UART4RST           BIT(RCC_APB1RSTR_UART4RST_BIT)
#define RCC_APB1RSTR_USART3RST          BIT(RCC_APB1RSTR_USART3RST_BIT)
#define RCC_APB1RSTR_USART2RST          BIT(RCC_APB1RSTR_USART2RST_BIT)
#define RCC_APB1RSTR_SPI3RST            BIT(RCC_APB1RSTR_SPI3RST_BIT)
#define RCC_APB1RSTR_SPI2RST            BIT(RCC_APB1RSTR_SPI2RST_BIT)
#define RCC_APB1RSTR_WWDRST             BIT(RCC_APB1RSTR_WWDRST_BIT)
#define RCC_APB1RSTR_TIM14RST           BIT(RCC_APB1RSTR_TIM14RST_BIT)
#define RCC_APB1RSTR_TIM13RST           BIT(RCC_APB1RSTR_TIM13RST_BIT)
#define RCC_APB1RSTR_TIM12RST           BIT(RCC_APB1RSTR_TIM12RST_BIT)
#define RCC_APB1RSTR_TIM7RST            BIT(RCC_APB1RSTR_TIM7RST_BIT)
#define RCC_APB1RSTR_TIM6RST            BIT(RCC_APB1RSTR_TIM6RST_BIT)
#define RCC_APB1RSTR_TIM5RST            BIT(RCC_APB1RSTR_TIM5RST_BIT)
#define RCC_APB1RSTR_TIM4RST            BIT(RCC_APB1RSTR_TIM4RST_BIT)
#define RCC_APB1RSTR_TIM3RST            BIT(RCC_APB1RSTR_TIM3RST_BIT)
#define RCC_APB1RSTR_TIM2RST            BIT(RCC_APB1RSTR_TIM2RST_BIT)

/*
RCC APB2 peripheral reset register (RCC_APB2RSTR)
Address offset: 0x24
Reset value: 0x0000 0000
Access: no wait state, word, half-word and byte access.
*/

#define RCC_APB2RSTR_DSIRST_BIT         27
#define RCC_APB2RSTR_LTDCRST_BIT        26
#define RCC_APB2RSTR_SAI1RST_BIT        22
#define RCC_APB2RSTR_SPI6RST_BIT        21
#define RCC_APB2RSTR_SPI5RST_BIT        20
#define RCC_APB2RSTR_TIM11RST_BIT       18
#define RCC_APB2RSTR_TIM10RST_BIT       17
#define RCC_APB2RSTR_TIM9RST_BIT        16
#define RCC_APB2RSTR_SYSCFGRST_BIT      14
#define RCC_APB2RSTR_SPI4RST_BIT        13
#define RCC_APB2RSTR_SPI1RST_BIT        12
#define RCC_APB2RSTR_SDIORST_BIT        11
#define RCC_APB2RSTR_ADCRST_BIT         8
#define RCC_APB2RSTR_USART6RST_BIT      5
#define RCC_APB2RSTR_USART1RST_BIT      4
#define RCC_APB2RSTR_TIM8RST_BIT        2
#define RCC_APB2RSTR_TIM1RST_BIT        1

#define RCC_APB2RSTR_DSIRST             BIT(RCC_APB2RSTR_DSIRST_BIT)
#define RCC_APB2RSTR_LTDCRST            BIT(RCC_APB2RSTR_LTDCRST_BIT)
#define RCC_APB2RSTR_SAI1RST            BIT(RCC_APB2RSTR_SAI1RST_BIT)
#define RCC_APB2RSTR_SPI6RST            BIT(RCC_APB2RSTR_SPI6RST_BIT)
#define RCC_APB2RSTR_SPI5RST            BIT(RCC_APB2RSTR_SPI5RST_BIT)
#define RCC_APB2RSTR_TIM11RST           BIT(RCC_APB2RSTR_TIM11RST_BIT)
#define RCC_APB2RSTR_TIM10RST           BIT(RCC_APB2RSTR_TIM10RST_BIT)
#define RCC_APB2RSTR_TIM9RST            BIT(RCC_APB2RSTR_TIM9RST_BIT)
#define RCC_APB2RSTR_SYSCFGRST          BIT(RCC_APB2RSTR_SYSCFGRST_BIT)
#define RCC_APB2RSTR_SPI4RST            BIT(RCC_APB2RSTR_SPI4RST_BIT)
#define RCC_APB2RSTR_SPI1RST            BIT(RCC_APB2RSTR_SPI1RST_BIT)
#define RCC_APB2RSTR_SDIORST            BIT(RCC_APB2RSTR_SDIORST_BIT)
#define RCC_APB2RSTR_ADCRST             BIT(RCC_APB2RSTR_ADCRST_BIT)
#define RCC_APB2RSTR_USART6RST          BIT(RCC_APB2RSTR_USART6RST_BIT)
#define RCC_APB2RSTR_USART1RST          BIT(RCC_APB2RSTR_USART1RST_BIT)
#define RCC_APB2RSTR_TIM8RST            BIT(RCC_APB2RSTR_TIM8RST_BIT)
#define RCC_APB2RSTR_TIM1RST            BIT(RCC_APB2RSTR_TIM1RST_BIT)

/*
RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)
Address offset: 0x30
Reset value: 0x0010 0000
Access: no wait state, word, half-word and byte access.
*/

#define RCC_AHB1ENR_OTGHSULPIEN_BIT     30
#define RCC_AHB1ENR_OTGHSEN_BIT         29
#define RCC_AHB1ENR_ETHMACPTPEN_BIT     28
#define RCC_AHB1ENR_ETHMACRXEN_BIT      27
#define RCC_AHB1ENR_ETHMACXTEN_BIT      26
#define RCC_AHB1ENR_ETHMACEN_BIT        25
#define RCC_AHB1ENR_DMA2DEN_BIT         23
#define RCC_AHB1ENR_DMA2EN_BIT          22
#define RCC_AHB1ENR_DMA1EN_BIT          21
#define RCC_AHB1ENR_CCMDATARAMEN_BIT    20
#define RCC_AHB1ENR_BKPSRAMEN_BIT       18
#define RCC_AHB1ENR_CRCEN_BIT           12
#define RCC_AHB1ENR_GPIOK_BIT           10
#define RCC_AHB1ENR_GPIOJ_BIT           9
#define RCC_AHB1ENR_GPIOI_BIT           8
#define RCC_AHB1ENR_GPIOH_BIT           7
#define RCC_AHB1ENR_GPIOG_BIT           6
#define RCC_AHB1ENR_GPIOF_BIT           5
#define RCC_AHB1ENR_GPIOE_BIT           4
#define RCC_AHB1ENR_GPIOD_BIT           3
#define RCC_AHB1ENR_GPIOC_BIT           2
#define RCC_AHB1ENR_GPIOB_BIT           1
#define RCC_AHB1ENR_GPIOA_BIT           0

/*
RCC AHB2 peripheral clock enable register (RCC_AHB2ENR)
Address offset: 0x34
Reset value: 0x0000 0000
Access: no wait state, word, half-word and byte access.
*/

#define RCC_AHB2ENR_OTGFSEN_BIT         7
#define RCC_AHB2ENR_RNGEN_BIT           6
#define RCC_AHB2ENR_HASHEN_BIT          5
#define RCC_AHB2ENR_CRYPEN_BIT          4
#define RCC_AHB2ENR_DCMIEN_BIT          0

/*
RCC AHB3 peripheral clock enable register (RCC_AHB3ENR)
Address offset: 0x38
Reset value: 0x0000 0000
Access: no wait state, word, half-word and byte access.
*/

#define RCC_AHB3ENR_QSPIEN_BIT          1
#define RCC_AHB3ENR_FMCEN_BIT           0

/*
RCC APB1 peripheral clock enable register (RCC_APB1ENR)
Address offset: 0x40
Reset value: 0x0000 0000
Access: no wait state, word, half-word and byte access.
*/
#define RCC_APB1ENR                     0x40023840
#define RCC_APB1ENR_UART8EN_BIT         31
#define RCC_APB1ENR_UART7EN_BIT         30
#define RCC_APB1ENR_DACEN_BIT           29
#define RCC_APB1ENR_PWREN_BIT           28

#define RCC_APB1ENR_CAN2EN_BIT          26
#define RCC_APB1ENR_CAN1EN_BIT          25
#define RCC_APB1ENR_CANEN_BIT           25      // only for compatibility

#define RCC_APB1ENR_I2C3EWN_BIT         23
#define RCC_APB1ENR_I2C2EN_BIT          22
#define RCC_APB1ENR_I2C1EN_BIT          21
#define RCC_APB1ENR_UART5EN_BIT         20
#define RCC_APB1ENR_UART4EN_BIT         19
#define RCC_APB1ENR_USART3EN_BIT        18
#define RCC_APB1ENR_USART2EN_BIT        17
#define RCC_APB1ENR_SPI3EN_BIT          15
#define RCC_APB1ENR_SPI2EN_BIT          14
#define RCC_APB1ENR_WWDEN_BIT           11
#define RCC_APB1ENR_TIM14EN_BIT         8
#define RCC_APB1ENR_TIM13EN_BIT         7
#define RCC_APB1ENR_TIM12EN_BIT         6
#define RCC_APB1ENR_TIM7EN_BIT          5
#define RCC_APB1ENR_TIM6EN_BIT          4
#define RCC_APB1ENR_TIM5EN_BIT          3
#define RCC_APB1ENR_TIM4EN_BIT          2
#define RCC_APB1ENR_TIM3EN_BIT          1
#define RCC_APB1ENR_TIM2EN_BIT          0

#define RCC_APB1ENR_UART8EN             BIT(RCC_APB1ENR_UART8EN_BIT)
#define RCC_APB1ENR_UART7EN             BIT(RCC_APB1ENR_UART7EN_BIT)
#define RCC_APB1ENR_DACEN               BIT(RCC_APB1ENR_DACEN_BIT)
#define RCC_APB1ENR_PWREN               BIT(RCC_APB1ENR_PWREN_BIT)

#define RCC_APB1ENR_CAN2EN              BIT(RCC_APB1ENR_CAN2EN_BIT)
#define RCC_APB1ENR_CAN1EN              BIT(RCC_APB1ENR_CAN1EN_BIT)
#define RCC_APB1ENR_CANEN               BIT(RCC_APB1ENR_CANEN_BIT)         // only for compatibility

#define RCC_APB1ENR_I2C3EN              BIT(RCC_APB1ENR_I2C3EN_BIT)
#define RCC_APB1ENR_I2C2EN              BIT(RCC_APB1ENR_I2C2EN_BIT)
#define RCC_APB1ENR_I2C1EN              BIT(RCC_APB1ENR_I2C1EN_BIT)
#define RCC_APB1ENR_UART5EN             BIT(RCC_APB1ENR_UART5EN_BIT)
#define RCC_APB1ENR_UART4EN             BIT(RCC_APB1ENR_UART4EN_BIT)
#define RCC_APB1ENR_USART3EN            BIT(RCC_APB1ENR_USART3EN_BIT)
#define RCC_APB1ENR_USART2EN            BIT(RCC_APB1ENR_USART2EN_BIT)
#define RCC_APB1ENR_SPI3EN              BIT(RCC_APB1ENR_SPI3EN_BIT)
#define RCC_APB1ENR_SPI2EN              BIT(RCC_APB1ENR_SPI2EN_BIT)
#define RCC_APB1ENR_WWDEN               BIT(RCC_APB1ENR_WWDEN_BIT)
#define RCC_APB1ENR_TIM14EN             BIT(RCC_APB1ENR_TIM14EN_BIT)
#define RCC_APB1ENR_TIM13EN             BIT(RCC_APB1ENR_TIM13EN_BIT)
#define RCC_APB1ENR_TIM12EN             BIT(RCC_APB1ENR_TIM12EN_BIT)
#define RCC_APB1ENR_TIM7EN              BIT(RCC_APB1ENR_TIM7EN_BIT)
#define RCC_APB1ENR_TIM6EN              BIT(RCC_APB1ENR_TIM6EN_BIT)
#define RCC_APB1ENR_TIM5EN              BIT(RCC_APB1ENR_TIM5EN_BIT)
#define RCC_APB1ENR_TIM4EN              BIT(RCC_APB1ENR_TIM4EN_BIT)
#define RCC_APB1ENR_TIM3EN              BIT(RCC_APB1ENR_TIM3EN_BIT)
#define RCC_APB1ENR_TIM2EN              BIT(RCC_APB1ENR_TIM2EN_BIT)

/*
RCC APB2 peripheral clock enable register (RCC_APB2ENR)
Address offset: 0x44
Reset value: 0x0000 0000
Access: no wait state, word, half-word and byte access.
*/
#define RCC_APB2ENR                     0x40023844
#define RCC_APB2ENR_DSIEN_BIT           27
#define RCC_APB2ENR_LTDCEN_BIT          26
#define RCC_APB2ENR_SAI1EN_BIT          22
#define RCC_APB2ENR_SPI6EN_BIT          21
#define RCC_APB2ENR_SPI5EN_BIT          20
#define RCC_APB2ENR_TIM11EN_BIT         18
#define RCC_APB2ENR_TIM10EN_BIT         17
#define RCC_APB2ENR_TIM9EN_BIT          16
#define RCC_APB2ENR_SYSCFGEN_BIT        14
#define RCC_APB2ENR_SPI4EN_BIT          13
#define RCC_APB2ENR_SPI1EN_BIT          12
#define RCC_APB2ENR_SDIOEN_BIT          11
#define RCC_APB2ENR_ADC3EN_BIT          10
#define RCC_APB2ENR_ADC2EN_BIT          9
#define RCC_APB2ENR_ADC1EN_BIT          8
#define RCC_APB2ENR_USART6EN_BIT        5
#define RCC_APB2ENR_USART1EN_BIT        4
#define RCC_APB2ENR_TIM8EN_BIT          1
#define RCC_APB2ENR_TIM1EN_BIT          0

#define RCC_APB2ENR_DSIEN               BIT(RCC_APB2ENR_DSIEN_BIT)
#define RCC_APB2ENR_LTDCEN              BIT(RCC_APB2ENR_LTDCEN_BIT)
#define RCC_APB2ENR_SAI1EN              BIT(RCC_APB2ENR_SAI1EN_BIT)
#define RCC_APB2ENR_SPI6EN              BIT(RCC_APB2ENR_SPI6EN_BIT)
#define RCC_APB2ENR_SPI5EN              BIT(RCC_APB2ENR_SPI5EN_BIT)
#define RCC_APB2ENR_TIM11EN             BIT(RCC_APB2ENR_TIM11EN_BIT)
#define RCC_APB2ENR_TIM10EN             BIT(RCC_APB2ENR_TIM10EN_BIT)
#define RCC_APB2ENR_TIM9EN              BIT(RCC_APB2ENR_TIM9EN_BIT)
#define RCC_APB2ENR_SYSCFGEN            BIT(RCC_APB2ENR_SYSCFGEN_BIT)
#define RCC_APB2ENR_SPI4EN              BIT(RCC_APB2ENR_SPI4EN_BIT)
#define RCC_APB2ENR_SPI1EN              BIT(RCC_APB2ENR_SPI1EN_BIT)
#define RCC_APB2ENR_SDIOEN              BIT(RCC_APB2ENR_SDIOEN_BIT)
#define RCC_APB2ENR_ADC3EN              BIT(RCC_APB2ENR_ADC3EN_BIT)
#define RCC_APB2ENR_ADC2EN              BIT(RCC_APB2ENR_ADC2EN_BIT)
#define RCC_APB2ENR_ADC1EN              BIT(RCC_APB2ENR_ADC1EN_BIT)
#define RCC_APB2ENR_USART6EN            BIT(RCC_APB2ENR_USART6EN_BIT)
#define RCC_APB2ENR_USART1EN            BIT(RCC_APB2ENR_USART1EN_BIT)
#define RCC_APB2ENR_TIM8EN              BIT(IRCC_APB2ENR_TIM8EN_BIT)
#define RCC_APB2ENR_TIM1EN              BIT(RCC_APB2ENR_TIM1EN_BIT)

/*
RCC AHB1 peripheral clock enable in low power mode register
(RCC_AHB1LPENR)
Address offset: 0x50
Reset value: 0x7EEF 97FF
Access: no wait state, word, half-word and byte access.
*/

#define RCC_AHB1LPENR_OTGHSULPILPEN_BIT   30
#define RCC_AHB1LPENR_OTGHSLPEN_BIT       29
#define RCC_AHB1LPENR_ETHPTPLPEN_BIT      28
#define RCC_AHB1LPENR_ETHRXLPEN_BIT       27
#define RCC_AHB1LPENR_ETHTXLPEN_BIT       26
#define RCC_AHB1LPENR_ETHMACLPEN_BIT      25
#define RCC_AHB1LPENR_DMA2DLPEN_BIT       23
#define RCC_AHB1LPENR_DMA2LPEN_BIT        22
#define RCC_AHB1LPENR_DMA1LPEN_BIT        21
#define RCC_AHB1LPENR_SRAM3LPEN_BIT       19
#define RCC_AHB1LPENR_BKPSRAMLPEN_BIT     18
#define RCC_AHB1LPENR_SRAM2LPEN_BIT       17
#define RCC_AHB1LPENR_SRAM1LPEN_BIT       16
#define RCC_AHB1LPENR_FLITFLPEN_BIT       15
#define RCC_AHB1LPENR_CRCLPEN_BIT         12
#define RCC_AHB1LPENR_GPIOK_BIT           10
#define RCC_AHB1LPENR_GPIOJ_BIT           9
#define RCC_AHB1LPENR_GPIOI_BIT           8
#define RCC_AHB1LPENR_GPIOH_BIT           7
#define RCC_AHB1LPENR_GPIOG_BIT           6
#define RCC_AHB1LPENR_GPIOF_BIT           5
#define RCC_AHB1LPENR_GPIOE_BIT           4
#define RCC_AHB1LPENR_GPIOD_BIT           3
#define RCC_AHB1LPENR_GPIOC_BIT           2
#define RCC_AHB1LPENR_GPIOB_BIT           1
#define RCC_AHB1LPENR_GPIOA_BIT           0

#define RCC_AHB1LPENR_OTGHSULPILPEN       BIT(RCC_AHB1LPENR_OTGHSULPILPEN_BIT)
#define RCC_AHB1LPENR_OTGHSLPEN           BIT(RCC_AHB1LPENR_OTGHSLPEN_BIT)
#define RCC_AHB1LPENR_ETHPTPLPEN          BIT(RCC_AHB1LPENR_ETHPTPLPEN_BIT)
#define RCC_AHB1LPENR_ETHRXLPEN           BIT(RCC_AHB1LPENR_ETHRXLPEN_BIT)
#define RCC_AHB1LPENR_ETHTXLPEN           BIT(RCC_AHB1LPENR_ETHTXLPEN_BIT)
#define RCC_AHB1LPENR_ETHMACLPEN          BIT(RCC_AHB1LPENR_ETHMACLPEN_BIT)
#define RCC_AHB1LPENR_DMA2DLPEN           BIT(RCC_AHB1LPENR_DMA2DLPEN_BIT)
#define RCC_AHB1LPENR_DMA2LPEN            BIT(RCC_AHB1LPENR_DMA2LPEN_BIT)
#define RCC_AHB1LPENR_DMA1LPEN            BIT(CC_AHB1LPENR_DMA1LPEN_BIT)
#define RCC_AHB1LPENR_SRAM3LPEN           BIT(RCC_AHB1LPENR_SRAM3LPEN_BIT)
#define RCC_AHB1LPENR_BKPSRAMLPEN         BIT(RCC_AHB1LPENR_BKPSRAMLPEN_BIT)
#define RCC_AHB1LPENR_SRAM2LPEN           BIT(RCC_AHB1LPENR_SRAM2LPEN_BIT)
#define RCC_AHB1LPENR_SRAM1LPEN           BIT(RCC_AHB1LPENR_SRAM1LPEN_BIT)
#define RCC_AHB1LPENR_FLITFLPEN           BIT(RCC_AHB1LPENR_FLITFLPEN_BIT)
#define RCC_AHB1LPENR_CRCLPEN             BIT(RCC_AHB1LPENR_CRCLPEN_BIT)
#define RCC_AHB1LPENR_GPIOKLPEN           BIT(RCC_AHB1LPENR_GPIOKLPEN_BIT)
#define RCC_AHB1LPENR_GPIOJLPEN           BIT(RCC_AHB1LPENR_GPIOJLPEN_BIT)
#define RCC_AHB1LPENR_GPIOILPEN           BIT(RCC_AHB1LPENR_GPIOILPEN_BIT)
#define RCC_AHB1LPENR_GPIOHLPEN           BIT(RCC_AHB1LPENR_GPIOHLPEN_BIT)
#define RCC_AHB1LPENR_GPIOGLPEN           BIT(RCC_AHB1LPENR_GPIOGLPEN_BIT)
#define RCC_AHB1LPENR_GPIOFLPEN           BIT(RCC_AHB1LPENR_GPIOFLPEN_BIT)
#define RCC_AHB1LPENR_GPIOELPEN           BIT(RCC_AHB1LPENR_GPIOELPEN_BIT)
#define RCC_AHB1LPENR_GPIODLPEN           BIT(RCC_AHB1LPENR_GPIODLPEN_BIT)
#define RCC_AHB1LPENR_GPIOCLPEN           BIT(RCC_AHB1LPENR_GPIOCLPEN_BIT)
#define RCC_AHB1LPENR_GPIOBLPEN           BIT(RCC_AHB1LPENR_GPIOBLPEN_BIT)
#define RCC_AHB1LPENR_GPIOALPEN           BIT(RCC_AHB1LPENR_GPIOALPEN_BIT)

/*
RCC AHB2 peripheral clock enable in low power mode register
(RCC_AHB2LPENR)
Address offset: 0x54
Reset value: 0x0000 00F1
Access: no wait state, word, half-word and byte access.
*/

#define RCC_AHB2LPENR_OTGFSLPEN_BIT       7
#define RCC_AHB2LPENR_RNGLPEN_BIT         6
#define RCC_AHB2LPENR_HASHLPEN_BIT        5
#define RCC_AHB2LPENR_CRYPLPEN_BIT        4
#define RCC_AHB2LPENR_DCMILPEN_BIT        0

#define RCC_AHB2LPENR_OTGFSLPEN           BIT(RCC_AHB2LPENR_OTGFSLPEN_BIT)
#define RCC_AHB2LPENR_RNGLPEN             BIT(RCC_AHB2LPENR_RNGLPEN_BIT)
#define RCC_AHB2LPENR_HASHLPEN            BIT(RCC_AHB2LPENR_HASHLPEN_BIT)
#define RCC_AHB2LPENR_CRYPLPEN            BIT(RCC_AHB2LPENR_CRYPLPEN_BIT)
#define RCC_AHB2LPENR_DCMILPEN            BIT(RCC_AHB2LPENR_DCMILPEN_BIT)

/*
RCC AHB3 peripheral clock enable in low power mode register
(RCC_AHB3LPENR)
Address offset: 0x58
Reset value: 0x0000 0003
Access: no wait state, word, half-word and byte access.
*/

#define RCC_AHB3LPENR_QSPILPEN_BIT      1
#define RCC_AHB3LPENR_FMCLPEN_BIT       0

#define RCC_AHB3LPENR_QSPILPEN      BIT(RCC_AHB3LPENR_QSPILPEN_BIT)
#define RCC_AHB3LPENR_FMCLPEN       BIT(RCC_AHB3LPENR_FMCLPEN_BIT)

/*
RCC APB1 peripheral clock enable in low power mode register
(RCC_APB1LPENR)
Address offset: 0x60
Reset value: 0xF6FE C9FF
Access: no wait state, word, half-word and byte access.
*/

#define RCC_APB1LPENR_UART8LPEN_BIT         31
#define RCC_APB1LPENR_UART7LPEN_BIT         30
#define RCC_APB1LPENR_DACLPEN_BIT           29
#define RCC_APB1LPENR_PWRLPEN_BIT           28

#define RCC_APB1LPENR_CAN2LPEN_BIT          26
#define RCC_APB1LPENR_CAN1LPEN_BIT          25
#define RCC_APB1LPENR_CANLPEN_BIT           25      // only for compatibility

#define RCC_APB1LPENR_I2C3LPEN_BIT          23
#define RCC_APB1LPENR_I2C2LPEN_BIT          22
#define RCC_APB1LPENR_I2C1LPEN_BIT          21
#define RCC_APB1LPENR_UART5LPEN_BIT         20
#define RCC_APB1LPENR_UART4LPEN_BIT         19
#define RCC_APB1LPENR_USART3LPEN_BIT        18
#define RCC_APB1LPENR_USART2LPEN_BIT        17
#define RCC_APB1LPENR_SPI3LPEN_BIT          15
#define RCC_APB1LPENR_SPI2LPEN_BIT          14
#define RCC_APB1LPENR_WWDLPEN_BIT           11
#define RCC_APB1LPENR_TIM14LPEN_BIT         8
#define RCC_APB1LPENR_TIM13LPEN_BIT         7
#define RCC_APB1LPENR_TIM12LPEN_BIT         6
#define RCC_APB1LPENR_TIM7LPEN_BIT          5
#define RCC_APB1LPENR_TIM6LPEN_BIT          4
#define RCC_APB1LPENR_TIM5LPEN_BIT          3
#define RCC_APB1LPENR_TIM4LPEN_BIT          2
#define RCC_APB1LPENR_TIM3LPEN_BIT          1
#define RCC_APB1LPENR_TIM2LPEN_BIT          0

#define RCC_APB1LPENR_UART8LPEN_BIT         BIT(RCC_APB1LPENR_UART8LPEN_BIT)
#define RCC_APB1LPENR_UART7LPEN             BIT(RCC_APB1LPENR_UART7LPEN_BIT)
#define RCC_APB1LPENR_DACLPEN               BIT(RCC_APB1LPENR_DACLPEN_BIT)
#define RCC_APB1LPENR_PWRLPEN               BIT(RCC_APB1LPENR_PWRLPEN_BIT)
#define RCC_APB1LPENR_CAN2LPEN              BIT(RCC_APB1LPENR_CAN2LPEN_BIT)
#define RCC_APB1LPENR_CAN1LPEN              BIT(RCC_APB1LPENR_CAN1LPEN_BIT)
#define RCC_APB1LPENR_CANLPEN               BIT(RCC_APB1LPENR_CANLPEN_BIT)         // only for compatibilit
#define RCC_APB1LPENR_I2C3LPEN              BIT(RCC_APB1LPENR_I2C3LPEN_BIT)
#define RCC_APB1LPENR_I2C2LPEN              BIT(RCC_APB1LPENR_I2C2LPEN_BIT)
#define RCC_APB1LPENR_I2C1LPEN              BIT(RCC_APB1LPENR_I2C1LPEN_BIT)
#define RCC_APB1LPENR_UART5LPEN             BIT(RCC_APB1LPENR_UART5LPEN_BIT)
#define RCC_APB1LPENR_UART4LPEN             BIT(RCC_APB1LPENR_UART4LPEN_BIT)
#define RCC_APB1LPENR_USART3LPEN            BIT(RCC_APB1LPENR_USART3LPEN_BIT)
#define RCC_APB1LPENR_USART2LPEN            BIT(RCC_APB1LPENR_USART2LPEN_BIT)
#define RCC_APB1LPENR_SPI3LPEN              BIT(RCC_APB1LPENR_SPI3LPEN_BIT)
#define RCC_APB1LPENR_SPI2LPEN              BIT(RCC_APB1LPENR_SPI2LPEN_BIT)
#define RCC_APB1LPENR_WWDLPEN               BIT(RCC_APB1LPENR_WWDLPEN_BIT)
#define RCC_APB1LPENR_TIM14LPEN             BIT(RCC_APB1LPENR_TIM14LPEN_BIT)
#define RCC_APB1LPENR_TIM13LPEN             BIT(RCC_APB1LPENR_TIM13LPEN_BIT)
#define RCC_APB1LPENR_TIM12LPEN             BIT(RCC_APB1LPENR_TIM12LPEN_BIT)
#define RCC_APB1LPENR_TIM7LPEN              BIT(RCC_APB1LPENR_TIM7LPEN_BIT)
#define RCC_APB1LPENR_TIM6LPEN              BIT(RCC_APB1LPENR_TIM6LPEN_BIT)
#define RCC_APB1LPENR_TIM5LPEN              BIT(RCC_APB1LPENR_TIM5LPEN_BIT)
#define RCC_APB1LPENR_TIM4LPEN              BIT(RCC_APB1LPENR_TIM4LPEN_BIT)
#define RCC_APB1LPENR_TIM3LPEN              BIT(RCC_APB1LPENR_TIM3LPEN_BIT)
#define RCC_APB1LPENR_TIM2LPEN              BIT(RCC_APB1LPENR_TIM2LPEN_BIT)


/*
RCC APB2 peripheral clock enabled in low power mode register
(RCC_APB2LPENR)
Address offset: 0x64
Reset value: 0x0C77 7F33
Access: no wait state, word, half-word and byte access.
*/


#define RCC_APB2LPENR_DSILPEN_BIT           27
#define RCC_APB2LPENR_LTDCLPEN_BIT          26
#define RCC_APB2LPENR_SAI1LPEN_BIT          22
#define RCC_APB2LPENR_SPI6LPEN_BIT          21
#define RCC_APB2LPENR_SPI5LPEN_BIT          20
#define RCC_APB2LPENR_TIM11LPEN_BIT         18
#define RCC_APB2LPENR_TIM10LPEN_BIT         17
#define RCC_APB2LPENR_TIM9LPEN_BIT          16
#define RCC_APB2LPENR_SYSCFGLPEN_BIT        14
#define RCC_APB2LPENR_SPI4LPEN_BIT          13
#define RCC_APB2LPENR_SPI1LPEN_BIT          12
#define RCC_APB2LPENR_SDIOLPEN_BIT          11
#define RCC_APB2LPENR_ADC3LPEN_BIT          10
#define RCC_APB2LPENR_ADC2LPEN_BIT          9
#define RCC_APB2LPENR_ADC1LPEN_BIT          8
#define RCC_APB2LPENR_USART6LPEN_BIT        5
#define RCC_APB2LPENR_USART1LPEN_BIT        4
#define RCC_APB2LPENR_TIM8LPEN_BIT          1
#define RCC_APB2LPENR_TIM1LPEN_BIT          0

#define RCC_APB2LPENR_DSILPEN               BIT(RCC_APB2LPENR_DSILPEN_BIT)
#define RCC_APB2LPENR_LTDCLPEN              BIT(RCC_APB2LPENR_LTDCLPEN_BIT)
#define RCC_APB2LPENR_SAI1LPEN              BIT(RCC_APB2LPENR_SAI1LPEN_BIT)
#define RCC_APB2LPENR_SPI6LPEN              BIT(RCC_APB2LPENR_SPI6LPEN_BIT)
#define RCC_APB2LPENR_SPI5LPEN              BIT(RCC_APB2LPENR_SPI5LPEN_BIT)
#define RCC_APB2LPENR_TIM11LPEN             BIT(RCC_APB2LPENR_TIM11LPEN_BIT)
#define RCC_APB2LPENR_TIM10LPEN             BIT(RCC_APB2LPENR_TIM10LPEN_BIT)
#define RCC_APB2LPENR_TIM9LPEN              BIT(RCC_APB2LPENR_TIM9LPEN_BIT)
#define RCC_APB2LPENR_SYSCFGLPEN            BIT(RCC_APB2LPENR_SYSCFGLPEN_BIT)
#define RCC_APB2LPENR_SPI4LPEN              BIT(RCC_APB2LPENR_SPI4LPEN_BIT)
#define RCC_APB2LPENR_SPI1LPEN              BIT(RCC_APB2LPENR_SPI1LPEN_BIT)
#define RCC_APB2LPENR_SDIOLPEN              BIT(RCC_APB2LPENR_SDIOLPEN_BIT)
#define RCC_APB2LPENR_ADC3LPEN              BIT(RCC_APB2LPENR_ADC3LPEN_BIT)
#define RCC_APB2LPENR_ADC2LPEN              BIT(RCC_APB2LPENR_ADC2LPEN_BIT)
#define RCC_APB2LPENR_ADC1LPEN              BIT(RCC_APB2LPENR_ADC1LPEN_BIT)
#define RCC_APB2LPENR_USART6LPEN            BIT(RCC_APB2LPENR_USART6LPEN_BIT)
#define RCC_APB2LPENR_USART1LPEN            BIT(RCC_APB2LPENR_USART1LPEN_BIT)
#define RCC_APB2LPENR_TIM8LPEN              BIT(IRCC_APB2LPENR_TIM8LPEN_BIT)
#define RCC_APB2LPENR_TIM1LPEN              BIT(RCC_APB2LPENR_TIM1LPEN_BIT)

/*
Address offset: 0x70
Reset value: 0x0000 0000, reset by Backup domain reset.
Access: 0 ≤ wait state ≤ 3, word, half-word and byte access
Wait states are inserted in case of successive accesses to this register.
*/

#define RCC_BDCR_BDRST_BIT              16
#define RCC_BDCR_RTCEN_BIT              15
#define RCC_BDCR_LSEMOD_BIT             3
#define RCC_BDCR_LSEBYP_BIT             2
#define RCC_BDCR_LSERDY_BIT             1
#define RCC_BDCR_LSEON_BIT              0

#define RCC_BDCR_BDRST                  BIT(RCC_BDCR_BDRST_BIT)
#define RCC_BDCR_RTCEN                  BIT(RCC_BDCR_RTC_BIT)
#define RCC_BDCR_RTCSEL                 (0x3 << 8)
#define RCC_BDCR_RTCSEL_NONE            (0x0 << 8)
#define RCC_BDCR_RTCSEL_LSE             (0x1 << 8)
#define RCC_BDCR_RTCSEL_HSE             (0x3 << 8)
#define RCC_BDCR_LSEMOD                 BIT(RCC_BDCR_LSEMOD_BIT)
#define RCC_BDCR_LSEBYP                 BIT(RCC_BDCR_LSEBYP_BIT)
#define RCC_BDCR_LSERDY                 BIT(RCC_BDCR_LSERDY_BIT)
#define RCC_BDCR_LSEON                  BIT(RCC_BDCR_LSEON_BIT)

/*
RCC clock control & status register (RCC_CSR)
Address offset: 0x74
Reset value: 0x0E00 0000, reset by system reset, except reset flags by power reset only.
Access: 0 ≤ wait state ≤ 3, word, half-word and byte access
Wait states are inserted in case of successive accesses to this register.
*/

#define RCC_CSR_LPWRRSTF_BIT            31
#define RCC_CSR_WWDGRSTF_BIT            30
#define RCC_CSR_IWDGRSTF_BIT            29
#define RCC_CSR_SFTRSTF_BIT             28
#define RCC_CSR_PORRSTF_BIT             27
#define RCC_CSR_PINRSTF_BIT             26
#define RCC_CSR_BORRSTF_BIT             25
#define RCC_CSR_RMVF_BIT                24
#define RCC_CSR_LSIRDY_BIT              1
#define RCC_CSR_LSION_BIT               0

#define RCC_CSR_LPWRRSTF                BIT(RCC_CSR_LPWRRSTF_BIT)
#define RCC_CSR_WWDGRSTF                BIT(RCC_CSR_WWDGRSTF_BIT)
#define RCC_CSR_IWDGRSTF                BIT(RCC_CSR_IWDGRSTF_BIT)
#define RCC_CSR_SFTRSTF                 BIT(RCC_CSR_SFTRSTF_BIT)
#define RCC_CSR_PORRSTF                 BIT(RCC_CSR_PORRSTF_BIT)
#define RCC_CSR_PINRSTF                 BIT(RCC_CSR_PINRSTF_BIT)
#define RCC_CSR_BORRSTF                 BIT(RCC_CSR_BORRSTF_BIT)
#define RCC_CSR_RMVF                    BIT(RCC_CSR_RMVF_BIT)
#define RCC_CSR_LSIRDY                  BIT(RCC_CSR_LSIRDY_BIT)
#define RCC_CSR_LSION                   BIT(RCC_CSR_LSION_BIT)

/*
RCC spread spectrum clock generation register (RCC_SSCGR)
Address offset: 0x80
Reset value: 0x0000 0000
Access: no wait state, word, half-word and byte access.
The spread spectrum clock generation is available only for the main PLL.
The RCC_SSCGR register must be written either before the main PLL is enabled or after
the main PLL disabled.
*/

#define RCC_SSCGR_SSCGEN_BIT          31
#define RCC_SSCGR_SPREADSEL_BIT       30

#define RCC_SSCGR_SSCGEN              BIT(RCC_SSCGR_SSCGEN_BIT)
#define RCC_SSCGR_SPREADSEL           BIT(RCC_SSCGR_SPREADSEL_BIT)
#define RCC_SSCGR_INCSTEP             (0x00 << 13)
#define RCC_SSCGR_MODPER              (0x00 << 0)

/*
RCC PLLI2S configuration register (RCC_PLLI2SCFGR)
Address offset: 0x84
Reset value: 0x2400 3000
Access: no wait state, word, half-word and byte access.
*/

#define RCC_PLLI2SCFGR_PLLI2SR        (0b010 << 28)     // alfran: to be setted
#define RCC_PLLI2SCFGR_PLLI2SQ        (0b0010 << 24)    // alfran: to be setted
#define RCC_PLLI2SCFGR_PLLI2SN        (0b001100010 <<6) // alfran: to be setted

/*
RCC PLL configuration register (RCC_PLLSAICFGR)
Address offset: 0x88
Reset value: 0x2400 3000
Access: no wait state, word, half-word and byte access.
This register is used to configure the PLLSAI clock outputs according to the formulas:
*/

#define RCC_PLLSAICFGR_PLLSAIR        (0b010 << 28)       // alfran: to be setted
#define RCC_PLLSAICFGR_PLLSAIQ        (0b0010 << 24)      // alfran: to be setted
#define RCC_PLLSAICFGR_PLLSAIP        (0b00 << 16)        // alfran: to be setted
#define RCC_PLLSAICFGR_PLLSAIN        (0b001100010 << 6)  // alfran: to be setted

/*
RCC Dedicated Clock Configuration Register (RCC_DCKCFGR)
Address offset: 0x8C
Reset value: 0x0000 0000
Access: no wait state, word, half-word and byte access.
*/

#define RCC_DCKCFGR_DSISEL_BIT        29
#define RCC_DCKCFGR_SDMMCSEL_BIT      28
#define RCC_DCKCFGR_48MSEL_BIT        27
#define RCC_DCKCFGR_TIMPRE_BIT        24

#define RCC_DCKCFGR_DSISEL            BIT(RCC_DCKCFGR_DSISEL_BIT)
#define RCC_DCKCFGR_SDMMCSEL          BIT(RCC_DCKCFGR_SDMMCSEL_BIT)
#define RCC_DCKCFGR_48MSEL            BIT(RCC_DCKCFGR_48MSEL_BIT)
#define RCC_DCKCFGR_TIMPRE            BIT(RCC_DCKCFGR_TIMPRE_BIT)
#define RCC_DCKCFGR_SAI1BSRC          (0b00 << 22)  // alfran: to be setted
#define RCC_DCKCFGR_SAI1ARSR          (0b00 << 20)  // alfran: to be setted
#define RCC_DCKCFGR_PLLSAIDIVR        (0b00 << 16)  // alfran: no configuration reported in datasheet
#define RCC_DCKCFGR_PLLSAIDIVQ        (0b00000 << 8)// alfran: to be setted
#define RCC_DCKCFGR_PLLIS2DIVQ        (0b00000 << 0)// alfran: to be setted

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
