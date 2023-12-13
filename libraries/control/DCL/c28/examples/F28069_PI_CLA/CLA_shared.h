/*  CLA_shared.h */

#ifndef _C_CLA_SHARED_H
#define _C_CLA_SHARED_H

#include "DCLCLA.h"
#include "F2806x_Cla_typedefs.h"

#define CLA_PROG_ENABLE      0x0001
#define CLARAM0_ENABLE       0x0010
#define CLARAM1_ENABLE       0x0020
#define CLARAM2_ENABLE       0x0040
#define CLA_RAM0CPUE         0x0100
#define CLA_RAM1CPUE         0x0200
#define CLA_RAM2CPUE         0x0400

/* shared controller data */
extern float rk;
extern float yk;
extern float uk;
extern DCL_PI_CLA pi1;

// CLA memory address symbols
extern Uint16 Cla1funcsLoadStart;
extern Uint16 Cla1funcsLoadEnd;
extern Uint16 Cla1funcsLoadSize;
extern Uint16 Cla1funcsRunStart;
extern Uint16 Cla1Prog_Start;

// CLA math table symbols
extern Uint16 Cla1mathTablesLoadStart;
extern Uint16 Cla1mathTablesLoadEnd;
extern Uint16 Cla1mathTablesLoadSize;
extern Uint16 Cla1mathTablesRunStart;

// CLA C Tasks
__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();



#endif // _C_CLA_SHARED_H

/* end of file */
