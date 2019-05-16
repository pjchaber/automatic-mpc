delete(instrfindall); % zamkniecie wszystkich polaczen szeregowych
clearvars;
% sendmailsetup();

try
warning('OFF', 'MATLAB:serial:fgetl:unsuccessfulRead');
s = serial('COM11'); % COM9 to jest port utworzony przez mikrokontroler
set(s,'BaudRate',115200);
set(s,'StopBits',1);
set(s,'Parity','none');
set(s,'DataBits',7); 
set(s,'Timeout',1000);
set(s,'InputBufferSize',10000);
set(s,'Terminator',10);
fopen(s); % otwarcie kanalu komunikacyjnego
profiler = 0;
experiment_size = 1000;
X = cell(experiment_size,1);
% A = zeros(experiment_size,1);
for k = 1:experiment_size
    txt = fgetl(s);
%     disp(char(txt));
    eval(char(txt));
    if(txt(1)=='%')
        disp(char(txt));
        continue;
    end
    X{k} = x;
%     A(k) = a;
end

fclose(s); % zamkniêcie kanalu komunikacyjnego

opis='X{p} -- p to iteracja, x(1:2) -- y, x(3:4) -- z, x(5:6) -- U';
plik_generujacy = fileread('eksperymenty_MIMO.m');

plot_data
catch ME
%     sendmail('juzio6666@gmail.com','Hello from MATLAB! :(','Shiet happend :(');
    rethrow(ME);
end
% sendmail('juzio6666@gmail.com','Hello from MATLAB! :)','Everything is OK :)');
