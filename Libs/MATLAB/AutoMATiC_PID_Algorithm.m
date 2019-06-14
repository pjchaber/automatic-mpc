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

if( INIT == 1 )
    nu = length(K);
    r = [K.*Td./T;
         K.*(T./(2*Ti)-2*Td./T-1);
         K.*(1+T./(2*Ti)+Td./T)];
    INIT = 0; return;
end
%% TRANSLATE -- variables created in this section will be declared from scratch
e     = zeros(nu, 3); tmpu = zeros(nu,1);
er    = zeros(nu, 3); du = zeros(nu,1);
control_value = zeros(1,nu);
for n=1:nu
    e( n,1) = AD_Z(n) - AD_Y(AD_K-0,n);
    e( n,2) = AD_Z(n) - AD_Y(AD_K-1,n);
    e( n,3) = AD_Z(n) - AD_Y(AD_K-2,n);
    er(n,1) = e(n,1)*r(1,n);
    er(n,2) = e(n,2)*r(2,n);
    er(n,3) = e(n,3)*r(3,n);
    
    du(n,1) = du(n,1) + er(n,1);
    du(n,1) = du(n,1) + er(n,2);
    du(n,1) = du(n,1) + er(n,3);

    if(du(n,1)>dumax(1,n)); du(n,1) = dumax(1,n); end
    if(du(n,1)<dumin(1,n)); du(n,1) = dumin(1,n); end
    tmpu(n,1) = AD_U(AD_K-1,n) + du(n,1);
    if(tmpu(n,1)>umax(1,n)); tmpu(n,1) = umax(1,n); end
    if(tmpu(n,1)<umin(1,n)); tmpu(n,1) = umin(1,n); end
    du(n,1) = tmpu(n,1) - AD_U(AD_K-1,n);
end

for n=1:nu
    control_value(1,n) = du(n,1);
end
%% STOP