/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_filex.c
  * @author  MCD Application Team
  * @brief   FileX applicative file
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

/* Includes ------------------------------------------------------------------*/
#include "app_filex.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define FILEX_DEFAULT_STACK_SIZE               2048

/* Thread_0 priority */
#define DEFAULT_THREAD_PRIO                    10

/* Thread_0 preemption priority */
#define DEFAULT_PREEMPTION_THRESHOLD           DEFAULT_THREAD_PRIO
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
/* Buffer for FileX FX_MEDIA sector cache. */
ULONG media_memory[4096];

/* Define FileX global data structures.  */
FX_MEDIA        nor_flash_disk;
FX_FILE         fx_file;

/* Define ThreadX global data structures.  */
TX_THREAD       fx_thread;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void fx_thread_entry(ULONG thread_input);
void Error_Handler(void);
/* USER CODE END PFP */

/**
  * @brief  Application FileX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT MX_FileX_Init(VOID *memory_ptr)
{
  UINT ret = FX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

  /* USER CODE BEGIN MX_FileX_MEM_POOL */

  /* USER CODE END MX_FileX_MEM_POOL */

  /* USER CODE BEGIN MX_FileX_Init */

  CHAR *pointer;

  ret = tx_byte_allocate(byte_pool, (VOID **) &pointer, FILEX_DEFAULT_STACK_SIZE, TX_NO_WAIT);

  /* Check FILEX_DEFAULT_STACK_SIZE allocation*/
  if (ret != FX_SUCCESS)
  {
    Error_Handler();
  }

  /* Create the main thread.  */
  ret = tx_thread_create(&fx_thread, "thread 0", fx_thread_entry, 0, pointer, FILEX_DEFAULT_STACK_SIZE,
                          DEFAULT_THREAD_PRIO, DEFAULT_PREEMPTION_THRESHOLD, TX_NO_TIME_SLICE, TX_AUTO_START);

  /* Check main thread creation */
  if (ret != FX_SUCCESS)
  {
    Error_Handler();
  }

  /* Initialize FileX.  */
  fx_system_initialize();

  /* USER CODE END MX_FileX_Init */
  return ret;
}

/* USER CODE BEGIN 1 */

void fx_thread_entry(ULONG thread_input)
{

  UINT status;
  ULONG available_space_pre;
  ULONG available_space_post;
  ULONG bytes_read;
  CHAR read_buffer[32];
  CHAR data[] = "This is FileX working on STM32";

  printf("[STM32F469I-DISCO]: FileX/LevelX NOR QUAD-SPI Application Start.\n");

  /* Print the absolute size of the NOR chip*/
  printf("[STM32F469I-DISCO]: Total NOR Flash Chip size is: %lu bytes.\n", (unsigned long)N25Q128A_FLASH_SIZE);

  /* Format the NOR flash as FAT */
  status =  fx_media_format(&nor_flash_disk,
                            fx_stm32_levelx_nor_driver,   // Driver entry
                            (VOID*)LX_NOR_QSPI_DRIVER_ID, // Device info pointer
                            (UCHAR*)media_memory,                 // Media buffer pointer
                            sizeof(media_memory),         // Media buffer size
                            "NOR_FLASH_DISK",             // Volume Name
                            1,                            // Number of FATs
                            32,                           // Directory Entries
                            0,                            // Hidden sectors
                            N25Q128A_FLASH_SIZE/512,      // Total sectors
                            512,                          // Sector size
                            8,                            // Sectors per cluster
                            1,                            // Heads
                            1);                           // Sectors per track

  /* Check if the format status */
  if (status != FX_SUCCESS)
  {
    Error_Handler();
  }

  /* Open the QUAD-SPI NOR Flash disk driver.  */
  status =  fx_media_open(&nor_flash_disk, "FX_LX_NOR_DISK", fx_stm32_levelx_nor_driver,(VOID*)LX_NOR_QSPI_DRIVER_ID , media_memory, sizeof(media_memory));

  /* Check the media open status.  */
  if (status != FX_SUCCESS)
  {
    Error_Handler();
  }

  /* Get the available usable space */
  status =  fx_media_space_available(&nor_flash_disk, &available_space_pre);

  /* Check the get available state request status.  */
  if (status != FX_SUCCESS)
  {
    Error_Handler();
  }

  printf("[STM32F469I-DISCO]: User available NOR Flash disk space size before file is written: %lu bytes.\n", available_space_pre);

  /* Create a file called STM32.TXT in the root directory.  */
  status =  fx_file_create(&nor_flash_disk, "STM32.TXT");

  /* Check the create status.  */
  if (status != FX_SUCCESS)
  {
    /* Check for an already created status. This is expected on the
    second pass of this loop!  */
    if (status != FX_ALREADY_CREATED)
    {
      /* Create error, call error handler.  */
      Error_Handler();
    }
  }

  /* Open the test file.  */
  status =  fx_file_open(&nor_flash_disk, &fx_file, "STM32.TXT", FX_OPEN_FOR_WRITE);

  /* Check the file open status.  */
  if (status != FX_SUCCESS)
  {
    /* Error opening file, call error handler.  */
    Error_Handler();
  }

  /* Seek to the beginning of the test file.  */
  status =  fx_file_seek(&fx_file, 0);

  /* Check the file seek status.  */
  if (status != FX_SUCCESS)
  {
    /* Error performing file seek, call error handler.  */
    Error_Handler();
  }

  status =  fx_file_write(&fx_file, data, sizeof(data));

  /* Check the file write status.  */
  if (status != FX_SUCCESS)
  {
    /* Error writing to a file, call error handler.  */
    Error_Handler();
  }

  /* Close the test file.  */
  status =  fx_file_close(&fx_file);

  /* Check the file close status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, call error handler.  */
    Error_Handler();
  }

  status = fx_media_flush(&nor_flash_disk);

  /* Check the media flush  status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, call error handler.  */
    Error_Handler();
  }

  /* Open the test file.  */
  status =  fx_file_open(&nor_flash_disk, &fx_file, "STM32.TXT", FX_OPEN_FOR_READ);

  /* Check the file open status.  */
  if (status != FX_SUCCESS)
  {
    /* Error opening file, call error handler.  */
    Error_Handler();
  }

  /* Seek to the beginning of the test file.  */
  status =  fx_file_seek(&fx_file, 0);

  /* Check the file seek status.  */
  if (status != FX_SUCCESS)
  {
    /* Error performing file seek, call error handler.  */
    Error_Handler();
  }

  /* Read the first 31 bytes of the test file.  */
  status =  fx_file_read(&fx_file, read_buffer, sizeof(data), &bytes_read);

  /* Check the file read status.  */
  if ((status != FX_SUCCESS) || (bytes_read != sizeof(data)))
  {
    /* Error reading file, call error handler.  */
    Error_Handler();
  }

  /* Close the test file.  */
  status =  fx_file_close(&fx_file);

  /* Check the file close status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the file, call error handler.  */
    Error_Handler();
  }

  /* Get the available usable space, after the file has been created */
  status =  fx_media_space_available(&nor_flash_disk, &available_space_post);

  /* Check the get available state request status.  */
  if (status != FX_SUCCESS)
  {
    Error_Handler();
  }

  printf("[STM32F469I-DISCO]: User available NOR Flash disk space size after file is written: %lu bytes.\n", available_space_post);
  printf("[STM32F469I-DISCO]: The test file occupied a total of %lu cluster(s) (%u per cluster).\n",
         (available_space_pre - available_space_post) / (nor_flash_disk.fx_media_bytes_per_sector * nor_flash_disk.fx_media_sectors_per_cluster),
         nor_flash_disk.fx_media_bytes_per_sector * nor_flash_disk.fx_media_sectors_per_cluster);

  /* Close the media.  */
  status =  fx_media_close(&nor_flash_disk);

  /* Check the media close status.  */
  if (status != FX_SUCCESS)
  {
    /* Error closing the media, call error handler.  */
    Error_Handler();
  }

  while(1)
  {
    BSP_LED_Toggle(LED_GREEN);
    tx_thread_sleep(40);
  }

}

/* USER CODE END 1 */
