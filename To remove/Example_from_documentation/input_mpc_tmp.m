global MPC_CROSSCOMPILER

%% PID parameters
pid_par = [4.5, 0.5, 0, 0.1]; % K, Ti, Td, T

%% DMC parameters
S = [0.000000, 0.092150, 0.173850, 0.248100, 0.318800, 0.377800, 0.431050, 0.482250, 0.525350, 0.562900, 0.601350, 0.632200, 0.662350, 0.687750, 0.708050, 0.730500, 0.750150, 0.767650, 0.781550, 0.796300, 0.808050, 0.818450, 0.827000, 0.838500, 0.845200, 0.852700, 0.858100, 0.864350, 0.870200, 0.873350, 0.879250, 0.882050, 0.886500, 0.888350, 0.891600, 0.894450, 0.896650, 0.898500, 0.899500, 0.903350, 0.904200, 0.903200, 0.905050, 0.906650, 0.907000, 0.907750, 0.907550, 0.908850, 0.910550, 0.910400];
N  = 10;
Nu =  5;
lambda = 1;

%% Code generation
if(MPC_CROSSCOMPILER == 1)
    generate(PID(pid_par),'PID');
    generate(DMC_analitic(S,N,Nu,lambda,[],[],[],[]),'DMC_analitic');
    return;
end

%% Optional simulation
fprintf('Tutaj mozna przeprowadzic symulacje...\n');
