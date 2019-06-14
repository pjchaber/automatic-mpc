%% Algorytm DMC 1x1 (benchmark)
function [Gs, Gz] = object_generator(Tp)
if(nargin == 0)
    Tp = 0.01; 
end

%% Obiekt regulacji
nu = 2;
ny = 2;

Gs  = [... % Model w postaci transmitancji ci¹g³ej
    tf(5,[.14,1]),tf(1,[.10,1]);...
    tf(1,[.06,1]),tf(2,[.08,1]);...
];
Gz = c2d(Gs,Tp,'zoh');
step(Gz)
D = 2.5/Tp; % 5s of step response divided in parts of Tp [s] length

% Y1/U1=G(1,1) and Y1/U2=G(1,2) => Y1 = G(1,1)*U1 + G(1,2)*U2
for m=1:2
    tmpa = conv(Gz.Denominator{m,1},Gz.Denominator{m,2});
    a(m,:) = tmpa(2:end);

    tmpb = conv(Gz.Numerator{m,1},Gz.Denominator{m,2});
    b(m,1,:) = tmpb(2:end);

    tmpb = conv(Gz.Numerator{m,2},Gz.Denominator{m,1});
    b(m,2,:) = tmpb(2:end);
end  
na = size(a,2);
nb = size(b,3);

ffmat = '%+.12ef';

fprintf('#define ALGORITHM "OBJ%dx%d"\n',ny,nu);
fprintf('#define PARAMETERS ""\n');
fprintf('#define TP %d // [us]\n', Tp*1000*1000);

fprintf('#define nu %d\n',nu);
fprintf('#define ny %d\n',ny);

fprintf('#define na %d\n',na);
fprintf('#define nb %d\n',nb);
% a
fprintf('float a[ny][na] = {');
for m=1:ny
    fprintf('{');
    for i=1:na
        fprintf(ffmat,a(m,i));   
        if(i~=na); fprintf(','); end
    end     
    fprintf('}');
    if(m~=ny); fprintf(','); end
end 
fprintf('};\n');

% b
fprintf('float b[ny][nu][nb] = {');
for m=1:ny
    fprintf('{');
    for n=1:nu
        fprintf('{');
        for i=1:nb
            fprintf(ffmat,b(m,n,i));
            if(i~=nb); fprintf(','); end
        end
        fprintf('}');
        if(n~=nu); fprintf(','); end
    end
    fprintf('}');
    if(m~=ny); fprintf(','); end
end
fprintf('};\n\n');