close all;
clearvars -except X A name
kk = length(X);
U=zeros(kk,2); % 2 wejscia
Y=zeros(kk,2); % 2 wyjscia
Z=zeros(kk,2); % 2 wyjscia
FBt=zeros(kk,1); % jeden pomiar czasu na iteracjê 
ALG=zeros(kk,1); % jedna wartoœæ na iteracjê
T=(0:(kk-1))*.1;
for k=1:kk
    cX = X{k};
    Y(k,:) = cX(1,2:3);
    Z(k,:) = cX(1,4:5);
    U(k,:) = cX(1,6:7);
    FBt(k) = cX(1,8:8);
    ALG(k) = cX(1,9:9);
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


