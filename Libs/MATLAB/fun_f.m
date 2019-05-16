function out = fun_f(p,j,m,pars)
    % wartoœci N, a, b, na, nb, nu, ny musz¹ ju¿ byæ w workspace'ie
    persistent F
    if(nargin == 0)
        F = [];
        return;
    end
    N = pars.N;
    a  = pars.a;
    b  = pars.b;
    na = pars.na;
    nb = pars.nb;
    nu = pars.nu;
    ny = pars.ny;
    
    o = 1;
    if(isempty(F))
        F=cell(ny,N,na+o);
        for m=1:ny; for p=1:N; for j=(1-o):na; fun_f(p,j,m,pars); end; end; end
    end
    if(~isempty(F{m,p,j+o}))
        out = F{m,p,j+o};
    else
        if(p == 1)
            if(j==0)
                out = 1 - a(m,1);
            elseif(j>=1 && j<=(na-1))
                out = a(m,j)-a(m,j+1);
            elseif(j==na)
                out = a(m,j);
            else
                disp(N);disp(a);disp(b);disp(na);disp(nb);disp(nu);disp(ny);disp(F);disp(o);error('Error!');
            end
        elseif(p>=2 && p<=N)
            if(j>=0 && j<=(na-1))
                out = fun_f(p-1,0,m,pars)*fun_f(1,j,m,pars)+fun_f(p-1,j+1,m,pars);
            elseif(j==na)
                out = fun_f(p-1,0,m,pars)*fun_f(1,j,m,pars);
            else
                disp(N);disp(a);disp(b);disp(na);disp(nb);disp(nu);disp(ny);disp(F);disp(o);error('Error!');
            end
        else
            disp(N);disp(a);disp(b);disp(na);disp(nb);disp(nu);disp(ny);disp(F);disp(o);error('Error!');
        end
        F{m,p,j+o} = out;
    end
end