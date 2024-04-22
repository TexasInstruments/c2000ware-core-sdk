;;##########################################################################
;;
;;Title:    Table 2 For IQmath Functions
;;
;;Version:  1.0
;;
;;Contents: IQexp Function Table,                  Size Of Table =  140x16
;;
;;##########################################################################

;;==========================================================================
;; IQexp Function Table, Size Of Table = 140x16
;;==========================================================================

	.def	_IQexpTable
	.def	_IQexpTableMinMax
	.def	_IQexpTableMinMaxEnd
	.def	_IQexpTableCoeff
	.def	_IQexpTableCoeffEnd

	.sect	 "IQmathTablesRam"

_IQexpTable:
_IQexpTableMinMax:
	.long	          42	; Q 1 Max Input Value =      20.794415416333
	.long	          -1	; Q 1 Min Input Value =      -0.693147180560
	.long	          80	; Q 2 Max Input Value =      20.101268235773
	.long	          -6	; Q 2 Min Input Value =      -1.386294361120
	.long	         155	; Q 3 Max Input Value =      19.408121055213
	.long	         -17	; Q 3 Min Input Value =      -2.079441541680
	.long	         299	; Q 4 Max Input Value =      18.714973874653
	.long	         -44	; Q 4 Min Input Value =      -2.772588722240
	.long	         577	; Q 5 Max Input Value =      18.021826694093
	.long	        -111	; Q 5 Min Input Value =      -3.465735902800
	.long	        1109	; Q 6 Max Input Value =      17.328679513533
	.long	        -266	; Q 6 Min Input Value =      -4.158883083360
	.long	        2129	; Q 7 Max Input Value =      16.635532332973
	.long	        -621	; Q 7 Min Input Value =      -4.852030263920
	.long	        4081	; Q 8 Max Input Value =      15.942385152413
	.long	       -1420	; Q 8 Min Input Value =      -5.545177444480
	.long	        7808	; Q 9 Max Input Value =      15.249237971853
	.long	       -3194	; Q 9 Min Input Value =      -6.238324625040
	.long	       14905	; Q10 Max Input Value =      14.556090791293
	.long	       -7098	; Q10 Min Input Value =      -6.931471805599
	.long	       28391	; Q11 Max Input Value =      13.862943610733
	.long	      -15615	; Q11 Min Input Value =      -7.624618986159
	.long	       53943	; Q12 Max Input Value =      13.169796430173
	.long	      -34070	; Q12 Min Input Value =      -8.317766166719
	.long	      102209	; Q13 Max Input Value =      12.476649249613
	.long	      -73817	; Q13 Min Input Value =      -9.010913347279
	.long	      193061	; Q14 Max Input Value =      11.783502069053
	.long	     -158991	; Q14 Min Input Value =      -9.704060527839
	.long	      363409	; Q15 Max Input Value =      11.090354888493
	.long	     -340696	; Q15 Min Input Value =     -10.397207708399
	.long	      681391	; Q16 Max Input Value =      10.397207707934
	.long	     -726817	; Q16 Min Input Value =     -11.090354888959
	.long	     1271931	; Q17 Max Input Value =       9.704060527374
	.long	    -1544487	; Q17 Min Input Value =     -11.783502069519
	.long	     2362157	; Q18 Max Input Value =       9.010913346814
	.long	    -3270679	; Q18 Min Input Value =     -12.476649250079
	.long	     4360905	; Q19 Max Input Value =       8.317766166254
	.long	    -6904766	; Q19 Min Input Value =     -13.169796430639
	.long	     7994992	; Q20 Max Input Value =       7.624618985694
	.long	   -14536350	; Q20 Min Input Value =     -13.862943611199
	.long	    14536350	; Q21 Max Input Value =       6.931471805134
	.long	   -30526335	; Q21 Min Input Value =     -14.556090791759
	.long	    26165430	; Q22 Max Input Value =       6.238324624574
	.long	   -63959940	; Q22 Min Input Value =     -15.249237972319
	.long	    46516320	; Q23 Max Input Value =       5.545177444014
	.long	  -133734420	; Q23 Min Input Value =     -15.942385152879
	.long	    81403560	; Q24 Max Input Value =       4.852030263454
	.long	  -279097919	; Q24 Min Input Value =     -16.635532333439
	.long	   139548960	; Q25 Max Input Value =       4.158883082894
	.long	  -581453998	; Q25 Min Input Value =     -17.328679513999
	.long	   232581599	; Q26 Max Input Value =       3.465735902334
	.long	 -1209424317	; Q26 Min Input Value =     -18.021826694559
	.long	   372130559	; Q27 Max Input Value =       2.772588721774
	.long	 -2147483648	; Q27 Min Input Value =     -16.000000000000
	.long	   558195838	; Q28 Max Input Value =       2.079441541214
	.long	 -2147483648	; Q28 Min Input Value =      -8.000000000000
	.long	   744261118	; Q29 Max Input Value =       1.386294360654
	.long	 -2147483648	; Q29 Min Input Value =      -4.000000000000
	.long	   744261117	; Q30 Max Input Value =       0.693147180094
	.long	 -2147483648	; Q30 Min Input Value =      -2.000000000000
_IQexpTableMinMaxEnd:

_IQexpTableCoeff:
	.long	  0x0BA2E8BA	; 1/11 in Q31
	.long	  0x0CCCCCCD	; 1/10 in Q31
	.long	  0x0E38E38E	; 1/9  in Q31
	.long	  0x10000000	; 1/8  in Q31
	.long	  0x12492492	; 1/7  in Q31
	.long	  0x15555555	; 1/6  in Q31
	.long	  0x1999999A	; 1/5  in Q31
	.long	  0x20000000	; 1/4  in Q31
	.long	  0x2AAAAAAB	; 1/3  in Q31
	.long	  0x40000000	; 1/2  in Q31
_IQexpTableCoeffEnd:
_IQexpTableEnd:


;;
;; End Of File.
;;
