if(MPC_CROSSCOMPILER == 1)
    %generate(PID([1,1,1,1]),'PID');
    generate(DMC_analitic([1,2,3],2,2,1,[],[],[],[]),'DMC_analitic');
    return;
end
