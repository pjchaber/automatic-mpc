clear all
%% Process definition
Gs  = [... 
    tf(5,[.14,1]),tf(1,[.10,1]);...
    tf(1,[.06,1]),tf(2,[.08,1]);...
];               % continuous transfer function
Ts = 0.1;        % sampling time
Gz = c2d(Gs,Ts); % discrete transfer function
ny = 2; % number of output signals
nu = 2; % number of control signals

for m=1:2 % ARX model determination
    tmpa = conv(Gz.Den{m,1},Gz.Den{m,2}); GPC_a(m,:)   = tmpa(2:end);
    tmpb = conv(Gz.Num{m,1},Gz.Den{m,2}); GPC_b(m,1,:) = [tmpb(1:end) 0]; 
    tmpb = conv(Gz.Num{m,2},Gz.Den{m,1}); GPC_b(m,2,:) = [tmpb(1:end) 0];
end

D = 5;  % dynamics horizon
S = step_response_generation(GPC_a,GPC_b,D);

% General control algorithms' parameters
N  = 5; % prediction horizon
Nu = 5; % control horizon
lambda= [1.0 1.0]; % Penalty--control signals' incr.
psi   = [1.0 1.0]; % Penalty--control errors
dumin =-[.1 .1]; % Lower bound--control increments
dumax = [.1 .1]; % Upper bound--control increments
umin  =-[1.0 1.0]; % Lower bound--control signal
umax  = [1.0 1.0]; % Upper bound--control signal

T = 0.1;
K =  [.1 .05];
Ti = [1 .1];
Td = [0.0 0.0];

%AutoMATiC_Generate('AutoMATiC_PID_Algorithm_s','controller');
%AutoMATiC_Generate('AutoMATiC_DMC_Analytic_Algorithm','controller');
%AutoMATiC_Generate('AutoMATiC_DMC_Numeric_Algorithm','controller');
%AutoMATiC_Generate('AutoMATiC_GPC_Analytic_Algorithm','controller');
AutoMATiC_Generate('AutoMATiC_GPC_Numeric_Algorithm','controller');


function S = step_response_generation(GPC_a,GPC_b,D)
    ny = size(GPC_a,1);
    nu = size(GPC_b,2);
    S = zeros(ny,nu,D);
    for k = 1:size(S,3)
        for m=1:ny
            for n=1:nu
                for i=1:min(k,size(GPC_b,3))
                    S(m,n,k) = S(m,n,k) + GPC_b(m,n,i)*1;
                end
                for i=1:min(k-1,size(GPC_a,2))
                    S(m,n,k) = S(m,n,k) - GPC_a(m,i)*S(m,n,k-i);
                end         
            end   
        end 
    end
end