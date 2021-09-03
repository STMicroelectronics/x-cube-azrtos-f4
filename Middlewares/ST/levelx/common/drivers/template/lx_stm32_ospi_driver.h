/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/

#ifndef LX_STM32_OSPI_DRIVER_H
#define LX_STM32_OSPI_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "lx_api.h"

#include "stm32NNxx_hal.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* the OctoSPI instance ,default value set to 0 */
#define LX_STM32_OSPI_INSTANCE                           0
#define LX_STM32_OSPI_DEFAULT_TIMEOUT                    10 * TX_TIMER_TICKS_PER_SECOND
#define LX_STM32_DEFAULT_SECTOR_SIZE                     4096 /* default block size */
#define LX_STM32_OSPI_DMA_API                            0
/* when set to 1 LevelX is initializing the OctoSPI memory, otherwise it is the up
   to the application to perform it
 */

#define LX_STM32_OSPI_INIT                              1
#if (LX_STM32_OSPI_INIT == 1)

/* allow the driver to fully erase the OctoSPI chip. This should be used carefully.
 * the call is blocking and takes a while. by default it is set to 0.
 */
#define LX_STM32_OSPI_ERASE  0
#endif

/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

#define LX_STM32_OSPI_CURRENT_TIME                              tx_time_get

#define LX_STM32_OSPI_POST_INIT()

#define LX_STM32_OSPI_PRE_READ_TRANSFER(__status__)

#define LX_STM32_OSPI_READ_CPLT_NOTIFY(__status__)

#define LX_STM32_OSPI_POST_READ_TRANSFER(__status__)

#define LX_STM32_OSPI_READ_TRANSFER_ERROR(__status__)

#define LX_STM32_OSPI_PRE_WRITE_TRANSFER(__status__)

#define LX_STM32_OSPI_WRITE_CPLT_NOTIFY(__status__)

#define LX_STM32_OSPI_POST_WRITE_TRANSFER(__status__)

#define LX_STM32_OSPI_WRITE_TRANSFER_ERROR(__status__)

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
INT lx_stm32_ospi_lowlevel_init(UINT instance);

INT lx_stm32_ospi_get_status(UINT instance);
INT lx_stm32_ospi_get_info(UINT instance, ULONG *block_size, ULONG *total_blocks);

INT lx_stm32_ospi_read(UINT instance, ULONG *address,ULONG *buffer, ULONG words);
INT lx_stm32_ospi_write(UINT instance, ULONG *address, ULONG *buffer, ULONG words);

INT lx_stm32_ospi_erase(UINT instance, ULONG block, ULONG erase_count, UINT full_chip_erase);
INT lx_stm32_ospi_is_block_erased(UINT instance, ULONG block);

__WEAK UINT  lx_ospi_driver_system_error(UINT error_code);

UINT lx_stm32_ospi_initialize(LX_NOR_FLASH *nor_flash);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /* LX_STM32_OSPI_DRIVER_H */
