/**
  ******************************************************************************
  * @file    sd_conf.h
  * @author  fpiSTM
  * @date    2017
  * @brief   This file contains hw config for SD
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SD_CONF_H
#define __SD_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32_def.h"

#define SD_DATATIMEOUT           ((uint32_t)100000000)

/*SD-detect signal */
#define SD_DETECT_PIN                        GPIO_PIN_10
#define SD_DETECT_GPIO_PORT                  GPIOG
#define SD_DETECT_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOG_CLK_ENABLE()
#define SD_DETECT_GPIO_CLK_DISABLE()         __HAL_RCC_GPIOG_CLK_DISABLE()
#define SD_DETECT_EXTI_IRQn                  EXTI2_IRQn

/* Definition for BSP SD */
#define SD_INSTANCE                          SDIO

#define SD_CLK_ENABLE                        __HAL_RCC_SDIO_CLK_ENABLE
#define SD_CLK_DISABLE                       __HAL_RCC_SDIO_CLK_DISABLE
#define SD_CLK_EDGE                          SDIO_CLOCK_EDGE_RISING
#define SD_CLK_BYPASS                        SDIO_CLOCK_BYPASS_DISABLE
#define SD_CLK_PWR_SAVE                      SDIO_CLOCK_POWER_SAVE_DISABLE
#define SD_BUS_WIDE_1B                       SDIO_BUS_WIDE_1B
#define SD_BUS_WIDE_4B                       SDIO_BUS_WIDE_4B
#define SD_HW_FLOW_CTRL                      SDIO_HARDWARE_FLOW_CONTROL_ENABLE
#define SD_CLK_DIV                           SDIO_TRANSFER_CLK_DIV

/* Definition for MSP SD */
#define SD_AF                                GPIO_AF12_SDIO


#ifdef __cplusplus
}
#endif

#endif /* __SD_CONF_H */
