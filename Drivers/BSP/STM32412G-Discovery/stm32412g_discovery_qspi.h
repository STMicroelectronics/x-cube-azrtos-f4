/**
  ******************************************************************************
  * @file    stm32412g_discovery_qspi.h
  * @author  MCD Application Team
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32412g_discovery_qspi.c driver.
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

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32412G_DISCOVERY
  * @{
  */
    
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32412G_DISCOVERY_QSPI_H
#define __STM32412G_DISCOVERY_QSPI_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "../Components/n25q128a/n25q128a.h"

/** @addtogroup STM32412G_DISCOVERY_QSPI
  * @{
  */    

  
/* Exported constants --------------------------------------------------------*/ 
/** @defgroup STM32412G_DISCOVERY_QSPI_Exported_Constants STM32412G Discovery QSPI Exported Constants
  * @{
  */
/* QSPI Error codes */
#define QSPI_OK            ((uint8_t)0x00)
#define QSPI_ERROR         ((uint8_t)0x01)
#define QSPI_BUSY          ((uint8_t)0x02)
#define QSPI_NOT_SUPPORTED ((uint8_t)0x04)
#define QSPI_SUSPENDED     ((uint8_t)0x08)


/* Definition for QSPI clock resources */
#define QSPI_CLK_ENABLE()           __HAL_RCC_QSPI_CLK_ENABLE()
#define QSPI_CLK_DISABLE()          __HAL_RCC_QSPI_CLK_DISABLE()
#define QSPI_CS_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOG_CLK_ENABLE()
#define QSPI_CS_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOG_CLK_DISABLE()
#define QSPI_CLK_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define QSPI_CLK_GPIO_CLK_DISABLE() __HAL_RCC_GPIOB_CLK_DISABLE()
#define QSPI_Dx_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOF_CLK_ENABLE()
#define QSPI_Dx_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOF_CLK_DISABLE()

#define QSPI_FORCE_RESET()          __HAL_RCC_QSPI_FORCE_RESET()
#define QSPI_RELEASE_RESET()        __HAL_RCC_QSPI_RELEASE_RESET()

/* Definition for QSPI Pins */
#define QSPI_CS_PIN                GPIO_PIN_6
#define QSPI_CS_GPIO_PORT          GPIOG
#define QSPI_CLK_PIN               GPIO_PIN_2
#define QSPI_CLK_GPIO_PORT         GPIOB
#define QSPI_D0_PIN                GPIO_PIN_8
#define QSPI_D0_GPIO_PORT          GPIOF
#define QSPI_D1_PIN                GPIO_PIN_9
#define QSPI_D1_GPIO_PORT          GPIOF
#define QSPI_D2_PIN                GPIO_PIN_7
#define QSPI_D2_GPIO_PORT          GPIOF
#define QSPI_D3_PIN                GPIO_PIN_6
#define QSPI_D3_GPIO_PORT          GPIOF

/* N25Q128A13EF840F Micron memory */
/* Size of the flash */
#define QSPI_FLASH_SIZE            23     /* Address bus width to access whole memory space */
#define QSPI_PAGE_SIZE             256

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup STM32412G_DISCOVERY_QSPI_Exported_Types STM32412G Discovery QSPI Exported Types
  * @{
  */
/* QSPI Info */
typedef struct {
  uint32_t FlashSize;          /*!< Size of the flash */
  uint32_t EraseSectorSize;    /*!< Size of sectors for the erase operation */
  uint32_t EraseSectorsNumber; /*!< Number of sectors for the erase operation */
  uint32_t ProgPageSize;       /*!< Size of pages for the program operation */
  uint32_t ProgPagesNumber;    /*!< Number of pages for the program operation */
} QSPI_Info;

/**
  * @}
  */

  
/* Exported functions --------------------------------------------------------*/
/** @defgroup STM32412G_DISCOVERY_QSPI_Exported_Functions STM32412G Discovery QSPI Exported Functions
  * @{
  */  
uint8_t BSP_QSPI_Init       (void);
uint8_t BSP_QSPI_DeInit     (void);
uint8_t BSP_QSPI_Read       (uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
uint8_t BSP_QSPI_Write      (uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
uint8_t BSP_QSPI_Erase_Block(uint32_t BlockAddress);
uint8_t BSP_QSPI_Erase_Chip (void);
uint8_t BSP_QSPI_GetStatus  (void);
uint8_t BSP_QSPI_GetInfo    (QSPI_Info* pInfo);
uint8_t BSP_QSPI_EnableMemoryMappedMode(void);
/* BSP Aliased function maintained for legacy purpose */
#define BSP_QSPI_MemoryMappedMode      BSP_QSPI_EnableMemoryMappedMode

/* These functions can be modified in case the current settings
   need to be changed for specific application needs */
void BSP_QSPI_MspInit(QSPI_HandleTypeDef *hqspi, void *Params);
void BSP_QSPI_MspDeInit(QSPI_HandleTypeDef *hqspi, void *Params);

/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __STM32412G_DISCOVERY_QSPI_H */
/**
  * @}
  */ 

/**
  * @}
  */ 
