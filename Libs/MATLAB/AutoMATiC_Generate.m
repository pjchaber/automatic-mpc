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

function code = AutoMATiC_Generate(alg,name,first)
    if(nargin < 3)
        first = 1;
    end
    evalin('base','INIT = 1;');
    L = AutoMATiC_Lexer(fileread([alg '.m']));
    tokens = L.gettokens();
    toexecute = L.getcodetoexecute();

    P = AutoMATiC_Parser(tokens);
    tree = P.gettree();

%    G = AutoMATiC_Generator_Active_Set(toexecute,tree);
    G = AutoMATiC_Generator_osQP(toexecute,tree);
    
    if(first)
        mode = 'w';
    else
        mode = 'a';
    end
    fd = fopen('C:/AutoMATiC_Temp/tmp.c',mode);
    fprintf(fd,G.code,name);
    code = sprintf(G.code,name);
    fclose(fd);
end