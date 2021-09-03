
## <b>Ux_Device_CDC_ACM Application Description</b>

This application provides an example of Azure RTOS USBX stack usage on STM32F469NI board, it shows how to develop USB Device communication Class "CDC_ACM" based application.
The application is designed to emulate an USB-to-UART bridge following the Virtual COM Port (VCP) implementation, the code provides all required device descriptors framework
and associated Class descriptor report to build a compliant USB CDC_ACM device.
At the beginning ThreadX call the entry function tx_application_define(), at this stage, all USBx resources are initialized, the CDC_ACM Class driver is registered and
the application creates 3 threads with the same priorities :

  - usbx_app_thread_entry (Prio : 20; PreemptionPrio : 20) used to initialize USB OTG HAL PCD driver and start the device.
  - usbx_cdc_acm_read_thread_entry (Prio : 20; PreemptionPrio : 20) used to Read the received data from Virtual COM Port.
  - usbx_cdc_acm_write_thread_entry (Prio : 20; PreemptionPrio : 20) used to send the received data over UART.

During enumeration phase, three communication pipes "endpoints" are declared in the CDC class implementation :

 - 1 x Bulk IN endpoint for receiving data from STM32 device to PC host:
   When data are received over UART they are saved in the buffer "UserTxBufferFS". Periodically, in a
   usbx_cdc_acm_write_thread_entry the state of the buffer "UserTxBufferFS" is checked. If there are available data, they
   are transmitted in response to IN token otherwise it is NAKed.

 - 1 x Bulk OUT endpoint for transmitting data from PC host to STM32 device:
   When data are received through this endpoint they are saved in the buffer "UserRxBufferFS" then they are transmitted
   over UART using DMA mode and in meanwhile the OUT endpoint is NAKed.
   Once the transmission is over, the OUT endpoint is prepared to receive next packet in HAL_UART_RxCpltCallback().
 - 1 x Interrupt IN endpoint for setting and getting serial-port parameters:
   When control setup is received, the corresponding request is executed in ux_app_parameters_change().

In CDC_ACM application, two requests are implemented:

    - Set line: Set the bit rate, number of Stop bits, parity, and number of data bits
    - Get line: Get the bit rate, number of Stop bits, parity, and number of data bits
   The other requests (send break, control line state) are not implemented.

<b>Notes</b>

- Receiving data over UART is handled by interrupt while transmitting is handled by DMA allowing hence the application to receive data at the same time it is transmitting another data (full- duplex feature).
The support of the VCP interface is managed through the ST Virtual COM Port driver available for download from www.st.com.

- The user has to check the list of the COM ports in Device Manager to find out the COM port number that have been assigned (by OS) to the VCP interface.

#### <b>Expected success behavior</b>

When plugged to PC host, the STM32F469NI must be properly enumerated as an USB Serial device and an STlink Com port.
During the enumeration phase, the device must provide host with the requested descriptors (Device descriptor, configuration descriptor, string descriptors).
Those descriptors are used by host driver to identify the device capabilities. Once STM32F469NI USB device successfully completed the enumeration phase,
Open two hyperterminals (USB com port and UART com port(USB STLink VCP)) to send/receive data to/from host from/to device.

#### <b>Error behaviors</b>

Host PC shows that USB device does not operate as designed (CDC Device enumeration failed, PC and Device can not communicate over VCP ports).

#### <b>Assumptions if any</b>

User is familiar with USB 2.0 "Universal Serial BUS" Specification and CDC_ACM class Specification.

#### <b>Known limitations</b>


### <b>Notes</b>

#### <b>ThreadX usage hints</b>
 - ThreadX uses the Systick as time base, thus it is mandatory that the HAL uses a separate time base through the TIM IPs.
 - ThreadX is configured with 100 ticks/sec by default, this should be taken into account when using delays or timeouts at application. It is always possible to reconfigure it in the "tx_user.h", the "TX_TIMER_TICKS_PER_SECOND" define,but this should be reflected in "tx_initialize_low_level.s" file too.
 - ThreadX is disabling all interrupts during kernel start-up to avoid any unexpected behavior, therefore all system related calls (HAL, BSP) should be done either at the beginning of the application or inside the thread entry functions.
 - ThreadX offers the "tx_application_define()" function, that is automatically called by the tx_kernel_enter() API. It is highly recommended to use it to create all applications ThreadX related resources (threads, semaphores, memory pools...) but it should not in any way contain a system API call (HAL or BSP).
 - ThreadX needs to know the first free memory block in the RAM to be used for resource allocations.
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

RTOS, ThreadX, USBX, Device, USB_OTG, Full Speed, CDC, VCP, USART, DMA.

### <b>Hardware and Software environment</b>

  - This example runs on STM32F469xx devices
  - This example has been tested with STMicroelectronics STM32F469I-Discovery boards Revision MB1189 B-03 and can be easily tailored to any other supported device and development board.
  - STM32F469NI Set-up
  - Connect the STM32F469NI board CN13 to the PC through "USB micro A-Male " to "A-Female" cable.
  - For VCP the configuration is dynamic for example it can be :
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1
    - Parity = None
    - Flow control = None

  - The USART3 interface available on PB10 and PB11 of the microcontroller are
  connected to ST-LINK MCU.
  By default the USART3 communication between the target MCU and ST-LINK MCU is enabled.
  It's configuration is as following:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1
    - Parity = None
    - Flow control = None

<b>Note</b>

 - In case User configures USB VCP baudrate under 9600 the USART3 baudrate shall be set to 9600.

### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the application