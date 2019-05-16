if( INIT == 1 )
    nu = length(K); to_vec = ones(nu,1);
    r = [K.*Td./T;K.*(T./(2*Ti)-2*Td./T- 1);K.*(1+T./(2*Ti)+Td./T)];
    INIT = 0; return;
end
%% TRANSLATE -- variables created in this section will be declared from scratch
dutmp = zeros(nu,nu); du   = zeros(nu,1);
e     = zeros(nu, 3); tmpu = zeros(nu,1);
control_value = zeros(1,nu);
for n=1:nu
    e( n,1) = AD_Z(n) - AD_Y(AD_K-0,n);
    e( n,2) = AD_Z(n) - AD_Y(AD_K-1,n);
    e( n,3) = AD_Z(n) - AD_Y(AD_K-2,n);
end
dutmp = r*e;
du    = dutmp * to_vec;
for n=1:nu
    control_value(1,n) = du(n,1);
end
%% STOP