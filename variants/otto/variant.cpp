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
 * @file   discovery_f4.cpp
 * @author ala42
 * @brief  discovery_f4 board file.
 */

 /*
 * Arduino srl
 * Firmware and Library Development Team
 *
 * Francesco Alessi (alfran) - francesco@arduino.org
 * 2016 Jun 9: Edited for Arduino STAR OTTO first release
 * 2016 Jul 21: Renamed and reorganized Pin info structure
 * 2016 Dec 20: Modified for HW rev 3
 */

#include "variant.h"
#include "gpio.h"
#include "rcc.h"
#include "timer.h"
#include "wiring_types.h"

extern const stm32_pin_info PIN_MAP[GPIO_PINS] = {

//   GPIO   BIT   TIMER   TIM_CH   AF    ADC   ADC_CH
// D0...D13                                                NAME               - IRQ   - TIMER                           -  ADC          - ALTERNATE             -
    {GPIOA_dev,  1,   TIMER5,   2,      2,   NULL,      ADCx}, // PA1:  D00            -       - TIM2_CH2/TIM5_CH2               -  ADC123_IN1   - UART4_RX (Serial0)    -
    {GPIOA_dev,  0,   TIMER5,   1,      2,   NULL,      ADCx}, // PA0:  D01            -       - TIM2_CH1/TIM5_CH1               -  ADC123_IN0   - UART4_TX (Serial0)    -
    {GPIOH_dev,  6,   TIMER12,  1,      9,   NULL,      ADCx}, // PH6:  D02            -       - TIM12_CH1                       -               -
    {GPIOB_dev, 15,   TIMER12,  2,      9,   NULL,      ADCx}, // PB15: D03            -       - TIM1_CH3N/TIM8_CH3N/TIM12_CH2   -               -
    {GPIOC_dev,  7,   TIMER8,   2,      3,   NULL,      ADCx}, // PC7:  D04            -       - TIM3_CH2/TIM8_CH2               -               -
    {GPIOC_dev,  6,   TIMER8,   1,      3,   NULL,      ADCx}, // PC6:  D05            -       - TIM3_CH1/TIM8_CH1               -               -
    {GPIOD_dev, 13,   TIMER4,   2,      2,   NULL,      ADCx}, // PD13: D06            -       - TIM4_CH2                        -               -
    {GPIOD_dev, 12,   TIMER4,   1,      2,   NULL,      ADCx}, // PD12: D07            -       - TIM4_CH1                        -               -
    {GPIOA_dev,  8,   TIMER1,   1,      1,   NULL,      ADCx}, // PA8:  D08            -       - TIM1_CH1                        -               -
    {GPIOA_dev,  9,   TIMER1,   2,      1,   NULL,      ADCx}, // PA9:  D09            -       - TIM1_CH2                        -               -
    {GPIOA_dev, 15,   TIMER2,   1,      1,   NULL,      ADCx}, // PA15: D10            -       - TIM2_CH1                        -               - SPI1_NSS
    {GPIOB_dev,  5,   TIMER3,   2,      2,   NULL,      ADCx}, // PB5:  D11            -       - TIM3_CH2                        -               - SPI1_MOSI
    {GPIOB_dev,  4,   TIMER3,   1,      2,   NULL,      ADCx}, // PB4:  D12            -       - TIM3_CH1                        -               - SPI1_MISO
    {GPIOB_dev,  3,   TIMER2,   2,      1,   NULL,      ADCx}, // PB3:  D13            -       - TIM2_CH2                        -               - SPI1_SCK
// D14...D21
    {GPIOG_dev, 14,   NULL,     0,    AFx,   NULL,      ADCx}, // PG14: D14            -       -                                 -               - USART6_TX (Serial3)   -
    {GPIOG_dev,  9,   NULL,     0,    AFx,   NULL,      ADCx}, // PG9:  D15            -       -                                 -               - USART6_RX (Serial3)   -
    {GPIOD_dev,  5,   NULL,     0,    AFx,   NULL,      ADCx}, // PD5:  D16            -       -                                 -               - USART2_TX (Serial2)   -
    {GPIOD_dev,  6,   NULL,     0,    AFx,   NULL,      ADCx}, // PD6:  D17            -       -                                 -               - USART2_RX (Serial2)   -
    {GPIOB_dev, 10,   TIMER2,   3,      1,   NULL,      ADCx}, // PB10: D18            -       - TIM2_CH3                        -               - USART3_TX (Serial1)   -
    {GPIOB_dev, 11,   TIMER2,   4,      1,   NULL,      ADCx}, // PB11: D19            -       - TIM2_CH4                        -               - USART3_RX (Serial1)   -
    {GPIOH_dev,  5,   NULL,     0,    AFx,   NULL,      ADCx}, // PH5:  D20            -       -                                 -               - I2C2_SDA              -
    {GPIOH_dev,  4,   NULL,     0,    AFx,   NULL,      ADCx}, // PH4:  D21            -       -                                 -               - I2C2_SCL              -
// D22...D53
    {GPIOJ_dev,  3,   NULL,     0,    AFx,   NULL,      ADCx}, // PE5:  D22            -       -                                 -               -
    {GPIOG_dev, 11,   NULL,     0,    AFx,   NULL,      ADCx}, // PE6:  D23            -       -                                 -               -
    {GPIOE_dev,  2,   NULL,     0,    AFx,   NULL,      ADCx}, // PE2:  D24            -       -                                 -               -
    {GPIOE_dev,  4,   NULL,     0,    AFx,   NULL,      ADCx}, // PE4:  D25            -       -                                 -               -
    {GPIOI_dev,  8,   NULL,     0,    AFx,   NULL,      ADCx}, // PI8:  D26            -       -                                 -               -
    {GPIOC_dev, 13,   NULL,     0,    AFx,   NULL,      ADCx}, // PC13: D27            -       -                                 -               -
    {GPIOI_dev, 11,   NULL,     0,    AFx,   NULL,      ADCx}, // PI11: D28            -       -                                 -               -
    {GPIOI_dev, 12,   NULL,     0,    AFx,   NULL,      ADCx}, // PI12: D29            -       -                                 -               -
    {GPIOI_dev, 13,   NULL,     0,    AFx,   NULL,      ADCx}, // PI13: D30            -       -                                 -               -
    {GPIOI_dev, 14,   NULL,     0,    AFx,   NULL,      ADCx}, // PI14: D31            -       -                                 -               -
    {GPIOI_dev, 15,   NULL,     0,    AFx,   NULL,      ADCx}, // PI15: D32            -       -                                 -               -
    {GPIOJ_dev,  0,   NULL,     0,    AFx,   NULL,      ADCx}, // PJ0:  D33            -       -                                 -               -
    {GPIOJ_dev,  1,   NULL,     0,    AFx,   NULL,      ADCx}, // PJ1:  D34            -       -                                 -               -
    {GPIOI_dev, 10,   NULL,     0,    AFx,   NULL,      ADCx}, // PI10: D35            -       -                                 -               -
    {GPIOK_dev,  3,   NULL,     0,    AFx,   NULL,      ADCx}, // PK3:  D36            -       -                                 -               -
    {GPIOJ_dev,  4,   NULL,     0,    AFx,   NULL,      ADCx}, // PJ4:  D37            -       -                                 -               -
    {GPIOK_dev,  5,   NULL,     0,    AFx,   NULL,      ADCx}, // PK5:  D38            -       -                                 -               -
    {GPIOJ_dev,  5,   NULL,     0,    AFx,   NULL,      ADCx}, // PJ5:  D39            -       -                                 -               -
    {GPIOD_dev, 11,   NULL,     0,    AFx,   NULL,      ADCx}, // PD11: D40            -       -                                 -               -
    {GPIOG_dev,  2,   NULL,     0,    AFx,   NULL,      ADCx}, // PG2:  D41            -       -                                 -               -
    {GPIOG_dev,  3,   NULL,     0,    AFx,   NULL,      ADCx}, // PG3:  D42            -       -                                 -               -
    {GPIOG_dev,  6,   NULL,     0,    AFx,   NULL,      ADCx}, // PG6:  D43            -       -                                 -               -
    {GPIOG_dev,  7,   NULL,     0,    AFx,   NULL,      ADCx}, // PG7:  D44            -       -                                 -               -
    {GPIOD_dev,  4,   NULL,     0,    AFx,   NULL,      ADCx}, // PD4:  D45            -       -                                 -               -
    {GPIOJ_dev, 12,   NULL,     0,    AFx,   NULL,      ADCx}, // PJ12: D46            -       -                                 -               -
    {GPIOJ_dev, 13,   NULL,     0,    AFx,   NULL,      ADCx}, // PJ13: D47            -       -                                 -               -
    {GPIOJ_dev, 14,   NULL,     0,    AFx,   NULL,      ADCx}, // PJ14: D48            -       -                                 -               -
    {GPIOJ_dev, 15,   NULL,     0,    AFx,   NULL,      ADCx}, // PJ15: D49            -       -                                 -               -
    {GPIOG_dev, 12,   NULL,     0,    AFx,   NULL,      ADCx}, // PG12: D50            -       -                                 -               -
    {GPIOB_dev, 13,   TIMER1,   5,      1,   NULL,      ADCx}, // PB13: D51            -       - TIM1_CH1N                       -               -
    {GPIOG_dev, 13,   NULL,     0,    AFx,   NULL,      ADCx}, // PG13: D52            -       -                                 -               -
    {GPIOB_dev, 12,   NULL,     0,    AFx,   NULL,      ADCx}, // PB12: D53            -       -                                 -               -
// A0...A11 (D54...D65)
    {GPIOB_dev,  0,   TIMER3,   3,      2,   ADC1_dev,     8}, // PB0:  D54 / A0       - INT   - TIM1_CH2N/TIM3_CH3/TIM8_CH2N    - ADC12_IN8     -
    {GPIOB_dev,  1,   TIMER3,   4,      2,   ADC1_dev,     9}, // PB1:  D55 / A1       - INT   - TIM1_CH3N/TIM3_CH4/TIM8_CH3N    - ADC12_IN9     -
    {GPIOF_dev,  6,   TIMER10,  1,      3,   ADC3_dev,     4}, // PF6:  D56 / A2       - INT   - TIM10_CH1                       - ADC3_IN4      -
    {GPIOC_dev,  5,   NULL,     0,    AFx,   ADC1_dev,    15}, // PC5:  D57 / A3       - INT   -                                 - ADC12_IN15    -
    {GPIOA_dev,  3,   TIMER5,   4,      2,   ADC3_dev,     3}, // PA3:  D58 / A4       -       - TIM2_CH4/TIM5_CH4/TIM9_CH2      - ADC123_IN3    -
    {GPIOA_dev,  2,   TIMER5,   3,      2,   ADC2_dev,     2}, // PA2:  D59 / A5       - INT   - TIM2_CH3/TIM5_CH3/TIM9_CH1      - ADC123_IN1    -
    {GPIOF_dev, 10,   NULL,     0,    AFx,   ADC3_dev,     8}, // PF10: D60 / A6       - INT   -                                 - ADC3_IN8      -
    {GPIOA_dev,  7,   NULL,     0,    AFx,   ADC1_dev,     7}, // PA7:  D61 / A7       - INT   - TIM1_CH1N/TIM3_CH1/TIM8_CH1N    - ADC12_IN      -
    {GPIOC_dev,  2,   NULL,     0,    AFx,   ADC2_dev,    12}, // PC2:  D62 / A8       - INT   -                                 - ADC123_IN12   -
    {GPIOC_dev,  4,   NULL,     0,    AFx,   ADC1_dev,    14}, // PC4:  D63 / A9       -       -                                 - ADC12_IN14    -
    {GPIOF_dev,  7,   TIMER11,  1,      3,   ADC3_dev,     5}, // PF7:  D64 / A10      -       - TIM11_CH1                       - ADC3_IN5      -
    {GPIOC_dev,  1,   NULL,     0,    AFx,   ADC3_dev,    11}, // PC1:  D65 / A11      -       -                                 - ADC123_IN11   -
// DAC0 - DAC1 (D66 - D67)
    {GPIOA_dev,  4,   NULL,     0,    AFx,   ADC2_dev,     4}, // PA4:  D66 / A12      - INT   -                                 - ADC12_IN4     - DAC_OUT1
    {GPIOA_dev,  5,   TIMER8,   5,      3,   ADC2_dev,     5}, // PA5:  D67 / A13      - INT   - TIM2_CH1/TIM8_CH1N              - ADC12_IN5     - DAC_OUT2
// CANRX - CANTX (D68 - D69)
    {GPIOB_dev,  9,   TIMER4,   4,      2,   NULL,      ADCx}, // PB9:  D68            - INT   - TIM4_CH4/TIM11_CH1              -               -
    {GPIOB_dev,  8,   TIMER4,   3,      2,   NULL,      ADCx}, // PB8:  D69            - INT   - TIM4_CH3/TIM10_CH1              -               -
// I2CB - (D70 - D71)
    {GPIOB_dev,  7,   TIMER4,   2,      2,   NULL,      ADCx}, // PB7:  D70            -       - TIM4_CH2                        -               - I2C1_SDA
    {GPIOB_dev,  6,   TIMER4,   1,      2,   NULL,      ADCx}, // PB6:  D71            -       - TIM4_CH1                        -               - I2C1_SCL
// SPI - (D72 - D74)
    {GPIOB_dev, 14,   NULL,     0,    AFx,   NULL,      ADCx}, // PB14: D72 / MISO     -       -                                 -               - SPI2_MISO
    {GPIOD_dev,  3,   NULL,     0,    AFx,   NULL,      ADCx}, // PD3:  D73 / SCK      -       -                                 -               - SPI2_SCK
    {GPIOC_dev,  3,   NULL,     0,    AFx,   NULL,      ADCx}, // PC3:  D74 / MOSI     -       -                                 -               - SPI2_MOSI
// ESP8266 POWER (D75)
    {GPIOH_dev, 13,   NULL,     0,    AFx,   NULL,      ADCx}, // PH13: D75 / WIFI_PWR -       -                                 -               -
// USB POWER ENABLE (D76)
    {GPIOK_dev,  4,   NULL,     0,    AFx,   NULL,      ADCx}, // PK4:  D76 / USB_PWR  -       -                                 -               -
// LCD BACK LIGHT CONTROL (D77)
    {GPIOJ_dev,  3,   NULL,     0,    AFx,   NULL,      ADCx}, // PJ3:  D77 / LCD_BL   -       -                                 -               -
// AUDIO SELECTION PIN (D78)
    {GPIOD_dev,  7,   NULL,     0,    AFx,   NULL,      ADCx}, // PD7:  D78 / AUDIO_SEL-       -                                 -               -
};

extern const uint8 boardPWMPins[BOARD_NR_PWM_PINS] __FLASH__ = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 18, 19, 51, 54, 55, 56, 58, 59, 64, 67, 68, 69
};

extern const uint8 boardADCPins[BOARD_NR_ADC_PINS] __FLASH__ = {
    54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67
};
