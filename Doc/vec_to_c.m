
function vec_to_c(v,name,integer)
    if(nargin == 2)
        if(all(mod(v,1) == 0))
            integer = 1;
        else
            integer = 0;
        end
    end
    
    if(integer)
        fprintf('c_int %s[%d] = {', name, length(v));
    else
        fprintf('c_float %s[%d] = {', name, length(v));
    end
        
    for i = 1:length(v)
        if(i~=1)
            fprintf(',');
        end
        
        if(integer)
            fprintf('%d',v(i));
        else 
            fprintf('%e',v(i));
        end
    end
    
    fprintf('};\n');
end