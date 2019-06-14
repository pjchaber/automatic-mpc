/* Matrices are defined as:

float A[Ax*Ay] = {A11 ,A12 ,...,A1Ay ,
                  A21 ,A22 ,...,A2Ay ,
                  ....,....,...,.....,
                  AAx1,AAx2,...,AAxAy};

where Ax is number of rows of matrix A 
and Ay is number of columns of matrix A */

float mat_get(float * A, int Ax, int Ay, int x, int y);							// returns value from position (x,y) of matrix A which dimensionality is Ax x Ay
void mat_set(float * A, int Ax, int Ay, int x, int y, float X);					// sets value X at position (x,y) of matrix A which dimensionality is Ax x Ay

int mat_str(float * A, int Ax, int Ay, char * str, int strlen);					// converts matrix A which dimensionality is Ax x Ay into string str which length is strlen

void mat_mul(float * A, int Ax, int Ay, float * B, int Bx, int By, float * C);	// multiplies matrix A which dimensionality is Ax x Ay and B which dimensionality is Bx x By storing results to the matrix C which dimensionality is Ax x By
void mat_mul_s(float * A, int Ax, int Ay, float X, float * C);					// multiplies matrix A which dimensionality is Ax x Ay and scalar X storing results to the matrix C which dimensionality is Ax x Ay
void mat_add(float * A, int Ax, int Ay, float * B, float * C);					// adds matrix A which dimensionality is Ax x Ay and B which dimensionality is Ax x Ay storing results to the matrix C which dimensionality is Ax x Ay
void mat_add_s(float * A, int Ax, int Ay, float X, float * C);					// adds matrix A which dimensionality is Ax x Ay and scalar X storing results to the matrix C which dimensionality is Ax x Ay
void mat_trans(float * A, int Ax, float * C);									// creates a transposition of matrix A which dimensionality is Ax x Ax storing results to the matrix C which dimensionality is Ax x Ax
void mat_move_up(float * A, int Ax, int Ay, float X, float * C);				// shifts up every elements of matrix A which dimensionality is Ax x Ay filling empty spaces with value X storing results to the matrix C which dimensionality is Ax x Ay
void mat_move_down(float * A, int Ax, int Ay, float X, float * C);				// shifts down every elements of matrix A which dimensionality is Ax x Ay filling empty spaces with value X storing results to the matrix C which dimensionality is Ax x Ay
void mat_move_left(float * A, int Ax, int Ay, float X, float * C);				// shifts left every elements of matrix A which dimensionality is Ax x Ay filling empty spaces with value X storing results to the matrix C which dimensionality is Ax x Ay
void mat_move_right(float * A, int Ax, int Ay, float X, float * C);				// shifts right every elements of matrix A which dimensionality is Ax x Ay filling empty spaces with value X storing results to the matrix C which dimensionality is Ax x Ay

void mat_set_all(float * A, int Ax, int Ay, float X);
