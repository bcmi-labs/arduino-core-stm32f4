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
 */

#ifdef BOARD_discovery_f4

#include "otto.h"

#include "gpio.h"
#include "rcc.h"
#include "timer.h"

#include "wiring_types.h"

void boardInit(void)
{

    // PWM output setting

    gpio_set_af_mode(GPIOA,  0, 2); // D00 - TIM5_CH1
    gpio_set_af_mode(GPIOA,  1, 2); // D01 - TIM5_CH2
    gpio_set_af_mode(GPIOH,  6, 9); // D02 - TIM12_CH1
    gpio_set_af_mode(GPIOB, 15, 9); // D03 - TIM12_CH2
    gpio_set_af_mode(GPIOC,  7, 3); // D04 - TIM8_CH2
    gpio_set_af_mode(GPIOC,  6, 3); // D05 - TIM8_CH1
    gpio_set_af_mode(GPIOD, 13, 2); // D06 - TIM4_CH2
    gpio_set_af_mode(GPIOD, 12, 2); // D07 - TIM4_CH1
    gpio_set_af_mode(GPIOB,  5, 2); // D08 - TIM3_CH2
    gpio_set_af_mode(GPIOB,  4, 2); // D09 - TIM3_CH1
    gpio_set_af_mode(GPIOB,  3, 1); // D10 - TIM2_CH2
    gpio_set_af_mode(GPIOA, 15, 1); // D11 - TIM2_CH1
    gpio_set_af_mode(GPIOA,  9, 1); // D12 - TIM1_CH2
    gpio_set_af_mode(GPIOA,  8, 1); // D13 - TIM1_CH1

    gpio_set_af_mode(GPIOB, 11, 1); // D18 - TIM2_CH4
    gpio_set_af_mode(GPIOB, 10, 1); // D19 - TIM2_CH3
    gpio_set_af_mode(GPIOE,  5, 3); // D22 - TIM9_CH1
    gpio_set_af_mode(GPIOE,  6, 3); // D23 - TIM9_CH2
    gpio_set_af_mode(GPIOB, 13, 1); // D51 - TIM1_CH1N

    gpio_set_af_mode(GPIOB,  0, 2); // D54 - TIM3_CH3
    gpio_set_af_mode(GPIOB,  1, 2); // D55 - TIM3_CH4
    gpio_set_af_mode(GPIOF,  6, 3); // D56 - TIM10_CH1
    gpio_set_af_mode(GPIOF,  7, 3); // D57 - TIM11_CH1
    gpio_set_af_mode(GPIOA,  3, 2); // D58 - TIM5_CH4
    gpio_set_af_mode(GPIOA,  2, 2); // D59 - TIM5_CH3
    gpio_set_af_mode(GPIOA,  7, 3); // D65 - TIM8_CH1N

    gpio_set_af_mode(GPIOA,  5, 1); // D67 - TIM2_CH1

    gpio_set_af_mode(GPIOB,  8, 2); // D68 - TIM4_CH3
    gpio_set_af_mode(GPIOB,  9, 2); // D69 - TIM4_CH4

	return;
}

extern const stm32_pin_info PIN_MAP[GPIO_PINS] = {


//   GPIO   BIT  TIMER  TIM_CH  ADC  DC_CH
// D0...D13                                          NAME        - IRQ   - TIMER                           -  ADC          - ALTERNATE             -
    {GPIOA,  0, TIMER5,  1,    NULL, ADCx}, // PA0:  D00         -       - TIM2_CH1/TIM5_CH1               -  ADC123_IN0   - UART4_TX (Serial0)    - TX and RX pins are inverted in HW
    {GPIOA,  1, TIMER5,  2,    NULL, ADCx}, // PA1:  D01         -       - TIM2_CH2/TIM5_CH2               -  ADC123_IN1   - UART4_RX (Serial0)    - TX and RX pins are inverted in HW
    {GPIOH,  6, TIMER12, 1,    NULL, ADCx}, // PH6:  D02         -       - TIM12_CH1                       -               -
    {GPIOB, 15, TIMER12, 2,    NULL, ADCx}, // PB15: D03         -       - TIM1_CH3N/TIM8_CH3N/TIM12_CH2   -               -
    {GPIOC,  7, TIMER8,  2,    NULL, ADCx}, // PC7:  D04         -       - TIM3_CH2/TIM8_CH2               -               -
    {GPIOC,  6, TIMER8,  1,    NULL, ADCx}, // PC6:  D05         -       - TIM3_CH1/TIM8_CH1               -               -
    {GPIOD, 13, TIMER4,  2,    NULL, ADCx}, // PD13: D06         -       - TIM4_CH2                        -               -
    {GPIOD, 12, TIMER4,  1,    NULL, ADCx}, // PD12: D07         -       - TIM4_CH1                        -               -
    {GPIOB,  5, TIMER3,  2,    NULL, ADCx}, // PB5:  D08         -       - TIM3_CH2                        -               -
    {GPIOB,  4, TIMER3,  1,    NULL, ADCx}, // PB4:  D09         -       - TIM3_CH1                        -               -
    {GPIOB,  3, TIMER2,  2,    NULL, ADCx}, // PB3:  D10         -       - TIM2_CH2                        -               -
    {GPIOA, 15, TIMER2,  1,    NULL, ADCx}, // PA15: D11         -       - TIM2_CH1                        -               -
    {GPIOA,  9, TIMER1,  2,    NULL, ADCx}, // PA9:  D12         -       - TIM1_CH2                        -               -
    {GPIOA,  8, TIMER1,  1,    NULL, ADCx}, // PA8:  D13         -       - TIM1_CH1                        -               -
// D14...D21
    {GPIOG, 14, NULL,    0,    NULL, ADCx}, // PG14: D14         -       -                                 -               - USART6_TX (Serial3)   -
    {GPIOG,  9, NULL,    0,    NULL, ADCx}, // PG9:  D15         -       -                                 -               - USART6_RX (Serial3)   -
    {GPIOD,  5, NULL,    0,    NULL, ADCx}, // PD5:  D16         -       -                                 -               - USART2_TX (Serial2)   -
    {GPIOD,  6, NULL,    0,    NULL, ADCx}, // PD6:  D17         -       -                                 -               - USART2_RX (Serial2)   -
    {GPIOB, 10, TIMER2,  3,    NULL, ADCx}, // PB10: D18         -       - TIM2_CH3                        -               - USART3_TX (Serial3)   - TX and RX pins are inverted in HW
    {GPIOB, 11, TIMER2,  4,    NULL, ADCx}, // PB11: D19         -       - TIM2_CH4                        -               - USART3_RX (Serial3)   - TX and RX pins are inverted in HW
    {GPIOH,  5, NULL,    0,    NULL, ADCx}, // PH5:  D20         -       -                                 -               - I2C2_SDA              -
    {GPIOH,  4, NULL,    0,    NULL, ADCx}, // PH4:  D21         -       -                                 -               - I2C2_SCL              -
// D22...D53
    {GPIOE,  5, TIMER9,  1,    NULL, ADCx}, // PE5:  D22         -       - TIM9_CH1                        -               -
    {GPIOE,  6, TIMER9,  2,    NULL, ADCx}, // PE6:  D23         -       - TIM9_CH2                        -               -
    {GPIOE,  2, NULL,    0,    NULL, ADCx}, // PE2:  D24         -       -                                 -               -
    {GPIOE,  4, NULL,    0,    NULL, ADCx}, // PE4:  D25         -       -                                 -               -
    {GPIOI,  8, NULL,    0,    NULL, ADCx}, // PI8:  D26         -       -                                 -               -
    {GPIOC, 13, NULL,    0,    NULL, ADCx}, // PC13: D27         -       -                                 -               -
    {GPIOI, 11, NULL,    0,    NULL, ADCx}, // PI11: D28         -       -                                 -               -
    {GPIOI, 12, NULL,    0,    NULL, ADCx}, // PI12: D29         -       -                                 -               -
    {GPIOI, 13, NULL,    0,    NULL, ADCx}, // PI13: D30         -       -                                 -               -
    {GPIOI, 14, NULL,    0,    NULL, ADCx}, // PI14: D31         -       -                                 -               -
    {GPIOI, 15, NULL,    0,    NULL, ADCx}, // PI15: D32         -       -                                 -               -
    {GPIOJ,  0, NULL,    0,    NULL, ADCx}, // PJ0:  D33         -       -                                 -               -
    {GPIOJ,  1, NULL,    0,    NULL, ADCx}, // PJ1:  D34         -       -                                 -               -
    {GPIOI, 10, NULL,    0,    NULL, ADCx}, // PI10: D35         -       -                                 -               -
    {GPIOK,  3, NULL,    0,    NULL, ADCx}, // PK3:  D36         -       -                                 -               -
    {GPIOJ,  4, NULL,    0,    NULL, ADCx}, // PJ4:  D37         -       -                                 -               -
    {GPIOK,  5, NULL,    0,    NULL, ADCx}, // PK5:  D38         -       -                                 -               -
    {GPIOJ,  5, NULL,    0,    NULL, ADCx}, // PJ5:  D39         -       -                                 -               -
    {GPIOD, 11, NULL,    0,    NULL, ADCx}, // PD11: D40         -       -                                 -               -
    {GPIOG,  2, NULL,    0,    NULL, ADCx}, // PG2:  D41         -       -                                 -               -
    {GPIOG,  3, NULL,    0,    NULL, ADCx}, // PG3:  D42         -       -                                 -               -
    {GPIOG,  6, NULL,    0,    NULL, ADCx}, // PG6:  D43         -       -                                 -               -
    {GPIOG,  7, NULL,    0,    NULL, ADCx}, // PG7:  D44         -       -                                 -               -
    {GPIOD,  4, NULL,    0,    NULL, ADCx}, // PD4:  D45         -       -                                 -               -
    {GPIOJ, 12, NULL,    0,    NULL, ADCx}, // PJ12: D46         -       -                                 -               -
    {GPIOJ, 13, NULL,    0,    NULL, ADCx}, // PJ13: D47         -       -                                 -               -
    {GPIOJ, 14, NULL,    0,    NULL, ADCx}, // PJ14: D48         -       -                                 -               -
    {GPIOJ, 15, NULL,    0,    NULL, ADCx}, // PJ15: D49         -       -                                 -               -
    {GPIOG, 12, NULL,    0,    NULL, ADCx}, // PG12: D50         -       -                                 -               -
    {GPIOB, 13, TIMER1,  5,    NULL, ADCx}, // PB13: D51         -       - TIM1_CH1N                       -               -
    {GPIOG, 13, NULL,    0,    NULL, ADCx}, // PG13: D52         -       -                                 -               -
    {GPIOB, 12, NULL,    0,    NULL, ADCx}, // PB12: D53         -       -                                 -               -
// A0...A11 (D54...D65)
    {GPIOB,  0, TIMER3,  3,    ADC1,    8}, // PB0:  D54 / A0    - INT   - TIM1_CH2N/TIM3_CH3/TIM8_CH2N  - ADC12_IN8     -
    {GPIOB,  1, TIMER3,  4,    ADC1,    9}, // PB1:  D55 / A1    - LCD   - TIM1_CH3N/TIM3_CH4/TIM8_CH3N  - ADC12_IN9     -
    {GPIOF,  6, TIMER10, 1,    ADC3,    4}, // PF6:  D56 / A2    - INT   - TIM10_CH1                     - ADC3_IN4      -
    {GPIOF,  7, TIMER11, 1,    ADC3,    5}, // PF7:  D57 / A3    - INT   - TIM11_CH1                     - ADC3_IN5      -
    {GPIOA,  3, TIMER5,  4,    ADC3,    3}, // PA3:  D58 / A4    -       - TIM2_CH4/TIM5_CH4/TIM9_CH2    - ADC123_IN3    -
    {GPIOA,  2, TIMER5,  3,    ADC2,    2}, // PA2:  D59 / A5    - INT   - TIM2_CH3/TIM5_CH3/TIM9_CH1    - ADC123_IN1    -
    {GPIOF, 10, NULL,    0,    ADC3,    8}, // PF10: D60 / A6    - INT   -                               - ADC3_IN8      -
    {GPIOC,  1, NULL,    0,    ADC2,   11}, // PC1:  D61 / A7    - INT   -                               - ADC123_IN11   -
    {GPIOC,  2, NULL,    0,    ADC2,   12}, // PC2:  D62 / A8    - INT   -                               - ADC123_IN12   -
    {GPIOC,  4, NULL,    0,    ADC1,   14}, // PC4:  D63 / A9    -       -                               - ADC12_IN14    -
    {GPIOC,  5, NULL,    0,    ADC1,   15}, // PC5:  D64 / A10   -       -                               - ADC12_IN15    -
    {GPIOA,  7, TIMER8,  5,    ADC2,    7}, // PA7:  D65 / A11   -       - TIM1_CH1N/TIM3_CH2/TIM8_CH1N  - ADC12_IN7     -
// DAC0 - DAC1 (D66 - D67)
    {GPIOA,  4, NULL,    0,    ADC2,    4}, // PA4:  D66 / A12   - INT   -                               - ADC12_IN4     - DAC_OUT1
    {GPIOA,  5, NULL,    0,    ADC2,    5}, // PA5:  D67 / A13   - INT   - TIM2_CH1/TIM8_CH1N            - ADC12_IN5     - DAC_OUT2
// CANRX - CANTX (D68 - D69)
    {GPIOB,  8, TIMER4,  3,    NULL, ADCx}, // PB8:  D68         - INT   - TIM4_CH3/TIM10_CH1            -               -
    {GPIOB,  9, TIMER4,  4,    NULL, ADCx}, // PB9:  D69         - INT   - TIM4_CH4/TIM11_CH1            -               -
// SPI - (D70 - D72)
    {GPIOB, 14, NULL,    0,    NULL, ADCx}, // PB14: D70 / MISO  -       - TIM1_CH2N/TIM8_CH2N           -               -
    {GPIOD, 10, NULL,    0,    NULL, ADCx}, // PB10: D71 / SCK   -       - TIM2_CH3                      -               -
    {GPIOC, 15, NULL,    0,    NULL, ADCx}, // PB15: D72 / MOSI  -       - TIM1_CH3N/TIM8_CH3N           -               -
    // RESET
// I2C - (D73 - D74)
    {GPIOB,  7, TIMER4,  2,    NULL, ADCx}, // PB7:  D73         -       - TIM4_CH2                      -               -
    {GPIOB,  6, TIMER4,  1,    NULL, ADCx}, // PB6:  D74         -       - TIM4_CH1                      -               -
// DSI-TE - LCD-INT (D74 - D75)
    {GPIOJ,  2, NULL,    0,   NULL,  ADCx}, // PJ2:  D75         - INT   -                               -               -
    {GPIOJ,  5, NULL,    0,   NULL,  ADCx}, // PJ5:  D76         - INT   -                               -               -
// USBOTG POWER - UOTGID
    {GPIOK,  4, NULL,    0,   NULL,  ADCx}, // PK4:  D77 / UOTGPWR_PIN - USB POWER ENABLE
// ESP8266
    {GPIOG, 11, NULL,    0,   NULL,  ADCx}, // PG11: D78 / WIFIEN_PIN  - ESP8266 ENABLE
    {GPIOH, 13, NULL,    0,   NULL,  ADCx}, // PH13: D79 / WIFIPWR_PIN - ESP8266 POWER
// LCD
    {GPIOD,  7, NULL,    0,   NULL,  ADCx}, // PD7:  D80 / LCDBL_PIN   - LCD BACK LIGHT CONTROL
// CAMERA
    {GPIOJ,  3, NULL,    0,   NULL,  ADCx}, // PJ3:  D81 - CAMERA PLUG
};

extern const uint8 boardPWMPins[BOARD_NR_PWM_PINS] __FLASH__ = {
    3, 5, 6
};

extern const uint8 boardADCPins[BOARD_NR_ADC_PINS] __FLASH__ = {
    16, 17, 18, 19, 20, 21
};

#endif
