/*
 * This file is part of AutoMATiC.
 * AutoMATiC -- Automatic code generation based on the MATLAB and 
 * C languages.
 * 
 * Copytight (C) 2018-2019 by Patryk Chaber. Developed within the 
 * Warsaw University of Technology, Institute of Control and 
 * Computation Engineering under supervision of Maciej Lawrynczuk. 
 * All rights reserved.
 * 
 * AutoMATiC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AutoMATiC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with AutoMATiC.  If not, see <https://www.gnu.org/licenses/>.
 */

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
