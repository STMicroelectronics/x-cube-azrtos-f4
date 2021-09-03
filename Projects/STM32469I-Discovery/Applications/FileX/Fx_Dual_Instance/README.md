##  <b>Fx_Dual_Instance application description</b>

This application provides an example of Azure RTOS FileX stack usage on STM32F469I-Discovery board. It demonstrate the coexistence capability of two FileX/LevelX instances running independently.

Two independent media storage devices: µSD and QSPI NOR Flash will be used on the STM32F469I-Discovery board.

The main entry function, tx_application_define(), is called by ThreadX during kernel start. At this stage, all FileX/LevelX resources are initialized, the SD card detection event is registered and both media storage drivers (SDIO and QSPI) are initialized.
The application creates 2 threads with the same priorities. Each thread will create its own file system using one instance:

  - fx_thread_one_entry (Prio : 10; PreemptionPrio : 10) used to create file system on µSD using FileX stack.

  - fx_thread_two_entry (Prio : 10; PreemptionPrio : 10) used to create file system on QSPI NOR Flash using FileX/LevelX stacks.

The fx_thread_one_entry uses FileX services to open the SD media for file operations and attempt to create file STM32.TXT. If the file exists already, it will be overwritten. Simple string data content is then written into the file and it is closed. The file is reopened in read mode to check the content integrity.

The fx_thread_two_entry will start by formatting the NOR Flash using FileX services. The resulting file system is a FAT32 compatible, with 512 bytes per sector and 8 sectors per cluster. Optionally, the NOR flash can be erased prior to format, this allows LevelX and FileX to create a clean FAT FileSystem. Chip erase operation takes considerable time to finish whole flash reset, therefore it is disabled by default. To enable it, please set the following flags in "lx_stm32_qspi_driver.h":

  - LX_DRIVER_CALLS_QSPI_INIT
  - LX_DRIVER_ERASES_QPSI_AFTER_INIT

Upon successful opening of the flash media, FileX continue with creating a file called "STM32.TXT" into the root directory, then write into it some simple string data. Then file is re-opened in read only mode and the content is checked.

Through all the steps, FileX/LevelX services are called to print (using USRAT3) the flash size available before and after the example file is written into the flash. The number of occupied sectors is also shown.

<b>Note</b>:
  - A FAT32 compatible SD card is expected to be used with this example. The program will start file operations without formatting the media, so all user related files are kept.

  - The provided HAL Polling based implementation for QuadSPI component N25Q128A, assumes the following settings are set:

  QuadSPI Mode: Bank1 with QuadSPI Lines
  ClockPrescaler = 1;
  FifoThreshold = 1;
  SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  FlashSize = 23;
  ChipSelectHighTime = QSPI_CS_HIGH_TIME_5_CYCLE;
  ClockMode = QSPI_CLOCK_MODE_0;
  FlashID = QSPI_FLASH_ID_1;
  DualFlash = QSPI_DUALFLASH_DISABLE;

    Different configuration can be used but need to be reflected in the implementation guarded with QSPI_HAL_CFG_xxx user tags.

#### <b>Expected success behavior</b>

  - A file named STM32.TXT should be visible in the root directory of the SD card.
  - A blinking green LED light marks the success of uSD file operations.
  - Successful NOR Flash operation is also marked by a toggeling blue LED.
  - Information regarding the actual working thread, the status of uSD Card and the total and available size of the flash media is printed to the serial port(USART3).

#### <b> Error behaviors</b>

  - On failure, the red LED should start blinking and both green and blue LEDs are off.
  - Error handler is called at the spot where the error occurred.

#### <b>Assumptions if any</b>

- The “SD hot-blug detection” is not supported due to a problem in the HAL/SDMMC driver. As soon as the issue is fixed, the application will be updated.

#### <b>Known limitations</b>
None

#### <b>ThreadX usage hints</b>

 - ThreadX uses the Systick as time base, thus it is mandatory that the HAL uses a separate time base through the TIM IPs.
 - ThreadX is configured with 100 ticks/sec by default, this should be taken into account when using delays or timeouts at application. It is always possible to reconfigure it in the "tx_user.h", the "TX_TIMER_TICKS_PER_SECOND" define,but this should be reflected in "tx_initialize_low_level.s" file too.
 - ThreadX is disabling all interrupts during kernel start-up to avoid any unexpected behavior, therefore all system related calls (HAL, BSP) should be done either at the beginning of the application or inside the thread entry functions.
 - ThreadX offers the "tx_application_define()" function, that is automatically called by the tx_kernel_enter() API.
   It is highly recommended to use it to create all applications ThreadX related resources (threads, semaphores, memory pools...)  but it should not in any way contain a system API call (HAL or BSP).
 - Using dynamic memory allocation requires to apply some changes to the linker file.
   ThreadX needs to pass a pointer to the first free memory location in RAM to the tx_application_define() function, using the "first_unused_memory" argument.
   This require changes in the linker files to expose this memory location.
    + For EWARM add the following section into the .icf file:
     ```
	 place in RAM_region    { last section FREE_MEM };
	 ```
    + For MDK-ARM:
	```
    either define the RW_IRAM1 region in the ".sct" file
    or modify the line below in "tx_low_level_initilize.s to match the memory region being used
        LDR r1, =|Image$$RW_IRAM1$$ZI$$Limit|
	```
    + For STM32CubeIDE add the following section into the .ld file:
	```
    ._threadx_heap :
      {
         . = ALIGN(8);
         __RAM_segment_used_end__ = .;
         . = . + 64K;
         . = ALIGN(8);
       } >RAM_D1 AT> RAM_D1
	```

       The simplest way to provide memory for ThreadX is to define a new section, see ._threadx_heap above.
       In the example above the ThreadX heap size is set to 64KBytes.
       The ._threadx_heap must be located between the .bss and the ._user_heap_stack sections in the linker script.
       Caution: Make sure that ThreadX does not need more than the provided heap memory (64KBytes in this example).
       Read more in STM32CubeIDE User Guide, chapter: "Linker script".

    + The "tx_initialize_low_level.s" should be also modified to enable the "USE_DYNAMIC_MEMORY_ALLOCATION" flag.


#### <b>FileX/LevelX usage hints</b>

- When calling the fx_media_format() API, it is highly recommended to understand all the parameters used by the API to correctly generate a valid filesystem.
- When calling the fx_media_format() API, NOR sector size is always 512 bytes.
- FileX is using data buffers, passed as arguments to fx_media_open(), fx_media_read() and fx_media_write() API it is recommended that these buffers are multiple of sector size and "4 bytes" aligned to avoid unalgined access issues.

### <b>Keywords</b>

RTOS, ThreadX, FileX, LevelX, File system, NOR, SDMMC, QSPI, FAT32

### <b>Hardware and Software environment</b>

  - This application runs on STM32F469xx devices.
  - This application has been tested with STMicroelectronics STM32F469I-Discovery boards Revision: MB1189 B-03.
    and can be easily tailored to any other supported device and development board.

  - This application uses USART3 to display Cortex-M4 logs, the hyperterminal configuration is as follows:
      - BaudRate = 115200 baud
      - Word Length = 8 Bits
      - Stop Bit = 1
      - Parity = None
      - Flow control = None

###  <b>How to use it ?</b>

In order to make the program work, you must do the following :

  - Open your preferred toolchain
  - Rebuild all files and load your image into target memory
  - Run the application


