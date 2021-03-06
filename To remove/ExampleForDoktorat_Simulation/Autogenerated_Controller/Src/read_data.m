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
profiler_started = 0;
while 1
    txt = fgetl(s);
    if(txt(1)~='x')
        profiler_started = 1;
    else
        if(profiler_started)
            break;
        else
            continue;
        end
    end
    disp(char(txt));
end
fclose(s); % zamkni�cie kanalu komunikacyjnego

plot_data(X,'dmc an');
