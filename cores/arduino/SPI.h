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

 /*
 * Arduino srl - www.arduino.org
 * 2016 Jun 9: Edited Francesco Alessi (alfran) - francesco@arduino.org
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <Arduino.h>

#define SPI2_CLK_ENABLE()                __HAL_RCC_SPI2_CLK_ENABLE()
#define SPI2_SCK_CLK_ENABLE()            __HAL_RCC_GPIOD_CLK_ENABLE()
#define SPI2_MISO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI2_MOSI_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()

#define SPI2_FORCE_RESET()               __HAL_RCC_SPI2_FORCE_RESET()
#define SPI2_RELEASE_RESET()             __HAL_RCC_SPI2_RELEASE_RESET()

/* Definition for SPI2 Pins */
#define SPI2_SCK_PIN                     GPIO_PIN_3
#define SPI2_SCK_GPIO_PORT               GPIOD
#define SPI2_SCK_AF                      GPIO_AF5_SPI2
#define SPI2_MISO_PIN                    GPIO_PIN_14
#define SPI2_MISO_GPIO_PORT              GPIOB
#define SPI2_MISO_AF                     GPIO_AF5_SPI2
#define SPI2_MOSI_PIN                    GPIO_PIN_3
#define SPI2_MOSI_GPIO_PORT              GPIOC
#define SPI2_MOSI_AF                     GPIO_AF5_SPI2

#define SPI1_CLK_ENABLE()                __HAL_RCC_SPI1_CLK_ENABLE()
#define SPI1_SCK_CLK_ENABLE()            __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI1_MISO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI1_MOSI_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPI1_NSS_CLK_ENABLE()            __HAL_RCC_GPIOA_CLK_ENABLE()

#define SPI1_FORCE_RESET()               __HAL_RCC_SPI1_FORCE_RESET()
#define SPI1_RELEASE_RESET()             __HAL_RCC_SPI1_RELEASE_RESET()

/* Definition for SPI2 Pins */
#define SPI1_SCK_PIN                     GPIO_PIN_3
#define SPI1_SCK_GPIO_PORT               GPIOB
#define SPI1_SCK_AF                      GPIO_AF5_SPI1
#define SPI1_MISO_PIN                    GPIO_PIN_4
#define SPI1_MISO_GPIO_PORT              GPIOB
#define SPI1_MISO_AF                     GPIO_AF5_SPI1
#define SPI1_MOSI_PIN                    GPIO_PIN_5
#define SPI1_MOSI_GPIO_PORT              GPIOB
#define SPI1_MOSI_AF                     GPIO_AF5_SPI1

#define SPI1_NSS_PIN                     GPIO_PIN_15
#define SPI1_NSS_GPIO_PORT               GPIOA
#define SPI1_NSS_AF                      GPIO_AF5_SPI1

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

enum SPITransferMode {
	SPI_CONTINUE,
	SPI_LAST
};

class SPISettings {
public:
  SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
  {
    init_AlwaysInline(clock, bitOrder, dataMode);
  }
  SPISettings()
  {
    init_AlwaysInline(4000000, MSBFIRST, SPI_MODE0);
  }
private:
  void init_AlwaysInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
    __attribute__((__always_inline__)) {

    /* Select the Bit Order */
    if(bitOrder == LSBFIRST)
    {
      FirstBit = SPI_FIRSTBIT_LSB;
    }
    else
    {
      FirstBit = SPI_FIRSTBIT_MSB;
    }

    /* Select the SPI Communication Mode */
    if(dataMode == SPI_MODE0)
    {
      CLKPhase          = SPI_PHASE_1EDGE;
      CLKPolarity       = SPI_POLARITY_LOW;
    }
    else if(dataMode == SPI_MODE1)
    {
      CLKPhase          = SPI_PHASE_2EDGE;
      CLKPolarity       = SPI_POLARITY_LOW;
    }
    else if(dataMode == SPI_MODE2)
    {
      CLKPhase          = SPI_PHASE_1EDGE;
      CLKPolarity       = SPI_POLARITY_HIGH;
    }
    else
    {
      CLKPhase          = SPI_PHASE_2EDGE;
      CLKPolarity       = SPI_POLARITY_HIGH;
    }

    /* Select the Clock Divider */
    BaudRatePrescaler = (((HAL_RCC_GetPCLK1Freq()) / 2  ) < clock) ? SPI_CLOCK_DIV2
                      : (((HAL_RCC_GetPCLK1Freq()) / 4  ) < clock) ? SPI_CLOCK_DIV4
                      : (((HAL_RCC_GetPCLK1Freq()) / 8  ) < clock) ? SPI_CLOCK_DIV8
                      : (((HAL_RCC_GetPCLK1Freq()) / 16 ) < clock) ? SPI_CLOCK_DIV16
                      : (((HAL_RCC_GetPCLK1Freq()) / 32 ) < clock) ? SPI_CLOCK_DIV32
                      : (((HAL_RCC_GetPCLK1Freq()) / 64 ) < clock) ? SPI_CLOCK_DIV64
                      : (((HAL_RCC_GetPCLK1Freq()) / 128) < clock) ? SPI_CLOCK_DIV128
                      :                                              SPI_CLOCK_DIV256;
  }

  uint32_t FirstBit;
  uint32_t CLKPhase;
  uint32_t CLKPolarity;
  uint32_t BaudRatePrescaler;

  friend class SPIClass;
};

class SPIClass {
public:
  /* Constructor */
  SPIClass(SPI_TypeDef *spiInstance);
  /* Initialize the SPI peripheral */
  void begin();

  /* Initialize the SPI peripheral and SS pin */
  void begin(uint8_t slaveSelectPin);

  /* Initialize the SPI peripheral with settings */
  void beginTransaction(SPISettings settings);

  /* Initialize the SPI peripheral */
  void endTransaction();

  /* Begin the transfer */
  uint8_t transfer(uint8_t data);
  uint16_t transfer16(uint16_t data);
  void transfer(void *buf, size_t count);
  uint8_t transfer(uint8_t slaveSelectPin, uint8_t val, SPITransferMode transferMode);

  /* End the transfer */
  void end();

  void end(uint8_t slaveSelectPin);

  /* Set Bit Order */
  void setBitOrder(uint8_t bitOrder);

  /* Set Clock Divider */
  void setClockDivider(uint8_t clockDiv);

  /* Set Communication Mode */
  void setDataMode(uint8_t dataMode);

private:

  SPI_HandleTypeDef hSPIx;

};

extern SPIClass SPI;
extern SPIClass SPI7;

#endif
