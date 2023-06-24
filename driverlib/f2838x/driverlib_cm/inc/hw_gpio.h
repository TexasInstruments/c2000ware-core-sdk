//###########################################################################
//
// FILE:    hw_gpio.h
//
// TITLE:   Definitions for the GPIO registers.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef HW_GPIO_H
#define HW_GPIO_H

//*************************************************************************************************
//
// The following are defines for the GPIO register offsets
//
//*************************************************************************************************
#define GPIO_O_GPADAT      0x0U    // GPIO A Data Register (GPIO0 to 31)
#define GPIO_O_GPASET      0x4U    // GPIO A Data Set Register (GPIO0 to 31)
#define GPIO_O_GPACLEAR    0x8U    // GPIO A Data Clear Register (GPIO0 to 31)
#define GPIO_O_GPATOGGLE   0xCU    // GPIO A Data Toggle Register (GPIO0 to 31)
#define GPIO_O_GPBDAT      0x10U   // GPIO B Data Register (GPIO32 to 63)
#define GPIO_O_GPBSET      0x14U   // GPIO B Data Set Register (GPIO32 to 63)
#define GPIO_O_GPBCLEAR    0x18U   // GPIO B Data Clear Register (GPIO32 to 63)
#define GPIO_O_GPBTOGGLE   0x1CU   // GPIO B Data Toggle Register (GPIO32 to 63)
#define GPIO_O_GPCDAT      0x20U   // GPIO C Data Register (GPIO64 to 95)
#define GPIO_O_GPCSET      0x24U   // GPIO C Data Set Register (GPIO64 to 95)
#define GPIO_O_GPCCLEAR    0x28U   // GPIO C Data Clear Register (GPIO64 to 95)
#define GPIO_O_GPCTOGGLE   0x2CU   // GPIO C Data Toggle Register (GPIO64 to 95)
#define GPIO_O_GPDDAT      0x30U   // GPIO D Data Register (GPIO96 to 127)
#define GPIO_O_GPDSET      0x34U   // GPIO D Data Set Register (GPIO96 to 127)
#define GPIO_O_GPDCLEAR    0x38U   // GPIO D Data Clear Register (GPIO96 to 127)
#define GPIO_O_GPDTOGGLE   0x3CU   // GPIO D Data Toggle Register (GPIO96 to 127)
#define GPIO_O_GPEDAT      0x40U   // GPIO E Data Register (GPIO128 to 159)
#define GPIO_O_GPESET      0x44U   // GPIO E Data Set Register (GPIO128 to 159)
#define GPIO_O_GPECLEAR    0x48U   // GPIO E Data Clear Register (GPIO128 to 159)
#define GPIO_O_GPETOGGLE   0x4CU   // GPIO E Data Toggle Register (GPIO128 to 159)
#define GPIO_O_GPFDAT      0x50U   // GPIO F Data Register (GPIO160 to 191)
#define GPIO_O_GPFSET      0x54U   // GPIO F Data Set Register (GPIO160 to 191)
#define GPIO_O_GPFCLEAR    0x58U   // GPIO F Data Clear Register (GPIO160 to 191)
#define GPIO_O_GPFTOGGLE   0x5CU   // GPIO F Data Toggle Register (GPIO160 to 191)

#define GPIO_O_GPADAT_R   0x0U    // GPIO A Data Read Register
#define GPIO_O_GPBDAT_R   0x4U    // GPIO B Data Read Register
#define GPIO_O_GPCDAT_R   0x8U    // GPIO C Data Read Register
#define GPIO_O_GPDDAT_R   0xCU    // GPIO D Data Read Register
#define GPIO_O_GPEDAT_R   0x10U   // GPIO E Data Read Register
#define GPIO_O_GPFDAT_R   0x14U   // GPIO F Data Read Register
#define GPIO_O_GPGDAT_R   0x18U   // GPIO G Data Read Register
#define GPIO_O_GPHDAT_R   0x1CU   // GPIO H Data Read Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the GPADAT register
//
//*************************************************************************************************
#define GPIO_GPADAT_GPIO0    0x1U          // Data Register for this pin
#define GPIO_GPADAT_GPIO1    0x2U          // Data Register for this pin
#define GPIO_GPADAT_GPIO2    0x4U          // Data Register for this pin
#define GPIO_GPADAT_GPIO3    0x8U          // Data Register for this pin
#define GPIO_GPADAT_GPIO4    0x10U         // Data Register for this pin
#define GPIO_GPADAT_GPIO5    0x20U         // Data Register for this pin
#define GPIO_GPADAT_GPIO6    0x40U         // Data Register for this pin
#define GPIO_GPADAT_GPIO7    0x80U         // Data Register for this pin
#define GPIO_GPADAT_GPIO8    0x100U        // Data Register for this pin
#define GPIO_GPADAT_GPIO9    0x200U        // Data Register for this pin
#define GPIO_GPADAT_GPIO10   0x400U        // Data Register for this pin
#define GPIO_GPADAT_GPIO11   0x800U        // Data Register for this pin
#define GPIO_GPADAT_GPIO12   0x1000U       // Data Register for this pin
#define GPIO_GPADAT_GPIO13   0x2000U       // Data Register for this pin
#define GPIO_GPADAT_GPIO14   0x4000U       // Data Register for this pin
#define GPIO_GPADAT_GPIO15   0x8000U       // Data Register for this pin
#define GPIO_GPADAT_GPIO16   0x10000U      // Data Register for this pin
#define GPIO_GPADAT_GPIO17   0x20000U      // Data Register for this pin
#define GPIO_GPADAT_GPIO18   0x40000U      // Data Register for this pin
#define GPIO_GPADAT_GPIO19   0x80000U      // Data Register for this pin
#define GPIO_GPADAT_GPIO20   0x100000U     // Data Register for this pin
#define GPIO_GPADAT_GPIO21   0x200000U     // Data Register for this pin
#define GPIO_GPADAT_GPIO22   0x400000U     // Data Register for this pin
#define GPIO_GPADAT_GPIO23   0x800000U     // Data Register for this pin
#define GPIO_GPADAT_GPIO24   0x1000000U    // Data Register for this pin
#define GPIO_GPADAT_GPIO25   0x2000000U    // Data Register for this pin
#define GPIO_GPADAT_GPIO26   0x4000000U    // Data Register for this pin
#define GPIO_GPADAT_GPIO27   0x8000000U    // Data Register for this pin
#define GPIO_GPADAT_GPIO28   0x10000000U   // Data Register for this pin
#define GPIO_GPADAT_GPIO29   0x20000000U   // Data Register for this pin
#define GPIO_GPADAT_GPIO30   0x40000000U   // Data Register for this pin
#define GPIO_GPADAT_GPIO31   0x80000000U   // Data Register for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPASET register
//
//*************************************************************************************************
#define GPIO_GPASET_GPIO0    0x1U          // Output Set bit for this pin
#define GPIO_GPASET_GPIO1    0x2U          // Output Set bit for this pin
#define GPIO_GPASET_GPIO2    0x4U          // Output Set bit for this pin
#define GPIO_GPASET_GPIO3    0x8U          // Output Set bit for this pin
#define GPIO_GPASET_GPIO4    0x10U         // Output Set bit for this pin
#define GPIO_GPASET_GPIO5    0x20U         // Output Set bit for this pin
#define GPIO_GPASET_GPIO6    0x40U         // Output Set bit for this pin
#define GPIO_GPASET_GPIO7    0x80U         // Output Set bit for this pin
#define GPIO_GPASET_GPIO8    0x100U        // Output Set bit for this pin
#define GPIO_GPASET_GPIO9    0x200U        // Output Set bit for this pin
#define GPIO_GPASET_GPIO10   0x400U        // Output Set bit for this pin
#define GPIO_GPASET_GPIO11   0x800U        // Output Set bit for this pin
#define GPIO_GPASET_GPIO12   0x1000U       // Output Set bit for this pin
#define GPIO_GPASET_GPIO13   0x2000U       // Output Set bit for this pin
#define GPIO_GPASET_GPIO14   0x4000U       // Output Set bit for this pin
#define GPIO_GPASET_GPIO15   0x8000U       // Output Set bit for this pin
#define GPIO_GPASET_GPIO16   0x10000U      // Output Set bit for this pin
#define GPIO_GPASET_GPIO17   0x20000U      // Output Set bit for this pin
#define GPIO_GPASET_GPIO18   0x40000U      // Output Set bit for this pin
#define GPIO_GPASET_GPIO19   0x80000U      // Output Set bit for this pin
#define GPIO_GPASET_GPIO20   0x100000U     // Output Set bit for this pin
#define GPIO_GPASET_GPIO21   0x200000U     // Output Set bit for this pin
#define GPIO_GPASET_GPIO22   0x400000U     // Output Set bit for this pin
#define GPIO_GPASET_GPIO23   0x800000U     // Output Set bit for this pin
#define GPIO_GPASET_GPIO24   0x1000000U    // Output Set bit for this pin
#define GPIO_GPASET_GPIO25   0x2000000U    // Output Set bit for this pin
#define GPIO_GPASET_GPIO26   0x4000000U    // Output Set bit for this pin
#define GPIO_GPASET_GPIO27   0x8000000U    // Output Set bit for this pin
#define GPIO_GPASET_GPIO28   0x10000000U   // Output Set bit for this pin
#define GPIO_GPASET_GPIO29   0x20000000U   // Output Set bit for this pin
#define GPIO_GPASET_GPIO30   0x40000000U   // Output Set bit for this pin
#define GPIO_GPASET_GPIO31   0x80000000U   // Output Set bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACLEAR register
//
//*************************************************************************************************
#define GPIO_GPACLEAR_GPIO0    0x1U          // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO1    0x2U          // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO2    0x4U          // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO3    0x8U          // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO4    0x10U         // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO5    0x20U         // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO6    0x40U         // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO7    0x80U         // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO8    0x100U        // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO9    0x200U        // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO10   0x400U        // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO11   0x800U        // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO12   0x1000U       // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO13   0x2000U       // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO14   0x4000U       // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO15   0x8000U       // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO16   0x10000U      // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO17   0x20000U      // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO18   0x40000U      // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO19   0x80000U      // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO20   0x100000U     // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO21   0x200000U     // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO22   0x400000U     // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO23   0x800000U     // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO24   0x1000000U    // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO25   0x2000000U    // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO26   0x4000000U    // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO27   0x8000000U    // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO28   0x10000000U   // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO29   0x20000000U   // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO30   0x40000000U   // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO31   0x80000000U   // Output Clear bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPATOGGLE register
//
//*************************************************************************************************
#define GPIO_GPATOGGLE_GPIO0    0x1U          // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO1    0x2U          // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO2    0x4U          // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO3    0x8U          // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO4    0x10U         // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO5    0x20U         // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO6    0x40U         // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO7    0x80U         // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO8    0x100U        // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO9    0x200U        // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO10   0x400U        // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO11   0x800U        // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO12   0x1000U       // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO13   0x2000U       // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO14   0x4000U       // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO15   0x8000U       // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO16   0x10000U      // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO17   0x20000U      // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO18   0x40000U      // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO19   0x80000U      // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO20   0x100000U     // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO21   0x200000U     // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO22   0x400000U     // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO23   0x800000U     // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO24   0x1000000U    // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO25   0x2000000U    // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO26   0x4000000U    // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO27   0x8000000U    // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO28   0x10000000U   // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO29   0x20000000U   // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO30   0x40000000U   // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO31   0x80000000U   // Output Toggle bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBDAT register
//
//*************************************************************************************************
#define GPIO_GPBDAT_GPIO32   0x1U          // Data Register for this pin
#define GPIO_GPBDAT_GPIO33   0x2U          // Data Register for this pin
#define GPIO_GPBDAT_GPIO34   0x4U          // Data Register for this pin
#define GPIO_GPBDAT_GPIO35   0x8U          // Data Register for this pin
#define GPIO_GPBDAT_GPIO36   0x10U         // Data Register for this pin
#define GPIO_GPBDAT_GPIO37   0x20U         // Data Register for this pin
#define GPIO_GPBDAT_GPIO38   0x40U         // Data Register for this pin
#define GPIO_GPBDAT_GPIO39   0x80U         // Data Register for this pin
#define GPIO_GPBDAT_GPIO40   0x100U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO41   0x200U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO42   0x400U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO43   0x800U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO44   0x1000U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO45   0x2000U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO46   0x4000U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO47   0x8000U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO48   0x10000U      // Data Register for this pin
#define GPIO_GPBDAT_GPIO49   0x20000U      // Data Register for this pin
#define GPIO_GPBDAT_GPIO50   0x40000U      // Data Register for this pin
#define GPIO_GPBDAT_GPIO51   0x80000U      // Data Register for this pin
#define GPIO_GPBDAT_GPIO52   0x100000U     // Data Register for this pin
#define GPIO_GPBDAT_GPIO53   0x200000U     // Data Register for this pin
#define GPIO_GPBDAT_GPIO54   0x400000U     // Data Register for this pin
#define GPIO_GPBDAT_GPIO55   0x800000U     // Data Register for this pin
#define GPIO_GPBDAT_GPIO56   0x1000000U    // Data Register for this pin
#define GPIO_GPBDAT_GPIO57   0x2000000U    // Data Register for this pin
#define GPIO_GPBDAT_GPIO58   0x4000000U    // Data Register for this pin
#define GPIO_GPBDAT_GPIO59   0x8000000U    // Data Register for this pin
#define GPIO_GPBDAT_GPIO60   0x10000000U   // Data Register for this pin
#define GPIO_GPBDAT_GPIO61   0x20000000U   // Data Register for this pin
#define GPIO_GPBDAT_GPIO62   0x40000000U   // Data Register for this pin
#define GPIO_GPBDAT_GPIO63   0x80000000U   // Data Register for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBSET register
//
//*************************************************************************************************
#define GPIO_GPBSET_GPIO32   0x1U          // Output Set bit for this pin
#define GPIO_GPBSET_GPIO33   0x2U          // Output Set bit for this pin
#define GPIO_GPBSET_GPIO34   0x4U          // Output Set bit for this pin
#define GPIO_GPBSET_GPIO35   0x8U          // Output Set bit for this pin
#define GPIO_GPBSET_GPIO36   0x10U         // Output Set bit for this pin
#define GPIO_GPBSET_GPIO37   0x20U         // Output Set bit for this pin
#define GPIO_GPBSET_GPIO38   0x40U         // Output Set bit for this pin
#define GPIO_GPBSET_GPIO39   0x80U         // Output Set bit for this pin
#define GPIO_GPBSET_GPIO40   0x100U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO41   0x200U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO42   0x400U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO43   0x800U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO44   0x1000U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO45   0x2000U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO46   0x4000U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO47   0x8000U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO48   0x10000U      // Output Set bit for this pin
#define GPIO_GPBSET_GPIO49   0x20000U      // Output Set bit for this pin
#define GPIO_GPBSET_GPIO50   0x40000U      // Output Set bit for this pin
#define GPIO_GPBSET_GPIO51   0x80000U      // Output Set bit for this pin
#define GPIO_GPBSET_GPIO52   0x100000U     // Output Set bit for this pin
#define GPIO_GPBSET_GPIO53   0x200000U     // Output Set bit for this pin
#define GPIO_GPBSET_GPIO54   0x400000U     // Output Set bit for this pin
#define GPIO_GPBSET_GPIO55   0x800000U     // Output Set bit for this pin
#define GPIO_GPBSET_GPIO56   0x1000000U    // Output Set bit for this pin
#define GPIO_GPBSET_GPIO57   0x2000000U    // Output Set bit for this pin
#define GPIO_GPBSET_GPIO58   0x4000000U    // Output Set bit for this pin
#define GPIO_GPBSET_GPIO59   0x8000000U    // Output Set bit for this pin
#define GPIO_GPBSET_GPIO60   0x10000000U   // Output Set bit for this pin
#define GPIO_GPBSET_GPIO61   0x20000000U   // Output Set bit for this pin
#define GPIO_GPBSET_GPIO62   0x40000000U   // Output Set bit for this pin
#define GPIO_GPBSET_GPIO63   0x80000000U   // Output Set bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCLEAR register
//
//*************************************************************************************************
#define GPIO_GPBCLEAR_GPIO32   0x1U          // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO33   0x2U          // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO34   0x4U          // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO35   0x8U          // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO36   0x10U         // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO37   0x20U         // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO38   0x40U         // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO39   0x80U         // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO40   0x100U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO41   0x200U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO42   0x400U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO43   0x800U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO44   0x1000U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO45   0x2000U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO46   0x4000U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO47   0x8000U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO48   0x10000U      // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO49   0x20000U      // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO50   0x40000U      // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO51   0x80000U      // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO52   0x100000U     // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO53   0x200000U     // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO54   0x400000U     // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO55   0x800000U     // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO56   0x1000000U    // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO57   0x2000000U    // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO58   0x4000000U    // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO59   0x8000000U    // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO60   0x10000000U   // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO61   0x20000000U   // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO62   0x40000000U   // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO63   0x80000000U   // Output Clear bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBTOGGLE register
//
//*************************************************************************************************
#define GPIO_GPBTOGGLE_GPIO32   0x1U          // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO33   0x2U          // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO34   0x4U          // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO35   0x8U          // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO36   0x10U         // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO37   0x20U         // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO38   0x40U         // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO39   0x80U         // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO40   0x100U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO41   0x200U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO42   0x400U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO43   0x800U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO44   0x1000U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO45   0x2000U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO46   0x4000U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO47   0x8000U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO48   0x10000U      // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO49   0x20000U      // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO50   0x40000U      // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO51   0x80000U      // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO52   0x100000U     // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO53   0x200000U     // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO54   0x400000U     // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO55   0x800000U     // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO56   0x1000000U    // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO57   0x2000000U    // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO58   0x4000000U    // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO59   0x8000000U    // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO60   0x10000000U   // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO61   0x20000000U   // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO62   0x40000000U   // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO63   0x80000000U   // Output Toggle bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCDAT register
//
//*************************************************************************************************
#define GPIO_GPCDAT_GPIO64   0x1U          // Data Register for this pin
#define GPIO_GPCDAT_GPIO65   0x2U          // Data Register for this pin
#define GPIO_GPCDAT_GPIO66   0x4U          // Data Register for this pin
#define GPIO_GPCDAT_GPIO67   0x8U          // Data Register for this pin
#define GPIO_GPCDAT_GPIO68   0x10U         // Data Register for this pin
#define GPIO_GPCDAT_GPIO69   0x20U         // Data Register for this pin
#define GPIO_GPCDAT_GPIO70   0x40U         // Data Register for this pin
#define GPIO_GPCDAT_GPIO71   0x80U         // Data Register for this pin
#define GPIO_GPCDAT_GPIO72   0x100U        // Data Register for this pin
#define GPIO_GPCDAT_GPIO73   0x200U        // Data Register for this pin
#define GPIO_GPCDAT_GPIO74   0x400U        // Data Register for this pin
#define GPIO_GPCDAT_GPIO75   0x800U        // Data Register for this pin
#define GPIO_GPCDAT_GPIO76   0x1000U       // Data Register for this pin
#define GPIO_GPCDAT_GPIO77   0x2000U       // Data Register for this pin
#define GPIO_GPCDAT_GPIO78   0x4000U       // Data Register for this pin
#define GPIO_GPCDAT_GPIO79   0x8000U       // Data Register for this pin
#define GPIO_GPCDAT_GPIO80   0x10000U      // Data Register for this pin
#define GPIO_GPCDAT_GPIO81   0x20000U      // Data Register for this pin
#define GPIO_GPCDAT_GPIO82   0x40000U      // Data Register for this pin
#define GPIO_GPCDAT_GPIO83   0x80000U      // Data Register for this pin
#define GPIO_GPCDAT_GPIO84   0x100000U     // Data Register for this pin
#define GPIO_GPCDAT_GPIO85   0x200000U     // Data Register for this pin
#define GPIO_GPCDAT_GPIO86   0x400000U     // Data Register for this pin
#define GPIO_GPCDAT_GPIO87   0x800000U     // Data Register for this pin
#define GPIO_GPCDAT_GPIO88   0x1000000U    // Data Register for this pin
#define GPIO_GPCDAT_GPIO89   0x2000000U    // Data Register for this pin
#define GPIO_GPCDAT_GPIO90   0x4000000U    // Data Register for this pin
#define GPIO_GPCDAT_GPIO91   0x8000000U    // Data Register for this pin
#define GPIO_GPCDAT_GPIO92   0x10000000U   // Data Register for this pin
#define GPIO_GPCDAT_GPIO93   0x20000000U   // Data Register for this pin
#define GPIO_GPCDAT_GPIO94   0x40000000U   // Data Register for this pin
#define GPIO_GPCDAT_GPIO95   0x80000000U   // Data Register for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCSET register
//
//*************************************************************************************************
#define GPIO_GPCSET_GPIO64   0x1U          // Output Set bit for this pin
#define GPIO_GPCSET_GPIO65   0x2U          // Output Set bit for this pin
#define GPIO_GPCSET_GPIO66   0x4U          // Output Set bit for this pin
#define GPIO_GPCSET_GPIO67   0x8U          // Output Set bit for this pin
#define GPIO_GPCSET_GPIO68   0x10U         // Output Set bit for this pin
#define GPIO_GPCSET_GPIO69   0x20U         // Output Set bit for this pin
#define GPIO_GPCSET_GPIO70   0x40U         // Output Set bit for this pin
#define GPIO_GPCSET_GPIO71   0x80U         // Output Set bit for this pin
#define GPIO_GPCSET_GPIO72   0x100U        // Output Set bit for this pin
#define GPIO_GPCSET_GPIO73   0x200U        // Output Set bit for this pin
#define GPIO_GPCSET_GPIO74   0x400U        // Output Set bit for this pin
#define GPIO_GPCSET_GPIO75   0x800U        // Output Set bit for this pin
#define GPIO_GPCSET_GPIO76   0x1000U       // Output Set bit for this pin
#define GPIO_GPCSET_GPIO77   0x2000U       // Output Set bit for this pin
#define GPIO_GPCSET_GPIO78   0x4000U       // Output Set bit for this pin
#define GPIO_GPCSET_GPIO79   0x8000U       // Output Set bit for this pin
#define GPIO_GPCSET_GPIO80   0x10000U      // Output Set bit for this pin
#define GPIO_GPCSET_GPIO81   0x20000U      // Output Set bit for this pin
#define GPIO_GPCSET_GPIO82   0x40000U      // Output Set bit for this pin
#define GPIO_GPCSET_GPIO83   0x80000U      // Output Set bit for this pin
#define GPIO_GPCSET_GPIO84   0x100000U     // Output Set bit for this pin
#define GPIO_GPCSET_GPIO85   0x200000U     // Output Set bit for this pin
#define GPIO_GPCSET_GPIO86   0x400000U     // Output Set bit for this pin
#define GPIO_GPCSET_GPIO87   0x800000U     // Output Set bit for this pin
#define GPIO_GPCSET_GPIO88   0x1000000U    // Output Set bit for this pin
#define GPIO_GPCSET_GPIO89   0x2000000U    // Output Set bit for this pin
#define GPIO_GPCSET_GPIO90   0x4000000U    // Output Set bit for this pin
#define GPIO_GPCSET_GPIO91   0x8000000U    // Output Set bit for this pin
#define GPIO_GPCSET_GPIO92   0x10000000U   // Output Set bit for this pin
#define GPIO_GPCSET_GPIO93   0x20000000U   // Output Set bit for this pin
#define GPIO_GPCSET_GPIO94   0x40000000U   // Output Set bit for this pin
#define GPIO_GPCSET_GPIO95   0x80000000U   // Output Set bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCCLEAR register
//
//*************************************************************************************************
#define GPIO_GPCCLEAR_GPIO64   0x1U          // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO65   0x2U          // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO66   0x4U          // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO67   0x8U          // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO68   0x10U         // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO69   0x20U         // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO70   0x40U         // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO71   0x80U         // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO72   0x100U        // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO73   0x200U        // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO74   0x400U        // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO75   0x800U        // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO76   0x1000U       // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO77   0x2000U       // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO78   0x4000U       // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO79   0x8000U       // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO80   0x10000U      // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO81   0x20000U      // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO82   0x40000U      // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO83   0x80000U      // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO84   0x100000U     // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO85   0x200000U     // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO86   0x400000U     // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO87   0x800000U     // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO88   0x1000000U    // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO89   0x2000000U    // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO90   0x4000000U    // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO91   0x8000000U    // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO92   0x10000000U   // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO93   0x20000000U   // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO94   0x40000000U   // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO95   0x80000000U   // Output Clear bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCTOGGLE register
//
//*************************************************************************************************
#define GPIO_GPCTOGGLE_GPIO64   0x1U          // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO65   0x2U          // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO66   0x4U          // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO67   0x8U          // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO68   0x10U         // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO69   0x20U         // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO70   0x40U         // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO71   0x80U         // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO72   0x100U        // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO73   0x200U        // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO74   0x400U        // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO75   0x800U        // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO76   0x1000U       // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO77   0x2000U       // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO78   0x4000U       // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO79   0x8000U       // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO80   0x10000U      // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO81   0x20000U      // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO82   0x40000U      // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO83   0x80000U      // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO84   0x100000U     // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO85   0x200000U     // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO86   0x400000U     // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO87   0x800000U     // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO88   0x1000000U    // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO89   0x2000000U    // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO90   0x4000000U    // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO91   0x8000000U    // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO92   0x10000000U   // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO93   0x20000000U   // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO94   0x40000000U   // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO95   0x80000000U   // Output Toggle bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPDDAT register
//
//*************************************************************************************************
#define GPIO_GPDDAT_GPIO96    0x1U          // Data Register for this pin
#define GPIO_GPDDAT_GPIO97    0x2U          // Data Register for this pin
#define GPIO_GPDDAT_GPIO98    0x4U          // Data Register for this pin
#define GPIO_GPDDAT_GPIO99    0x8U          // Data Register for this pin
#define GPIO_GPDDAT_GPIO100   0x10U         // Data Register for this pin
#define GPIO_GPDDAT_GPIO101   0x20U         // Data Register for this pin
#define GPIO_GPDDAT_GPIO102   0x40U         // Data Register for this pin
#define GPIO_GPDDAT_GPIO103   0x80U         // Data Register for this pin
#define GPIO_GPDDAT_GPIO104   0x100U        // Data Register for this pin
#define GPIO_GPDDAT_GPIO105   0x200U        // Data Register for this pin
#define GPIO_GPDDAT_GPIO106   0x400U        // Data Register for this pin
#define GPIO_GPDDAT_GPIO107   0x800U        // Data Register for this pin
#define GPIO_GPDDAT_GPIO108   0x1000U       // Data Register for this pin
#define GPIO_GPDDAT_GPIO109   0x2000U       // Data Register for this pin
#define GPIO_GPDDAT_GPIO110   0x4000U       // Data Register for this pin
#define GPIO_GPDDAT_GPIO111   0x8000U       // Data Register for this pin
#define GPIO_GPDDAT_GPIO112   0x10000U      // Data Register for this pin
#define GPIO_GPDDAT_GPIO113   0x20000U      // Data Register for this pin
#define GPIO_GPDDAT_GPIO114   0x40000U      // Data Register for this pin
#define GPIO_GPDDAT_GPIO115   0x80000U      // Data Register for this pin
#define GPIO_GPDDAT_GPIO116   0x100000U     // Data Register for this pin
#define GPIO_GPDDAT_GPIO117   0x200000U     // Data Register for this pin
#define GPIO_GPDDAT_GPIO118   0x400000U     // Data Register for this pin
#define GPIO_GPDDAT_GPIO119   0x800000U     // Data Register for this pin
#define GPIO_GPDDAT_GPIO120   0x1000000U    // Data Register for this pin
#define GPIO_GPDDAT_GPIO121   0x2000000U    // Data Register for this pin
#define GPIO_GPDDAT_GPIO122   0x4000000U    // Data Register for this pin
#define GPIO_GPDDAT_GPIO123   0x8000000U    // Data Register for this pin
#define GPIO_GPDDAT_GPIO124   0x10000000U   // Data Register for this pin
#define GPIO_GPDDAT_GPIO125   0x20000000U   // Data Register for this pin
#define GPIO_GPDDAT_GPIO126   0x40000000U   // Data Register for this pin
#define GPIO_GPDDAT_GPIO127   0x80000000U   // Data Register for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPDSET register
//
//*************************************************************************************************
#define GPIO_GPDSET_GPIO96    0x1U          // Output Set bit for this pin
#define GPIO_GPDSET_GPIO97    0x2U          // Output Set bit for this pin
#define GPIO_GPDSET_GPIO98    0x4U          // Output Set bit for this pin
#define GPIO_GPDSET_GPIO99    0x8U          // Output Set bit for this pin
#define GPIO_GPDSET_GPIO100   0x10U         // Output Set bit for this pin
#define GPIO_GPDSET_GPIO101   0x20U         // Output Set bit for this pin
#define GPIO_GPDSET_GPIO102   0x40U         // Output Set bit for this pin
#define GPIO_GPDSET_GPIO103   0x80U         // Output Set bit for this pin
#define GPIO_GPDSET_GPIO104   0x100U        // Output Set bit for this pin
#define GPIO_GPDSET_GPIO105   0x200U        // Output Set bit for this pin
#define GPIO_GPDSET_GPIO106   0x400U        // Output Set bit for this pin
#define GPIO_GPDSET_GPIO107   0x800U        // Output Set bit for this pin
#define GPIO_GPDSET_GPIO108   0x1000U       // Output Set bit for this pin
#define GPIO_GPDSET_GPIO109   0x2000U       // Output Set bit for this pin
#define GPIO_GPDSET_GPIO110   0x4000U       // Output Set bit for this pin
#define GPIO_GPDSET_GPIO111   0x8000U       // Output Set bit for this pin
#define GPIO_GPDSET_GPIO112   0x10000U      // Output Set bit for this pin
#define GPIO_GPDSET_GPIO113   0x20000U      // Output Set bit for this pin
#define GPIO_GPDSET_GPIO114   0x40000U      // Output Set bit for this pin
#define GPIO_GPDSET_GPIO115   0x80000U      // Output Set bit for this pin
#define GPIO_GPDSET_GPIO116   0x100000U     // Output Set bit for this pin
#define GPIO_GPDSET_GPIO117   0x200000U     // Output Set bit for this pin
#define GPIO_GPDSET_GPIO118   0x400000U     // Output Set bit for this pin
#define GPIO_GPDSET_GPIO119   0x800000U     // Output Set bit for this pin
#define GPIO_GPDSET_GPIO120   0x1000000U    // Output Set bit for this pin
#define GPIO_GPDSET_GPIO121   0x2000000U    // Output Set bit for this pin
#define GPIO_GPDSET_GPIO122   0x4000000U    // Output Set bit for this pin
#define GPIO_GPDSET_GPIO123   0x8000000U    // Output Set bit for this pin
#define GPIO_GPDSET_GPIO124   0x10000000U   // Output Set bit for this pin
#define GPIO_GPDSET_GPIO125   0x20000000U   // Output Set bit for this pin
#define GPIO_GPDSET_GPIO126   0x40000000U   // Output Set bit for this pin
#define GPIO_GPDSET_GPIO127   0x80000000U   // Output Set bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPDCLEAR register
//
//*************************************************************************************************
#define GPIO_GPDCLEAR_GPIO96    0x1U          // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO97    0x2U          // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO98    0x4U          // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO99    0x8U          // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO100   0x10U         // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO101   0x20U         // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO102   0x40U         // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO103   0x80U         // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO104   0x100U        // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO105   0x200U        // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO106   0x400U        // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO107   0x800U        // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO108   0x1000U       // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO109   0x2000U       // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO110   0x4000U       // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO111   0x8000U       // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO112   0x10000U      // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO113   0x20000U      // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO114   0x40000U      // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO115   0x80000U      // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO116   0x100000U     // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO117   0x200000U     // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO118   0x400000U     // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO119   0x800000U     // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO120   0x1000000U    // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO121   0x2000000U    // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO122   0x4000000U    // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO123   0x8000000U    // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO124   0x10000000U   // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO125   0x20000000U   // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO126   0x40000000U   // Output Clear bit for this pin
#define GPIO_GPDCLEAR_GPIO127   0x80000000U   // Output Clear bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPDTOGGLE register
//
//*************************************************************************************************
#define GPIO_GPDTOGGLE_GPIO96    0x1U          // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO97    0x2U          // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO98    0x4U          // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO99    0x8U          // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO100   0x10U         // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO101   0x20U         // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO102   0x40U         // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO103   0x80U         // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO104   0x100U        // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO105   0x200U        // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO106   0x400U        // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO107   0x800U        // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO108   0x1000U       // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO109   0x2000U       // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO110   0x4000U       // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO111   0x8000U       // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO112   0x10000U      // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO113   0x20000U      // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO114   0x40000U      // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO115   0x80000U      // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO116   0x100000U     // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO117   0x200000U     // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO118   0x400000U     // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO119   0x800000U     // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO120   0x1000000U    // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO121   0x2000000U    // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO122   0x4000000U    // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO123   0x8000000U    // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO124   0x10000000U   // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO125   0x20000000U   // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO126   0x40000000U   // Output Toggle bit for this pin
#define GPIO_GPDTOGGLE_GPIO127   0x80000000U   // Output Toggle bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPEDAT register
//
//*************************************************************************************************
#define GPIO_GPEDAT_GPIO128   0x1U          // Data Register for this pin
#define GPIO_GPEDAT_GPIO129   0x2U          // Data Register for this pin
#define GPIO_GPEDAT_GPIO130   0x4U          // Data Register for this pin
#define GPIO_GPEDAT_GPIO131   0x8U          // Data Register for this pin
#define GPIO_GPEDAT_GPIO132   0x10U         // Data Register for this pin
#define GPIO_GPEDAT_GPIO133   0x20U         // Data Register for this pin
#define GPIO_GPEDAT_GPIO134   0x40U         // Data Register for this pin
#define GPIO_GPEDAT_GPIO135   0x80U         // Data Register for this pin
#define GPIO_GPEDAT_GPIO136   0x100U        // Data Register for this pin
#define GPIO_GPEDAT_GPIO137   0x200U        // Data Register for this pin
#define GPIO_GPEDAT_GPIO138   0x400U        // Data Register for this pin
#define GPIO_GPEDAT_GPIO139   0x800U        // Data Register for this pin
#define GPIO_GPEDAT_GPIO140   0x1000U       // Data Register for this pin
#define GPIO_GPEDAT_GPIO141   0x2000U       // Data Register for this pin
#define GPIO_GPEDAT_GPIO142   0x4000U       // Data Register for this pin
#define GPIO_GPEDAT_GPIO143   0x8000U       // Data Register for this pin
#define GPIO_GPEDAT_GPIO144   0x10000U      // Data Register for this pin
#define GPIO_GPEDAT_GPIO145   0x20000U      // Data Register for this pin
#define GPIO_GPEDAT_GPIO146   0x40000U      // Data Register for this pin
#define GPIO_GPEDAT_GPIO147   0x80000U      // Data Register for this pin
#define GPIO_GPEDAT_GPIO148   0x100000U     // Data Register for this pin
#define GPIO_GPEDAT_GPIO149   0x200000U     // Data Register for this pin
#define GPIO_GPEDAT_GPIO150   0x400000U     // Data Register for this pin
#define GPIO_GPEDAT_GPIO151   0x800000U     // Data Register for this pin
#define GPIO_GPEDAT_GPIO152   0x1000000U    // Data Register for this pin
#define GPIO_GPEDAT_GPIO153   0x2000000U    // Data Register for this pin
#define GPIO_GPEDAT_GPIO154   0x4000000U    // Data Register for this pin
#define GPIO_GPEDAT_GPIO155   0x8000000U    // Data Register for this pin
#define GPIO_GPEDAT_GPIO156   0x10000000U   // Data Register for this pin
#define GPIO_GPEDAT_GPIO157   0x20000000U   // Data Register for this pin
#define GPIO_GPEDAT_GPIO158   0x40000000U   // Data Register for this pin
#define GPIO_GPEDAT_GPIO159   0x80000000U   // Data Register for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPESET register
//
//*************************************************************************************************
#define GPIO_GPESET_GPIO128   0x1U          // Output Set bit for this pin
#define GPIO_GPESET_GPIO129   0x2U          // Output Set bit for this pin
#define GPIO_GPESET_GPIO130   0x4U          // Output Set bit for this pin
#define GPIO_GPESET_GPIO131   0x8U          // Output Set bit for this pin
#define GPIO_GPESET_GPIO132   0x10U         // Output Set bit for this pin
#define GPIO_GPESET_GPIO133   0x20U         // Output Set bit for this pin
#define GPIO_GPESET_GPIO134   0x40U         // Output Set bit for this pin
#define GPIO_GPESET_GPIO135   0x80U         // Output Set bit for this pin
#define GPIO_GPESET_GPIO136   0x100U        // Output Set bit for this pin
#define GPIO_GPESET_GPIO137   0x200U        // Output Set bit for this pin
#define GPIO_GPESET_GPIO138   0x400U        // Output Set bit for this pin
#define GPIO_GPESET_GPIO139   0x800U        // Output Set bit for this pin
#define GPIO_GPESET_GPIO140   0x1000U       // Output Set bit for this pin
#define GPIO_GPESET_GPIO141   0x2000U       // Output Set bit for this pin
#define GPIO_GPESET_GPIO142   0x4000U       // Output Set bit for this pin
#define GPIO_GPESET_GPIO143   0x8000U       // Output Set bit for this pin
#define GPIO_GPESET_GPIO144   0x10000U      // Output Set bit for this pin
#define GPIO_GPESET_GPIO145   0x20000U      // Output Set bit for this pin
#define GPIO_GPESET_GPIO146   0x40000U      // Output Set bit for this pin
#define GPIO_GPESET_GPIO147   0x80000U      // Output Set bit for this pin
#define GPIO_GPESET_GPIO148   0x100000U     // Output Set bit for this pin
#define GPIO_GPESET_GPIO149   0x200000U     // Output Set bit for this pin
#define GPIO_GPESET_GPIO150   0x400000U     // Output Set bit for this pin
#define GPIO_GPESET_GPIO151   0x800000U     // Output Set bit for this pin
#define GPIO_GPESET_GPIO152   0x1000000U    // Output Set bit for this pin
#define GPIO_GPESET_GPIO153   0x2000000U    // Output Set bit for this pin
#define GPIO_GPESET_GPIO154   0x4000000U    // Output Set bit for this pin
#define GPIO_GPESET_GPIO155   0x8000000U    // Output Set bit for this pin
#define GPIO_GPESET_GPIO156   0x10000000U   // Output Set bit for this pin
#define GPIO_GPESET_GPIO157   0x20000000U   // Output Set bit for this pin
#define GPIO_GPESET_GPIO158   0x40000000U   // Output Set bit for this pin
#define GPIO_GPESET_GPIO159   0x80000000U   // Output Set bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPECLEAR register
//
//*************************************************************************************************
#define GPIO_GPECLEAR_GPIO128   0x1U          // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO129   0x2U          // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO130   0x4U          // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO131   0x8U          // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO132   0x10U         // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO133   0x20U         // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO134   0x40U         // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO135   0x80U         // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO136   0x100U        // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO137   0x200U        // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO138   0x400U        // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO139   0x800U        // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO140   0x1000U       // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO141   0x2000U       // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO142   0x4000U       // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO143   0x8000U       // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO144   0x10000U      // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO145   0x20000U      // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO146   0x40000U      // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO147   0x80000U      // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO148   0x100000U     // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO149   0x200000U     // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO150   0x400000U     // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO151   0x800000U     // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO152   0x1000000U    // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO153   0x2000000U    // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO154   0x4000000U    // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO155   0x8000000U    // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO156   0x10000000U   // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO157   0x20000000U   // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO158   0x40000000U   // Output Clear bit for this pin
#define GPIO_GPECLEAR_GPIO159   0x80000000U   // Output Clear bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPETOGGLE register
//
//*************************************************************************************************
#define GPIO_GPETOGGLE_GPIO128   0x1U          // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO129   0x2U          // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO130   0x4U          // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO131   0x8U          // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO132   0x10U         // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO133   0x20U         // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO134   0x40U         // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO135   0x80U         // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO136   0x100U        // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO137   0x200U        // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO138   0x400U        // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO139   0x800U        // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO140   0x1000U       // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO141   0x2000U       // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO142   0x4000U       // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO143   0x8000U       // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO144   0x10000U      // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO145   0x20000U      // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO146   0x40000U      // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO147   0x80000U      // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO148   0x100000U     // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO149   0x200000U     // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO150   0x400000U     // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO151   0x800000U     // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO152   0x1000000U    // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO153   0x2000000U    // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO154   0x4000000U    // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO155   0x8000000U    // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO156   0x10000000U   // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO157   0x20000000U   // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO158   0x40000000U   // Output Toggle bit for this pin
#define GPIO_GPETOGGLE_GPIO159   0x80000000U   // Output Toggle bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPFDAT register
//
//*************************************************************************************************
#define GPIO_GPFDAT_GPIO160   0x1U     // Data Register for this pin
#define GPIO_GPFDAT_GPIO161   0x2U     // Data Register for this pin
#define GPIO_GPFDAT_GPIO162   0x4U     // Data Register for this pin
#define GPIO_GPFDAT_GPIO163   0x8U     // Data Register for this pin
#define GPIO_GPFDAT_GPIO164   0x10U    // Data Register for this pin
#define GPIO_GPFDAT_GPIO165   0x20U    // Data Register for this pin
#define GPIO_GPFDAT_GPIO166   0x40U    // Data Register for this pin
#define GPIO_GPFDAT_GPIO167   0x80U    // Data Register for this pin
#define GPIO_GPFDAT_GPIO168   0x100U   // Data Register for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPFSET register
//
//*************************************************************************************************
#define GPIO_GPFSET_GPIO160   0x1U     // Output Set bit for this pin
#define GPIO_GPFSET_GPIO161   0x2U     // Output Set bit for this pin
#define GPIO_GPFSET_GPIO162   0x4U     // Output Set bit for this pin
#define GPIO_GPFSET_GPIO163   0x8U     // Output Set bit for this pin
#define GPIO_GPFSET_GPIO164   0x10U    // Output Set bit for this pin
#define GPIO_GPFSET_GPIO165   0x20U    // Output Set bit for this pin
#define GPIO_GPFSET_GPIO166   0x40U    // Output Set bit for this pin
#define GPIO_GPFSET_GPIO167   0x80U    // Output Set bit for this pin
#define GPIO_GPFSET_GPIO168   0x100U   // Output Set bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPFCLEAR register
//
//*************************************************************************************************
#define GPIO_GPFCLEAR_GPIO160   0x1U     // Output Clear bit for this pin
#define GPIO_GPFCLEAR_GPIO161   0x2U     // Output Clear bit for this pin
#define GPIO_GPFCLEAR_GPIO162   0x4U     // Output Clear bit for this pin
#define GPIO_GPFCLEAR_GPIO163   0x8U     // Output Clear bit for this pin
#define GPIO_GPFCLEAR_GPIO164   0x10U    // Output Clear bit for this pin
#define GPIO_GPFCLEAR_GPIO165   0x20U    // Output Clear bit for this pin
#define GPIO_GPFCLEAR_GPIO166   0x40U    // Output Clear bit for this pin
#define GPIO_GPFCLEAR_GPIO167   0x80U    // Output Clear bit for this pin
#define GPIO_GPFCLEAR_GPIO168   0x100U   // Output Clear bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPFTOGGLE register
//
//*************************************************************************************************
#define GPIO_GPFTOGGLE_GPIO160   0x1U     // Output Toggle bit for this pin
#define GPIO_GPFTOGGLE_GPIO161   0x2U     // Output Toggle bit for this pin
#define GPIO_GPFTOGGLE_GPIO162   0x4U     // Output Toggle bit for this pin
#define GPIO_GPFTOGGLE_GPIO163   0x8U     // Output Toggle bit for this pin
#define GPIO_GPFTOGGLE_GPIO164   0x10U    // Output Toggle bit for this pin
#define GPIO_GPFTOGGLE_GPIO165   0x20U    // Output Toggle bit for this pin
#define GPIO_GPFTOGGLE_GPIO166   0x40U    // Output Toggle bit for this pin
#define GPIO_GPFTOGGLE_GPIO167   0x80U    // Output Toggle bit for this pin
#define GPIO_GPFTOGGLE_GPIO168   0x100U   // Output Toggle bit for this pin




#endif
