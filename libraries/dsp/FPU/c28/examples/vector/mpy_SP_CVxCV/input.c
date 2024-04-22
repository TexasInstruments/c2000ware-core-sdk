//#############################################################################
//! \file   input.c
//! \brief  Input Vector (64) 
//! \author Vishal Coelho 
//! \date   16-Sep-2016
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


float test_input[256] = {
     1.977467242167F,  2.456117572862F,  2.549665936805F,  2.885813134564F, 
    -2.343710955249F,  0.296663924139F,  2.597317105635F, -2.270589591193F, 
     0.831637671153F, -2.203550751411F, -2.528728214041F, -1.523620574802F, 
    -1.391736736729F,  2.140789656699F,  0.294565272647F, -1.543890602798F, 
     2.874600226335F,  1.974709801425F,  2.920980813840F, -1.611480148166F, 
    -2.151280454574F,  2.697142890117F,  2.956821652023F, -0.942579797403F, 
     2.872464652128F, -1.906348264619F, -0.091887509072F, -1.563986246285F, 
     1.886717830155F,  0.729130204141F, -2.250094495438F, -0.167831112112F, 
    -0.491588359455F, -0.932050805682F,  2.612143343541F,  2.078657573992F, 
     1.835992799739F,  0.535730084761F,  2.887076062272F,  0.312422645035F, 
     0.978547672671F,  2.621305098824F, -2.917209559478F, -1.345613130319F, 
     2.193644124941F,  1.616036700552F,  2.726859997725F,  1.594226917175F, 
     1.123026098879F, -0.751180897697F,  1.619429001520F,  0.426135936514F, 
     1.527646351421F, -2.664986095921F, -0.677157607374F, -2.802614060663F, 
     0.976896395155F,  0.193506732563F, -2.065994971947F,  1.754059438423F, 
     1.294625752847F,  2.726969554308F, -2.941580980945F, -2.325367873196F, 
    -1.401634223263F,  0.432431814778F, -2.851489250364F, -0.192324274365F, 
    -2.531295672869F, -3.066809745375F,  2.032345474438F, -1.023388607585F, 
     1.224144341300F, -2.122571157666F, -1.149197859557F,  1.849044302155F, 
     2.828828562229F, -1.186170874041F, -2.925161546684F,  0.179278977780F, 
    -0.384880539389F, -2.100790990244F, -0.744190162153F,  0.640771435812F, 
     1.668291182107F, -1.489295342357F,  1.854795681505F,  0.968107527693F, 
    -1.967437450339F,  1.188869786035F, -0.064312197993F,  1.559182441983F, 
    -0.341891984201F, -0.310756301606F,  0.919311755380F, -2.614927402932F, 
     1.315478029088F, -1.702887928066F,  1.600243618166F,  2.597075236696F, 
    -1.407275945379F, -2.184173323665F,  1.129105218868F,  2.047168445792F, 
     0.974509499741F,  0.240912625867F, -2.119872988240F,  3.117306361892F, 
    -2.393908169234F, -2.650401319947F, -0.010278964549F, -0.360163053129F, 
     2.888656485213F, -2.471473535021F, -1.002886057027F,  2.902191235043F, 
     0.535753080132F, -3.112474964600F, -1.735340763808F,  1.727313392665F, 
     1.578757495207F,  1.993674933930F, -1.538782772203F,  2.316577155575F, 
     0.037429259497F, -2.611066589676F,  1.250835938798F, -0.629684186706F, 
    -1.508778756628F, -0.082990621216F,  1.885385866093F, -0.403012373810F, 
    -0.430939631557F, -0.334367563686F,  2.580174931748F, -1.216742152153F, 
    -1.999014077203F,  0.053461458475F, -1.484070044508F,  0.067679733742F, 
    -2.227144270415F,  1.995713750084F, -2.286648684742F,  1.852480426657F, 
     2.320331373100F,  0.906777555193F,  0.500798692250F, -0.762719743298F, 
     0.313280887591F,  1.957717757485F, -2.230814795185F,  0.206249257244F, 
     2.218159931847F, -0.937909269566F,  0.766895008813F,  2.758328164187F, 
    -0.936493810448F,  2.362118349513F,  0.083249314220F,  0.315141596761F, 
    -0.616958319613F,  0.769533660858F, -2.664279852523F,  0.546918008580F, 
    -1.634155002626F, -1.836309332210F, -2.366756934136F, -1.248806137336F, 
    -1.986065940378F, -0.182693989376F, -1.633926469911F, -1.693392831870F, 
    -0.519826335949F,  2.163355947396F, -2.829604666531F, -1.917852531019F, 
     2.530339944784F, -1.722084238812F,  2.794680335281F, -2.069002359933F, 
    -0.057402599972F, -1.711135682579F, -0.067527664496F, -0.404017083271F, 
    -1.019639019851F, -1.186879337078F,  2.513612449892F,  2.660172746622F, 
    -0.821546703732F, -0.438519893348F, -2.442885135410F, -1.980357466459F, 
     1.760875677982F,  2.543942153566F, -0.692791319558F,  3.014347962030F, 
    -1.623001517063F, -0.384091286682F, -0.603737795039F, -2.443409981523F, 
    -2.535550998241F, -1.520124347933F, -2.312380000546F, -0.573530121743F, 
     2.777485776991F,  0.596249617920F,  2.865977841269F, -1.494067652563F, 
     0.472549539571F,  0.646182188150F, -2.765986707674F,  1.327107888265F, 
    -1.666426951467F, -1.748316832498F, -0.922631907783F, -2.403835794929F, 
     2.018121674125F, -1.277523165990F, -3.044810000457F, -1.138649510681F, 
    -2.871266135154F, -0.476474301162F, -2.079796983410F,  0.049375058722F, 
     0.936920161319F, -2.604281053782F,  1.455954688915F, -1.492368133138F, 
     0.928315264773F,  1.891330655033F, -0.308355446684F, -2.957996234940F, 
     0.295365581320F,  2.694570028092F, -1.279754121583F,  1.447211493283F, 
     1.537450250181F, -0.071571928431F, -1.954353279419F,  0.493387509668F, 
     1.173544658663F, -1.650695951534F, -1.988558056158F, -0.258560438153F, 
    -0.826335651000F,  2.909671105971F,  0.789284695086F,  0.294089004273F, 
     1.760720903212F,  0.1328001341563F, -2.631864414619F, -1.686442205798F, 
     2.697911623900F, -0.069757532277F,  1.732353851235F,  0.779492523220F, 
}; 

// End of File
