clearvars -except MPC_CROSSCOMPILER
warning off

if(~exist('MPC_CROSSCOMPILER','var'))
    NO_CROSSCOMPILER = 1;
    addpath('..\\Libs\\MATLAB\\');
else
    NO_CROSSCOMPILER = 0;
end

alg = 'AutoMATiC_DMC_Numeric_Algorithm';
%% Przygotowanie danych
control_value = zeros(2,1); % tutaj przechowywane s¹ nowe przyrosty sterowañ

INIT = 1;
kp = 100; kk = 1000;    % Czas startu i koñca eksperymentu
nu = 2; ny = 2; nx = 2; % Wymiarowoœæ zadania
AD_Y    = zeros(kk,ny); % Macierze i wektory
AD_U    = zeros(kk,nu); % do przechowywania
AD_X    = zeros(kk,nx); % danych na temat
AD_DU   = zeros(kk,nu); % procesu regulacji
AD_Z    = zeros(1,2);   % i samej regulacji

%% Obiekt regulacji i jego modele
KS = [1,.1;.02,.9]; % Macierz wzmocnieñ statycznych
Gs  = [... % Model w postaci transmitancji ci¹g³ej
    tf(KS(1,1),[1,1]), tf(KS(1,2),[1,1]);...
    tf(KS(2,1),[1,1]), tf(KS(2,2),[1,1]);...
];
SSs = ss([-1,0;0,-1],KS,[1,0;0,1],[0,0;0,0]); % Model w przestrzeni stanów
Gz = c2d(Gs,1); % Dyskretyzacja transmitancji ci¹g³ej
SSz = c2d(SSs,1); % Dyskretyzacja modelu w przestrzeni stanów
Stmp = step(Gz);      % OdpowiedŸ skokowa
S = shiftdim(Stmp,1); % Przekszta³cenie do wygodniejszej postaci
DMC_S=S(:,:,2:end);   % Pozbycie siê pierwszego elementu
for m=1:ny % Wyznaczenie parametrów modelu ARX
    tmpa = conv(Gz.Denominator{m,1},Gz.Denominator{m,2});
    GPC_a(m,:) = tmpa(2:end);
    tmpb = conv(Gz.Numerator{m,1},Gz.Denominator{m,2});
    GPC_b(m,1,:) = tmpb(1:end);
    tmpb = conv(Gz.Numerator{m,2},Gz.Denominator{m,1});
    GPC_b(m,2,:) = tmpb(1:end);
end

%% Parametry algorytmu regulacji
N  = 10; % Horyzont predykcji
Nu = 10; % Horyzont sterowania
lambda = 1.0; % Wspó³czynnik kary za przyrosty sterowañ
psi = 1.0; % Wspó³czynnik kary za uchyb regulacji
dumin = -0.10; % Ograniczenie na minimalny przyrost sterowania
dumax =  0.10; % Ograniczenie na maksymalny przyrost sterowania
umin  = -4.00; % Ograniczenie na minimaln¹ wartoœæ sterowania
umax  =  4.00; % Ograniczenie na maksymaln¹ wartoœæ sterowania

run(alg); % Uruchomienie inicjalizuj¹ce algorytm

%% Inicjalizacja procesu regulacji
Zpp = [0;0]; % Domyœlna wartoœæ zadana
Xpp = [0;0]; % Stan w punkcie pracy (nie wyznaczony)
Upp = [1;1]; % Sterowanie w punkcie pracy
for AD_K = 1:kk % Wyznaczenie stanu w punkcie pracy
    Xpp = SSz.A*Xpp+SSz.B*Upp;
end
Ypp = SSz.C*Xpp; % Wyznaczenie sterowania w punkcie pracy
simT = (1:kk)'; % Czas dyskretny regulacji
simU = ones(kk,1)*Upp'; % Trajektoria sygna³u steruj¹cego
simY = ones(kk,1)*Ypp'; % Trajektoria sygna³u wyjœciowego
simZ = ones(kk,1)*Zpp'; % Trajektoria sygna³u zadanego
for AD_K = 1:(kp-1) % Inicjalizacja pocz¹tkowych wartoœci trajektorii
    AD_Y(AD_K,:) = Ypp;
    AD_U(AD_K,:) = Upp;
    AD_X(AD_K,:) = Xpp;
end

%% Symulacja
if(NO_CROSSCOMPILER)
    for AD_K = kp:kk
        % Symulacja z wykorzystaniem dyskretnych równañ stanu
        AD_X(AD_K,:) = (SSz.A*AD_X(AD_K-1,:)'+SSz.B*AD_U(AD_K-1,:)')';
        AD_Y(AD_K,:) = (SSz.C*AD_X(AD_K-1,:)'+SSz.D*AD_U(AD_K-1,:)')';

        % Okreœlenie wartoœci zadanej
        if    (AD_K<= 200); AD_Z = [0.0, 0.0];
        elseif(AD_K<= 400); AD_Z = [0.0, 0.4];
        elseif(AD_K<= 600); AD_Z = [0.1, 0.4];
        elseif(AD_K<= 800); AD_Z = [0.1, 0.2];
        elseif(AD_K<=1000); AD_Z = [0.5, 0.2];
        end

        % Algorytm regulacji
        run(alg);

        % Zapis nowej wartoœci przyrosti sterowania (control_value)
        AD_DU(AD_K,:) = control_value';              
        % Zapis nowej wartoœci sterowania
        AD_U (AD_K,:) = AD_U(AD_K-1,:)+AD_DU(AD_K,:);

        % Zapis danych do póŸniejszych prezentacji
        simT(AD_K) = AD_K;
        simU(AD_K,:) = AD_U(AD_K,:);
        simY(AD_K,:) = AD_Y(AD_K,:);
        simZ(AD_K,:) = AD_Z(:);
    end
end

% Wyœwietlenie przebiegu eksperymentu
if(NO_CROSSCOMPILER)
    plot_result(simT,simY,simZ,simU)
end

% Wygenerowanie algorytmu regulacji w jêzyku C (dodatkowo kod zapisany jest
% do zmiennej ,,code'' na potrzeby jego skopiowania w dodatkowe miejsce
if(~NO_CROSSCOMPILER)
    funname = 'controller';
    code = AutoMATiC_Generate(alg,funname);
    fprintf('[MATLAB] Generated algorithm ''%s'', to a function called ''%s''\n',alg,funname);
else
    fprintf('[MATLAB] Did not generate anything\n');
end

% Kompilacja programu testuj¹cego wygenerowany algorytm regulacji
if(NO_CROSSCOMPILER)
    %fd=fopen('./controller.cinclude','w');
    %fprintf(fd,code);
    %fclose(fd);
    %!mex -v -client engine ./*.c -output test.exe
end

% Uruchomienie programu testuj¹cego wygenerowany algorytm regulacji
if(NO_CROSSCOMPILER)
    %!test.exe
end

% Wyœwietlenie danych z przebiegu regulacji -- 
%     -- (program w C zapisuje dane do data.csv)
if(NO_CROSSCOMPILER)
    data = csvread('data.csv',1);
    simT = data(:,1);
    simZ = data(:,2:3);
    simY = data(:,4:5);
    simU = data(:,6:7);
    Empty = data(:,8);
    plot_result(simT,simY,simZ,simU);
end

function plot_result(simT,simY,simZ,simU)
%% Funkcja wyœwietlaj¹ca przebieg regulacji na jednej figurze podzielonej 
%% w poziomie na górny wykres (wyjœcie Y i wartoœæ zadana Z w czasie T), 
%% oraz na dolny wykres (wartoœæ sterowania U w czasie T)
    figure;
    subplot(2,1,1);
    plot(simT,simY);
    hold on;
    stairs(simT,simZ,'--');
    grid;
    title('Wyjœcie');

    subplot(2,1,2);
    stairs(simT,simU);
    grid;
    ylim([-2 2]);
    title('Sterowanie');
end


