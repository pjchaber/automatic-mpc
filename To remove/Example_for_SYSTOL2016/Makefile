all:
	../crosscompiler -i input.mpc -o main.c -l ../Libs/MATLAB -L ../Libs/C -I -p
	make -f Makefile_stm32

clean:
	rm -rf ./*.out
