//#############################################################################
//
// FILE:   startup_cm.c
//
// TITLE:  Cortex M4 Family Interrupt Vector Table for CGT.
//
//#############################################################################
//
//
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
//#############################################################################

#include <stdint.h>

//
// Forward declaration of the default fault handlers.
//
static void resetISR(void);
static void nmiISR(void);
static void faultISR(void);
static void defaultISR(void);

//
// External declaration for the reset handler that is to be called when the
// processor is started     
//                                               
extern void _c_int00(void);

//
// Linker variable that marks the top of the stack.
//
extern unsigned long __STACK_END;

// External declarations for the interrupt handlers used by the application.
// To be added by user

//
// Interrupt vector table. In the RAM variant, the vectorTableRAM is used and 
// in the Flash variant, the vectorTableFlash is used. The Flash variant can be
// be used when memory is a concern and the RAM variant can be used when 
// speed is a concern.
//                          
#ifdef _FLASH
#pragma RETAIN(vectorTableFlash)
#pragma DATA_ALIGN(vectorTableFlash, 1024U)
#pragma DATA_SECTION(vectorTableFlash, ".vftable")
void (* const vectorTableFlash[])(void) =
#else
#pragma RETAIN(vectorTableRAM)
#pragma DATA_ALIGN(vectorTableRAM, 1024U)
#pragma DATA_SECTION(vectorTableRAM, ".vtable")
void (* const vectorTableRAM[])(void) =
#endif
{
    (void (*)(void))((uint32_t)&__STACK_END),
                                            /* The initial stack pointer */
    resetISR,                               /* The reset handler         */
    nmiISR,                                 /* The NMI handler           */
    faultISR,                               /* The hard fault handler    */
    defaultISR,                             /* The MPU fault handler     */
    defaultISR,                             /* The bus fault handler     */
    defaultISR,                             /* The usage fault handler   */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    0,                                      /* Reserved                  */
    defaultISR,                             /* SVCall handler            */
    defaultISR,                             /* Debug monitor handler     */
    0,                                      /* Reserved                  */
    defaultISR,                             /* The PendSV handler        */
    defaultISR,                             /* The SysTick handler       */
    defaultISR,                             /* MCANSS_0 handler          */
    defaultISR,                             /* MCANSS_1 handler          */
    defaultISR,                             /* MCANSS_WAKE_AND_TS_PLS ISR*/
    defaultISR,                             /* MCANSS_ECC_CORR_PLS ISR   */
    defaultISR,                             /* Reserved                  */
    defaultISR,                             /* ECAT ISR                  */
    defaultISR,                             /* ECAT_SYNC0 ISR            */
    defaultISR,                             /* ECAT_SYNC1 ISR            */
    defaultISR,                             /* ECAT_RST ISR  ISR         */
    defaultISR,                             /* CANA0 ISR                 */
    defaultISR,                             /* CANA1 ISR                 */
    defaultISR,                             /* CANB0 ISR                 */
    defaultISR,                             /* CANB1 ISR                 */
    defaultISR,                             /* EMAC ISR                  */
    defaultISR,                             /* EMAC_TX0 ISR              */
    defaultISR,                             /* EMAC_TX1 ISR              */
    defaultISR,                             /* EMAC_RX0 ISR              */
    defaultISR,                             /* EMAC_RX1 ISR              */
    defaultISR,                             /* UART0 ISR                 */
    defaultISR,                             /* Reserved                  */
    defaultISR,                             /* SSI0 ISR                  */
    defaultISR,                             /* Reserved                  */
    defaultISR,                             /* I2C0 ISR                  */
    defaultISR,                             /* Reserved                  */
    defaultISR,                             /* USB ISR                   */
    defaultISR,                             /* UDMA_SW ISR               */
    defaultISR,                             /* UDMA_ERR ISR              */
    defaultISR,                             /* Reserved                  */
    defaultISR,                             /* Reserved                  */
    defaultISR,                             /* CPU1TOCMIPC0 ISR          */
    defaultISR,                             /* CPU1TOCMIPC1 ISR          */
    defaultISR,                             /* CPU1TOCMIPC2 ISR          */
    defaultISR,                             /* CPU1TOCMIPC3 ISR          */
    defaultISR,                             /* CPU1TOCMIPC4 ISR          */
    defaultISR,                             /* CPU1TOCMIPC5 ISR          */
    defaultISR,                             /* CPU1TOCMIPC6 ISR          */
    defaultISR,                             /* CPU1TOCMIPC7 ISR          */
    defaultISR,                             /* CPU2TOCMIPC0 ISR          */
    defaultISR,                             /* CPU2TOCMIPC1 ISR          */
    defaultISR,                             /* CPU2TOCMIPC2 ISR          */
    defaultISR,                             /* CPU2TOCMIPC3 ISR          */
    defaultISR,                             /* CPU2TOCMIPC4 ISR          */
    defaultISR,                             /* CPU2TOCMIPC5 ISR          */
    defaultISR,                             /* CPU2TOCMIPC6 ISR          */
    defaultISR,                             /* CPU2TOCMIPC7 ISR          */
    defaultISR,                             /* FMC ISR                   */
    defaultISR,                             /* FMC_CORR_ERR ISR          */
    defaultISR,                             /* AES Interrupt ISR         */
    defaultISR,                             /* TIMER0 ISR                */
    defaultISR,                             /* TIMER1 ISR                */
    defaultISR,                             /* TIMER2 ISR                */
    defaultISR,                             /* CMRAM_TESTERROR_LOG ISR   */
    defaultISR,                             /* Reserved 52               */
    defaultISR,                             /* Reserved 53               */
    defaultISR,                             /* Reserved 54               */
    defaultISR,                             /* Reserved 55               */
    defaultISR,                             /* Reserved 56               */
    defaultISR,                             /* Reserved 57               */
    defaultISR,                             /* Reserved 58               */
    defaultISR,                             /* Reserved 59               */
    defaultISR,                             /* Reserved 60               */
    defaultISR,                             /* Reserved 61               */
    defaultISR,                             /* Reserved 62               */
    defaultISR                              /* Reserved 63               */
};

//
// This is the code that gets called when the processor first starts execution
// following a reset event. 
// Any actions (such as making decisions based on the reset cause register,    
// and resetting the bits in that register) are left solely in the hands of    
// the application.
//                                                               
#pragma RETAIN(resetISR)
#pragma CODE_SECTION(resetISR, ".resetisr")
void resetISR(void)
{
    //
    // Jump to the CCS C Initialization Routine.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

//
// This is the code that gets called when the processor receives a NMI.  This 
// simply enters an infinite loop, preserving the system state for examination
// by a debugger. 
//                                                            
static void nmiISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }

}

//
// This is the code that gets called when the processor receives a fault       
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger. 
//                                             
static void faultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }

}

//
// This is the code that gets called when the processor receives an unexpected 
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.    
//                                          
static void defaultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}
