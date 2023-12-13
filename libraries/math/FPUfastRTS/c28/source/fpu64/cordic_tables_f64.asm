;;#############################################################################
;;! \file   cordic_tables_f64.asm 
;;! \brief  CORDIC Tables (64) 
;;! \author Vishal Coelho 
;;! \date   15-Nov-2016
;;! 
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
    .asg    CORDIC_F64_atanTable, _CORDIC_F64_atanTable
    .asg    CORDIC_F64_atanTableEnd, _CORDIC_F64_atanTableEnd
    .asg    CORDIC_F64_PI_O_2, _CORDIC_F64_PI_O_2
    .asg    CORDIC_F64_PI, _CORDIC_F64_PI
    .asg    CORDIC_F64_3PI_O_2, _CORDIC_F64_3PI_O_2
    .asg    CORDIC_F64_2PI, _CORDIC_F64_2PI
    .asg    CORDIC_F64_scaleFactor, _CORDIC_F64_scaleFactor
    .endif
    .def    _CORDIC_F64_atanTable
    .def    _CORDIC_F64_atanTableEnd

    .sect   "FPU64mathTables"
    .align  2
_CORDIC_F64_atanTable:
    .long   0x442D1800, 0x1921FB54  ; IQ61(arctan(2^-  0)) 
    .long   0xB0DDA780, 0x0ED63382  ; IQ61(arctan(2^-  1)) 
    .long   0x4B203740, 0x07D6DD7E  ; IQ61(arctan(2^-  2)) 
    .long   0x5585EDC0, 0x03FAB753  ; IQ61(arctan(2^-  3)) 
    .long   0x72CFDEA0, 0x01FF55BB  ; IQ61(arctan(2^-  4)) 
    .long   0xDD4BB128, 0x00FFEAAD  ; IQ61(arctan(2^-  5)) 
    .long   0x6EEDCA6C, 0x007FFD55  ; IQ61(arctan(2^-  6)) 
    .long   0xAB77752E, 0x003FFFAA  ; IQ61(arctan(2^-  7)) 
    .long   0x555BBBB7, 0x001FFFF5  ; IQ61(arctan(2^-  8)) 
    .long   0xAAAADDDE, 0x000FFFFE  ; IQ61(arctan(2^-  9)) 
    .long   0xD55556EF, 0x0007FFFF  ; IQ61(arctan(2^- 10)) 
    .long   0xFAAAAAB8, 0x0003FFFF  ; IQ61(arctan(2^- 11)) 
    .long   0xFF555556, 0x0001FFFF  ; IQ61(arctan(2^- 12)) 
    .long   0xFFEAAAAB, 0x0000FFFF  ; IQ61(arctan(2^- 13)) 
    .long   0xFFFD5555, 0x00007FFF  ; IQ61(arctan(2^- 14)) 
    .long   0xFFFFAAAB, 0x00003FFF  ; IQ61(arctan(2^- 15)) 
    .long   0xFFFFF555, 0x00001FFF  ; IQ61(arctan(2^- 16)) 
    .long   0xFFFFFEAB, 0x00000FFF  ; IQ61(arctan(2^- 17)) 
    .long   0xFFFFFFD5, 0x000007FF  ; IQ61(arctan(2^- 18)) 
    .long   0xFFFFFFFB, 0x000003FF  ; IQ61(arctan(2^- 19)) 
    .long   0xFFFFFFFF, 0x000001FF  ; IQ61(arctan(2^- 20)) 
    .long   0x00000000, 0x00000100  ; IQ61(arctan(2^- 21)) 
    .long   0x00000000, 0x00000080  ; IQ61(arctan(2^- 22)) 
    .long   0x00000000, 0x00000040  ; IQ61(arctan(2^- 23)) 
    .long   0x00000000, 0x00000020  ; IQ61(arctan(2^- 24)) 
    .long   0x00000000, 0x00000010  ; IQ61(arctan(2^- 25)) 
    .long   0x00000000, 0x00000008  ; IQ61(arctan(2^- 26)) 
    .long   0x00000000, 0x00000004  ; IQ61(arctan(2^- 27)) 
    .long   0x00000000, 0x00000002  ; IQ61(arctan(2^- 28)) 
    .long   0x00000000, 0x00000001  ; IQ61(arctan(2^- 29)) 
    .long   0x80000000, 0x00000000  ; IQ61(arctan(2^- 30)) 
    .long   0x40000000, 0x00000000  ; IQ61(arctan(2^- 31)) 
    .long   0x20000000, 0x00000000  ; IQ61(arctan(2^- 32)) 
    .long   0x10000000, 0x00000000  ; IQ61(arctan(2^- 33)) 
    .long   0x08000000, 0x00000000  ; IQ61(arctan(2^- 34)) 
    .long   0x04000000, 0x00000000  ; IQ61(arctan(2^- 35)) 
    .long   0x02000000, 0x00000000  ; IQ61(arctan(2^- 36)) 
    .long   0x01000000, 0x00000000  ; IQ61(arctan(2^- 37)) 
    .long   0x00800000, 0x00000000  ; IQ61(arctan(2^- 38)) 
    .long   0x00400000, 0x00000000  ; IQ61(arctan(2^- 39)) 
    .long   0x00200000, 0x00000000  ; IQ61(arctan(2^- 40)) 
    .long   0x00100000, 0x00000000  ; IQ61(arctan(2^- 41)) 
    .long   0x00080000, 0x00000000  ; IQ61(arctan(2^- 42)) 
    .long   0x00040000, 0x00000000  ; IQ61(arctan(2^- 43)) 
    .long   0x00020000, 0x00000000  ; IQ61(arctan(2^- 44)) 
    .long   0x00010000, 0x00000000  ; IQ61(arctan(2^- 45)) 
    .long   0x00008000, 0x00000000  ; IQ61(arctan(2^- 46)) 
    .long   0x00004000, 0x00000000  ; IQ61(arctan(2^- 47)) 
    .long   0x00002000, 0x00000000  ; IQ61(arctan(2^- 48)) 
    .long   0x00001000, 0x00000000  ; IQ61(arctan(2^- 49)) 
    .long   0x00000800, 0x00000000  ; IQ61(arctan(2^- 50)) 
    .long   0x00000400, 0x00000000  ; IQ61(arctan(2^- 51)) 
    .long   0x00000200, 0x00000000  ; IQ61(arctan(2^- 52)) 
    .long   0x00000100, 0x00000000  ; IQ61(arctan(2^- 53)) 
    .long   0x00000080, 0x00000000  ; IQ61(arctan(2^- 54)) 
    .long   0x00000040, 0x00000000  ; IQ61(arctan(2^- 55)) 
    .long   0x00000020, 0x00000000  ; IQ61(arctan(2^- 56)) 
    .long   0x00000010, 0x00000000  ; IQ61(arctan(2^- 57)) 
    .long   0x00000008, 0x00000000  ; IQ61(arctan(2^- 58)) 
    .long   0x00000004, 0x00000000  ; IQ61(arctan(2^- 59)) 
    .long   0x00000002, 0x00000000  ; IQ61(arctan(2^- 60)) 
    .long   0x00000001, 0x00000000  ; IQ61(arctan(2^- 61)) 
    .long   0x00000001, 0x00000000  ; IQ61(arctan(2^- 62)) 
    .long   0x00000000, 0x00000000  ; IQ61(arctan(2^- 63))
_CORDIC_F64_atanTableEnd:

    .sect   "FPU64mathTables"
    .align  2
    .def    _CORDIC_F64_scaleFactor
_CORDIC_F64_scaleFactor:
    .long   0x086BCD00, 0x136E9DB5   ; IQ61(1/sqrt(1 + 2^(-2* 63)))
	.def	_CORDIC_F64_PI_O_2
_CORDIC_F64_PI_O_2:
	.long	0x54442D18, 0x3FF921FB
	.def	_CORDIC_F64_PI
_CORDIC_F64_PI:
	.long	0x54442D18, 0x400921FB 
	.def	_CORDIC_F64_3PI_O_2
_CORDIC_F64_3PI_O_2:
	.long	0x7F3321D2, 0x4012D97C 
	.def	_CORDIC_F64_2PI
_CORDIC_F64_2PI:
	.long	0x54442D18, 0x401921FB 
;; End of File
