/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@arduino.cc>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * Copyright (c) 2014 by Matthijs Kooijman <matthijs@stdin.nl> (SPISettings AVR)
 * Copyright (c) 2014 by Andrew J. Kroll <xxxajk@gmail.com> (atomicity fixes)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <Arduino.h>
extern SPI_HandleTypeDef hSPIx;

#define SPIx                             HAL_SPI2
#define SPIx_CLK_ENABLE()                __HAL_RCC_SPI2_CLK_ENABLE()
#define SPIx_SCK_CLK_ENABLE()            __HAL_RCC_GPIOD_CLK_ENABLE()
#define SPIx_MISO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MOSI_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define SPIx_NSS_CLK_ENABLE()            __HAL_RCC_GPIOA_CLK_ENABLE()

#define SPIx_FORCE_RESET()               __HAL_RCC_SPI2_FORCE_RESET()
#define SPIx_RELEASE_RESET()             __HAL_RCC_SPI2_RELEASE_RESET()
#define SPIx_NSS_CLK_DISABLE             __HAL_RCC_GPIOA_CLK_DISABLE

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN                     GPIO_PIN_3
#define SPIx_SCK_GPIO_PORT               HAL_GPIOD
#define SPIx_SCK_AF                      GPIO_AF5_SPI2
#define SPIx_MISO_PIN                    GPIO_PIN_14
#define SPIx_MISO_GPIO_PORT              HAL_GPIOB
#define SPIx_MISO_AF                     GPIO_AF5_SPI2
#define SPIx_MOSI_PIN                    GPIO_PIN_3
#define SPIx_MOSI_GPIO_PORT              HAL_GPIOC
#define SPIx_MOSI_AF                     GPIO_AF5_SPI2

#define SPIx_NSS_PIN                     GPIO_PIN_15
#define SPIx_NSS_GPIO_PORT               HAL_GPIOA
#define SPIx_NSS_AF                      GPIO_AF5_SPI2


#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif




#define SPI_CLOCK_DIV2   SPI_BAUDRATEPRESCALER_2
#define SPI_CLOCK_DIV4   SPI_BAUDRATEPRESCALER_4
#define SPI_CLOCK_DIV8   SPI_BAUDRATEPRESCALER_8
#define SPI_CLOCK_DIV16  SPI_BAUDRATEPRESCALER_16
#define SPI_CLOCK_DIV32  SPI_BAUDRATEPRESCALER_32
#define SPI_CLOCK_DIV64  SPI_BAUDRATEPRESCALER_64
#define SPI_CLOCK_DIV128 SPI_BAUDRATEPRESCALER_128
#define SPI_CLOCK_DIV256 SPI_BAUDRATEPRESCALER_256

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_LAST  0
#define SPI_CONTINUE 1


class SPISettings {
public:
  SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
      init_AlwaysInline(clock, bitOrder, dataMode);
  }
  SPISettings() {
    init_AlwaysInline(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0);
  }
private:
  void init_AlwaysInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
    __attribute__((__always_inline__)) {

    /* Select the Bit Order */
    if(bitOrder == LSBFIRST) {
      bitOrder = SPI_FIRSTBIT_LSB;
    }
    else {
      bitOrder = SPI_FIRSTBIT_MSB;
    }
    hSPIx.Init.FirstBit = bitOrder;

    /* Select the SPI Communication Mode */
    if(dataMode == SPI_MODE0) {
      hSPIx.Init.CLKPhase          = SPI_PHASE_1EDGE;
      hSPIx.Init.CLKPolarity       = SPI_POLARITY_LOW;
    }
    else if(dataMode == SPI_MODE1) {
      hSPIx.Init.CLKPhase          = SPI_PHASE_2EDGE;
      hSPIx.Init.CLKPolarity       = SPI_POLARITY_LOW;
    }
    else if(dataMode == SPI_MODE2) {
      hSPIx.Init.CLKPhase          = SPI_PHASE_1EDGE;
      hSPIx.Init.CLKPolarity       = SPI_POLARITY_HIGH;
    }
    else {
      hSPIx.Init.CLKPhase          = SPI_PHASE_2EDGE;
      hSPIx.Init.CLKPolarity       = SPI_POLARITY_HIGH;
    }

    /* Select the Clock Divider */
    hSPIx.Init.BaudRatePrescaler = clock;

    /* Initialize the SPIx */
    HAL_SPI_Init(&hSPIx);
  }

  friend class SPIClass;
};


class SPIClass {
public:
  /* Initialize the SPI peripheral */
  static void begin();

  /* Initialize the SPI peripheral and SS pin */
  static void begin(uint8_t slaveSelectPin);

  /* Initialize the SPI peripheral with settings */
  static void beginTransaction(SPISettings settings);

  /* Initialize the SPI peripheral */
  static void endTransaction();

  /* Begin the transfer */
  static uint8_t transfer(uint8_t data);
  static uint16_t transfer16(uint16_t data);
  static void transfer(void *buf, size_t count);
  static void transfer(uint8_t slaveSelectPin, uint8_t val, uint8_t transferMode);

  /* End the transfer */
  static void end();

  static void end(uint8_t slaveSelectPin);

  /* Set Bit Order */
  static void setBitOrder(uint8_t bitOrder);

  /* Set Clock Divider */
  static void setClockDivider(uint8_t clockDiv);

  /* Set Communication Mode */
  static void setDataMode(uint8_t dataMode);

};

extern SPIClass SPI;
//extern SPISettings SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0);
#endif
