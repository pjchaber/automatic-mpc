clearvars -except X A name
kk = length(X);
U=zeros(kk,2); % 2 wejscia
Y=zeros(kk,2); % 2 wyjscia
Z=zeros(kk,2); % 2 wyjscia
T=(0:(kk-1))*.1;

for k=1:kk
    cX = X{k};
    Y(k,:) = cX(1,:);
    Z(k,:) = cX(2,:);
    U(k,:) = cX(3,:);
end

subplot(2,1,1);
plot(T,Y); hold on; 
stairs(T,Z); 
if(exist('A','var'))
    tmp = ylim();
    stairs(T,(A-0.5)*10,'k--'); 
    ylim(tmp);
end
hold off;
subplot(2,1,2);
stairs(T,U); hold on;
if(exist('A','var'))
    tmp = ylim();
    stairs(T,(A-0.5)*10,'k--'); 
    ylim(tmp);
end
hold off;

