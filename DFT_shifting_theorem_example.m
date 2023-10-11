
%% A DFT shifting theorem example (using exponential form of DFT equation)
clc;   clear;   close all;

DFT_points = 8;      j = sqrt(-1);
N = DFT_points;   % Total number of samples of input sequence- x; total number of frequency points in the DFT output  
k = 3;            % Amount of shift in Time-domain signal  
Fs = 8e3;         % Sampling frequency 8KHz
ts = 1/Fs;
ind = 1;   x = [];
for n = 1:N+k
    m = n-1;
    x(ind) = sin(2*pi*1000*m*ts)+0.5*sin(2*pi*2000*m*ts+(3*pi/4));
    ind = ind + 1;
end

t = 1:N;
% Plot first N discrete values of x_1 signal:
   figure(1);   plot(t,x(1,1:N),'k--o');   grid on;
   xlabel('Time (millisecond)');     ylabel('Signal amplitude')
   title('x1 discrete-time signal');   zoom xon;
   
% Plot first N discrete values of x_2 signal:
   figure(2);   plot(t,x(4:N+k),'b--o');   grid on;
   xlabel('Time (millisecond)');     ylabel('Signal amplitude')
   title('x2 discrete-time signal');   zoom xon;

x1 = x(1,1:N); 
x2 = x(1,1+k:end);            % time sequence shifted by k samples
   
f_analysis_1m = (1*Fs)/N;      % DFT analysis frequency for m=1
X1_dft = zeros(N,1);
X1_mag = zeros(N,1);      X1_deg = zeros(N,1);

[X1_dft, X1_mag, X1_deg] = dft_mag_ang(x1, N);

X_shifted_mag = zeros(N,1);     X_shifted_deg = zeros(N,1);   
[X_shifted_dft, X_shifted_mag, X_shifted_deg]  = dft_mag_ang(x2, N);

% m = 1;
X_dft_k = zeros(N,1);
Xe_real = zeros(N,1);      Xe_imag = zeros(N,1);    
Xe_ang_rad = zeros(N,1);   Xe_ang_deg_k = zeros(N,1);

for m = 1:N
    m_e = m-1;
    X_dft_k(m,1) = exp((j*2*pi*k*m_e)/N)*X1_dft(m,1);
    
    Xe_real(m,1) = real(X_dft_k(m,1));
            if Xe_real(m,1) > 0 && Xe_real(m,1) < 1e-10
               Xe_real(m,1) = 0;  
            end  
            if Xe_real(m,1) < 0 && Xe_real(m,1) > -1e-10
               Xe_real(m,1) = 0;  
            end
        Xe_imag(m,1) = imag(X_dft_k(m,1));
            if Xe_imag(m,1) > 0 && Xe_imag(m,1) < 1e-10
               Xe_imag(m,1) = 0;  
            end  
            if Xe_imag(m,1) < 0 && Xe_imag(m,1) > -1e-10
               Xe_imag(m,1) = 0;  
            end
        X_dft_k_mag(m,1) = sqrt(Xe_real(m,1).^2 + Xe_imag(m,1).^2);
        Xe_ang_rad(m,1) = atan(Xe_imag(m,1)/Xe_real(m,1));     Xe_ang_rad(isnan(Xe_ang_rad)) = 0;
        Xe_ang_deg_k(m,1) = (180/3.14159)*Xe_ang_rad(m,1); 
       
end


mf = 0:DFT_points-1;

figure(3); 
stem(mf,X1_mag,'LineStyle','--',...
     'MarkerSize',15,'Marker','s',...
     'MarkerFaceColor','black',...
     'MarkerEdgeColor','green')
grid on;
title('Magnitude of X1_dft(m)')
xlabel('m (KHz)')
ylabel('Magnitude')

figure(4); 
stem(mf,X_shifted_mag,'LineStyle','--',...
     'MarkerSize',15,'Marker','s',...
     'MarkerFaceColor','black',...
     'MarkerEdgeColor','green')
grid on;
title('Magnitude of X_shifted(m)')
xlabel('m (KHz)')
ylabel('Magnitude')

figure(5); 
stem(mf,X_dft_k_mag,'LineStyle','--',...
     'MarkerSize',15,'Marker','s',...
     'MarkerFaceColor','blue',...
     'MarkerEdgeColor','green')
grid on;
title('Magnitude of X_dft_k(m)')
xlabel('m (KHz)')
ylabel('Magnitude')

figure(6); 
stem(mf,X1_deg,'LineStyle','--',...
     'MarkerSize',15,'Marker','s',...
     'MarkerFaceColor','cyan',...
     'MarkerEdgeColor','green')
grid on;
title('Phase angle of X1_dft')
xlabel('m (KHz)')
ylabel('Degree')

figure(7); 
stem(mf,X_shifted_deg,'LineStyle','--',...
     'MarkerSize',15,'Marker','s',...
     'MarkerFaceColor','black',...
     'MarkerEdgeColor','green')
grid on;
title('Phase angle of X_shifted')
xlabel('m (KHz)')
ylabel('Degree')

figure(8); 
stem(mf,Xe_ang_deg_k,'LineStyle','--',...
     'MarkerSize',15,'Marker','s',...
     'MarkerFaceColor','blue',...
     'MarkerEdgeColor','green')
grid on;
title('Phase angle of X_dft_k')
xlabel('m (KHz)')
ylabel('Degree')

% Verify DFT shifting property: 
DFT_Magnitude_error = max(abs(X_shifted_mag - X1_mag));
    if DFT_Magnitude_error < 1e-9
       'DFT magnitudes of X1_dft and X_shifted_dft are same'  
    end



















