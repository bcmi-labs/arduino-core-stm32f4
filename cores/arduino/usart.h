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
 * @file usart.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>,
 *         Perry Hung <perry@leaflabs.com>
 * @brief USART definitions and prototypes
 */

 /*
  * Arduino srl - www.arduino.org
  * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
  */

#ifndef _USART_H_
#define _USART_H_

#include "types.h"
#include "util.h"
#include "rcc.h"
#include "nvic.h"
#include "ring_buffer.h"
#include "bitband.h"


#ifdef __cplusplus
extern "C"{
#endif

/*
 * Devices
 */

#ifndef USART_RX_BUF_SIZE
#define USART_RX_BUF_SIZE               256
#endif

#ifndef USART_TX_BUF_SIZE
#define USART_TX_BUF_SIZE               256
#endif

/** USART device type */
typedef struct usart_dev {
    USART_TypeDef *regs;             /**< Register map */
    ring_buffer rbRX;                 /**< RX ring buffer */
    ring_buffer rbTX;                 /**< RX ring buffer */
    uint32 max_baud;                 /**< Maximum baud */
    uint8 rx_buf[USART_RX_BUF_SIZE]; /**< @brief Deprecated.
                                      * Actual RX buffer used by rb.
                                      * This field will be removed in
                                      * a future release. */
    uint8 tx_buf[USART_TX_BUF_SIZE];
    rcc_clk_id clk_id;               /**< RCC clock information */
    IRQn_Type irq_num;            /**< USART NVIC interrupt */
} usart_dev;

extern usart_dev *USART1_dev;
extern usart_dev *USART2_dev;
extern usart_dev *USART3_dev;
extern usart_dev *UART4_dev;
extern usart_dev *UART5_dev;
extern usart_dev *USART6_dev;
extern usart_dev *UART7_dev;
extern usart_dev *UART8_dev;

void usart_init(usart_dev *dev);
void usart_set_baud_rate(usart_dev *dev, uint32 baud);
void usart_enable(usart_dev *dev);
void usart_disable(usart_dev *dev);
void usart_foreach(void (*fn)(usart_dev *dev));
uint32 usart_tx(usart_dev *dev, const uint8 *buf, uint32 len);
void usart_putudec(usart_dev *dev, uint32 val);

/**
 * @brief Disable all serial ports.
 */
static inline void usart_disable_all(void) {
    usart_foreach(usart_disable);
}

/**
 * @brief Transmit one character on a serial port.
 *
 * This function blocks until the character has been successfully
 * transmitted.
 *
 * @param dev Serial port to send on.
 * @param byte Byte to transmit.
 */
static inline void usart_putc(usart_dev* dev, uint8 byte) {
    while (!usart_tx(dev, &byte, 1))
        ;
}

/**
 * @brief Transmit a character string on a serial port.
 *
 * This function blocks until str is completely transmitted.
 *
 * @param dev Serial port to send on
 * @param str String to send
 */
static inline void usart_putstr(usart_dev *dev, const char* str) {
    uint32 i = 0;
    while (str[i] != '\0') {
        usart_putc(dev, str[i++]);
    }
}

/**
 * @brief Read one character from a serial port.
 *
 * It's not safe to call this function if the serial port has no data
 * available.
 *
 * @param dev Serial port to read from
 * @return byte read
 * @see usart_data_available()
 */
static inline uint8 usart_getc(usart_dev *dev) {
    return rb_remove(&dev->rbRX);
}

/*
 * Roger Clark. 20141125,
 * added peek function.
 * @param dev Serial port to read from
 * @return byte read
 */
static inline int usart_peek(usart_dev *dev)
{
    return rb_peek(&dev->rbRX);
}


/**
 * @brief Return the amount of data available in a serial port's RX buffer.
 * @param dev Serial port to check
 * @return Number of bytes in dev's RX buffer.
 */
static inline uint32 usart_data_available(usart_dev *dev) {
    return rb_full_count(&dev->rbRX);
}

/**
 * @brief Return the amount of data available in a serial port's TX buffer.
 * @param dev Serial port to check
 * @return Number of bytes in dev's TX buffer.
 */
static inline uint32 usart_data_pending(usart_dev *dev) {
    return rb_full_count(&dev->rbTX);
}

/**
 * @brief Discard the contents of a serial port's RX buffer.
 * @param dev Serial port whose buffer to empty.
 */
static inline void usart_reset_rx(usart_dev *dev) {
    rb_reset(&dev->rbRX);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _USART_H_
