/**
  ******************************************************************************
  * @file    stm32469i_eval_nor.h
  * @author  MCD Application Team
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32469i_eval_nor.c driver.
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
#ifndef __STM32469I_EVAL_NOR_H
#define __STM32469I_EVAL_NOR_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32469I_EVAL
  * @{
  */
    
/** @defgroup STM32469I-EVAL_NOR STM32469I EVAL NOR
  * @{
  */    

/** @defgroup STM32469I-EVAL_NOR_Exported_Types STM32469I EVAL NOR Exported Types
  * @{
  */
/**
  * @}
  */ 

/** @defgroup STM32469I-EVAL_NOR_Exported_Constants STM32469I EVAL NOR Exported Constants
  * @{
  */
/** 
  * @brief  NOR status structure definition  
  */     
#define   NOR_STATUS_OK         ((uint8_t) 0x00)
#define   NOR_STATUS_ERROR      ((uint8_t) 0x01)
#define NOR_DEVICE_ADDR  ((uint32_t)0x60000000)  
  
/* #define NOR_MEMORY_WIDTH    FMC_NORSRAM_MEM_BUS_WIDTH_8  */
#define NOR_MEMORY_WIDTH    FMC_NORSRAM_MEM_BUS_WIDTH_16

#define NOR_BURSTACCESS    FMC_BURST_ACCESS_MODE_DISABLE  
/* #define NOR_BURSTACCESS    FMC_BURST_ACCESS_MODE_ENABLE*/
  
#define NOR_WRITEBURST    FMC_WRITE_BURST_DISABLE  
/* #define NOR_WRITEBURST   FMC_WRITE_BURST_ENABLE */
 
#define CONTINUOUSCLOCK_FEATURE    FMC_CONTINUOUS_CLOCK_SYNC_ONLY 
/* #define CONTINUOUSCLOCK_FEATURE     FMC_CONTINUOUS_CLOCK_SYNC_ASYNC */ 

/* NOR operations Timeout definitions */
#define BLOCKERASE_TIMEOUT   ((uint32_t)0x00A00000)  /* NOR block erase timeout */
#define CHIPERASE_TIMEOUT    ((uint32_t)0x30000000)  /* NOR chip erase timeout  */ 
#define PROGRAM_TIMEOUT      ((uint32_t)0x00004400)  /* NOR program timeout     */ 

/* NOR Ready/Busy signal GPIO definitions */
#define NOR_READY_BUSY_PIN    GPIO_PIN_6 
#define NOR_READY_BUSY_GPIO   GPIOD
#define NOR_READY_STATE       GPIO_PIN_SET
#define NOR_BUSY_STATE        GPIO_PIN_RESET 
/**
  * @}
  */ 
    
/** @defgroup STM32469I-EVAL_NOR_Exported_Macro STM32469I EVAL NOR Exported Macro
  * @{
  */ 
/**
  * @}
  */ 
    
/** @defgroup STM32469I-EVAL_NOR_Exported_Functions STM32469I EVAL NOR Exported Functions
  * @{
  */  
uint8_t BSP_NOR_Init(void);
uint8_t BSP_NOR_DeInit(void);
uint8_t BSP_NOR_ReadData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_NOR_WriteData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_NOR_ProgramData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize);
uint8_t BSP_NOR_Erase_Block(uint32_t BlockAddress);
uint8_t BSP_NOR_Erase_Chip(void);
uint8_t BSP_NOR_Read_ID(NOR_IDTypeDef *pNOR_ID);
void BSP_NOR_ReturnToReadMode(void);  

/* These functions can be modified in case the current settings (e.g. DMA stream)
   need to be changed for specific application needs */
void BSP_NOR_MspInit(NOR_HandleTypeDef *hnor, void *Params);
uint8_t BSP_NOR_MspDeInit(NOR_HandleTypeDef *hnor, void *Params);
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

#endif /* __STM32469I_EVAL_NOR_H */
