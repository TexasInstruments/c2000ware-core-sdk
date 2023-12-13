;;#############################################################################
;; FILE: CLAexpTable.asm
;; 
;; DESCRIPTION: Exponential Tables
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
;;#############################################################################
    
	.include "CLAeabi.asm"
	
    .def    _CLAINV1
    .def    _CLAINV2
    .def    _CLAINV3
    .def    _CLAINV4
    .def    _CLAINV5
    .def    _CLAINV6
    .def    _CLAINV7
    .def    _CLALOG10
    .def    _CLAExpTable
    .def    _CLAExpTableEnd

   .sect    "CLA1mathTables"
_CLAINV1    .float   1  
_CLAINV2    .float   0.5                   ; 1/2
_CLAINV3    .float   0.333333333333333333  ; 1/3
_CLAINV4    .float   0.25                  ; 1/4
_CLAINV5    .float   0.20                  ; 1/5
_CLAINV6    .float   0.166666666666666666  ; 1/6
_CLAINV7    .float   0.142857142857142857  ; 1/7

_CLALOG10   .float   2.302585092           ; LOG10(e)

_CLAExpTable:
      .float       1.0                     ; exp(0)
      .float       2.7182818285e+0         ; exp(1)
      .float       7.3890560989e+0         ; exp(2)
      .float       2.0085536923e+1         ; exp(3)
      .float       5.4598150033e+1         ; exp(4)
      .float       1.484131591e+2          ; exp(5)
      .float       4.0342879349e+2         ; exp(6)
      .float       1.0966331584e+3         ; exp(7)
      .float       2.980957987e+3          ; exp(8)
      .float       8.1030839276e+3         ; exp(9)
      .float       2.2026465795e+4         ; exp(10)
      .float       5.9874141715e+4         ; exp(11)
      .float       1.6275479142e+5         ; exp(12)
      .float       4.4241339201e+5         ; exp(13)
      .float       1.2026042842e+6         ; exp(14)
      .float       3.2690173725e+6         ; exp(15)
      .float       8.8861105205e+6         ; exp(16)
      .float       2.4154952754e+7         ; exp(17)
      .float       6.5659969137e+7         ; exp(18)
      .float       1.7848230096e+8         ; exp(19)
      .float       4.8516519541e+8         ; exp(20)
      .float       1.3188157345e+9         ; exp(21)
      .float       3.5849128461e+9         ; exp(22)
      .float       9.7448034462e+9         ; exp(23)
      .float       2.648912213e+10         ; exp(24)
      .float       7.2004899337e+10        ; exp(25)
      .float       1.9572960943e+11        ; exp(26)
      .float       5.320482406e+11         ; exp(27)
      .float       1.4462570643e+12        ; exp(28)
      .float       3.9313342971e+12        ; exp(29)
      .float       1.0686474582e+13        ; exp(30)
      .float       2.9048849665e+13        ; exp(31)
      .float       7.8962960183e+13        ; exp(32)
      .float       2.1464357979e+14        ; exp(33)
      .float       5.8346174253e+14        ; exp(34)
      .float       1.5860134523e+15        ; exp(35)
      .float       4.3112315471e+15        ; exp(36)
      .float       1.1719142373e+16        ; exp(37)
      .float       3.1855931757e+16        ; exp(38)
      .float       8.6593400424e+16        ; exp(39)
      .float       2.3538526684e+17        ; exp(40)
      .float       6.3984349353e+17        ; exp(41)
      .float       1.7392749415e+18        ; exp(42)
      .float       4.7278394682e+18        ; exp(43)
      .float       1.2851600114e+19        ; exp(44)
      .float       3.4934271057e+19        ; exp(45)
      .float       9.4961194206e+19        ; exp(46)
      .float       2.5813128862e+20        ; exp(47)
      .float       7.0167359121e+20        ; exp(48)
      .float       1.9073465725e+21        ; exp(49)
      .float       5.1847055286e+21        ; exp(50)
      .float       1.4093490824e+22        ; exp(51)
      .float       3.8310080007e+22        ; exp(52)
      .float       1.0413759433e+23        ; exp(53)
      .float       2.8307533033e+23        ; exp(54)
      .float       7.6947852651e+23        ; exp(55)
      .float       2.091659496e+24         ; exp(56)
      .float       5.6857199993e+24        ; exp(57)
      .float       1.5455389356e+25        ; exp(58)
      .float       4.2012104038e+25        ; exp(59)
      .float       1.1420073898e+26        ; exp(60)
      .float       3.1042979357e+26        ; exp(61)
      .float       8.4383566687e+26        ; exp(62)
      .float       2.2937831595e+27        ; exp(63)
      .float       6.2351490808e+27        ; exp(64)
      .float       1.6948892444e+28        ; exp(65)
      .float       4.6071866343e+28        ; exp(66)
      .float       1.2523631708e+29        ; exp(67)
      .float       3.4042760499e+29        ; exp(68)
      .float       9.2537817256e+29        ; exp(69)
      .float       2.5154386709e+30        ; exp(70)
      .float       6.8376712298e+30        ; exp(71)
      .float       1.8586717453e+31        ; exp(72)
      .float       5.0523936303e+31        ; exp(73)
      .float       1.3733829795e+32        ; exp(74)
      .float       3.7332419968e+32        ; exp(75)
      .float       1.0148003881e+33        ; exp(76)
      .float       2.7585134545e+33        ; exp(77)
      .float       7.498416997e+33         ; exp(78)
      .float       2.0382810665e+34        ; exp(79)
      .float       5.5406223844e+34        ; exp(80)
      .float       1.5060973146e+35        ; exp(81)
      .float       4.0939969621e+35        ; exp(82)
      .float       1.1128637548e+36        ; exp(83)
      .float       3.0250773222e+36        ; exp(84)
      .float       8.2230127146e+36        ; exp(85)
      .float       2.2352466037e+37        ; exp(86)
      .float       6.0760302251e+37        ; exp(87)
      .float       1.651636255e+38         ; exp(88)

_CLAExpTableEnd:

 ;; End of File
