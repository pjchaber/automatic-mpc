function output = makeCSC(x,p,i)
    output.p=p;
    output.i=i;
    output.x=x;
    output.m=max(max(i));
    output.n=length(p)-1;
end