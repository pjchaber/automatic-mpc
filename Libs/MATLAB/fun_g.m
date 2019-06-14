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

function out = fun_g(p,j,m,n,pars)
    % wartoœci N, a, b, na, nb, nu, ny musz¹ ju¿ byæ w workspace'ie
    persistent G
    if(nargin == 0)
        G = [];
        return;
    end
    N = pars.N;
    a  = pars.a;
    b  = pars.b;
    na = pars.na;
    nb = pars.nb;
    nu = pars.nu;
    ny = pars.ny;
    
    o = N;
    if(isempty(G))
        G=cell(ny,nu,N,nb-1+o);
        for m=1:ny; for n=1:nu; for p=1:N; for j=(1-p):(nb-1); fun_g(p,j,m,n,pars); end; end; end; end
    end
    if(~isempty(G{m,n,p,j+o}))
        out = G{m,n,p,j+o};
    else
        if(p == 1)
            if(j>=0 && j<=(nb-1))
                out = b(m,n,j+1);
            else
                disp(N);disp(a);disp(b);disp(na);disp(nb);disp(nu);disp(ny);disp(G);disp(o);error('Error!');
            end
        elseif(p>=2 && p<=N)
            if(j>=(1-p) && j<=(-1))
                out = fun_g(p-1,j+1,m,n,pars);
            elseif(j>=0 && j<=(nb-2))
                out = fun_f(p-1,0,m,pars)*fun_g(1,j,m,n,pars)+fun_g(p-1,j+1,m,n,pars);
            elseif(j==(nb-1))
                out = fun_f(p-1,0,m,pars)*fun_g(1,j,m,n,pars);
            else
                disp(N);disp(a);disp(b);disp(na);disp(nb);disp(nu);disp(ny);disp(G);disp(o);error('Error!');
            end
        else
            disp(N);disp(a);disp(b);disp(na);disp(nb);disp(nu);disp(ny);disp(G);disp(o);error('Error!');
        end
        G{m,n,p,j+o} = out;
    end
end