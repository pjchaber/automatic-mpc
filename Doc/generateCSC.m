
function output = generateCSC(M)
    n = size(M,1);
    m = size(M,2);
    x = [];
    ind = [];
    p = [];
    
    
    for j = 1:m
        ptmp = [];
        for i = 1:n
            if(M(i,j) ~= 0)
                x = [x M(i,j)];
                if( isempty(ptmp))
                    ptmp = length(x)-1;
                end
                ind = [ind, i-1];
            end
        end
        p = [p ptmp];
    end
    p = [p length(x)];
    nnz = length(x);
    output.p=p;
    output.i=ind;
    output.x=x;
    output.m=size(M,1);
    output.n=size(M,2);
end
