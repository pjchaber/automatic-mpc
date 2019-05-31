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
set(s,'InputBufferSize',10000);
set(s,'Terminator',10);
fopen(s); % otwarcie kanalu komunikacyjnego
profiler = 0;
experiment_size = 500;
X = cell(experiment_size,1);
for k = 1:experiment_size
    txt = fgetl(s);
    disp(char(txt));
    eval(char(txt));
    X{k} = x;
end
fprintf('----------------------------------------------------------------------------------------------------------------\n');
fprintf('----------------------------------------------------------------------------------------------------------------\n');
fprintf('----------------------------------------------------------------------------------------------------------------\n');
fprintf('----------------------------------------------------------------------------------------------------------------\n');
fprintf('----------------------------------------------------------------------------------------------------------------\n');
for i=1:20
    txt = fgetl(s);
    disp(char(txt));
end
fclose(s); % zamkniêcie kanalu komunikacyjnego

plot_data
