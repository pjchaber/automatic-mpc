clear all
addpath('..\\Libs\\MATLAB\\');
%% Przygotowanie danych
% Obiekt regulacji i jego modele
% Gs  = [... % Model w postaci transmitancji ci¹g³ej
%     tf(1,[.1,1]),0;...
%     0,tf(1,[.1,1]);...
% ]; % Transmitancja u¿yta w doktoracie
Gs  = [... % Model w postaci transmitancji ci¹g³ej
    tf(5,[.014,1]),tf(1,[.010,1]);...
    tf(1,[.006,1]),tf(2,[.008,1]);...
]; % Transmitancja na potrzeby artyku³u
Gz = c2d(Gs,.1); % Dyskretyzacja transmitancji ci¹g³ej

for m=1:2 % Wyznaczenie parametrów modelu ARX
    tmpa = conv(Gz.Denominator{m,1},Gz.Denominator{m,2});
    GPC_a(m,:) = tmpa(2:end);
    tmpb = conv(Gz.Numerator{m,1},Gz.Denominator{m,2});
    GPC_b(m,1,:) = [tmpb(2:end) 0.0000001];
    tmpb = conv(Gz.Numerator{m,2},Gz.Denominator{m,1});
    GPC_b(m,2,:) = [tmpb(2:end) 0.0000001];
end

% Parametry algorytmu regulacji
N  = 10; % Horyzont predykcji
Nu = 10; % Horyzont sterowania
lambda = 1.0; % Wspó³czynnik kary za przyrosty sterowañ
psi = 1.0; % Wspó³czynnik kary za uchyb regulacji
dumin = -0.10; % Ograniczenie na minimalny przyrost sterowania
dumax =  0.10; % Ograniczenie na maksymalny przyrost sterowania
umin  =  0.00; % Ograniczenie na minimaln¹ wartoœæ sterowania
umax  =  4.00; % Ograniczenie na maksymaln¹ wartoœæ sterowania
INIT=1;
AutoMATiC_GPC_Analytic_Algorithm

codea = AutoMATiC_Generate('AutoMATiC_GPC_Analytic_Algorithm','controllera');
% coden = AutoMATiC_Generate('AutoMATiC_GPC_Numeric_Algorithm','controllern');