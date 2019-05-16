all:
#	g++ main.cpp -o ./crosscompiler -I/usr/local/MATLAB/R2012a/extern/include -L/usr/local/MATLAB/R2012a/bin/glnxa64 -lmx -leng
#	matlab -nodisplay -nosplash -nodesktop -r "cd C:/Users/Admin/Documents/GitHub/Cpp/Kompilator_skrosny/ ; mex -v -client engine main.cpp XGetopt.cpp; exit;" -wait
	matlab -nodisplay -nosplash -nodesktop -r "cd C:/Users/Admin/Documents/GitHub/AutoMATiC/ ; mex -v -client engine main.cpp XGetopt.cpp; exit;" -wait
#	matlab -nodisplay -nosplash -nodesktop -r "cd D:/Git/GitHub/Cpp/Kompilator_skrosny/ ; mex -client engine main.cpp XGetopt.cpp; exit;"
	./main


clean:
	rm -rf ./crosscompiler
	rm -rf *tmp.m
