function test(a)
    persistent x
    if(nargin == 0)
        fprintf('CLEAR\n');
        x = [];
        return;
    end
    if(isempty(x))
        fprintf('EMPTY\n');
        x = 10;
    else
        fprintf('FULL\n');
        x = x+1;
    end
    x
end