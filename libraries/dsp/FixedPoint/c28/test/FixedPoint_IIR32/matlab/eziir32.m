
Ni=500;             % Number of impulses required for Impulse response
FMAT=32;            % 16 bit representation or 32 bit representation
disp('ezIIR FILTER DESIGN SCRIPT');
disp('Butterworth       : 1');
disp('Chebyshev(Type 1) : 2');
disp('Chebyshev(Type 2) : 3');
disp('Elliptic          : 4');
ftype=input('Select Any one of the above IIR Filter Type     : ');
disp('Low pass          : 1');
disp('High Pass         : 2');
disp('Band Pass         : 3');
disp('Band Stop         : 4');
fres=input('Select Any one of the above Response            : ');
fs=input('Enter the Sampling frequency                    : ');
Rp=input('Enter the Pass band Ripples in dB(RP)           : ');
Rs=input('Enter the stop band Rippled in dB(RS)           : ');
Wp=input('Enter the pass band corner frequency(FP)        : ');
Ws=input('Enter the stop band corner frequency(FS)        : ');
fname=input('Enter the name of the file for coeff storage    : ','s');

% Design the Filter
if fres==1
    res='low';
   elseif fres==2
      res='high';
   elseif fres==3
      res='bandpass';
   elseif fres==4
      res='stop';
end

Wp=Wp/(fs/2);                           % Normalise the frequency values
Ws=Ws/(fs/2);                           % Normalise the frequency values

if ftype==1
   [N,Wn]=buttord(Wp,Ws,Rp,Rs);
   [Z,P,K]=butter(N,Wn,res);
end

if ftype==2
   [N,Wn]=cheb1ord(Wp,Ws,Rp,Rs);
   [Z,P,K]=cheby1(N,Rp,Wn,res);
end

if ftype==3
   [N,Wn]=cheb2ord(Wp,Ws,Rp,Rs);
   [Z,P,K]=cheby2(N,Rs,Wn,res);
end

if ftype==4
   [N,Wn]=ellipord(Wp,Ws,Rp,Rs);
   [Z,P,K]=ellip(N,Rp,Rs,Wn,res);
end

sos=zp2sos(Z,P,K);                      % Convert ZP to SOS 
ssos=sos;                               % Copy of SOS, will be used for scaling 
isos=ssos;                              % Copy of SOS, will be used for Q format Rep
nbiq=size(sos,1);                       % Number of biquads(no of rows)
dmag=zeros(1,nbiq);                     % Clear Peak manitude buffer for Delay node
ymag=zeros(1,nbiq);                     % Clear Peak manitude buffer for Output node
sf=zeros(1,nbiq);                       % Clear Scale Factor array

B=zeros(1,nbiq*3);
A=zeros(1,nbiq*3);

% Obtain the peak magnitude at various nodes in Cascaded Biquad implementation
for i=1:nbiq                            % Loop to find the peak magnitude in SOS nodes
   if i==1                              % Obtain the peak magnitue at the first delay node
      num=[1 0 0];               
      den=sos(1,4:6);
      h=impz(num,den,Ni);
      dmag(i)=sum(abs(h));
   end
   
   if i~=1                              % Obtain the peak magnitue at the delay node
      [num,den]=sos2tf(sos(1:i-1,:)); 
      den=conv(den,sos(i,4:6));
      h=impz(num,den,Ni);
      dmag(i)=sum(abs(h));
   end
   
   [num,den]=sos2tf(sos(1:i,:));        % Obtain the peak magnitue at the biquad output node
   h=impz(num,den,Ni);
   ymag(i)=sum(abs(h));
   sf(i)=max(ymag(i),dmag(i));
end

% Scale the B coeff of biquad to avoid overflow in the node

for i=2:nbiq
   scale=sf(i)/sf(i-1);
   ssos(i-1,1:3)=ssos(i-1,1:3)/scale;
end

% Scale the 'b' coeff of last BIQUAD 
ssos(nbiq,1:3)=ssos(nbiq,1:3)*sf(nbiq);

% Determine the Q format for representing the coefficients & Input Scale factor
maxcoeff=max(max(abs(ssos)));
maxval=max(maxcoeff,1/sf(1));		% Modified from max(maxcoeff, sf(1)), Settu 27/12/2001
qformat=FMAT-1;
if(maxval>1)
   qformat=(FMAT-1)-ceil(log2(maxval));
   qscale=2^qformat;
end

% Respresent the scaled second order section and ISF in appropriate number format 
isos=ssos*qscale;
isos=round(isos);

isf=(1/sf(1))*qscale;                   % Represent the input scale factor in Fixed Point format    
isf=round(isf);

% Saturate the coefficient to maximum positive value
for i=1:nbiq
    for j=1:6
        if isos(i,j)==2^(FMAT-1)
         isos(i,j)=(2^(FMAT-1))-1;
      end
   end
end

if isf==2^(FMAT-1)                      % Saturate to maximum positive value
   isf=(2^(FMAT-1))-1;
end

% Open the file and store the scaled IIR filter coefficients and Input scale factor
fid = fopen(fname,'w');

fprintf(fid,'#define IIR32_COEFF {\\');
fprintf(fid,'\n');
   for i=1:nbiq
      fprintf(fid,'\t\t\t');
      bis=isos(i,1:3);
      bis=fliplr(bis);
      ais=isos(i,5:6);
      ais=-fliplr(ais);                 % Negate the 'a' coefficients
      fprintf(fid,'%d,',ais);
      fprintf(fid,'%d,',bis);
      fprintf(fid,'\\');
        fprintf(fid,'\n');
    end
    fseek(fid,-3,0);
   fprintf(fid,'}\n');
   fprintf(fid,'\n#define IIR32_ISF\t%d\n',isf);
   fprintf(fid,'#define IIR32_NBIQ\t%d\n',nbiq);
   fprintf(fid,'#define IIR32_QFMAT\t%d\n',qformat);
fclose(fid);

% Display Q format of the IIR filter coefficients, No of biquads
disp(' ');
disp('Q format of the IIR filter coefficients:');
disp(qformat);

disp('Input Scaling value:');
disp(1/sf(1));

disp('Number of Biquads:');
disp(nbiq);

% Plot the frequency response of the filter
[B,A]=sos2tf(sos);                  
[H,f]=freqz(B,A,512,fs);
figure(1);
subplot(2,1,1);
plot(f,abs(H));
grid;
xlabel('Hertz');
ylabel('Magnitude Response');
subplot(2,1,2);
plot(f,unwrap(angle(H))*180/pi);
grid;
xlabel('Hertz');
ylabel('Phase (degrees)');
figure(2);
freqz(B,A,512,fs);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % 
% % 
% %           SIGNAL WAVEFORM GENERATION
% % 
% %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

RadStep = 0.1963495408494;

N=input('Please enter signal length N =');
halfSize=N-1;

Rad=[0:RadStep:(halfSize)*RadStep];

CFFTinBuf1=zeros(1,N);

Rx=sin(Rad)+cos(Rad*2.3567);
Ix=0*(cos(Rad*8.345) + sin(Rad*5.789));

x=Rx+j*Ix;
x_raw_sig=x/2;

x_Q31=2^31*x/2;

filter_out_Q31=filter(B,A,x_Q31);
 
d=zeros(nbiq,3);
taps=3;

for k=1:length(x_Q31)
    
    accum=floor(x_Q31(k)*isf/2^32);
    
    for j=1:nbiq

        b_temp=isos(j,1:3);
        a_temp=isos(j,4:6);
        
        for ii=2:taps
            accum=accum-ceil(a_temp(ii)*d(j,ii)/2^32);
        end

        d(j,1)=floor(accum*2^(32-qformat));
        
        accum1=0;
        
        for ii=1:taps
            accum1=accum1+floor(b_temp(ii)*d(j,ii)/2^32);
        end
        
        for ii=(taps-2+1):-1:1
            d(j,ii+1)=d(j,ii);
        end
        
        accum=floor(accum1);
    
    end
    
    x_no_scale_biq_fixed(k)=(accum1)*2^(32-qformat);      % direct I form high order implementation output
    
end
   
figure(4)
plot(filter_out_Q31)
peak1=max(filter_out_Q31);
hold on
peak2=max(x_no_scale_biq_fixed);
plot(x_no_scale_biq_fixed,'r')

x_output_final=floor(x_no_scale_biq_fixed/2);



