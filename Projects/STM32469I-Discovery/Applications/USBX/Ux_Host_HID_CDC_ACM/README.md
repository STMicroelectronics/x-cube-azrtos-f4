
## <b>Ux_Host_HID_CDC_ACM Application Description </b>

This application provides an example of Azure RTOS USBX stack usage on STM32F469I-Discovery.
It shows how to develop a composite "USB HID CDC_ACM Host" that is able to enumerate and communicate with:

  - Composite USB HID CDC_ACM device
  - Simple HID/CDC_ACM device,

The application is designed to behave as a composite USB HID CDC_ACM Host, the code provides the required requests to properly manage the enumeration process of a compisite HID CDC_ACM device or a simple HID/CDC_ACM device.
In case of composite or a simple device, the CDC_ACM Class APIs is used to send, receive and display data on uart terminal. Also an HID Class APIs is used to decode HID reports received from a mouse or a keyboard and display data on uart terminal.

The main entry function tx_application_define() is called by ThreadX during kernel start, at this stage, all USBx resources are initialized.
The application creates 5 threads with different priorities :

  - usbx_app_thread_entry            (Priority : 25; Preemption threshold : 25) used to initialize USB OTG HAL HCD driver and start the Host.
  - cdc_acm_send_app_thread_entry    (Priority : 30; Preemption threshold : 30) used to send data from host to device.
  - cdc_acm_recieve_app_thread_entry (Priority : 30; Preemption threshold : 30) used to receive data from the device.
  - hid_mouse_thread_entry           (Priority : 30; Preemption threshold : 30) used to decode HID reports received  from a mouse.
  - hid_keyboard_thread_entry        (Priority : 30; Preemption threshold : 30) used to decode HID reports received  from a keyboard.

#### <b> Expected success behavior</b>

- In case of composite HID CDC_ACM device or a simple HID/CDC_ACM is plugged to STM32F469I-Discovery board, a message will be displayed on the uart console(ST-Link VCP) showing
the Vendor ID and Product ID of the attached device. The host should be able to properly decode composite HID CDC_ACM class or simple HID/CDC_ACM request data sent by the device.
After enumeration phase, the device will be ready to use.

in case of a CDC_ACM
   - The Sent/received data are displayed on respective terminals.

in case of a mouse:
   - (x,y) mouse position
   - Wheel position
   - Pressed mouse buttons

in case of a keyboard:
   - Pressed key

in case of Composite HID CDC_ACM
   - The Sent/received data are displayed on respective terminals.
   - (x,y) mouse position, Wheel position, Pressed mouse buttons or Pressed key in case of a Keyboard

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

Connectivity, USBX Host, ThreadX, USB, Composite, CDC_ACM, HID, Mouse, Keyboard UART, USART,


### <b>Hardware and Software environment</b>

  - This application runs on STM32F469xx devices
  - This application has been tested with STMicroelectronics STM32F469I-Discovery boards Revision MB1189 B-03
    and can be easily tailored to any other supported device and development board.

  - STM32F469I-Discovery Set-up
    - Plug the USB CDC_ACM device into the STM32F469I-Discovery board through 'USB micro A-Male  to A-Female' cable to the connector:
       - CN13 : to use USB Full Speed OTG IP.
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

- The user has to check the list of the COM ports in Device Manager to find out the number of the COM ports that have been assigned (by OS) to the ST-Link VCP.

- The application uses the bypass HSE clock (STlink MCO Output) which is HSI/2 (Default configuration).
It is recommended for USB Host applications on STM32F469I-Discovery board to change the USB Clock source to ST-Link V3 MCO output: HSE/3(8.33MHZ) in order to have more accurate HSE input clock.
To change MCO Clock Output please follow the steps below :

  - Connect to your board using Cubeprogrammer
  - Select "Firmware upgrade".
  - Select "Open in update mode".
  - Select MCO Output : HSE/3 (8.33MHZ).
  - Select "Upgrade".
  - Update the Clock configuration settings in your application code in order to obtain  48MHZ as USB clock source.
