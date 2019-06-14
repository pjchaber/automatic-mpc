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

function CHECK_FOR_VARIABLE(var,what_to_do)
    if(nargin == 1)
        what_to_do = 'ignore';
    end
    existin=@(var)(evalin('base',sprintf('exist(''%s'',''var'')',var)));
    if(~existin(var))
        if(strcmp(what_to_do,'define'))
            eval([var '=[];']);
        elseif(strcmp(what_to_do,'warning'))
            wanrning('CheckForVariable:NoVariable','No "%s" variable defined',var); 
        elseif(strcmp(what_to_do,'error'))
            error('No "%s" variable defined',var); 
        else
            %fprintf('no action\n');
        end
    end
end