#include "mat_lib.h"
#include <stdio.h>
#include <stdlib.h>

#define MICROCONTROLLER_USED

static void error(const char * err){
	#ifdef MICROCONTROLLER_USED
		while(1);
	#else
		printf("[EE] Error occured: %s\n",err);
		exit(1);
	#endif
}

float mat_get(float * A, int Ax, int Ay, int x, int y){
	if(x>=Ax || y>=Ay || x<0 || y<0) 
		error("incorrect index");
	return *(A+x*Ay+y);
}

void mat_set(float * A, int Ax, int Ay, int x, int y, float X){
	if(x>=Ax || y>=Ay || x<0 || y<0) 
		error("incorrect index");
	A[x*Ay+y] = X;
}

void mat_mul(float * A, int Ax, int Ay, float * B, int Bx, int By, float * C){
	int x = 0; int y = 0; int k = 0;
	if(Bx!=Ay) 
		error("inconsistent matrices sizes");
	
	for(x=0; x<Ax; ++x){
		for(y=0; y<By; ++y){
			mat_set(C,Ax,By,x,y,0.0);
			for(k=0; k<Ay; ++k){
				mat_set(C,Ax,By,x,y,mat_get(C,Ax,By,x,y)+mat_get(A,Ax,Ay,x,k)*mat_get(B,Bx,By,k,y));
			}
		}
	}
}

void mat_mul_s(float * A, int Ax, int Ay, float X, float * C){
	int x = 0; int y = 0;

	for(x=0; x<Ax; ++x){
		for(y=0; y<Ay; ++y){
			mat_set(C,Ax,Ay,x,y,mat_get(A,Ax,Ay,x,y)*X);
		}
	}
}

void mat_add(float * A, int Ax, int Ay, float * B, float * C){
	int x = 0; int y = 0;
	
	for(x=0; x<Ax; ++x){
		for(y=0; y<Ay; ++y){
			mat_set(C,Ax,Ay,x,y,mat_get(A,Ax,Ay,x,y)+mat_get(B,Ax,Ay,x,y));
		}
	}
}

void mat_add_s(float * A, int Ax, int Ay, float X, float * C){
	int x = 0; int y = 0;
	
	for(x=0; x<Ax; ++x){
		for(y=0; y<Ay; ++y){
			mat_set(C,Ax,Ay,x,y,mat_get(A,Ax,Ay,x,y)+X);
		}
	}
}

void mat_trans(float * A, int Ax, float * C){
	int x = 0; int y = 0;
	float tmp = 0.0;

	for(x=0; x<Ax; ++x){
		for(y=0; y<=x; ++y){
			tmp = mat_get(A,Ax,Ax,x,y);
			mat_set(C,Ax,Ax,x,y,mat_get(A,Ax,Ax,y,x));
			mat_set(C,Ax,Ax,y,x,tmp);
		}
	}
}

void mat_move_up(float * A, int Ax, int Ay, float X, float * C){
	int x = 0; int y = 0;
	for(x=0; x<(Ax-1); ++x){
		for(y=0; y<Ay; ++y){
			mat_set(C,Ax,Ay,x,y,mat_get(A,Ax,Ay,x+1,y));
		}
	}
	for(y=0; y<Ay; ++y){
		mat_set(C,Ax,Ay,Ax-1,y,X);
	}
}

void mat_move_down(float * A, int Ax, int Ay, float X, float * C){
	int x = 0; int y = 0;
	for(x=(Ax-1); x>0; --x){
		for(y=0; y<Ay; ++y){
			mat_set(C,Ax,Ay,x,y,mat_get(A,Ax,Ay,x-1,y));
		}
	}
	for(y=0; y<Ay; ++y){
		mat_set(C,Ax,Ay,0,y,X);
	}
}

void mat_move_left(float * A, int Ax, int Ay, float X, float * C){
	int x = 0; int y = 0;
	for(x=0; x<Ax; ++x){
		for(y=0; y<(Ay-1); ++y){
			mat_set(C,Ax,Ay,x,y,mat_get(A,Ax,Ay,x,y+1));
		}
	}
	for(x=0; x<Ax; ++x){
		mat_set(C,Ax,Ay,x,Ay-1,X);
	}
}

void mat_move_right(float * A, int Ax, int Ay, float X, float * C){
	int x = 0; int y = 0;
	for(x=0; x<Ax; ++x){
		for(y=(Ay-1); y>0; --y){
			mat_set(C,Ax,Ay,x,y,mat_get(A,Ax,Ay,x,y-1));
		}
	}
	for(x=0; x<Ax; ++x){
		mat_set(C,Ax,Ay,x,0,X);
	}
}


int mat_str(float * A, int Ax, int Ay, char * str, int strlen){
	static char tmpstr[100] = {0};
	int stored = 0;
	int tmpstored = 0;
	int x = 0; int y = 0; int i = 0;
	char oc = ' '; char cc = ' ';
	for(x=0; x<Ax; ++x){
		for(y=0; y<Ay; ++y){
			oc = ' '; cc = ' ';
			if(y==(Ay-1)) cc = ';';
			else cc = ',';
			if(x==0 && y==0) oc = '[';
			else if(x==(Ax-1) && y==(Ay-1)) cc = ']';

			tmpstored = sprintf(tmpstr, "%c%f%c", oc,mat_get(A,Ax,Ay,x,y),cc);
			if(cc==';') tmpstr[tmpstored++]='\n';
			if((stored+tmpstored) > strlen) return 1;
	 		for(i=0; i<tmpstored; ++i) str[stored+i] = tmpstr[i];
	 		stored+=tmpstored;
		}
	}
	if(stored+1 > strlen) return 1;
	str[stored++] = '\0';
	return 0;
}

void mat_set_all(float * A, int Ax, int Ay, float X){
	int x = 0;
	for(x=0; x<Ax*Ay; ++x){
		A[x] = X;
	}
}
