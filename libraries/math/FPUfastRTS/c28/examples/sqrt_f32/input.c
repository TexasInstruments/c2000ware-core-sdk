//#############################################################################
//! \file input.c
//! \brief  Square Root Input Vector (512) 
//! \author Vishal Coelho 
//! \date   21-Sep-2016
//! 
//
//  Group:          C2000
//  Target Family:  $DEVICE$
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

#include "fastrts.h"

const float32_t test_input[512] = {
    2.718281828459e+00F, 2.719108607414e+00F, 2.719935386370e+00F, 
    2.720762165325e+00F, 2.721588944280e+00F, 2.722415723236e+00F, 
    2.723242502191e+00F, 2.724069281146e+00F, 2.724896060102e+00F, 
    2.725722839057e+00F, 2.726549618012e+00F, 2.727376396968e+00F, 
    2.728203175923e+00F, 2.729029954878e+00F, 2.729856733834e+00F, 
    2.730683512789e+00F, 2.731510291744e+00F, 2.732337070700e+00F, 
    2.733163849655e+00F, 2.733990628610e+00F, 2.734817407566e+00F, 
    2.735644186521e+00F, 2.736470965476e+00F, 2.737297744432e+00F, 
    2.738124523387e+00F, 2.738951302342e+00F, 2.739778081298e+00F, 
    2.740604860253e+00F, 2.741431639208e+00F, 2.742258418164e+00F, 
    2.743085197119e+00F, 2.743911976074e+00F, 2.744738755030e+00F, 
    2.745565533985e+00F, 2.746392312940e+00F, 2.747219091896e+00F, 
    2.748045870851e+00F, 2.748872649806e+00F, 2.749699428762e+00F, 
    2.750526207717e+00F, 2.751352986672e+00F, 2.752179765628e+00F, 
    2.753006544583e+00F, 2.753833323538e+00F, 2.754660102494e+00F, 
    2.755486881449e+00F, 2.756313660404e+00F, 2.757140439360e+00F, 
    2.757967218315e+00F, 2.758793997270e+00F, 2.759620776226e+00F, 
    2.760447555181e+00F, 2.761274334136e+00F, 2.762101113092e+00F, 
    2.762927892047e+00F, 2.763754671002e+00F, 2.764581449958e+00F, 
    2.765408228913e+00F, 2.766235007868e+00F, 2.767061786824e+00F, 
    2.767888565779e+00F, 2.768715344734e+00F, 2.769542123690e+00F, 
    2.770368902645e+00F, 2.771195681600e+00F, 2.772022460556e+00F, 
    2.772849239511e+00F, 2.773676018466e+00F, 2.774502797422e+00F, 
    2.775329576377e+00F, 2.776156355332e+00F, 2.776983134288e+00F, 
    2.777809913243e+00F, 2.778636692198e+00F, 2.779463471154e+00F, 
    2.780290250109e+00F, 2.781117029064e+00F, 2.781943808020e+00F, 
    2.782770586975e+00F, 2.783597365930e+00F, 2.784424144886e+00F, 
    2.785250923841e+00F, 2.786077702796e+00F, 2.786904481752e+00F, 
    2.787731260707e+00F, 2.788558039662e+00F, 2.789384818618e+00F, 
    2.790211597573e+00F, 2.791038376528e+00F, 2.791865155484e+00F, 
    2.792691934439e+00F, 2.793518713394e+00F, 2.794345492350e+00F, 
    2.795172271305e+00F, 2.795999050260e+00F, 2.796825829216e+00F, 
    2.797652608171e+00F, 2.798479387126e+00F, 2.799306166082e+00F, 
    2.800132945037e+00F, 2.800959723992e+00F, 2.801786502948e+00F, 
    2.802613281903e+00F, 2.803440060858e+00F, 2.804266839814e+00F, 
    2.805093618769e+00F, 2.805920397724e+00F, 2.806747176680e+00F, 
    2.807573955635e+00F, 2.808400734590e+00F, 2.809227513546e+00F, 
    2.810054292501e+00F, 2.810881071456e+00F, 2.811707850412e+00F, 
    2.812534629367e+00F, 2.813361408322e+00F, 2.814188187278e+00F, 
    2.815014966233e+00F, 2.815841745188e+00F, 2.816668524144e+00F, 
    2.817495303099e+00F, 2.818322082054e+00F, 2.819148861010e+00F, 
    2.819975639965e+00F, 2.820802418920e+00F, 2.821629197876e+00F, 
    2.822455976831e+00F, 2.823282755786e+00F, 2.824109534742e+00F, 
    2.824936313697e+00F, 2.825763092652e+00F, 2.826589871608e+00F, 
    2.827416650563e+00F, 2.828243429518e+00F, 2.829070208474e+00F, 
    2.829896987429e+00F, 2.830723766384e+00F, 2.831550545340e+00F, 
    2.832377324295e+00F, 2.833204103250e+00F, 2.834030882206e+00F, 
    2.834857661161e+00F, 2.835684440116e+00F, 2.836511219072e+00F, 
    2.837337998027e+00F, 2.838164776982e+00F, 2.838991555938e+00F, 
    2.839818334893e+00F, 2.840645113848e+00F, 2.841471892804e+00F, 
    2.842298671759e+00F, 2.843125450714e+00F, 2.843952229670e+00F, 
    2.844779008625e+00F, 2.845605787580e+00F, 2.846432566536e+00F, 
    2.847259345491e+00F, 2.848086124446e+00F, 2.848912903402e+00F, 
    2.849739682357e+00F, 2.850566461312e+00F, 2.851393240268e+00F, 
    2.852220019223e+00F, 2.853046798178e+00F, 2.853873577134e+00F, 
    2.854700356089e+00F, 2.855527135044e+00F, 2.856353914000e+00F, 
    2.857180692955e+00F, 2.858007471910e+00F, 2.858834250866e+00F, 
    2.859661029821e+00F, 2.860487808776e+00F, 2.861314587732e+00F, 
    2.862141366687e+00F, 2.862968145642e+00F, 2.863794924598e+00F, 
    2.864621703553e+00F, 2.865448482508e+00F, 2.866275261464e+00F, 
    2.867102040419e+00F, 2.867928819374e+00F, 2.868755598330e+00F, 
    2.869582377285e+00F, 2.870409156240e+00F, 2.871235935196e+00F, 
    2.872062714151e+00F, 2.872889493106e+00F, 2.873716272062e+00F, 
    2.874543051017e+00F, 2.875369829972e+00F, 2.876196608928e+00F, 
    2.877023387883e+00F, 2.877850166838e+00F, 2.878676945794e+00F, 
    2.879503724749e+00F, 2.880330503704e+00F, 2.881157282660e+00F, 
    2.881984061615e+00F, 2.882810840570e+00F, 2.883637619526e+00F, 
    2.884464398481e+00F, 2.885291177436e+00F, 2.886117956392e+00F, 
    2.886944735347e+00F, 2.887771514302e+00F, 2.888598293258e+00F, 
    2.889425072213e+00F, 2.890251851168e+00F, 2.891078630124e+00F, 
    2.891905409079e+00F, 2.892732188034e+00F, 2.893558966990e+00F, 
    2.894385745945e+00F, 2.895212524900e+00F, 2.896039303856e+00F, 
    2.896866082811e+00F, 2.897692861766e+00F, 2.898519640722e+00F, 
    2.899346419677e+00F, 2.900173198632e+00F, 2.900999977588e+00F, 
    2.901826756543e+00F, 2.902653535498e+00F, 2.903480314454e+00F, 
    2.904307093409e+00F, 2.905133872364e+00F, 2.905960651320e+00F, 
    2.906787430275e+00F, 2.907614209230e+00F, 2.908440988186e+00F, 
    2.909267767141e+00F, 2.910094546096e+00F, 2.910921325052e+00F, 
    2.911748104007e+00F, 2.912574882962e+00F, 2.913401661918e+00F, 
    2.914228440873e+00F, 2.915055219828e+00F, 2.915881998784e+00F, 
    2.916708777739e+00F, 2.917535556694e+00F, 2.918362335650e+00F, 
    2.919189114605e+00F, 2.920015893560e+00F, 2.920842672516e+00F, 
    2.921669451471e+00F, 2.922496230426e+00F, 2.923323009382e+00F, 
    2.924149788337e+00F, 2.924976567292e+00F, 2.925803346248e+00F, 
    2.926630125203e+00F, 2.927456904158e+00F, 2.928283683114e+00F, 
    2.929110462069e+00F, 2.929937241024e+00F, 2.930764019980e+00F, 
    2.931590798935e+00F, 2.932417577890e+00F, 2.933244356846e+00F, 
    2.934071135801e+00F, 2.934897914756e+00F, 2.935724693712e+00F, 
    2.936551472667e+00F, 2.937378251622e+00F, 2.938205030578e+00F, 
    2.939031809533e+00F, 2.939858588488e+00F, 2.940685367444e+00F, 
    2.941512146399e+00F, 2.942338925354e+00F, 2.943165704310e+00F, 
    2.943992483265e+00F, 2.944819262220e+00F, 2.945646041176e+00F, 
    2.946472820131e+00F, 2.947299599086e+00F, 2.948126378042e+00F, 
    2.948953156997e+00F, 2.949779935952e+00F, 2.950606714908e+00F, 
    2.951433493863e+00F, 2.952260272818e+00F, 2.953087051774e+00F, 
    2.953913830729e+00F, 2.954740609684e+00F, 2.955567388640e+00F, 
    2.956394167595e+00F, 2.957220946550e+00F, 2.958047725506e+00F, 
    2.958874504461e+00F, 2.959701283416e+00F, 2.960528062372e+00F, 
    2.961354841327e+00F, 2.962181620282e+00F, 2.963008399238e+00F, 
    2.963835178193e+00F, 2.964661957148e+00F, 2.965488736104e+00F, 
    2.966315515059e+00F, 2.967142294014e+00F, 2.967969072970e+00F, 
    2.968795851925e+00F, 2.969622630880e+00F, 2.970449409836e+00F, 
    2.971276188791e+00F, 2.972102967746e+00F, 2.972929746702e+00F, 
    2.973756525657e+00F, 2.974583304612e+00F, 2.975410083568e+00F, 
    2.976236862523e+00F, 2.977063641478e+00F, 2.977890420434e+00F, 
    2.978717199389e+00F, 2.979543978344e+00F, 2.980370757300e+00F, 
    2.981197536255e+00F, 2.982024315210e+00F, 2.982851094166e+00F, 
    2.983677873121e+00F, 2.984504652076e+00F, 2.985331431032e+00F, 
    2.986158209987e+00F, 2.986984988942e+00F, 2.987811767898e+00F, 
    2.988638546853e+00F, 2.989465325808e+00F, 2.990292104764e+00F, 
    2.991118883719e+00F, 2.991945662674e+00F, 2.992772441630e+00F, 
    2.993599220585e+00F, 2.994425999540e+00F, 2.995252778496e+00F, 
    2.996079557451e+00F, 2.996906336406e+00F, 2.997733115362e+00F, 
    2.998559894317e+00F, 2.999386673272e+00F, 3.000213452228e+00F, 
    3.001040231183e+00F, 3.001867010138e+00F, 3.002693789094e+00F, 
    3.003520568049e+00F, 3.004347347004e+00F, 3.005174125960e+00F, 
    3.006000904915e+00F, 3.006827683870e+00F, 3.007654462826e+00F, 
    3.008481241781e+00F, 3.009308020736e+00F, 3.010134799692e+00F, 
    3.010961578647e+00F, 3.011788357602e+00F, 3.012615136558e+00F, 
    3.013441915513e+00F, 3.014268694468e+00F, 3.015095473424e+00F, 
    3.015922252379e+00F, 3.016749031334e+00F, 3.017575810290e+00F, 
    3.018402589245e+00F, 3.019229368200e+00F, 3.020056147156e+00F, 
    3.020882926111e+00F, 3.021709705066e+00F, 3.022536484022e+00F, 
    3.023363262977e+00F, 3.024190041932e+00F, 3.025016820888e+00F, 
    3.025843599843e+00F, 3.026670378798e+00F, 3.027497157754e+00F, 
    3.028323936709e+00F, 3.029150715664e+00F, 3.029977494620e+00F, 
    3.030804273575e+00F, 3.031631052530e+00F, 3.032457831486e+00F, 
    3.033284610441e+00F, 3.034111389396e+00F, 3.034938168352e+00F, 
    3.035764947307e+00F, 3.036591726262e+00F, 3.037418505218e+00F, 
    3.038245284173e+00F, 3.039072063128e+00F, 3.039898842084e+00F, 
    3.040725621039e+00F, 3.041552399994e+00F, 3.042379178950e+00F, 
    3.043205957905e+00F, 3.044032736860e+00F, 3.044859515816e+00F, 
    3.045686294771e+00F, 3.046513073726e+00F, 3.047339852682e+00F, 
    3.048166631637e+00F, 3.048993410592e+00F, 3.049820189548e+00F, 
    3.050646968503e+00F, 3.051473747458e+00F, 3.052300526414e+00F, 
    3.053127305369e+00F, 3.053954084324e+00F, 3.054780863280e+00F, 
    3.055607642235e+00F, 3.056434421190e+00F, 3.057261200146e+00F, 
    3.058087979101e+00F, 3.058914758056e+00F, 3.059741537012e+00F, 
    3.060568315967e+00F, 3.061395094922e+00F, 3.062221873878e+00F, 
    3.063048652833e+00F, 3.063875431788e+00F, 3.064702210744e+00F, 
    3.065528989699e+00F, 3.066355768654e+00F, 3.067182547610e+00F, 
    3.068009326565e+00F, 3.068836105520e+00F, 3.069662884476e+00F, 
    3.070489663431e+00F, 3.071316442386e+00F, 3.072143221342e+00F, 
    3.072970000297e+00F, 3.073796779252e+00F, 3.074623558208e+00F, 
    3.075450337163e+00F, 3.076277116118e+00F, 3.077103895074e+00F, 
    3.077930674029e+00F, 3.078757452984e+00F, 3.079584231940e+00F, 
    3.080411010895e+00F, 3.081237789850e+00F, 3.082064568806e+00F, 
    3.082891347761e+00F, 3.083718126716e+00F, 3.084544905672e+00F, 
    3.085371684627e+00F, 3.086198463582e+00F, 3.087025242538e+00F, 
    3.087852021493e+00F, 3.088678800448e+00F, 3.089505579404e+00F, 
    3.090332358359e+00F, 3.091159137314e+00F, 3.091985916270e+00F, 
    3.092812695225e+00F, 3.093639474180e+00F, 3.094466253136e+00F, 
    3.095293032091e+00F, 3.096119811046e+00F, 3.096946590002e+00F, 
    3.097773368957e+00F, 3.098600147912e+00F, 3.099426926868e+00F, 
    3.100253705823e+00F, 3.101080484778e+00F, 3.101907263734e+00F, 
    3.102734042689e+00F, 3.103560821644e+00F, 3.104387600600e+00F, 
    3.105214379555e+00F, 3.106041158510e+00F, 3.106867937466e+00F, 
    3.107694716421e+00F, 3.108521495376e+00F, 3.109348274332e+00F, 
    3.110175053287e+00F, 3.111001832242e+00F, 3.111828611198e+00F, 
    3.112655390153e+00F, 3.113482169108e+00F, 3.114308948064e+00F, 
    3.115135727019e+00F, 3.115962505974e+00F, 3.116789284930e+00F, 
    3.117616063885e+00F, 3.118442842840e+00F, 3.119269621796e+00F, 
    3.120096400751e+00F, 3.120923179706e+00F, 3.121749958662e+00F, 
    3.122576737617e+00F, 3.123403516572e+00F, 3.124230295528e+00F, 
    3.125057074483e+00F, 3.125883853438e+00F, 3.126710632394e+00F, 
    3.127537411349e+00F, 3.128364190304e+00F, 3.129190969260e+00F, 
    3.130017748215e+00F, 3.130844527170e+00F, 3.131671306126e+00F, 
    3.132498085081e+00F, 3.133324864036e+00F, 3.134151642992e+00F, 
    3.134978421947e+00F, 3.135805200902e+00F, 3.136631979858e+00F, 
    3.137458758813e+00F, 3.138285537768e+00F, 3.139112316724e+00F, 
    3.139939095679e+00F, 3.140765874634e+00F, }; 

// End of File