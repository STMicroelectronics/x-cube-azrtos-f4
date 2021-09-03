
## <b>Tx_CMSIS_Wrapper application description</b> 

This application provides an example of CMSIS RTOS adaptation layer for Azure RTOS ThreadX, it shows how to develop an application using the CMSIS RTOS 2 APIs.
It demonstrates how to create multiple threads using CMSIS RTOS 2 for ThreadX APIs. 
At the main function, the application creates 2 threads with the same priority which execute in a periodic cycle of 15 seconds : 

  - 'ThreadOne' (Priority : osPriorityNormal)
  - 'ThreadTwo' (Priority : osPriorityNormal)

The function "Led_Toggle()" is the entry function for both threads to toggle the leds.Therefore it is considered as a "critical section" that needs protection with a 'SyncObject' flag in the file "app_tx_cmsisrtos.h"
Each thread is running in an infinite loop as following:

- 'ThreadOne':
  + try to acquire the 'SyncObject' immediately.
  + On Success toggle the 'LED_GREEN' each 500ms for 5 seconds.
  + Release the 'SyncObject'
  + Sleep for 10ms.
  + repeat the steps above

- 'ThreadTwo':
  + try to acquire the 'SyncObject' immediately.
  + On Success toggle the 'LED_RED' each 500ms for 5 seconds.
  + Release the 'SyncObject'
  + Sleep for 10ms.
  + Repeat the steps above.

By default the 'SyncObject' is defined as  "osMutexId_t" .It is possible to use a semaphore "osSemaphoreId_t" by tuning
the compile flags in the file "app_tx_cmsisrtos.h".

####  <b>Expected success behavior</b>

  - 'LED_GREEN' toggles every 500ms for 5 seconds
  - 'LED_RED' toggles every 500ms for 5 seconds
  - Messages on HyperTerminal : 
     + "** ThreadXXX : waiting for SyncObject !! **" : When thread is waiting for the SyncObject.
	 + "** ThreadXXX : waiting SyncObject released **" : When thread put the SyncObject.
	 + "** ThreadXXX : waiting SyncObject acquired **" : When thread get the SyncObject.

#### <b>Error behaviors</b>

'LED_RED' toggles every 1 second if any error occurs.

#### <b>Assumptions if any</b>
None

#### <b>Known limitations</b>
None
    
#### <b>ThreadX usage hints</b>

 - ThreadX uses the Systick as time base, thus it is mandatory that the HAL uses a separate time base through the TIM IPs.
 - ThreadX is configured with 100 ticks/sec by default, this should be taken into account when using delays or timeouts at application. It is always possible to reconfigure it in the "tx_user.h", the "TX_TIMER_TICKS_PER_SECOND" define,but this should be reflected in "tx_initialize_low_level.s" file too.
 - ThreadX is disabling all interrupts during kernel start-up to avoid any unexpected behavior, therefore all system related calls (HAL, BSP) should be done either at the beginning of the application or inside the thread entry functions.
 - ThreadX offers the "tx_application_define()" function, that is automatically called by the tx_kernel_enter() API.
   It is highly recommended to use it to create all applications ThreadX related resources (threads, semaphores, memory pools...)  but it should not in any way contain a system API call (HAL or BSP).
 - Using dynamic memory allocation requires to apply some changes to the linker file.
   ThreadX needs to pass a pointer to the first free memory location in RAM to the tx_application_define() function,
   using the "first_unused_memory" argument.
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
         
### <b>Keywords</b>

RTOS, ThreadX, Thread, CMSIS RTOS, Semaphore, Mutex



### <b>Hardware and Software environment</b>

  - This example runs on STM32F469xxx devices
  - This example has been tested with STMicroelectronics STM32F469I-Discovery boards Revision: MB1189 B-03.
    and can be easily tailored to any other supported device and development board.
  - A virtual COM port appears in the HyperTerminal:
      - Hyperterminal configuration:
        + Data Length = 8 Bits
        + One Stop Bit
        + No parity
        + BaudRate = 115200 baud
        + Flow control: None


### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files 
 - Load images into target memory
 - Run the application
