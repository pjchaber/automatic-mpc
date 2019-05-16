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
CHECK_FOR_VARIABLE AD_Y % GENERAL REQUIREMENT
CHECK_FOR_VARIABLE AD_U % GENERAL REQUIREMENT
CHECK_FOR_VARIABLE AD_DU % GENERAL REQUIREMENT
CHECK_FOR_VARIABLE AD_Z % GENERAL REQUIREMENT
CHECK_FOR_VARIABLE control_value % ALGORITHM SPECIFIC REQUIREMENT

%% INITIALIZE -- variables here cannot be changed further in code
% required: S,N,Nu,lambda,psi
% optional: dumin,dumax,umin,umax
CHECK_FOR_VARIABLE S      % GENERAL REQUIREMENT
CHECK_FOR_VARIABLE N      % GENERAL REQUIREMENT
CHECK_FOR_VARIABLE Nu     % GENERAL REQUIREMENT
CHECK_FOR_VARIABLE lambda % GENERAL REQUIREMENT
CHECK_FOR_VARIABLE psi    % GENERAL REQUIREMENT

if( INIT == 1 )
    AutoMATiC_DMC_ny = size(S,1);
    AutoMATiC_DMC_nu = size(S,2);
    AutoMATiC_DMC_D  = size(S,3); 

    if(isrow(lambda)); tmp_lambda = repmat(lambda,1,Nu);
    else             ; tmp_lambda = repmat(lambda,Nu,1);
    end
    if(isrow(psi))   ; tmp_psi = repmat(psi,1,N);
    else             ; tmp_psi = repmat(psi,N,1);
    end
    AutoMATiC_DMC_Lambda = diag(tmp_lambda);
    AutoMATiC_DMC_Psi = diag(tmp_psi);

    AutoMATiC_DMC_M = cell(N,Nu);
    for AutoMATiC_DMC_row = 1:N
       for AutoMATiC_DMC_col = 1:Nu
            if(AutoMATiC_DMC_row-AutoMATiC_DMC_col+1 >= 1)
                AutoMATiC_DMC_M{AutoMATiC_DMC_row,AutoMATiC_DMC_col} = S(:,:,min(AutoMATiC_DMC_row-AutoMATiC_DMC_col+1,AutoMATiC_DMC_D));
            else
                AutoMATiC_DMC_M{AutoMATiC_DMC_row,AutoMATiC_DMC_col} = zeros(size(S(:,:,1)));
            end
       end
    end
    AutoMATiC_DMC_M=cell2mat(AutoMATiC_DMC_M);
    % Macierz Mp
    AutoMATiC_DMC_Mp = cell(N,(AutoMATiC_DMC_D-1));
    for AutoMATiC_DMC_row = 1:N
       for AutoMATiC_DMC_col = 1:(AutoMATiC_DMC_D-1)
            AutoMATiC_DMC_Mp{AutoMATiC_DMC_row,AutoMATiC_DMC_col} = S(:,:,min(AutoMATiC_DMC_row+AutoMATiC_DMC_col,AutoMATiC_DMC_D)) - S(:,:,AutoMATiC_DMC_col);
       end
    end
    AutoMATiC_DMC_Mp = cell2mat(AutoMATiC_DMC_Mp);

    % Macierz K
    AutoMATiC_DMC_K = (AutoMATiC_DMC_M'*AutoMATiC_DMC_Psi*AutoMATiC_DMC_M+AutoMATiC_DMC_Lambda)^(-1)*AutoMATiC_DMC_M'*AutoMATiC_DMC_Psi;

    %% Macierze dla wersji minimalistycznej algorytmu
    AutoMATiC_DMC_Ku=AutoMATiC_DMC_K(1:AutoMATiC_DMC_nu,:)*AutoMATiC_DMC_Mp;

    AutoMATiC_DMC_Ke=zeros(AutoMATiC_DMC_nu,1);
    for AutoMATiC_DMC_n=1:AutoMATiC_DMC_nu
        for AutoMATiC_DMC_m=1:AutoMATiC_DMC_ny
            AutoMATiC_DMC_Ke(AutoMATiC_DMC_n,AutoMATiC_DMC_m) = sum(AutoMATiC_DMC_K(AutoMATiC_DMC_n,AutoMATiC_DMC_m:AutoMATiC_DMC_ny:end));
        end
    end
    
    INIT = 0;
    return; % exits only this script, not the one higher in call stack
end

%% TRANSLATE -- variables created in this section will be declared from scratch
AutoMATiC_DMC_dUp  = zeros(AutoMATiC_DMC_nu*(AutoMATiC_DMC_D-1),1);
AutoMATiC_DMC_Yzad = zeros(AutoMATiC_DMC_ny*N,1);
AutoMATiC_DMC_Y    = zeros(AutoMATiC_DMC_ny*N,1);
AutoMATiC_DMC_tmpu = zeros(AutoMATiC_DMC_nu,1);
%Y0tmp1 = zeros(ny*N,1);
%Y0   = zeros(ny*N,1);
AutoMATiC_DMC_itmp = 1;
for AutoMATiC_DMC_i = 1:(AutoMATiC_DMC_D-1)
    for AutoMATiC_DMC_j = 1:AutoMATiC_DMC_nu
        AutoMATiC_DMC_dUp(AutoMATiC_DMC_itmp,1) = AD_DU(AD_K-AutoMATiC_DMC_i,AutoMATiC_DMC_j);
        AutoMATiC_DMC_itmp = AutoMATiC_DMC_itmp+1;
    end
end

AutoMATiC_DMC_itmp = 1;
for AutoMATiC_DMC_i = 1:N
    for AutoMATiC_DMC_j = 1:AutoMATiC_DMC_ny
        AutoMATiC_DMC_Yzad(AutoMATiC_DMC_itmp,1) = AD_Z(AutoMATiC_DMC_j);
        AutoMATiC_DMC_itmp = AutoMATiC_DMC_itmp+1;
    end
end

AutoMATiC_DMC_itmp = 1;
for AutoMATiC_DMC_i = 1:N
    for AutoMATiC_DMC_j = 1:AutoMATiC_DMC_ny
        AutoMATiC_DMC_Y(AutoMATiC_DMC_itmp,1) = AD_Y(AD_K,AutoMATiC_DMC_j);
        AutoMATiC_DMC_itmp = AutoMATiC_DMC_itmp+1;
    end
end
%% wyznaczenie du (optymalnie)
AutoMATiC_DMC_e=zeros(AutoMATiC_DMC_ny,1);
for AutoMATiC_DMC_i=1:AutoMATiC_DMC_ny
    AutoMATiC_DMC_e(AutoMATiC_DMC_i,1) = AD_Z(AutoMATiC_DMC_i)-AD_Y(AD_K,AutoMATiC_DMC_i);
end
AutoMATiC_DMC_dutmp1 = AutoMATiC_DMC_Ke*AutoMATiC_DMC_e;
AutoMATiC_DMC_dutmp2 = AutoMATiC_DMC_Ku*AutoMATiC_DMC_dUp;
AutoMATiC_DMC_du = AutoMATiC_DMC_dutmp1 - AutoMATiC_DMC_dutmp2;  

for AutoMATiC_DMC_n=1:AutoMATiC_DMC_nu
    if(AutoMATiC_DMC_du(AutoMATiC_DMC_n,1)>dumax(1,AutoMATiC_DMC_n)); AutoMATiC_DMC_du(AutoMATiC_DMC_n,1) = dumax(1,AutoMATiC_DMC_n); end
    if(AutoMATiC_DMC_du(AutoMATiC_DMC_n,1)<dumin(1,AutoMATiC_DMC_n)); AutoMATiC_DMC_du(AutoMATiC_DMC_n,1) = dumin(1,AutoMATiC_DMC_n); end
    AutoMATiC_DMC_tmpu(AutoMATiC_DMC_n,1) = AD_U(AD_K-1,AutoMATiC_DMC_n) + AutoMATiC_DMC_du(AutoMATiC_DMC_n,1);
    if(AutoMATiC_DMC_tmpu(AutoMATiC_DMC_n,1)>umax(1,AutoMATiC_DMC_n)); AutoMATiC_DMC_tmpu(AutoMATiC_DMC_n,1) = umax(1,AutoMATiC_DMC_n); end
    if(AutoMATiC_DMC_tmpu(AutoMATiC_DMC_n,1)<umin(1,AutoMATiC_DMC_n)); AutoMATiC_DMC_tmpu(AutoMATiC_DMC_n,1) = umin(1,AutoMATiC_DMC_n); end
    AutoMATiC_DMC_du(AutoMATiC_DMC_n,1) = AutoMATiC_DMC_tmpu(AutoMATiC_DMC_n,1) - AD_U(AD_K-1,AutoMATiC_DMC_n);
end

control_value = zeros(1,AutoMATiC_DMC_nu);
for AutoMATiC_DMC_n=1:AutoMATiC_DMC_nu
    control_value(1,AutoMATiC_DMC_n) = AutoMATiC_DMC_du(AutoMATiC_DMC_n,1);
end

%% STOP
