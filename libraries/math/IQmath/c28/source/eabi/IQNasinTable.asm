***********************************************************************
* File: IQNasinTable.asm
* Devices: TMS320F2812, TMS320F2811, TMS320F2810
* Author: David M. Alter, Texas Instruments Inc.
* History:
*   04/29/04 - original (D. Alter)
***********************************************************************

;;==========================================================================
;; IQasin Function Table, Size Of Table = 85x16
;;==========================================================================

	.def	_IQasinTable
	.sect	 "IQmathTablesRam"

_IQasinTable:
; for f(x) = c4*x^4 + c3*x^3 + c2*x^2 + c1*x + c0

;point 0 (x=0)
point0:
	.long             0 ; c4 for point 0       =   0.00000000000000 in Q29
	.long      89478485 ; c3 for point 0       =   0.16666666666667 in Q29
	.long             0 ; c2 for point 0       =   0.00000000000000 in Q29
	.long     536870912 ; c1 for point 0       =   1.00000000000000 in Q29
	.long             0 ; c0 for point 0       =   0.00000000000000 in Q29
;point 1 (x=0.03125)
point1:
	.long       6317117 ; c4 for point 1       =   0.01176654801806 in Q29
	.long      89082863 ; c3 for point 1       =   0.16592976253570 in Q29
	.long         12378 ; c2 for point 1       =   0.00002305630012 in Q29
	.long     536870718 ; c1 for point 1       =   0.99999963945303 in Q29
	.long             1 ; c0 for point 1       =   0.00000000225472 in Q29
;point 2 (x=0.06250)
point2:
	.long      12789687 ; c4 for point 2       =   0.02382264819581 in Q29
	.long      87866810 ; c3 for point 2       =   0.16366468695565 in Q29
	.long        101217 ; c2 for point 2       =   0.00018853150967 in Q29
	.long     536867739 ; c1 for point 2       =   0.99999408944239 in Q29
	.long            40 ; c0 for point 2       =   0.00000007405140 in Q29
;point 3 (x=0.09375)
point3:
	.long      19580708 ; c4 for point 3       =   0.03647191042431 in Q29
	.long      85740406 ; c3 for point 3       =   0.15970395152535 in Q29
	.long        354217 ; c2 for point 3       =   0.00065978084316 in Q29
	.long     536854190 ; c1 for point 3       =   0.99996885226392 in Q29
	.long           315 ; c0 for point 3       =   0.00000058698337 in Q29
;point 4 (x=0.1250)
point4:
	.long      26868885 ; c4 for point 4       =   0.05004719802685 in Q29
	.long      82545646 ; c3 for point 4       =   0.15375324754641 in Q29
	.long        882934 ; c2 for point 4       =   0.00164459220320 in Q29
	.long     536815043 ; c1 for point 4       =   0.99989593609382 in Q29
	.long          1409 ; c0 for point 4       =   0.00000262453734 in Q29
;point 5 (x=0.15625)
point5:
	.long      34858083 ; c4 for point 5       =   0.06492823848730 in Q29
	.long      78043250 ; c3 for point 5       =   0.14536688064656 in Q29
	.long       1838350 ; c2 for point 5       =   0.00342419379134 in Q29
	.long     536724572 ; c1 for point 5       =   0.99972742028566 in Q29
	.long          4634 ; c0 for point 5       =   0.00000863223157 in Q29
;point 6 (x=0.18750)
point6:
	.long      43788925 ; c4 for point 6       =   0.08156322849045 in Q29
	.long      71892080 ; c3 for point 6       =   0.13390943393951 in Q29
	.long       3431456 ; c2 for point 6       =   0.00639158410284 in Q29
	.long     536540695 ; c1 for point 6       =   0.99938492317316 in Q29
	.long         12614 ; c0 for point 6       =   0.00002349611964 in Q29
;point 7 (x=0.21875)
point7:
	.long      53953665 ; c4 for point 7       =   0.10049653164769 in Q29
	.long      63618641 ; c3 for point 7       =   0.11849895225606 in Q29
	.long       5961683 ; c2 for point 7       =   0.01110450018835 in Q29
	.long     536196110 ; c1 for point 7       =   0.99874308390293 in Q29
	.long         30246 ; c0 for point 7       =   0.00005633823023 in Q29
;point 8 (x=0.25000)
point8:
	.long      65715899 ; c4 for point 8       =   0.12240539958384 in Q29
	.long      52572719 ; c3 for point 8       =   0.09792431966707 in Q29
	.long       9857385 ; c2 for point 8       =   0.01836080993758 in Q29
	.long     535584573 ; c1 for point 8       =   0.99760400660829 in Q29
	.long         66298 ; c0 for point 8       =   0.00012348928199 in Q29
;point 9 (x=0.28125)
point9:
	.long      79537402 ; c4 for point 9       =   0.14814995596061 in Q29
	.long      37863112 ; c3 for point 9       =   0.07052554134789 in Q29
	.long      15734668 ; c2 for point 9       =   0.02930810346023 in Q29
	.long     534539695 ; c1 for point 9       =   0.99565777006874 in Q29
	.long        136037 ; c0 for point 9       =   0.00025338900082 in Q29
;point 10 (x=0.31250)
point10:
	.long      96015466 ; c4 for point 10      =   0.17884274290911 in Q29
	.long      18264067 ; c3 for point 10      =   0.03401947530154 in Q29
	.long      24484384 ; c2 for point 10      =   0.04560571931992 in Q29
	.long     532802024 ; c1 for point 10      =   0.99242110469066 in Q29
	.long        265566 ; c0 for point 10      =   0.00049465588355 in Q29
;point 11 (x=0.34375)
point11:
	.long     115935880 ; c4 for point 11      =   0.21594740492715 in Q29
	.long      -7922211 ; c3 for point 11      =  -0.01475626778059 in Q29
	.long      37402735 ; c2 for point 11      =   0.06966802370550 in Q29
	.long     529967480 ; c1 for point 11      =   0.98714135522368 in Q29
	.long        498974 ; c0 for point 11      =   0.00092941064669 in Q29
;point 12 (x=0.37500)
point12:
	.long     140349533 ; c4 for point 12      =   0.26142137657237 in Q29
	.long     -43070227 ; c3 for point 12      =  -0.08022454942433 in Q29
	.long      56390437 ; c2 for point 12      =   0.10503537451569 in Q29
	.long     525405717 ; c1 for point 12      =   0.97864440922208 in Q29
	.long        910213 ; c0 for point 12      =   0.00169540313020 in Q29
;point 13 (x=0.40625)
point13:
	.long     170685304 ; c4 for point 13      =   0.31792615376935 in Q29
	.long     -90540603 ; c3 for point 13      =  -0.16864501479554 in Q29
	.long      84261400 ; c2 for point 13      =   0.15694908812191 in Q29
	.long     518129119 ; c1 for point 13      =   0.96509068936447 in Q29
	.long       1623008 ; c0 for point 13      =   0.00302308763644 in Q29
;point 14 (x=0.43750)
point14:
	.long     208919771 ; c4 for point 14      =   0.38914339775461 in Q29
	.long    -155156187 ; c3 for point 14      =  -0.28900091994247 in Q29
	.long     125229731 ; c2 for point 14      =   0.23325855153370 in Q29
	.long     506579341 ; c1 for point 14      =   0.94357755204347 in Q29
	.long       2844600 ; c0 for point 14      =   0.00529848115859 in Q29
;point 15 (x=0.46875)
point15:
	.long     257837857 ; c4 for point 15      =   0.48026043442295 in Q29
	.long    -243949525 ; c3 for point 15      =  -0.45439139960266 in Q29
	.long     185693290 ; c2 for point 15      =   0.34588070642185 in Q29
	.long     488273269 ; c1 for point 15      =   0.90947983687988 in Q29
	.long       4923808 ; c0 for point 15      =   0.00917130774387 in Q29
;point 16 (x=0.50000)
point16:
	.long     321442661 ; c4 for point 16      =   0.59873361249295 in Q29
	.long    -367363041 ; c3 for point 16      =  -0.68426698570622 in Q29
	.long     275522281 ; c2 for point 16      =   0.51320023927967 in Q29
	.long     459203801 ; c1 for point 16      =   0.85533373213278 in Q29
	.long       8452695 ; c0 for point 16      =   0.01574437214446 in Q29
;end of IQasinTable

	.end

;end file IQNasinTable.asm
