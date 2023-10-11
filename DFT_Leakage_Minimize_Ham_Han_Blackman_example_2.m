
%% DFT Leakage Minimization (filtering) using Hamming window function
clc;    clear;   close all;
   Fs = 64000;                  % Sampling frequency (24KHz)
   ts = 1/Fs;     % seconds
   DFT_points = 64;      N = DFT_points;
     a = 8;   Fc_1 = 3300;   b = 6;   Fc_2 = 3700;
     ind = 1;   x = [];
    for n = 1:DFT_points
        m = n-1;
        x1(ind) = a*sin(2*pi*Fc_1*m*ts);
        x2(ind) = b*sin(2*pi*Fc_2*m*ts);
        ind = ind + 1;
    end
    x_comb = x1 + x2;     
    t = 1:DFT_points;
% Plot first N discrete values of x_comb signal:
   figure(1);   plot(t,x_comb,'b--o');   grid on;
   xlabel('Time (millisecond)');     ylabel('Signal amplitude')
   title('x_comb signal versus time');   zoom xon;
   
%% DFT of x_comb (using exponential equation):
Dft_x_comb = zeros(N,1);     
% Dft_x_comb = dft(x_comb, N);
[Dft_x_comb, Dft_x_comb_mag, Dft_x_comb_deg] = dft_mag_ang(x_comb, N);

mf = 0:DFT_points-1;
figure(2); 
stem(mf,Dft_x_comb_mag,'LineStyle','-',...
     'MarkerSize',15,'Marker','s',...
     'MarkerFaceColor','black',...
     'MarkerEdgeColor','green')
grid on;
title('Magnitude of Dft_x_comb')
xlabel('Frequency m (KHz)')
ylabel('Magnitude')

%% Filtering using Hamming Window
w_Hamming = zeros(N,1);
for ii = 1:DFT_points
    n = ii - 1;
    w_Hamming(ii,1) = 0.54 - 0.46*cos(2*pi*(n/(N-1)));      %Define Hamming window function
end

figure(3);
stem(t,w_Hamming); grid on;
title('Hamming Window');  xlabel('n');  ylabel('w')
x_sig = x_comb';
x_Hamming = x_sig.*w_Hamming;               % Multiplication of Hamming Window and sin function: x_comb

figure(4)
stem(t,x_Hamming); grid on;
title('Multiplication of Hamming Window and sin function');
xlabel('Time');  ylabel('Amplitude')
x_sig_Hamming = x_Hamming';
%  Xdft_Hamming = dft(x_sig_Hamming, N);     
[Xdft_Hamming, Xdft_Hamming_mag, Xdft_Hamming_deg] = dft_mag_ang(x_sig_Hamming, N);     % DFT of x_sig_Hamming
 
figure(5); 
stem(mf,Xdft_Hamming_mag,'LineStyle','-',...
     'MarkerSize',15,'Marker','s',...
     'MarkerFaceColor','black',...
     'MarkerEdgeColor','green')
grid on;
title('Magnitude of Xdft_Hamming')
xlabel('Frequency m (KHz)')
ylabel('Magnitude')


%% Filtering using Hanning Window
w_Hanning = zeros(N,1);
for ii = 1:DFT_points
    n = ii - 1;
    w_Hanning(ii,1) = 0.5 - 0.5*cos(2*pi*(n/(N-1)));      %Define Hanning window function
end

figure(6);
stem(t,w_Hanning); grid on;
title('Hanning Window');  xlabel('n');  ylabel('w')
x_sig = x_comb';
x_Hanning = x_sig.*w_Hanning;               % Multiplication of Hanning Window and sin function: x_comb

figure(7)
stem(t,x_Hanning); grid on;
title('Multiplication of Hanning Window and sin function');
xlabel('Time');  ylabel('Amplitude')
x_sig_Hanning = x_Hanning';
%  X_dft_Hanning = dft(x_sig_Hanning, N);     
[Xdft_Hanning, Xdft_Hanning_mag, Xdft_Hanning_deg] = dft_mag_ang(x_sig_Hanning, N);   % DFT of x_sig_Hanning
 
figure(8); 
stem(mf,Xdft_Hanning_mag,'LineStyle','-',...
     'MarkerSize',15,'Marker','s',...
     'MarkerFaceColor','black',...
     'MarkerEdgeColor','green')
grid on;
title('Magnitude of Xdft_Hanning')
xlabel('Frequency m (KHz)')
ylabel('Magnitude')


%% Filtering using Blackman Window
w_Blackman = zeros(N,1);
for ii = 1:DFT_points
    n = ii - 1;
    w_Blackman(ii,1) = 0.42 - (0.5*cos(2*pi*(n/(N-1)))) + (0.08*cos(4*pi*(n/(N-1))));      %Define Blackman window function
end

figure(9);
stem(t,w_Blackman); grid on;
title('Blackman Window');  xlabel('n');  ylabel('w')
x_sig = x_comb';
x_Blackman = x_sig.*w_Blackman;               % Multiplication of Blackman Window and sin function: x_comb

figure(10)
stem(t,x_Blackman); grid on;
title('Multiplication of Blackman Window and sin function');
xlabel('Time');  ylabel('Amplitude')
x_sig_Blackman = x_Blackman';
%  X_dft_Blackman = dft(x_sig_Blackman, N);     
[Xdft_Blackman, Xdft_Blackman_mag, Xdft_Blackman_deg] = dft_mag_ang(x_sig_Blackman, N);   % DFT of x_sig_Blackman
 
 figure(11); 
stem(mf,Xdft_Blackman_mag,'LineStyle','-',...
     'MarkerSize',15,'Marker','s',...
     'MarkerFaceColor','black',...
     'MarkerEdgeColor','green')
grid on;
title('Magnitude of Xdft_Blackman')
xlabel('Frequency m (KHz)')
ylabel('Magnitude')
 
% Ploting DFT outputs combined in one plot
figure(12); 
plot(mf,Dft_x_comb_mag,'k--o');   grid on;    hold on;
plot(mf,Xdft_Hamming_mag,'b--o');    hold on;  
plot(mf,Xdft_Hanning_mag,'r--s');    hold on;  
plot(mf,Xdft_Blackman_mag,'c--o');

% stem(mf,Dft_x_comb_mag,'LineStyle','-',...
%      'MarkerSize',15,'Marker','s',...
%      'MarkerFaceColor','black',...
%      'MarkerEdgeColor','green')
% hold on;   grid on;
% stem(mf,Xdft_Hamming_mag,'LineStyle','-',...
%      'MarkerSize',15,'Marker','s',...
%      'MarkerFaceColor','blue',...
%      'MarkerEdgeColor','green')
% hold on;
% stem(mf,Xdft_Hanning_mag,'LineStyle','-',...
%      'MarkerSize',15,'Marker','s',...
%      'MarkerFaceColor','Red',...
%      'MarkerEdgeColor','green')
% hold on;
% stem(mf,Xdft_Blackman_mag,'LineStyle','-',...
%      'MarkerSize',15,'Marker','s',...
%      'MarkerFaceColor','Cyan',...
%      'MarkerEdgeColor','green')
xlabel('Frequency m(KHz)'); ylabel('Magnitude of Frequency Bins');
title('Magnitude of DFTs(Filtered by Hamming, Hanning and Blackman Windows)');
legend('Rectangular Window','Hamming Window','Hanning Window','Blackman Window','location','north');

