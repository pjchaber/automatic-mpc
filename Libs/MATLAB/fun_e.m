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

function out = fun_e(p,j,m,n,pars)
    % wartoœci N, a, b, na, nb, nu, ny musz¹ ju¿ byæ w workspace'ie
    persistent E
    if(nargin == 0)
        E = [];
        return;
    end
    N = pars.N;
    a  = pars.a;
    b  = pars.b;
    na = pars.na;
    nb = pars.nb;
    nu = pars.nu;
    ny = pars.ny;
    o = 0;
    if(isempty(E))
        E=cell(ny,nu,N,nb+o);
        for m=1:ny; for n=1:nu; for p=1:N; for j=(1-o):nb; fun_e(p,j,m,n,pars); end; end; end; end
    end
    if(~isempty(E{m,n,p,j+o}))
        out = E{m,n,p,j+o};
    else
        if(j==1 && nb==1)
            out = 0;
        elseif(j==1 && nb>1)
            out = fun_g(p,j,m,n,pars);
        elseif(j>=2 && j<=(nb-1) && j<nb && nb>1)
            out = fun_g(p,j,m,n,pars) - fun_g(p,j-1,m,n,pars);
        elseif(j==nb && nb>1)
            out = -fun_g(p,j-1,m,n,pars);
        else
            disp(N);disp(a);disp(b);disp(na);disp(nb);disp(nu);disp(ny);
            disp(p);disp(j);disp(m);disp(n);
            %disp(E);disp(o);
            error('Error!');
        end
        E{m,n,p,j+o} = out;
    end
end



