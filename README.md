<div align="center">

<img src="https://upload.wikimedia.org/wikipedia/commons/b/ba/TexasInstruments-Logo.svg" width="150"><br/>
# C2000Ware

[Introduction](#introduction) | [Layout](#Repository Layout) | [Overview](#overview) | [Contribute](#contributing-to-the-project)

</div>

## Introduction

C2000Ware for C2000 microcontrollers is a cohesive set of development software and documentation designed to minimize software development time. 
It includes device-specific drivers and device peripheral examples, C2000Ware provides a solid foundation to begin development and evaluation.
List of devices supported
- [F280015x](https://www.ti.com/product/TMS320F2800157) 
- [F280013x(https://www.ti.com/product/TMS320F2800137)
- [F28004x](https://www.ti.com/product/TMS320F280049C)
- [F28003x](https://www.ti.com/product/TMS320F280039C)
- [F28002x](https://www.ti.com/product/TMS320F280025C)

The SDK includes peripheral usage examples to help users to get started quickly.

## Repository Layout

- .metadata folder
  - This folder contains the C2000Ware resource explorer standalone GUI files. Do not modify.
  
- device_support
  - This folder contains all device-specific support files, bit field headers and device development user’s guides.

- docs
  - This folder contains the C2000Ware Quick start guides and links to references articles

- driverlib
  - This folder contains the device-specific driver library and driver-based peripheral examples.

- examples
  - This folder contains the examples involving multiple devices/peripherals to showcase different applications.

- utilities
  - This folder contains development utility applications such as flash programmers, windows drivers.
  
## Overview

C2000Ware SDK comprises of multiple repositories with the current repository at it's core. 
There are other repositories that need to be cloned and are listed below:

- [Ethernet Low Level Driver (ENET LLD)](https://github.com/TexasInstruments/mcupsdk-enet-lld)
- [FreeRTOS-Kernel](https://github.com/TexasInstruments/mcupsdk-FreeRTOS-Kernel)
- [FreeRTOS-POSIX](https://github.com/TexasInstruments/mcupsdk-FreeRTOS-POSIX)
- [FreeRTOS-FAT](https://github.com/TexasInstruments/mcupsdk-FreeRTOS-FAT)


C2000Ware installers is available for download 
- [C2000Ware](https://www.ti.com/tool/C2000Ware)

## Contributing to the project

This project is currently not accepting contributions. 
