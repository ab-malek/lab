%% DFT using exponential form equation:
function [X_exp, Xe_mag, Xe_ang_deg] = dft_mag_ang(x, N)
    X_exp = zeros(N,1);     Xe_real = zeros(N,1);     Xe_imag = zeros(N,1);
    Xe_mag = zeros(N,1);    j = sqrt(-1);
    Xe_ang_deg = zeros(N,1);
    
    for m = 1:N
        X_1 = zeros(N,1);   m_e = m - 1;
        for ii = 1:N
            n = ii-1;   X_p1 = [];   
            X_p1 = x(1,ii)*exp((-j*2*pi*n*m_e)/N);                    
            X_1(ii,1) = X_p1;  
        end
        X_exp(m,1) = sum(X_1(:,1));     % DFT output
        
        Xe_real(m,1) = real(X_exp(m,1));
            if Xe_real(m,1) > 0 && Xe_real(m,1) < 1e-10
               Xe_real(m,1) = 0;  
            end  
            if Xe_real(m,1) < 0 && Xe_real(m,1) > -1e-10
               Xe_real(m,1) = 0;  
            end
        Xe_imag(m,1) = imag(X_exp(m,1));
            if Xe_imag(m,1) > 0 && Xe_imag(m,1) < 1e-10
               Xe_imag(m,1) = 0;  
            end  
            if Xe_imag(m,1) < 0 && Xe_imag(m,1) > -1e-10
               Xe_imag(m,1) = 0;  
            end
        Xe_mag(m,1) = sqrt(Xe_real(m,1).^2 + Xe_imag(m,1).^2);    % DFT output magnitude
        Xe_ang_rad(m,1) = atan(Xe_imag(m,1)/Xe_real(m,1));     Xe_ang_rad(isnan(Xe_ang_rad)) = 0;
        Xe_ang_deg(m,1) = (180/3.14159)*Xe_ang_rad(m,1);          % DFT output phase in degree
        
    end   
end

