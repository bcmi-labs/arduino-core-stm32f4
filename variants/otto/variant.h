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

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "Arduino.h"

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

/**
 * Libc porting layers
 */
#if defined (  __GNUC__  ) /* GCC CS3 */
#    include <syscalls.h> /** RedHat Newlib minimal stub */
#endif

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/
#include "PeripheralPins.h"

extern const PinName digital_arduino[];

enum {
  D0,  D1,  D2,  D3,  D4,  D5,  D6,  D7,  D8,  D9,
  D10, D11, D12, D13, D14, D15, D16, D17, D18, D19,
  D20, D21, D22, D23, D24, D25, D26, D27, D28, D29,
  D30, D31, D32, D33, D34, D35, D36, D37, D38, D39,
  D40, D41, D42, D43, D44, D45, D46, D47, D48, D49,
  D50, D51, D52, D53, D54, D55, D56, D57, D58, D59,
  D60, D61, D62, D63, D64, D65, D66, D67, D68, D69,
  D70, D71, D72, D73, D74, D75, D76, D77, D78, D79,
  D80,
  DEND
};

enum {
  A_START_AFTER = D53,
  A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9,
  A10, A11, A12, A13,
  AEND
};

#define MAX_ANALOG_IOS          (sizeof(PinMap_ADC)/sizeof(PinMap))
#define MAX_DIGITAL_IOS         DEND
#define NUM_DIGITAL_PINS        MAX_DIGITAL_IOS
#define NUM_ANALOG_INPUTS       (AEND - A0)

// Convert a digital pin number Dxx to a PinName Pxy
#define digitalToPinName(p)     ((p < NUM_DIGITAL_PINS) ? digital_arduino[p] : (STM_VALID_PINNAME(p))? (PinName)p : NC)
// Convert an analog pin number Axx to a PinName Pxy
#define analogToPinName(p)      (digitalToPinName(p))
// Convert an analog pin number to a digital pin number
#define analogToDigital(p)      (p)
// Convert a PinName Pxy to a pin number
uint32_t pinNametoPinNumber(PinName p);

#define digitalPinToPort(p)     ( get_GPIO_Port(digitalToPinName(p)) )
#define digitalPinToBitMask(p)  ( STM_GPIO_PIN(digitalToPinName(p)) )

//ADC resolution is 12bits
#define ADC_RESOLUTION          12
#define DACC_RESOLUTION         12

//PWR resolution
#define PWM_RESOLUTION          8
#define PWM_FREQUENCY           1000
#define PWM_MAX_DUTY_CYCLE      255

//On-board LED pin number
#define LED_BUILTIN             D13
#define LED_L                   LED_BUILTIN


//SPI definitions
//define 16 channels. As many channel as digital IOs
#define SPI_CHANNELS_NUM        16

//default chip salect pin
#define BOARD_SPI_DEFAULT_SS    D23

//In case SPI CS channel is not used we define a default one
#define BOARD_SPI_OWN_SS        SPI_CHANNELS_NUM

// SPI PIN
#define MISO                    D72
#define SCK                     D73
#define SCLK                    SCK
#define MOSI                    D74
#define SS                      D23
#define MISO1                   D12
#define SCK1                    D13
#define SCLK1                   SCK1
#define MOSI1                   D11
#define SS1                     D10

// DAC PIN Definition
#define DAC_0                   D66
#define DAC_1                   D67

// CAN PIN
#define CANRX                   D69
#define CANTX                   D68

// I2C PIN
#define SCL                     D71
#define SDA                     D70
#define SCL1                    D21
#define SDA1                    D20
#define SCL2                    D80
#define SDA2                    D79

//Timer Definitions
//Do not use timer used by PWM pins when possible. See PinMap_PWM.
#define TIMER_TONE              TIM2
#define TIMER_UART_EMULATED     TIM7

//Do not use basic timer: OC is required
#define TIMER_SERVO             TIM2  //TODO: advanced-control timers don't work

#define DEBUG_UART              ((USART_TypeDef *) USART6)

// SERIAL PORT PIN
#define RX                      D0
#define TX                      D1
#define RX1                     D19
#define TX1                     D18
#define RX2                     D17
#define TX2                     D16
#define RX3                     D15
#define TX3                     D14

// WIFI POWER PIN
#define WIFI_PWR                D75

// USB POWER PIN
#define USB_PWR                 D76

// LCD CONTROL
#define LCD_BL                  D77

// MIC SEL
#define MIC_SEL                 D78
#define CODEC                   0
#define MCU                     1

//Enable Firmata
#define STM32 1

#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern HardwareSerial Serial;
extern HardwareSerial Serial1;
extern HardwareSerial Serial2;
extern HardwareSerial Serial3;

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR   Serial3
#define SERIAL_PORT_HARDWARE  Serial3
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
