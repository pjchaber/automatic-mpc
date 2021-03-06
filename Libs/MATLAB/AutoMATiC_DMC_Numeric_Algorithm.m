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
    AutoMATiC_DMC_options = optimset('Display', 'off');

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

    AutoMATiC_DMC_H = 2*(AutoMATiC_DMC_M'*AutoMATiC_DMC_Psi*AutoMATiC_DMC_M+AutoMATiC_DMC_Lambda);
    AutoMATiC_DMC_H=(AutoMATiC_DMC_H+AutoMATiC_DMC_H')/2;
    AutoMATiC_DMC_fconst = -2*AutoMATiC_DMC_M'*AutoMATiC_DMC_Psi;
    
    % ograniczenia sterowan w zadaniu PK
    AutoMATiC_DMC_EYEnu = eye(AutoMATiC_DMC_nu);
    AutoMATiC_DMC_Aducell = cell(Nu,Nu);
    AutoMATiC_DMC_Aucell = cell(Nu,Nu);
    AutoMATiC_DMC_bvarcell = cell(Nu,1);

    for AutoMATiC_DMC_i = 1:Nu
        AutoMATiC_DMC_bvarcell{AutoMATiC_DMC_i}  = eye(AutoMATiC_DMC_nu);
        for AutoMATiC_DMC_j = 1:Nu
            if(AutoMATiC_DMC_i>=AutoMATiC_DMC_j)
                AutoMATiC_DMC_Aucell{AutoMATiC_DMC_i,AutoMATiC_DMC_j} = AutoMATiC_DMC_EYEnu;      
            else
                AutoMATiC_DMC_Aucell{AutoMATiC_DMC_i,AutoMATiC_DMC_j} = AutoMATiC_DMC_EYEnu*0;            
            end

            if(AutoMATiC_DMC_i==AutoMATiC_DMC_j)
                AutoMATiC_DMC_Aducell{AutoMATiC_DMC_i,AutoMATiC_DMC_j} = AutoMATiC_DMC_EYEnu;   
            else
                AutoMATiC_DMC_Aducell{AutoMATiC_DMC_i,AutoMATiC_DMC_j} = AutoMATiC_DMC_EYEnu*0;
            end
        end
    end

%     AutoMATiC_DMC_bducell = cell(Nu*2,1);
%     AutoMATiC_DMC_bucell = cell(Nu*2,1);
    AutoMATiC_DMC_bcell = cell(Nu*4,1);
    for AutoMATiC_DMC_i = 1:Nu
%         AutoMATiC_DMC_bducell{AutoMATiC_DMC_i}     = -dumin';
%         AutoMATiC_DMC_bducell{AutoMATiC_DMC_i+Nu}  = +dumax';
%         AutoMATiC_DMC_bucell{AutoMATiC_DMC_i}      = -umin';
%         AutoMATiC_DMC_bucell{AutoMATiC_DMC_i+Nu}   = +umax';
        
        AutoMATiC_DMC_bcell{AutoMATiC_DMC_i+Nu*0} = -dumin';
        AutoMATiC_DMC_bcell{AutoMATiC_DMC_i+Nu*1} = -umin';
        AutoMATiC_DMC_bcell{AutoMATiC_DMC_i+Nu*2} = +dumax';
        AutoMATiC_DMC_bcell{AutoMATiC_DMC_i+Nu*3} = +umax';
    end
    
% Active Set version    
%     AutoMATiC_DMC_Adu = [-cell2mat(AutoMATiC_DMC_Aducell); cell2mat(AutoMATiC_DMC_Aducell)];
%     AutoMATiC_DMC_Au  = [-cell2mat(AutoMATiC_DMC_Aucell ); cell2mat(AutoMATiC_DMC_Aucell )];
%     AutoMATiC_DMC_A = [AutoMATiC_DMC_Adu;AutoMATiC_DMC_Au];

% osQP adaptation
    AutoMATiC_DMC_A = [
        -cell2mat(AutoMATiC_DMC_Aducell); 
        -cell2mat(AutoMATiC_DMC_Aucell );
         cell2mat(AutoMATiC_DMC_Aducell);  
         cell2mat(AutoMATiC_DMC_Aucell )];

    AutoMATiC_DMC_b = cell2mat(AutoMATiC_DMC_bcell);
    
    AutoMATiC_DMC_bvar = [
         cell2mat(AutoMATiC_DMC_bvarcell)*0; 
         cell2mat(AutoMATiC_DMC_bvarcell); 
        -cell2mat(AutoMATiC_DMC_bvarcell)*0; 
        -cell2mat(AutoMATiC_DMC_bvarcell);
        ];
    
    INIT = 0;
    return; % exits only this script, not the one higher in call stack
end

%% TRANSLATE -- variables created in this section will be declared from scratch
AutoMATiC_DMC_dUp  = zeros(AutoMATiC_DMC_nu*(AutoMATiC_DMC_D-1),1);
AutoMATiC_DMC_Yzad = zeros(AutoMATiC_DMC_ny*N,1);
AutoMATiC_DMC_Y    = zeros(AutoMATiC_DMC_ny*N,1);
AutoMATiC_DMC_tmpu = zeros(AutoMATiC_DMC_nu,1);

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

AutoMATiC_DMC_du = zeros(AutoMATiC_DMC_nu,1);
AutoMATiC_DMC_uk = zeros(AutoMATiC_DMC_nu,1);
for AutoMATiC_DMC_i = 1:AutoMATiC_DMC_nu
    AutoMATiC_DMC_uk(AutoMATiC_DMC_i,1) = AD_U(AD_K-1,AutoMATiC_DMC_i);
end

AutoMATiC_DMC_ftmp1 = AutoMATiC_DMC_Yzad-AutoMATiC_DMC_Y;
AutoMATiC_DMC_ftmp2 = AutoMATiC_DMC_Mp*AutoMATiC_DMC_dUp;
AutoMATiC_DMC_ftmp3 = AutoMATiC_DMC_ftmp1-AutoMATiC_DMC_ftmp2;
AutoMATiC_DMC_ftmp4 = AutoMATiC_DMC_fconst*AutoMATiC_DMC_ftmp3;
for AutoMATiC_DMC_i =1:AutoMATiC_DMC_nu*Nu
    AutoMATiC_DMC_ftmp(AutoMATiC_DMC_i) = AutoMATiC_DMC_ftmp4(AutoMATiC_DMC_i,1);
end

AutoMATiC_DMC_btmp1 = AutoMATiC_DMC_bvar*AutoMATiC_DMC_uk;
AutoMATiC_DMC_btmp2 = AutoMATiC_DMC_b+AutoMATiC_DMC_btmp1;
for AutoMATiC_DMC_i = 1:(4*AutoMATiC_DMC_nu*Nu)
    AutoMATiC_DMC_btmp(AutoMATiC_DMC_i) = AutoMATiC_DMC_btmp2(AutoMATiC_DMC_i,1);
end

for AutoMATiC_DMC_i=1:(AutoMATiC_DMC_nu*Nu)
    AutoMATiC_DMC_qpx(AutoMATiC_DMC_i) = 0;
end
AutoMATiC_DMC_qpx = quadprog(AutoMATiC_DMC_H,AutoMATiC_DMC_ftmp,AutoMATiC_DMC_A,AutoMATiC_DMC_btmp,[],[],[],[],[],AutoMATiC_DMC_options);
for AutoMATiC_DMC_i=1:AutoMATiC_DMC_nu
    AutoMATiC_DMC_du(AutoMATiC_DMC_i,1) = AutoMATiC_DMC_qpx(AutoMATiC_DMC_i);
end

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
