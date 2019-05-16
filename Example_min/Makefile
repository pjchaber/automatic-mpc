all:
	../crosscompiler -p -i input.mpc -l ../Libs/MATLAB -L ../Libs/C -o main.c -v -I -T 20000000
	make -f Makefile_stm32
	# gcc ./Libs/*.o main.c -lm -oa.out
	# ./a.out

clean:
	rm -rf ./*.out
