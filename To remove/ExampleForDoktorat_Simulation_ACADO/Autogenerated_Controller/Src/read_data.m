delete(instrfindall); % zamkniecie wszystkich polaczen szeregowych
clearvars;
close all;
% sendmailsetup();

try
warning('OFF', 'MATLAB:serial:fgetl:unsuccessfulRead');
s = serial('COM7'); % COM9 to jest port utworzony przez mikrokontroler
set(s,'BaudRate',115200);
set(s,'StopBits',1);
set(s,'Parity','none');
set(s,'DataBits',7); 
set(s,'Timeout',10);
set(s,'InputBufferSize',10000);
set(s,'Terminator',10);
fopen(s); % otwarcie kanalu komunikacyjnego

% figure;
% drawnow();
experiment_size = 300;
X = cell(experiment_size,1);
for k = 1:experiment_size
    txt = fgetl(s);
    disp(char(txt));
    eval(char(txt));
    X{k} = x;
%     
%     subplot(3,1,1); hold on;
%     plot(k+(1:length(cy)/4),cy(1:4:end),'r');
%     plot(k+(1:length(cy)/4),cy(2:4:end),'b'); 
%     plot(k+(1:length(cy)/4),cy(3:4:end),'r--'); 
%     plot(k+(1:length(cy)/4),cy(4:4:end),'b--'); 
%     plot(k+length(cy)/4,cyn(1),'rx'); 
%     plot(k+length(cy)/4,cyn(2),'bx'); 
%     subplot(3,1,2); hold on;
%     plot(k+(1:length(cx)/2),cx(1:2:end),'r'); 
%     plot(k+(1:length(cx)/2),cx(2:2:end),'b');
%     subplot(3,1,3);hold on;
%     stairs(k+(1:length(cu)/2),cu(1:2:end),'r');
%     stairs(k+(1:length(cu)/2),cu(2:2:end),'b');
%     drawnow
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
