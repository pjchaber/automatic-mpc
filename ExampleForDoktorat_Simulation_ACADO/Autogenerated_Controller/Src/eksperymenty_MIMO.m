clear all
%% Przygotowanie danych
% Obiekt regulacji i jego modele
Gs  = [... % Model w postaci transmitancji ci¹g³ej
    tf(1,[.1,1]),0;...
    0,tf(1,[.1,1]);...
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
offset = 2;
for k=(size(S,3):-1:1)+offset
    for m=1:ny
        for n=1:nu
            S(m,n,k)=S(m,n,k-offset);
        end
    end
end
for k=offset:-1:1
    for m=1:ny
        for n=1:nu
            S(m,n,k)=0;
        end
    end
end
    

% Parametry algorytmu regulacji
N  = 5; % Horyzont predykcji
Nu = 5; % Horyzont sterowania
lambda = 1.0; % Wspó³czynnik kary za przyrosty sterowañ
psi = 1.0; % Wspó³czynnik kary za uchyb regulacji
dumin = -0.01; % Ograniczenie na minimalny przyrost sterowania
dumax =  0.01; % Ograniczenie na maksymalny przyrost sterowania
umin  = -1.00; % Ograniczenie na minimaln¹ wartoœæ sterowania
umax  =  1.00; % Ograniczenie na maksymaln¹ wartoœæ sterowania

code = AutoMATiC_Generate('AutoMATiC_DMC_Analytic_Algorithm','controller',1);

dumin = -0.1; % Ograniczenie na minimalny przyrost sterowania
dumax =  0.1; % Ograniczenie na maksymalny przyrost sterowania
lambda = .01; % Wspó³czynnik kary za przyrosty sterowañ
code = AutoMATiC_Generate('AutoMATiC_DMC_Numeric_Algorithm','controller_fast',0);
%code = AutoMATiC_Generate('AutoMATiC_GPC_Analytic_Algorithm','controller');
%code = AutoMATiC_Generate('AutoMATiC_GPC_Numeric_Algorithm','controller');