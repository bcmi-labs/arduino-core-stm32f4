#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifndef _OTTO_H_
#define _OTTO_H_


#define digitalPinToPort(P)        ( PIN_MAP[P].gpio_device )
#define digitalPinToBitMask(P)     ( BIT(PIN_MAP[P].gpio_bit) )
#define portOutputRegister(port)   ( &(port->regs->ODR) )
#define portInputRegister(port)    ( &(port->regs->IDR) )

#define portSetRegister(pin)		( &(PIN_MAP[pin].gpio_device->regs->BSRR) )
#define portClearRegister(pin)		( &(PIN_MAP[pin].gpio_device->regs->BRR) )

#define portConfigRegister(pin)		( &(PIN_MAP[pin].gpio_device->regs->CRL) )

#include "stm32f4xx_hal.h"

#define Port2Pin(port, bit) ((port-'A')*16+bit)

#define CYCLES_PER_MICROSECOND  180

#undef  STM32_PCLK1
#undef  STM32_PCLK2
#define STM32_PCLK1   (CYCLES_PER_MICROSECOND*1000000/4)
#define STM32_PCLK2   (CYCLES_PER_MICROSECOND*1000000/2)

#define SYSTICK_RELOAD_VAL      (CYCLES_PER_MICROSECOND*1000-1)

// PINs definition

// USART1 - NOT USED
#define USART1_TX_GPIO_DEV	GPIOB_dev
#define USART1_TX_GPIO_PIN 	6
#define USART1_TX_AF		7
#define USART1_RX_GPIO_DEV 	GPIOB_dev
#define USART1_RX_GPIO_PIN 	7
#define USART1_RX_AF		7

// USART2 - Serial2
#define USART2_TX_GPIO_DEV	GPIOD_dev
#define USART2_TX_GPIO_PIN 	5
#define USART2_TX_AF		7
#define USART2_RX_GPIO_DEV 	GPIOD_dev
#define USART2_RX_GPIO_PIN 	6
#define USART2_RX_AF		7

// USART3 - Serial1 / SerialESP
#define USART3_TX_GPIO_DEV	GPIOB_dev
#define USART3_TX_GPIO_PIN 	10
#define USART3_TX_AF		7
#define USART3_RX_GPIO_DEV 	GPIOB_dev
#define USART3_RX_GPIO_PIN 	11
#define USART3_RX_AF		7

// UART4 - Serial0
#define UART4_TX_GPIO_DEV	GPIOA_dev
#define UART4_TX_GPIO_PIN 	0
#define UART4_TX_AF			8
#define UART4_RX_GPIO_DEV 	GPIOA_dev
#define UART4_RX_GPIO_PIN 	1
#define UART4_RX_AF			8

// UART5 - NOT USED
#define UART5_TX_GPIO_DEV	GPIOD_dev
#define UART5_TX_GPIO_PIN 	2
#define UART5_TX_AF			8
#define UART5_RX_GPIO_DEV 	GPIOC_dev
#define UART5_RX_GPIO_PIN 	12
#define UART5_RX_AF			8

// USART6 - Serial3
#define USART6_TX_GPIO_DEV	GPIOG_dev
#define USART6_TX_GPIO_PIN 	14
#define USART6_TX_AF		8
#define USART6_RX_GPIO_DEV 	GPIOG_dev
#define USART6_RX_GPIO_PIN 	9
#define USART6_RX_AF		8

// UART7 - NOT USED
#define UART7_TX_GPIO_DEV	GPIOF_dev
#define UART7_TX_GPIO_PIN 	7
#define UART7_TX_AF			8
#define UART7_RX_GPIO_DEV 	GPIOF_dev
#define UART7_RX_GPIO_PIN 	6
#define UART7_RX_AF			8

// UART8 - NOT USED
#define UART8_TX_GPIO_DEV	GPIOE_dev
#define UART8_TX_GPIO_PIN 	0
#define UART8_TX_AF			8
#define UART8_RX_GPIO_DEV 	GPIOE_dev
#define UART8_RX_GPIO_PIN 	1
#define UART8_RX_AF			8

#define GPIO_PINS      		165
#define BOARD_NR_PWM_PINS   26
#define BOARD_NR_ADC_PINS   14
#define BOARD_NR_USED_PINS  80

// Analog PIN Definition
#define A0 			D54
#define A1			D55
#define A2			D56
#define A3			D57
#define A4			D58
#define A5			D59
#define A6			D60
#define A7			D61
#define A8			D62
#define A9			D63
#define A10			D64
#define A11			D65
#define A12			D66
#define A13			D67

// DAC PIN Definition
#define DAC0 		D66
#define DAC1 		D67

// LEDs PIN Definition
#define LED_L		D13
#define LED_BUILTIN D13

// CAN PIN
#define CANRX		D68
#define CANTX		D69
// #define CANRX1	D
// #define CANTX1	D

// SPI PIN
#define MISO 		D72
#define SCK 		D73
#define MOSI 		D74
#define SS    		D23
#define MISO1 		D12
#define SCK1  		D13
#define MOSI1 		D11
#define SS1   		D10

// I2C PIN
#define SCL 		D70
#define SDA 		D71
#define SDA1		D20
#define SCL1 		D21

// SERIAL PORT PIN
#define RX 			D0
#define TX 			D1
#define RX1 		D19
#define TX1 		D18
#define RX2 		D17
#define TX2 		D16
#define RX3 		D15
#define TX3 		D14

// WIFI POWER PIN
#define WIFI_PWR	D75

// USB POWER PIN
#define USB_PWR		D76

// LCD CONTROL
#define LCD_BL   	D77

// MIC SEL
#define MIC_SEL  	D78
#define CODEC     	0
#define MCU       	1

#endif
#endif
