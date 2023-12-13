;;#############################################################################
;;! \file fft_tables.asm 
;;! \brief  Twiddle Factor Table (1024) 
;;! \author Vishal Coelho 
;;! \date   22-Aug-2016
;;! 
;;  Revision History:
;;+----------+---------------+------------------------------------------------+
;;| DATE     | AUTHOR        | CHANGE                                         |
;;+----------+---------------+------------------------------------------------+
;;| 01/16/18 | Ritvik Sadana | Changed symbol names to keep naming consistent |
;;|          |               | with FPU math table symbols.                   |
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
    .asg    FPU64CFFTtwiddleFactors     , _FPU64CFFTtwiddleFactors
    .asg    FPU64CFFTtwiddleFactorsEnd  , _FPU64CFFTtwiddleFactorsEnd
    .asg    FPU64RFFTtwiddleFactors    , _FPU64RFFTtwiddleFactors
    .asg    FPU64RFFTtwiddleFactorsEnd , _FPU64RFFTtwiddleFactorsEnd
    .endif
    
    .def    _FPU64CFFTtwiddleFactors
    .def    _FPU64CFFTtwiddleFactorsEnd
    .def    _FPU64RFFTtwiddleFactors
    .def    _FPU64RFFTtwiddleFactorsEnd

    .sect   "FPU64fftTables"
    .align  2
_FPU64CFFTtwiddleFactors:
    .xldouble    0.0000000000000    ; sin(2 * pi *    0/1024)
    .xldouble    0.0061358846492    ; sin(2 * pi *    1/1024)
    .xldouble    0.0122715382857    ; sin(2 * pi *    2/1024)
    .xldouble    0.0184067299058    ; sin(2 * pi *    3/1024)
    .xldouble    0.0245412285229    ; sin(2 * pi *    4/1024)
    .xldouble    0.0306748031766    ; sin(2 * pi *    5/1024)
    .xldouble    0.0368072229414    ; sin(2 * pi *    6/1024)
    .xldouble    0.0429382569349    ; sin(2 * pi *    7/1024)
    .xldouble    0.0490676743274    ; sin(2 * pi *    8/1024)
    .xldouble    0.0551952443497    ; sin(2 * pi *    9/1024)
    .xldouble    0.0613207363022    ; sin(2 * pi *   10/1024)
    .xldouble    0.0674439195637    ; sin(2 * pi *   11/1024)
    .xldouble    0.0735645635997    ; sin(2 * pi *   12/1024)
    .xldouble    0.0796824379714    ; sin(2 * pi *   13/1024)
    .xldouble    0.0857973123444    ; sin(2 * pi *   14/1024)
    .xldouble    0.0919089564971    ; sin(2 * pi *   15/1024)
    .xldouble    0.0980171403296    ; sin(2 * pi *   16/1024)
    .xldouble    0.1041216338721    ; sin(2 * pi *   17/1024)
    .xldouble    0.1102222072939    ; sin(2 * pi *   18/1024)
    .xldouble    0.1163186309119    ; sin(2 * pi *   19/1024)
    .xldouble    0.1224106751992    ; sin(2 * pi *   20/1024)
    .xldouble    0.1284981107938    ; sin(2 * pi *   21/1024)
    .xldouble    0.1345807085071    ; sin(2 * pi *   22/1024)
    .xldouble    0.1406582393328    ; sin(2 * pi *   23/1024)
    .xldouble    0.1467304744554    ; sin(2 * pi *   24/1024)
    .xldouble    0.1527971852584    ; sin(2 * pi *   25/1024)
    .xldouble    0.1588581433339    ; sin(2 * pi *   26/1024)
    .xldouble    0.1649131204900    ; sin(2 * pi *   27/1024)
    .xldouble    0.1709618887603    ; sin(2 * pi *   28/1024)
    .xldouble    0.1770042204121    ; sin(2 * pi *   29/1024)
    .xldouble    0.1830398879551    ; sin(2 * pi *   30/1024)
    .xldouble    0.1890686641498    ; sin(2 * pi *   31/1024)
    .xldouble    0.1950903220161    ; sin(2 * pi *   32/1024)
    .xldouble    0.2011046348421    ; sin(2 * pi *   33/1024)
    .xldouble    0.2071113761922    ; sin(2 * pi *   34/1024)
    .xldouble    0.2131103199161    ; sin(2 * pi *   35/1024)
    .xldouble    0.2191012401569    ; sin(2 * pi *   36/1024)
    .xldouble    0.2250839113598    ; sin(2 * pi *   37/1024)
    .xldouble    0.2310581082807    ; sin(2 * pi *   38/1024)
    .xldouble    0.2370236059944    ; sin(2 * pi *   39/1024)
    .xldouble    0.2429801799033    ; sin(2 * pi *   40/1024)
    .xldouble    0.2489276057457    ; sin(2 * pi *   41/1024)
    .xldouble    0.2548656596045    ; sin(2 * pi *   42/1024)
    .xldouble    0.2607941179153    ; sin(2 * pi *   43/1024)
    .xldouble    0.2667127574749    ; sin(2 * pi *   44/1024)
    .xldouble    0.2726213554499    ; sin(2 * pi *   45/1024)
    .xldouble    0.2785196893851    ; sin(2 * pi *   46/1024)
    .xldouble    0.2844075372113    ; sin(2 * pi *   47/1024)
    .xldouble    0.2902846772545    ; sin(2 * pi *   48/1024)
    .xldouble    0.2961508882436    ; sin(2 * pi *   49/1024)
    .xldouble    0.3020059493192    ; sin(2 * pi *   50/1024)
    .xldouble    0.3078496400415    ; sin(2 * pi *   51/1024)
    .xldouble    0.3136817403989    ; sin(2 * pi *   52/1024)
    .xldouble    0.3195020308160    ; sin(2 * pi *   53/1024)
    .xldouble    0.3253102921623    ; sin(2 * pi *   54/1024)
    .xldouble    0.3311063057599    ; sin(2 * pi *   55/1024)
    .xldouble    0.3368898533922    ; sin(2 * pi *   56/1024)
    .xldouble    0.3426607173120    ; sin(2 * pi *   57/1024)
    .xldouble    0.3484186802494    ; sin(2 * pi *   58/1024)
    .xldouble    0.3541635254205    ; sin(2 * pi *   59/1024)
    .xldouble    0.3598950365350    ; sin(2 * pi *   60/1024)
    .xldouble    0.3656129978048    ; sin(2 * pi *   61/1024)
    .xldouble    0.3713171939518    ; sin(2 * pi *   62/1024)
    .xldouble    0.3770074102164    ; sin(2 * pi *   63/1024)
    .xldouble    0.3826834323651    ; sin(2 * pi *   64/1024)
    .xldouble    0.3883450466988    ; sin(2 * pi *   65/1024)
    .xldouble    0.3939920400610    ; sin(2 * pi *   66/1024)
    .xldouble    0.3996241998456    ; sin(2 * pi *   67/1024)
    .xldouble    0.4052413140050    ; sin(2 * pi *   68/1024)
    .xldouble    0.4108431710579    ; sin(2 * pi *   69/1024)
    .xldouble    0.4164295600976    ; sin(2 * pi *   70/1024)
    .xldouble    0.4220002707998    ; sin(2 * pi *   71/1024)
    .xldouble    0.4275550934303    ; sin(2 * pi *   72/1024)
    .xldouble    0.4330938188532    ; sin(2 * pi *   73/1024)
    .xldouble    0.4386162385385    ; sin(2 * pi *   74/1024)
    .xldouble    0.4441221445704    ; sin(2 * pi *   75/1024)
    .xldouble    0.4496113296546    ; sin(2 * pi *   76/1024)
    .xldouble    0.4550835871263    ; sin(2 * pi *   77/1024)
    .xldouble    0.4605387109582    ; sin(2 * pi *   78/1024)
    .xldouble    0.4659764957680    ; sin(2 * pi *   79/1024)
    .xldouble    0.4713967368260    ; sin(2 * pi *   80/1024)
    .xldouble    0.4767992300633    ; sin(2 * pi *   81/1024)
    .xldouble    0.4821837720791    ; sin(2 * pi *   82/1024)
    .xldouble    0.4875501601484    ; sin(2 * pi *   83/1024)
    .xldouble    0.4928981922298    ; sin(2 * pi *   84/1024)
    .xldouble    0.4982276669728    ; sin(2 * pi *   85/1024)
    .xldouble    0.5035383837257    ; sin(2 * pi *   86/1024)
    .xldouble    0.5088301425431    ; sin(2 * pi *   87/1024)
    .xldouble    0.5141027441932    ; sin(2 * pi *   88/1024)
    .xldouble    0.5193559901656    ; sin(2 * pi *   89/1024)
    .xldouble    0.5245896826785    ; sin(2 * pi *   90/1024)
    .xldouble    0.5298036246863    ; sin(2 * pi *   91/1024)
    .xldouble    0.5349976198871    ; sin(2 * pi *   92/1024)
    .xldouble    0.5401714727299    ; sin(2 * pi *   93/1024)
    .xldouble    0.5453249884220    ; sin(2 * pi *   94/1024)
    .xldouble    0.5504579729366    ; sin(2 * pi *   95/1024)
    .xldouble    0.5555702330196    ; sin(2 * pi *   96/1024)
    .xldouble    0.5606615761973    ; sin(2 * pi *   97/1024)
    .xldouble    0.5657318107836    ; sin(2 * pi *   98/1024)
    .xldouble    0.5707807458870    ; sin(2 * pi *   99/1024)
    .xldouble    0.5758081914178    ; sin(2 * pi *  100/1024)
    .xldouble    0.5808139580958    ; sin(2 * pi *  101/1024)
    .xldouble    0.5857978574564    ; sin(2 * pi *  102/1024)
    .xldouble    0.5907597018589    ; sin(2 * pi *  103/1024)
    .xldouble    0.5956993044924    ; sin(2 * pi *  104/1024)
    .xldouble    0.6006164793839    ; sin(2 * pi *  105/1024)
    .xldouble    0.6055110414043    ; sin(2 * pi *  106/1024)
    .xldouble    0.6103828062763    ; sin(2 * pi *  107/1024)
    .xldouble    0.6152315905806    ; sin(2 * pi *  108/1024)
    .xldouble    0.6200572117633    ; sin(2 * pi *  109/1024)
    .xldouble    0.6248594881424    ; sin(2 * pi *  110/1024)
    .xldouble    0.6296382389149    ; sin(2 * pi *  111/1024)
    .xldouble    0.6343932841636    ; sin(2 * pi *  112/1024)
    .xldouble    0.6391244448638    ; sin(2 * pi *  113/1024)
    .xldouble    0.6438315428898    ; sin(2 * pi *  114/1024)
    .xldouble    0.6485144010221    ; sin(2 * pi *  115/1024)
    .xldouble    0.6531728429538    ; sin(2 * pi *  116/1024)
    .xldouble    0.6578066932971    ; sin(2 * pi *  117/1024)
    .xldouble    0.6624157775902    ; sin(2 * pi *  118/1024)
    .xldouble    0.6669999223036    ; sin(2 * pi *  119/1024)
    .xldouble    0.6715589548470    ; sin(2 * pi *  120/1024)
    .xldouble    0.6760927035753    ; sin(2 * pi *  121/1024)
    .xldouble    0.6806009977955    ; sin(2 * pi *  122/1024)
    .xldouble    0.6850836677727    ; sin(2 * pi *  123/1024)
    .xldouble    0.6895405447371    ; sin(2 * pi *  124/1024)
    .xldouble    0.6939714608897    ; sin(2 * pi *  125/1024)
    .xldouble    0.6983762494090    ; sin(2 * pi *  126/1024)
    .xldouble    0.7027547444572    ; sin(2 * pi *  127/1024)
    .xldouble    0.7071067811865    ; sin(2 * pi *  128/1024)
    .xldouble    0.7114321957452    ; sin(2 * pi *  129/1024)
    .xldouble    0.7157308252838    ; sin(2 * pi *  130/1024)
    .xldouble    0.7200025079614    ; sin(2 * pi *  131/1024)
    .xldouble    0.7242470829515    ; sin(2 * pi *  132/1024)
    .xldouble    0.7284643904482    ; sin(2 * pi *  133/1024)
    .xldouble    0.7326542716724    ; sin(2 * pi *  134/1024)
    .xldouble    0.7368165688774    ; sin(2 * pi *  135/1024)
    .xldouble    0.7409511253550    ; sin(2 * pi *  136/1024)
    .xldouble    0.7450577854415    ; sin(2 * pi *  137/1024)
    .xldouble    0.7491363945235    ; sin(2 * pi *  138/1024)
    .xldouble    0.7531867990436    ; sin(2 * pi *  139/1024)
    .xldouble    0.7572088465065    ; sin(2 * pi *  140/1024)
    .xldouble    0.7612023854843    ; sin(2 * pi *  141/1024)
    .xldouble    0.7651672656225    ; sin(2 * pi *  142/1024)
    .xldouble    0.7691033376456    ; sin(2 * pi *  143/1024)
    .xldouble    0.7730104533627    ; sin(2 * pi *  144/1024)
    .xldouble    0.7768884656732    ; sin(2 * pi *  145/1024)
    .xldouble    0.7807372285721    ; sin(2 * pi *  146/1024)
    .xldouble    0.7845565971556    ; sin(2 * pi *  147/1024)
    .xldouble    0.7883464276266    ; sin(2 * pi *  148/1024)
    .xldouble    0.7921065773002    ; sin(2 * pi *  149/1024)
    .xldouble    0.7958369046089    ; sin(2 * pi *  150/1024)
    .xldouble    0.7995372691079    ; sin(2 * pi *  151/1024)
    .xldouble    0.8032075314806    ; sin(2 * pi *  152/1024)
    .xldouble    0.8068475535438    ; sin(2 * pi *  153/1024)
    .xldouble    0.8104571982526    ; sin(2 * pi *  154/1024)
    .xldouble    0.8140363297059    ; sin(2 * pi *  155/1024)
    .xldouble    0.8175848131516    ; sin(2 * pi *  156/1024)
    .xldouble    0.8211025149911    ; sin(2 * pi *  157/1024)
    .xldouble    0.8245893027850    ; sin(2 * pi *  158/1024)
    .xldouble    0.8280450452578    ; sin(2 * pi *  159/1024)
    .xldouble    0.8314696123025    ; sin(2 * pi *  160/1024)
    .xldouble    0.8348628749864    ; sin(2 * pi *  161/1024)
    .xldouble    0.8382247055548    ; sin(2 * pi *  162/1024)
    .xldouble    0.8415549774369    ; sin(2 * pi *  163/1024)
    .xldouble    0.8448535652497    ; sin(2 * pi *  164/1024)
    .xldouble    0.8481203448033    ; sin(2 * pi *  165/1024)
    .xldouble    0.8513551931053    ; sin(2 * pi *  166/1024)
    .xldouble    0.8545579883654    ; sin(2 * pi *  167/1024)
    .xldouble    0.8577286100003    ; sin(2 * pi *  168/1024)
    .xldouble    0.8608669386378    ; sin(2 * pi *  169/1024)
    .xldouble    0.8639728561216    ; sin(2 * pi *  170/1024)
    .xldouble    0.8670462455157    ; sin(2 * pi *  171/1024)
    .xldouble    0.8700869911087    ; sin(2 * pi *  172/1024)
    .xldouble    0.8730949784183    ; sin(2 * pi *  173/1024)
    .xldouble    0.8760700941954    ; sin(2 * pi *  174/1024)
    .xldouble    0.8790122264286    ; sin(2 * pi *  175/1024)
    .xldouble    0.8819212643484    ; sin(2 * pi *  176/1024)
    .xldouble    0.8847970984309    ; sin(2 * pi *  177/1024)
    .xldouble    0.8876396204029    ; sin(2 * pi *  178/1024)
    .xldouble    0.8904487232448    ; sin(2 * pi *  179/1024)
    .xldouble    0.8932243011955    ; sin(2 * pi *  180/1024)
    .xldouble    0.8959662497562    ; sin(2 * pi *  181/1024)
    .xldouble    0.8986744656940    ; sin(2 * pi *  182/1024)
    .xldouble    0.9013488470460    ; sin(2 * pi *  183/1024)
    .xldouble    0.9039892931234    ; sin(2 * pi *  184/1024)
    .xldouble    0.9065957045149    ; sin(2 * pi *  185/1024)
    .xldouble    0.9091679830905    ; sin(2 * pi *  186/1024)
    .xldouble    0.9117060320054    ; sin(2 * pi *  187/1024)
    .xldouble    0.9142097557035    ; sin(2 * pi *  188/1024)
    .xldouble    0.9166790599210    ; sin(2 * pi *  189/1024)
    .xldouble    0.9191138516901    ; sin(2 * pi *  190/1024)
    .xldouble    0.9215140393420    ; sin(2 * pi *  191/1024)
    .xldouble    0.9238795325113    ; sin(2 * pi *  192/1024)
    .xldouble    0.9262102421383    ; sin(2 * pi *  193/1024)
    .xldouble    0.9285060804732    ; sin(2 * pi *  194/1024)
    .xldouble    0.9307669610790    ; sin(2 * pi *  195/1024)
    .xldouble    0.9329927988347    ; sin(2 * pi *  196/1024)
    .xldouble    0.9351835099389    ; sin(2 * pi *  197/1024)
    .xldouble    0.9373390119126    ; sin(2 * pi *  198/1024)
    .xldouble    0.9394592236022    ; sin(2 * pi *  199/1024)
    .xldouble    0.9415440651830    ; sin(2 * pi *  200/1024)
    .xldouble    0.9435934581620    ; sin(2 * pi *  201/1024)
    .xldouble    0.9456073253805    ; sin(2 * pi *  202/1024)
    .xldouble    0.9475855910177    ; sin(2 * pi *  203/1024)
    .xldouble    0.9495281805930    ; sin(2 * pi *  204/1024)
    .xldouble    0.9514350209690    ; sin(2 * pi *  205/1024)
    .xldouble    0.9533060403542    ; sin(2 * pi *  206/1024)
    .xldouble    0.9551411683058    ; sin(2 * pi *  207/1024)
    .xldouble    0.9569403357322    ; sin(2 * pi *  208/1024)
    .xldouble    0.9587034748959    ; sin(2 * pi *  209/1024)
    .xldouble    0.9604305194156    ; sin(2 * pi *  210/1024)
    .xldouble    0.9621214042690    ; sin(2 * pi *  211/1024)
    .xldouble    0.9637760657954    ; sin(2 * pi *  212/1024)
    .xldouble    0.9653944416977    ; sin(2 * pi *  213/1024)
    .xldouble    0.9669764710449    ; sin(2 * pi *  214/1024)
    .xldouble    0.9685220942744    ; sin(2 * pi *  215/1024)
    .xldouble    0.9700312531945    ; sin(2 * pi *  216/1024)
    .xldouble    0.9715038909863    ; sin(2 * pi *  217/1024)
    .xldouble    0.9729399522056    ; sin(2 * pi *  218/1024)
    .xldouble    0.9743393827856    ; sin(2 * pi *  219/1024)
    .xldouble    0.9757021300385    ; sin(2 * pi *  220/1024)
    .xldouble    0.9770281426578    ; sin(2 * pi *  221/1024)
    .xldouble    0.9783173707196    ; sin(2 * pi *  222/1024)
    .xldouble    0.9795697656854    ; sin(2 * pi *  223/1024)
    .xldouble    0.9807852804032    ; sin(2 * pi *  224/1024)
    .xldouble    0.9819638691096    ; sin(2 * pi *  225/1024)
    .xldouble    0.9831054874312    ; sin(2 * pi *  226/1024)
    .xldouble    0.9842100923869    ; sin(2 * pi *  227/1024)
    .xldouble    0.9852776423889    ; sin(2 * pi *  228/1024)
    .xldouble    0.9863080972446    ; sin(2 * pi *  229/1024)
    .xldouble    0.9873014181579    ; sin(2 * pi *  230/1024)
    .xldouble    0.9882575677307    ; sin(2 * pi *  231/1024)
    .xldouble    0.9891765099648    ; sin(2 * pi *  232/1024)
    .xldouble    0.9900582102623    ; sin(2 * pi *  233/1024)
    .xldouble    0.9909026354278    ; sin(2 * pi *  234/1024)
    .xldouble    0.9917097536691    ; sin(2 * pi *  235/1024)
    .xldouble    0.9924795345987    ; sin(2 * pi *  236/1024)
    .xldouble    0.9932119492348    ; sin(2 * pi *  237/1024)
    .xldouble    0.9939069700024    ; sin(2 * pi *  238/1024)
    .xldouble    0.9945645707343    ; sin(2 * pi *  239/1024)
    .xldouble    0.9951847266722    ; sin(2 * pi *  240/1024)
    .xldouble    0.9957674144677    ; sin(2 * pi *  241/1024)
    .xldouble    0.9963126121828    ; sin(2 * pi *  242/1024)
    .xldouble    0.9968202992912    ; sin(2 * pi *  243/1024)
    .xldouble    0.9972904566787    ; sin(2 * pi *  244/1024)
    .xldouble    0.9977230666442    ; sin(2 * pi *  245/1024)
    .xldouble    0.9981181129001    ; sin(2 * pi *  246/1024)
    .xldouble    0.9984755805733    ; sin(2 * pi *  247/1024)
    .xldouble    0.9987954562052    ; sin(2 * pi *  248/1024)
    .xldouble    0.9990777277526    ; sin(2 * pi *  249/1024)
    .xldouble    0.9993223845883    ; sin(2 * pi *  250/1024)
    .xldouble    0.9995294175011    ; sin(2 * pi *  251/1024)
    .xldouble    0.9996988186962    ; sin(2 * pi *  252/1024)
    .xldouble    0.9998305817958    ; sin(2 * pi *  253/1024)
    .xldouble    0.9999247018391    ; sin(2 * pi *  254/1024)
    .xldouble    0.9999811752826    ; sin(2 * pi *  255/1024)
    .xldouble    1.0000000000000    ; sin(2 * pi *  256/1024)
    .xldouble    0.9999811752826    ; sin(2 * pi *  257/1024)
    .xldouble    0.9999247018391    ; sin(2 * pi *  258/1024)
    .xldouble    0.9998305817958    ; sin(2 * pi *  259/1024)
    .xldouble    0.9996988186962    ; sin(2 * pi *  260/1024)
    .xldouble    0.9995294175011    ; sin(2 * pi *  261/1024)
    .xldouble    0.9993223845883    ; sin(2 * pi *  262/1024)
    .xldouble    0.9990777277526    ; sin(2 * pi *  263/1024)
    .xldouble    0.9987954562052    ; sin(2 * pi *  264/1024)
    .xldouble    0.9984755805733    ; sin(2 * pi *  265/1024)
    .xldouble    0.9981181129001    ; sin(2 * pi *  266/1024)
    .xldouble    0.9977230666442    ; sin(2 * pi *  267/1024)
    .xldouble    0.9972904566787    ; sin(2 * pi *  268/1024)
    .xldouble    0.9968202992912    ; sin(2 * pi *  269/1024)
    .xldouble    0.9963126121828    ; sin(2 * pi *  270/1024)
    .xldouble    0.9957674144677    ; sin(2 * pi *  271/1024)
    .xldouble    0.9951847266722    ; sin(2 * pi *  272/1024)
    .xldouble    0.9945645707343    ; sin(2 * pi *  273/1024)
    .xldouble    0.9939069700024    ; sin(2 * pi *  274/1024)
    .xldouble    0.9932119492348    ; sin(2 * pi *  275/1024)
    .xldouble    0.9924795345987    ; sin(2 * pi *  276/1024)
    .xldouble    0.9917097536691    ; sin(2 * pi *  277/1024)
    .xldouble    0.9909026354278    ; sin(2 * pi *  278/1024)
    .xldouble    0.9900582102623    ; sin(2 * pi *  279/1024)
    .xldouble    0.9891765099648    ; sin(2 * pi *  280/1024)
    .xldouble    0.9882575677307    ; sin(2 * pi *  281/1024)
    .xldouble    0.9873014181579    ; sin(2 * pi *  282/1024)
    .xldouble    0.9863080972446    ; sin(2 * pi *  283/1024)
    .xldouble    0.9852776423889    ; sin(2 * pi *  284/1024)
    .xldouble    0.9842100923869    ; sin(2 * pi *  285/1024)
    .xldouble    0.9831054874312    ; sin(2 * pi *  286/1024)
    .xldouble    0.9819638691096    ; sin(2 * pi *  287/1024)
    .xldouble    0.9807852804032    ; sin(2 * pi *  288/1024)
    .xldouble    0.9795697656854    ; sin(2 * pi *  289/1024)
    .xldouble    0.9783173707196    ; sin(2 * pi *  290/1024)
    .xldouble    0.9770281426578    ; sin(2 * pi *  291/1024)
    .xldouble    0.9757021300385    ; sin(2 * pi *  292/1024)
    .xldouble    0.9743393827856    ; sin(2 * pi *  293/1024)
    .xldouble    0.9729399522056    ; sin(2 * pi *  294/1024)
    .xldouble    0.9715038909863    ; sin(2 * pi *  295/1024)
    .xldouble    0.9700312531945    ; sin(2 * pi *  296/1024)
    .xldouble    0.9685220942744    ; sin(2 * pi *  297/1024)
    .xldouble    0.9669764710449    ; sin(2 * pi *  298/1024)
    .xldouble    0.9653944416977    ; sin(2 * pi *  299/1024)
    .xldouble    0.9637760657954    ; sin(2 * pi *  300/1024)
    .xldouble    0.9621214042690    ; sin(2 * pi *  301/1024)
    .xldouble    0.9604305194156    ; sin(2 * pi *  302/1024)
    .xldouble    0.9587034748959    ; sin(2 * pi *  303/1024)
    .xldouble    0.9569403357322    ; sin(2 * pi *  304/1024)
    .xldouble    0.9551411683058    ; sin(2 * pi *  305/1024)
    .xldouble    0.9533060403542    ; sin(2 * pi *  306/1024)
    .xldouble    0.9514350209690    ; sin(2 * pi *  307/1024)
    .xldouble    0.9495281805930    ; sin(2 * pi *  308/1024)
    .xldouble    0.9475855910177    ; sin(2 * pi *  309/1024)
    .xldouble    0.9456073253805    ; sin(2 * pi *  310/1024)
    .xldouble    0.9435934581620    ; sin(2 * pi *  311/1024)
    .xldouble    0.9415440651830    ; sin(2 * pi *  312/1024)
    .xldouble    0.9394592236022    ; sin(2 * pi *  313/1024)
    .xldouble    0.9373390119126    ; sin(2 * pi *  314/1024)
    .xldouble    0.9351835099389    ; sin(2 * pi *  315/1024)
    .xldouble    0.9329927988347    ; sin(2 * pi *  316/1024)
    .xldouble    0.9307669610790    ; sin(2 * pi *  317/1024)
    .xldouble    0.9285060804732    ; sin(2 * pi *  318/1024)
    .xldouble    0.9262102421383    ; sin(2 * pi *  319/1024)
    .xldouble    0.9238795325113    ; sin(2 * pi *  320/1024)
    .xldouble    0.9215140393420    ; sin(2 * pi *  321/1024)
    .xldouble    0.9191138516901    ; sin(2 * pi *  322/1024)
    .xldouble    0.9166790599210    ; sin(2 * pi *  323/1024)
    .xldouble    0.9142097557035    ; sin(2 * pi *  324/1024)
    .xldouble    0.9117060320054    ; sin(2 * pi *  325/1024)
    .xldouble    0.9091679830905    ; sin(2 * pi *  326/1024)
    .xldouble    0.9065957045149    ; sin(2 * pi *  327/1024)
    .xldouble    0.9039892931234    ; sin(2 * pi *  328/1024)
    .xldouble    0.9013488470460    ; sin(2 * pi *  329/1024)
    .xldouble    0.8986744656940    ; sin(2 * pi *  330/1024)
    .xldouble    0.8959662497562    ; sin(2 * pi *  331/1024)
    .xldouble    0.8932243011955    ; sin(2 * pi *  332/1024)
    .xldouble    0.8904487232448    ; sin(2 * pi *  333/1024)
    .xldouble    0.8876396204029    ; sin(2 * pi *  334/1024)
    .xldouble    0.8847970984309    ; sin(2 * pi *  335/1024)
    .xldouble    0.8819212643484    ; sin(2 * pi *  336/1024)
    .xldouble    0.8790122264286    ; sin(2 * pi *  337/1024)
    .xldouble    0.8760700941954    ; sin(2 * pi *  338/1024)
    .xldouble    0.8730949784183    ; sin(2 * pi *  339/1024)
    .xldouble    0.8700869911087    ; sin(2 * pi *  340/1024)
    .xldouble    0.8670462455157    ; sin(2 * pi *  341/1024)
    .xldouble    0.8639728561216    ; sin(2 * pi *  342/1024)
    .xldouble    0.8608669386378    ; sin(2 * pi *  343/1024)
    .xldouble    0.8577286100003    ; sin(2 * pi *  344/1024)
    .xldouble    0.8545579883654    ; sin(2 * pi *  345/1024)
    .xldouble    0.8513551931053    ; sin(2 * pi *  346/1024)
    .xldouble    0.8481203448033    ; sin(2 * pi *  347/1024)
    .xldouble    0.8448535652497    ; sin(2 * pi *  348/1024)
    .xldouble    0.8415549774369    ; sin(2 * pi *  349/1024)
    .xldouble    0.8382247055548    ; sin(2 * pi *  350/1024)
    .xldouble    0.8348628749864    ; sin(2 * pi *  351/1024)
    .xldouble    0.8314696123025    ; sin(2 * pi *  352/1024)
    .xldouble    0.8280450452578    ; sin(2 * pi *  353/1024)
    .xldouble    0.8245893027850    ; sin(2 * pi *  354/1024)
    .xldouble    0.8211025149911    ; sin(2 * pi *  355/1024)
    .xldouble    0.8175848131516    ; sin(2 * pi *  356/1024)
    .xldouble    0.8140363297059    ; sin(2 * pi *  357/1024)
    .xldouble    0.8104571982526    ; sin(2 * pi *  358/1024)
    .xldouble    0.8068475535438    ; sin(2 * pi *  359/1024)
    .xldouble    0.8032075314806    ; sin(2 * pi *  360/1024)
    .xldouble    0.7995372691079    ; sin(2 * pi *  361/1024)
    .xldouble    0.7958369046089    ; sin(2 * pi *  362/1024)
    .xldouble    0.7921065773002    ; sin(2 * pi *  363/1024)
    .xldouble    0.7883464276266    ; sin(2 * pi *  364/1024)
    .xldouble    0.7845565971556    ; sin(2 * pi *  365/1024)
    .xldouble    0.7807372285721    ; sin(2 * pi *  366/1024)
    .xldouble    0.7768884656732    ; sin(2 * pi *  367/1024)
    .xldouble    0.7730104533627    ; sin(2 * pi *  368/1024)
    .xldouble    0.7691033376456    ; sin(2 * pi *  369/1024)
    .xldouble    0.7651672656225    ; sin(2 * pi *  370/1024)
    .xldouble    0.7612023854843    ; sin(2 * pi *  371/1024)
    .xldouble    0.7572088465065    ; sin(2 * pi *  372/1024)
    .xldouble    0.7531867990436    ; sin(2 * pi *  373/1024)
    .xldouble    0.7491363945235    ; sin(2 * pi *  374/1024)
    .xldouble    0.7450577854415    ; sin(2 * pi *  375/1024)
    .xldouble    0.7409511253550    ; sin(2 * pi *  376/1024)
    .xldouble    0.7368165688774    ; sin(2 * pi *  377/1024)
    .xldouble    0.7326542716724    ; sin(2 * pi *  378/1024)
    .xldouble    0.7284643904482    ; sin(2 * pi *  379/1024)
    .xldouble    0.7242470829515    ; sin(2 * pi *  380/1024)
    .xldouble    0.7200025079614    ; sin(2 * pi *  381/1024)
    .xldouble    0.7157308252838    ; sin(2 * pi *  382/1024)
    .xldouble    0.7114321957452    ; sin(2 * pi *  383/1024)
    .xldouble    0.7071067811865    ; sin(2 * pi *  384/1024)
    .xldouble    0.7027547444572    ; sin(2 * pi *  385/1024)
    .xldouble    0.6983762494090    ; sin(2 * pi *  386/1024)
    .xldouble    0.6939714608897    ; sin(2 * pi *  387/1024)
    .xldouble    0.6895405447371    ; sin(2 * pi *  388/1024)
    .xldouble    0.6850836677727    ; sin(2 * pi *  389/1024)
    .xldouble    0.6806009977955    ; sin(2 * pi *  390/1024)
    .xldouble    0.6760927035753    ; sin(2 * pi *  391/1024)
    .xldouble    0.6715589548470    ; sin(2 * pi *  392/1024)
    .xldouble    0.6669999223036    ; sin(2 * pi *  393/1024)
    .xldouble    0.6624157775902    ; sin(2 * pi *  394/1024)
    .xldouble    0.6578066932971    ; sin(2 * pi *  395/1024)
    .xldouble    0.6531728429538    ; sin(2 * pi *  396/1024)
    .xldouble    0.6485144010221    ; sin(2 * pi *  397/1024)
    .xldouble    0.6438315428898    ; sin(2 * pi *  398/1024)
    .xldouble    0.6391244448638    ; sin(2 * pi *  399/1024)
    .xldouble    0.6343932841636    ; sin(2 * pi *  400/1024)
    .xldouble    0.6296382389149    ; sin(2 * pi *  401/1024)
    .xldouble    0.6248594881424    ; sin(2 * pi *  402/1024)
    .xldouble    0.6200572117633    ; sin(2 * pi *  403/1024)
    .xldouble    0.6152315905806    ; sin(2 * pi *  404/1024)
    .xldouble    0.6103828062763    ; sin(2 * pi *  405/1024)
    .xldouble    0.6055110414043    ; sin(2 * pi *  406/1024)
    .xldouble    0.6006164793839    ; sin(2 * pi *  407/1024)
    .xldouble    0.5956993044924    ; sin(2 * pi *  408/1024)
    .xldouble    0.5907597018589    ; sin(2 * pi *  409/1024)
    .xldouble    0.5857978574564    ; sin(2 * pi *  410/1024)
    .xldouble    0.5808139580958    ; sin(2 * pi *  411/1024)
    .xldouble    0.5758081914178    ; sin(2 * pi *  412/1024)
    .xldouble    0.5707807458870    ; sin(2 * pi *  413/1024)
    .xldouble    0.5657318107836    ; sin(2 * pi *  414/1024)
    .xldouble    0.5606615761973    ; sin(2 * pi *  415/1024)
    .xldouble    0.5555702330196    ; sin(2 * pi *  416/1024)
    .xldouble    0.5504579729366    ; sin(2 * pi *  417/1024)
    .xldouble    0.5453249884220    ; sin(2 * pi *  418/1024)
    .xldouble    0.5401714727299    ; sin(2 * pi *  419/1024)
    .xldouble    0.5349976198871    ; sin(2 * pi *  420/1024)
    .xldouble    0.5298036246863    ; sin(2 * pi *  421/1024)
    .xldouble    0.5245896826785    ; sin(2 * pi *  422/1024)
    .xldouble    0.5193559901656    ; sin(2 * pi *  423/1024)
    .xldouble    0.5141027441932    ; sin(2 * pi *  424/1024)
    .xldouble    0.5088301425431    ; sin(2 * pi *  425/1024)
    .xldouble    0.5035383837257    ; sin(2 * pi *  426/1024)
    .xldouble    0.4982276669728    ; sin(2 * pi *  427/1024)
    .xldouble    0.4928981922298    ; sin(2 * pi *  428/1024)
    .xldouble    0.4875501601484    ; sin(2 * pi *  429/1024)
    .xldouble    0.4821837720791    ; sin(2 * pi *  430/1024)
    .xldouble    0.4767992300633    ; sin(2 * pi *  431/1024)
    .xldouble    0.4713967368260    ; sin(2 * pi *  432/1024)
    .xldouble    0.4659764957680    ; sin(2 * pi *  433/1024)
    .xldouble    0.4605387109582    ; sin(2 * pi *  434/1024)
    .xldouble    0.4550835871263    ; sin(2 * pi *  435/1024)
    .xldouble    0.4496113296546    ; sin(2 * pi *  436/1024)
    .xldouble    0.4441221445704    ; sin(2 * pi *  437/1024)
    .xldouble    0.4386162385385    ; sin(2 * pi *  438/1024)
    .xldouble    0.4330938188532    ; sin(2 * pi *  439/1024)
    .xldouble    0.4275550934303    ; sin(2 * pi *  440/1024)
    .xldouble    0.4220002707998    ; sin(2 * pi *  441/1024)
    .xldouble    0.4164295600976    ; sin(2 * pi *  442/1024)
    .xldouble    0.4108431710579    ; sin(2 * pi *  443/1024)
    .xldouble    0.4052413140050    ; sin(2 * pi *  444/1024)
    .xldouble    0.3996241998456    ; sin(2 * pi *  445/1024)
    .xldouble    0.3939920400610    ; sin(2 * pi *  446/1024)
    .xldouble    0.3883450466988    ; sin(2 * pi *  447/1024)
    .xldouble    0.3826834323651    ; sin(2 * pi *  448/1024)
    .xldouble    0.3770074102164    ; sin(2 * pi *  449/1024)
    .xldouble    0.3713171939518    ; sin(2 * pi *  450/1024)
    .xldouble    0.3656129978048    ; sin(2 * pi *  451/1024)
    .xldouble    0.3598950365350    ; sin(2 * pi *  452/1024)
    .xldouble    0.3541635254205    ; sin(2 * pi *  453/1024)
    .xldouble    0.3484186802494    ; sin(2 * pi *  454/1024)
    .xldouble    0.3426607173120    ; sin(2 * pi *  455/1024)
    .xldouble    0.3368898533922    ; sin(2 * pi *  456/1024)
    .xldouble    0.3311063057599    ; sin(2 * pi *  457/1024)
    .xldouble    0.3253102921623    ; sin(2 * pi *  458/1024)
    .xldouble    0.3195020308160    ; sin(2 * pi *  459/1024)
    .xldouble    0.3136817403989    ; sin(2 * pi *  460/1024)
    .xldouble    0.3078496400415    ; sin(2 * pi *  461/1024)
    .xldouble    0.3020059493192    ; sin(2 * pi *  462/1024)
    .xldouble    0.2961508882436    ; sin(2 * pi *  463/1024)
    .xldouble    0.2902846772545    ; sin(2 * pi *  464/1024)
    .xldouble    0.2844075372113    ; sin(2 * pi *  465/1024)
    .xldouble    0.2785196893851    ; sin(2 * pi *  466/1024)
    .xldouble    0.2726213554499    ; sin(2 * pi *  467/1024)
    .xldouble    0.2667127574749    ; sin(2 * pi *  468/1024)
    .xldouble    0.2607941179153    ; sin(2 * pi *  469/1024)
    .xldouble    0.2548656596045    ; sin(2 * pi *  470/1024)
    .xldouble    0.2489276057457    ; sin(2 * pi *  471/1024)
    .xldouble    0.2429801799033    ; sin(2 * pi *  472/1024)
    .xldouble    0.2370236059944    ; sin(2 * pi *  473/1024)
    .xldouble    0.2310581082807    ; sin(2 * pi *  474/1024)
    .xldouble    0.2250839113598    ; sin(2 * pi *  475/1024)
    .xldouble    0.2191012401569    ; sin(2 * pi *  476/1024)
    .xldouble    0.2131103199161    ; sin(2 * pi *  477/1024)
    .xldouble    0.2071113761922    ; sin(2 * pi *  478/1024)
    .xldouble    0.2011046348421    ; sin(2 * pi *  479/1024)
    .xldouble    0.1950903220161    ; sin(2 * pi *  480/1024)
    .xldouble    0.1890686641498    ; sin(2 * pi *  481/1024)
    .xldouble    0.1830398879551    ; sin(2 * pi *  482/1024)
    .xldouble    0.1770042204121    ; sin(2 * pi *  483/1024)
    .xldouble    0.1709618887603    ; sin(2 * pi *  484/1024)
    .xldouble    0.1649131204900    ; sin(2 * pi *  485/1024)
    .xldouble    0.1588581433339    ; sin(2 * pi *  486/1024)
    .xldouble    0.1527971852584    ; sin(2 * pi *  487/1024)
    .xldouble    0.1467304744554    ; sin(2 * pi *  488/1024)
    .xldouble    0.1406582393328    ; sin(2 * pi *  489/1024)
    .xldouble    0.1345807085071    ; sin(2 * pi *  490/1024)
    .xldouble    0.1284981107938    ; sin(2 * pi *  491/1024)
    .xldouble    0.1224106751992    ; sin(2 * pi *  492/1024)
    .xldouble    0.1163186309119    ; sin(2 * pi *  493/1024)
    .xldouble    0.1102222072939    ; sin(2 * pi *  494/1024)
    .xldouble    0.1041216338721    ; sin(2 * pi *  495/1024)
    .xldouble    0.0980171403296    ; sin(2 * pi *  496/1024)
    .xldouble    0.0919089564971    ; sin(2 * pi *  497/1024)
    .xldouble    0.0857973123444    ; sin(2 * pi *  498/1024)
    .xldouble    0.0796824379714    ; sin(2 * pi *  499/1024)
    .xldouble    0.0735645635997    ; sin(2 * pi *  500/1024)
    .xldouble    0.0674439195637    ; sin(2 * pi *  501/1024)
    .xldouble    0.0613207363022    ; sin(2 * pi *  502/1024)
    .xldouble    0.0551952443497    ; sin(2 * pi *  503/1024)
    .xldouble    0.0490676743274    ; sin(2 * pi *  504/1024)
    .xldouble    0.0429382569349    ; sin(2 * pi *  505/1024)
    .xldouble    0.0368072229414    ; sin(2 * pi *  506/1024)
    .xldouble    0.0306748031766    ; sin(2 * pi *  507/1024)
    .xldouble    0.0245412285229    ; sin(2 * pi *  508/1024)
    .xldouble    0.0184067299058    ; sin(2 * pi *  509/1024)
    .xldouble    0.0122715382857    ; sin(2 * pi *  510/1024)
    .xldouble    0.0061358846492    ; sin(2 * pi *  511/1024)
    .xldouble    0.0000000000000    ; sin(2 * pi *  512/1024)
    .xldouble   -0.0061358846492    ; sin(2 * pi *  513/1024)
    .xldouble   -0.0122715382857    ; sin(2 * pi *  514/1024)
    .xldouble   -0.0184067299058    ; sin(2 * pi *  515/1024)
    .xldouble   -0.0245412285229    ; sin(2 * pi *  516/1024)
    .xldouble   -0.0306748031766    ; sin(2 * pi *  517/1024)
    .xldouble   -0.0368072229414    ; sin(2 * pi *  518/1024)
    .xldouble   -0.0429382569349    ; sin(2 * pi *  519/1024)
    .xldouble   -0.0490676743274    ; sin(2 * pi *  520/1024)
    .xldouble   -0.0551952443497    ; sin(2 * pi *  521/1024)
    .xldouble   -0.0613207363022    ; sin(2 * pi *  522/1024)
    .xldouble   -0.0674439195637    ; sin(2 * pi *  523/1024)
    .xldouble   -0.0735645635997    ; sin(2 * pi *  524/1024)
    .xldouble   -0.0796824379714    ; sin(2 * pi *  525/1024)
    .xldouble   -0.0857973123444    ; sin(2 * pi *  526/1024)
    .xldouble   -0.0919089564971    ; sin(2 * pi *  527/1024)
    .xldouble   -0.0980171403296    ; sin(2 * pi *  528/1024)
    .xldouble   -0.1041216338721    ; sin(2 * pi *  529/1024)
    .xldouble   -0.1102222072939    ; sin(2 * pi *  530/1024)
    .xldouble   -0.1163186309119    ; sin(2 * pi *  531/1024)
    .xldouble   -0.1224106751992    ; sin(2 * pi *  532/1024)
    .xldouble   -0.1284981107938    ; sin(2 * pi *  533/1024)
    .xldouble   -0.1345807085071    ; sin(2 * pi *  534/1024)
    .xldouble   -0.1406582393328    ; sin(2 * pi *  535/1024)
    .xldouble   -0.1467304744554    ; sin(2 * pi *  536/1024)
    .xldouble   -0.1527971852584    ; sin(2 * pi *  537/1024)
    .xldouble   -0.1588581433339    ; sin(2 * pi *  538/1024)
    .xldouble   -0.1649131204900    ; sin(2 * pi *  539/1024)
    .xldouble   -0.1709618887603    ; sin(2 * pi *  540/1024)
    .xldouble   -0.1770042204121    ; sin(2 * pi *  541/1024)
    .xldouble   -0.1830398879551    ; sin(2 * pi *  542/1024)
    .xldouble   -0.1890686641498    ; sin(2 * pi *  543/1024)
    .xldouble   -0.1950903220161    ; sin(2 * pi *  544/1024)
    .xldouble   -0.2011046348421    ; sin(2 * pi *  545/1024)
    .xldouble   -0.2071113761922    ; sin(2 * pi *  546/1024)
    .xldouble   -0.2131103199161    ; sin(2 * pi *  547/1024)
    .xldouble   -0.2191012401569    ; sin(2 * pi *  548/1024)
    .xldouble   -0.2250839113598    ; sin(2 * pi *  549/1024)
    .xldouble   -0.2310581082807    ; sin(2 * pi *  550/1024)
    .xldouble   -0.2370236059944    ; sin(2 * pi *  551/1024)
    .xldouble   -0.2429801799033    ; sin(2 * pi *  552/1024)
    .xldouble   -0.2489276057457    ; sin(2 * pi *  553/1024)
    .xldouble   -0.2548656596045    ; sin(2 * pi *  554/1024)
    .xldouble   -0.2607941179153    ; sin(2 * pi *  555/1024)
    .xldouble   -0.2667127574749    ; sin(2 * pi *  556/1024)
    .xldouble   -0.2726213554499    ; sin(2 * pi *  557/1024)
    .xldouble   -0.2785196893851    ; sin(2 * pi *  558/1024)
    .xldouble   -0.2844075372113    ; sin(2 * pi *  559/1024)
    .xldouble   -0.2902846772545    ; sin(2 * pi *  560/1024)
    .xldouble   -0.2961508882436    ; sin(2 * pi *  561/1024)
    .xldouble   -0.3020059493192    ; sin(2 * pi *  562/1024)
    .xldouble   -0.3078496400415    ; sin(2 * pi *  563/1024)
    .xldouble   -0.3136817403989    ; sin(2 * pi *  564/1024)
    .xldouble   -0.3195020308160    ; sin(2 * pi *  565/1024)
    .xldouble   -0.3253102921623    ; sin(2 * pi *  566/1024)
    .xldouble   -0.3311063057599    ; sin(2 * pi *  567/1024)
    .xldouble   -0.3368898533922    ; sin(2 * pi *  568/1024)
    .xldouble   -0.3426607173120    ; sin(2 * pi *  569/1024)
    .xldouble   -0.3484186802494    ; sin(2 * pi *  570/1024)
    .xldouble   -0.3541635254205    ; sin(2 * pi *  571/1024)
    .xldouble   -0.3598950365350    ; sin(2 * pi *  572/1024)
    .xldouble   -0.3656129978048    ; sin(2 * pi *  573/1024)
    .xldouble   -0.3713171939518    ; sin(2 * pi *  574/1024)
    .xldouble   -0.3770074102164    ; sin(2 * pi *  575/1024)
    .xldouble   -0.3826834323651    ; sin(2 * pi *  576/1024)
    .xldouble   -0.3883450466988    ; sin(2 * pi *  577/1024)
    .xldouble   -0.3939920400610    ; sin(2 * pi *  578/1024)
    .xldouble   -0.3996241998456    ; sin(2 * pi *  579/1024)
    .xldouble   -0.4052413140050    ; sin(2 * pi *  580/1024)
    .xldouble   -0.4108431710579    ; sin(2 * pi *  581/1024)
    .xldouble   -0.4164295600976    ; sin(2 * pi *  582/1024)
    .xldouble   -0.4220002707998    ; sin(2 * pi *  583/1024)
    .xldouble   -0.4275550934303    ; sin(2 * pi *  584/1024)
    .xldouble   -0.4330938188532    ; sin(2 * pi *  585/1024)
    .xldouble   -0.4386162385385    ; sin(2 * pi *  586/1024)
    .xldouble   -0.4441221445704    ; sin(2 * pi *  587/1024)
    .xldouble   -0.4496113296546    ; sin(2 * pi *  588/1024)
    .xldouble   -0.4550835871263    ; sin(2 * pi *  589/1024)
    .xldouble   -0.4605387109582    ; sin(2 * pi *  590/1024)
    .xldouble   -0.4659764957680    ; sin(2 * pi *  591/1024)
    .xldouble   -0.4713967368260    ; sin(2 * pi *  592/1024)
    .xldouble   -0.4767992300633    ; sin(2 * pi *  593/1024)
    .xldouble   -0.4821837720791    ; sin(2 * pi *  594/1024)
    .xldouble   -0.4875501601484    ; sin(2 * pi *  595/1024)
    .xldouble   -0.4928981922298    ; sin(2 * pi *  596/1024)
    .xldouble   -0.4982276669728    ; sin(2 * pi *  597/1024)
    .xldouble   -0.5035383837257    ; sin(2 * pi *  598/1024)
    .xldouble   -0.5088301425431    ; sin(2 * pi *  599/1024)
    .xldouble   -0.5141027441932    ; sin(2 * pi *  600/1024)
    .xldouble   -0.5193559901656    ; sin(2 * pi *  601/1024)
    .xldouble   -0.5245896826785    ; sin(2 * pi *  602/1024)
    .xldouble   -0.5298036246863    ; sin(2 * pi *  603/1024)
    .xldouble   -0.5349976198871    ; sin(2 * pi *  604/1024)
    .xldouble   -0.5401714727299    ; sin(2 * pi *  605/1024)
    .xldouble   -0.5453249884220    ; sin(2 * pi *  606/1024)
    .xldouble   -0.5504579729366    ; sin(2 * pi *  607/1024)
    .xldouble   -0.5555702330196    ; sin(2 * pi *  608/1024)
    .xldouble   -0.5606615761973    ; sin(2 * pi *  609/1024)
    .xldouble   -0.5657318107836    ; sin(2 * pi *  610/1024)
    .xldouble   -0.5707807458870    ; sin(2 * pi *  611/1024)
    .xldouble   -0.5758081914178    ; sin(2 * pi *  612/1024)
    .xldouble   -0.5808139580958    ; sin(2 * pi *  613/1024)
    .xldouble   -0.5857978574564    ; sin(2 * pi *  614/1024)
    .xldouble   -0.5907597018589    ; sin(2 * pi *  615/1024)
    .xldouble   -0.5956993044924    ; sin(2 * pi *  616/1024)
    .xldouble   -0.6006164793839    ; sin(2 * pi *  617/1024)
    .xldouble   -0.6055110414043    ; sin(2 * pi *  618/1024)
    .xldouble   -0.6103828062763    ; sin(2 * pi *  619/1024)
    .xldouble   -0.6152315905806    ; sin(2 * pi *  620/1024)
    .xldouble   -0.6200572117633    ; sin(2 * pi *  621/1024)
    .xldouble   -0.6248594881424    ; sin(2 * pi *  622/1024)
    .xldouble   -0.6296382389149    ; sin(2 * pi *  623/1024)
    .xldouble   -0.6343932841636    ; sin(2 * pi *  624/1024)
    .xldouble   -0.6391244448638    ; sin(2 * pi *  625/1024)
    .xldouble   -0.6438315428898    ; sin(2 * pi *  626/1024)
    .xldouble   -0.6485144010221    ; sin(2 * pi *  627/1024)
    .xldouble   -0.6531728429538    ; sin(2 * pi *  628/1024)
    .xldouble   -0.6578066932971    ; sin(2 * pi *  629/1024)
    .xldouble   -0.6624157775902    ; sin(2 * pi *  630/1024)
    .xldouble   -0.6669999223036    ; sin(2 * pi *  631/1024)
    .xldouble   -0.6715589548470    ; sin(2 * pi *  632/1024)
    .xldouble   -0.6760927035753    ; sin(2 * pi *  633/1024)
    .xldouble   -0.6806009977955    ; sin(2 * pi *  634/1024)
    .xldouble   -0.6850836677727    ; sin(2 * pi *  635/1024)
    .xldouble   -0.6895405447371    ; sin(2 * pi *  636/1024)
    .xldouble   -0.6939714608897    ; sin(2 * pi *  637/1024)
    .xldouble   -0.6983762494090    ; sin(2 * pi *  638/1024)
    .xldouble   -0.7027547444572    ; sin(2 * pi *  639/1024)
    .xldouble   -0.7071067811865    ; sin(2 * pi *  640/1024)
    .xldouble   -0.7114321957452    ; sin(2 * pi *  641/1024)
    .xldouble   -0.7157308252838    ; sin(2 * pi *  642/1024)
    .xldouble   -0.7200025079614    ; sin(2 * pi *  643/1024)
    .xldouble   -0.7242470829515    ; sin(2 * pi *  644/1024)
    .xldouble   -0.7284643904482    ; sin(2 * pi *  645/1024)
    .xldouble   -0.7326542716724    ; sin(2 * pi *  646/1024)
    .xldouble   -0.7368165688774    ; sin(2 * pi *  647/1024)
    .xldouble   -0.7409511253550    ; sin(2 * pi *  648/1024)
    .xldouble   -0.7450577854415    ; sin(2 * pi *  649/1024)
    .xldouble   -0.7491363945235    ; sin(2 * pi *  650/1024)
    .xldouble   -0.7531867990436    ; sin(2 * pi *  651/1024)
    .xldouble   -0.7572088465065    ; sin(2 * pi *  652/1024)
    .xldouble   -0.7612023854843    ; sin(2 * pi *  653/1024)
    .xldouble   -0.7651672656225    ; sin(2 * pi *  654/1024)
    .xldouble   -0.7691033376456    ; sin(2 * pi *  655/1024)
    .xldouble   -0.7730104533627    ; sin(2 * pi *  656/1024)
    .xldouble   -0.7768884656732    ; sin(2 * pi *  657/1024)
    .xldouble   -0.7807372285721    ; sin(2 * pi *  658/1024)
    .xldouble   -0.7845565971556    ; sin(2 * pi *  659/1024)
    .xldouble   -0.7883464276266    ; sin(2 * pi *  660/1024)
    .xldouble   -0.7921065773002    ; sin(2 * pi *  661/1024)
    .xldouble   -0.7958369046089    ; sin(2 * pi *  662/1024)
    .xldouble   -0.7995372691079    ; sin(2 * pi *  663/1024)
    .xldouble   -0.8032075314806    ; sin(2 * pi *  664/1024)
    .xldouble   -0.8068475535438    ; sin(2 * pi *  665/1024)
    .xldouble   -0.8104571982526    ; sin(2 * pi *  666/1024)
    .xldouble   -0.8140363297059    ; sin(2 * pi *  667/1024)
    .xldouble   -0.8175848131516    ; sin(2 * pi *  668/1024)
    .xldouble   -0.8211025149911    ; sin(2 * pi *  669/1024)
    .xldouble   -0.8245893027850    ; sin(2 * pi *  670/1024)
    .xldouble   -0.8280450452578    ; sin(2 * pi *  671/1024)
    .xldouble   -0.8314696123025    ; sin(2 * pi *  672/1024)
    .xldouble   -0.8348628749864    ; sin(2 * pi *  673/1024)
    .xldouble   -0.8382247055548    ; sin(2 * pi *  674/1024)
    .xldouble   -0.8415549774369    ; sin(2 * pi *  675/1024)
    .xldouble   -0.8448535652497    ; sin(2 * pi *  676/1024)
    .xldouble   -0.8481203448033    ; sin(2 * pi *  677/1024)
    .xldouble   -0.8513551931053    ; sin(2 * pi *  678/1024)
    .xldouble   -0.8545579883654    ; sin(2 * pi *  679/1024)
    .xldouble   -0.8577286100003    ; sin(2 * pi *  680/1024)
    .xldouble   -0.8608669386378    ; sin(2 * pi *  681/1024)
    .xldouble   -0.8639728561216    ; sin(2 * pi *  682/1024)
    .xldouble   -0.8670462455157    ; sin(2 * pi *  683/1024)
    .xldouble   -0.8700869911087    ; sin(2 * pi *  684/1024)
    .xldouble   -0.8730949784183    ; sin(2 * pi *  685/1024)
    .xldouble   -0.8760700941954    ; sin(2 * pi *  686/1024)
    .xldouble   -0.8790122264286    ; sin(2 * pi *  687/1024)
    .xldouble   -0.8819212643484    ; sin(2 * pi *  688/1024)
    .xldouble   -0.8847970984309    ; sin(2 * pi *  689/1024)
    .xldouble   -0.8876396204029    ; sin(2 * pi *  690/1024)
    .xldouble   -0.8904487232448    ; sin(2 * pi *  691/1024)
    .xldouble   -0.8932243011955    ; sin(2 * pi *  692/1024)
    .xldouble   -0.8959662497562    ; sin(2 * pi *  693/1024)
    .xldouble   -0.8986744656940    ; sin(2 * pi *  694/1024)
    .xldouble   -0.9013488470460    ; sin(2 * pi *  695/1024)
    .xldouble   -0.9039892931234    ; sin(2 * pi *  696/1024)
    .xldouble   -0.9065957045149    ; sin(2 * pi *  697/1024)
    .xldouble   -0.9091679830905    ; sin(2 * pi *  698/1024)
    .xldouble   -0.9117060320054    ; sin(2 * pi *  699/1024)
    .xldouble   -0.9142097557035    ; sin(2 * pi *  700/1024)
    .xldouble   -0.9166790599210    ; sin(2 * pi *  701/1024)
    .xldouble   -0.9191138516901    ; sin(2 * pi *  702/1024)
    .xldouble   -0.9215140393420    ; sin(2 * pi *  703/1024)
    .xldouble   -0.9238795325113    ; sin(2 * pi *  704/1024)
    .xldouble   -0.9262102421383    ; sin(2 * pi *  705/1024)
    .xldouble   -0.9285060804732    ; sin(2 * pi *  706/1024)
    .xldouble   -0.9307669610790    ; sin(2 * pi *  707/1024)
    .xldouble   -0.9329927988347    ; sin(2 * pi *  708/1024)
    .xldouble   -0.9351835099389    ; sin(2 * pi *  709/1024)
    .xldouble   -0.9373390119126    ; sin(2 * pi *  710/1024)
    .xldouble   -0.9394592236022    ; sin(2 * pi *  711/1024)
    .xldouble   -0.9415440651830    ; sin(2 * pi *  712/1024)
    .xldouble   -0.9435934581620    ; sin(2 * pi *  713/1024)
    .xldouble   -0.9456073253805    ; sin(2 * pi *  714/1024)
    .xldouble   -0.9475855910177    ; sin(2 * pi *  715/1024)
    .xldouble   -0.9495281805930    ; sin(2 * pi *  716/1024)
    .xldouble   -0.9514350209690    ; sin(2 * pi *  717/1024)
    .xldouble   -0.9533060403542    ; sin(2 * pi *  718/1024)
    .xldouble   -0.9551411683058    ; sin(2 * pi *  719/1024)
    .xldouble   -0.9569403357322    ; sin(2 * pi *  720/1024)
    .xldouble   -0.9587034748959    ; sin(2 * pi *  721/1024)
    .xldouble   -0.9604305194156    ; sin(2 * pi *  722/1024)
    .xldouble   -0.9621214042690    ; sin(2 * pi *  723/1024)
    .xldouble   -0.9637760657954    ; sin(2 * pi *  724/1024)
    .xldouble   -0.9653944416977    ; sin(2 * pi *  725/1024)
    .xldouble   -0.9669764710449    ; sin(2 * pi *  726/1024)
    .xldouble   -0.9685220942744    ; sin(2 * pi *  727/1024)
    .xldouble   -0.9700312531945    ; sin(2 * pi *  728/1024)
    .xldouble   -0.9715038909863    ; sin(2 * pi *  729/1024)
    .xldouble   -0.9729399522056    ; sin(2 * pi *  730/1024)
    .xldouble   -0.9743393827856    ; sin(2 * pi *  731/1024)
    .xldouble   -0.9757021300385    ; sin(2 * pi *  732/1024)
    .xldouble   -0.9770281426578    ; sin(2 * pi *  733/1024)
    .xldouble   -0.9783173707196    ; sin(2 * pi *  734/1024)
    .xldouble   -0.9795697656854    ; sin(2 * pi *  735/1024)
    .xldouble   -0.9807852804032    ; sin(2 * pi *  736/1024)
    .xldouble   -0.9819638691096    ; sin(2 * pi *  737/1024)
    .xldouble   -0.9831054874312    ; sin(2 * pi *  738/1024)
    .xldouble   -0.9842100923869    ; sin(2 * pi *  739/1024)
    .xldouble   -0.9852776423889    ; sin(2 * pi *  740/1024)
    .xldouble   -0.9863080972446    ; sin(2 * pi *  741/1024)
    .xldouble   -0.9873014181579    ; sin(2 * pi *  742/1024)
    .xldouble   -0.9882575677307    ; sin(2 * pi *  743/1024)
    .xldouble   -0.9891765099648    ; sin(2 * pi *  744/1024)
    .xldouble   -0.9900582102623    ; sin(2 * pi *  745/1024)
    .xldouble   -0.9909026354278    ; sin(2 * pi *  746/1024)
    .xldouble   -0.9917097536691    ; sin(2 * pi *  747/1024)
    .xldouble   -0.9924795345987    ; sin(2 * pi *  748/1024)
    .xldouble   -0.9932119492348    ; sin(2 * pi *  749/1024)
    .xldouble   -0.9939069700024    ; sin(2 * pi *  750/1024)
    .xldouble   -0.9945645707343    ; sin(2 * pi *  751/1024)
    .xldouble   -0.9951847266722    ; sin(2 * pi *  752/1024)
    .xldouble   -0.9957674144677    ; sin(2 * pi *  753/1024)
    .xldouble   -0.9963126121828    ; sin(2 * pi *  754/1024)
    .xldouble   -0.9968202992912    ; sin(2 * pi *  755/1024)
    .xldouble   -0.9972904566787    ; sin(2 * pi *  756/1024)
    .xldouble   -0.9977230666442    ; sin(2 * pi *  757/1024)
    .xldouble   -0.9981181129001    ; sin(2 * pi *  758/1024)
    .xldouble   -0.9984755805733    ; sin(2 * pi *  759/1024)
    .xldouble   -0.9987954562052    ; sin(2 * pi *  760/1024)
    .xldouble   -0.9990777277526    ; sin(2 * pi *  761/1024)
    .xldouble   -0.9993223845883    ; sin(2 * pi *  762/1024)
    .xldouble   -0.9995294175011    ; sin(2 * pi *  763/1024)
    .xldouble   -0.9996988186962    ; sin(2 * pi *  764/1024)
    .xldouble   -0.9998305817958    ; sin(2 * pi *  765/1024)
    .xldouble   -0.9999247018391    ; sin(2 * pi *  766/1024)
    .xldouble   -0.9999811752826    ; sin(2 * pi *  767/1024)
_FPU64CFFTtwiddleFactorsEnd:

    .sect   "FPU64fftTables"
    .align  2
_FPU64RFFTtwiddleFactors:
                                ; +---------Stage  3--------+
    .xldouble   0.7071067811865 ; | Cos(  1 * 2 * pi /    8)|
    .xldouble   0.7071067811865 ; | Sin(  1 * 2 * pi /    8)|
    .xldouble   0.0000000000000 ; | Cos(  2 * 2 * pi /    8)|
    .xldouble   1.0000000000000 ; | Sin(  2 * 2 * pi /    8)|
                                ; +---------Stage  4--------+
    .xldouble   0.9238795325113 ; | Cos(  1 * 2 * pi /   16)|
    .xldouble   0.3826834323651 ; | Sin(  1 * 2 * pi /   16)|
    .xldouble   0.7071067811865 ; | Cos(  2 * 2 * pi /   16)|
    .xldouble   0.7071067811865 ; | Sin(  2 * 2 * pi /   16)|
    .xldouble   0.3826834323651 ; | Cos(  3 * 2 * pi /   16)|
    .xldouble   0.9238795325113 ; | Sin(  3 * 2 * pi /   16)|
    .xldouble   0.0000000000000 ; | Cos(  4 * 2 * pi /   16)|
    .xldouble   1.0000000000000 ; | Sin(  4 * 2 * pi /   16)|
                                ; +---------Stage  5--------+
    .xldouble   0.9807852804032 ; | Cos(  1 * 2 * pi /   32)|
    .xldouble   0.1950903220161 ; | Sin(  1 * 2 * pi /   32)|
    .xldouble   0.9238795325113 ; | Cos(  2 * 2 * pi /   32)|
    .xldouble   0.3826834323651 ; | Sin(  2 * 2 * pi /   32)|
    .xldouble   0.8314696123025 ; | Cos(  3 * 2 * pi /   32)|
    .xldouble   0.5555702330196 ; | Sin(  3 * 2 * pi /   32)|
    .xldouble   0.7071067811865 ; | Cos(  4 * 2 * pi /   32)|
    .xldouble   0.7071067811865 ; | Sin(  4 * 2 * pi /   32)|
    .xldouble   0.5555702330196 ; | Cos(  5 * 2 * pi /   32)|
    .xldouble   0.8314696123025 ; | Sin(  5 * 2 * pi /   32)|
    .xldouble   0.3826834323651 ; | Cos(  6 * 2 * pi /   32)|
    .xldouble   0.9238795325113 ; | Sin(  6 * 2 * pi /   32)|
    .xldouble   0.1950903220161 ; | Cos(  7 * 2 * pi /   32)|
    .xldouble   0.9807852804032 ; | Sin(  7 * 2 * pi /   32)|
    .xldouble   0.0000000000000 ; | Cos(  8 * 2 * pi /   32)|
    .xldouble   1.0000000000000 ; | Sin(  8 * 2 * pi /   32)|
                                ; +---------Stage  6--------+
    .xldouble   0.9951847266722 ; | Cos(  1 * 2 * pi /   64)|
    .xldouble   0.0980171403296 ; | Sin(  1 * 2 * pi /   64)|
    .xldouble   0.9807852804032 ; | Cos(  2 * 2 * pi /   64)|
    .xldouble   0.1950903220161 ; | Sin(  2 * 2 * pi /   64)|
    .xldouble   0.9569403357322 ; | Cos(  3 * 2 * pi /   64)|
    .xldouble   0.2902846772545 ; | Sin(  3 * 2 * pi /   64)|
    .xldouble   0.9238795325113 ; | Cos(  4 * 2 * pi /   64)|
    .xldouble   0.3826834323651 ; | Sin(  4 * 2 * pi /   64)|
    .xldouble   0.8819212643484 ; | Cos(  5 * 2 * pi /   64)|
    .xldouble   0.4713967368260 ; | Sin(  5 * 2 * pi /   64)|
    .xldouble   0.8314696123025 ; | Cos(  6 * 2 * pi /   64)|
    .xldouble   0.5555702330196 ; | Sin(  6 * 2 * pi /   64)|
    .xldouble   0.7730104533627 ; | Cos(  7 * 2 * pi /   64)|
    .xldouble   0.6343932841636 ; | Sin(  7 * 2 * pi /   64)|
    .xldouble   0.7071067811865 ; | Cos(  8 * 2 * pi /   64)|
    .xldouble   0.7071067811865 ; | Sin(  8 * 2 * pi /   64)|
    .xldouble   0.6343932841636 ; | Cos(  9 * 2 * pi /   64)|
    .xldouble   0.7730104533627 ; | Sin(  9 * 2 * pi /   64)|
    .xldouble   0.5555702330196 ; | Cos( 10 * 2 * pi /   64)|
    .xldouble   0.8314696123025 ; | Sin( 10 * 2 * pi /   64)|
    .xldouble   0.4713967368260 ; | Cos( 11 * 2 * pi /   64)|
    .xldouble   0.8819212643484 ; | Sin( 11 * 2 * pi /   64)|
    .xldouble   0.3826834323651 ; | Cos( 12 * 2 * pi /   64)|
    .xldouble   0.9238795325113 ; | Sin( 12 * 2 * pi /   64)|
    .xldouble   0.2902846772545 ; | Cos( 13 * 2 * pi /   64)|
    .xldouble   0.9569403357322 ; | Sin( 13 * 2 * pi /   64)|
    .xldouble   0.1950903220161 ; | Cos( 14 * 2 * pi /   64)|
    .xldouble   0.9807852804032 ; | Sin( 14 * 2 * pi /   64)|
    .xldouble   0.0980171403296 ; | Cos( 15 * 2 * pi /   64)|
    .xldouble   0.9951847266722 ; | Sin( 15 * 2 * pi /   64)|
    .xldouble   0.0000000000000 ; | Cos( 16 * 2 * pi /   64)|
    .xldouble   1.0000000000000 ; | Sin( 16 * 2 * pi /   64)|
                                ; +---------Stage  7--------+
    .xldouble   0.9987954562052 ; | Cos(  1 * 2 * pi /  128)|
    .xldouble   0.0490676743274 ; | Sin(  1 * 2 * pi /  128)|
    .xldouble   0.9951847266722 ; | Cos(  2 * 2 * pi /  128)|
    .xldouble   0.0980171403296 ; | Sin(  2 * 2 * pi /  128)|
    .xldouble   0.9891765099648 ; | Cos(  3 * 2 * pi /  128)|
    .xldouble   0.1467304744554 ; | Sin(  3 * 2 * pi /  128)|
    .xldouble   0.9807852804032 ; | Cos(  4 * 2 * pi /  128)|
    .xldouble   0.1950903220161 ; | Sin(  4 * 2 * pi /  128)|
    .xldouble   0.9700312531945 ; | Cos(  5 * 2 * pi /  128)|
    .xldouble   0.2429801799033 ; | Sin(  5 * 2 * pi /  128)|
    .xldouble   0.9569403357322 ; | Cos(  6 * 2 * pi /  128)|
    .xldouble   0.2902846772545 ; | Sin(  6 * 2 * pi /  128)|
    .xldouble   0.9415440651830 ; | Cos(  7 * 2 * pi /  128)|
    .xldouble   0.3368898533922 ; | Sin(  7 * 2 * pi /  128)|
    .xldouble   0.9238795325113 ; | Cos(  8 * 2 * pi /  128)|
    .xldouble   0.3826834323651 ; | Sin(  8 * 2 * pi /  128)|
    .xldouble   0.9039892931234 ; | Cos(  9 * 2 * pi /  128)|
    .xldouble   0.4275550934303 ; | Sin(  9 * 2 * pi /  128)|
    .xldouble   0.8819212643484 ; | Cos( 10 * 2 * pi /  128)|
    .xldouble   0.4713967368260 ; | Sin( 10 * 2 * pi /  128)|
    .xldouble   0.8577286100003 ; | Cos( 11 * 2 * pi /  128)|
    .xldouble   0.5141027441932 ; | Sin( 11 * 2 * pi /  128)|
    .xldouble   0.8314696123025 ; | Cos( 12 * 2 * pi /  128)|
    .xldouble   0.5555702330196 ; | Sin( 12 * 2 * pi /  128)|
    .xldouble   0.8032075314806 ; | Cos( 13 * 2 * pi /  128)|
    .xldouble   0.5956993044924 ; | Sin( 13 * 2 * pi /  128)|
    .xldouble   0.7730104533627 ; | Cos( 14 * 2 * pi /  128)|
    .xldouble   0.6343932841636 ; | Sin( 14 * 2 * pi /  128)|
    .xldouble   0.7409511253550 ; | Cos( 15 * 2 * pi /  128)|
    .xldouble   0.6715589548470 ; | Sin( 15 * 2 * pi /  128)|
    .xldouble   0.7071067811865 ; | Cos( 16 * 2 * pi /  128)|
    .xldouble   0.7071067811865 ; | Sin( 16 * 2 * pi /  128)|
    .xldouble   0.6715589548470 ; | Cos( 17 * 2 * pi /  128)|
    .xldouble   0.7409511253550 ; | Sin( 17 * 2 * pi /  128)|
    .xldouble   0.6343932841636 ; | Cos( 18 * 2 * pi /  128)|
    .xldouble   0.7730104533627 ; | Sin( 18 * 2 * pi /  128)|
    .xldouble   0.5956993044924 ; | Cos( 19 * 2 * pi /  128)|
    .xldouble   0.8032075314806 ; | Sin( 19 * 2 * pi /  128)|
    .xldouble   0.5555702330196 ; | Cos( 20 * 2 * pi /  128)|
    .xldouble   0.8314696123025 ; | Sin( 20 * 2 * pi /  128)|
    .xldouble   0.5141027441932 ; | Cos( 21 * 2 * pi /  128)|
    .xldouble   0.8577286100003 ; | Sin( 21 * 2 * pi /  128)|
    .xldouble   0.4713967368260 ; | Cos( 22 * 2 * pi /  128)|
    .xldouble   0.8819212643484 ; | Sin( 22 * 2 * pi /  128)|
    .xldouble   0.4275550934303 ; | Cos( 23 * 2 * pi /  128)|
    .xldouble   0.9039892931234 ; | Sin( 23 * 2 * pi /  128)|
    .xldouble   0.3826834323651 ; | Cos( 24 * 2 * pi /  128)|
    .xldouble   0.9238795325113 ; | Sin( 24 * 2 * pi /  128)|
    .xldouble   0.3368898533922 ; | Cos( 25 * 2 * pi /  128)|
    .xldouble   0.9415440651830 ; | Sin( 25 * 2 * pi /  128)|
    .xldouble   0.2902846772545 ; | Cos( 26 * 2 * pi /  128)|
    .xldouble   0.9569403357322 ; | Sin( 26 * 2 * pi /  128)|
    .xldouble   0.2429801799033 ; | Cos( 27 * 2 * pi /  128)|
    .xldouble   0.9700312531945 ; | Sin( 27 * 2 * pi /  128)|
    .xldouble   0.1950903220161 ; | Cos( 28 * 2 * pi /  128)|
    .xldouble   0.9807852804032 ; | Sin( 28 * 2 * pi /  128)|
    .xldouble   0.1467304744554 ; | Cos( 29 * 2 * pi /  128)|
    .xldouble   0.9891765099648 ; | Sin( 29 * 2 * pi /  128)|
    .xldouble   0.0980171403296 ; | Cos( 30 * 2 * pi /  128)|
    .xldouble   0.9951847266722 ; | Sin( 30 * 2 * pi /  128)|
    .xldouble   0.0490676743274 ; | Cos( 31 * 2 * pi /  128)|
    .xldouble   0.9987954562052 ; | Sin( 31 * 2 * pi /  128)|
    .xldouble   0.0000000000000 ; | Cos( 32 * 2 * pi /  128)|
    .xldouble   1.0000000000000 ; | Sin( 32 * 2 * pi /  128)|
                                ; +---------Stage  8--------+
    .xldouble   0.9996988186962 ; | Cos(  1 * 2 * pi /  256)|
    .xldouble   0.0245412285229 ; | Sin(  1 * 2 * pi /  256)|
    .xldouble   0.9987954562052 ; | Cos(  2 * 2 * pi /  256)|
    .xldouble   0.0490676743274 ; | Sin(  2 * 2 * pi /  256)|
    .xldouble   0.9972904566787 ; | Cos(  3 * 2 * pi /  256)|
    .xldouble   0.0735645635997 ; | Sin(  3 * 2 * pi /  256)|
    .xldouble   0.9951847266722 ; | Cos(  4 * 2 * pi /  256)|
    .xldouble   0.0980171403296 ; | Sin(  4 * 2 * pi /  256)|
    .xldouble   0.9924795345987 ; | Cos(  5 * 2 * pi /  256)|
    .xldouble   0.1224106751992 ; | Sin(  5 * 2 * pi /  256)|
    .xldouble   0.9891765099648 ; | Cos(  6 * 2 * pi /  256)|
    .xldouble   0.1467304744554 ; | Sin(  6 * 2 * pi /  256)|
    .xldouble   0.9852776423889 ; | Cos(  7 * 2 * pi /  256)|
    .xldouble   0.1709618887603 ; | Sin(  7 * 2 * pi /  256)|
    .xldouble   0.9807852804032 ; | Cos(  8 * 2 * pi /  256)|
    .xldouble   0.1950903220161 ; | Sin(  8 * 2 * pi /  256)|
    .xldouble   0.9757021300385 ; | Cos(  9 * 2 * pi /  256)|
    .xldouble   0.2191012401569 ; | Sin(  9 * 2 * pi /  256)|
    .xldouble   0.9700312531945 ; | Cos( 10 * 2 * pi /  256)|
    .xldouble   0.2429801799033 ; | Sin( 10 * 2 * pi /  256)|
    .xldouble   0.9637760657954 ; | Cos( 11 * 2 * pi /  256)|
    .xldouble   0.2667127574749 ; | Sin( 11 * 2 * pi /  256)|
    .xldouble   0.9569403357322 ; | Cos( 12 * 2 * pi /  256)|
    .xldouble   0.2902846772545 ; | Sin( 12 * 2 * pi /  256)|
    .xldouble   0.9495281805930 ; | Cos( 13 * 2 * pi /  256)|
    .xldouble   0.3136817403989 ; | Sin( 13 * 2 * pi /  256)|
    .xldouble   0.9415440651830 ; | Cos( 14 * 2 * pi /  256)|
    .xldouble   0.3368898533922 ; | Sin( 14 * 2 * pi /  256)|
    .xldouble   0.9329927988347 ; | Cos( 15 * 2 * pi /  256)|
    .xldouble   0.3598950365350 ; | Sin( 15 * 2 * pi /  256)|
    .xldouble   0.9238795325113 ; | Cos( 16 * 2 * pi /  256)|
    .xldouble   0.3826834323651 ; | Sin( 16 * 2 * pi /  256)|
    .xldouble   0.9142097557035 ; | Cos( 17 * 2 * pi /  256)|
    .xldouble   0.4052413140050 ; | Sin( 17 * 2 * pi /  256)|
    .xldouble   0.9039892931234 ; | Cos( 18 * 2 * pi /  256)|
    .xldouble   0.4275550934303 ; | Sin( 18 * 2 * pi /  256)|
    .xldouble   0.8932243011955 ; | Cos( 19 * 2 * pi /  256)|
    .xldouble   0.4496113296546 ; | Sin( 19 * 2 * pi /  256)|
    .xldouble   0.8819212643484 ; | Cos( 20 * 2 * pi /  256)|
    .xldouble   0.4713967368260 ; | Sin( 20 * 2 * pi /  256)|
    .xldouble   0.8700869911087 ; | Cos( 21 * 2 * pi /  256)|
    .xldouble   0.4928981922298 ; | Sin( 21 * 2 * pi /  256)|
    .xldouble   0.8577286100003 ; | Cos( 22 * 2 * pi /  256)|
    .xldouble   0.5141027441932 ; | Sin( 22 * 2 * pi /  256)|
    .xldouble   0.8448535652497 ; | Cos( 23 * 2 * pi /  256)|
    .xldouble   0.5349976198871 ; | Sin( 23 * 2 * pi /  256)|
    .xldouble   0.8314696123025 ; | Cos( 24 * 2 * pi /  256)|
    .xldouble   0.5555702330196 ; | Sin( 24 * 2 * pi /  256)|
    .xldouble   0.8175848131516 ; | Cos( 25 * 2 * pi /  256)|
    .xldouble   0.5758081914178 ; | Sin( 25 * 2 * pi /  256)|
    .xldouble   0.8032075314806 ; | Cos( 26 * 2 * pi /  256)|
    .xldouble   0.5956993044924 ; | Sin( 26 * 2 * pi /  256)|
    .xldouble   0.7883464276266 ; | Cos( 27 * 2 * pi /  256)|
    .xldouble   0.6152315905806 ; | Sin( 27 * 2 * pi /  256)|
    .xldouble   0.7730104533627 ; | Cos( 28 * 2 * pi /  256)|
    .xldouble   0.6343932841636 ; | Sin( 28 * 2 * pi /  256)|
    .xldouble   0.7572088465065 ; | Cos( 29 * 2 * pi /  256)|
    .xldouble   0.6531728429538 ; | Sin( 29 * 2 * pi /  256)|
    .xldouble   0.7409511253550 ; | Cos( 30 * 2 * pi /  256)|
    .xldouble   0.6715589548470 ; | Sin( 30 * 2 * pi /  256)|
    .xldouble   0.7242470829515 ; | Cos( 31 * 2 * pi /  256)|
    .xldouble   0.6895405447371 ; | Sin( 31 * 2 * pi /  256)|
    .xldouble   0.7071067811865 ; | Cos( 32 * 2 * pi /  256)|
    .xldouble   0.7071067811865 ; | Sin( 32 * 2 * pi /  256)|
    .xldouble   0.6895405447371 ; | Cos( 33 * 2 * pi /  256)|
    .xldouble   0.7242470829515 ; | Sin( 33 * 2 * pi /  256)|
    .xldouble   0.6715589548470 ; | Cos( 34 * 2 * pi /  256)|
    .xldouble   0.7409511253550 ; | Sin( 34 * 2 * pi /  256)|
    .xldouble   0.6531728429538 ; | Cos( 35 * 2 * pi /  256)|
    .xldouble   0.7572088465065 ; | Sin( 35 * 2 * pi /  256)|
    .xldouble   0.6343932841636 ; | Cos( 36 * 2 * pi /  256)|
    .xldouble   0.7730104533627 ; | Sin( 36 * 2 * pi /  256)|
    .xldouble   0.6152315905806 ; | Cos( 37 * 2 * pi /  256)|
    .xldouble   0.7883464276266 ; | Sin( 37 * 2 * pi /  256)|
    .xldouble   0.5956993044924 ; | Cos( 38 * 2 * pi /  256)|
    .xldouble   0.8032075314806 ; | Sin( 38 * 2 * pi /  256)|
    .xldouble   0.5758081914178 ; | Cos( 39 * 2 * pi /  256)|
    .xldouble   0.8175848131516 ; | Sin( 39 * 2 * pi /  256)|
    .xldouble   0.5555702330196 ; | Cos( 40 * 2 * pi /  256)|
    .xldouble   0.8314696123025 ; | Sin( 40 * 2 * pi /  256)|
    .xldouble   0.5349976198871 ; | Cos( 41 * 2 * pi /  256)|
    .xldouble   0.8448535652497 ; | Sin( 41 * 2 * pi /  256)|
    .xldouble   0.5141027441932 ; | Cos( 42 * 2 * pi /  256)|
    .xldouble   0.8577286100003 ; | Sin( 42 * 2 * pi /  256)|
    .xldouble   0.4928981922298 ; | Cos( 43 * 2 * pi /  256)|
    .xldouble   0.8700869911087 ; | Sin( 43 * 2 * pi /  256)|
    .xldouble   0.4713967368260 ; | Cos( 44 * 2 * pi /  256)|
    .xldouble   0.8819212643484 ; | Sin( 44 * 2 * pi /  256)|
    .xldouble   0.4496113296546 ; | Cos( 45 * 2 * pi /  256)|
    .xldouble   0.8932243011955 ; | Sin( 45 * 2 * pi /  256)|
    .xldouble   0.4275550934303 ; | Cos( 46 * 2 * pi /  256)|
    .xldouble   0.9039892931234 ; | Sin( 46 * 2 * pi /  256)|
    .xldouble   0.4052413140050 ; | Cos( 47 * 2 * pi /  256)|
    .xldouble   0.9142097557035 ; | Sin( 47 * 2 * pi /  256)|
    .xldouble   0.3826834323651 ; | Cos( 48 * 2 * pi /  256)|
    .xldouble   0.9238795325113 ; | Sin( 48 * 2 * pi /  256)|
    .xldouble   0.3598950365350 ; | Cos( 49 * 2 * pi /  256)|
    .xldouble   0.9329927988347 ; | Sin( 49 * 2 * pi /  256)|
    .xldouble   0.3368898533922 ; | Cos( 50 * 2 * pi /  256)|
    .xldouble   0.9415440651830 ; | Sin( 50 * 2 * pi /  256)|
    .xldouble   0.3136817403989 ; | Cos( 51 * 2 * pi /  256)|
    .xldouble   0.9495281805930 ; | Sin( 51 * 2 * pi /  256)|
    .xldouble   0.2902846772545 ; | Cos( 52 * 2 * pi /  256)|
    .xldouble   0.9569403357322 ; | Sin( 52 * 2 * pi /  256)|
    .xldouble   0.2667127574749 ; | Cos( 53 * 2 * pi /  256)|
    .xldouble   0.9637760657954 ; | Sin( 53 * 2 * pi /  256)|
    .xldouble   0.2429801799033 ; | Cos( 54 * 2 * pi /  256)|
    .xldouble   0.9700312531945 ; | Sin( 54 * 2 * pi /  256)|
    .xldouble   0.2191012401569 ; | Cos( 55 * 2 * pi /  256)|
    .xldouble   0.9757021300385 ; | Sin( 55 * 2 * pi /  256)|
    .xldouble   0.1950903220161 ; | Cos( 56 * 2 * pi /  256)|
    .xldouble   0.9807852804032 ; | Sin( 56 * 2 * pi /  256)|
    .xldouble   0.1709618887603 ; | Cos( 57 * 2 * pi /  256)|
    .xldouble   0.9852776423889 ; | Sin( 57 * 2 * pi /  256)|
    .xldouble   0.1467304744554 ; | Cos( 58 * 2 * pi /  256)|
    .xldouble   0.9891765099648 ; | Sin( 58 * 2 * pi /  256)|
    .xldouble   0.1224106751992 ; | Cos( 59 * 2 * pi /  256)|
    .xldouble   0.9924795345987 ; | Sin( 59 * 2 * pi /  256)|
    .xldouble   0.0980171403296 ; | Cos( 60 * 2 * pi /  256)|
    .xldouble   0.9951847266722 ; | Sin( 60 * 2 * pi /  256)|
    .xldouble   0.0735645635997 ; | Cos( 61 * 2 * pi /  256)|
    .xldouble   0.9972904566787 ; | Sin( 61 * 2 * pi /  256)|
    .xldouble   0.0490676743274 ; | Cos( 62 * 2 * pi /  256)|
    .xldouble   0.9987954562052 ; | Sin( 62 * 2 * pi /  256)|
    .xldouble   0.0245412285229 ; | Cos( 63 * 2 * pi /  256)|
    .xldouble   0.9996988186962 ; | Sin( 63 * 2 * pi /  256)|
    .xldouble   0.0000000000000 ; | Cos( 64 * 2 * pi /  256)|
    .xldouble   1.0000000000000 ; | Sin( 64 * 2 * pi /  256)|
                                ; +---------Stage  9--------+
    .xldouble   0.9999247018391 ; | Cos(  1 * 2 * pi /  512)|
    .xldouble   0.0122715382857 ; | Sin(  1 * 2 * pi /  512)|
    .xldouble   0.9996988186962 ; | Cos(  2 * 2 * pi /  512)|
    .xldouble   0.0245412285229 ; | Sin(  2 * 2 * pi /  512)|
    .xldouble   0.9993223845883 ; | Cos(  3 * 2 * pi /  512)|
    .xldouble   0.0368072229414 ; | Sin(  3 * 2 * pi /  512)|
    .xldouble   0.9987954562052 ; | Cos(  4 * 2 * pi /  512)|
    .xldouble   0.0490676743274 ; | Sin(  4 * 2 * pi /  512)|
    .xldouble   0.9981181129001 ; | Cos(  5 * 2 * pi /  512)|
    .xldouble   0.0613207363022 ; | Sin(  5 * 2 * pi /  512)|
    .xldouble   0.9972904566787 ; | Cos(  6 * 2 * pi /  512)|
    .xldouble   0.0735645635997 ; | Sin(  6 * 2 * pi /  512)|
    .xldouble   0.9963126121828 ; | Cos(  7 * 2 * pi /  512)|
    .xldouble   0.0857973123444 ; | Sin(  7 * 2 * pi /  512)|
    .xldouble   0.9951847266722 ; | Cos(  8 * 2 * pi /  512)|
    .xldouble   0.0980171403296 ; | Sin(  8 * 2 * pi /  512)|
    .xldouble   0.9939069700024 ; | Cos(  9 * 2 * pi /  512)|
    .xldouble   0.1102222072939 ; | Sin(  9 * 2 * pi /  512)|
    .xldouble   0.9924795345987 ; | Cos( 10 * 2 * pi /  512)|
    .xldouble   0.1224106751992 ; | Sin( 10 * 2 * pi /  512)|
    .xldouble   0.9909026354278 ; | Cos( 11 * 2 * pi /  512)|
    .xldouble   0.1345807085071 ; | Sin( 11 * 2 * pi /  512)|
    .xldouble   0.9891765099648 ; | Cos( 12 * 2 * pi /  512)|
    .xldouble   0.1467304744554 ; | Sin( 12 * 2 * pi /  512)|
    .xldouble   0.9873014181579 ; | Cos( 13 * 2 * pi /  512)|
    .xldouble   0.1588581433339 ; | Sin( 13 * 2 * pi /  512)|
    .xldouble   0.9852776423889 ; | Cos( 14 * 2 * pi /  512)|
    .xldouble   0.1709618887603 ; | Sin( 14 * 2 * pi /  512)|
    .xldouble   0.9831054874312 ; | Cos( 15 * 2 * pi /  512)|
    .xldouble   0.1830398879551 ; | Sin( 15 * 2 * pi /  512)|
    .xldouble   0.9807852804032 ; | Cos( 16 * 2 * pi /  512)|
    .xldouble   0.1950903220161 ; | Sin( 16 * 2 * pi /  512)|
    .xldouble   0.9783173707196 ; | Cos( 17 * 2 * pi /  512)|
    .xldouble   0.2071113761922 ; | Sin( 17 * 2 * pi /  512)|
    .xldouble   0.9757021300385 ; | Cos( 18 * 2 * pi /  512)|
    .xldouble   0.2191012401569 ; | Sin( 18 * 2 * pi /  512)|
    .xldouble   0.9729399522056 ; | Cos( 19 * 2 * pi /  512)|
    .xldouble   0.2310581082807 ; | Sin( 19 * 2 * pi /  512)|
    .xldouble   0.9700312531945 ; | Cos( 20 * 2 * pi /  512)|
    .xldouble   0.2429801799033 ; | Sin( 20 * 2 * pi /  512)|
    .xldouble   0.9669764710449 ; | Cos( 21 * 2 * pi /  512)|
    .xldouble   0.2548656596045 ; | Sin( 21 * 2 * pi /  512)|
    .xldouble   0.9637760657954 ; | Cos( 22 * 2 * pi /  512)|
    .xldouble   0.2667127574749 ; | Sin( 22 * 2 * pi /  512)|
    .xldouble   0.9604305194156 ; | Cos( 23 * 2 * pi /  512)|
    .xldouble   0.2785196893851 ; | Sin( 23 * 2 * pi /  512)|
    .xldouble   0.9569403357322 ; | Cos( 24 * 2 * pi /  512)|
    .xldouble   0.2902846772545 ; | Sin( 24 * 2 * pi /  512)|
    .xldouble   0.9533060403542 ; | Cos( 25 * 2 * pi /  512)|
    .xldouble   0.3020059493192 ; | Sin( 25 * 2 * pi /  512)|
    .xldouble   0.9495281805930 ; | Cos( 26 * 2 * pi /  512)|
    .xldouble   0.3136817403989 ; | Sin( 26 * 2 * pi /  512)|
    .xldouble   0.9456073253805 ; | Cos( 27 * 2 * pi /  512)|
    .xldouble   0.3253102921623 ; | Sin( 27 * 2 * pi /  512)|
    .xldouble   0.9415440651830 ; | Cos( 28 * 2 * pi /  512)|
    .xldouble   0.3368898533922 ; | Sin( 28 * 2 * pi /  512)|
    .xldouble   0.9373390119126 ; | Cos( 29 * 2 * pi /  512)|
    .xldouble   0.3484186802494 ; | Sin( 29 * 2 * pi /  512)|
    .xldouble   0.9329927988347 ; | Cos( 30 * 2 * pi /  512)|
    .xldouble   0.3598950365350 ; | Sin( 30 * 2 * pi /  512)|
    .xldouble   0.9285060804732 ; | Cos( 31 * 2 * pi /  512)|
    .xldouble   0.3713171939518 ; | Sin( 31 * 2 * pi /  512)|
    .xldouble   0.9238795325113 ; | Cos( 32 * 2 * pi /  512)|
    .xldouble   0.3826834323651 ; | Sin( 32 * 2 * pi /  512)|
    .xldouble   0.9191138516901 ; | Cos( 33 * 2 * pi /  512)|
    .xldouble   0.3939920400610 ; | Sin( 33 * 2 * pi /  512)|
    .xldouble   0.9142097557035 ; | Cos( 34 * 2 * pi /  512)|
    .xldouble   0.4052413140050 ; | Sin( 34 * 2 * pi /  512)|
    .xldouble   0.9091679830905 ; | Cos( 35 * 2 * pi /  512)|
    .xldouble   0.4164295600976 ; | Sin( 35 * 2 * pi /  512)|
    .xldouble   0.9039892931234 ; | Cos( 36 * 2 * pi /  512)|
    .xldouble   0.4275550934303 ; | Sin( 36 * 2 * pi /  512)|
    .xldouble   0.8986744656940 ; | Cos( 37 * 2 * pi /  512)|
    .xldouble   0.4386162385385 ; | Sin( 37 * 2 * pi /  512)|
    .xldouble   0.8932243011955 ; | Cos( 38 * 2 * pi /  512)|
    .xldouble   0.4496113296546 ; | Sin( 38 * 2 * pi /  512)|
    .xldouble   0.8876396204029 ; | Cos( 39 * 2 * pi /  512)|
    .xldouble   0.4605387109582 ; | Sin( 39 * 2 * pi /  512)|
    .xldouble   0.8819212643484 ; | Cos( 40 * 2 * pi /  512)|
    .xldouble   0.4713967368260 ; | Sin( 40 * 2 * pi /  512)|
    .xldouble   0.8760700941954 ; | Cos( 41 * 2 * pi /  512)|
    .xldouble   0.4821837720791 ; | Sin( 41 * 2 * pi /  512)|
    .xldouble   0.8700869911087 ; | Cos( 42 * 2 * pi /  512)|
    .xldouble   0.4928981922298 ; | Sin( 42 * 2 * pi /  512)|
    .xldouble   0.8639728561216 ; | Cos( 43 * 2 * pi /  512)|
    .xldouble   0.5035383837257 ; | Sin( 43 * 2 * pi /  512)|
    .xldouble   0.8577286100003 ; | Cos( 44 * 2 * pi /  512)|
    .xldouble   0.5141027441932 ; | Sin( 44 * 2 * pi /  512)|
    .xldouble   0.8513551931053 ; | Cos( 45 * 2 * pi /  512)|
    .xldouble   0.5245896826785 ; | Sin( 45 * 2 * pi /  512)|
    .xldouble   0.8448535652497 ; | Cos( 46 * 2 * pi /  512)|
    .xldouble   0.5349976198871 ; | Sin( 46 * 2 * pi /  512)|
    .xldouble   0.8382247055548 ; | Cos( 47 * 2 * pi /  512)|
    .xldouble   0.5453249884220 ; | Sin( 47 * 2 * pi /  512)|
    .xldouble   0.8314696123025 ; | Cos( 48 * 2 * pi /  512)|
    .xldouble   0.5555702330196 ; | Sin( 48 * 2 * pi /  512)|
    .xldouble   0.8245893027850 ; | Cos( 49 * 2 * pi /  512)|
    .xldouble   0.5657318107836 ; | Sin( 49 * 2 * pi /  512)|
    .xldouble   0.8175848131516 ; | Cos( 50 * 2 * pi /  512)|
    .xldouble   0.5758081914178 ; | Sin( 50 * 2 * pi /  512)|
    .xldouble   0.8104571982526 ; | Cos( 51 * 2 * pi /  512)|
    .xldouble   0.5857978574564 ; | Sin( 51 * 2 * pi /  512)|
    .xldouble   0.8032075314806 ; | Cos( 52 * 2 * pi /  512)|
    .xldouble   0.5956993044924 ; | Sin( 52 * 2 * pi /  512)|
    .xldouble   0.7958369046089 ; | Cos( 53 * 2 * pi /  512)|
    .xldouble   0.6055110414043 ; | Sin( 53 * 2 * pi /  512)|
    .xldouble   0.7883464276266 ; | Cos( 54 * 2 * pi /  512)|
    .xldouble   0.6152315905806 ; | Sin( 54 * 2 * pi /  512)|
    .xldouble   0.7807372285721 ; | Cos( 55 * 2 * pi /  512)|
    .xldouble   0.6248594881424 ; | Sin( 55 * 2 * pi /  512)|
    .xldouble   0.7730104533627 ; | Cos( 56 * 2 * pi /  512)|
    .xldouble   0.6343932841636 ; | Sin( 56 * 2 * pi /  512)|
    .xldouble   0.7651672656225 ; | Cos( 57 * 2 * pi /  512)|
    .xldouble   0.6438315428898 ; | Sin( 57 * 2 * pi /  512)|
    .xldouble   0.7572088465065 ; | Cos( 58 * 2 * pi /  512)|
    .xldouble   0.6531728429538 ; | Sin( 58 * 2 * pi /  512)|
    .xldouble   0.7491363945235 ; | Cos( 59 * 2 * pi /  512)|
    .xldouble   0.6624157775902 ; | Sin( 59 * 2 * pi /  512)|
    .xldouble   0.7409511253550 ; | Cos( 60 * 2 * pi /  512)|
    .xldouble   0.6715589548470 ; | Sin( 60 * 2 * pi /  512)|
    .xldouble   0.7326542716724 ; | Cos( 61 * 2 * pi /  512)|
    .xldouble   0.6806009977955 ; | Sin( 61 * 2 * pi /  512)|
    .xldouble   0.7242470829515 ; | Cos( 62 * 2 * pi /  512)|
    .xldouble   0.6895405447371 ; | Sin( 62 * 2 * pi /  512)|
    .xldouble   0.7157308252838 ; | Cos( 63 * 2 * pi /  512)|
    .xldouble   0.6983762494090 ; | Sin( 63 * 2 * pi /  512)|
    .xldouble   0.7071067811865 ; | Cos( 64 * 2 * pi /  512)|
    .xldouble   0.7071067811865 ; | Sin( 64 * 2 * pi /  512)|
    .xldouble   0.6983762494090 ; | Cos( 65 * 2 * pi /  512)|
    .xldouble   0.7157308252838 ; | Sin( 65 * 2 * pi /  512)|
    .xldouble   0.6895405447371 ; | Cos( 66 * 2 * pi /  512)|
    .xldouble   0.7242470829515 ; | Sin( 66 * 2 * pi /  512)|
    .xldouble   0.6806009977955 ; | Cos( 67 * 2 * pi /  512)|
    .xldouble   0.7326542716724 ; | Sin( 67 * 2 * pi /  512)|
    .xldouble   0.6715589548470 ; | Cos( 68 * 2 * pi /  512)|
    .xldouble   0.7409511253550 ; | Sin( 68 * 2 * pi /  512)|
    .xldouble   0.6624157775902 ; | Cos( 69 * 2 * pi /  512)|
    .xldouble   0.7491363945235 ; | Sin( 69 * 2 * pi /  512)|
    .xldouble   0.6531728429538 ; | Cos( 70 * 2 * pi /  512)|
    .xldouble   0.7572088465065 ; | Sin( 70 * 2 * pi /  512)|
    .xldouble   0.6438315428898 ; | Cos( 71 * 2 * pi /  512)|
    .xldouble   0.7651672656225 ; | Sin( 71 * 2 * pi /  512)|
    .xldouble   0.6343932841636 ; | Cos( 72 * 2 * pi /  512)|
    .xldouble   0.7730104533627 ; | Sin( 72 * 2 * pi /  512)|
    .xldouble   0.6248594881424 ; | Cos( 73 * 2 * pi /  512)|
    .xldouble   0.7807372285721 ; | Sin( 73 * 2 * pi /  512)|
    .xldouble   0.6152315905806 ; | Cos( 74 * 2 * pi /  512)|
    .xldouble   0.7883464276266 ; | Sin( 74 * 2 * pi /  512)|
    .xldouble   0.6055110414043 ; | Cos( 75 * 2 * pi /  512)|
    .xldouble   0.7958369046089 ; | Sin( 75 * 2 * pi /  512)|
    .xldouble   0.5956993044924 ; | Cos( 76 * 2 * pi /  512)|
    .xldouble   0.8032075314806 ; | Sin( 76 * 2 * pi /  512)|
    .xldouble   0.5857978574564 ; | Cos( 77 * 2 * pi /  512)|
    .xldouble   0.8104571982526 ; | Sin( 77 * 2 * pi /  512)|
    .xldouble   0.5758081914178 ; | Cos( 78 * 2 * pi /  512)|
    .xldouble   0.8175848131516 ; | Sin( 78 * 2 * pi /  512)|
    .xldouble   0.5657318107836 ; | Cos( 79 * 2 * pi /  512)|
    .xldouble   0.8245893027850 ; | Sin( 79 * 2 * pi /  512)|
    .xldouble   0.5555702330196 ; | Cos( 80 * 2 * pi /  512)|
    .xldouble   0.8314696123025 ; | Sin( 80 * 2 * pi /  512)|
    .xldouble   0.5453249884220 ; | Cos( 81 * 2 * pi /  512)|
    .xldouble   0.8382247055548 ; | Sin( 81 * 2 * pi /  512)|
    .xldouble   0.5349976198871 ; | Cos( 82 * 2 * pi /  512)|
    .xldouble   0.8448535652497 ; | Sin( 82 * 2 * pi /  512)|
    .xldouble   0.5245896826785 ; | Cos( 83 * 2 * pi /  512)|
    .xldouble   0.8513551931053 ; | Sin( 83 * 2 * pi /  512)|
    .xldouble   0.5141027441932 ; | Cos( 84 * 2 * pi /  512)|
    .xldouble   0.8577286100003 ; | Sin( 84 * 2 * pi /  512)|
    .xldouble   0.5035383837257 ; | Cos( 85 * 2 * pi /  512)|
    .xldouble   0.8639728561216 ; | Sin( 85 * 2 * pi /  512)|
    .xldouble   0.4928981922298 ; | Cos( 86 * 2 * pi /  512)|
    .xldouble   0.8700869911087 ; | Sin( 86 * 2 * pi /  512)|
    .xldouble   0.4821837720791 ; | Cos( 87 * 2 * pi /  512)|
    .xldouble   0.8760700941954 ; | Sin( 87 * 2 * pi /  512)|
    .xldouble   0.4713967368260 ; | Cos( 88 * 2 * pi /  512)|
    .xldouble   0.8819212643484 ; | Sin( 88 * 2 * pi /  512)|
    .xldouble   0.4605387109582 ; | Cos( 89 * 2 * pi /  512)|
    .xldouble   0.8876396204029 ; | Sin( 89 * 2 * pi /  512)|
    .xldouble   0.4496113296546 ; | Cos( 90 * 2 * pi /  512)|
    .xldouble   0.8932243011955 ; | Sin( 90 * 2 * pi /  512)|
    .xldouble   0.4386162385385 ; | Cos( 91 * 2 * pi /  512)|
    .xldouble   0.8986744656940 ; | Sin( 91 * 2 * pi /  512)|
    .xldouble   0.4275550934303 ; | Cos( 92 * 2 * pi /  512)|
    .xldouble   0.9039892931234 ; | Sin( 92 * 2 * pi /  512)|
    .xldouble   0.4164295600976 ; | Cos( 93 * 2 * pi /  512)|
    .xldouble   0.9091679830905 ; | Sin( 93 * 2 * pi /  512)|
    .xldouble   0.4052413140050 ; | Cos( 94 * 2 * pi /  512)|
    .xldouble   0.9142097557035 ; | Sin( 94 * 2 * pi /  512)|
    .xldouble   0.3939920400610 ; | Cos( 95 * 2 * pi /  512)|
    .xldouble   0.9191138516901 ; | Sin( 95 * 2 * pi /  512)|
    .xldouble   0.3826834323651 ; | Cos( 96 * 2 * pi /  512)|
    .xldouble   0.9238795325113 ; | Sin( 96 * 2 * pi /  512)|
    .xldouble   0.3713171939518 ; | Cos( 97 * 2 * pi /  512)|
    .xldouble   0.9285060804732 ; | Sin( 97 * 2 * pi /  512)|
    .xldouble   0.3598950365350 ; | Cos( 98 * 2 * pi /  512)|
    .xldouble   0.9329927988347 ; | Sin( 98 * 2 * pi /  512)|
    .xldouble   0.3484186802494 ; | Cos( 99 * 2 * pi /  512)|
    .xldouble   0.9373390119126 ; | Sin( 99 * 2 * pi /  512)|
    .xldouble   0.3368898533922 ; | Cos(100 * 2 * pi /  512)|
    .xldouble   0.9415440651830 ; | Sin(100 * 2 * pi /  512)|
    .xldouble   0.3253102921623 ; | Cos(101 * 2 * pi /  512)|
    .xldouble   0.9456073253805 ; | Sin(101 * 2 * pi /  512)|
    .xldouble   0.3136817403989 ; | Cos(102 * 2 * pi /  512)|
    .xldouble   0.9495281805930 ; | Sin(102 * 2 * pi /  512)|
    .xldouble   0.3020059493192 ; | Cos(103 * 2 * pi /  512)|
    .xldouble   0.9533060403542 ; | Sin(103 * 2 * pi /  512)|
    .xldouble   0.2902846772545 ; | Cos(104 * 2 * pi /  512)|
    .xldouble   0.9569403357322 ; | Sin(104 * 2 * pi /  512)|
    .xldouble   0.2785196893851 ; | Cos(105 * 2 * pi /  512)|
    .xldouble   0.9604305194156 ; | Sin(105 * 2 * pi /  512)|
    .xldouble   0.2667127574749 ; | Cos(106 * 2 * pi /  512)|
    .xldouble   0.9637760657954 ; | Sin(106 * 2 * pi /  512)|
    .xldouble   0.2548656596045 ; | Cos(107 * 2 * pi /  512)|
    .xldouble   0.9669764710449 ; | Sin(107 * 2 * pi /  512)|
    .xldouble   0.2429801799033 ; | Cos(108 * 2 * pi /  512)|
    .xldouble   0.9700312531945 ; | Sin(108 * 2 * pi /  512)|
    .xldouble   0.2310581082807 ; | Cos(109 * 2 * pi /  512)|
    .xldouble   0.9729399522056 ; | Sin(109 * 2 * pi /  512)|
    .xldouble   0.2191012401569 ; | Cos(110 * 2 * pi /  512)|
    .xldouble   0.9757021300385 ; | Sin(110 * 2 * pi /  512)|
    .xldouble   0.2071113761922 ; | Cos(111 * 2 * pi /  512)|
    .xldouble   0.9783173707196 ; | Sin(111 * 2 * pi /  512)|
    .xldouble   0.1950903220161 ; | Cos(112 * 2 * pi /  512)|
    .xldouble   0.9807852804032 ; | Sin(112 * 2 * pi /  512)|
    .xldouble   0.1830398879551 ; | Cos(113 * 2 * pi /  512)|
    .xldouble   0.9831054874312 ; | Sin(113 * 2 * pi /  512)|
    .xldouble   0.1709618887603 ; | Cos(114 * 2 * pi /  512)|
    .xldouble   0.9852776423889 ; | Sin(114 * 2 * pi /  512)|
    .xldouble   0.1588581433339 ; | Cos(115 * 2 * pi /  512)|
    .xldouble   0.9873014181579 ; | Sin(115 * 2 * pi /  512)|
    .xldouble   0.1467304744554 ; | Cos(116 * 2 * pi /  512)|
    .xldouble   0.9891765099648 ; | Sin(116 * 2 * pi /  512)|
    .xldouble   0.1345807085071 ; | Cos(117 * 2 * pi /  512)|
    .xldouble   0.9909026354278 ; | Sin(117 * 2 * pi /  512)|
    .xldouble   0.1224106751992 ; | Cos(118 * 2 * pi /  512)|
    .xldouble   0.9924795345987 ; | Sin(118 * 2 * pi /  512)|
    .xldouble   0.1102222072939 ; | Cos(119 * 2 * pi /  512)|
    .xldouble   0.9939069700024 ; | Sin(119 * 2 * pi /  512)|
    .xldouble   0.0980171403296 ; | Cos(120 * 2 * pi /  512)|
    .xldouble   0.9951847266722 ; | Sin(120 * 2 * pi /  512)|
    .xldouble   0.0857973123444 ; | Cos(121 * 2 * pi /  512)|
    .xldouble   0.9963126121828 ; | Sin(121 * 2 * pi /  512)|
    .xldouble   0.0735645635997 ; | Cos(122 * 2 * pi /  512)|
    .xldouble   0.9972904566787 ; | Sin(122 * 2 * pi /  512)|
    .xldouble   0.0613207363022 ; | Cos(123 * 2 * pi /  512)|
    .xldouble   0.9981181129001 ; | Sin(123 * 2 * pi /  512)|
    .xldouble   0.0490676743274 ; | Cos(124 * 2 * pi /  512)|
    .xldouble   0.9987954562052 ; | Sin(124 * 2 * pi /  512)|
    .xldouble   0.0368072229414 ; | Cos(125 * 2 * pi /  512)|
    .xldouble   0.9993223845883 ; | Sin(125 * 2 * pi /  512)|
    .xldouble   0.0245412285229 ; | Cos(126 * 2 * pi /  512)|
    .xldouble   0.9996988186962 ; | Sin(126 * 2 * pi /  512)|
    .xldouble   0.0122715382857 ; | Cos(127 * 2 * pi /  512)|
    .xldouble   0.9999247018391 ; | Sin(127 * 2 * pi /  512)|
    .xldouble   0.0000000000000 ; | Cos(128 * 2 * pi /  512)|
    .xldouble   1.0000000000000 ; | Sin(128 * 2 * pi /  512)|
                                ; +---------Stage 10--------+
    .xldouble   0.9999811752826 ; | Cos(  1 * 2 * pi / 1024)|
    .xldouble   0.0061358846492 ; | Sin(  1 * 2 * pi / 1024)|
    .xldouble   0.9999247018391 ; | Cos(  2 * 2 * pi / 1024)|
    .xldouble   0.0122715382857 ; | Sin(  2 * 2 * pi / 1024)|
    .xldouble   0.9998305817958 ; | Cos(  3 * 2 * pi / 1024)|
    .xldouble   0.0184067299058 ; | Sin(  3 * 2 * pi / 1024)|
    .xldouble   0.9996988186962 ; | Cos(  4 * 2 * pi / 1024)|
    .xldouble   0.0245412285229 ; | Sin(  4 * 2 * pi / 1024)|
    .xldouble   0.9995294175011 ; | Cos(  5 * 2 * pi / 1024)|
    .xldouble   0.0306748031766 ; | Sin(  5 * 2 * pi / 1024)|
    .xldouble   0.9993223845883 ; | Cos(  6 * 2 * pi / 1024)|
    .xldouble   0.0368072229414 ; | Sin(  6 * 2 * pi / 1024)|
    .xldouble   0.9990777277526 ; | Cos(  7 * 2 * pi / 1024)|
    .xldouble   0.0429382569349 ; | Sin(  7 * 2 * pi / 1024)|
    .xldouble   0.9987954562052 ; | Cos(  8 * 2 * pi / 1024)|
    .xldouble   0.0490676743274 ; | Sin(  8 * 2 * pi / 1024)|
    .xldouble   0.9984755805733 ; | Cos(  9 * 2 * pi / 1024)|
    .xldouble   0.0551952443497 ; | Sin(  9 * 2 * pi / 1024)|
    .xldouble   0.9981181129001 ; | Cos( 10 * 2 * pi / 1024)|
    .xldouble   0.0613207363022 ; | Sin( 10 * 2 * pi / 1024)|
    .xldouble   0.9977230666442 ; | Cos( 11 * 2 * pi / 1024)|
    .xldouble   0.0674439195637 ; | Sin( 11 * 2 * pi / 1024)|
    .xldouble   0.9972904566787 ; | Cos( 12 * 2 * pi / 1024)|
    .xldouble   0.0735645635997 ; | Sin( 12 * 2 * pi / 1024)|
    .xldouble   0.9968202992912 ; | Cos( 13 * 2 * pi / 1024)|
    .xldouble   0.0796824379714 ; | Sin( 13 * 2 * pi / 1024)|
    .xldouble   0.9963126121828 ; | Cos( 14 * 2 * pi / 1024)|
    .xldouble   0.0857973123444 ; | Sin( 14 * 2 * pi / 1024)|
    .xldouble   0.9957674144677 ; | Cos( 15 * 2 * pi / 1024)|
    .xldouble   0.0919089564971 ; | Sin( 15 * 2 * pi / 1024)|
    .xldouble   0.9951847266722 ; | Cos( 16 * 2 * pi / 1024)|
    .xldouble   0.0980171403296 ; | Sin( 16 * 2 * pi / 1024)|
    .xldouble   0.9945645707343 ; | Cos( 17 * 2 * pi / 1024)|
    .xldouble   0.1041216338721 ; | Sin( 17 * 2 * pi / 1024)|
    .xldouble   0.9939069700024 ; | Cos( 18 * 2 * pi / 1024)|
    .xldouble   0.1102222072939 ; | Sin( 18 * 2 * pi / 1024)|
    .xldouble   0.9932119492348 ; | Cos( 19 * 2 * pi / 1024)|
    .xldouble   0.1163186309119 ; | Sin( 19 * 2 * pi / 1024)|
    .xldouble   0.9924795345987 ; | Cos( 20 * 2 * pi / 1024)|
    .xldouble   0.1224106751992 ; | Sin( 20 * 2 * pi / 1024)|
    .xldouble   0.9917097536691 ; | Cos( 21 * 2 * pi / 1024)|
    .xldouble   0.1284981107938 ; | Sin( 21 * 2 * pi / 1024)|
    .xldouble   0.9909026354278 ; | Cos( 22 * 2 * pi / 1024)|
    .xldouble   0.1345807085071 ; | Sin( 22 * 2 * pi / 1024)|
    .xldouble   0.9900582102623 ; | Cos( 23 * 2 * pi / 1024)|
    .xldouble   0.1406582393328 ; | Sin( 23 * 2 * pi / 1024)|
    .xldouble   0.9891765099648 ; | Cos( 24 * 2 * pi / 1024)|
    .xldouble   0.1467304744554 ; | Sin( 24 * 2 * pi / 1024)|
    .xldouble   0.9882575677307 ; | Cos( 25 * 2 * pi / 1024)|
    .xldouble   0.1527971852584 ; | Sin( 25 * 2 * pi / 1024)|
    .xldouble   0.9873014181579 ; | Cos( 26 * 2 * pi / 1024)|
    .xldouble   0.1588581433339 ; | Sin( 26 * 2 * pi / 1024)|
    .xldouble   0.9863080972446 ; | Cos( 27 * 2 * pi / 1024)|
    .xldouble   0.1649131204900 ; | Sin( 27 * 2 * pi / 1024)|
    .xldouble   0.9852776423889 ; | Cos( 28 * 2 * pi / 1024)|
    .xldouble   0.1709618887603 ; | Sin( 28 * 2 * pi / 1024)|
    .xldouble   0.9842100923869 ; | Cos( 29 * 2 * pi / 1024)|
    .xldouble   0.1770042204121 ; | Sin( 29 * 2 * pi / 1024)|
    .xldouble   0.9831054874312 ; | Cos( 30 * 2 * pi / 1024)|
    .xldouble   0.1830398879551 ; | Sin( 30 * 2 * pi / 1024)|
    .xldouble   0.9819638691096 ; | Cos( 31 * 2 * pi / 1024)|
    .xldouble   0.1890686641498 ; | Sin( 31 * 2 * pi / 1024)|
    .xldouble   0.9807852804032 ; | Cos( 32 * 2 * pi / 1024)|
    .xldouble   0.1950903220161 ; | Sin( 32 * 2 * pi / 1024)|
    .xldouble   0.9795697656854 ; | Cos( 33 * 2 * pi / 1024)|
    .xldouble   0.2011046348421 ; | Sin( 33 * 2 * pi / 1024)|
    .xldouble   0.9783173707196 ; | Cos( 34 * 2 * pi / 1024)|
    .xldouble   0.2071113761922 ; | Sin( 34 * 2 * pi / 1024)|
    .xldouble   0.9770281426578 ; | Cos( 35 * 2 * pi / 1024)|
    .xldouble   0.2131103199161 ; | Sin( 35 * 2 * pi / 1024)|
    .xldouble   0.9757021300385 ; | Cos( 36 * 2 * pi / 1024)|
    .xldouble   0.2191012401569 ; | Sin( 36 * 2 * pi / 1024)|
    .xldouble   0.9743393827856 ; | Cos( 37 * 2 * pi / 1024)|
    .xldouble   0.2250839113598 ; | Sin( 37 * 2 * pi / 1024)|
    .xldouble   0.9729399522056 ; | Cos( 38 * 2 * pi / 1024)|
    .xldouble   0.2310581082807 ; | Sin( 38 * 2 * pi / 1024)|
    .xldouble   0.9715038909863 ; | Cos( 39 * 2 * pi / 1024)|
    .xldouble   0.2370236059944 ; | Sin( 39 * 2 * pi / 1024)|
    .xldouble   0.9700312531945 ; | Cos( 40 * 2 * pi / 1024)|
    .xldouble   0.2429801799033 ; | Sin( 40 * 2 * pi / 1024)|
    .xldouble   0.9685220942744 ; | Cos( 41 * 2 * pi / 1024)|
    .xldouble   0.2489276057457 ; | Sin( 41 * 2 * pi / 1024)|
    .xldouble   0.9669764710449 ; | Cos( 42 * 2 * pi / 1024)|
    .xldouble   0.2548656596045 ; | Sin( 42 * 2 * pi / 1024)|
    .xldouble   0.9653944416977 ; | Cos( 43 * 2 * pi / 1024)|
    .xldouble   0.2607941179153 ; | Sin( 43 * 2 * pi / 1024)|
    .xldouble   0.9637760657954 ; | Cos( 44 * 2 * pi / 1024)|
    .xldouble   0.2667127574749 ; | Sin( 44 * 2 * pi / 1024)|
    .xldouble   0.9621214042690 ; | Cos( 45 * 2 * pi / 1024)|
    .xldouble   0.2726213554499 ; | Sin( 45 * 2 * pi / 1024)|
    .xldouble   0.9604305194156 ; | Cos( 46 * 2 * pi / 1024)|
    .xldouble   0.2785196893851 ; | Sin( 46 * 2 * pi / 1024)|
    .xldouble   0.9587034748959 ; | Cos( 47 * 2 * pi / 1024)|
    .xldouble   0.2844075372113 ; | Sin( 47 * 2 * pi / 1024)|
    .xldouble   0.9569403357322 ; | Cos( 48 * 2 * pi / 1024)|
    .xldouble   0.2902846772545 ; | Sin( 48 * 2 * pi / 1024)|
    .xldouble   0.9551411683058 ; | Cos( 49 * 2 * pi / 1024)|
    .xldouble   0.2961508882436 ; | Sin( 49 * 2 * pi / 1024)|
    .xldouble   0.9533060403542 ; | Cos( 50 * 2 * pi / 1024)|
    .xldouble   0.3020059493192 ; | Sin( 50 * 2 * pi / 1024)|
    .xldouble   0.9514350209690 ; | Cos( 51 * 2 * pi / 1024)|
    .xldouble   0.3078496400415 ; | Sin( 51 * 2 * pi / 1024)|
    .xldouble   0.9495281805930 ; | Cos( 52 * 2 * pi / 1024)|
    .xldouble   0.3136817403989 ; | Sin( 52 * 2 * pi / 1024)|
    .xldouble   0.9475855910177 ; | Cos( 53 * 2 * pi / 1024)|
    .xldouble   0.3195020308160 ; | Sin( 53 * 2 * pi / 1024)|
    .xldouble   0.9456073253805 ; | Cos( 54 * 2 * pi / 1024)|
    .xldouble   0.3253102921623 ; | Sin( 54 * 2 * pi / 1024)|
    .xldouble   0.9435934581620 ; | Cos( 55 * 2 * pi / 1024)|
    .xldouble   0.3311063057599 ; | Sin( 55 * 2 * pi / 1024)|
    .xldouble   0.9415440651830 ; | Cos( 56 * 2 * pi / 1024)|
    .xldouble   0.3368898533922 ; | Sin( 56 * 2 * pi / 1024)|
    .xldouble   0.9394592236022 ; | Cos( 57 * 2 * pi / 1024)|
    .xldouble   0.3426607173120 ; | Sin( 57 * 2 * pi / 1024)|
    .xldouble   0.9373390119126 ; | Cos( 58 * 2 * pi / 1024)|
    .xldouble   0.3484186802494 ; | Sin( 58 * 2 * pi / 1024)|
    .xldouble   0.9351835099389 ; | Cos( 59 * 2 * pi / 1024)|
    .xldouble   0.3541635254205 ; | Sin( 59 * 2 * pi / 1024)|
    .xldouble   0.9329927988347 ; | Cos( 60 * 2 * pi / 1024)|
    .xldouble   0.3598950365350 ; | Sin( 60 * 2 * pi / 1024)|
    .xldouble   0.9307669610790 ; | Cos( 61 * 2 * pi / 1024)|
    .xldouble   0.3656129978048 ; | Sin( 61 * 2 * pi / 1024)|
    .xldouble   0.9285060804732 ; | Cos( 62 * 2 * pi / 1024)|
    .xldouble   0.3713171939518 ; | Sin( 62 * 2 * pi / 1024)|
    .xldouble   0.9262102421383 ; | Cos( 63 * 2 * pi / 1024)|
    .xldouble   0.3770074102164 ; | Sin( 63 * 2 * pi / 1024)|
    .xldouble   0.9238795325113 ; | Cos( 64 * 2 * pi / 1024)|
    .xldouble   0.3826834323651 ; | Sin( 64 * 2 * pi / 1024)|
    .xldouble   0.9215140393420 ; | Cos( 65 * 2 * pi / 1024)|
    .xldouble   0.3883450466988 ; | Sin( 65 * 2 * pi / 1024)|
    .xldouble   0.9191138516901 ; | Cos( 66 * 2 * pi / 1024)|
    .xldouble   0.3939920400610 ; | Sin( 66 * 2 * pi / 1024)|
    .xldouble   0.9166790599210 ; | Cos( 67 * 2 * pi / 1024)|
    .xldouble   0.3996241998456 ; | Sin( 67 * 2 * pi / 1024)|
    .xldouble   0.9142097557035 ; | Cos( 68 * 2 * pi / 1024)|
    .xldouble   0.4052413140050 ; | Sin( 68 * 2 * pi / 1024)|
    .xldouble   0.9117060320054 ; | Cos( 69 * 2 * pi / 1024)|
    .xldouble   0.4108431710579 ; | Sin( 69 * 2 * pi / 1024)|
    .xldouble   0.9091679830905 ; | Cos( 70 * 2 * pi / 1024)|
    .xldouble   0.4164295600976 ; | Sin( 70 * 2 * pi / 1024)|
    .xldouble   0.9065957045149 ; | Cos( 71 * 2 * pi / 1024)|
    .xldouble   0.4220002707998 ; | Sin( 71 * 2 * pi / 1024)|
    .xldouble   0.9039892931234 ; | Cos( 72 * 2 * pi / 1024)|
    .xldouble   0.4275550934303 ; | Sin( 72 * 2 * pi / 1024)|
    .xldouble   0.9013488470460 ; | Cos( 73 * 2 * pi / 1024)|
    .xldouble   0.4330938188532 ; | Sin( 73 * 2 * pi / 1024)|
    .xldouble   0.8986744656940 ; | Cos( 74 * 2 * pi / 1024)|
    .xldouble   0.4386162385385 ; | Sin( 74 * 2 * pi / 1024)|
    .xldouble   0.8959662497562 ; | Cos( 75 * 2 * pi / 1024)|
    .xldouble   0.4441221445704 ; | Sin( 75 * 2 * pi / 1024)|
    .xldouble   0.8932243011955 ; | Cos( 76 * 2 * pi / 1024)|
    .xldouble   0.4496113296546 ; | Sin( 76 * 2 * pi / 1024)|
    .xldouble   0.8904487232448 ; | Cos( 77 * 2 * pi / 1024)|
    .xldouble   0.4550835871263 ; | Sin( 77 * 2 * pi / 1024)|
    .xldouble   0.8876396204029 ; | Cos( 78 * 2 * pi / 1024)|
    .xldouble   0.4605387109582 ; | Sin( 78 * 2 * pi / 1024)|
    .xldouble   0.8847970984309 ; | Cos( 79 * 2 * pi / 1024)|
    .xldouble   0.4659764957680 ; | Sin( 79 * 2 * pi / 1024)|
    .xldouble   0.8819212643484 ; | Cos( 80 * 2 * pi / 1024)|
    .xldouble   0.4713967368260 ; | Sin( 80 * 2 * pi / 1024)|
    .xldouble   0.8790122264286 ; | Cos( 81 * 2 * pi / 1024)|
    .xldouble   0.4767992300633 ; | Sin( 81 * 2 * pi / 1024)|
    .xldouble   0.8760700941954 ; | Cos( 82 * 2 * pi / 1024)|
    .xldouble   0.4821837720791 ; | Sin( 82 * 2 * pi / 1024)|
    .xldouble   0.8730949784183 ; | Cos( 83 * 2 * pi / 1024)|
    .xldouble   0.4875501601484 ; | Sin( 83 * 2 * pi / 1024)|
    .xldouble   0.8700869911087 ; | Cos( 84 * 2 * pi / 1024)|
    .xldouble   0.4928981922298 ; | Sin( 84 * 2 * pi / 1024)|
    .xldouble   0.8670462455157 ; | Cos( 85 * 2 * pi / 1024)|
    .xldouble   0.4982276669728 ; | Sin( 85 * 2 * pi / 1024)|
    .xldouble   0.8639728561216 ; | Cos( 86 * 2 * pi / 1024)|
    .xldouble   0.5035383837257 ; | Sin( 86 * 2 * pi / 1024)|
    .xldouble   0.8608669386378 ; | Cos( 87 * 2 * pi / 1024)|
    .xldouble   0.5088301425431 ; | Sin( 87 * 2 * pi / 1024)|
    .xldouble   0.8577286100003 ; | Cos( 88 * 2 * pi / 1024)|
    .xldouble   0.5141027441932 ; | Sin( 88 * 2 * pi / 1024)|
    .xldouble   0.8545579883654 ; | Cos( 89 * 2 * pi / 1024)|
    .xldouble   0.5193559901656 ; | Sin( 89 * 2 * pi / 1024)|
    .xldouble   0.8513551931053 ; | Cos( 90 * 2 * pi / 1024)|
    .xldouble   0.5245896826785 ; | Sin( 90 * 2 * pi / 1024)|
    .xldouble   0.8481203448033 ; | Cos( 91 * 2 * pi / 1024)|
    .xldouble   0.5298036246863 ; | Sin( 91 * 2 * pi / 1024)|
    .xldouble   0.8448535652497 ; | Cos( 92 * 2 * pi / 1024)|
    .xldouble   0.5349976198871 ; | Sin( 92 * 2 * pi / 1024)|
    .xldouble   0.8415549774369 ; | Cos( 93 * 2 * pi / 1024)|
    .xldouble   0.5401714727299 ; | Sin( 93 * 2 * pi / 1024)|
    .xldouble   0.8382247055548 ; | Cos( 94 * 2 * pi / 1024)|
    .xldouble   0.5453249884220 ; | Sin( 94 * 2 * pi / 1024)|
    .xldouble   0.8348628749864 ; | Cos( 95 * 2 * pi / 1024)|
    .xldouble   0.5504579729366 ; | Sin( 95 * 2 * pi / 1024)|
    .xldouble   0.8314696123025 ; | Cos( 96 * 2 * pi / 1024)|
    .xldouble   0.5555702330196 ; | Sin( 96 * 2 * pi / 1024)|
    .xldouble   0.8280450452578 ; | Cos( 97 * 2 * pi / 1024)|
    .xldouble   0.5606615761973 ; | Sin( 97 * 2 * pi / 1024)|
    .xldouble   0.8245893027850 ; | Cos( 98 * 2 * pi / 1024)|
    .xldouble   0.5657318107836 ; | Sin( 98 * 2 * pi / 1024)|
    .xldouble   0.8211025149911 ; | Cos( 99 * 2 * pi / 1024)|
    .xldouble   0.5707807458870 ; | Sin( 99 * 2 * pi / 1024)|
    .xldouble   0.8175848131516 ; | Cos(100 * 2 * pi / 1024)|
    .xldouble   0.5758081914178 ; | Sin(100 * 2 * pi / 1024)|
    .xldouble   0.8140363297059 ; | Cos(101 * 2 * pi / 1024)|
    .xldouble   0.5808139580958 ; | Sin(101 * 2 * pi / 1024)|
    .xldouble   0.8104571982526 ; | Cos(102 * 2 * pi / 1024)|
    .xldouble   0.5857978574564 ; | Sin(102 * 2 * pi / 1024)|
    .xldouble   0.8068475535438 ; | Cos(103 * 2 * pi / 1024)|
    .xldouble   0.5907597018589 ; | Sin(103 * 2 * pi / 1024)|
    .xldouble   0.8032075314806 ; | Cos(104 * 2 * pi / 1024)|
    .xldouble   0.5956993044924 ; | Sin(104 * 2 * pi / 1024)|
    .xldouble   0.7995372691079 ; | Cos(105 * 2 * pi / 1024)|
    .xldouble   0.6006164793839 ; | Sin(105 * 2 * pi / 1024)|
    .xldouble   0.7958369046089 ; | Cos(106 * 2 * pi / 1024)|
    .xldouble   0.6055110414043 ; | Sin(106 * 2 * pi / 1024)|
    .xldouble   0.7921065773002 ; | Cos(107 * 2 * pi / 1024)|
    .xldouble   0.6103828062763 ; | Sin(107 * 2 * pi / 1024)|
    .xldouble   0.7883464276266 ; | Cos(108 * 2 * pi / 1024)|
    .xldouble   0.6152315905806 ; | Sin(108 * 2 * pi / 1024)|
    .xldouble   0.7845565971556 ; | Cos(109 * 2 * pi / 1024)|
    .xldouble   0.6200572117633 ; | Sin(109 * 2 * pi / 1024)|
    .xldouble   0.7807372285721 ; | Cos(110 * 2 * pi / 1024)|
    .xldouble   0.6248594881424 ; | Sin(110 * 2 * pi / 1024)|
    .xldouble   0.7768884656732 ; | Cos(111 * 2 * pi / 1024)|
    .xldouble   0.6296382389149 ; | Sin(111 * 2 * pi / 1024)|
    .xldouble   0.7730104533627 ; | Cos(112 * 2 * pi / 1024)|
    .xldouble   0.6343932841636 ; | Sin(112 * 2 * pi / 1024)|
    .xldouble   0.7691033376456 ; | Cos(113 * 2 * pi / 1024)|
    .xldouble   0.6391244448638 ; | Sin(113 * 2 * pi / 1024)|
    .xldouble   0.7651672656225 ; | Cos(114 * 2 * pi / 1024)|
    .xldouble   0.6438315428898 ; | Sin(114 * 2 * pi / 1024)|
    .xldouble   0.7612023854843 ; | Cos(115 * 2 * pi / 1024)|
    .xldouble   0.6485144010221 ; | Sin(115 * 2 * pi / 1024)|
    .xldouble   0.7572088465065 ; | Cos(116 * 2 * pi / 1024)|
    .xldouble   0.6531728429538 ; | Sin(116 * 2 * pi / 1024)|
    .xldouble   0.7531867990436 ; | Cos(117 * 2 * pi / 1024)|
    .xldouble   0.6578066932971 ; | Sin(117 * 2 * pi / 1024)|
    .xldouble   0.7491363945235 ; | Cos(118 * 2 * pi / 1024)|
    .xldouble   0.6624157775902 ; | Sin(118 * 2 * pi / 1024)|
    .xldouble   0.7450577854415 ; | Cos(119 * 2 * pi / 1024)|
    .xldouble   0.6669999223036 ; | Sin(119 * 2 * pi / 1024)|
    .xldouble   0.7409511253550 ; | Cos(120 * 2 * pi / 1024)|
    .xldouble   0.6715589548470 ; | Sin(120 * 2 * pi / 1024)|
    .xldouble   0.7368165688774 ; | Cos(121 * 2 * pi / 1024)|
    .xldouble   0.6760927035753 ; | Sin(121 * 2 * pi / 1024)|
    .xldouble   0.7326542716724 ; | Cos(122 * 2 * pi / 1024)|
    .xldouble   0.6806009977955 ; | Sin(122 * 2 * pi / 1024)|
    .xldouble   0.7284643904482 ; | Cos(123 * 2 * pi / 1024)|
    .xldouble   0.6850836677727 ; | Sin(123 * 2 * pi / 1024)|
    .xldouble   0.7242470829515 ; | Cos(124 * 2 * pi / 1024)|
    .xldouble   0.6895405447371 ; | Sin(124 * 2 * pi / 1024)|
    .xldouble   0.7200025079614 ; | Cos(125 * 2 * pi / 1024)|
    .xldouble   0.6939714608897 ; | Sin(125 * 2 * pi / 1024)|
    .xldouble   0.7157308252838 ; | Cos(126 * 2 * pi / 1024)|
    .xldouble   0.6983762494090 ; | Sin(126 * 2 * pi / 1024)|
    .xldouble   0.7114321957452 ; | Cos(127 * 2 * pi / 1024)|
    .xldouble   0.7027547444572 ; | Sin(127 * 2 * pi / 1024)|
    .xldouble   0.7071067811865 ; | Cos(128 * 2 * pi / 1024)|
    .xldouble   0.7071067811865 ; | Sin(128 * 2 * pi / 1024)|
    .xldouble   0.7027547444572 ; | Cos(129 * 2 * pi / 1024)|
    .xldouble   0.7114321957452 ; | Sin(129 * 2 * pi / 1024)|
    .xldouble   0.6983762494090 ; | Cos(130 * 2 * pi / 1024)|
    .xldouble   0.7157308252838 ; | Sin(130 * 2 * pi / 1024)|
    .xldouble   0.6939714608897 ; | Cos(131 * 2 * pi / 1024)|
    .xldouble   0.7200025079614 ; | Sin(131 * 2 * pi / 1024)|
    .xldouble   0.6895405447371 ; | Cos(132 * 2 * pi / 1024)|
    .xldouble   0.7242470829515 ; | Sin(132 * 2 * pi / 1024)|
    .xldouble   0.6850836677727 ; | Cos(133 * 2 * pi / 1024)|
    .xldouble   0.7284643904482 ; | Sin(133 * 2 * pi / 1024)|
    .xldouble   0.6806009977955 ; | Cos(134 * 2 * pi / 1024)|
    .xldouble   0.7326542716724 ; | Sin(134 * 2 * pi / 1024)|
    .xldouble   0.6760927035753 ; | Cos(135 * 2 * pi / 1024)|
    .xldouble   0.7368165688774 ; | Sin(135 * 2 * pi / 1024)|
    .xldouble   0.6715589548470 ; | Cos(136 * 2 * pi / 1024)|
    .xldouble   0.7409511253550 ; | Sin(136 * 2 * pi / 1024)|
    .xldouble   0.6669999223036 ; | Cos(137 * 2 * pi / 1024)|
    .xldouble   0.7450577854415 ; | Sin(137 * 2 * pi / 1024)|
    .xldouble   0.6624157775902 ; | Cos(138 * 2 * pi / 1024)|
    .xldouble   0.7491363945235 ; | Sin(138 * 2 * pi / 1024)|
    .xldouble   0.6578066932971 ; | Cos(139 * 2 * pi / 1024)|
    .xldouble   0.7531867990436 ; | Sin(139 * 2 * pi / 1024)|
    .xldouble   0.6531728429538 ; | Cos(140 * 2 * pi / 1024)|
    .xldouble   0.7572088465065 ; | Sin(140 * 2 * pi / 1024)|
    .xldouble   0.6485144010221 ; | Cos(141 * 2 * pi / 1024)|
    .xldouble   0.7612023854843 ; | Sin(141 * 2 * pi / 1024)|
    .xldouble   0.6438315428898 ; | Cos(142 * 2 * pi / 1024)|
    .xldouble   0.7651672656225 ; | Sin(142 * 2 * pi / 1024)|
    .xldouble   0.6391244448638 ; | Cos(143 * 2 * pi / 1024)|
    .xldouble   0.7691033376456 ; | Sin(143 * 2 * pi / 1024)|
    .xldouble   0.6343932841636 ; | Cos(144 * 2 * pi / 1024)|
    .xldouble   0.7730104533627 ; | Sin(144 * 2 * pi / 1024)|
    .xldouble   0.6296382389149 ; | Cos(145 * 2 * pi / 1024)|
    .xldouble   0.7768884656732 ; | Sin(145 * 2 * pi / 1024)|
    .xldouble   0.6248594881424 ; | Cos(146 * 2 * pi / 1024)|
    .xldouble   0.7807372285721 ; | Sin(146 * 2 * pi / 1024)|
    .xldouble   0.6200572117633 ; | Cos(147 * 2 * pi / 1024)|
    .xldouble   0.7845565971556 ; | Sin(147 * 2 * pi / 1024)|
    .xldouble   0.6152315905806 ; | Cos(148 * 2 * pi / 1024)|
    .xldouble   0.7883464276266 ; | Sin(148 * 2 * pi / 1024)|
    .xldouble   0.6103828062763 ; | Cos(149 * 2 * pi / 1024)|
    .xldouble   0.7921065773002 ; | Sin(149 * 2 * pi / 1024)|
    .xldouble   0.6055110414043 ; | Cos(150 * 2 * pi / 1024)|
    .xldouble   0.7958369046089 ; | Sin(150 * 2 * pi / 1024)|
    .xldouble   0.6006164793839 ; | Cos(151 * 2 * pi / 1024)|
    .xldouble   0.7995372691079 ; | Sin(151 * 2 * pi / 1024)|
    .xldouble   0.5956993044924 ; | Cos(152 * 2 * pi / 1024)|
    .xldouble   0.8032075314806 ; | Sin(152 * 2 * pi / 1024)|
    .xldouble   0.5907597018589 ; | Cos(153 * 2 * pi / 1024)|
    .xldouble   0.8068475535438 ; | Sin(153 * 2 * pi / 1024)|
    .xldouble   0.5857978574564 ; | Cos(154 * 2 * pi / 1024)|
    .xldouble   0.8104571982526 ; | Sin(154 * 2 * pi / 1024)|
    .xldouble   0.5808139580958 ; | Cos(155 * 2 * pi / 1024)|
    .xldouble   0.8140363297059 ; | Sin(155 * 2 * pi / 1024)|
    .xldouble   0.5758081914178 ; | Cos(156 * 2 * pi / 1024)|
    .xldouble   0.8175848131516 ; | Sin(156 * 2 * pi / 1024)|
    .xldouble   0.5707807458870 ; | Cos(157 * 2 * pi / 1024)|
    .xldouble   0.8211025149911 ; | Sin(157 * 2 * pi / 1024)|
    .xldouble   0.5657318107836 ; | Cos(158 * 2 * pi / 1024)|
    .xldouble   0.8245893027850 ; | Sin(158 * 2 * pi / 1024)|
    .xldouble   0.5606615761973 ; | Cos(159 * 2 * pi / 1024)|
    .xldouble   0.8280450452578 ; | Sin(159 * 2 * pi / 1024)|
    .xldouble   0.5555702330196 ; | Cos(160 * 2 * pi / 1024)|
    .xldouble   0.8314696123025 ; | Sin(160 * 2 * pi / 1024)|
    .xldouble   0.5504579729366 ; | Cos(161 * 2 * pi / 1024)|
    .xldouble   0.8348628749864 ; | Sin(161 * 2 * pi / 1024)|
    .xldouble   0.5453249884220 ; | Cos(162 * 2 * pi / 1024)|
    .xldouble   0.8382247055548 ; | Sin(162 * 2 * pi / 1024)|
    .xldouble   0.5401714727299 ; | Cos(163 * 2 * pi / 1024)|
    .xldouble   0.8415549774369 ; | Sin(163 * 2 * pi / 1024)|
    .xldouble   0.5349976198871 ; | Cos(164 * 2 * pi / 1024)|
    .xldouble   0.8448535652497 ; | Sin(164 * 2 * pi / 1024)|
    .xldouble   0.5298036246863 ; | Cos(165 * 2 * pi / 1024)|
    .xldouble   0.8481203448033 ; | Sin(165 * 2 * pi / 1024)|
    .xldouble   0.5245896826785 ; | Cos(166 * 2 * pi / 1024)|
    .xldouble   0.8513551931053 ; | Sin(166 * 2 * pi / 1024)|
    .xldouble   0.5193559901656 ; | Cos(167 * 2 * pi / 1024)|
    .xldouble   0.8545579883654 ; | Sin(167 * 2 * pi / 1024)|
    .xldouble   0.5141027441932 ; | Cos(168 * 2 * pi / 1024)|
    .xldouble   0.8577286100003 ; | Sin(168 * 2 * pi / 1024)|
    .xldouble   0.5088301425431 ; | Cos(169 * 2 * pi / 1024)|
    .xldouble   0.8608669386378 ; | Sin(169 * 2 * pi / 1024)|
    .xldouble   0.5035383837257 ; | Cos(170 * 2 * pi / 1024)|
    .xldouble   0.8639728561216 ; | Sin(170 * 2 * pi / 1024)|
    .xldouble   0.4982276669728 ; | Cos(171 * 2 * pi / 1024)|
    .xldouble   0.8670462455157 ; | Sin(171 * 2 * pi / 1024)|
    .xldouble   0.4928981922298 ; | Cos(172 * 2 * pi / 1024)|
    .xldouble   0.8700869911087 ; | Sin(172 * 2 * pi / 1024)|
    .xldouble   0.4875501601484 ; | Cos(173 * 2 * pi / 1024)|
    .xldouble   0.8730949784183 ; | Sin(173 * 2 * pi / 1024)|
    .xldouble   0.4821837720791 ; | Cos(174 * 2 * pi / 1024)|
    .xldouble   0.8760700941954 ; | Sin(174 * 2 * pi / 1024)|
    .xldouble   0.4767992300633 ; | Cos(175 * 2 * pi / 1024)|
    .xldouble   0.8790122264286 ; | Sin(175 * 2 * pi / 1024)|
    .xldouble   0.4713967368260 ; | Cos(176 * 2 * pi / 1024)|
    .xldouble   0.8819212643484 ; | Sin(176 * 2 * pi / 1024)|
    .xldouble   0.4659764957680 ; | Cos(177 * 2 * pi / 1024)|
    .xldouble   0.8847970984309 ; | Sin(177 * 2 * pi / 1024)|
    .xldouble   0.4605387109582 ; | Cos(178 * 2 * pi / 1024)|
    .xldouble   0.8876396204029 ; | Sin(178 * 2 * pi / 1024)|
    .xldouble   0.4550835871263 ; | Cos(179 * 2 * pi / 1024)|
    .xldouble   0.8904487232448 ; | Sin(179 * 2 * pi / 1024)|
    .xldouble   0.4496113296546 ; | Cos(180 * 2 * pi / 1024)|
    .xldouble   0.8932243011955 ; | Sin(180 * 2 * pi / 1024)|
    .xldouble   0.4441221445704 ; | Cos(181 * 2 * pi / 1024)|
    .xldouble   0.8959662497562 ; | Sin(181 * 2 * pi / 1024)|
    .xldouble   0.4386162385385 ; | Cos(182 * 2 * pi / 1024)|
    .xldouble   0.8986744656940 ; | Sin(182 * 2 * pi / 1024)|
    .xldouble   0.4330938188532 ; | Cos(183 * 2 * pi / 1024)|
    .xldouble   0.9013488470460 ; | Sin(183 * 2 * pi / 1024)|
    .xldouble   0.4275550934303 ; | Cos(184 * 2 * pi / 1024)|
    .xldouble   0.9039892931234 ; | Sin(184 * 2 * pi / 1024)|
    .xldouble   0.4220002707998 ; | Cos(185 * 2 * pi / 1024)|
    .xldouble   0.9065957045149 ; | Sin(185 * 2 * pi / 1024)|
    .xldouble   0.4164295600976 ; | Cos(186 * 2 * pi / 1024)|
    .xldouble   0.9091679830905 ; | Sin(186 * 2 * pi / 1024)|
    .xldouble   0.4108431710579 ; | Cos(187 * 2 * pi / 1024)|
    .xldouble   0.9117060320054 ; | Sin(187 * 2 * pi / 1024)|
    .xldouble   0.4052413140050 ; | Cos(188 * 2 * pi / 1024)|
    .xldouble   0.9142097557035 ; | Sin(188 * 2 * pi / 1024)|
    .xldouble   0.3996241998456 ; | Cos(189 * 2 * pi / 1024)|
    .xldouble   0.9166790599210 ; | Sin(189 * 2 * pi / 1024)|
    .xldouble   0.3939920400610 ; | Cos(190 * 2 * pi / 1024)|
    .xldouble   0.9191138516901 ; | Sin(190 * 2 * pi / 1024)|
    .xldouble   0.3883450466988 ; | Cos(191 * 2 * pi / 1024)|
    .xldouble   0.9215140393420 ; | Sin(191 * 2 * pi / 1024)|
    .xldouble   0.3826834323651 ; | Cos(192 * 2 * pi / 1024)|
    .xldouble   0.9238795325113 ; | Sin(192 * 2 * pi / 1024)|
    .xldouble   0.3770074102164 ; | Cos(193 * 2 * pi / 1024)|
    .xldouble   0.9262102421383 ; | Sin(193 * 2 * pi / 1024)|
    .xldouble   0.3713171939518 ; | Cos(194 * 2 * pi / 1024)|
    .xldouble   0.9285060804732 ; | Sin(194 * 2 * pi / 1024)|
    .xldouble   0.3656129978048 ; | Cos(195 * 2 * pi / 1024)|
    .xldouble   0.9307669610790 ; | Sin(195 * 2 * pi / 1024)|
    .xldouble   0.3598950365350 ; | Cos(196 * 2 * pi / 1024)|
    .xldouble   0.9329927988347 ; | Sin(196 * 2 * pi / 1024)|
    .xldouble   0.3541635254205 ; | Cos(197 * 2 * pi / 1024)|
    .xldouble   0.9351835099389 ; | Sin(197 * 2 * pi / 1024)|
    .xldouble   0.3484186802494 ; | Cos(198 * 2 * pi / 1024)|
    .xldouble   0.9373390119126 ; | Sin(198 * 2 * pi / 1024)|
    .xldouble   0.3426607173120 ; | Cos(199 * 2 * pi / 1024)|
    .xldouble   0.9394592236022 ; | Sin(199 * 2 * pi / 1024)|
    .xldouble   0.3368898533922 ; | Cos(200 * 2 * pi / 1024)|
    .xldouble   0.9415440651830 ; | Sin(200 * 2 * pi / 1024)|
    .xldouble   0.3311063057599 ; | Cos(201 * 2 * pi / 1024)|
    .xldouble   0.9435934581620 ; | Sin(201 * 2 * pi / 1024)|
    .xldouble   0.3253102921623 ; | Cos(202 * 2 * pi / 1024)|
    .xldouble   0.9456073253805 ; | Sin(202 * 2 * pi / 1024)|
    .xldouble   0.3195020308160 ; | Cos(203 * 2 * pi / 1024)|
    .xldouble   0.9475855910177 ; | Sin(203 * 2 * pi / 1024)|
    .xldouble   0.3136817403989 ; | Cos(204 * 2 * pi / 1024)|
    .xldouble   0.9495281805930 ; | Sin(204 * 2 * pi / 1024)|
    .xldouble   0.3078496400415 ; | Cos(205 * 2 * pi / 1024)|
    .xldouble   0.9514350209690 ; | Sin(205 * 2 * pi / 1024)|
    .xldouble   0.3020059493192 ; | Cos(206 * 2 * pi / 1024)|
    .xldouble   0.9533060403542 ; | Sin(206 * 2 * pi / 1024)|
    .xldouble   0.2961508882436 ; | Cos(207 * 2 * pi / 1024)|
    .xldouble   0.9551411683058 ; | Sin(207 * 2 * pi / 1024)|
    .xldouble   0.2902846772545 ; | Cos(208 * 2 * pi / 1024)|
    .xldouble   0.9569403357322 ; | Sin(208 * 2 * pi / 1024)|
    .xldouble   0.2844075372113 ; | Cos(209 * 2 * pi / 1024)|
    .xldouble   0.9587034748959 ; | Sin(209 * 2 * pi / 1024)|
    .xldouble   0.2785196893851 ; | Cos(210 * 2 * pi / 1024)|
    .xldouble   0.9604305194156 ; | Sin(210 * 2 * pi / 1024)|
    .xldouble   0.2726213554499 ; | Cos(211 * 2 * pi / 1024)|
    .xldouble   0.9621214042690 ; | Sin(211 * 2 * pi / 1024)|
    .xldouble   0.2667127574749 ; | Cos(212 * 2 * pi / 1024)|
    .xldouble   0.9637760657954 ; | Sin(212 * 2 * pi / 1024)|
    .xldouble   0.2607941179153 ; | Cos(213 * 2 * pi / 1024)|
    .xldouble   0.9653944416977 ; | Sin(213 * 2 * pi / 1024)|
    .xldouble   0.2548656596045 ; | Cos(214 * 2 * pi / 1024)|
    .xldouble   0.9669764710449 ; | Sin(214 * 2 * pi / 1024)|
    .xldouble   0.2489276057457 ; | Cos(215 * 2 * pi / 1024)|
    .xldouble   0.9685220942744 ; | Sin(215 * 2 * pi / 1024)|
    .xldouble   0.2429801799033 ; | Cos(216 * 2 * pi / 1024)|
    .xldouble   0.9700312531945 ; | Sin(216 * 2 * pi / 1024)|
    .xldouble   0.2370236059944 ; | Cos(217 * 2 * pi / 1024)|
    .xldouble   0.9715038909863 ; | Sin(217 * 2 * pi / 1024)|
    .xldouble   0.2310581082807 ; | Cos(218 * 2 * pi / 1024)|
    .xldouble   0.9729399522056 ; | Sin(218 * 2 * pi / 1024)|
    .xldouble   0.2250839113598 ; | Cos(219 * 2 * pi / 1024)|
    .xldouble   0.9743393827856 ; | Sin(219 * 2 * pi / 1024)|
    .xldouble   0.2191012401569 ; | Cos(220 * 2 * pi / 1024)|
    .xldouble   0.9757021300385 ; | Sin(220 * 2 * pi / 1024)|
    .xldouble   0.2131103199161 ; | Cos(221 * 2 * pi / 1024)|
    .xldouble   0.9770281426578 ; | Sin(221 * 2 * pi / 1024)|
    .xldouble   0.2071113761922 ; | Cos(222 * 2 * pi / 1024)|
    .xldouble   0.9783173707196 ; | Sin(222 * 2 * pi / 1024)|
    .xldouble   0.2011046348421 ; | Cos(223 * 2 * pi / 1024)|
    .xldouble   0.9795697656854 ; | Sin(223 * 2 * pi / 1024)|
    .xldouble   0.1950903220161 ; | Cos(224 * 2 * pi / 1024)|
    .xldouble   0.9807852804032 ; | Sin(224 * 2 * pi / 1024)|
    .xldouble   0.1890686641498 ; | Cos(225 * 2 * pi / 1024)|
    .xldouble   0.9819638691096 ; | Sin(225 * 2 * pi / 1024)|
    .xldouble   0.1830398879551 ; | Cos(226 * 2 * pi / 1024)|
    .xldouble   0.9831054874312 ; | Sin(226 * 2 * pi / 1024)|
    .xldouble   0.1770042204121 ; | Cos(227 * 2 * pi / 1024)|
    .xldouble   0.9842100923869 ; | Sin(227 * 2 * pi / 1024)|
    .xldouble   0.1709618887603 ; | Cos(228 * 2 * pi / 1024)|
    .xldouble   0.9852776423889 ; | Sin(228 * 2 * pi / 1024)|
    .xldouble   0.1649131204900 ; | Cos(229 * 2 * pi / 1024)|
    .xldouble   0.9863080972446 ; | Sin(229 * 2 * pi / 1024)|
    .xldouble   0.1588581433339 ; | Cos(230 * 2 * pi / 1024)|
    .xldouble   0.9873014181579 ; | Sin(230 * 2 * pi / 1024)|
    .xldouble   0.1527971852584 ; | Cos(231 * 2 * pi / 1024)|
    .xldouble   0.9882575677307 ; | Sin(231 * 2 * pi / 1024)|
    .xldouble   0.1467304744554 ; | Cos(232 * 2 * pi / 1024)|
    .xldouble   0.9891765099648 ; | Sin(232 * 2 * pi / 1024)|
    .xldouble   0.1406582393328 ; | Cos(233 * 2 * pi / 1024)|
    .xldouble   0.9900582102623 ; | Sin(233 * 2 * pi / 1024)|
    .xldouble   0.1345807085071 ; | Cos(234 * 2 * pi / 1024)|
    .xldouble   0.9909026354278 ; | Sin(234 * 2 * pi / 1024)|
    .xldouble   0.1284981107938 ; | Cos(235 * 2 * pi / 1024)|
    .xldouble   0.9917097536691 ; | Sin(235 * 2 * pi / 1024)|
    .xldouble   0.1224106751992 ; | Cos(236 * 2 * pi / 1024)|
    .xldouble   0.9924795345987 ; | Sin(236 * 2 * pi / 1024)|
    .xldouble   0.1163186309119 ; | Cos(237 * 2 * pi / 1024)|
    .xldouble   0.9932119492348 ; | Sin(237 * 2 * pi / 1024)|
    .xldouble   0.1102222072939 ; | Cos(238 * 2 * pi / 1024)|
    .xldouble   0.9939069700024 ; | Sin(238 * 2 * pi / 1024)|
    .xldouble   0.1041216338721 ; | Cos(239 * 2 * pi / 1024)|
    .xldouble   0.9945645707343 ; | Sin(239 * 2 * pi / 1024)|
    .xldouble   0.0980171403296 ; | Cos(240 * 2 * pi / 1024)|
    .xldouble   0.9951847266722 ; | Sin(240 * 2 * pi / 1024)|
    .xldouble   0.0919089564971 ; | Cos(241 * 2 * pi / 1024)|
    .xldouble   0.9957674144677 ; | Sin(241 * 2 * pi / 1024)|
    .xldouble   0.0857973123444 ; | Cos(242 * 2 * pi / 1024)|
    .xldouble   0.9963126121828 ; | Sin(242 * 2 * pi / 1024)|
    .xldouble   0.0796824379714 ; | Cos(243 * 2 * pi / 1024)|
    .xldouble   0.9968202992912 ; | Sin(243 * 2 * pi / 1024)|
    .xldouble   0.0735645635997 ; | Cos(244 * 2 * pi / 1024)|
    .xldouble   0.9972904566787 ; | Sin(244 * 2 * pi / 1024)|
    .xldouble   0.0674439195637 ; | Cos(245 * 2 * pi / 1024)|
    .xldouble   0.9977230666442 ; | Sin(245 * 2 * pi / 1024)|
    .xldouble   0.0613207363022 ; | Cos(246 * 2 * pi / 1024)|
    .xldouble   0.9981181129001 ; | Sin(246 * 2 * pi / 1024)|
    .xldouble   0.0551952443497 ; | Cos(247 * 2 * pi / 1024)|
    .xldouble   0.9984755805733 ; | Sin(247 * 2 * pi / 1024)|
    .xldouble   0.0490676743274 ; | Cos(248 * 2 * pi / 1024)|
    .xldouble   0.9987954562052 ; | Sin(248 * 2 * pi / 1024)|
    .xldouble   0.0429382569349 ; | Cos(249 * 2 * pi / 1024)|
    .xldouble   0.9990777277526 ; | Sin(249 * 2 * pi / 1024)|
    .xldouble   0.0368072229414 ; | Cos(250 * 2 * pi / 1024)|
    .xldouble   0.9993223845883 ; | Sin(250 * 2 * pi / 1024)|
    .xldouble   0.0306748031766 ; | Cos(251 * 2 * pi / 1024)|
    .xldouble   0.9995294175011 ; | Sin(251 * 2 * pi / 1024)|
    .xldouble   0.0245412285229 ; | Cos(252 * 2 * pi / 1024)|
    .xldouble   0.9996988186962 ; | Sin(252 * 2 * pi / 1024)|
    .xldouble   0.0184067299058 ; | Cos(253 * 2 * pi / 1024)|
    .xldouble   0.9998305817958 ; | Sin(253 * 2 * pi / 1024)|
    .xldouble   0.0122715382857 ; | Cos(254 * 2 * pi / 1024)|
    .xldouble   0.9999247018391 ; | Sin(254 * 2 * pi / 1024)|
    .xldouble   0.0061358846492 ; | Cos(255 * 2 * pi / 1024)|
    .xldouble   0.9999811752826 ; | Sin(255 * 2 * pi / 1024)|
    .xldouble   0.0000000000000 ; | Cos(256 * 2 * pi / 1024)|
    .xldouble   1.0000000000000 ; | Sin(256 * 2 * pi / 1024)|
                                ; +-------------------------+
_FPU64RFFTtwiddleFactorsEnd:


;; End of File
