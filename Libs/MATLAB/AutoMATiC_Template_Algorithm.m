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

if( INIT == 1 )
    % here is the initialization code
    INIT = 0;
    return; % exits only this script, not the one higher in call stack
end
%% TRANSLATE -- variables created in this section will be declared from scratch
% new control value store in a special vector "control_value"
control_value = zeros(1,1); 
%% STOP
% here one can define additional functions
