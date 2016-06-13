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

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
	#include "stm32f4xx_hal.h"

}

#include "HardwareSPI.h"
SPIClass SPI;

SPI_HandleTypeDef hSPIx;

/**
  * @brief  Configure SPI, configure relatives IOs and enable SPIx
  * @param  None
  * @retval None
  */
void SPIClass::begin() {
  /* SPIx configuration ----------------------------------------------------*/
  hSPIx.Instance               = SPIx;
  hSPIx.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
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
void SPIClass::begin(uint8_t slaveSelectPin) {
   GPIO_InitTypeDef  GPIO_InitStruct;
  /* SPIx configuration        */
  SPI.begin();

  /* NSS pin PB3 configuration */
  SPIx_NSS_CLK_ENABLE();
  GPIO_InitStruct.Pin = slaveSelectPin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  HAL_GPIO_Init(SPIx_NSS_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief  Configure SPI with parameters clock, bitOrder and dataMode
  *         defined within settings object
  * @param  settings: object containing parameters clock, bitOrder and dataMode
  * @retval None
  */
void SPIClass::beginTransaction(SPISettings settings) {
  // do nothing
}

/**
  * @brief  End SPI transaction
  * @param  None
  * @retval None
  */
void SPIClass::endTransaction() {
   HAL_SPI_DeInit(&hSPIx);
}

/**
  * @brief  Transmit and Receive one byte of data in blocking mode
  * @param  data: data to be transmitted
  * @retval Byte received
  */
uint8_t SPIClass::transfer(uint8_t data) {
    uint8_t rxdata;
    HAL_SPI_TransmitReceive(&hSPIx, (uint8_t*)&data, (uint8_t*)&rxdata, 1,5000);
    return rxdata;
}

/**
  * @brief  Transmit and Receive 2 bytes of data in blocking mode
  * @param  data: data to be transmitted
  * @retval Bytes received
  */
uint16_t SPIClass::transfer16(uint16_t data) {
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
void SPIClass::transfer(void *buf, size_t count) {
    uint8_t rxdata;
    HAL_SPI_TransmitReceive(&hSPIx, (uint8_t*)buf, (uint8_t*)&rxdata, count,5000);
}

/**
  * @brief  Transmit and Receive one byte of data in blocking mode
  * @param  data: data to be transmitted
  * @retval Byte received
  */
void  SPIClass::transfer(uint8_t slaveSelectPin, uint8_t val, uint8_t transferMode) {
	HAL_SPI_Transmit(&hSPIx, (uint8_t *)&val, 1,5000);

	if(transferMode == SPI_LAST) {
    HAL_GPIO_WritePin(SPIx_NSS_GPIO_PORT, SPIx_NSS_PIN, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(SPIx_NSS_GPIO_PORT, SPIx_NSS_PIN, GPIO_PIN_RESET);
	}
}

/**
  * @brief  Set the bit order to LSB of MSB first
  * @param  bitOrder: LSBFIRST or MSBFIRST
  * @retval None
  */
void SPIClass::setBitOrder(uint8_t bitOrder) {
    if(bitOrder == LSBFIRST) {
      bitOrder = SPI_FIRSTBIT_LSB;
    }
    else {
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
void SPIClass::setDataMode(uint8_t dataMode) {
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

    /* Change CPOL and CPHASE */
    HAL_SPI_Init(&hSPIx);
  }

/**
  * @brief  Set clock divider
  * @param  clockDiv: clock divider
  * @retval None
  */
void SPIClass::setClockDivider(uint8_t clockDiv) {
    hSPIx.Init.BaudRatePrescaler = clockDiv;
    HAL_SPI_Init(&hSPIx);
 }

/**
  * @brief  Disable SPIx peripheral.
  * @param  None
  * @retval None
  */
void SPIClass::end() {
    HAL_SPI_DeInit(&hSPIx);
}

/**
  * @brief  Disable SPIx peripheral and SS pin.
  * @param  None
  * @retval None
  */
void SPIClass::end(uint8_t slaveSelectPin) {
    HAL_SPI_DeInit(&hSPIx);
    SPIx_NSS_CLK_DISABLE();
}

/**
  * @brief SPI MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi) {
  GPIO_InitTypeDef  GPIO_InitStruct;
  if(hspi->Instance == SPIx) {
    /* Enable GPIO clock */
    SPIx_SCK_CLK_ENABLE();
    SPIx_MISO_CLK_ENABLE();
    SPIx_MOSI_CLK_ENABLE();
    SPIx_NSS_CLK_ENABLE();

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

    GPIO_InitStruct.Pin = SPIx_NSS_PIN;
    GPIO_InitStruct.Alternate = SPIx_NSS_AF;
    HAL_GPIO_Init(SPIx_NSS_GPIO_PORT, &GPIO_InitStruct);
  }
}

/**
* @brief  SPI BSP Deinit
* @param  hspi : SPI handle
* @retval None
*/
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
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
