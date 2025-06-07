#ifndef TRBT_H_
#define TRBT_H_

#ifdef _TMS320C28X
#include "driverlib.h"
#include "device.h"

#define CHECK_RESULT(r)     if (!r)\
                            {\
                                ESTOP0;\
                            }\

#endif
#ifdef SOC_AM243X

#define ESTOP0  __asm__("BKPT")

#define CHECK_RESULT(r)     if (!r)\
                            {\
                                ESTOP0;\
                            }\

#endif

#endif
