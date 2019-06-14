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

classdef AutoMATiC_Node < handle
    properties
        type
        value
        children
        parent
        id
        parentid
    end
    
    methods
        function obj = AutoMATiC_Node(type, value)
            if(nargin == 1)
                value = '';
            end
            obj.type = type;
            obj.value = value;
            obj.parent = [];
            obj.children = [];
            obj.id = [];
            obj.parentid = [];
        end
        
        function addchild(obj, node)
            node.parent = obj;
            obj.children = [obj.children, node];
        end
        
        function t = eq(obj, b)
            t = strcmp(obj.type, b);
        end
        
        function nodes  = assignIds(obj, nodes, id, parentid)
            persistent lastid
            if(id==1)
                lastid = 1;
                obj.parentid = 0;
            else
                obj.parentid = parentid;
            end
            nodes{lastid}=obj;
            obj.id = id;
            for ci = 1:length(obj.children)
                lastid=lastid+1;
                nodes = obj.children(ci).assignIds(nodes,lastid,id);
            end
        end
        
        function nodes  = getGraphViz(obj, nodes, id, parentid, name)
            persistent lastid
            if(id==1)
                lastid = 1;
                obj.parentid = 0;
            else
                obj.parentid = parentid;
            end
            nodes{lastid}=obj;
            obj.id = id;
            for ci = 1:length(obj.children)
                lastid=lastid+1;
                nodes = obj.children(ci).getGraphViz(nodes,lastid,id);
            end
            if(id==1)
                %fprintf('digraph %s{\nrankdir=LR;\nnode [style=filled,fillcolor=white]\n',name);
                fprintf('digraph %s{rankdir=LR;node [style=filled,fillcolor=white];',name);
                edges = [];
                for n = 1:length(nodes)
                    thisnode = nodes{n};
                    if(thisnode.parentid)
                        edges = [edges; thisnode.parentid, thisnode.id];
                    end
                    style = '';
%                     if(strcmp(thisnode.type, 'IDENTIFIER'))
%                         style = 'fillcolor = red2,';
%                     elseif(strcmp(thisnode.type, 'REAL') || strcmp(thisnode.type, 'INTEGER'))
%                         style = 'fillcolor = springgreen3,';
%                     elseif(strcmp(thisnode.type, 'OPERATION'))
%                         style = 'fillcolor = dodgerblue,';
%                     end
                    %fprintf('n%d [%slabel = "%s\\n\\"%s\\""]\n',thisnode.id,style,thisnode.type,thisnode.value);
                    fprintf('n%d [%slabel = "%s\\n\\"%s\\""];',thisnode.id,style,thisnode.type,thisnode.value);
                end
                for eid = 1:size(edges,1) % 1 is root
                    %fprintf('n%d->n%d\n',edges(eid,1),edges(eid,2));
                    fprintf('n%d->n%d;',edges(eid,1),edges(eid,2));
                end
                  %"webgraphviz" -> "@" -> "gmail" -> "." -> "com"
                fprintf('}\n');
                
            end
        end
        
        function plot(obj,name)
            obj.getGraphViz({},1,[],name);
        end
        
        function disp(obj,lvl)
            try
            if(nargin == 1)
                lvl = 0;
            end
            if(lvl > 100)
                throw(MException('AutoMATiC_Node:Display:RecursionPossible','Possible recursion -- displaying aborted.'));
            end
            for i=1:lvl
                fprintf('\t');
            end
            fprintf('"%s" (%s)\n',obj.value,obj.type);
            %for c = obj.children 
            %    disp(c,lvl+1);
            %end
            catch ME
                throwAsCaller(ME);
            end
        end
    end
end