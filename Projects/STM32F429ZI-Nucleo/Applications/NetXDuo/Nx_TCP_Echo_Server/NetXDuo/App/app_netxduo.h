/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_netxduo.h
  * @author  MCD Application Team
  * @brief   NetXDuo applicative header file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_NETXDUO_H__
#define __APP_NETXDUO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "nx_api.h"

/* Private includes ----------------------------------------------------------*/
#include "nx_stm32_eth_driver.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "main.h"
#include "nxd_dhcp_client.h"
#include "stm32f4xx_nucleo_144.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define PRINT_IP_ADDRESS(addr)             do { \
                                                printf("STM 32 %s: %lu.%lu.%lu.%lu \n", #addr, \
                                                (addr >> 24) & 0xff, \
                                                (addr >> 16) & 0xff, \
                                                (addr >> 8) & 0xff, \
                                                addr& 0xff);\
                                           }while(0)

#define PRINT_DATA(addr, port, data)       do { \
                                                printf("[%lu.%lu.%lu.%lu:%u] -> '%s' \n", \
                                                (addr >> 24) & 0xff, \
                                                (addr >> 16) & 0xff, \
                                                (addr >> 8) & 0xff,  \
                                                (addr & 0xff), port, data); \
                                           } while(0)

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
UINT MX_NetXDuo_Init(VOID *memory_ptr);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PAYLOAD_SIZE             1536
#define NX_PACKET_POOL_SIZE      (( PAYLOAD_SIZE + sizeof(NX_PACKET)) * 10)

#define DEFAULT_MEMORY_SIZE      1024
#define DEFAULT_PRIORITY         10
#define WINDOW_SIZE              512

#define NULL_ADDRESS             0

#define DEFAULT_PORT             6000
#define MAX_TCP_CLIENTS          1
/* USER CODE END PD */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /* __APP_NETXDUO_H__ */
