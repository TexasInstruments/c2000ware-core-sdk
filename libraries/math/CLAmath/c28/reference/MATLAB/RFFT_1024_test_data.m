
%% 1024 RFFT - data in/out 1
n = 0 : 1023;
f0 = 1000;
fs = 10240;
I = sin(2*pi.*n*f0/fs);
Q = zeros(1, length(I));
A = I + j*Q;
delete ../examples/fft/2837x_cla_rfft_1024/rfft_1024_data_in1.h
fileID = fopen('../examples/fft/2837x_cla_rfft_1024/rfft_1024_data_in1.h','w')
fprintf(fileID,'// 1024 RFFT Data Input 1\n');
Si1 = fprintf(fileID,'%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', I)
fclose(fileID);
D = fft(A);
f = fs/2*linspace(0,1,1024);
%plot(f, abs(D))
I = real(D);
Q = imag(D);
B = [I; Q]';
C = reshape(B', 8, 2048/8)';
delete ../examples/fft/2837x_cla_rfft_2024/rfft_1024_data_out1.h
fileID = fopen('../examples/fft/2837x_cla_rfft_1024/rfft_1024_data_out1.h','w');
fprintf(fileID,'// 1024 RFFT Data Output 1\n');
So1 = fprintf(fileID, '%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', C')
fclose(fileID);

%% 1024 RFFT - data in/out 2
n = 0 : 1023;
f0 = 1000; f1 = 2000; 
fs = 10240;
I = sin(2*pi.*n*f0/fs) + sin(2*pi.*n*f0/fs);
Q = zeros(1, length(I));
A = I + j*Q;
delete ../examples/fft/2837x_cla_rfft_1024/rfft_1024_data_in2.h
fileID = fopen('../examples/fft/2837x_cla_rfft_1024/rfft_1024_data_in2.h','w')
fprintf(fileID,'// 1024 RFFT Data Input 2\n');
Si1 = fprintf(fileID,'%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', I)
fclose(fileID);
D = fft(A);
f = fs/2*linspace(0,1,1024);
%plot(f, abs(D))
I = real(D);
Q = imag(D);
B = [I; Q]';
C = reshape(B', 8, 2048/8)';
delete ../examples/fft/2837x_cla_rfft_2024/rfft_1024_data_out2.h
fileID = fopen('../examples/fft/2837x_cla_rfft_1024/rfft_1024_data_out2.h','w');
fprintf(fileID,'// 1024 RFFT Data Output 2\n');
So1 = fprintf(fileID, '%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', C')
fclose(fileID);

%% 1024 RFFT - data in/out 3
n = 0 : 1023;
f0 = 1570; f1 = 2500; f2 = 3500;
fs = 10240;
I = sin(2*pi.*n*f0/fs) + sin(2*pi.*n*f1/fs) + sin(2*pi.*n*f2/fs);
Q = zeros(1, length(I));
A = I + j*Q;
delete ../examples/fft/2837x_cla_rfft_1024/rfft_1024_data_in3.h
fileID = fopen('../examples/fft/2837x_cla_rfft_1024/rfft_1024_data_in3.h','w')
fprintf(fileID,'// 1024 RFFT Data Input 3\n');
Si1 = fprintf(fileID,'%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', I)
fclose(fileID);
D = fft(A);
f = fs/2*linspace(0,1,1024);
%plot(f, abs(D))
I = real(D);
Q = imag(D);
B = [I; Q]';
C = reshape(B', 8, 2048/8)';
delete ../examples/fft/2837x_cla_rfft_2024/rfft_1024_data_out3.h
fileID = fopen('../examples/fft/2837x_cla_rfft_1024/rfft_1024_data_out3.h','w');
fprintf(fileID,'// 1024 RFFT Data Output 3\n');
So1 = fprintf(fileID, '%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', C')
fclose(fileID);

%% 1024 RFFT - data in/out 4
n = 0 : 1023;
f0 = 1300; f1 = 2200; f2 = 3700;
fs = 10240;
I = sin(2*pi.*n*f0/fs) + sin(2*pi.*n*f1/fs) + sin(2*pi.*n*f2/fs);
Q = zeros(1, length(I));
A = I + j*Q;
delete ../examples/fft/2837x_cla_rfft_1024/rfft_1024_data_in4.h
fileID = fopen('../examples/fft/2837x_cla_rfft_1024/rfft_1024_data_in4.h','w')
fprintf(fileID,'// 1024 RFFT Data Input 4\n');
Si1 = fprintf(fileID,'%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', I)
fclose(fileID);
D = fft(A);
f = fs/2*linspace(0,1,1024);
%plot(f, abs(D))
I = real(D);
Q = imag(D);
B = [I; Q]';
C = reshape(B', 8, 2048/8)';
delete ../examples/fft/2837x_cla_rfft_2024/rfft_1024_data_out4.h
fileID = fopen('../examples/fft/2837x_cla_rfft_1024/rfft_1024_data_out4.h','w');
fprintf(fileID,'// 1024 RFFT Data Output 4\n');
So1 = fprintf(fileID, '%12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, %12.8f, \n', C')
fclose(fileID);
