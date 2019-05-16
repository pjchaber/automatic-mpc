global MPC_CROSSCOMPILER

if(MPC_CROSSCOMPILER == 1)
    A = -1; % 0 -- DMC_A, 1 -- DMC_N, 2 -- GPC_A, 3 -- GPC_N, -1 -- CONST,
    load('C:\\Users\\Admin\\Documents\\GitHub\\Cpp\\Kompilator_skrosny\\ExampleForGrant\\conf.mat');

        if (A == 1) generate(Constant(-1),'CONTROLLER');
    elseif (A == 2) generate(DMC_MIMO_A(S  ,N,Nu,Lambda,Psi,dumin,dumax,umin,umax),'CONTROLLER');
    elseif (A == 3) generate(DMC_MIMO_N(S  ,N,Nu,Lambda,Psi,dumin,dumax,umin,umax),'CONTROLLER');
    elseif (A == 4) generate(GPC_MIMO_A(a,b,N,Nu,Lambda,Psi,dumin,dumax,umin,umax),'CONTROLLER');
    elseif (A == 5) generate(GPC_MIMO_N(a,b,N,Nu,Lambda,Psi,dumin,dumax,umin,umax),'CONTROLLER');
    end

    return;
end

%% Optional simulation
fprintf('Tutaj mozna przeprowadzic symulacje...\n');
