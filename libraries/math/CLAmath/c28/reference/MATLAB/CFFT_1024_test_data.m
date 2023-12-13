close all
clc
%% 1024 CFFT - data in/out 1
n = 1 : 1024;
f0 = 1000;
fs = 10240;
I = sin(2*pi.*n*f0/fs);
Q  = cos((2*pi+pi/4).*n*f0/fs);
A = I+j*Q;
B = [I; Q]';
delete ../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_in1.h
fileID = fopen('../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_in1.h','w')
fprintf(fileID,'// 1024 CFFT Data Input 1\n');
Si1 = fprintf(fileID,'%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', B')
fclose(fileID);
D = fft(A);
f = fs/2*linspace(0,1,1024);
%plot(f, abs(D))
I = real(D);
Q = imag(D);
B = [I; Q]';
C = reshape(B', 8, 2048/8)';
delete ../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_out1.h
fileID = fopen('../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_out1.h','w');
fprintf(fileID,'// 1024 CFFT Data Output 1\n');
So1 = fprintf(fileID, '%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', C')
fclose(fileID);

%% 1024 CFFT - data in/out 2
close all
clc
n = 1 : 1024;
f0 = 1000; f1 = 2000;
fs = 10240;
I = sin(2*pi.*n*f0/fs) + sin(2*pi.*n*f1/fs);
Q  = cos((2*pi+pi/4).*n*f0/fs) + cos(2*pi.*n*f1/fs);
A = I+j*Q;
B = [I; Q]';
delete ../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_in2.h
fileID = fopen('../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_in2.h','w')
fprintf(fileID,'// 1024 CFFT Data Input 2\n');
Si1 = fprintf(fileID,'%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', B')
fclose(fileID);
D = fft(A);
f = fs/2*linspace(0,1,1024);
%plot(f, abs(D))
I = real(D);
Q = imag(D);
B = [I; Q]';
C = reshape(B', 8, 2048/8)';
delete ../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_out2.h
fileID = fopen('../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_out2.h','w');
fprintf(fileID,'// 1024 CFFT Data Output 2\n');
So1 = fprintf(fileID, '%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', C')
fclose(fileID);

%% 1024 CFFT - data in/out 3
close all
clc
n = 1 : 1024;
f0 = 1000; f1 = 2000; f2 = 3750;
fs = 10240;
I = sin(2*pi.*n*f0/fs) + sin(2*pi.*n*f1/fs) + sin(2*pi.*n*f2/fs);
Q  = cos((2*pi+pi/4).*n*f0/fs) + cos(2*pi.*n*f1/fs);
A = I+j*Q;
B = [I; Q]';
delete ../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_in3.h
fileID = fopen('../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_in3.h','w')
fprintf(fileID,'// 1024 CFFT Data Input 3\n');
Si1 = fprintf(fileID,'%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', B')
fclose(fileID);
D = fft(A);
f = fs/2*linspace(0,1,1024);
%plot(f, abs(D))
I = real(D);
Q = imag(D);
B = [I; Q]';
C = reshape(B', 8, 2048/8)';
delete ../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_out3.h
fileID = fopen('../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_out3.h','w');
fprintf(fileID,'// 1024 CFFT Data Output 3\n');
So1 = fprintf(fileID, '%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', C')
fclose(fileID);


%% 1024 CFFT - data in/out 4
close all
clc
n = 1 : 1024;
f0 = 1000; f1 = 1750; f2 = 3750;
fs = 10240;
I = sin(2*pi.*n*f0/fs) + cos(2*pi.*n*f1/fs) + sin(2*pi.*n*f2/fs);
Q  = sin((2*pi+pi/4).*n*f0/fs) + cos(2*pi.*n*f1/fs);
A = I+j*Q;
B = [I; Q]';
delete ../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_in4.h
fileID = fopen('../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_in4.h','w')
fprintf(fileID,'// 1024 CFFT Data Input 4\n');
Si1 = fprintf(fileID,'%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', B')
fclose(fileID);
D = fft(A);
f = fs/2*linspace(0,1,1024);
%plot(f, abs(D))
I = real(D);
Q = imag(D);
B = [I; Q]';
C = reshape(B', 8, 2048/8)';
delete ../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_out4.h
fileID = fopen('../examples/fft/2837x_cla_cfft_1024/cfft_1024_data_out4.h','w');
fprintf(fileID,'// 1024 CFFT Data Output 4\n');
So1 = fprintf(fileID, '%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', C')
fclose(fileID);
