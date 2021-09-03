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
#include "nx_web_http_server.h"
#include "app_filex.h"
#include "tx_thread.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define PRINT_APP_START(test)            do { \
                                              printf("%s Application started..\n\n", #test);\
                                            } while(0)

#define PRINT_IP_ADDRESS(addr) do { \
                                    printf("%s: %lu.%lu.%lu.%lu \n", #addr, \
                                    (addr >> 24) & 0xff, \
                                    (addr >> 16) & 0xff, \
                                    (addr >> 8) & 0xff, \
                                     addr& 0xff);\
                                  }while(0)
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
UINT MX_NetXDuo_Init(VOID *memory_ptr);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* Pirority IP creation */
#define DEFAULT_MEMORY_SIZE              1024
#define DEFAULT_MAIN_PRIORITY            10
#define TOGGLE_LED_PRIORITY              15 
#define DEFAULT_PRIORITY                 5
 /*Packet payload size */
#define PACKET_PAYLOAD_SIZE              1536
/* Packet pool size */
#define NX_PACKET_POOL_SIZE             ((1536 + sizeof(NX_PACKET)) * 50)
 /* APP Cache size  */
#define ARP_CACHE_SIZE                   1024
 /* Wait option for getting @IP */
#define WAIT_OPTION                      1000
/* Entry input for Main thread */
#define ENTRY_INPUT                      0
/* Main Thread priority */
#define THREAD_PRIO                      4
/* Main Thread preemption threshold */
#define THREAD_PREEMPT_THRESHOLD         4
/* Web application size */
#define WEB_APP_SIZE                     2048
/* Memory size */
#define MEMORY_SIZE                      2048
/* HTTP connection port */
#define CONNECTION_PORT                  80
/* Server packet size */
#define SERVER_PACKET_SIZE               (NX_WEB_HTTP_SERVER_MIN_PACKET_SIZE * 2)
/* Server stack */
#define SERVER_STACK                     4096
/* Default value 16GB */
#define SIZE_16GB                        16777216
/* LED state */
#define LED_ON                           "led=ON"
#define LED_OFF                          "led=OFF"
#define LED_TOGGLE                       "led=TOGGLE"
#define THREAD_CNT_CMD                   "/Get_THREAD_COUNT"
/* Server pool size */
#define SERVER_POOL_SIZE                 (SERVER_PACKET_SIZE * 4)
/* SD Driver information pointer */
#define SD_DRIVER_INFO_POINTER           0

#define NULL_IP_ADDRESS                  IP_ADDRESS(0,0,0,0)
/* USER CODE END PD */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /* __APP_NETXDUO_H__ */
