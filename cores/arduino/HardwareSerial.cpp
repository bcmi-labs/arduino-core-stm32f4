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
 * @file HardwareSerial.cpp
 * @brief Wirish serial port implementation.
 */

 /*
 * Arduino srl - www.arduino.org
 * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
 */

#include "memory.h"
#include "gpio.h"
#include "timer.h"

#include "HardwareSerial.h"
#include "boards.h"

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

HardwareSerial Serial0(UART4);
HardwareSerial Serial1(USART3);
HardwareSerial Serial2(USART2);
HardwareSerial Serial3(USART6);
HardwareSerial SerialESP(USART3);

HardwareSerial::HardwareSerial(usart_dev *usart_device)
{
    this->usart_device = usart_device;
}

void HardwareSerial::begin(uint32 baud)
{
    ASSERT(baud <= usart_device->max_baud);

    if (baud > usart_device->max_baud)
    {
        return;
    }

    if (usart_device == USART1) // Arduino OTTO not use this device
    {

        // USART 1 pin definition

        // USART1 TX
        gpio_set_mode(USART1_TX_GPIO_DEV, USART1_TX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(USART1_TX_GPIO_DEV, USART1_TX_GPIO_PIN, USART1_TX_AF);

        // USART1 RX
        gpio_set_mode(USART1_RX_GPIO_DEV, USART1_RX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(USART1_RX_GPIO_DEV, USART1_RX_GPIO_PIN, USART1_RX_AF);

        // enable USART1 clock
        *((uint32_t*)(RCC_APB2ENR)) |= (1 <<  RCC_APB2ENR_USART1EN_BIT);

    }

    else if (usart_device == USART2)
    {
        // USART 2 pin definition

        // USART2 TX
        gpio_set_mode(USART2_TX_GPIO_DEV, USART2_TX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(USART2_TX_GPIO_DEV, USART2_TX_GPIO_PIN, USART2_TX_AF);

        // USART2 RX
        gpio_set_mode(USART2_RX_GPIO_DEV, USART2_RX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(USART2_RX_GPIO_DEV, USART2_RX_GPIO_PIN, USART2_RX_AF);

        // enable USART2 clock
        *((uint32_t*)(RCC_APB1ENR)) |= (1 << RCC_APB1ENR_USART2EN_BIT);
    }

    else if (usart_device == USART3)
    {
        // USART 3 pin definition (Used also for ESP8266)
        // USART3 TX
        gpio_set_mode(USART3_TX_GPIO_DEV, USART3_TX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(USART3_TX_GPIO_DEV, USART3_TX_GPIO_PIN, USART3_TX_AF);

        // USART3 RX
        gpio_set_mode(USART3_RX_GPIO_DEV, USART3_RX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(USART3_RX_GPIO_DEV, USART3_RX_GPIO_PIN, USART3_RX_AF);

        // enable USART3 clock
        *((uint32_t*)(RCC_APB1ENR)) |= (1 << RCC_APB1ENR_USART3EN_BIT);
    }

    else if (usart_device == UART4)
    {
		// USART 4 pin definition

		// USART4 TX
        gpio_set_mode(UART4_TX_GPIO_DEV, UART4_TX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(UART4_TX_GPIO_DEV, UART4_TX_GPIO_PIN, UART4_TX_AF);

		// USART4 RX
        gpio_set_mode(UART4_RX_GPIO_DEV, UART4_RX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(UART4_RX_GPIO_DEV, UART4_RX_GPIO_PIN, UART4_RX_AF);

        // enable UART4 clock
        *((uint32_t*)(RCC_APB1ENR)) |= (1 << RCC_APB1ENR_UART4EN_BIT);
    }

    else if (usart_device == UART5) // Arduino OTTO not use this device
    {
        // UART 5 pin definition

        // UART5 TX
        gpio_set_mode(UART5_TX_GPIO_DEV, UART5_TX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(UART5_TX_GPIO_DEV, UART5_TX_GPIO_PIN, UART5_TX_AF);

        // UART5 RX
        gpio_set_mode(UART5_RX_GPIO_DEV, UART5_RX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(UART5_RX_GPIO_DEV, UART5_RX_GPIO_PIN, UART5_RX_AF);

        // enable UART5 clock
        *((uint32_t*)(RCC_APB1ENR)) |= (1 << RCC_APB1ENR_UART5EN_BIT);
    }

    else if (usart_device == USART6)
    {
        // USART 6 pin definition

        // USART6 TX
        gpio_set_mode(USART6_TX_GPIO_DEV, USART6_TX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(USART6_TX_GPIO_DEV, USART6_TX_GPIO_PIN, USART6_TX_AF);

        // USART6 RX
        gpio_set_mode(USART6_RX_GPIO_DEV, USART6_RX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(USART6_RX_GPIO_DEV, USART6_RX_GPIO_PIN, USART6_RX_AF);

        // enable USART6 clock
        *((uint32_t*)(RCC_APB2ENR)) |= (1 << RCC_APB2ENR_USART6EN_BIT);
    }

    else if (usart_device == UART7) // Arduino OTTO not use this device
    {
        // UART 7 pin definition

        // UART7 TX
        gpio_set_mode(UART7_TX_GPIO_DEV, UART7_TX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(UART7_TX_GPIO_DEV, UART7_TX_GPIO_PIN, UART7_TX_AF);

        // UART7 RX
        gpio_set_mode(UART7_RX_GPIO_DEV, UART7_RX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(UART7_RX_GPIO_DEV, UART7_RX_GPIO_PIN, UART7_RX_AF);

        // enable UART7 clock
        *((uint32_t*)(RCC_APB1ENR)) |= (1 << RCC_APB1ENR_UART7EN_BIT);
    }

    else if (usart_device == UART8) // Arduino OTTO not use this device
    {
        // UART 8 pin definition

        // UART8 TX
        gpio_set_mode(UART8_TX_GPIO_DEV, UART8_TX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(UART8_TX_GPIO_DEV, UART8_TX_GPIO_PIN, UART8_TX_AF);

        // UART8 RX
        gpio_set_mode(UART8_RX_GPIO_DEV, UART8_RX_GPIO_PIN, GPIO_AF_OUTPUT_PP);
        gpio_set_af_mode(UART8_RX_GPIO_DEV, UART8_RX_GPIO_PIN, UART8_RX_AF);

        // enable UART8 clock
        *((uint32_t*)(RCC_APB1ENR)) |= (1 << RCC_APB1ENR_UART8EN_BIT);
    }

#if 0
    if (txi->timer_device != NULL)
    {
        /* Turn off any PWM if there's a conflict on this GPIO bit. */
        timer_set_mode(txi->timer_device, txi->timer_channel, TIMER_DISABLED);
    }
#endif


    UartHandle.Instance          = (USART_TypeDef*)usart_device->regs;

    UartHandle.Init.BaudRate     = baud;
    UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits     = UART_STOPBITS_1;
    UartHandle.Init.Parity       = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode         = UART_MODE_TX_RX;
    UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&UartHandle);
	usart_init(usart_device);
    usart_enable(usart_device);
}

void HardwareSerial::end(void)
{
    usart_disable(usart_device);
}


int HardwareSerial::read(void)
{
	if(usart_data_available(usart_device) > 0)
    {
		return usart_getc(usart_device);
	}
    else
    {
		return -1;
	}
}

int HardwareSerial::available(void)
{
    return usart_data_available(usart_device);
}

int HardwareSerial::peek(void)
{
    return usart_peek(usart_device);
}

uint32 HardwareSerial::pending(void)
{
    return usart_data_pending(usart_device);
}

size_t HardwareSerial::write(unsigned char ch)
{
    usart_putc(usart_device, ch);
    return 1;
}

void HardwareSerial::flush(void)
{
    usart_reset_rx(usart_device);
}
