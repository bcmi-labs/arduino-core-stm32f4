/**
  ******************************************************************************
  * @file    stm32469i_discovery_sd.h
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    13-January-2016
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32469i_discovery_sd.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32469I_DISCOVERY_SD_H
#define __STM32469I_DISCOVERY_SD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I_Discovery
  * @{
  */

/** @addtogroup STM32469I-Discovery_SD 
  * @{
  */

/** @defgroup STM32469I-Discovery_SD_Exported_Types STM32469I Discovery SD Exported Types
  * @{
  */

/**
  * @brief SD Card information structure
  */
#define SD_CardInfo HAL_SD_CardInfoTypedef
/**
  * @}
  */

/**
  * @brief  SD status structure definition
  */
#define   MSD_OK                        ((uint8_t)0x00)
#define   MSD_ERROR                     ((uint8_t)0x01)
#define   MSD_ERROR_SD_NOT_PRESENT      ((uint8_t)0x02)

/** @defgroup STM32469I-Discovery_SD_Exported_Constants STM32469I Discovery SD Exported Constants
  * @{
  */
#define SD_PRESENT               ((uint8_t)0x01)
#define SD_NOT_PRESENT           ((uint8_t)0x00)

#define SD_DATATIMEOUT           ((uint32_t)100000000)

/**
  * @brief SD-detect signal
  */
#define SD_DETECT_PIN                        GPIO_PIN_2
#define SD_DETECT_GPIO_PORT                  HAL_GPIOG
#define SD_DETECT_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOG_CLK_ENABLE()
#define SD_DETECT_GPIO_CLK_DISABLE()         __HAL_RCC_GPIOG_CLK_DISABLE()
#define SD_DETECT_EXTI_IRQn                  EXTI2_IRQn

/**
  * @}
  */

/** @defgroup STM32469I-Discovery_SD_Exported_Macro STM32469I Discovery SD Exported Macro
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-Discovery_SD_Exported_Functions STM32469I Discovery SD Exported Functions
  * @{
  */
uint8_t BSP_SD_Init(void);
uint8_t BSP_SD_CSInit(void);
uint8_t BSP_SD_DeInit(void);
uint8_t BSP_SD_ITConfig(void);

uint8_t BSP_SD_ReadBlocks(uint32_t *pData, uint64_t ReadAddr, uint32_t BlockSize, uint32_t NumOfBlocks);
uint8_t BSP_SD_WriteBlocks(uint32_t *pData, uint64_t WriteAddr, uint32_t BlockSize, uint32_t NumOfBlocks);
uint8_t BSP_SD_Erase(uint64_t StartAddr, uint64_t EndAddr);
HAL_SD_TransferStateTypedef BSP_SD_GetStatus(void);
void    BSP_SD_GetCardInfo(HAL_SD_CardInfoTypedef *CardInfo);
uint8_t BSP_SD_IsDetected(void);

/* These __weak function can be surcharged by application code in case the current settings (e.g. DMA stream)
   need to be changed for specific needs */
void    BSP_SD_MspInit(SD_HandleTypeDef *hsd, void *Params);
void    BSP_SD_Detect_MspInit(SD_HandleTypeDef *hsd, void *Params);
void    BSP_SD_MspDeInit(SD_HandleTypeDef *hsd, void *Params);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32469I_DISCOVERY_SD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
