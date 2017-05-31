/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digital_arduino[] = {
  PA1,  //D0
  PA0,  //D1
  PH6,  //D2
  PB15, //D3
  PC7,  //D4
  PC6,  //D5
  PD13, //D6
  PD12, //D7
  PA8,  //D8
  PA9,  //D9
  PA15, //D10
  PB5,  //D11
  PB4,  //D12
  PB3,  //D13
  PG14, //D14
  PG9,  //D15
  PD5,  //D16
  PD6,  //D17
  PB10, //D18
  PB11, //D19
  PH5,  //D20
  PH4,  //D21
  PJ3,  //D22
  PG11, //D23
  PE2,  //D24
  PE4,  //D25
  PI8,  //D26
  PC13, //D27
  PI11, //D28
  PI12, //D29
  PI13, //D30
  PI14, //D31
  PI15, //D32
  PJ0,  //D33
  PJ1,  //D34
  PI10, //D35
  PK3,  //D36
  PJ4,  //D37
  PK5,  //D38
  PJ5,  //D39
  PD11, //D40
  PG2,  //D41
  PG3,  //D42
  PG6,  //D43
  PG7,  //D44
  PD4,  //D45
  PJ12, //D46
  PJ13, //D47
  PJ14, //D48
  PJ15, //D49
  PG12, //D50
  PB13, //D51
  PG13, //D52
  PB12, //D53
  PB0,  //D54/A0
  PB1,  //D55/A1
  PF6,  //D56/A2
  PC5,  //D57/A3
  PA3,  //D58/A4
  PA2,  //D59/A5
  PF10, //D60/A6
  PA7,  //D61/A7
  PC2,  //D62/A8
  PC4,  //D63/A9
  PF7,  //D64/A10
  PC1,  //D65/A11
  PA4,  //D66/A12
  PA5,  //D67/A13
  PB9,  //D68
  PB8,  //D69
  PB7,  //D70
  PB6,  //D71
  PB14, //D72
  PD3,  //D73
  PC3,  //D74
  PH13, //D75
  PK4,  //D76
  PJ3,  //D77
  PD7,  //D78
  PH8,  //D79
  PH7,  //D80
};

#ifdef __cplusplus
}
#endif

/*
 * UART objects
 */
HardwareSerial  Serial(PA1, PA0);    // RX/TX
HardwareSerial  Serial1(PB11, PB10); // RX1/TX1
HardwareSerial  Serial2(PD6, PD5);   // RX2/TX2
HardwareSerial  Serial3(PG9, PG14);  // RX3/TX3

void serialEvent() __attribute__((weak));
void serialEvent() { }

void serialEvent1() __attribute__((weak));
void serialEvent1() { }

void serialEvent2() __attribute__((weak));
void serialEvent2() { }

void serialEvent3() __attribute__((weak));
void serialEvent3() { }

void serialEventRun(void)
{
  if (Serial.available()) serialEvent();
  if (Serial1.available()) serialEvent1();
  if (Serial2.available()) serialEvent2();
  if (Serial3.available()) serialEvent2();
}

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

void __libc_init_array(void);

uint32_t pinNametoPinNumber(PinName p)
{
  uint32_t i = 0;
  for(i = 0; i < NUM_DIGITAL_PINS; i++) {
	  if (digital_arduino[i] == p)
		  break;
  }
  return i;
}

void init( void )
{
  hw_config_init();
}

/**
  * @brief  System Clock Configuration
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
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
  RCC_OscInitStruct.PLL.PLLM = 4;
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

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#ifdef __cplusplus
}
#endif
