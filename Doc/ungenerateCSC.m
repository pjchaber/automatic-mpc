function M = ungenerateCSC(csc)
    M = zeros(csc.m,csc.n);
    for i = 1:(length(csc.p)-1)
        ind = (csc.p(i):(csc.p(i+1)-1))+1;
        M(csc.i(ind)+1,i) = csc.x(ind);
    end
end