;;#############################################################################
;;! \file   logtable_f32.asm
;;! \brief  Natural Logarithm Lookup Table (32) 
;;! \author Vishal Coelho 
;;! \date   30-Jan-2017
;;! 
;;  Revision History:
;;+----------+---------------+------------------------------------------------+
;;| DATE     | AUTHOR        | CHANGE                                         |
;;+----------+---------------+------------------------------------------------+
;;| 01/16/18 | Ritvik Sadana | Modified symbol names to keep naming           |
;;|          |               | consistent with FPU64 symbols.                 |
;;+----------+---------------+------------------------------------------------+
;;| 02/13/18 | Ritvik Sadana | Modified table values to match with CLA table  |
;;|          |               | as advised by Alex T.                          |
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
    .asg    FPU32LOG2, _FPU32LOG2
    .asg    FPU32INVLOG10, _FPU32INVLOG10
    .asg    FPU32EXPBIAS, _FPU32EXPBIAS
    .asg    FPU32LOG_TABLE_MASK1, _FPU32LOG_TABLE_MASK1
    .asg    FPU32LOG_TABLE_MASK2, _FPU32LOG_TABLE_MASK2
    .asg    FPU32logTable, _FPU32logTable
    .asg    FPU32logTableEnd, _FPU32logTableEnd
    .endif
    .def    _FPU32LOG2
    .def    _FPU32INVLOG10
    .def    _FPU32EXPBIAS
    .def    _FPU32LOG_TABLE_MASK1
    .def    _FPU32LOG_TABLE_MASK2
    .def    _FPU32logTable
    .def    _FPU32logTableEnd

    .sect   "FPUmathTables"

_FPU32LOG2:             .float   0.693147180559 ;
_FPU32INVLOG10:         .float   0.4342944819032;
_FPU32EXPBIAS:          .float   127.0          ;
_FPU32LOG_TABLE_MASK1:  .long    0x3FFFFFFF     ;
_FPU32LOG_TABLE_MASK2:  .long    0x3F800000     ;

_FPU32logTable:
    .float                       0              ;        
    .float                       1              ;        
    .float                      -0.5            ;
    .float                       9.49154e-06    ;        
    .float                       0.999081726    ;        
    .float                      -0.470156107    ;
    .float                       7.09886e-05    ;        
    .float                       0.996539792    ;        
    .float                      -0.442906574    ;
    .float                       0.000224404    ;        
    .float                       0.992653061    ;        
    .float                      -0.417959184    ;
    .float                       0.000499085    ;        
    .float                       0.987654321    ;        
    .float                      -0.395061728    ;
    .float                       0.000916122    ;        
    .float                       0.981738495    ;        
    .float                      -0.373995617    ;
    .float                       0.001490146    ;        
    .float                       0.975069252    ;        
    .float                      -0.354570637    ;
    .float                       0.00223074     ;        
    .float                       0.967784352    ;        
    .float                      -0.336620644    ;
    .float                       0.003143551    ;        
    .float                       0.96           ;        
    .float                      -0.32           ;
    .float                       0.004231167    ;        
    .float                       0.951814396    ;        
    .float                      -0.304580607    ;
    .float                       0.005493806    ;        
    .float                       0.943310658    ;        
    .float                      -0.290249433    ;
    .float                       0.00692987     ;        
    .float                       0.934559221    ;        
    .float                      -0.276906436    ;
    .float                       0.008536376    ;        
    .float                       0.925619835    ;        
    .float                      -0.26446281     ;
    .float                       0.010309303    ;        
    .float                       0.91654321     ;        
    .float                      -0.252839506    ;
    .float                       0.012243868    ;        
    .float                       0.907372401    ;        
    .float                      -0.241965974    ;
    .float                       0.014334741    ;        
    .float                       0.898143957    ;        
    .float                      -0.231779086    ;
    .float                       0.016576219    ;        
    .float                       0.888888889    ;        
    .float                      -0.222222222    ;
    .float                       0.018962363    ;        
    .float                       0.879633486    ;        
    .float                      -0.213244481    ;
    .float                       0.021487103    ;        
    .float                       0.8704         ;        
    .float                      -0.2048         ;
    .float                       0.024144324    ;        
    .float                       0.861207228    ;        
    .float                      -0.196847366    ;
    .float                       0.026927934    ;        
    .float                       0.852071006    ;        
    .float                      -0.189349112    ;
    .float                       0.02983191     ;        
    .float                       0.843004628    ;        
    .float                      -0.182271271    ;
    .float                       0.032850339    ;        
    .float                       0.834019204    ;        
    .float                      -0.17558299     ;
    .float                       0.035977448    ;    
    .float                       0.825123967    ;        
    .float                      -0.169256198    ;
    .float                       0.039207625    ;        
    .float                       0.816326531    ;        
    .float                      -0.163265306    ;
    .float                       0.042535433    ;        
    .float                       0.807633118    ;        
    .float                      -0.15758695     ;
    .float                       0.045955621    ;        
    .float                       0.799048751    ;        
    .float                      -0.152199762    ;
    .float                       0.049463133    ;        
    .float                       0.79057742     ;        
    .float                      -0.147084171    ;
    .float                       0.053053104    ;        
    .float                       0.782222222    ;        
    .float                      -0.142222222    ;
    .float                       0.056720869    ;        
    .float                       0.773985488    ;        
    .float                      -0.13759742     ;
    .float                       0.060461958    ;        
    .float                       0.765868887    ;        
    .float                      -0.133194589    ;
    .float                       0.064272091    ;        
    .float                       0.75787352     ;        
    .float                      -0.128999748    ;
    .float                       0.068147181    ;        
    .float                       0.75           ;        
    .float                      -0.125          ; 
_FPU32logTableEnd:

;; End of File
