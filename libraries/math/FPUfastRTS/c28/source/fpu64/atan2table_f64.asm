;;#############################################################################
;;! \file atan2table_f64.asm
;;! \brief  Arctangent Lookup Table (256) 
;;! \author Vishal Coelho 
;;! \date   03-Mar-2016
;;! 
;;  Revision History:
;;+----------+---------------+------------------------------------------------+
;;| DATE     | AUTHOR        | CHANGE                                         |
;;+----------+---------------+------------------------------------------------+
;;| 01/16/18 | Ritvik Sadana | Changed symbol names to avoid conflicts with   |
;;|          |               | FPU32 symbols.                                 |
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
    .asg    FPU64atan2HalfPITable, _FPU64atan2HalfPITable
    .asg    FPU64atan2Table, _FPU64atan2Table
    .asg    FPU64atan2TableEnd, _FPU64atan2TableEnd
    .endif
    .def    _FPU64atan2HalfPITable
    .def    _FPU64atan2Table
    .def    _FPU64atan2TableEnd

    .sect   "FPU64mathTables"

_FPU64atan2HalfPITable:
    .xldouble    2.0000000000000
    .xldouble    1.5707963267949
_FPU64atan2Table:
	.xldouble	 0.0000000000000,  1.0000406796754, -0.0078110697504 ;   0 -> a0 a1 a2 
	.xldouble	-0.0000038070221,  1.0005280677716, -0.0234103454930 ;   1 -> a0 a1 a2 
	.xldouble	-0.0000189683103,  1.0014985681064, -0.0389411970749 ;   2 -> a0 a1 a2 
	.xldouble	-0.0000528319270,  1.0029436809648, -0.0543585631597 ;   3 -> a0 a1 a2 
	.xldouble	-0.0001124179960,  1.0048507857875, -0.0696182066495 ;   4 -> a0 a1 a2 
	.xldouble	-0.0002042958852,  1.0072032932429, -0.0846770287235 ;   5 -> a0 a1 a2 
	.xldouble	-0.0003344694932,  1.0099808435012, -0.0994933676284 ;   6 -> a0 a1 a2 
	.xldouble	-0.0005082726057,  1.0131595470233, -0.1140272784299 ;   7 -> a0 a1 a2 
	.xldouble	-0.0007302760352,  1.0167122634486, -0.1282407903432 ;   8 -> a0 a1 a2 
	.xldouble	-0.0010042079796,  1.0206089135568, -0.1420981387153 ;   9 -> a0 a1 a2 
	.xldouble	-0.0013328887174,  1.0248168188011, -0.1555659692585 ;  10 -> a0 a1 a2 
	.xldouble	-0.0017181804313,  1.0293010625688, -0.1686135126670 ;  11 -> a0 a1 a2 
	.xldouble	-0.0021609526118,  1.0340248671352, -0.1812127283288 ;  12 -> a0 a1 a2 
	.xldouble	-0.0026610631593,  1.0389499802219, -0.1933384164099 ;  13 -> a0 a1 a2 
	.xldouble	-0.0032173549768,  1.0440370651602, -0.2049682981460 ;  14 -> a0 a1 a2 
	.xldouble	-0.0038276675461,  1.0492460888683, -0.2160830647060 ;  15 -> a0 a1 a2 
	.xldouble	-0.0044888627021,  1.0545367021923, -0.2266663955068 ;  16 -> a0 a1 a2 
	.xldouble	-0.0051968635789,  1.0598686075727, -0.2367049472787 ;  17 -> a0 a1 a2 
	.xldouble	-0.0059467055004,  1.0652019095265, -0.2461883156129 ;  18 -> a0 a1 a2 
	.xldouble	-0.0067325974217,  1.0704974439939, -0.2551089710223 ;  19 -> a0 a1 a2 
	.xldouble	-0.0075479924132,  1.0757170832221, -0.2634621718398 ;  20 -> a0 a1 a2 
	.xldouble	-0.0083856655986,  1.0808240134986, -0.2712458564756 ;  21 -> a0 a1 a2 
	.xldouble	-0.0092377979239,  1.0857829836932, -0.2784605176930 ;  22 -> a0 a1 a2 
	.xldouble	-0.0100960641391,  1.0905605232115, -0.2851090616505 ;  23 -> a0 a1 a2 
	.xldouble	-0.0109517234066,  1.0951251285570, -0.2911966544475 ;  24 -> a0 a1 a2 
	.xldouble	-0.0117957110286,  1.0994474183038, -0.2967305589200 ;  25 -> a0 a1 a2 
	.xldouble	-0.0126187298731,  1.1035002567840, -0.3017199643105 ;  26 -> a0 a1 a2 
	.xldouble	-0.0134113401986,  1.1072588472740, -0.3061758113249 ;  27 -> a0 a1 a2 
	.xldouble	-0.0141640467111,  1.1107007958875, -0.3101106149475 ;  28 -> a0 a1 a2 
	.xldouble	-0.0148673818311,  1.1138061477170, -0.3135382871760 ;  29 -> a0 a1 a2 
	.xldouble	-0.0155119842982,  1.1165573970591, -0.3164739616554 ;  30 -> a0 a1 a2 
	.xldouble	-0.0160886723953,  1.1189394737663, -0.3189338219481 ;  31 -> a0 a1 a2 
	.xldouble	-0.0165885112292,  1.1209397079557, -0.3209349349913 ;  32 -> a0 a1 a2 
	.xldouble	-0.0170028736449,  1.1225477753665, -0.3224950910217 ;  33 -> a0 a1 a2 
	.xldouble	-0.0173234944993,  1.1237556257493, -0.3236326510678 ;  34 -> a0 a1 a2 
	.xldouble	-0.0175425181404,  1.1245573966328, -0.3243664028596 ;  35 -> a0 a1 a2 
	.xldouble	-0.0176525390650,  1.1249493148104, -0.3247154258333 ;  36 -> a0 a1 a2 
	.xldouble	-0.0176466358231,  1.1249295877727, -0.3246989656827 ;  37 -> a0 a1 a2 
	.xldouble	-0.0175183983443,  1.1244982872665, -0.3243363187867 ;  38 -> a0 a1 a2 
	.xldouble	-0.0172619489202,  1.1236572269554, -0.3236467266133 ;  39 -> a0 a1 a2 
	.xldouble	-0.0168719571636,  1.1224098360981, -0.3226492801386 ;  40 -> a0 a1 a2 
	.xldouble	-0.0163436492943,  1.1207610309185, -0.3213628341191 ;  41 -> a0 a1 a2 
	.xldouble	-0.0156728121663,  1.1187170852579, -0.3198059310243 ;  42 -> a0 a1 a2 
	.xldouble	-0.0148557924513,  1.1162855018516, -0.3179967342794 ;  43 -> a0 a1 a2 
	.xldouble	-0.0138894914410,  1.1134748854835, -0.3159529704599 ;  44 -> a0 a1 a2 
	.xldouble	-0.0127713559110,  1.1102948190320, -0.3136918799664 ;  45 -> a0 a1 a2 
	.xldouble	-0.0114993655128,  1.1067557433290, -0.3112301757137 ;  46 -> a0 a1 a2 
	.xldouble	-0.0100720171306,  1.1028688415306, -0.3085840092872 ;  47 -> a0 a1 a2 
	.xldouble	-0.0084883066548,  1.0986459286453, -0.3057689440639 ;  48 -> a0 a1 a2 
	.xldouble	-0.0067477085786,  1.0940993466476, -0.3027999347241 ;  49 -> a0 a1 a2 
	.xldouble	-0.0048501538149,  1.0892418655233, -0.2996913126099 ;  50 -> a0 a1 a2 
	.xldouble	-0.0027960061186,  1.0840865905167, -0.2964567764093 ;  51 -> a0 a1 a2 
	.xldouble	-0.0005860374406,  1.0786468756663, -0.2931093876086 ;  52 -> a0 a1 a2 
	.xldouble	 0.0017785974517,  1.0729362437272, -0.2896615702293 ;  53 -> a0 a1 a2 
	.xldouble	 0.0042963868040,  1.0669683124404, -0.2861251143513 ;  54 -> a0 a1 a2 
	.xldouble	 0.0069654878940,  1.0607567270642, -0.2825111829598 ;  55 -> a0 a1 a2 
	.xldouble	 0.0097837530165,  1.0543150990086, -0.2788303216685 ;  56 -> a0 a1 a2 
	.xldouble	 0.0127487552067,  1.0476569504397, -0.2750924709426 ;  57 -> a0 a1 a2 
	.xldouble	 0.0158578135459,  1.0407956645818, -0.2713069804113 ;  58 -> a0 a1 a2 
	.xldouble	 0.0191080178933,  1.0337444414765, -0.2674826249277 ;  59 -> a0 a1 a2 
	.xldouble	 0.0224962528869,  1.0265162589889, -0.2636276220892 ;  60 -> a0 a1 a2 
	.xldouble	 0.0260192211618,  1.0191238386511, -0.2597496508597 ;  61 -> a0 a1 a2 
	.xldouble	 0.0296734656363,  1.0115796161864, -0.2558558711062 ;  62 -> a0 a1 a2 
	.xldouble	 0.0334553908381,  1.0038957163225, -0.2519529437632 ;  63 -> a0 a1 a2 
	.xldouble	 0.0373612832121,  0.9960839316110, -0.2480470514256 ;  64 -> a0 a1 a2 
_FPU64atan2TableEnd:

;; End of File
