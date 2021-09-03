﻿# X-CUBE-AZRTOS-F4 Azure RTOS Software Expansion for STM32Cube

![latest tag](https://img.shields.io/github/v/tag/STMicroelectronics/x-cube-azrtos-f4.svg?color=brightgreen)

With Azure RTOS complementing the extensive STM32Cube ecosystem providing free development tools, software bricks, and software expansion packages, STM32 users can also leverage the rich services of Azure RTOS, which meet the needs of tiny, smart, connected devices.

**X-CUBE-AZRTOS-F4** (Azure RTOS Software Expansion for STM32Cube) provides a full integration of **Microsoft Azure RTOS** in the STM32Cube environment for the STM32F4 series of microcontrollers. Ready-to-run applicative examples are also provided for the *NUCLEO-F429ZI* and *STM32469I-DISCO* evaluation boards, thus **reducing the learning curve** and ensuring a **smooth application development experience** with Azure RTOS and STM32F4 MCUs.

The scope of this package covers the following Azure RTOS middleware: RTOS (***ThreadX***), USB Device and Host (***USBX***), File System including NOR/NAND memories support (***FileX*** and ***LevelX***) and Networking including Ethernet and WiFi media (***NetXDuo***).

![](_htmresc/OverviewAzureRTOS_in_STM32Cube.png)

Azure RTOS is a professional grade, highly reliable and market proven Middleware suite:
 - **Integrated** and full featured **RTOS**. Learn more [_ThreadX_](https://aka.ms/threadx).
 - **Industrial grade** networking stack: optimized for performance coming with **many IoT protocols.** Learn more [_Netx Duo_](https://aka.ms/netxduo)
 - Advanced FS/FTL: **fully featured** to support **NAND/NOR Flash** memories. Learn more [_FileX_](https://aka.ms/filex)  _and_  [_LevelX_](https://docs.microsoft.com/en-us/azure/rtos/levelx/)
 - USB **Host** and **Device** stacks coming with **multiple classes.** Learn more [_USBX_](https://aka.ms/usbx)
 - **Safety pre-certifications (from Microsoft)**: IEC 61508 SIL4, IEC 62304 Class C and ISO 26262 ASIL D
 - **Security pre-certifications (from Microsoft)**: EAL4+ for TLS/DTLS, FIPS 140-2 for SW crypto lib
 - STM32 **granted production license:** [_here_](https://github.com/azure-rtos/threadx/blob/master/LICENSED-HARDWARE.txt)

### Prerequisites
- USBX, FileX and NetXDuo building require ThreadX as they are based on RTOS model.
- USBX Host MSC requires FileX Middleware usage
- USBX Device ECM/RNDIS classes require NetXDuo usage

One of the following toolchains:

- IAR Embedded Workbench for ARM (EWARM)toolchain 8.50.6 + ST-LINKV3.
- [STM32CubeIDE V1.7.0](https://www.st.com/en/development-tools/stm32cubeide.html)  + ST-LINKV3 
- RealView Microcontroller Development Kit (MDK-ARM) toolchain V5.32 + ST-LINKV3

## Supported Devices and Boards
- [NUCLEO-F429ZI](https://www.st.com/en/evaluation-tools/nucleo-f429zi.html) *(MB1137-B01)*
- [STM32469I-DISCO](https://www.st.com/en/evaluation-tools/32f469idiscovery.html) *(MB1189-B03)*

## Repository structure
The STMicroelectronics GitHub X-CUBE-AZRTOS repository consists of the following repositories:
- **Drivers**: contains STM32F4 CMSIS, HAL and BSP drivers
- **Middlewares**: contains ThreadX, NetX Duo, FileX, LevelX and USBX stacks including porting on STM32 hardware
- **Projects**: provides ready-to-run applicative examples for Azure RTOS on the supported boards. Projects are structured as follows:

![](_htmresc/AzureRTOS_Projects_Structure.png)

## Documentation
More comprehensive documentation is available on STM32 [MCU Wiki](https://wiki.st.com/stm32mcu/wiki/STM32CoreMW_overview).

## License
Azure RTOS is distributed by Microsoft under [GitHub](https://github.com/azure-rtos) and under Microsoft license. 
STMicroelectronics include Azure RTOS in selected STM32Cube software packages, whether delivered by Microsoft under GitHub, or by STMicroelectronics through STM32 CubeFW packages on www.st.com or GitHub, proprietary license terms are the same between Microsoft and User:
-	Source code is available
-	User is granted modification
-	User is granted redistribution of source (modified or not) and/or binary, provided he develops on an MCU/MPU that is listed officially by Microsoft
-	User is granted production, provided he develops on an MCU that is listed officially by Microsoft: [Licensed Hardware](https://github.com/azure-rtos/threadx/blob/master/LICENSED-HARDWARE.txt)
-	User is forbidden to reuse provided software to create a competing offer
Whenever a new STM32 series includes support for Azure RTOS, it is added by Microsoft in the official list

By using STM32F4 Series you inherit the “Distribution and Production Use” rights in Section 2 of the Microsoft Software License Terms for Azure RTOS.

For more details about license information relative to each component in this package, please refer to [LICENSE](./LICENSE.md)


## Applications
| Middleware   |  Applications                    |       Short Description      |
|--------------|----------------------------------|------------------------------|
|ThreadX | Tx_Thread_Creation           | It demonstrates how to create and destroy multiple threads using Azure RTOS ThreadX APIs. In addition, it shows how to use preemption threshold between threads and change priorities on-fly. [readme](./Projects/STM32F429ZI-Nucleo/Applications/ThreadX/Tx_Thread_Creation/README.md) |
|ThreadX | Tx_Thread_Sync               | It demonstrates how to synchronize between threads using binary semaphores or mutexes. [readme](./Projects/STM32469I-Discovery/Applications/ThreadX/Tx_Thread_Sync/README.md) |
|ThreadX | Tx_Thread_MsgQueue           | It demonstrates how to exchange message between threads using Message Queue API and how to handle message from different queues using event queue chaining feature. [readme](./Projects/STM32F429ZI-Nucleo/Applications/ThreadX/Tx_Thread_MsgQueue/README.md) |
|ThreadX | Tx_FreeRTOS_Wrapper          | It demonstrates how to create threads using the FreeRTOS wrapper APIs. [readme](./Projects/STM32F429ZI-Nucleo/Applications/ThreadX/Tx_FreeRTOS_Wrapper/README.md) |
|ThreadX | Tx_CMSIS_Wrapper             | It demonstrates how CMSIS RTOS adaptation layer for Azure RTOS ThreadX, it shows how to develop an application using the CMSIS RTOS 2 APIs. [readme](./Projects/STM32469I-Discovery/Applications/ThreadX/Tx_CMSIS_Wrapper/README.md) |
|ThreadX | Tx_LowPower                  | It demonstrates how to configure the LowPower feature of Azure RTOS ThreadX stack. In addition, it shows how to use ThreadX MACRO related to the LowPower feature. [readme](./Projects/STM32F429ZI-Nucleo/Applications/ThreadX/Tx_LowPower/README.md) |
|ThreadX | Tx_MPU                       | It demonstrates how to load, start and unload modules. In addition, it shows how ThreadX memory protection on modules using the Memory Protection Unit (MPU). [readme](./Projects/STM32F429ZI-Nucleo/Applications/ThreadX/Tx_MPU/README.md) |
|USBX    | Ux_Host_MSC                  | It demonstrates how to develop USB Host Mass Storage "MSC" able to enumerate and communicates with a removable usb flash disk. The application is designed to behave as an USB MSC Host able to operate with an USB flash disk using the Bulk Only Transfer (BOT) and Small Computer System Interface (SCSI) transparent commands combined with a file system AzureRTOS FileX.  [readme](./Projects/STM32F429ZI-Nucleo/Applications/USBX/Ux_Host_MSC/README.md) |
|USBX    | Ux_Host_HID                  | It demonstrates how to develop USB Host Human Interface "HID" able to enumerate and communicates with a mouse or a keyboard. The application is designed to behave as an USB HID Host, the code provides required requests to properly enumerate HID devices , HID Class APIs to decode HID reports received from a mouse or a keyboard and display data on uart HyperTerminal.  [readme](./Projects/STM32F429ZI-Nucleo/Applications/USBX/Ux_Host_HID/README.md) |
|USBX    | Ux_Host_CDC_ACM              | It demonstrates how to develop USB Host CDC ACM device able to properly enumerate CDC devices then send and receive data that can be displayed on Hyperterminal or alike. [readme](./Projects/STM32F429ZI-Nucleo/Applications/USBX/Ux_Host_CDC_ACM/README.md) |
|USBX    | Ux_Device_MSC                | It demonstrates how to develop USB Device mass storage class based application. The application is designed to emulate an USB MSC device, the code provides all required device descriptors framework and the associated Class descriptor report to build a compliant USB MSC device  [readme](./Projects/STM32469I-Discovery/Applications/USBX/Ux_Device_MSC/README.md) |
|USBX    | Ux_Device_CDC_ACM            | It demonstrates how to develop USB Device communication Class "CDC_ACM" based application. The application is designed to emulate an USB-to-UART bridge following the Virtual COM Port (VCP) implementation, the code provides all required device descriptors framework and associated Class descriptor report to build a compliant USB CDC_ACM device. [readme](./Projects/STM32469I-Discovery/Applications/USBX/Ux_Device_CDC_ACM/README.md). |
|USBX    | Ux_Device_HID                | It demonstrates how to develop USB Device Human Interface "HID" mouse based application. The application is designed to emulate an USB HID mouse device, the code provides all required device descriptors framework and associated Class descriptor report to build a compliant USB HID mouse device. [readme](./Projects/STM32F429ZI-Nucleo/Applications/USBX/Ux_Device_HID/README.md)  |
|USBX    | Ux_Device_CDC_ECM            | It demonstrates how to develop USB Device CDC ECM communication. It shows how to run Web HTTP server based application stack over USB interface using USB CDC ECM protocol. [readme](./Projects/STM32469I-Discovery/Applications/USBX/Ux_Device_CDC_ECM/README.md)  |
|USBX    | Ux_Host_DualClass            | It demonstrates how to develop USB Host supporting two device classes: USB_HID (mouse or keyboard) and USB_MSC (removable flash disk). [readme](./Projects/STM32469I-Discovery/Applications/USBX/Ux_Host_DualClass/README.md) |
|USBX    | Ux_Host_HID_CDC_ACM          | It demonstrates how to develop a composite "USB HID CDC_ACM Host" that is able to enumerate and communicate with composite USB HID CDC_ACM and simple HID/CDC_ACM devices. [readme](./Projects/STM32469I-Discovery/Applications/USBX/Ux_Host_HID_CDC_ACM/README.md) |
|USBX    | Ux_Device_HID_CDC_ACM        | It demonstrates how to develop a composite USB Device application. The application is designed to emulate a USB HID mouse combined with an USB-to-UART bridge following the Virtual COM Port (VCP) implementation, the code provides all required device descriptors framework and associated Class descriptor report to build a compliant composite USB HID and CDC_ACM device. [readme](./Projects/STM32469I-Discovery/Applications/USBX/Ux_Device_HID_CDC_ACM/README.md). |
|USBX    | Ux_Device_DFU                | It demonstrates how to develop USB Device Firmware Upgrade "DFU" based application.The application is designed to emulate an USB DFU device, the code provides all required device descriptors framework and associated Class descriptor report to build a compliant USB DFU device. [readme](./Projects/STM32F429ZI-Nucleo/Applications/USBX/Ux_Device_DFU/README.md) |
|FileX   | Fx_uSD_File_Edit             | It demonstrates how to develop a basic SD card file operations application. The application is designed to handle SD card insertion/removal events, and depending on that state, it starts and stops file operations from and into the SD card. [readme](./Projects/STM32469I-Discovery/Applications/FileX/Fx_uSD_File_Edit/README.md)  |
|FileX   | Fx_MultiAccess               | It demonstrates the FileX's concurrent file access capabilities. The application is designed to execute file operations on the SD card device, the code provides all required software code for handling SD card I/O operations. [readme](./Projects/STM32469I-Discovery/Applications/FileX/Fx_MultiAccess/README.md) |
|FileX   | Fx_NoR_Write_Read_File       | It demonstrates how to create a Fat File system on the NOR flash using FileX alongside LevelX. The application is designed to execute file operations on the MX25LM51245G NOR flash device, the code provides all required software code for properly managing it. [readme](./Projects/STM32469I-Discovery/Applications/FileX/Fx_NoR_Write_Read_File/README.md) |
|FileX   | Fx_DualInstance              | It demonstrates the coexistence capability of two FileX/Levelx stacks running independently on each core. [readme](./Projects/STM32469I-Discovery/Applications/FileX/Fx_Dual_Instance/README.md) |
|FileX   | Fx_IAP                       | It demonstrates how to implement an In-Application programming (IAP) using FileX's SD file access capabilities. The application is designed to erase and write to on-chip flash memory, it provides all required software code for handling SD card and flash memory I/O operations. This is a typical application on how to use the SD card peripheral for firmware upgrade application or IAP, allowing user to erase and write to on-chip flash memory. [readme](./Projects/STM32469I-Discovery/Applications/FileX/FX_IAP/IAP_main/README.md) |
|FileX   | Fx_SRAM_File_Edit_Standalone | It demonstrates how to create a Fat File system on the internal SRAM memory using FileX running in standalone mode without ThreadX. [readme](./Projects/STM32F429ZI-Nucleo/Applications/FileX/Fx_SRAM_File_Edit_Standalone/README.md) |
|NetXDuo | Nx_TCP_Echo_Server           | It demonstrates how to develop a NetX TCP server to communicate with a remote client using the NetX TCP socket API. [readme](./Projects/STM32F429ZI-Nucleo/Applications/NetXDuo/Nx_TCP_Echo_Server/README.md) |
|NetXDuo | Nx_TCP_Echo_Client           | It demonstrates how to develop a NetX TCP client to communicate with a remote sever using the NetX TCP socket API. [readme](./Projects/STM32F429ZI-Nucleo/Applications/NetXDuo/Nx_TCP_Echo_Client/README.md) |
|NetXDuo | Nx_UDP_Echo_Server           | It demonstrates how to develop a NetX UDP server to communicate with a remote client using the NetX UDP socket API. [readme](./Projects/STM32F429ZI-Nucleo/Applications/NetXDuo/Nx_UDP_Echo_Server/README.md) |
|NetXDuo | Nx_UDP_Echo_Client           | It demonstrates how to develop a NetX UDP client to communicate with a remote sever using the NetX UDP socket API. [readme](./Projects/STM32F429ZI-Nucleo/Applications/NetXDuo/Nx_UDP_Echo_Client/README.md) |
|NetXDuo | Nx_WebServer                 | It demonstrates how to develop Web HTTP server based application.It is designed to load files and static web pages stored in SD card using a Web HTTP server, the code provides all required features to build a compliant Web HTTP Server.  [readme](./Projects/STM32F429ZI-Nucleo/Applications/NetXDuo/Nx_WebServer/README.md) |
|NetXDuo | Nx_MQTT_Client               | It demonstrates how to exchange data between client and server using MQTT protocol in an encrypted mode supporting TLS v1.2. [readme](./Projects/STM32F429ZI-Nucleo/Applications/NetXDuo/Nx_MQTT_Client/README.md) |
|NetXDuo | Nx_SNTP_Client               | It demonstrates how to develop a NetX SNTP client and connect with an STNP server to get a time update. [readme](./Projects/STM32F429ZI-Nucleo/Applications/NetXDuo/Nx_SNTP_Client/README.md) |

## Main changes

- First official release of Azure RTOS integration in the STM32Cube Ecosystem for STM32F4 MCU series

## Known limitations

- USBX composite device descriptors
   - A maximum of 2 different class driver can be selected (restriction due to limited EP numbers)
   - A list of USB device Applications supporting auto generation of USB Device framework descriptors provided  for these USB class drivers :MSC, HID mouse, CDC ACM, CDC ECM, DFU. For the other device class drivers, user needs first to 
     disable the device framework builder (refer to : USBx wiki section 2.2 How to customize) and provide the full set of required device descriptors.
- NetXDuo
   - Ethernet cable hot-plug detection not supported.
   - User needs to point to the HAL Drivers under X-CUBE-AZRTOS-F4 install path instead of the default location when creating a NetXDuo based project.

## Troubleshooting
**Caution**  : The issues are  **strictly limited**  to submit problems or suggestions related to the software delivered in this repository.

**For any other question**  related to the product, the hardware performance or characteristics, the tools, the environment, you can submit it to the  **ST Community**  on the STM32 MCUs related  [page](https://community.st.com/s/topic/0TO0X000000BSqSWAW/stm32-mcus).

