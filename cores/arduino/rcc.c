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
 * @file rcc.c
 * @brief Implements pretty much only the basic clock setup on the
 *        stm32, clock enable/disable and peripheral reset commands.
 */

 /*
 * Arduino srl - www.arduino.org
 * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
 */

#include "memory.h"
#include "flash.h"
#include "gpio.h"
#include "rcc.h"
#include "bitband.h"

#define APB1                            RCC_APB1
#define APB2                            RCC_APB2
#define AHB1                            RCC_AHB1
#define AHB2                            RCC_AHB2
#define AHB3                            RCC_AHB3

struct rcc_dev_info {
    const rcc_clk_domain clk_domain;
    const uint8 line_num;
};

static uint32 rcc_dev_clk_speed_table[AHB3];

/* Device descriptor table, maps rcc_clk_id onto bus and enable/reset
 * register bit numbers. */
static const struct rcc_dev_info rcc_dev_table[] = {

// AHB3

	  [RCC_FMC] 		  = { .clk_domain = AHB3, .line_num = 0 },
	  [RCC_QSPI] 		  = { .clk_domain = AHB3, .line_num = 1 },

 // AHB2
    [RCC_DCMI]		  = { .clk_domain = AHB2, .line_num = 0 },

    [RCC_CRYP]		  = { .clk_domain = AHB2, .line_num = 4 },
    [RCC_HASH]		  = { .clk_domain = AHB2, .line_num = 5 },
    [RCC_RNG]		    = { .clk_domain = AHB2, .line_num = 6 },
    [RCC_OTGFS]   	= { .clk_domain = AHB2, .line_num = 7 },
    [RCC_USBFS]   	= { .clk_domain = AHB2, .line_num = 7 }, //for compatibility

// AHB1
    [RCC_GPIOA] 	  = { .clk_domain = AHB1, .line_num =  0 },
    [RCC_GPIOB]   	= { .clk_domain = AHB1, .line_num =  1 },
    [RCC_GPIOC]   	= { .clk_domain = AHB1, .line_num =  2 },
    [RCC_GPIOD]   	= { .clk_domain = AHB1, .line_num =  3 },
    [RCC_GPIOE]   	= { .clk_domain = AHB1, .line_num =  4 },
    [RCC_GPIOF]   	= { .clk_domain = AHB1, .line_num =  5 },
    [RCC_GPIOG]   	= { .clk_domain = AHB1, .line_num =  6 },
    [RCC_GPIOH]   	= { .clk_domain = AHB1, .line_num =  7 },
    [RCC_GPIOI]   	= { .clk_domain = AHB1, .line_num =  8 },
    [RCC_GPIOJ]   	= { .clk_domain = AHB1, .line_num =  9 },
    [RCC_GPIOK]   	= { .clk_domain = AHB1, .line_num = 10 },

    [RCC_CRC]     	= { .clk_domain = AHB1, .line_num = 12 },

    [RCC_FLITFLP]   = { .clk_domain = AHB1, .line_num = 15 },
    [RCC_SRAM1LP]  	= { .clk_domain = AHB1, .line_num = 16 },
    [RCC_SRAM2LP]  	= { .clk_domain = AHB1, .line_num = 17 },

    [RCC_BKP]     	= { .clk_domain = AHB1, .line_num = 18 },
	  [RCC_SRAM3LP]  	= { .clk_domain = AHB1, .line_num = 19 },
    [RCC_CCDATARAM] = { .clk_domain = AHB1, .line_num = 20 },
    [RCC_DMA1]    	= { .clk_domain = AHB1, .line_num = 21 },
    [RCC_DMA2]    	= { .clk_domain = AHB1, .line_num = 22 },
    [RCC_DMA2D]    	= { .clk_domain = AHB1, .line_num = 23 },

    [RCC_ETH]    	  = { .clk_domain = AHB1, .line_num = 25 },
    [RCC_ETHTX]    	= { .clk_domain = AHB1, .line_num = 26 },
    [RCC_ETHRX]    	= { .clk_domain = AHB1, .line_num = 27 },
    [RCC_ETHPTP]    = { .clk_domain = AHB1, .line_num = 28 },
    [RCC_OTGHS]    	= { .clk_domain = AHB1, .line_num = 29 },
    [RCC_OTGHSULPI] = { .clk_domain = AHB1, .line_num = 30 },

// APB2

    [RCC_TIMER1]  	= { .clk_domain = APB2, .line_num =  0 },
    [RCC_TIMER8]  	= { .clk_domain = APB2, .line_num =  1 },

    [RCC_USART1]  	= { .clk_domain = APB2, .line_num =  4 },
    [RCC_USART6]  	= { .clk_domain = APB2, .line_num =  5},

    [RCC_ADC1]    	= { .clk_domain = APB2, .line_num =  8 },
    [RCC_ADC2]    	= { .clk_domain = APB2, .line_num =  9 },
    [RCC_ADC3]    	= { .clk_domain = APB2, .line_num = 10 },
    [RCC_SDIO]    	= { .clk_domain = APB2, .line_num = 11 },
    [RCC_SPI1]    	= { .clk_domain = APB2, .line_num = 12 },
    [RCC_SPI4]    	= { .clk_domain = APB2, .line_num = 13 },
    [RCC_SYSCFG]  	= { .clk_domain = APB2, .line_num = 14 },

    [RCC_TIMER9]  	= { .clk_domain = APB2, .line_num = 16 },
    [RCC_TIMER10] 	= { .clk_domain = APB2, .line_num = 17 },
    [RCC_TIMER11] 	= { .clk_domain = APB2, .line_num = 18 },

    [RCC_SPI5]	 	  = { .clk_domain = APB2, .line_num = 20 },
    [RCC_SPI6]	 	  = { .clk_domain = APB2, .line_num = 21 },
    [RCC_SAI1]	 	  = { .clk_domain = APB2, .line_num = 22 },

    [RCC_LTDC]	 	  = { .clk_domain = APB2, .line_num = 26 },
    [RCC_DSI]	 	    = { .clk_domain = APB2, .line_num = 27 },


// APB1

    [RCC_TIMER2]  	= { .clk_domain = APB1, .line_num =  0 },
    [RCC_TIMER3]  	= { .clk_domain = APB1, .line_num =  1 },
    [RCC_TIMER4]  	= { .clk_domain = APB1, .line_num =  2 },
    [RCC_TIMER5]  	= { .clk_domain = APB1, .line_num =  3 },
    [RCC_TIMER6]  	= { .clk_domain = APB1, .line_num =  4 },
    [RCC_TIMER7]  	= { .clk_domain = APB1, .line_num =  5 },
    [RCC_TIMER12]  	= { .clk_domain = APB1, .line_num =  6 },
    [RCC_TIMER13]  	= { .clk_domain = APB1, .line_num =  7 },
    [RCC_TIMER14]  	= { .clk_domain = APB1, .line_num =  8 },

    [RCC_WWDG]  	  = { .clk_domain = APB1, .line_num = 11 },

    [RCC_SPI2]    	= { .clk_domain = APB1, .line_num = 14 },
    [RCC_SPI3]    	= { .clk_domain = APB1, .line_num = 15 },

    [RCC_USART2]  	= { .clk_domain = APB1, .line_num = 17 },
    [RCC_USART3]  	= { .clk_domain = APB1, .line_num = 18 },
	  [RCC_UART4]   	= { .clk_domain = APB1, .line_num = 19 },
    [RCC_UART5]   	= { .clk_domain = APB1, .line_num = 20 },
    [RCC_I2C1]    	= { .clk_domain = APB1, .line_num = 21 },
    [RCC_I2C2]    	= { .clk_domain = APB1, .line_num = 22 },
 	  [RCC_I2C3]    	= { .clk_domain = APB1, .line_num = 23 },

 	  [RCC_CAN1]    	= { .clk_domain = APB1, .line_num = 25 },
 	  [RCC_CAN2]    	= { .clk_domain = APB1, .line_num = 26 },

    [RCC_PWR]     	= { .clk_domain = APB1, .line_num = 28},
    [RCC_DAC]     	= { .clk_domain = APB1, .line_num = 29 },
	  [RCC_UART7]   	= { .clk_domain = APB1, .line_num = 30 },
    [RCC_UART8]   	= { .clk_domain = APB1, .line_num = 31 },

};

/**
 * @brief Initialize the clock control system. Initializes the system
 *        clock source to use the PLL driven by an external oscillator
 * @param sysclk_src system clock source, must be PLL
 * @param pll_src pll clock source, must be HSE
 * @param pll_mul pll multiplier
 */


/*******************  Bits definition for FLASH_ACR register  *****************/

#define RESET 0

void InitMCO1()
{
    RCC_TypeDef *rcc = RCC;
    // Turn MCO1 Master Clock Output mode
    rcc->CFGR &= RCC_CFGR_MCO1_RESET_MASK;
    rcc->CFGR |= RCC_CFGR_MCO1Source_PLLCLK | RCC_CFGR_MCO1Div_1;
    // PA8 Output the Master Clock MCO1
    gpio_set_af_mode(GPIOA_dev, 8, 0);
    gpio_set_mode(GPIOA_dev, 8, GPIO_MODE_AF | GPIO_OTYPE_PP | GPIO_OSPEED_100MHZ);
}

void SetupClock()
{

  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
#ifdef ARDUINO_STM32F4_NETDUINO2PLUS
  RCC_OscInitStruct.PLL.PLLM = 25;
#else
  RCC_OscInitStruct.PLL.PLLM = 4;
#endif
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  RCC_OscInitStruct.PLL.PLLR = 2;

  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Activate the OverDrive to reach the 180 MHz Frequency */
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV16;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }


  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CK48;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV8;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CK48CLKSOURCE_PLLSAIP;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

  HAL_RCC_EnableCSS();

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 7;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

  InitMCO1();

  // save bus clock values
  rcc_dev_clk_speed_table[RCC_AHB1] = (SystemCoreClock/1);
  rcc_dev_clk_speed_table[RCC_APB2] = (SystemCoreClock/2);
  rcc_dev_clk_speed_table[RCC_APB1] = (SystemCoreClock/4);
}

void rcc_clk_init(rcc_sysclk_src sysclk_src,
                  rcc_pllsrc pll_src,
                  rcc_pll_multiplier pll_mul) {
  UNUSED(sysclk_src);
  UNUSED(pll_src);
  UNUSED(pll_mul);
  SetupClock();
}

#define PLL_M      8
#define PLL_N      240
/* SYSCLK = PLL_VCO / PLL_P */
#define PLL_P      2

/* USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLLQ */
#define PLL_Q      5


void rcc_clk_init2(rcc_sysclk_src sysclk_src,
                  rcc_pllsrc pll_src,
                  rcc_pll_multiplier pll_mul) {

/******************************************************************************/
/*            PLL (clocked by HSE) used as System clock source                */
/******************************************************************************/
  uint32 StartUpCounter = 0, HSEStatus = 0;
  RCC_TypeDef *pRCC = RCC;
  UNUSED(sysclk_src);
  UNUSED(pll_src);
  UNUSED(pll_mul);

  /* Enable HSE */
  pRCC->CR |= RCC_CR_HSEON;

  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = pRCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((pRCC->CR & RCC_CR_HSERDY) != 0)
  {
    HSEStatus = 0x01;
  }
  else
  {
    HSEStatus = 0x00;
  }

  if (HSEStatus == 0x01)
  {
    /* HCLK = SYSCLK / 1*/
    pRCC->CFGR |= RCC_CFGR_HPRE_DIV1;

    /* PCLK2 = HCLK / 2*/
    pRCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

    /* PCLK1 = HCLK / 4*/
    pRCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

    /* Configure the main PLL */
    pRCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                   (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);

    /* Enable the main PLL */
    pRCC->CR |= RCC_CR_PLLON;

    /* Wait till the main PLL is ready */
    while((pRCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

    /* Configure Flash prefetch, Instruction cache, Data cache and wait state */
    ((FLASH_TypeDef*)FLASH)->ACR = FLASH_ACR_PRFTEN |FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_3WS;

    /* Select the main PLL as system clock source */
    pRCC->CFGR &= ~RCC_CFGR_SW;
    pRCC->CFGR |= RCC_CFGR_SW_PLL;

    /* Wait till the main PLL is used as system clock source */
    while ((pRCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }

#if 0
    uint32 cfgr = 0;
    uint32 cr;

    /* Assume that we're going to clock the chip off the PLL, fed by
     * the HSE */
    ASSERT(sysclk_src == RCC_CLKSRC_PLL &&
           pll_src    == RCC_PLLSRC_HSE);

    RCC_BASE->CFGR = pll_src | pll_mul;

    /* Turn on the HSE */
    cr = RCC_BASE->CR;
    cr |= RCC_CR_HSEON;
    RCC_BASE->CR = cr;
    while (!(RCC_BASE->CR & RCC_CR_HSERDY))
        ;

    /* Now the PLL */
    cr |= RCC_CR_PLLON;
    RCC_BASE->CR = cr;
    while (!(RCC_BASE->CR & RCC_CR_PLLRDY))
        ;

    /* Finally, let's switch over to the PLL */
    cfgr &= ~RCC_CFGR_SW;
    cfgr |= RCC_CFGR_SW_PLL;
    RCC_BASE->CFGR = cfgr;
    while ((RCC_BASE->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        ;
#endif
}

/**
 * @brief Turn on the clock line on a peripheral
 * @param id Clock ID of the peripheral to turn on.
 */
void rcc_clk_enable(rcc_clk_id id) {
    static const __io uint32* enable_regs[] = {
        [APB1] = (uint32*)&RCC->APB1ENR,
        [APB2] = (uint32*)&RCC->APB2ENR,
        [AHB1] = (uint32*)&RCC->AHB1ENR,
        [AHB2] = (uint32*)&RCC->AHB2ENR,
        [AHB3] = (uint32*)&RCC->AHB3ENR,
    };

    rcc_clk_domain clk_domain = rcc_dev_clk(id);
    __io uint32* enr = (__io uint32*)enable_regs[clk_domain];
    uint8 lnum = rcc_dev_table[id].line_num;

    bb_peri_set_bit(enr, lnum, 1);
}

/**
 * @brief Turn on the clock line on a peripheral
 * @param id Clock ID of the peripheral to turn on.
 */
void rcc_clk_disable(rcc_clk_id id) {
    static const __io uint32* enable_regs[] = {
        [APB1] = (uint32*)&RCC->APB1ENR,
        [APB2] = (uint32*)&RCC->APB2ENR,
        [AHB1] = (uint32*)&RCC->AHB1ENR,
        [AHB2] = (uint32*)&RCC->AHB2ENR,
        [AHB3] = (uint32*)&RCC->AHB3ENR,
    };

    rcc_clk_domain clk_domain = rcc_dev_clk(id);
    __io uint32* enr = (__io uint32*)enable_regs[clk_domain];
    uint8 lnum = rcc_dev_table[id].line_num;

    bb_peri_set_bit(enr, lnum, 0);
}

/**
 * @brief Reset a peripheral.
 * @param id Clock ID of the peripheral to reset.
 */
void rcc_reset_dev(rcc_clk_id id) {
    static const __io uint32* reset_regs[] = {
        [APB1] = (uint32*)&RCC->APB1RSTR,
        [APB2] = (uint32*)&RCC->APB2RSTR,
        [AHB1] = (uint32*)&RCC->AHB1RSTR,
        [AHB2] = (uint32*)&RCC->AHB2RSTR,
        [AHB3] = (uint32*)&RCC->AHB3RSTR,
    };

    rcc_clk_domain clk_domain = rcc_dev_clk(id);
    __io void* addr = (__io void*)reset_regs[clk_domain];
    uint8 lnum = rcc_dev_table[id].line_num;

    bb_peri_set_bit(addr, lnum, 1);
    bb_peri_set_bit(addr, lnum, 0);
}

/**
 * @brief Get a peripheral's clock domain
 * @param id Clock ID of the peripheral whose clock domain to return
 * @return Clock source for the given clock ID
 */
rcc_clk_domain rcc_dev_clk(rcc_clk_id id) {
    return rcc_dev_table[id].clk_domain;
}

/**
 * @brief Get a peripheral's clock domain speed
 * @param id Clock ID of the peripheral whose clock domain speed to return
 * @return Clock speed for the given clock ID
 */
uint32 rcc_dev_clk_speed(rcc_clk_id id) {
    return rcc_dev_clk_speed_table[rcc_dev_clk(id)];
}

/**
 * @brief Get a peripheral's timer clock domain speed
 * @param id Clock ID of the peripheral whose clock domain speed to return
 * @return Clock speed for the given clock ID
 */
uint32 rcc_dev_timer_clk_speed(rcc_clk_id id) {
    return 2*rcc_dev_clk_speed(id);
}

/**
 * @brief Set the divider on a peripheral prescaler
 * @param prescaler prescaler to set
 * @param divider prescaler divider
 */
void rcc_set_prescaler(rcc_prescaler prescaler, uint32 divider) {
#if 0
    static const uint32 masks[] = {
        [RCC_PRESCALER_AHB] = RCC_CFGR_HPRE,
        [RCC_PRESCALER_APB1] = RCC_CFGR_PPRE1,
        [RCC_PRESCALER_APB2] = RCC_CFGR_PPRE2,
        [RCC_PRESCALER_USB] = RCC_CFGR_USBPRE,
        [RCC_PRESCALER_ADC] = RCC_CFGR_ADCPRE,
    };

    uint32 cfgr = RCC->CFGR;
    cfgr &= ~masks[prescaler];
    cfgr |= divider;
    RCC->CFGR = cfgr;
#else
  UNUSED(prescaler);
  UNUSED(divider);
#endif
}
