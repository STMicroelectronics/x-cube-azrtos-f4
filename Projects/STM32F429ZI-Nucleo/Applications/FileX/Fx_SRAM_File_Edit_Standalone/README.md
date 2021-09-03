
## <b>Fx_SRAM_File_Edit_Standalone application description</b>

This application provides an example of FileX stack usage on STM32F429ZI-Nucleo board, running in standalone mode (without ThreadX). It demonstrates how to create a Fat File system on the internal SRAM memory using FileX. 

The application is designed to execute file operations on the SRAM-Disk device, it provides all required software code for properly managing it.

The application's main calls the fx_FileXApp() function that handles file operations. At this stage, all FileX resources are created and the SRAM driver is initialized. After that, the fx_FileXApp will start by formatting the SRAM-Disk using FileX services. The resulting file system is a FAT32 compatible, with 512 bytes per sector.

Upon successful opening of the created SRAM-Disk media, FileX continue with creating a file called "STM32.TXT" into the root directory, then write into it some predefined data. Then file is re-opened in read only mode and content is checked.

As stated earlier, the present application runs in standalone mode without ThreadX, for this reason, the standalone variant of fileX is used, plus the following flags need to be set in fx_user.h:
  #define FX_SINGLE_THREAD
  #define FX_STANDALONE_ENABLE

#### <b>Expected success behavior</b>

Successful operation is marked by a toggeling green LED light.

Also, information regarding executing operation on the SRAM-Disk is printed to the serial port.

#### <b>Error behaviors</b>

On failure, the red LED starts toggeling while the green LED is switched OFF.

#### <b>Assumptions if any</b>
None

#### <b>Known limitations</b>
None

### <b>Notes</b>
 1. The created SRAM-Disk, is placed in SRAM3(64 KB) starting from the(SRAM3_BASE=@0x20020000).
 2. First 512 byte of this memory is reserved for FAT file system, the rest is available for file storage.
               
#### <b>FileX/LevelX usage hints</b>

- When calling the fx_media_format() API, it is highly recommended to understand all the parameters used by the API to correctly generate a valid filesystem.
- FileX is using data buffers, passed as arguments to fx_media_open(), fx_media_read() and fx_media_write() API, it is recommended that these buffers are multiple of sector size and be "4 bytes" aligned to avoid unaligned access issues.

### <b>Keywords</b>

RTOS, ThreadX, FileX, File System, FAT32, SRAM, SRAM-DISK

### <b>Hardware and Software environment</b>

  - This application runs on STM32F429xx devices
  - This application has been tested with STMicroelectronics STM32F429ZI Nucleo boards Revision MB1137 B-01
    and can be easily tailored to any other supported device and development board.

  - This application uses USART3 to display logs, the hyperterminal configuration is as follows:
      - BaudRate = 115200 baud
      - Word Length = 8 Bits
      - Stop Bit = 1
      - Parity = none
      - Flow control = None


### <b>How to use it ?</b>

In order to make the program work, you must do the following :

 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the application
