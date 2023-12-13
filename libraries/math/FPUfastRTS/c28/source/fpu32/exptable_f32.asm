;;#############################################################################
;;! \file exptable_f32.asm
;;! \brief  Exponent Lookup Table (89) 
;;! \author Vishal Coelho 
;;! \date   19-Jan-2017
;;! 
;;  Revision History:
;;+----------+---------------+------------------------------------------------+
;;| DATE     | AUTHOR        | CHANGE                                         |
;;+----------+---------------+------------------------------------------------+
;;| 01/16/18 | Ritvik Sadana | Modified symbol names to keep naming           |
;;|          |               | consistent with FPU64 symbols.                 |
;;+----------+---------------+------------------------------------------------+
;;
;;#############################################################################
;;!
;;! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
;;!	All rights reserved not granted herein.
;;!	Limited License.
;;!
;;! Texas Instruments Incorporated grants a world-wide, royalty-free,
;;! non-exclusive license under copyrights and patents it now or hereafter
;;! owns or controls to make, have made, use, import, offer to sell and sell
;;! ("Utilize") this software subject to the terms herein. With respect to the
;;! foregoing patent license, such license is granted solely to the extent that
;;! any such patent is necessary to Utilize the software alone. The patent
;;! license shall not apply to any combinations which include this software,
;;! other than combinations with devices manufactured by or for TI 
;;! ("TI Devices").
;;! No hardware patent is licensed hereunder.
;;!
;;! Redistributions must preserve existing copyright notices and reproduce this
;;! license (including the above copyright notice and the disclaimer and
;;! (if applicable) source code license limitations below) in the documentation
;;!  and/or other materials provided with the distribution.
;;!
;;! Redistribution and use in binary form, without modification, are permitted
;;! provided that the following conditions are met:
;;!
;;! * No reverse engineering, decompilation, or disassembly of this software is 
;;! permitted with respect to any software provided in binary form.
;;! * Any redistribution and use are licensed by TI for use only 
;;!   with TI Devices.
;;! * Nothing shall obligate TI to provide you with source code for the 
;;!   software licensed and provided to you in object code.
;;!
;;! If software source code is provided to you, modification and redistribution
;;! of the source code are permitted provided that the following conditions 
;;! are met:
;;!
;;! * any redistribution and use of the source code, including any resulting
;;!   derivative works, are licensed by TI for use only with TI Devices.
;;! * any redistribution and use of any object code compiled from the source
;;!   code and any resulting derivative works, are licensed by TI for use 
;;!   only with TI Devices.
;;!
;;! Neither the name of Texas Instruments Incorporated nor the names of its
;;! suppliers may be used to endorse or promote products derived from this 
;;! software without specific prior written permission.
;;#############################################################################

    .if __TI_EABI__
    .asg    FPU32expTableCoeff, _FPU32expTableCoeff
    .asg    FPU32expTableCoeffEnd, _FPU32expTableCoeffEnd
    .asg    FPU32expTable, _FPU32expTable
    .asg    FPU32expTableEnd, _FPU32expTableEnd
    .endif
    .def    _FPU32expTableCoeff
    .def    _FPU32expTableCoeffEnd
    .def    _FPU32expTable
    .def    _FPU32expTableEnd

    .sect   "FPUmathTables"

_FPU32expTableCoeff:
    .float 0.1428571428571  ; 1/7
    .float 0.1666666666667  ; 1/6
    .float 0.2000000000000  ; 1/5
    .float 0.2500000000000  ; 1/4
    .float 0.3333333333333  ; 1/3
    .float 0.5000000000000  ; 1/2
_FPU32expTableCoeffEnd:

_FPU32expTable:
    .float  1.0000000000000e+00     ; exp(  0)
    .float  2.7182817459106e+00     ; exp(  1)
    .float  7.3890562057495e+00     ; exp(  2)
    .float  2.0085536956787e+01     ; exp(  3)
    .float  5.4598152160645e+01     ; exp(  4)
    .float  1.4841316223145e+02     ; exp(  5)
    .float  4.0342880249023e+02     ; exp(  6)
    .float  1.0966331787109e+03     ; exp(  7)
    .float  2.9809580078125e+03     ; exp(  8)
    .float  8.1030839843750e+03     ; exp(  9)
    .float  2.2026464843750e+04     ; exp( 10)
    .float  5.9874140625000e+04     ; exp( 11)
    .float  1.6275479687500e+05     ; exp( 12)
    .float  4.4241337500000e+05     ; exp( 13)
    .float  1.2026042500000e+06     ; exp( 14)
    .float  3.2690175000000e+06     ; exp( 15)
    .float  8.8861110000000e+06     ; exp( 16)
    .float  2.4154952000000e+07     ; exp( 17)
    .float  6.5659968000000e+07     ; exp( 18)
    .float  1.7848230400000e+08     ; exp( 19)
    .float  4.8516518400000e+08     ; exp( 20)
    .float  1.3188157440000e+09     ; exp( 21)
    .float  3.5849128960000e+09     ; exp( 22)
    .float  9.7448038400000e+09     ; exp( 23)
    .float  2.6489122816000e+10     ; exp( 24)
    .float  7.2004902912000e+10     ; exp( 25)
    .float  1.9572962099200e+11     ; exp( 26)
    .float  5.3204824883200e+11     ; exp( 27)
    .float  1.4462570987520e+12     ; exp( 28)
    .float  3.9313342464000e+12     ; exp( 29)
    .float  1.0686474223616e+13     ; exp( 30)
    .float  2.9048849825792e+13     ; exp( 31)
    .float  7.8962956959744e+13     ; exp( 32)
    .float  2.1464357430886e+14     ; exp( 33)
    .float  5.8346171059405e+14     ; exp( 34)
    .float  1.5860134450299e+15     ; exp( 35)
    .float  4.3112315318436e+15     ; exp( 36)
    .float  1.1719142537167e+16     ; exp( 37)
    .float  3.1855931348222e+16     ; exp( 38)
    .float  8.6593404045099e+16     ; exp( 39)
    .float  2.3538527034042e+17     ; exp( 40)
    .float  6.3984347447611e+17     ; exp( 41)
    .float  1.7392749753422e+18     ; exp( 42)
    .float  4.7278395262973e+18     ; exp( 43)
    .float  1.2851599879818e+19     ; exp( 44)
    .float  3.4934270576908e+19     ; exp( 45)
    .float  9.4961195300688e+19     ; exp( 46)
    .float  2.5813128932181e+20     ; exp( 47)
    .float  7.0167362905576e+20     ; exp( 48)
    .float  1.9073464997854e+21     ; exp( 49)
    .float  5.1847054576655e+21     ; exp( 50)
    .float  1.4093490364499e+22     ; exp( 51)
    .float  3.8310081899410e+22     ; exp( 52)
    .float  1.0413759887482e+23     ; exp( 53)
    .float  2.8307533984544e+23     ; exp( 54)
    .float  7.6947854714906e+23     ; exp( 55)
    .float  2.0916594490409e+24     ; exp( 56)
    .float  5.6857200220030e+24     ; exp( 57)
    .float  1.5455390078758e+25     ; exp( 58)
    .float  4.2012104528050e+25     ; exp( 59)
    .float  1.1420073962419e+26     ; exp( 60)
    .float  3.1042977826582e+26     ; exp( 61)
    .float  8.4383568232726e+26     ; exp( 62)
    .float  2.2937831182341e+27     ; exp( 63)
    .float  6.2351494320497e+27     ; exp( 64)
    .float  1.6948892066757e+28     ; exp( 65)
    .float  4.6071865476425e+28     ; exp( 66)
    .float  1.2523631854447e+29     ; exp( 67)
    .float  3.4042761729011e+29     ; exp( 68)
    .float  9.2537816213739e+29     ; exp( 69)
    .float  2.5154387003559e+30     ; exp( 70)
    .float  6.8376711375563e+30     ; exp( 71)
    .float  1.8586717056324e+31     ; exp( 72)
    .float  5.0523935602179e+31     ; exp( 73)
    .float  1.3733829622695e+32     ; exp( 74)
    .float  3.7332418496475e+32     ; exp( 75)
    .float  1.0148004187492e+33     ; exp( 76)
    .float  2.7585135499700e+33     ; exp( 77)
    .float  7.4984169815783e+33     ; exp( 78)
    .float  2.0382810254658e+34     ; exp( 79)
    .float  5.5406224846768e+34     ; exp( 80)
    .float  1.5060972626944e+35     ; exp( 81)
    .float  4.0939968518217e+35     ; exp( 82)
    .float  1.1128637275465e+36     ; exp( 83)
    .float  3.0250773415263e+36     ; exp( 84)
    .float  8.2230123930183e+36     ; exp( 85)
    .float  2.2352465286716e+37     ; exp( 86)
    .float  6.0760303473996e+37     ; exp( 87)
    .float  1.6516362661361e+38     ; exp( 88)
_FPU32expTableEnd:

;; End of File
