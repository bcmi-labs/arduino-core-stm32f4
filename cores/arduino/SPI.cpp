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
  * @brief  Configure SPI, configure relatives IOs and enable SPIx
  * @param  None
  * @retval None
  */
void SPIClass::begin()
{
  if(hSPIx.Instance == SPIx)
  {
    GPIO_InitTypeDef  GPIO_InitStruct;

    /* Enable GPIO clock */
    SPIx_SCK_CLK_ENABLE();
    SPIx_MISO_CLK_ENABLE();
    SPIx_MOSI_CLK_ENABLE();

    /* Enable SPI clock */
    SPIx_CLK_ENABLE();

    /* Configure SPI SCK pin(PB10) as alternate function  */
    GPIO_InitStruct.Pin = SPIx_SCK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = SPIx_SCK_AF;
    HAL_GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);

    /* Configure SPI MISO pin(PB14) as alternate function  */
    GPIO_InitStruct.Pin = SPIx_MISO_PIN;
    GPIO_InitStruct.Alternate = SPIx_MISO_AF;
    HAL_GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStruct);

    /* Configure SPI MOSI pin(PB15) as alternate function  */
    GPIO_InitStruct.Pin = SPIx_MOSI_PIN;
    GPIO_InitStruct.Alternate = SPIx_MOSI_AF;
    HAL_GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);

	/* Put NSS pin as Output pin in order to be used as normal GPIO in Master mode */
    GPIO_InitStruct.Pin = SPIx_NSS_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(SPIx_NSS_GPIO_PORT, &GPIO_InitStruct);
  }

  /* SPIx configuration ----------------------------------------------------*/
  hSPIx.Instance               = SPIx;
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
  /* SPIx configuration        */
  begin();

  /* TOBEFIXED: The correct way to proceed here it is to map the Arduino slaveSelectPin provided as parameter */
  /* with the Cube GPIO port and pin number and then call the HAL_GPIO_Init with the correct values */
  /* At the moment only NSS pin is supported */
  switch(slaveSelectPin)
  {
    case 10:
    default:
    {
      GPIO_InitTypeDef  GPIO_InitStruct;

      SPIx_NSS_CLK_ENABLE();
      GPIO_InitStruct.Pin = SPIx_NSS_PIN;
      GPIO_InitStruct.Alternate = SPIx_NSS_AF;
      GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      GPIO_InitStruct.Pull = GPIO_PULLDOWN;
      GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

	  HAL_GPIO_Init(SPIx_NSS_GPIO_PORT, &GPIO_InitStruct);
	  break;
    }
  }
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
  HAL_SPI_TransmitReceive(&hSPIx, (uint8_t*)buf, (uint8_t*)&rxdata, count,5000);
}

/**
  * @brief  Transmit and Receive one byte of data in blocking mode
  * @param  data: data to be transmitted
  * @retval Byte received
  */
uint8_t  SPIClass::transfer(uint8_t slaveSelectPin, uint8_t val, SPITransferMode transferMode)
{
  uint8_t rxdata;

  /* TOBEFIXED: The correct way to proceed here it is to map the Arduino pin provided as parameter */
  /* with the Cube GPIO port and pin number and then call the HAL_GPIO_WritePin */
  switch(slaveSelectPin)
  {
    case 10:
    default:
    {
      HAL_GPIO_WritePin(SPIx_NSS_GPIO_PORT, SPIx_NSS_PIN, GPIO_PIN_RESET);
      break;
    }
  }

  HAL_SPI_TransmitReceive(&hSPIx, (uint8_t *)&val, (uint8_t*)&rxdata, 1,5000);

  /* If transferMode is SPI_CONTINUE we need to hold CS GPIO pin low */
  /* If transferMode is SPI_LAST we need to put CS GPIO pin high */
  if(transferMode == SPI_LAST)
  {
    switch(slaveSelectPin)
    {
      case 10:
      default:
      {
        HAL_GPIO_WritePin(SPIx_NSS_GPIO_PORT, SPIx_NSS_PIN, GPIO_PIN_SET);
        break;
      }
    }
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
  if(hSPIx.Instance == SPIx)
  {
    /*##-1- Reset peripherals ##################################################*/
    SPIx_FORCE_RESET();
    SPIx_RELEASE_RESET();

    /*##-2- Disable peripherals and GPIO Clocks ################################*/
    /* Configure SPI SCK as alternate function  */
    HAL_GPIO_DeInit(SPIx_SCK_GPIO_PORT, SPIx_SCK_PIN);
    /* Configure SPI MISO as alternate function  */
    HAL_GPIO_DeInit(SPIx_MISO_GPIO_PORT, SPIx_MISO_PIN);
    /* Configure SPI MOSI as alternate function  */
    HAL_GPIO_DeInit(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_PIN);
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
  /* TOBEFIXED: The correct way to proceed here it is to map the Arduino slaveSelectPin provided as parameter */
  /* with the Cube GPIO port and pin number and then call the HAL_GPIO_DeInit with the correct values */
  switch(slaveSelectPin)
  {
    case 10:
    default:
    {
      HAL_GPIO_DeInit(SPIx_NSS_GPIO_PORT, SPIx_NSS_PIN);
	  break;
    }
  }

  HAL_SPI_DeInit(&hSPIx);
}

SPIClass SPI = SPIClass(HAL_SPI2);
