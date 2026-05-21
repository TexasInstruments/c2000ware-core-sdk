//#############################################################################
//
// FILE:   cpu_reg_access.c.c
//
//! \addtogroup driver_example_list
//! <h1>CPU Register Access</h1> 
//!
//! This example demonstrates functions which can be used to 
//! access CPU register contents using C-Callable assembly APIs .
//!
//
//#############################################################################
//
//
// $Copyright$
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "c28x_core_registers.h"


#pragma RETAIN(myPC)
#pragma RETAIN(mySP1)
#pragma RETAIN(mySP2)
#pragma RETAIN(myAux0)
#pragma RETAIN(myAux6)
#pragma RETAIN(myAux7)
#pragma RETAIN(myAux8)
#pragma RETAIN(myStatus0)
#pragma RETAIN(myStatus1)
uint16_t mySP1, mySP2;
uint16_t myStatus0, myStatus1;
uint32_t myPC, myAux0, myAux6, myAux7, myAux8;


//
// Main
//
void main(void)
{

    mySP1 = __get_SP();
    __set_SP(mySP1 + 0x5);

    mySP2 = __get_SP();

    if (mySP2 != mySP1 + 0x5 )
    {
        ESTOP0;
    }

    myPC = __get_PC();

    myAux0 = __get_Aux(0);
    myAux6 = __get_Aux(6);
    myAux7 = __get_Aux(7);
    myAux8 = __get_Aux(8);  // error, returns 0x5A5A5A5A

    myStatus0 = __get_Status0();
    myStatus1 = __get_Status1();

}

//
// End of File
//
