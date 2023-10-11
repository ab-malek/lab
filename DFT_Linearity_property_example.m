
%% DFT Linearity: The DFT of the sum of two signals is equal to the sum of the transforms of each signal
clc;    clear;   close all;
   Fs = 16000;      % Sampling frequency (16KHz)
   ts = 1/Fs;       % seconds
   DFT_points = 16;      N = DFT_points;
     a = 4;   Fc_1 = 1000;   b = 7;   Fc_2 = 3000;
     ind = 1;   x = [];
    for n = 1:DFT_points
        m = n-1;
        x1(ind) = a*sin(2*pi*Fc_1*m*ts);
        x2(ind) = b*sin(2*pi*Fc_2*m*ts);
        ind = ind + 1;
    end
    x_comb = x1 + x2;     
    
    t = 1:DFT_points;

% Plot first N discrete values of x1 signal:
   figure(1);   plot(t,x1,'k--o');   grid on;
   xlabel('Time (millisecond)');     ylabel('Signal amplitude')
   title('x1 signal versus time');   zoom xon;

% Plot first N discrete values of x2 signal:
   figure(2);   plot(t,x2,'r--o');   grid on;
   xlabel('Time (millisecond)');     ylabel('Signal amplitude')
   title('x2 signal versus time');   zoom xon;
   
% Plot first N discrete values of x_comb signal:

   figure(3);   plot(t,x_comb,'b--o');   grid on;
   xlabel('Time (millisecond)');     ylabel('Signal amplitude')
   title('x_comb signal versus time');   zoom xon;

%% DFT of x_seq1 (using exponential equation):
Dft_x1 = zeros(N,1);     
% [X_exp, Xe_mag, Xe_ang_deg] = dft_mag_ang(x, N)
[Dft_x1, Dft_x1_mag, Dft_x1_deg]  = dft_mag_ang(x1, N);
   
%% DFT of x_seq2 (using exponential equation):
Dft_x2 = zeros(N,1);     
% Dft_x2 = dft(x2, N);   
[Dft_x2, Dft_x2_mag, Dft_x2_deg]  = dft_mag_ang(x2, N);
   
%% DFT of x_comb (using exponential equation):
Dft_x_comb = zeros(N,1);     
% Dft_x_comb = dft(x_comb, N);
[Dft_x_comb, Dft_x_comb_mag, Dft_x_comb_deg]  = dft_mag_ang(x_comb, N);
% Combine the DFT outputs of x1 and x2:
DFTsum_x1x2 = Dft_x1 + Dft_x2;
%
DFTsum_x1x2_mag = Dft_x1_mag + Dft_x2_mag;
mf = 0:DFT_points-1;
figure(4); 
stem(mf,Dft_x_comb_mag,'LineStyle','--',...
     'MarkerSize',15,'Marker','s',...
     'MarkerFaceColor','black',...
     'MarkerEdgeColor','green')
grid on;
title('Magnitude of Dft_x_comb')
xlabel('m (KHz)')
ylabel('Magnitude')

figure(5); 
stem(mf,DFTsum_x1x2_mag,'LineStyle','--',...
     'MarkerSize',15,'Marker','s',...
     'MarkerFaceColor','blue',...
     'MarkerEdgeColor','green')
grid on;
title('Magnitude of DFTsum_x1x2')
xlabel('m (KHz)')
ylabel('Magnitude')


% Verify DFT Linearity property: 
DFT_Linearity_error = max(abs(DFTsum_x1x2 - Dft_x_comb));
    if DFT_Linearity_error < 1e-9
       'DFT_Linearity_is_proved'  
    end  
    





   