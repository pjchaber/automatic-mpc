close all;
clearvars -except X name
kk = length(X);
U=zeros(kk,2); % 2 wejscia
Y=zeros(kk,2); % 2 wyjscia
Z=zeros(kk,2); % 2 wyjscia
ALG=zeros(kk,1); % jedna wartoœæ na iteracjê
T=(0:(kk-1))*.1;
for k=1:kk
    cX = X{k};
    Y(k,:) = cX(1,1:2);
    Z(k,:) = cX(1,3:4);
    U(k,:) = cX(1,5:6);
    if(size(cX,2)>=7)
        ALG(k) = cX(1,7);
    else
        ALG(k) = 0;
    end
end

subplot(2,1,1);
plot(T,Y); hold on; 
stairs(T,Z); 
hold off;
subplot(2,1,2);
stairs(T,U); hold on;
hold off;
csvwrite('pid.csv',[T',Y,Z,U,(ALG-0.5)*100]);

U1=zeros(kk,2)*nan; % 2 wejscia
Y1=zeros(kk,2)*nan; % 2 wyjscia
U2=zeros(kk,2)*nan; % 2 wejscia
Y2=zeros(kk,2)*nan; % 2 wyjscia


ac = T([0;diff(ALG)]~=0);
col = 5;
fprintf('\\fill[mycolor%d,opacity=1] ({axis cs: \\xstart,-0.5}) rectangle ({axis cs:%.1f,0.5});\n',col,ac(1))
for i = 1:(length(ac) - 1)
    if(col == 5); col = 6;
    else        ; col = 5;
    end
    fprintf('\\fill[mycolor%d,opacity=1] ({axis cs: %.1f,-0.5}) rectangle ({axis cs:%.1f,0.5});\n',col,ac(i),ac(i+1))
end
if(col == 5); col = 6;
else        ; col = 5;
end
fprintf('\\fill[mycolor%d,opacity=1] ({axis cs:%.1f,-0.5}) rectangle ({axis cs:50.0,0.5});\n',col,ac(end))