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
% Date:   15.05.2019
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
CHECK_FOR_VARIABLE K      % GENERAL REQUIREMENT
CHECK_FOR_VARIABLE Ti     % GENERAL REQUIREMENT
CHECK_FOR_VARIABLE Td     % GENERAL REQUIREMENT
CHECK_FOR_VARIABLE T     % GENERAL REQUIREMENT

if( INIT == 1 )
    AutoMATiC_PID_nu = length(K);
    AutoMATiC_PID_r = zeros(3,AutoMATiC_PID_nu);
    AutoMATiC_PID_r(3,:) = K.*Td./T;
    AutoMATiC_PID_r(2,:) = K.*(T./(2*Ti) - 2*Td./T - 1);
    AutoMATiC_PID_r(1,:) = K.*(1 + T./(2*Ti) + Td./T);
    AutoMATiC_PID_to_vec = ones(AutoMATiC_PID_nu,1);
    INIT = 0;
    return; % exits only this script, not the one higher in call stack
end

%% TRANSLATE -- variables created in this section will be declared from scratch
AutoMATiC_PID_dutmp = zeros(AutoMATiC_PID_nu,AutoMATiC_PID_nu);
AutoMATiC_PID_du = zeros(AutoMATiC_PID_nu,1);
AutoMATiC_PID_e = zeros(AutoMATiC_PID_nu,3);
AutoMATiC_PID_tmpu = zeros(AutoMATiC_PID_nu,1);
for AutoMATiC_PID_n=1:AutoMATiC_PID_nu
    AutoMATiC_PID_e( AutoMATiC_PID_n,1) = AD_Z(AutoMATiC_PID_n) - AD_Y(AD_K-0,AutoMATiC_PID_n);
    AutoMATiC_PID_e( AutoMATiC_PID_n,2) = AD_Z(AutoMATiC_PID_n) - AD_Y(AD_K-1,AutoMATiC_PID_n);
    AutoMATiC_PID_e( AutoMATiC_PID_n,3) = AD_Z(AutoMATiC_PID_n) - AD_Y(AD_K-2,AutoMATiC_PID_n);
end
AutoMATiC_PID_dutmp = AutoMATiC_PID_r*AutoMATiC_PID_e;
AutoMATiC_PID_du    = AutoMATiC_PID_dutmp * AutoMATiC_PID_to_vec;
for AutoMATiC_PID_n=1:AutoMATiC_PID_nu
    if(AutoMATiC_PID_du(AutoMATiC_PID_n,1)>dumax(1,AutoMATiC_PID_n)); AutoMATiC_PID_du(AutoMATiC_PID_n,1) = dumax(1,AutoMATiC_PID_n); end
    if(AutoMATiC_PID_du(AutoMATiC_PID_n,1)<dumin(1,AutoMATiC_PID_n)); AutoMATiC_PID_du(AutoMATiC_PID_n,1) = dumin(1,AutoMATiC_PID_n); end
    AutoMATiC_PID_tmpu(AutoMATiC_PID_n,1) = AD_U(AD_K-1,AutoMATiC_PID_n) + AutoMATiC_PID_du(AutoMATiC_PID_n,1);
    if(AutoMATiC_PID_tmpu(AutoMATiC_PID_n,1)>umax(1,AutoMATiC_PID_n)); AutoMATiC_PID_tmpu(AutoMATiC_PID_n,1) = umax(1,AutoMATiC_PID_n); end
    if(AutoMATiC_PID_tmpu(AutoMATiC_PID_n,1)<umin(1,AutoMATiC_PID_n)); AutoMATiC_PID_tmpu(AutoMATiC_PID_n,1) = umin(1,AutoMATiC_PID_n); end
    AutoMATiC_PID_du(AutoMATiC_PID_n,1) = AutoMATiC_PID_tmpu(AutoMATiC_PID_n,1) - AD_U(AD_K-1,AutoMATiC_PID_n);
end

control_value = zeros(1,AutoMATiC_PID_nu);
for AutoMATiC_PID_n=1:AutoMATiC_PID_nu
    control_value(1,AutoMATiC_PID_n) = AutoMATiC_PID_du(AutoMATiC_PID_n,1);
end

%% STOP
