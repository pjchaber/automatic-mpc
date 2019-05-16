global MPC_CROSSCOMPILER
% Obiekt rzeczywisty -- 2xRC
%S(1,1,:)=[0.1784, 0.3805, 0.5334, 0.6467, 0.7305, 0.7926, 0.8385, 0.8724, 0.8975, 0.9161, 0.9299, 0.9401, 0.9476, 0.9532, 0.9573, 0.9603, 0.9626, 0.9643, 0.9655, 0.9664, 0.9671, 0.9676, 0.9679]; % Tp = 0.1
S(1,1,:)=[0.3805, 0.6467, 0.7926, 0.8724, 0.9161, 0.9401, 0.9532, 0.9603, 0.9643, 0.9664]; % Tp = 0.2
a(1,:) = [-7.875594597027e-01,+3.526926067685e-02]; % Tp = 0.1?
b(1,1,:) = [+1.783577301464e-01,+6.167306699759e-02]; % Tp = 0.1?


%% Code generation
if(MPC_CROSSCOMPILER == 1)
    %% DMC 
    % generate(DMC_MIMO_A(S,10,5,1,1,[],[],-1,1),'CONTROLLER');
    % generate(DMC_MIMO_N(S,10,5,1,1,[],[],-1,1),'CONTROLLER_N');
    %% GPC
    generate(GPC_MIMO_A(a,b,20,5,10,1,[],[],-1, 1),'CONTROLLER');
    generate(GPC_MIMO_N(a,b,20,5,10,1,[],[],-1, 1),'CONTROLLER_N');
    % generate(Constant([-1 -1]),'CONTROLLER');
    return;
end

%% Optional simulation
fprintf('Tutaj mozna przeprowadzic symulacje...\n');
