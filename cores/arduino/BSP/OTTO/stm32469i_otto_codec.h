/**
  ******************************************************************************
  * @file    stm32469i_otto_codec.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    04-Oct-2016
  * @brief   This file includes the definitions for I2C codec handler
  *          for STM32469I-otto board.
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
#ifndef __STM32469I_OTTO_CODEC_H
#define __STM32469I_OTTO_CODEC_H

#ifdef __cplusplus
 extern "C" {
#endif

 /* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"


/* Exported constant IO ------------------------------------------------------*/

/**
  * @brief Audio I2C Slave address
  */
#define AUDIO_I2C_ADDRESS                ((uint16_t)0x34)


/**
  * @brief I2C clock speed configuration (in Hz)
  * WARNING:
  * Make sure that this define is not already declared in other files
  * It can be used in parallel by other modules.
  */
#ifndef I2C_SCL_FREQ_KHZ
#define I2C_SCL_FREQ_KHZ                  400000 /*!< f(I2C_SCL) = 400 kHz */
#endif /* I2C_SCL_FREQ_KHZ */

/**
  * @brief User can use this section to tailor I2Cx/I2Cx instance used and associated
  * resources.
  * Definition for I2Cx clock resources
  */
#define EVAL_I2Cx                             HAL_I2C2
#define EVAL_I2Cx_CLK_ENABLE()                __HAL_RCC_I2C2_CLK_ENABLE()
#define EVAL_DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define EVAL_I2Cx_SCL_SDA_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOH_CLK_ENABLE()

#define EVAL_I2Cx_FORCE_RESET()               __HAL_RCC_I2C2_FORCE_RESET()
#define EVAL_I2Cx_RELEASE_RESET()             __HAL_RCC_I2C2_RELEASE_RESET()

/** @brief Definition for I2Cx Pins
  */
#define EVAL_I2Cx_SCL_PIN                     GPIO_PIN_4 /*!< PH4 */
#define EVAL_I2Cx_SCL_SDA_GPIO_PORT           HAL_GPIOH
#define EVAL_I2Cx_SCL_SDA_AF                  GPIO_AF4_I2C2
#define EVAL_I2Cx_SDA_PIN                     GPIO_PIN_5 /*!< PH5 */

/** @brief Definition of I2C interrupt requests
  */
#define EVAL_I2Cx_EV_IRQn                     I2C2_EV_IRQn
#define EVAL_I2Cx_ER_IRQn                     I2C2_ER_IRQn

/**
  * @}
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL_Exported_Macros STM32469I EVAL Low Level Exported Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I_EVAL_LOW_LEVEL_Exported_Functions STM32469I EVAL Low Level Exported Functions
  * @{
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

/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* __STM32469I_OTTO_CODEC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
