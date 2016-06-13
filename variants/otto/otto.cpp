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


//#if 0  
// defined in wiring_types.h                       
// typedef struct stm32_pin_info {
//     gpio_dev *gpio_device;      /**< Maple pin's GPIO device */
//     timer_dev *timer_device;    /**< Pin's timer device, if any. */
//     const adc_dev *adc_device;  /**< ADC device, if any. */
//     uint8 gpio_bit;             /**< Pin's GPIO port bit. */
//     uint8 timer_channel;        /**< Timer channel, or 0 if none. Complementary channels CH1N, CH2N, CH3N are mapped on 5..7 */
//     uint8 adc_channel;          /**< Pin ADC channel, or ADCx if none. */
// } stm32_pin_info;

//#endif

extern const stm32_pin_info PIN_MAP[GPIO_PINS] = {


//   GPIO     TIMER      ADC  PIN CH   ADC_CH
// D0...D13                                             NAME        - IRQ   - TIMER                           -  ADC          - ALTERNATE             -
    {GPIOA,  TIMER5,    NULL,   0,  1,  ADCx}, // PA0:  D00         -       - TIM2_CH1/TIM5_CH1               -  ADC123_IN0   - UART4_TX (Serial0)    - TX and RX pins are inverted in HW
    {GPIOA,  TIMER5,    NULL,   1,  2,  ADCx}, // PA1:  D01         -       - TIM2_CH2/TIM5_CH2               -  ADC123_IN1   - UART4_TX (Serial0)    - TX and RX pins are inverted in HW
    {GPIOH, TIMER12,    NULL,   6,  1,  ADCx}, // PH6:  D02         -       - TIM12_CH1                       -               -
    {GPIOB, TIMER12,    NULL,  15,  2,  ADCx}, // PB15: D03         -       - TIM1_CH3N/TIM8_CH3N/TIM12_CH2   -               -
    {GPIOC,  TIMER8,    NULL,   7,  2,  ADCx}, // PC7:  D04         -       - TIM3_CH2/TIM8_CH2               -               -
    {GPIOC,  TIMER8,    NULL,   6,  1,  ADCx}, // PC6:  D05         -       - TIM3_CH1/TIM8_CH1               -               -
    {GPIOD,  TIMER4,    NULL,  13,  2,  ADCx}, // PD13: D06         -       - TIM4_CH2                        -               -
    {GPIOD,  TIMER4,    NULL,  12,  1,  ADCx}, // PD12: D07         -       - TIM4_CH1                        -               -
    {GPIOB,  TIMER3,    NULL,   5,  2,  ADCx}, // PB5:  D08         -       - TIM3_CH2                        -               -
    {GPIOB,  TIMER3,    NULL,   4,  1,  ADCx}, // PB4:  D09         -       - TIM3_CH1                        -               -
    {GPIOB,  TIMER2,    NULL,   3,  2,  ADCx}, // PB3:  D10         -       - TIM2_CH2                        -               -
    {GPIOA,  TIMER2,    NULL,  15,  1,  ADCx}, // PA15: D11         -       - TIM2_CH1                        -               -
    {GPIOA,  TIMER1,    NULL,   9,  2,  ADCx}, // PA9:  D12         -       - TIM1_CH2                        -               -
    {GPIOA,  TIMER1,    NULL,   8,  1,  ADCx}, // PA8:  D13         -       - TIM1_CH1                        -               -
// D14...D21
    {GPIOG,    NULL,    NULL,  14,  0,  ADCx}, // PG14: D14         -       -                                 -               - USART6_TX (Serial3)   - 
    {GPIOG,    NULL,    NULL,   9,  0,  ADCx}, // PG9:  D15         -       -                                 -               - USART6_RX (Serial3)   -
    {GPIOD,    NULL,    NULL,   5,  0,  ADCx}, // PD5:  D16         -       -                                 -               - USART2_TX (Serial2)   -
    {GPIOD,    NULL,    NULL,   6,  0,  ADCx}, // PD6:  D17         -       -                                 -               - USART2_RX (Serial2)   -
    {GPIOB,  TIMER2,    NULL,  11,  4,  ADCx}, // PB11: D18         -       - TIM2_CH4                        -               - USART3_RX (Serial3)   - TX and RX pins are inverted in HW 
    {GPIOB,  TIMER2,    NULL,  10,  3,  ADCx}, // PB10: D19         -       - TIM2_CH3                        -               - USART3_RX (Serial3)   - TX and RX pins are inverted in HW
    {GPIOH,    NULL,    NULL,   5,  0,  ADCx}, // PH5:  D20         -       -                                 -               - I2C2_SDA      -
    {GPIOH,    NULL,    NULL,   4,  0,  ADCx}, // PH4:  D21         -       -                                 -               - I2C2_SCL      -
// D22...D53
    {GPIOE,  TIMER9,    NULL,   5,  1,  ADCx}, // PE5:  D22         -       - TIM9_CH1                        -               -
    {GPIOE,  TIMER9,    NULL,   6,  2,  ADCx}, // PE6:  D23         -       - TIM9_CH2                        -               -
    {GPIOE,    NULL,    NULL,   2,  0,  ADCx}, // PE2:  D24         -       -                                 -               -
    {GPIOE,    NULL,    NULL,   4,  0,  ADCx}, // PE4:  D25         -       -                                 -               -
    {GPIOI,    NULL,    NULL,   8,  0,  ADCx}, // PI8:  D26         -       -                                 -               -
    {GPIOC,    NULL,    NULL,  13,  0,  ADCx}, // PC13: D27         -       -                                 -               -
    {GPIOI,    NULL,    NULL,  11,  0,  ADCx}, // PI11: D28         -       -                                 -               -
    {GPIOI,    NULL,    NULL,  12,  0,  ADCx}, // PI12: D29         -       -                                 -               -
    {GPIOI,    NULL,    NULL,  13,  0,  ADCx}, // PI13: D30         -       -                                 -               -
    {GPIOI,    NULL,    NULL,  14,  0,  ADCx}, // PI14: D31         -       -                                 -               -
    {GPIOI,    NULL,    NULL,  15,  0,  ADCx}, // PI15: D32         -       -                                 -               -
    {GPIOJ,    NULL,    NULL,   0,  0,  ADCx}, // PJ0:  D33         -       -                                 -               -
    {GPIOJ,    NULL,    NULL,   1,  0,  ADCx}, // PJ1:  D34         -       -                                 -               -
    {GPIOI,    NULL,    NULL,  10,  0,  ADCx}, // PI10: D35         -       -                                 -               -
    {GPIOK,    NULL,    NULL,   3,  0,  ADCx}, // PK3:  D36         -       -                                 -               -
    {GPIOJ,    NULL,    NULL,   4,  0,  ADCx}, // PJ4:  D37         -       -                                 -               -
    {GPIOK,    NULL,    NULL,   5,  0,  ADCx}, // PK5:  D38         -       -                                 -               -
    {GPIOJ,    NULL,    NULL,   5,  0,  ADCx}, // PJ5:  D39         -       -                                 -               -
    {GPIOD,    NULL,    NULL,  11,  0,  ADCx}, // PD11: D40         -       -                                 -               -
    {GPIOG,    NULL,    NULL,   2,  0,  ADCx}, // PG2:  D41         -       -                                 -               -
    {GPIOG,    NULL,    NULL,   3,  0,  ADCx}, // PG3:  D42         -       -                                 -               -
    {GPIOG,    NULL,    NULL,   6,  0,  ADCx}, // PG6:  D43         -       -                                 -               -
    {GPIOG,    NULL,    NULL,   7,  0,  ADCx}, // PG7:  D44         -       -                                 -               -
    {GPIOD,    NULL,    NULL,   4,  0,  ADCx}, // PD4:  D45         -       -                                 -               -
    {GPIOJ,    NULL,    NULL,  12,  0,  ADCx}, // PJ12: D46         -       -                                 -               -
    {GPIOJ,    NULL,    NULL,  13,  0,  ADCx}, // PJ13: D47         -       -                                 -               -
    {GPIOJ,    NULL,    NULL,  14,  0,  ADCx}, // PJ14: D48         -       -                                 -               -
    {GPIOJ,    NULL,    NULL,  15,  0,  ADCx}, // PJ15: D49         -       -                                 -               -
    {GPIOG,    NULL,    NULL,  12,  0,  ADCx}, // PG12: D50         -       -                                 -               -
    {GPIOB,  TIMER1,    NULL,  13,  5,  ADCx}, // PB13: D51         -       - TIM1_CH1N                       -               -
    {GPIOG,    NULL,    NULL,  13,  0,  ADCx}, // PG13: D52         -       -                                 -               -
    {GPIOB,    NULL,    NULL,  12,  0,  ADCx}, // PB12: D53         -       -                                 -               -
// A0...A11 (D54...D65)
    {GPIOB,  TIMER3,    ADC1,   0,  3,     8}, // PB0:  D54 / A0    - INT   - TIM1_CH2N/TIM3_CH3/TIM8_CH2N  - ADC12_IN8     -
    {GPIOB,  TIMER3,    ADC1,   1,  4,     9}, // PB1:  D55 / A1    - LCD   - TIM1_CH3N/TIM3_CH4/TIM8_CH3N  - ADC12_IN9     -
    {GPIOF, TIMER10,    ADC3,   6,  1,     4}, // PF6:  D56 / A2    - INT   - TIM10_CH1                     - ADC3_IN4      -
    {GPIOF, TIMER11,    ADC3,   7,  1,     5}, // PF7:  D57 / A3    - INT   - TIM11_CH1                     - ADC3_IN5      -  
    {GPIOA,  TIMER5,    ADC3,   3,  4,     3}, // PA3:  D58 / A4    -       - TIM2_CH4/TIM5_CH4/TIM9_CH2    - ADC123_IN3    -
    {GPIOA,  TIMER5,    ADC2,   2,  3,     2}, // PA2:  D59 / A5    - INT   - TIM2_CH3/TIM5_CH3/TIM9_CH1    - ADC123_IN1    -
    {GPIOF,    NULL,    ADC3,  10,  0,     8}, // PF10: D60 / A6    - INT   -                               - ADC3_IN8      -
    {GPIOC,    NULL,    ADC2,   1,  0,    11}, // PC1:  D61 / A7    - INT   -                               - ADC123_IN11   -
    {GPIOC,    NULL,    ADC2,   2,  0,    12}, // PC2:  D62 / A8    - INT   -                               - ADC123_IN12   -
    {GPIOC,    NULL,    ADC1,   4,  0,    14}, // PC4:  D63 / A9    -       -                               - ADC12_IN14    -
    {GPIOC,    NULL,    ADC1,   5,  0,    15}, // PC5:  D64 / A10   -       -                               - ADC12_IN15    -
    {GPIOA,  TIMER8,    ADC2,   7,  5,     7}, // PA7:  D65 / A11   -       - TIM1_CH1N/TIM3_CH2/TIM8_CH1N  - ADC12_IN7     -
// DAC0 - DAC1 (D66 - D67)
    {GPIOA,    NULL,    ADC2,   4,  0,     4}, // PA4:  D66 / A12   - INT   -                               - ADC12_IN4     - DAC_OUT1
    {GPIOA,    NULL,    ADC2,   5,  0,     5}, // PA5:  D67 / A13   - INT   - TIM2_CH1/TIM8_CH1N            - ADC12_IN5     - DAC_OUT2 
// CANRX - CANTX (D68 - D69)
    {GPIOB,  TIMER4,    NULL,   8,  3,  ADCx}, // PB8:  D68         - INT   - TIM4_CH3/TIM10_CH1            -               -
    {GPIOB,  TIMER4,    NULL,   9,  4,  ADCx}, // PB9:  D69         - INT   - TIM4_CH4/TIM11_CH1            -               -
// SPI - (D70 - D72)     
    {GPIOB,    NULL,    NULL,  14,  0,  ADCx}, // PB14: D70 / MISO  -       - TIM1_CH2N/TIM8_CH2N           -               -
    {GPIOD,    NULL,    NULL,   3,  0,  ADCx}, // PB10: D71 / SCK   -       - TIM2_CH3                      -               -
    {GPIOC,    NULL,    NULL,   3,  0,  ADCx}, // PB15: D72 / MOSI  -       - TIM1_CH3N/TIM8_CH3N           -               -
    // RESET
// I2C - (D73 - D74)
    {GPIOB,  TIMER4,    NULL,   7,  2,  ADCx}, // PB7:  D73         -       - TIM4_CH2                      -               -
    {GPIOB,  TIMER4,    NULL,   6,  1,  ADCx}, // PB6:  D74         -       - TIM4_CH1                      -               -
// DSI-TE - LCD-INT (D74 - D75)
    {GPIOJ,    NULL,    NULL,   2,  0,  ADCx}, // PJ2:  D75         - INT   -                               -               -
    {GPIOJ,    NULL,    NULL,   5,  0,  ADCx}, // PJ5:  D76         - INT   -                               -               -
// USBOTG POWER - UOTGID
    {GPIOK,    NULL,    NULL,   4,  0,  ADCx}, // PK4:  D77 / UOTGPWR_PIN - USB POWER ENABLE
// ESP8266
    {GPIOG,    NULL,    NULL,  11,  0,  ADCx}, // PG11: D78 / WIFIEN_PIN  - ESP8266 ENABLE
    {GPIOH,    NULL,    NULL,  13,  0,  ADCx}, // PH13: D79 / WIFIPWR_PIN - ESP8266 POWER
// LCD
    {GPIOD,    NULL,    NULL,   7,  0,  ADCx}, // PD7:  D80 / LCDBL_PIN   - LCD BACK LIGHT CONTROL
// CAMERA
    {GPIOJ,    NULL,    NULL,   3,  0,  ADCx}, // PJ3:  D81 - CAMERA PLUG    
};

extern const uint8 boardPWMPins[BOARD_NR_PWM_PINS] __FLASH__ = {
    3, 5, 6
};

extern const uint8 boardADCPins[BOARD_NR_ADC_PINS] __FLASH__ = {
    16, 17, 18, 19, 20, 21
};

#endif
