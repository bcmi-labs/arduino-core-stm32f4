/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
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
 * @file   aeroquad32.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Private include file for Maple Native in boards.h
 *
 * See maple.h for more information on these definitions.
 */

 /*
 * 2016 May 31 first release for:
 * Adruino OTTO serial ports interface definitions
 *
 * Arduino srl
 *
 * Francesco Alessi (alfran) - francesco@arduino.org
 */


#ifndef _BOARD_DISCOVERY_F4_H_
#define _BOARD_DISCOVERY_F4_H_

#define Port2Pin(port, bit) ((port-'A')*16+bit)

#define CYCLES_PER_MICROSECOND  180

#undef  STM32_PCLK1
#undef  STM32_PCLK2
#define STM32_PCLK1   (CYCLES_PER_MICROSECOND*1000000/4)
#define STM32_PCLK2   (CYCLES_PER_MICROSECOND*1000000/2)

#define SYSTICK_RELOAD_VAL      (CYCLES_PER_MICROSECOND*1000-1)

// PINs definition

// USART1 - NOT USED
#define USART1_TX_GPIO_DEV	GPIOB
#define USART1_TX_GPIO_PIN 	6
#define USART1_TX_AF		7
#define USART1_RX_GPIO_DEV 	GPIOB
#define USART1_RX_GPIO_PIN 	7
#define USART1_RX_AF		7

// USART2 - Serial2
#define USART2_TX_GPIO_DEV	GPIOD
#define USART2_TX_GPIO_PIN 	5
#define USART2_TX_AF		7
#define USART2_RX_GPIO_DEV 	GPIOD
#define USART2_RX_GPIO_PIN 	6
#define USART2_RX_AF		7

// USART3 - Serial1 / SerialESP
#define USART3_TX_GPIO_DEV	GPIOB
#define USART3_TX_GPIO_PIN 	10
#define USART3_TX_AF		7
#define USART3_RX_GPIO_DEV 	GPIOB
#define USART3_RX_GPIO_PIN 	11
#define USART3_RX_AF		7

// UART4 - Serial0
#define UART4_TX_GPIO_DEV	GPIOA
#define UART4_TX_GPIO_PIN 	0
#define UART4_TX_AF			8
#define UART4_RX_GPIO_DEV 	GPIOA
#define UART4_RX_GPIO_PIN 	1
#define UART4_RX_AF			8

// UART5 - NOT USED
#define UART5_TX_GPIO_DEV	GPIOD
#define UART5_TX_GPIO_PIN 	2
#define UART5_TX_AF			8
#define UART5_RX_GPIO_DEV 	GPIOC
#define UART5_RX_GPIO_PIN 	12
#define UART5_RX_AF			8

// USART6 - Serial3
#define USART6_TX_GPIO_DEV	GPIOG
#define USART6_TX_GPIO_PIN 	14
#define USART6_TX_AF		8
#define USART6_RX_GPIO_DEV 	GPIOG
#define USART6_RX_GPIO_PIN 	9
#define USART6_RX_AF		8

// UART7 - NOT USED
#define UART7_TX_GPIO_DEV	GPIOF
#define UART7_TX_GPIO_PIN 	7
#define UART7_TX_AF			8
#define UART7_RX_GPIO_DEV 	GPIOF
#define UART7_RX_GPIO_PIN 	6
#define UART7_RX_AF			8

// UART8 - NOT USED
#define UART8_TX_GPIO_DEV	GPIOE
#define UART8_TX_GPIO_PIN 	0
#define UART8_TX_AF			8
#define UART8_RX_GPIO_DEV 	GPIOE
#define UART8_RX_GPIO_PIN 	1
#define UART8_RX_AF			8

#define GPIO_PINS      165
#define BOARD_NR_PWM_PINS       26
#define BOARD_NR_ADC_PINS       14
#define BOARD_NR_USED_PINS      80

// Analog PIN Definition
#define A0 	D54
#define A1	D55
#define A2	D56
#define A3	D57
#define A4	D58
#define A5	D59
#define A6	D60
#define A7	D61
#define A8	D62
#define A9	D63
#define A10	D64
#define A11	D65
#define A12	D66
#define A13	D67

// DAC PIN Definition
#define DAC0 D66
#define DAC1 D67

// LEDs PIN Definition
#define LED_L		D13
#define LED_BUILTIN D13

// CAN PIN
#define CANRX_PIN	D68
#define CANTX_PIN	D69

// SPI PIN
#define MISO_PIN 	D72
#define SCK_PIN 	D73
#define MOSI_PIN 	D74

// I2C PIN
#define SCL_PIN 	D70
#define SDA_PIN 	D71
#define SDA1_PIN	D20
#define SCL1_PIN 	D21

// SERIAL PORT PIN
#define RX0_PIN 	D0
#define TX0_PIN 	D1
#define RX1_PIN 	D19
#define TX1_PIN 	D18
#define RX2_PIN 	D17
#define TX2_PIN 	D16
#define RX3_PIN 	D14
#define TX3_PIN 	D15

// WIFI POWER PIN
#define WIFI_PWR	D75

// USB POWER PIN
#define USB_PWR		D76

// LCD CONTROL
#define LCD_BL   	D77


enum {
PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,
PF0,PF1,PF2,PF3,PF4,PF5,PF6,PF7,PF8,PF9,PF10,PF11,PF12,PF13,PF14,PF15,
PG0,PG1,PG2,PG3,PG4,PG5,PG6,PG7,PG8,PG9,PG10,PG11,PG12,PG13,PG14,PG15,
PH0,PH1,PH2,PH3,PH4,PH5,PH6,PH7,PH8,PH9,PH10,PH11,PH12,PH13,PH14,PH15
// alfran --- begin
,
PI0,PI1,PI2,PI3,PI4,PI5,PI6,PI7,PI8,PI9,PI10,PI11,PI12,PI13,PI14,PI15,
PJ0,PJ1,PJ2,PJ3,PJ4,PJ5,PJ6,PJ7,PJ8,PJ9,PJ10,PJ11,PJ12,PJ13,PJ14,PJ15,
PK0,PK1,PK2,PK3,PK4,PK5,PK6,PK7,PK8,PK9,PK10,PK11,PK12,PK13,PK14,PK15,
// alfran --- end
};

/*
// alfran --- begin

enum {
PC7,PC6,PD13,PD12,PB12,PB7,PB11,PB13,PA3,PA6,PA15,PA7,PA9,PC8,PC10,
PC11,PD5,PD6,PC5,PC4,PH5,PH4,PJ1,PJ0,PI15,PI14,PI13,PI12,PI11,PI8,
PH7,PH6,PG14,PG13,PG12,PG11,PG10,PG9,PG7,PG6,PJ3,PG3,PE2,PE3,PE4,
PE5,PE6,PD7,PD11,PB4,PC13,PB5,PG2,PB6,PB0,PB1,PC0,PF6,PF7,PF8,
PF9,PF10,PC1,PC2,PC3,PA1,PA2,PA4,PA5,PB8,PB9,PB14,PB10,PB15,PA8,
PC9,PJ2,PJ5,PD3,PD4,PB2,PA10,PA0,

PA11,PA12,PA13,PA14,
PB3,
PC12,PC14,PC15,
PD0,PD1,PD2,PD8,PD9,PD10,PD14,PD15,
PE0,PE1,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,
PF0,PF1,PF2,PF3,PF4,PF5,PF11,PF12,PF13,PF14,PF15,
PG0,PG1,PG4,PG5,PG8,PG15,
PH0,PH1,PH2,PH3,PH8,PH9,PH10,PH11,PH12,PH13,PH14,PH15,
PI0,PI1,PI2,PI3,PI4,PI5,PI6,PI7,PI9,PI10,
PJ4,PJ6,PJ7,PJ8,PJ9,PJ10,PJ11,PJ12,PJ13,PJ14,PJ15,
PK0,PK1,PK2,PK3,PK4,PK5,PK6,PK7,PK8,PK9,PK10,PK11,PK12,PK13,PK14,PK15,
// alfran --- end
};
*/

#endif
