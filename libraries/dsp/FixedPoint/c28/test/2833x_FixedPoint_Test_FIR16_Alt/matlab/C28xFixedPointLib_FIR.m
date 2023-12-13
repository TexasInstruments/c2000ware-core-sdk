%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Fixed Point Finite Impulse Response Filter
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%//! \brief 16/32-bit FIR filter
%//!
%//! \author Vishal Coelho
%//!
%//! \details 16/32 bit fixed point filter that replicates
%//!        the operation of the FIR16(32) filter in the fixed point
%//!        library. Will be used to test the output of the asm filter
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Basics of fimath
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Table taken from MATLAB R2013b help doc
%+-------------------------------------------------------------------------------------------+
%|             |A              |B              |Sum = A+B                   |Prod = A*B      |
%+-------------------------------------------------------------------------------------------+
%|Format       |fi(vA,s1,w1,f1)|fi(vB,s2,w2,f2)|-                           |-               |
%|Sign         |s1             |s2             |s1||s2                      |s1||s2          |
%|Integer bits |I1 = w1-f1-s1  |I2= w2-f2-s2   |max(I1 , I2) + 1            |(w1+w2)-(f1+f2) |
%|Fraction bits|f1             |f2             |max(f1 , f 2) + 1           |f1 + f2         |
%|Total bits   |w1             |w2             |1+max(I1,I2)+1+max(f1,f2)+1 |w1 + w2         |
%+-------------------------------------------------------------------------------------------+
clc
clear all
close all

TRUE           = 1;
FALSE          = 0;

% Force an FIR design
FORCE_FIR      = TRUE;

IMPULSE        = 1;
STEP           = 2;
RAMP           = 3;
MULTI          = 4;
USE_INPUT      = MULTI;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% User Inputs
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
W = input('Do you want \n 1. 16-bit\n 2. 32-bit FIR\n operation? :');
S = 1; % signed
if(W == 1)
    W = 16; Q = 15;
elseif(W == 2)
    W = 32; Q = 31;
else
    disp('Value out of range, default to 1\n');
    W = 16; Q = 15;
end
sizeOfInput = input('Size of input? ');
while(sizeOfInput <= 0 || sizeOfInput > 65536)
    disp('Invalid: ');
    sizeOfInput = input('Size of input? ');
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Specify the Fixed Point Math Object
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
FIPREF_STATE = get(fipref);
reset(fipref)
% Specify the preferences for the fi objects
P = fipref(...
    'NumberDisplay', 'RealWorldValue', ...
    'NumericTypeDisplay', 'full', ...
    'FimathDisplay', 'full'... %MATLAB displays custom and default fi objects info
    );
% Specifying fimath object allows you to control bit growth from successive
% operations and tells MATLAB how arithmetic operations should be handled
F = fimath(...
    'SumMode', 'SpecifyPrecision',...
    'SumWordLength', W,...
    'SumFractionLength', Q,...
    'ProductMode', 'SpecifyPrecision',...
    'ProductWordLength', W, ...
    'ProductFractionLength', Q, ...
    'RoundingMethod', 'Convergent' ... %round to closest (to even on ties)
    );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% filter coefficients
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if(FORCE_FIR == FALSE)
    % Using this method, you could get an FIR or IIR filter
    samplingFreq = 200e3;
    attenStop    = 60;
    attenPass    = 1;
    freqPass     = 20e3;
    freqStop     = 30e3;
    
    LowPassSpecObj = fdesign.lowpass('Fp,Fst,Ap,Ast', freqPass, freqStop,...
        attenPass, attenStop, samplingFreq);
else
    % Use this to force an FIR design
    order        = input('Filter order:? ');
    samplingFreq = 200e3;
    freqPass     = 20e3;
    
    LowPassSpecObj = fdesign.lowpass('N,Fc', order, freqPass, samplingFreq);
end
% Display all available methods
filterMenu = designmethods(LowPassSpecObj);
disp(filterMenu);
menuChoice = input('Choose a method(Enter a number):');
while(menuChoice < 1 || menuChoice > length(filterMenu))
    disp(['Invalid choice, choose between 1 and ',num2str(length(filterMenu))]);
    menuChoice = input('Choose a method(Enter a number):');
end

% what are the design options for the chosen method
LowPassDesignOpts = designopts(LowPassSpecObj, char(filterMenu(menuChoice)))

% Design the filter using the user specified method and min order
LowPassFilt = design(LowPassSpecObj, char(filterMenu(menuChoice)))

% Display the filter
% fvtool(LowPassFilt);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Build the MEX function
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Filter parameters
N    = length(LowPassFilt.Numerator);
x    = fi(zeros(sizeOfInput,1),S,W,Q,'fimath',F);
c    = fi(LowPassFilt.Numerator,S,W,Q, 'fimath', F);
C    = coder.Constant(c);

% For the 32-bit FIR we want the input to be Q31 but the output to be 
% Q30, so for each product there will be a scaling of 0.5
if W == 32
    yisd = fi(zeros(sizeOfInput,1),S,W,Q-1,'DataType','Fixed','fimath',F);
else
    yisd = fi(zeros(sizeOfInput,1),S,W,Q,'DataType','Fixed','fimath',F);
end

buildInstrumentedMex fir_m ...
    -o fir_fixed ...
    -args {x, C, yisd}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Test Bench 1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
t = linspace(0,1,sizeOfInput);        % Time vector from 0 to 1 second
n = 0 : sizeOfInput-1;

if USE_INPUT == MULTI
    f1 = 20e3; f2 = 40e3; f3 = 45e3;      % Frequencies of the inputs
    fs = samplingFreq;                    % Add two sine waves together
    k1 = f1/fs; k2 = f2/fs; k3 = f3/fs;
    xmulti = 0.5*(sin(2*pi*k1.*n)+sin(2*pi*k2.*n)+sin(2*pi*k3.*n));
    
elseif USE_INPUT == IMPULSE
    % Impulse function
    xmulti(1) = 1.0;
    xmulti(2:sizeOfInput) = 0.0;
elseif USE_INPUT == RAMP
    xmulti = t;
else % USE_INPUT == STEP
    xmulti = ones(sizeOfInput);
end
x(:) = xmulti;             % Cast the input to fixed-point
% Running the MEX function
ymulti = fir_fixed(x,yisd);

% Plot the output
clf
plot(t,x,'c',t,ymulti,'bo-')
title('Filter')
legend('Input','Fixed Point Output')
figure(gcf); drawnow;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Write the input/output/coeffs vectors to file
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
X   = reshape(x, sizeOfInput/8, 8);
if W == 16
    S_X = sprintf(['%10d, %10d, %10d, %10d, %10d, %10d,',...
        '%10d, %10d, \n'], (X.int));
else
    S_X = sprintf(['%14d, %14d, %14d, %14d, %14d, %14d,',...
        '%14d, %14d, \n'], (X.int));
end
fid = fopen('data_input.txt', 'w');
if USE_INPUT == MULTI
fprintf(fid, ['// f1 =',num2str(f1),', f2 = ',num2str(f2),...
    ', f3 = ',num2str(f3),' fs = ',num2str(samplingFreq),'\n']);
elseif USE_INPUT == IMPULSE
    fprintf(fid,'// Impulse \n');
elseif USE_INPUT == RAMP
    fprintf(fid,'// Ramp \n');
else % STEP
    fprintf(fid,'// Step \n');
end
fprintf(fid, S_X);
fclose(fid);

Y   = reshape(ymulti, sizeOfInput/8, 8);
if W == 16
    S_Y = sprintf(['%10d, %10d, %10d, %10d, %10d, %10d,',...
        '%10d, %10d, \n'], (Y.int));
else
    S_Y = sprintf(['%14d, %14d, %14d, %14d, %14d, %14d,',...
        '%14d, %14d, \n'], (Y.int));
end
fid = fopen('data_output.txt', 'w');
fprintf(fid, S_Y);
fclose(fid);

C = c(end:-1:1);
if W == 16
    S_C = sprintf(['%10d, %10d, %10d, %10d, %10d, %10d,',...
        '%10d, %10d, \n'], (C.int));
else
    S_C = sprintf(['%14d, %14d, %14d, %14d, %14d, %14d,',...
        '%14d, %14d, \n'], (C.int));
end
fid = fopen('coeffs.txt', 'w');
if FORCE_FIR == FALSE
    fprintf(fid, [...
        '// Fs  = ',num2str(samplingFreq ),'\n',...
        '// Fst = ',num2str(attenStop    ),'\n',...
        '// Fp  = ',num2str(attenPass    ),'\n',...
        '// Ap  = ',num2str(freqPass     ),'\n',...
        '// Ast = ',num2str(freqStop     ),'\n']);
else
    fprintf(fid, [...
        '// Fs  = ',num2str(samplingFreq ),'\n',...
        '// Fc  = ',num2str(freqPass    ),'\n',...
        '// N   = ',num2str(order     ),'\n']);
end
fprintf(fid, S_C);
fclose(fid);
