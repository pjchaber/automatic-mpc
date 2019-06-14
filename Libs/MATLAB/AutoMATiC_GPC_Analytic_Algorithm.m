%%
% This file is part of AutoMATiC.
% AutoMATiC -- Automatic code generation based on the MATLAB and 
% C languages.
% 
% Copytight (C) 2018-2019 by Patryk Chaber. Developed within the 
% Warsaw University of Technology, Institute of Control and 
% Computation Engineering under supervision of Maciej Lawrynczuk. 
% All rights reserved.
% 
% AutoMATiC is free software: you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation; either version 3 of the License, or
% (at your option) any later version.
% 
% AutoMATiC is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU General Public License for more details.
% 
% You should have received a copy of the GNU General Public License
% along with AutoMATiC.  If not, see <https://www.gnu.org/licenses/>.
%

%% DOCUMENTATION
% This algorithm calculates the control signal as constant. This constant
% may be different for each control signal. To get control value of 2 for
% first contol signal and 10 for second one, "control_value" variable must
% be defined as follows
%
% control_value = [2;10];
%
%--------------------------------------------------------------------------
% Author: Patryk Chaber
% Date:   19.04.2018
%--------------------------------------------------------------------------

%% CHECKING FOR REQUIRED VARIABLES
CHECK_FOR_VARIABLE AD_Y define% GENERAL REQUIREMENT
CHECK_FOR_VARIABLE AD_U define% GENERAL REQUIREMENT
CHECK_FOR_VARIABLE AD_DU define% GENERAL REQUIREMENT
CHECK_FOR_VARIABLE AD_Z define% GENERAL REQUIREMENT
CHECK_FOR_VARIABLE control_value define% GENERAL REQUIREMENT

%% INITIALIZE -- variables here cannot be changed further in code
% required: S,N,Nu,lambda,psi
% optional: dumin,dumax,umin,umax
CHECK_FOR_VARIABLE GPC_a error% ALGORITHM SPECIFIC REQUIREMENT
CHECK_FOR_VARIABLE GPC_b error% ALGORITHM SPECIFIC REQUIREMENT

if( INIT == 1 )
    AutoMATiC_GPC_a = GPC_a;
    AutoMATiC_GPC_b = GPC_b;
    AutoMATiC_GPC_na = size(AutoMATiC_GPC_a,2);
    AutoMATiC_GPC_nb = size(AutoMATiC_GPC_b,3);
    AutoMATiC_GPC_ny = size(AutoMATiC_GPC_b,1);
    AutoMATiC_GPC_nu = size(AutoMATiC_GPC_b,2);
    
    AutoMATiC_GPC_pars.N  = N ;
    AutoMATiC_GPC_pars.Nu = Nu;
    AutoMATiC_GPC_pars.a  = AutoMATiC_GPC_a ;
    AutoMATiC_GPC_pars.b  = AutoMATiC_GPC_b ;
    AutoMATiC_GPC_pars.na = AutoMATiC_GPC_na;
    AutoMATiC_GPC_pars.nb = AutoMATiC_GPC_nb;
    AutoMATiC_GPC_pars.nu = AutoMATiC_GPC_nu;
    AutoMATiC_GPC_pars.ny = AutoMATiC_GPC_ny;
    
    % Macierze Lambda oraz Psi -- wagi funkcji kosztów
    if(isrow(lambda)); tmp_lambda = repmat(lambda,1,Nu);
    else             ; tmp_lambda = repmat(lambda,Nu,1);
    end
    if(isrow(psi))   ; tmp_psi = repmat(psi,1,N);
    else             ; tmp_psi = repmat(psi,N,1);
    end
    AutoMATiC_GPC_Lambda = diag(tmp_lambda);
    AutoMATiC_GPC_Psi    = diag(tmp_psi);

    % OdpowiedŸ skokowa
    AutoMATiC_GPC_S = zeros(AutoMATiC_GPC_ny,AutoMATiC_GPC_nu,N);
    for AutoMATiC_GPC_k = 1:size(AutoMATiC_GPC_S,3)
        for AutoMATiC_GPC_m=1:AutoMATiC_GPC_ny
            for AutoMATiC_GPC_n=1:AutoMATiC_GPC_nu
                for AutoMATiC_GPC_i=1:min(AutoMATiC_GPC_k,AutoMATiC_GPC_nb)
                    AutoMATiC_GPC_S(AutoMATiC_GPC_m,AutoMATiC_GPC_n,AutoMATiC_GPC_k) = AutoMATiC_GPC_S(AutoMATiC_GPC_m,AutoMATiC_GPC_n,AutoMATiC_GPC_k) + AutoMATiC_GPC_b(AutoMATiC_GPC_m,AutoMATiC_GPC_n,AutoMATiC_GPC_i)*1;
                end
                for AutoMATiC_GPC_i=1:min(AutoMATiC_GPC_k-1,AutoMATiC_GPC_na)
                    AutoMATiC_GPC_S(AutoMATiC_GPC_m,AutoMATiC_GPC_n,AutoMATiC_GPC_k) = AutoMATiC_GPC_S(AutoMATiC_GPC_m,AutoMATiC_GPC_n,AutoMATiC_GPC_k) - AutoMATiC_GPC_a(AutoMATiC_GPC_m,AutoMATiC_GPC_i)*AutoMATiC_GPC_S(AutoMATiC_GPC_m,AutoMATiC_GPC_n,AutoMATiC_GPC_k-AutoMATiC_GPC_i);
                end         
            end   
        end 
    end

    % Macierz M
    AutoMATiC_GPC_M = cell(N,Nu);
    for AutoMATiC_GPC_row = 1:N
       for AutoMATiC_GPC_col = 1:Nu
            if(AutoMATiC_GPC_row-AutoMATiC_GPC_col+1 >= 1)
                AutoMATiC_GPC_M{AutoMATiC_GPC_row,AutoMATiC_GPC_col} = AutoMATiC_GPC_S(:,:,AutoMATiC_GPC_row-AutoMATiC_GPC_col+1);
            else
                AutoMATiC_GPC_M{AutoMATiC_GPC_row,AutoMATiC_GPC_col} = zeros(size(AutoMATiC_GPC_S(:,:,1)));
            end
       end
    end
    AutoMATiC_GPC_M=cell2mat(AutoMATiC_GPC_M);

    % Macierz K
    AutoMATiC_GPC_K = (AutoMATiC_GPC_M'*AutoMATiC_GPC_Psi*AutoMATiC_GPC_M+AutoMATiC_GPC_Lambda)^(-1)*AutoMATiC_GPC_M'*AutoMATiC_GPC_Psi;

    %% Macierze dla wersji minimalistycznej algorytmu
    AutoMATiC_GPC_Kyzad = zeros(AutoMATiC_GPC_nu,AutoMATiC_GPC_ny);   % r,m
    AutoMATiC_GPC_Ku = zeros(AutoMATiC_GPC_nu,AutoMATiC_GPC_nu,AutoMATiC_GPC_nb);   % r,n,j -> nu x nu x nb
    AutoMATiC_GPC_Ky = zeros(AutoMATiC_GPC_nu,AutoMATiC_GPC_ny,AutoMATiC_GPC_na+1); % r,m,j -> nu x ny x (na+1)
    % r -- numer sygna³u steruj¹cego, którego przyrost jest wyliczany
    % n -- numer sygna³u steruj¹cego
    % m -- numer sygna³u wyjœciowego
    % j -- dynamika sygna³u wejœciowego/wyjœciowego

    % Kolejnoœæ nie jest przypadkowa!
    fun_f(); % czyszczenie pamiêci funkcji f
    fun_g(); % czyszczenie pamiêci funkcji g
    fun_e(); % czyszczenie pamiêci funkcji e
    fun_f(1,1,1,AutoMATiC_GPC_pars);   % inicjalizacja parametrów f
    fun_g(1,1,1,1,AutoMATiC_GPC_pars); % inicjalizacja parametrów g
    fun_e(1,1,1,1,AutoMATiC_GPC_pars); % inicjalizacja parametrów e

    %% Wyznaczanie parametrów Ku, Ky
    for AutoMATiC_GPC_r=1:AutoMATiC_GPC_nu
        for AutoMATiC_GPC_n=1:AutoMATiC_GPC_nu
            for AutoMATiC_GPC_j=1:AutoMATiC_GPC_nb
                for AutoMATiC_GPC_p=1:N
                    for AutoMATiC_GPC_m=1:AutoMATiC_GPC_ny
                        AutoMATiC_GPC_s=(AutoMATiC_GPC_p-1)*AutoMATiC_GPC_ny+AutoMATiC_GPC_m;
                        AutoMATiC_GPC_Ku(AutoMATiC_GPC_r,AutoMATiC_GPC_n,AutoMATiC_GPC_j) = AutoMATiC_GPC_Ku(AutoMATiC_GPC_r,AutoMATiC_GPC_n,AutoMATiC_GPC_j) - AutoMATiC_GPC_K(AutoMATiC_GPC_r,AutoMATiC_GPC_s)*fun_e(AutoMATiC_GPC_p,AutoMATiC_GPC_j,AutoMATiC_GPC_m,AutoMATiC_GPC_n,AutoMATiC_GPC_pars);
                    end
                end
            end
        end
    end
    for AutoMATiC_GPC_r=1:AutoMATiC_GPC_nu
        for AutoMATiC_GPC_m=1:AutoMATiC_GPC_ny
            for AutoMATiC_GPC_j=0:AutoMATiC_GPC_na
                for AutoMATiC_GPC_p=1:N
                    AutoMATiC_GPC_s=(AutoMATiC_GPC_p-1)*AutoMATiC_GPC_ny+AutoMATiC_GPC_m;
                    AutoMATiC_GPC_Ky(AutoMATiC_GPC_r,AutoMATiC_GPC_m,AutoMATiC_GPC_j+1) = AutoMATiC_GPC_Ky(AutoMATiC_GPC_r,AutoMATiC_GPC_m,AutoMATiC_GPC_j+1) - AutoMATiC_GPC_K(AutoMATiC_GPC_r,AutoMATiC_GPC_s)*fun_f(AutoMATiC_GPC_p,AutoMATiC_GPC_j,AutoMATiC_GPC_m,AutoMATiC_GPC_pars);
                end
            end
        end
    end
    for AutoMATiC_GPC_r=1:AutoMATiC_GPC_nu
        for AutoMATiC_GPC_m=1:AutoMATiC_GPC_ny
            for AutoMATiC_GPC_p=1:N
                AutoMATiC_GPC_s=(AutoMATiC_GPC_p-1)*AutoMATiC_GPC_ny+AutoMATiC_GPC_m;
                AutoMATiC_GPC_Kyzad(AutoMATiC_GPC_r,AutoMATiC_GPC_m) = AutoMATiC_GPC_Kyzad(AutoMATiC_GPC_r,AutoMATiC_GPC_m) + AutoMATiC_GPC_K(AutoMATiC_GPC_r,AutoMATiC_GPC_s);
            end
        end
    end
    INIT = 0;
    return; % exits only this script, not the one higher in call stack
end

%% TRANSLATE -- variables created in this section will be declared from scratch
%% wyznaczenie du (optymalnie)
AutoMATiC_GPC_du = zeros(AutoMATiC_GPC_nu,1);
AutoMATiC_GPC_tmpu = zeros(AutoMATiC_GPC_nu,1);
for AutoMATiC_GPC_r=1:AutoMATiC_GPC_nu
    for AutoMATiC_GPC_m=1:AutoMATiC_GPC_ny
        AutoMATiC_GPC_du(AutoMATiC_GPC_r,1) = AutoMATiC_GPC_du(AutoMATiC_GPC_r,1) + AutoMATiC_GPC_Kyzad(AutoMATiC_GPC_r,AutoMATiC_GPC_m)*AD_Z(AutoMATiC_GPC_m);
    end
    for AutoMATiC_GPC_n=1:AutoMATiC_GPC_nu
        for AutoMATiC_GPC_j=1:AutoMATiC_GPC_nb
            AutoMATiC_GPC_du(AutoMATiC_GPC_r,1) = AutoMATiC_GPC_du(AutoMATiC_GPC_r,1) + AutoMATiC_GPC_Ku(AutoMATiC_GPC_r,AutoMATiC_GPC_n,AutoMATiC_GPC_j)*AD_U(AD_K-AutoMATiC_GPC_j,AutoMATiC_GPC_n);
        end
    end
    for AutoMATiC_GPC_m=1:AutoMATiC_GPC_ny
        for AutoMATiC_GPC_j=0:AutoMATiC_GPC_na
            AutoMATiC_GPC_du(AutoMATiC_GPC_r,1) = AutoMATiC_GPC_du(AutoMATiC_GPC_r,1) + AutoMATiC_GPC_Ky(AutoMATiC_GPC_r,AutoMATiC_GPC_m,AutoMATiC_GPC_j+1)*AD_Y(AD_K-AutoMATiC_GPC_j,AutoMATiC_GPC_m);
        end
    end
end

for AutoMATiC_GPC_n=1:AutoMATiC_GPC_nu
    if(AutoMATiC_GPC_du(AutoMATiC_GPC_n,1)>dumax(1,AutoMATiC_GPC_n)); AutoMATiC_GPC_du(AutoMATiC_GPC_n,1) = dumax(1,AutoMATiC_GPC_n); end
    if(AutoMATiC_GPC_du(AutoMATiC_GPC_n,1)<dumin(1,AutoMATiC_GPC_n)); AutoMATiC_GPC_du(AutoMATiC_GPC_n,1) = dumin(1,AutoMATiC_GPC_n); end
    AutoMATiC_GPC_tmpu(AutoMATiC_GPC_n,1) = AD_U(AD_K-1,AutoMATiC_GPC_n) + AutoMATiC_GPC_du(AutoMATiC_GPC_n,1);
    if(AutoMATiC_GPC_tmpu(AutoMATiC_GPC_n,1)>umax(1,AutoMATiC_GPC_n)); AutoMATiC_GPC_tmpu(AutoMATiC_GPC_n,1) = umax(1,AutoMATiC_GPC_n); end
    if(AutoMATiC_GPC_tmpu(AutoMATiC_GPC_n,1)<umin(1,AutoMATiC_GPC_n)); AutoMATiC_GPC_tmpu(AutoMATiC_GPC_n,1) = umin(1,AutoMATiC_GPC_n); end
    AutoMATiC_GPC_du(AutoMATiC_GPC_n,1) = AutoMATiC_GPC_tmpu(AutoMATiC_GPC_n,1) - AD_U(AD_K-1,AutoMATiC_GPC_n);
end

control_value = zeros(1,AutoMATiC_GPC_nu);
for AutoMATiC_GPC_n=1:AutoMATiC_GPC_nu
    control_value(1,AutoMATiC_GPC_n) = AutoMATiC_GPC_du(AutoMATiC_GPC_n,1);
end

%% STOP
