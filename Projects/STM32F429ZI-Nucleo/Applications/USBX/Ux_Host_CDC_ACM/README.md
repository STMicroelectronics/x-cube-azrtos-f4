
## <b>Ux_Host_CDC_ACM Application Description </b>

This application provides an example of Azure RTOS USBX stack usage .

The application is designed to behave as an USB CDC_ACM Host, the code provides required requests to properly enumerate
CDC devices , CDC_ACM Class APIs to send or receive data and display data on uart HyperTerminal.

The main entry function tx_application_define() is then called by ThreadX during kernel start, at this stage, all USBx resources
are initialized.
The application creates 3 threads with different priorities :

  - usbx_app_thread_entry            (Priority : 25; Preemption threshold : 25) used to initialize USB OTG HAL HCD driver and start the Host.
  - cdc_acm_send_app_thread_entry    (Priority : 30; Preemption threshold : 30) used to send data from host to device.
  - cdc_acm_recieve_app_thread_entry (Priority : 30; Preemption threshold : 30) used to receive data from the device.

#### <b> Expected success behavior</b>

- When a cdc device is plugged to NUCLEO-F429ZI board, a Message will be displayed on the uart HyperTerminal (STlink VCP) showing
the Vendor ID and Product ID of the attached device. The host must be able to properly decode CDC_ACM class request data sent by the device.
After enumeration phase, a message will indicates that the device is ready for use.

- The Sent/received data are displayed on respective Hyperterminals.

#### <b>Error behaviors</b>

Errors are detected such as (Unsupported device, Enumeration Fail) and the corresponding message is displayed on the HyperTerminal.

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" Specification and CDC_ACM class Specification.

#### <b>Known limitations</b>
None

#### <b>ThreadX usage hints</b>

 - ThreadX uses the Systick as time base, thus it is mandatory that the HAL uses a separate time base through the TIM IPs.
 - ThreadX is configured with 100 ticks/sec by default, this should be taken into account when using delays or timeouts at application. It is always possible to reconfigure it in the "tx_user.h", the "TX_TIMER_TICKS_PER_SECOND" define,but this should be reflected in "tx_initialize_low_level.s" file too.
 - ThreadX is disabling all interrupts during kernel start-up to avoid any unexpected behavior, therefore all system related calls (HAL, BSP) should be done either at the beginning of the application or inside the thread entry functions.
 - ThreadX offers the "tx_application_define()" function, that is automatically called by the tx_kernel_enter() API.
   It is highly recommended to use it to create all applications ThreadX related resources (threads, semaphores, memory pools...)  but it should not in any way contain a system API call (HAL or BSP).
 - ThreadX needs to know the first free memory block in the RAM to be used for resource allocations.
 
	+For EWARM ".icf" file add a reference to the "FREE_MEM" global symbol as below: place in RAM_region { last section FREE_MEM};

	+For CubeIDE ".ld" file add reference to "__RAM_segment_used_end__" as following:
          {
              . = ALIGN(8); `
              PROVIDE ( end = . );
              PROVIDE ( _end = . ); `
              . = . + _Min_Heap_Size;
              . = . + _Min_Stack_Size;
              . = ALIGN(8); `
              __RAM_segment_used_end__= .;
          } >RAM_D1
		  
### <b>Keywords</b>

Connectivity, USBX Host, ThreadX, USB, CDC_ACM, UART, USART,


### <b>Hardware and Software environment</b>

  - This application runs on STM32F429xx devices
  - This application has been tested with STMicroelectronics STM32F429ZI Nucleo boards Revision MB1137 B-01
    and can be easily tailored to any other supported device and development board.

  - NUCLEO-F429ZI Set-up
    - Plug the USB CDC_ACM device into the NUCLEO-F429ZI board through 'USB micro A-Male  to A-Female' cable to the connector:
      - CN13 : to use USB OTG IP in full speed (FS)
    - Connect ST-Link cable to the PC USB port to display data on the HyperTerminal.

  - A virtual COM port will then appear in the HyperTerminal:
     - Hyperterminal configuration
       - Data Length = 8 Bits
       - One Stop Bit
       - No parity
       - BaudRate = 115200 baud
       - Flow control: None

  - A second virtual COM port will then appear in the HyperTerminal when plugging the device:
     - Hyperterminal configuration
       - Data Length = 8 Bits
       - One Stop Bit
       - No parity
       - BaudRate = 9600 baud
       - Flow control: None

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the application

<b>Notes</b>

- The user has to check the list of the COM ports in Device Manager to find out the number of the COM ports that have been assigned (by OS) to the Stlink VCP.

- The application uses the bypass HSE clock (STlink MCO Output) which is HSI/2 (Default configuration).
It is recommended for USB Host applications on NUCLEO-F429ZI board to change the USB Clock source to StlinkV3 MCO output: HSE/3(8.33MHZ) in order to have more accurate HSE input clock.
To change MCO Clock Output please follow the steps below :

  - Connect to your board using Cubeprogrammer
  - Select "Firmware upgrade".
  - Select "Open in update mode".
  - Select MCO Output : HSE/3 (8.33MHZ).
  - Select "Upgrade".
  - Update the Clock configuration settings in your application code in order to obtain  48MHZ as USB clock source.
