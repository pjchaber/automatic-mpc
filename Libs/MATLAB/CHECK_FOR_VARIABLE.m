function CHECK_FOR_VARIABLE(var,what_to_do)
    if(nargin == 1)
        what_to_do = 'ignore';
    end
    existin=@(var)(evalin('base',sprintf('exist(''%s'',''var'')',var)));
    if(~existin(var))
        if(strcmp(what_to_do,'define'))
            eval([var '=[];']);
        elseif(strcmp(what_to_do,'warning'))
            wanrning('CheckForVariable:NoVariable','No "%s" variable defined',var); 
        elseif(strcmp(what_to_do,'error'))
            error('No "%s" variable defined',var); 
        else
            %fprintf('no action\n');
        end
    end
end