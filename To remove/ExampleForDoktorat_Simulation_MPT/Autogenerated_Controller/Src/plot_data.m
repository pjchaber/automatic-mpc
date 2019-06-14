clearvars -except X
kk = length(X);
U=zeros(kk,2); % 2 wejscia
Y=zeros(kk,2); % 2 wyjscia
Z=zeros(kk,2); % 2 wyjscia
times=zeros(kk,2); % 2 wyjscia
T=(0:(kk-1))*.1;

for k=1:kk
    cX = X{k};
    if(isempty(cX))
        break;
    end
    Y(k,:) = cX(2:3)';
    Z(k,:) = cX(4:5);
    U(k,:) = cX(6:7);
    J(k,:) = cX(8);
    times(k,:) = cX(9:10);
end

figure;
subplot(3,1,1);
plot(T,Y); hold on; 
stairs(T,Z); 
hold off;
subplot(3,1,2);
stairs(T,U); hold on;
hold off;
subplot(3,1,3);
plot(T,times);
