
## <b>Tx_LowPower application description</b>

This application provides an example of Azure RTOS ThreadX stack usage, it shows how to develop an application using the ThreadX low power APIs when coupled with STM32F4xx low power profiles.

It demonstrates how to enter the Stop mode by the ThreadX, and wake up from this mode by using a push-button as a wakeup source.

After peripheral initialization, the main entry function tx_application_define() is called by ThreadX during kernel start, at this stage, the application creates one thread with the following priority :

  - MainThread (Prio : 10; Preemption Threshold : 10)

The <b>MainThread</b> starts, by getting the semaphore that didn't incremented yet.
So, as there is no other thread to be run in the TX scheduler, the ThreadX will decide to Enter into the <b>low power mode</b> (e.g. turn off peripherals and select stop mode).

The entry function into stop mode is defined by <b>tx_low_power_enter</b> which will put the processor into the effective Stop mode.

    - STOP Mode
     ============
           - Regulator in LP mode
           - HSE as SysClk after Wake Up
           - Flash Power Down in Stop mode
           - No IWDG
           - Wakeup using EXTI Line (User push-button PC.13)


When User push-button is pressed, an interrupt will occur that put the semaphore in the EXTI handler.

Then <b>tx_low_power_exit</b> will be called by ThreadX in which, it will configure the processor to exit the low power mode (e.g. turn on peripherals and re-configure SysClk), 

Now, the ThreadX will execute again the <b>MainThread</b> and LED_GRREN will toggle every 500ms for 5s,(as the semaphore is available this time).

Finally the program will enter again (after executing the <b>MainThread</b>) into stop mode.

This previous steps will run infinitely.

####  <b>Expected success behavior</b>

  - System start by entering to the Low Power mode
  - On push button, LED_GREEN toggles every 500ms for 5 seconds (Low Power mode Exit)
  - LED_GREEN turn Off to signal Low Power mode enter, and so on.

#### <b>Error behaviors</b>

LED_RED toggles every 500ms second if any error occurs.

#### <b>Assumptions if any</b>
None

#### <b>Known limitations</b>
None

### <b>Notes</b>

1. <b>tx_low_power_enter()</b> service enters low power mode.
For keeping track of time while in low power mode, there are two possibilities:

    1.1. A ThreadX timer is active: Function **tx_timer_get_next** returns **TX_TRUE**. Note that in this situation, a low power clock must be used in order to wake up the CPU for the next ThreadX timer expiration.

    Therefore an alternative clock must be programmed. Program the hardware timer source such that the next timer interrupt is equal to: *tx_low_power_next_expiration* tick_frequency. The *tick_frequency* is application-specific and typically set up in **tx_low_level_initialize**.

    1.2. There are no ThreadX timers active: Function **tx_timer_get_next** returns **TX_FALSE**.

       1.2.1. The application may choose not to keep the ThreadX internal
       tick count updated (define **TX_LOW_POWER_TICKLESS**), therefore there is no need
       to set up a low power clock.

       1.2.2. The application still needs to keep the ThreadX tick up-to-date. In this case a low power clock needs to be set up.

2. Entering Low-power mode through WFI will be executed only if no interrupt is pending.

3. The Debug Module must be stopped during STOP mode, otherwise, It will generate interrupts that cause the Wake-up of the system immediately after entering the Stop mode.

4. The user push-button interrupt priority must be set to the highest possible value, otherwise, after Exit Stop mode the processor will not execute the interrupt handler.

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

RTOS, ThreadX, Thread, PWR, Stop mode, Interrupt, EXTI, Wakeup, Low Power


### <b>Hardware and Software environment</b>

  - This application runs on STM32F429xx devices
  - This application has been tested with STMicroelectronics STM32F429ZI Nucleo boards Revision MB1137 B-01
    and can be easily tailored to any other supported device and development board.


###  <b>How to use it ?</b>

In order to make the program work, you must do the following:

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the application