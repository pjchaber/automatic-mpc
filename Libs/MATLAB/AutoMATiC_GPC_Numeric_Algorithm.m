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

%% INITIALIZE -- variables here cannot be changed further in code
% required: S,N,Nu,lambda,psi
% optional: dumin,dumax,umin,umax

if( INIT == 1 )
    options = optimset('Display', 'off');
    na = size(GPC_a,2);
    nb = size(GPC_b,3);
    ny = size(GPC_b,1);
    nu = size(GPC_b,2);
    
    % Macierze Lambda oraz Psi -- wagi funkcji kosztów
    if(isrow(lambda)); tmp_lambda = repmat(lambda,1,Nu);
    else             ; tmp_lambda = repmat(lambda,Nu,1);
    end
    if(isrow(psi))   ; tmp_psi = repmat(psi,1,N);
    else             ; tmp_psi = repmat(psi,N,1);
    end
    Lambda = diag(tmp_lambda);
    Psi = diag(tmp_psi);
    
    % OdpowiedŸ skokowa
    S = zeros(ny,nu,N);
    for k = 1:size(S,3)
        for m=1:ny
            for n=1:nu
                for i=1:min(k,nb)
                    S(m,n,k) = S(m,n,k) + GPC_b(m,n,i)*1;
                end
                for i=1:min(k-1,na)
                    S(m,n,k) = S(m,n,k) - GPC_a(m,i)*S(m,n,k-i);
                end         
            end   
        end 
    end

    % Macierz M
    M = cell(N,Nu);
    for row = 1:N
       for col = 1:Nu
            if(row-col+1 >= 1)
                M{row,col} = S(:,:,row-col+1);
            else
                M{row,col} = zeros(size(S(:,:,1)));
            end
       end
    end
    M=cell2mat(M);

    H = 2*(M'*Psi*M+Lambda);
    H=(H+H')/2;
    
    fconst = -2*M'*Psi;
    
    % ograniczenia sterowan w zadaniu PK
    EYEnu = eye(nu);
    Aducell = cell(Nu,Nu);
    Aucell = cell(Nu,Nu);
    bvarcell = cell(Nu,1);

    for i = 1:Nu
        bvarcell{i}  = eye(nu);
        for j = 1:Nu
            if(i>=j)
                Aucell{i,j} = EYEnu;      
            else
                Aucell{i,j} = EYEnu*0;            
            end

            if(i==j)
                Aducell{i,j} = EYEnu;   
            else
                Aducell{i,j} = EYEnu*0;
            end
        end
    end

    bducell = cell(Nu,1);
    bucell = cell(Nu,1);
    for i = 1:Nu
        bducell{i}     = -dumin';
        bducell{i+Nu}  = +dumax';
        bucell{i}      = -umin';
        bucell{i+Nu}   = +umax';
    end
    
    Adu = [-cell2mat(Aducell); cell2mat(Aducell)];
    Au  = [-cell2mat(Aucell ); cell2mat(Aucell )];
    A = [Adu;Au];

    bdu = cell2mat(bducell);
    bu  = cell2mat(bucell);
    b = [bdu;bu];
    bvardu = [cell2mat(bvarcell)*0; cell2mat(bvarcell)*0];
    bvaru = [cell2mat(bvarcell); -cell2mat(bvarcell)];
    bvar = [bvardu; bvaru];
    
    INIT = 0;
    return; % exits only this script, not the one higher in call stack
end

%% TRANSLATE -- variables created in this section will be declared from scratch
%% wyznaczenie du (optymalnie)
tmpu = zeros(nu,1);
du = zeros(nu,1);
Yzad = zeros(ny*N,1);
y0   = zeros(ny,N);
Y0   = zeros(ny*N,1);

itmp = 1;
for i = 1:N
    for j = 1:ny
        Yzad(itmp,1) = AD_Z(j);
        itmp = itmp+1;
    end
end

uk = zeros(nu,1);
for i = 1:nu
    uk(i,1) = AD_U(AD_K-1,i);
end

disturbance = zeros(ny,1);
for m = 1:ny
    disturbance(m,1) = 0;
    for n=1:nu
        for i=1:nb
            disturbance(m,1) = disturbance(m,1) + GPC_b(m,n,i)*AD_U(AD_K-i,n);
        end
    end
    for i=1:na
        disturbance(m,1) = disturbance(m,1) - GPC_a(m,i)*AD_Y(AD_K-i,m);
    end
    disturbance(m,1) = AD_Y(AD_K,m) - disturbance(m,1);
    
    for p=1:N
        Iyf = p-1;
        if(na < Iyf)
            Iyf = na;
        end
        Iuftmp = nb;
        if(p < Iuftmp)
            Iuftmp = p;
        end
        Iuf = 0;
        if(Iuftmp > Iuf)
            Iuf = Iuftmp;
        end
        
        y0(m,p) = disturbance(m,1);
        for n=1:nu
            for r=1:Iuf
                y0(m,p) = y0(m,p)+GPC_b(m,n,r)*AD_U(AD_K-1,n);
            end
        end
        for n=1:nu
            for r=(Iuf+1):nb
                y0(m,p) = y0(m,p)+GPC_b(m,n,r)*AD_U(AD_K-r+p,n);
            end
        end
        
        for r=1:Iyf
            y0(m,p) = y0(m,p)-GPC_a(m,r)*y0(m,p-r);
        end
        
        for r=(Iyf+1):na
            y0(m,p) = y0(m,p)-GPC_a(m,r)*AD_Y(AD_K-r+p,m);
        end
    end
end
itmp = 1;
for i =1:N
    for j = 1:ny
        Y0(itmp,1) = y0(j,i);
        itmp = itmp + 1;
    end
end


ftmp1 = Yzad-Y0;
ftmp4 = fconst*ftmp1;
for i =1:nu*Nu
    ftmp(i) = ftmp4(i,1);
end

btmp1 = bvar*uk;
btmp2 = b+btmp1;
for i = 1:(4*nu*Nu)
    btmp(i) = btmp2(i,1);
end

for i=1:nu
    qpx(i) = 0;
end
qpx = quadprog(H,ftmp,A,btmp,[],[],[],[],[],options);
for i=1:nu
    du(i,1) = qpx(i);
end


for n=1:nu
    if(du(n,1)>dumax(1,n)); du(n,1) = dumax(1,n); end
    if(du(n,1)<dumin(1,n)); du(n,1) = dumin(1,n); end
    tmpu(n,1) = AD_U(AD_K-1,n) + du(n,1);
    if(tmpu(n,1)>umax(1,n)); tmpu(n,1) = umax(1,n); end
    if(tmpu(n,1)<umin(1,n)); tmpu(n,1) = umin(1,n); end
    du(n,1) = tmpu(n,1) - AD_U(AD_K-1,n);
end

control_value = zeros(1,nu);
for n=1:nu
    control_value(1,n) = du(n,1);
end

%% STOP
