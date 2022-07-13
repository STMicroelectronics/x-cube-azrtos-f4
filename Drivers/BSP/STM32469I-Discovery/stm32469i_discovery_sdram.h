/**
  ******************************************************************************
  * @file    stm32469i_discovery_sdram.h
  * @author  MCD Application Team
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32469i_discovery_sdram.c driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32469I_DISCOVERY_SDRAM_H
#define __STM32469I_DISCOVERY_SDRAM_H

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

/** @addtogroup STM32469I-Discovery_SDRAM
  * @{
  */

/** @defgroup STM32469I-Discovery_SDRAM_Exported_Types STM32469I Discovery SDRAM Exported Types
  * @{
  */

/**
  * @brief  SDRAM status structure definition
  */
#define   SDRAM_OK         ((uint8_t)0x00)
#define   SDRAM_ERROR      ((uint8_t)0x01)

/**
  * @}
  */

/** @defgroup STM32469I-Discovery_SDRAM_Exported_Constants STM32469I Discovery SDRAM Exported Constants
  * @{
  */
#define SDRAM_DEVICE_ADDR  ((uint32_t)0xC0000000)

 /* SDRAM device size in Bytes */
 #define SDRAM_DEVICE_SIZE  ((uint32_t)0x1000000)

#define SDRAM_MEMORY_WIDTH FMC_SDRAM_MEM_BUS_WIDTH_32
#define SDCLOCK_PERIOD     FMC_SDRAM_CLOCK_PERIOD_2

/* SDRAM refresh counter (90 MHz SD clock) */
#define REFRESH_COUNT       ((uint32_t)0x0569)
#define  SDRAM_TIMEOUT      ((uint32_t)0xFFFF)

/* DMA definitions for SDRAM DMA transfer */
#define __DMAx_CLK_ENABLE     __HAL_RCC_DMA2_CLK_ENABLE
#define __DMAx_CLK_DISABLE    __HAL_RCC_DMA2_CLK_DISABLE
#define SDRAM_DMAx_CHANNEL    DMA_CHANNEL_0
#define SDRAM_DMAx_STREAM     DMA2_Stream0
#define SDRAM_DMAx_IRQn       DMA2_Stream0_IRQn
#define SDRAM_DMAx_IRQHandler DMA2_Stream0_IRQHandler


/**
  * @brief  FMC SDRAM Mode definition register defines
  */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)
/**
  * @}
  */

/** @defgroup STM32469I-Discovery_SDRAM_Exported_Macro STM32469I Discovery SDRAM Exported Macro
  * @{
  */
/**
  * @}
  */

/** @addtogroup STM32469I_Discovery_SDRAM_Exported_Functions 
  * @{
  */
uint8_t BSP_SDRAM_Init(void);
uint8_t BSP_SDRAM_DeInit(void);
void    BSP_SDRAM_Initialization_sequence(uint32_t RefreshCount);
uint8_t BSP_SDRAM_ReadData(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);
uint8_t BSP_SDRAM_ReadData_DMA(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);
uint8_t BSP_SDRAM_WriteData(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);
uint8_t BSP_SDRAM_WriteData_DMA(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);
uint8_t BSP_SDRAM_Sendcmd(FMC_SDRAM_CommandTypeDef *SdramCmd);
void    BSP_SDRAM_DMA_IRQHandler(void);

/* These function can be modified in case the current settings (e.g. DMA stream)
   need to be changed for specific application needs */
void    BSP_SDRAM_MspInit(SDRAM_HandleTypeDef  *hsdram, void *Params);
void    BSP_SDRAM_MspDeInit(SDRAM_HandleTypeDef  *hsdram, void *Params);

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

#endif /* __STM32469I_DISCOVERY_SDRAM_H */
