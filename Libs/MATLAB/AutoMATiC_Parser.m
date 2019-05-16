classdef AutoMATiC_Parser < handle
    properties
        tokens
        variablesset
        variablesref
        tree
    end
    
    methods
        function obj = AutoMATiC_Parser(tokens)
            obj.tokens = tokens;
            obj.tree = obj.parse_all();

            %plot(obj.tree,'PAR_PRE_OPT');
            %plot(obj.tree,'START_PARSER');
            while(obj.simplify_expressions())
                continue;
            end
            %plot(obj.tree,'PAR_POST_OPT');
            %plot(obj.tree,'END_PARSER');
            %plot(obj.tree,'G');
            %disp(obj.tree);
            ids = obj.findallidentifiers(obj.tree);
            %disp(ids);
        end
        
        function sthdone = simplify_expressions(obj,node)
            sthdone = 0;
            if(nargin == 1)
                node = obj.tree;
            end
            if(node == 'SYMBOLORVALUE')
                sthdone = sthdone + 1;
                node.type = node.children(1).type;
                node.value = node.children(1).value;
                node.children = node.children(1).children;
            elseif(node == 'EXPRESSION')
                if(length(node.children) == 1) % getting rid of SYMBOLORVALUE
                    if(node.children(1) == 'SYMBOLORVALUE')
                        sthdone = sthdone + 1;
                        node.type = node.children(1).type;
                        node.value = node.children(1).children(1).value;
                        tmp = node.children(1).children(1);
                        node.children = tmp;
                    end
                else
                    chk1 = 0;
                    chk2 = 0;
                    if(node.children(1) == 'REAL' || ...
                            node.children(1) == 'INTEGER')
                        chk1 = 1;
                    end
                    if(node.children(3) == 'REAL' || ...
                            node.children(3) == 'INTEGER')
                        chk2 = 1;
                    end
                    if(chk1 && chk2)
                        sthdone = sthdone + 1;
                        if(strcmp(node.children(1).type, node.children(3).type))
                            node.type = node.children(1).type;
                        else
                            node.type = 'REAL';
                        end
                        node.value = num2str(eval(join([node.children(1).value node.children(2).value node.children(3).value],' ')));
                        node.children = [];                     
                    end
                end
            end
            for c = node.children
                sthdone = sthdone + obj.simplify_expressions(c);
            end
        end

        function identifiers = findallidentifiers(obj,node,identifiers)
            if(nargin == 2)
                identifiers = {};
            end
            if(node == 'IDENTIFIER')
                identifiers = [identifiers, node.value];
            end
            for c = node.children
                identifiers = obj.findallidentifiers(c,identifiers);
            end                
        end
        
        function simplify(obj,node)
            
        end
        
        function tree = gettree(obj)
            tree = obj.tree;
        end
        
        function all = parse_all(obj)
            all = AutoMATiC_Node('ALL');
            while(~isempty(obj.tokens))
                all.addchild(obj.parse_script());
            end
        end
        
        function script = parse_script(obj)
            script = AutoMATiC_Node('SCRIPT');
            if(obj.peek('IF'))
                script.addchild(obj.parse_if());
            elseif(obj.peek('FOR'))
                script.addchild(obj.parse_for());
            else
                script.addchild(obj.parse_assignment());
            end
        end
        
        function forr = parse_for(obj)
            forr = AutoMATiC_Node('FOR');
            obj.consume('FOR');
            if(obj.peek('SEMICOLON'))
                obj.consume('SEMICOLON');
            end
            forr.addchild(obj.consumenode('IDENTIFIER'));
            obj.consume('ASSIGN');
            forr.addchild(obj.parse_expression());
            obj.consume('COLON');
            forr.addchild(obj.parse_expression());
            while(~obj.peek('END'))
                forr.addchild(obj.parse_script());
            end
            obj.consume('END'); 
        end
        
        function iff = parse_if(obj)
            iff = AutoMATiC_Node('IF');
            obj.consume('IF');
            obj.consume('OPAREN');
            iff.addchild(obj.parse_expression())
            obj.consume('CPAREN');
            if(obj.peek('SEMICOLON'))
                obj.consume('SEMICOLON');
            end
            iff.addchild(obj.parse_script());
            while(~obj.peek('END'))
                iff.addchild(obj.parse_script());
            end
            obj.consume('END');
        end
        
        
        
        function symbolorvalue = parse_symbolorvalue(obj)
            symbolorvalue = AutoMATiC_Node('SYMBOLORVALUE');
            if(obj.peek('IDENTIFIER'))
                symbolorvalue.addchild(obj.parse_variable());
            elseif(obj.peek('REAL'))
                symbolorvalue.addchild(obj.consumenode('REAL'));
            elseif(obj.peek('INTEGER'))
                symbolorvalue.addchild(obj.consumenode('INTEGER'));
            end
        end
        
        function expression = parse_expression(obj)
            expression = AutoMATiC_Node('EXPRESSION');
            if(obj.peek('OPERATION'))
                expression.addchild(AutoMATiC_Node('INTEGER','0')); % changes -X to 0-X for further easier analisys                    
            elseif(obj.peek('OPAREN'))
                obj.consume('OPAREN');
                expression.addchild(obj.parse_expression());
                obj.consume('CPAREN');
            else
                expression.addchild(obj.parse_symbolorvalue());
            end
            if(obj.peek('OPERATION'))
                expression.addchild(obj.consumenode('OPERATION'));
                expression.addchild(obj.parse_expression());
            end
        end
        
        function zeross = parse_zeros(obj)
            zeross = AutoMATiC_Node('ZEROS');
            obj.consumenode('ZEROS');
            obj.consume('OPAREN');
            zeross.addchild(obj.parse_expression());
            while(obj.peek('COMA'))
                obj.consume('COMA');
                zeross.addchild(obj.parse_expression());
            end
            obj.consume('CPAREN'); 
        end
        
        function assignment = parse_assignment(obj)
            assignment = AutoMATiC_Node('ASSIGNMENT');
            assignment.addchild(obj.parse_variable());
            obj.consume('ASSIGN');
            if(obj.peek('OSPAREN'))
                assignment.addchild(obj.parse_matrixdef());
            elseif(obj.peek('ZEROS'))
                assignment.addchild(obj.parse_zeros());
            elseif(obj.peek('QP'))
                assignment.addchild(obj.parse_quadprog());
            else
                assignment.addchild(obj.parse_expression());
            end
            obj.consume('SEMICOLON');
        end
        
        function matrixdef = parse_matrixdef(obj)
            matrixdef = AutoMATiC_Node('MATRIX');
            obj.consume('OSPAREN');
            obj.consume('CSPAREN');
        end
        
        function quadprognode = parse_quadprog(obj)
            quadprognode = AutoMATiC_Node('QUADPROG');
            obj.consume('QP');
            obj.consume('OPAREN');
            quadprognode.addchild(obj.consumenode('IDENTIFIER'));
            obj.consume('COMA');
            quadprognode.addchild(obj.consumenode('IDENTIFIER'));
            obj.consume('COMA');
            quadprognode.addchild(obj.consumenode('IDENTIFIER'));
            obj.consume('COMA');
            quadprognode.addchild(obj.consumenode('IDENTIFIER'));
            while(obj.peek('COMA'))
                obj.consume('COMA');
                if(obj.peek('OSPAREN'))
                    obj.consume('OSPAREN');
                    obj.consume('CSPAREN');
                else
                    obj.consume('IDENTIFIER');
                end
            end
            obj.consume('CPAREN');
        end
        
        function variable = parse_variable(obj)
            variable = AutoMATiC_Node('VARIABLE');
            variable.addchild(obj.consumenode('IDENTIFIER'));
            if(obj.peek('OPAREN'))
                obj.consume('OPAREN');
                variable.addchild(obj.parse_range_limit());
                while(obj.peek('COMA'))
                    obj.consume('COMA');
                    variable.addchild(obj.parse_range_limit());
                end
                obj.consume('CPAREN');
            end
        end
        
        function rangelimit = parse_range_limit(obj)
            if(obj.peek('END'))
                obj.consumenode('END');
                rangelimit = AutoMATiC_Node('INTEGER','-1');
            else
                rangelimit = obj.parse_expression();
            end
        end
        
        function t = consume(obj, expected_type)
            t = obj.tokens(1,:);
            obj.tokens = obj.tokens(2:end,:);
            if(strcmp(t{1},expected_type))
                %fprintf('CONSUMED: %s (%s)\n',t{2},t{1});
            else
                error('Expected type %s, but got %s.',expected_type,t{1});
            end
        end
        
        function node = consumenode(obj, expected_type)
            token = obj.consume(expected_type);
            node = AutoMATiC_Node(token{1},token{2});
        end
        
        function f = peek(obj, expected_type, pos)
            if(nargin == 2)
                pos = 1;
            end
            
            if(strcmp(obj.tokens{pos,1},expected_type))
                f = true;
            else 
                f = false;
            end
        end
        
        function disp(obj)
            disp(obj.tree);
        end
    end
end