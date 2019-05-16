function code = AutoMATiC_Generate(alg,name,first)
    if(nargin < 3)
        first = 1;
    end
    evalin('base','INIT = 1;');
    L = AutoMATiC_Lexer(fileread([alg '.m']));
    tokens = L.gettokens();
    toexecute = L.getcodetoexecute();

    P = AutoMATiC_Parser(tokens);
    tree = P.gettree();

    G = AutoMATiC_Generator(toexecute,tree);
    
    if(first)
        mode = 'w';
    else
        mode = 'a';
    end
    fd = fopen('C:/AutoMATiC_Temp/tmp.c',mode);
    fprintf(fd,G.code,name);
    code = sprintf(G.code,name);
    fclose(fd);
end