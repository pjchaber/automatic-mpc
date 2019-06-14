%%
% This file is part of AutoMATiC.
% AutoMATiC -- Automatic code generation based on the MATLAB and 
% C languages.
% 
% Copytight (C) 2018-2019 by Patryk Chaber. Developed within the 
% Warsaw University of Technology, Institute of Control and 
% Computation Engineering under supervision of Maciej Lawrynczuk. 
% All rights reserved.
% 
% AutoMATiC is free software: you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation; either version 3 of the License, or
% (at your option) any later version.
% 
% AutoMATiC is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU General Public License for more details.
% 
% You should have received a copy of the GNU General Public License
% along with AutoMATiC.  If not, see <https://www.gnu.org/licenses/>.
%

classdef AutoMATiC_Lexer < handle
    properties (Constant)
         TOKEN_TYPES = [
            %% COMMENTS
            {'COMMENT'      ,'(%.*$)'};
            
            %% KEYWORDS
            {'SEMICOLON'    ,'(;)'};
            {'COLON'        ,'(:)'};
            {'OPAREN'       ,'(\()'};
            {'CPAREN'       ,'(\))'};
            {'COMA'         ,'(,)'};
            {'OPERATION'    ,'(==|>=|<=|>|<|~=|''\*|[\\*/+-])'};
            {'ASSIGN'       ,'(=)'};
            {'END'          ,'(end)'};
            {'FOR'          ,'(for)'};
            {'IF'           ,'(if)'};
            {'ELSE'         ,'(else)'};
            {'QP'           ,'(quadprog)'};
            {'OSPAREN'      ,'(\[)'};
            {'CSPAREN'      ,'(\])'};
            {'ZEROS'        ,'(zeros)'};
            
            %% VALUES AND IDENTIFIERS
            {'REAL'         ,'([+-]?[0-9]*\.[0-9]+)'};
            {'INTEGER'      ,'([+-]?[0-9]+)'};
            {'IDENTIFIER'   ,'([a-zA-Z][a-zA-Z_0-9]*)'};
            
            %% ADDITIONAL CORRECTNESS TESTS
            {'UNKNOWN'        ,'(.)'};
         ];
    end    
    properties
        totranslate % cell consisting of lines of code to translate
        toexecute   % cell consisting of lines of code to execute
        restofcode  % cell consisting of lines of code to process
        tokens      % array of cells containing consecutive tokens
    end
    methods
        function obj = AutoMATiC_Lexer(code)
            obj.totranslate = {};
            obj.toexecute   = {};
            obj.totranslate = {};
            
            obj.tokens      = [];
            
            obj.restofcode = split(code,newline); % read line by line
            obj.getcodeofinterest();
            obj.tokenize();
            if(obj.hasunknown())
                disp(obj.tokens);
                error('There are unknown tokens!');
            end
            obj.remove_comments();
        end
        
        function execute = getcodetoexecute(obj)
            execute = obj.toexecute;
        end
        
        function remove_comments(obj)
            tmptokens = [];
            for t = obj.tokens'
                if(strcmp(t{1},'COMMENT'))
                else
                    tmptokens = [tmptokens;t'];
                end
            end
            obj.tokens = tmptokens;                
        end
        
        function f = hasunknown(obj)
            f = false;
            for token = obj.tokens'
                if(strcmp(token{1},'UNKNOWN'))
                    f = true;
                    return;
                end
            end
        end
        
        function tokenize(obj)
            for i = 1:length(obj.totranslate)                
                codetotranslate = strtrim(obj.totranslate{i});
                while(~isempty(codetotranslate))
                    for token_type = obj.TOKEN_TYPES' % try each token type (from the beginning)
                        foundindex = regexpi(codetotranslate,['^\s*',token_type{2}],'tokenExtents','once'); % check if matches
                        if(~isempty(foundindex))
                            token=regexpi(codetotranslate,['^\s*',token_type{2}],'tokens','once'); % get token value
                            codetotranslate = codetotranslate(foundindex(1,2)+1:end); % remove token from input string
                            obj.tokens = [obj.tokens; {token_type{1},token{1}}]; % append token to array of tokens
                            break; % stop searching after first match
                        end
                    end
                    if(isempty(foundindex)) % if nothing matches then notify
                        fprintf('!! "%s"\n',codetotranslate)
                        codetotranslate = codetotranslate(2:end);
                    end
                end
            end
        end
        
        function getcodeofinterest(obj)
            copycontents = 0;
            obj.toexecute = [];
            obj.totranslate = [];  
            ie = 1; % iterator for executed code
            it = 1; % iterator for translated code
            for i=1:length(obj.restofcode)
                line = obj.restofcode{i};
                %fprintf('LINE: %s', line);
                if(regexpi(line,'^\s*%%\s*TRANSLATE.*$'))
                    copycontents = 1;
                elseif(regexpi(line,'^\s*%%\s*STOP.*$'))
                    if(copycontents == 0)
                        error('STOP keyword occured before TRANSLATE keyword\n');
                    end
                    if(i==length(obj.restofcode))
                        obj.restofcode = {};
                    else
                        obj.restofcode = obj.restofcode{i+1:end};
                    end
                    break; % THIS LINE MIGHT NEED REPLACING % TODO
                elseif(copycontents)
                    obj.totranslate{it}  = line;
                    it = it+1;
                else
                    obj.toexecute{ie}    = line;
                    ie = ie+1;
                end                
            end
        end
                    
        function t = gettokens(obj)
            t= obj.tokens; 
        end
        
        function disp(obj)
            for t = obj.tokens'
                fprintf('%-15s: %s\n', t{1}, t{2});
            end
        end
    end
end

