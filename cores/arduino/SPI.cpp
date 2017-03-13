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
 * 2016 Jun  9: Edited Francesco Alessi (alfran) - francesco@arduino.org
 */

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
  #include "stm32f4xx_hal.h"
}

#include "SPI.h"

SPIClass::SPIClass(SPI_TypeDef *spiInstance)
{
  hSPIx.Instance = spiInstance;
}

/**
  * @brief  Configure SPI, configure relatives IOs and enable SPI2
  * @param  None
  * @retval None
  */
void SPIClass::begin()
{
  if(hSPIx.Instance == SPI2)
  {
    GPIO_InitTypeDef  GPIO_InitStruct;

    /* Enable GPIO clock */
    SPI2_SCK_CLK_ENABLE();
    SPI2_MISO_CLK_ENABLE();
    SPI2_MOSI_CLK_ENABLE();

    /* Enable SPI2 clock */
    SPI2_CLK_ENABLE();

    /* Configure SPI2 SCK PIN defined in SPI.h */
    GPIO_InitStruct.Pin = SPI2_SCK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = SPI2_SCK_AF;
    HAL_GPIO_Init(SPI2_SCK_GPIO_PORT, &GPIO_InitStruct);

    /* Configure SPI2 MISO PIN defined in SPI.h */
    GPIO_InitStruct.Pin = SPI2_MISO_PIN;
    GPIO_InitStruct.Alternate = SPI2_MISO_AF;
    HAL_GPIO_Init(SPI2_MISO_GPIO_PORT, &GPIO_InitStruct);

    /* Configure SPI2 MOSI PIN defined in SPI.h */
    GPIO_InitStruct.Pin = SPI2_MOSI_PIN;
    GPIO_InitStruct.Alternate = SPI2_MOSI_AF;
    HAL_GPIO_Init(SPI2_MOSI_GPIO_PORT, &GPIO_InitStruct);
  }
  else if (hSPIx.Instance == SPI1)
  {
    GPIO_InitTypeDef  GPIO_InitStruct;

    /* Enable GPIO clock */
    SPI1_SCK_CLK_ENABLE();
    SPI1_MISO_CLK_ENABLE();
    SPI1_MOSI_CLK_ENABLE();
    SPI1_NSS_CLK_ENABLE();

    /* Enable SPI1 clock */
    SPI1_CLK_ENABLE();

    /* Configure SPI1 SCK PIN defined in SPI.h */
    GPIO_InitStruct.Pin = SPI1_SCK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = SPI1_SCK_AF;
    HAL_GPIO_Init(SPI1_SCK_GPIO_PORT, &GPIO_InitStruct);

    /* Configure SPI1 MISO PIN defined in SPI.h */
    GPIO_InitStruct.Pin = SPI1_MISO_PIN;
    GPIO_InitStruct.Alternate = SPI1_MISO_AF;
    HAL_GPIO_Init(SPI1_MISO_GPIO_PORT, &GPIO_InitStruct);

    /* Configure SPI1 MOSI PIN defined in SPI.h */
    GPIO_InitStruct.Pin = SPI1_MOSI_PIN;
    GPIO_InitStruct.Alternate = SPI1_MOSI_AF;
    HAL_GPIO_Init(SPI1_MOSI_GPIO_PORT, &GPIO_InitStruct);

	/* Put SPI1 NSS pin as Output pin in order to be used as normal GPIO in Master mode */
    GPIO_InitStruct.Pin = SPI1_NSS_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SPI1_NSS_GPIO_PORT, &GPIO_InitStruct);
  }

  /* SPI general configuration */
  hSPIx.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hSPIx.Init.Direction         = SPI_DIRECTION_2LINES;
  hSPIx.Init.CLKPhase          = SPI_PHASE_1EDGE;
  hSPIx.Init.CLKPolarity       = SPI_POLARITY_LOW;
  hSPIx.Init.DataSize          = SPI_DATASIZE_8BIT;
  hSPIx.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  hSPIx.Init.TIMode            = SPI_TIMODE_DISABLE;
  hSPIx.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  hSPIx.Init.CRCPolynomial     = 7;
  hSPIx.Init.NSS               = SPI_NSS_SOFT;
  hSPIx.Init.Mode              = SPI_MODE_MASTER;

  HAL_SPI_Init(&hSPIx);
}

/**
  * @brief  Configure SPI, configure relatives IOs and enable SPIx
  * @param  slaveSelectPin: IO to configure
  * @retval None
  */
void SPIClass::begin(uint8_t slaveSelectPin)
{
  /* SPIx configuration */
  begin();
  pinMode(slaveSelectPin, OUTPUT);
}

/**
  * @brief  Configure SPI with parameters clock, bitOrder and dataMode
  *         defined within settings object
  * @param  settings: object containing parameters clock, bitOrder and dataMode
  * @retval None
  */
void SPIClass::beginTransaction(SPISettings settings)
{
  hSPIx.Init.FirstBit          = settings.FirstBit;
  hSPIx.Init.CLKPhase          = settings.CLKPhase;
  hSPIx.Init.CLKPolarity       = settings.CLKPolarity;
  hSPIx.Init.BaudRatePrescaler = settings.BaudRatePrescaler;

  HAL_SPI_Init(&hSPIx);
}

/**
  * @brief  End SPI transaction
  * @param  None
  * @retval None
  */
void SPIClass::endTransaction()
{
  /* Go back to default settings */
  hSPIx.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  hSPIx.Init.CLKPhase          = SPI_PHASE_1EDGE;
  hSPIx.Init.CLKPolarity       = SPI_POLARITY_LOW;
  hSPIx.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;

  HAL_SPI_Init(&hSPIx);
}

/**
  * @brief  Transmit and Receive one byte of data in blocking mode
  * @param  data: data to be transmitted
  * @retval Byte received
  */
uint8_t SPIClass::transfer(uint8_t data)
{
  uint8_t rxdata;
  HAL_SPI_TransmitReceive(&hSPIx, (uint8_t*)&data, (uint8_t*)&rxdata, 1,5000);
  return rxdata;
}

/**
  * @brief  Transmit and Receive 2 bytes of data in blocking mode
  * @param  data: data to be transmitted
  * @retval Bytes received
  */
uint16_t SPIClass::transfer16(uint16_t data)
{
  uint16_t rxdata;
  HAL_SPI_TransmitReceive(&hSPIx, (uint8_t*)&data, (uint8_t*)&rxdata, 2,5000);
  return rxdata;
}

/**
  * @brief  Transmit and Receive an amount of data in blocking mode
  * @param  buf: pointer to transmission data buffer
  * @param  count: number of data in byte to be transmitted
  * @retval None
  */
void SPIClass::transfer(void *buf, size_t count)
{
  uint8_t rxdata;
  int i;

  for(i = 0; i < count; i++)
  {
    HAL_SPI_TransmitReceive(&hSPIx, ((uint8_t*)buf + i), (uint8_t*)&rxdata, 1,5000);
    *((uint8_t*)buf + i) = rxdata;
  }
}

/**
  * @brief  Transmit and Receive one byte of data in blocking mode
  * @param  data: data to be transmitted
  * @retval Byte received
  */
uint8_t  SPIClass::transfer(uint8_t slaveSelectPin, uint8_t val, SPITransferMode transferMode)
{
  uint8_t rxdata;
  digitalWrite(slaveSelectPin,LOW);
  HAL_SPI_TransmitReceive(&hSPIx, (uint8_t *)&val, (uint8_t*)&rxdata, 1,5000);

  /* If transferMode is SPI_CONTINUE we need to hold CS GPIO pin low */
  /* If transferMode is SPI_LAST we need to put CS GPIO pin high */
  if(transferMode == SPI_LAST)
  {
    digitalWrite(slaveSelectPin, HIGH);
  }

  return rxdata;
}

/**
  * @brief  Set the bit order to LSB of MSB first
  * @param  bitOrder: LSBFIRST or MSBFIRST
  * @retval None
  */
void SPIClass::setBitOrder(uint8_t bitOrder)
{
  if(bitOrder == LSBFIRST)
  {
    bitOrder = SPI_FIRSTBIT_LSB;
  }
  else
  {
    bitOrder = SPI_FIRSTBIT_MSB;
  }
  hSPIx.Init.FirstBit = bitOrder;
  HAL_SPI_Init(&hSPIx);
}

/**
  * @brief  Set mode to control clock polarity and phase
  * @param  dataMode: This parameter can be one of the following values
  *                   SPI_MODE0
  *                   SPI_MODE1
  *                   SPI_MODE2
  *                   SPI_MODE3
  * @retval None
  */
void SPIClass::setDataMode(uint8_t dataMode)
{
  if(dataMode == SPI_MODE0)
  {
    hSPIx.Init.CLKPhase          = SPI_PHASE_1EDGE;
    hSPIx.Init.CLKPolarity       = SPI_POLARITY_LOW;
  }
  else if(dataMode == SPI_MODE1)
  {
    hSPIx.Init.CLKPhase          = SPI_PHASE_2EDGE;
    hSPIx.Init.CLKPolarity       = SPI_POLARITY_LOW;
  }
  else if(dataMode == SPI_MODE2)
  {
    hSPIx.Init.CLKPhase          = SPI_PHASE_1EDGE;
    hSPIx.Init.CLKPolarity       = SPI_POLARITY_HIGH;
  }
  else
  {
    hSPIx.Init.CLKPhase          = SPI_PHASE_2EDGE;
    hSPIx.Init.CLKPolarity       = SPI_POLARITY_HIGH;
  }

  /* Change CPOL and CPHASE */
  HAL_SPI_Init(&hSPIx);
}

/**
  * @brief  Set clock divider
  * @param  clockDiv: clock divider
  * @retval None
  */
void SPIClass::setClockDivider(uint8_t clockDiv)
{
  hSPIx.Init.BaudRatePrescaler = clockDiv;
  HAL_SPI_Init(&hSPIx);
}

/**
  * @brief  Disable SPIx peripheral.
  * @param  None
  * @retval None
  */
void SPIClass::end()
{
  if(hSPIx.Instance == SPI2)
  {
    /*##-1- Reset peripherals ##################################################*/
    SPI2_FORCE_RESET();
    SPI2_RELEASE_RESET();

    /*##-2- Disable peripherals and GPIO Clocks ################################*/
    /* Configure SPI2 SCK as alternate function  */
    HAL_GPIO_DeInit(SPI2_SCK_GPIO_PORT, SPI2_SCK_PIN);
    /* Configure SPI2 MISO as alternate function  */
    HAL_GPIO_DeInit(SPI2_MISO_GPIO_PORT, SPI2_MISO_PIN);
    /* Configure SPI2 MOSI as alternate function  */
    HAL_GPIO_DeInit(SPI2_MOSI_GPIO_PORT, SPI2_MOSI_PIN);
  }
  else if (hSPIx.Instance == SPI1)
  {
    /*##-1- Reset peripherals ##################################################*/
    SPI1_FORCE_RESET();
    SPI1_RELEASE_RESET();

    /*##-2- Disable peripherals and GPIO Clocks ################################*/
    /* Configure SPI1 SCK as alternate function  */
    HAL_GPIO_DeInit(SPI1_SCK_GPIO_PORT, SPI1_SCK_PIN);
    /* Configure SPI1 MISO as alternate function  */
    HAL_GPIO_DeInit(SPI1_MISO_GPIO_PORT, SPI1_MISO_PIN);
    /* Configure SPI1 MOSI as alternate function  */
    HAL_GPIO_DeInit(SPI1_MOSI_GPIO_PORT, SPI1_MOSI_PIN);
  }

  HAL_SPI_DeInit(&hSPIx);
}

/**
  * @brief  Disable SPIx peripheral and SS pin.
  * @param  None
  * @retval None
  */
void SPIClass::end(uint8_t slaveSelectPin)
{
  pinMode(slaveSelectPin, INPUT);
  end();
}

SPIClass SPI = SPIClass(SPI2);
SPIClass SPI7 = SPIClass(SPI1);
