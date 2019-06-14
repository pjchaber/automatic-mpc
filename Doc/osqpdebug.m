delete(instrfindall); % zamkniecie wszystkich polaczen szeregowych
clearvars;
% sendmailsetup();

warning('OFF', 'MATLAB:serial:fgetl:unsuccessfulRead');
s = serial('COM7'); % COM9 to jest port utworzony przez mikrokontroler

set(s,'BaudRate',115200);
set(s,'StopBits',1);
set(s,'Parity','none');
set(s,'DataBits',7); 
set(s,'Timeout',1000);
set(s,'InputBufferSize',1000000);
set(s,'Terminator',10);
fopen(s); % otwarcie kanalu komunikacyjnego

GO = 0;
for i = 1:100
    txt = fgetl(s);
    %fprintf('%s\n',char(txt));
    eval(char(txt));
    if(GO == 1)
        GO = 0; 
        vec_to_c(q,'osqp_q',0);
        vec_to_c(l,'osqp_lb',0);
        vec_to_c(u,'osqp_ub',0);
        vec_to_c(x,'osqp_x',0);
        fprintf('\n');
%         P=ungenerateCSC(makeCSC(P_x,P_p,P_i));
%         A=ungenerateCSC(makeCSC(A_x,A_p,A_i));
%         qpx=quadprog(P,q',[A;-A],[l';u']);
        
    end
end

X=generateCSC([1,0,0,0;0,1,1,0;1,0,0,0;0,0,0,0]);
