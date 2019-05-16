clear all
%% Przygotowanie danych
% Obiekt regulacji i jego modele
Gs  = [... % Model w postaci transmitancji ci¹g³ej
    tf(5,[.14,1]),tf(1,[.10,1]);...
    tf(1,[.06,1]),tf(2,[.08,1]);...
];
Gz = c2d(Gs,.1); % Dyskretyzacja transmitancji ci¹g³ej

ny = 2; nu = 2; D = 5;
for m=1:2 % Wyznaczenie parametrów modelu ARX
    tmpa = conv(Gz.Denominator{m,1},Gz.Denominator{m,2});
    GPC_a(m,:) = tmpa(2:end);
    tmpb = conv(Gz.Numerator{m,1},Gz.Denominator{m,2});
    GPC_b(m,1,:) = [tmpb(2:end) 0]; 
    tmpb = conv(Gz.Numerator{m,2},Gz.Denominator{m,1});
    GPC_b(m,2,:) = [tmpb(2:end) 0];
end

S = zeros(ny,nu,D);
for k = 1:size(S,3)
    % symulacja obiektu regulacji
    for m=1:ny
        for n=1:nu
            for i=1:min(k,size(GPC_b,3))
                S(m,n,k) = S(m,n,k) + GPC_b(m,n,i)*1;
            end
            for i=1:min(k-1,size(GPC_a,2))
                S(m,n,k) = S(m,n,k) - GPC_a(m,i)*S(m,n,k-i);
            end         
        end   
    end 
end
S(:,:,2:end+1) = S(:,:,1:end);
S(:,:,1) = S(:,:,1)*0; 

% Parametry algorytmu regulacji
N  = 5; % Horyzont predykcji
Nu = 5; % Horyzont sterowania
lambda= [1.0 1.0]; % Penalty--control signals' incr.
psi   = [1.0 1.0]; % Penalty--control errors
dumin =-[.01 .01]; % Lower bound--control increments
dumax = [.01 .01]; % Upper bound--control increments
umin  =-[1.0 1.0]; % Lower bound--control signal
umax  = [1.0 1.0]; % Upper bound--control signal

T = 0.1;
K =  [4.5 4.5];
Ti = [0.5 0.5];
Td = [0.0 0.1];

code = AutoMATiC_Generate('AutoMATiC_PID_Algorithm_s','controller');
%code = AutoMATiC_Generate('AutoMATiC_DMC_Analytic_Algorithm','controller');
%code = AutoMATiC_Generate('AutoMATiC_DMC_Numeric_Algorithm','controller');
%code = AutoMATiC_Generate('AutoMATiC_GPC_Analytic_Algorithm','controller');
%code = AutoMATiC_Generate('AutoMATiC_GPC_Numeric_Algorithm','controller');


% lambda = 0.01; % Wspó³czynnik kary za przyrosty sterowañ
% dumin = -0.1; % Ograniczenie na minimalny przyrost sterowania
% dumax =  0.1; % Ograniczenie na maksymalny przyrost sterowania
% code = AutoMATiC_Generate('AutoMATiC_DMC_Numeric_Algorithm','controller2',0);
% %code = AutoMATiC_Generate('AutoMATiC_GPC_Analytic_Algorithm','controller');
% %code = AutoMATiC_Generate('AutoMATiC_GPC_Numeric_Algorithm','controller');