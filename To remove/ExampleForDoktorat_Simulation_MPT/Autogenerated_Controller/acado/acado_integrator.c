/*
 *    This file was auto-generated using the ACADO Toolkit.
 *    
 *    While ACADO Toolkit is free software released under the terms of
 *    the GNU Lesser General Public License (LGPL), the generated code
 *    as such remains the property of the user who used ACADO Toolkit
 *    to generate this code. In particular, user dependent data of the code
 *    do not inherit the GNU LGPL license. On the other hand, parts of the
 *    generated code that are a direct copy of source code from the
 *    ACADO Toolkit or the software tools it is based on, remain, as derived
 *    work, automatically covered by the LGPL license.
 *    
 *    ACADO Toolkit is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *    
 */


#include "acado_common.h"


void acado_rhs(const real_t* in, real_t* out)
{
const real_t* xd = in;
const real_t* u = in + 2;

/* Compute outputs: */
out[0] = ((((real_t)(0.0000000000000000e+00)-xd[0])+u[0])+((real_t)(1.0000000000000001e-01)*u[1]));
out[1] = ((((real_t)(0.0000000000000000e+00)-xd[1])+((real_t)(2.0000000000000000e-02)*u[0]))+((real_t)(9.0000000000000002e-01)*u[1]));
}



void acado_diffs(const real_t* in, real_t* out)
{
const real_t* xd = in;

/* Compute outputs: */
out[0] = ((real_t)(0.0000000000000000e+00)-(real_t)(1.0000000000000000e+00));
out[1] = (real_t)(0.0000000000000000e+00);
out[2] = (real_t)(1.0000000000000000e+00);
out[3] = (real_t)(1.0000000000000001e-01);
out[4] = (real_t)(0.0000000000000000e+00);
out[5] = ((real_t)(0.0000000000000000e+00)-(real_t)(1.0000000000000000e+00));
out[6] = (real_t)(2.0000000000000000e-02);
out[7] = (real_t)(9.0000000000000002e-01);
}



void acado_solve_dim4_triangular( real_t* const A, real_t* const b )
{

b[3] = b[3]/A[15];
b[2] -= + A[11]*b[3];
b[2] = b[2]/A[10];
b[1] -= + A[7]*b[3];
b[1] -= + A[6]*b[2];
b[1] = b[1]/A[5];
b[0] -= + A[3]*b[3];
b[0] -= + A[2]*b[2];
b[0] -= + A[1]*b[1];
b[0] = b[0]/A[0];
}

real_t acado_solve_dim4_system( real_t* const A, real_t* const b, int* const rk_perm )
{
real_t det;

int i;
int j;
int k;

int indexMax;

int intSwap;

real_t valueMax;

real_t temp;

for (i = 0; i < 4; ++i)
{
rk_perm[i] = i;
}
det = 1.0000000000000000e+00;
if(fabs(A[4]) > fabs(A[0]) && fabs(A[4]) > fabs(A[8]) && fabs(A[4]) > fabs(A[12])) {
acadoWorkspace.rk_dim4_swap = A[0];
A[0] = A[4];
A[4] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[1];
A[1] = A[5];
A[5] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[2];
A[2] = A[6];
A[6] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[3];
A[3] = A[7];
A[7] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = b[0];
b[0] = b[1];
b[1] = acadoWorkspace.rk_dim4_swap;
intSwap = rk_perm[0];
rk_perm[0] = rk_perm[1];
rk_perm[1] = intSwap;
}
else if(fabs(A[8]) > fabs(A[0]) && fabs(A[8]) > fabs(A[4]) && fabs(A[8]) > fabs(A[12])) {
acadoWorkspace.rk_dim4_swap = A[0];
A[0] = A[8];
A[8] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[1];
A[1] = A[9];
A[9] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[2];
A[2] = A[10];
A[10] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[3];
A[3] = A[11];
A[11] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = b[0];
b[0] = b[2];
b[2] = acadoWorkspace.rk_dim4_swap;
intSwap = rk_perm[0];
rk_perm[0] = rk_perm[2];
rk_perm[2] = intSwap;
}
else if(fabs(A[12]) > fabs(A[0]) && fabs(A[12]) > fabs(A[4]) && fabs(A[12]) > fabs(A[8])) {
acadoWorkspace.rk_dim4_swap = A[0];
A[0] = A[12];
A[12] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[1];
A[1] = A[13];
A[13] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[2];
A[2] = A[14];
A[14] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[3];
A[3] = A[15];
A[15] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = b[0];
b[0] = b[3];
b[3] = acadoWorkspace.rk_dim4_swap;
intSwap = rk_perm[0];
rk_perm[0] = rk_perm[3];
rk_perm[3] = intSwap;
}

A[4] = -A[4]/A[0];
A[5] += + A[4]*A[1];
A[6] += + A[4]*A[2];
A[7] += + A[4]*A[3];
b[1] += + A[4]*b[0];

A[8] = -A[8]/A[0];
A[9] += + A[8]*A[1];
A[10] += + A[8]*A[2];
A[11] += + A[8]*A[3];
b[2] += + A[8]*b[0];

A[12] = -A[12]/A[0];
A[13] += + A[12]*A[1];
A[14] += + A[12]*A[2];
A[15] += + A[12]*A[3];
b[3] += + A[12]*b[0];

det = + det*A[0];

if(fabs(A[9]) > fabs(A[5]) && fabs(A[9]) > fabs(A[13])) {
acadoWorkspace.rk_dim4_swap = A[4];
A[4] = A[8];
A[8] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[5];
A[5] = A[9];
A[9] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[6];
A[6] = A[10];
A[10] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[7];
A[7] = A[11];
A[11] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = b[1];
b[1] = b[2];
b[2] = acadoWorkspace.rk_dim4_swap;
intSwap = rk_perm[1];
rk_perm[1] = rk_perm[2];
rk_perm[2] = intSwap;
}
else if(fabs(A[13]) > fabs(A[5]) && fabs(A[13]) > fabs(A[9])) {
acadoWorkspace.rk_dim4_swap = A[4];
A[4] = A[12];
A[12] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[5];
A[5] = A[13];
A[13] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[6];
A[6] = A[14];
A[14] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[7];
A[7] = A[15];
A[15] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = b[1];
b[1] = b[3];
b[3] = acadoWorkspace.rk_dim4_swap;
intSwap = rk_perm[1];
rk_perm[1] = rk_perm[3];
rk_perm[3] = intSwap;
}

A[9] = -A[9]/A[5];
A[10] += + A[9]*A[6];
A[11] += + A[9]*A[7];
b[2] += + A[9]*b[1];

A[13] = -A[13]/A[5];
A[14] += + A[13]*A[6];
A[15] += + A[13]*A[7];
b[3] += + A[13]*b[1];

det = + det*A[5];

if(fabs(A[14]) > fabs(A[10])) {
acadoWorkspace.rk_dim4_swap = A[8];
A[8] = A[12];
A[12] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[9];
A[9] = A[13];
A[13] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[10];
A[10] = A[14];
A[14] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = A[11];
A[11] = A[15];
A[15] = acadoWorkspace.rk_dim4_swap;
acadoWorkspace.rk_dim4_swap = b[2];
b[2] = b[3];
b[3] = acadoWorkspace.rk_dim4_swap;
intSwap = rk_perm[2];
rk_perm[2] = rk_perm[3];
rk_perm[3] = intSwap;
}

A[14] = -A[14]/A[10];
A[15] += + A[14]*A[11];
b[3] += + A[14]*b[2];

det = + det*A[10];

det = + det*A[15];

det = fabs(det);
acado_solve_dim4_triangular( A, b );
return det;
}

void acado_solve_dim4_system_reuse( real_t* const A, real_t* const b, int* const rk_perm )
{

acadoWorkspace.rk_dim4_bPerm[0] = b[rk_perm[0]];
acadoWorkspace.rk_dim4_bPerm[1] = b[rk_perm[1]];
acadoWorkspace.rk_dim4_bPerm[2] = b[rk_perm[2]];
acadoWorkspace.rk_dim4_bPerm[3] = b[rk_perm[3]];
acadoWorkspace.rk_dim4_bPerm[1] += A[4]*acadoWorkspace.rk_dim4_bPerm[0];

acadoWorkspace.rk_dim4_bPerm[2] += A[8]*acadoWorkspace.rk_dim4_bPerm[0];
acadoWorkspace.rk_dim4_bPerm[2] += A[9]*acadoWorkspace.rk_dim4_bPerm[1];

acadoWorkspace.rk_dim4_bPerm[3] += A[12]*acadoWorkspace.rk_dim4_bPerm[0];
acadoWorkspace.rk_dim4_bPerm[3] += A[13]*acadoWorkspace.rk_dim4_bPerm[1];
acadoWorkspace.rk_dim4_bPerm[3] += A[14]*acadoWorkspace.rk_dim4_bPerm[2];


acado_solve_dim4_triangular( A, acadoWorkspace.rk_dim4_bPerm );
b[0] = acadoWorkspace.rk_dim4_bPerm[0];
b[1] = acadoWorkspace.rk_dim4_bPerm[1];
b[2] = acadoWorkspace.rk_dim4_bPerm[2];
b[3] = acadoWorkspace.rk_dim4_bPerm[3];
}



/** Matrix of size: 2 x 2 (row major format) */
static const real_t acado_Ah_mat[ 4 ] = 
{ 2.7777777777777780e-02, -5.5555555555555549e-03, 
5.0000000000000003e-02, 1.6666666666666666e-02 };


/* Fixed step size:0.0666667 */
int acado_integrate( real_t* const rk_eta, int resetIntegrator )
{
int error;

int i;
int j;
int k;
int run;
int run1;
int tmp_index1;
int tmp_index2;

real_t det;

acadoWorkspace.rk_ttt = 0.0000000000000000e+00;
acadoWorkspace.rk_xxx[2] = rk_eta[10];
acadoWorkspace.rk_xxx[3] = rk_eta[11];

for (run = 0; run < 3; ++run)
{
if( run > 0 ) {
for (i = 0; i < 2; ++i)
{
acadoWorkspace.rk_diffsPrev2[i * 4] = rk_eta[i * 2 + 2];
acadoWorkspace.rk_diffsPrev2[i * 4 + 1] = rk_eta[i * 2 + 3];
acadoWorkspace.rk_diffsPrev2[i * 4 + 2] = rk_eta[i * 2 + 6];
acadoWorkspace.rk_diffsPrev2[i * 4 + 3] = rk_eta[i * 2 + 7];
}
}
if( resetIntegrator ) {
for (i = 0; i < 1; ++i)
{
for (run1 = 0; run1 < 2; ++run1)
{
for (j = 0; j < 2; ++j)
{
acadoWorkspace.rk_xxx[j] = rk_eta[j];
tmp_index1 = j;
acadoWorkspace.rk_xxx[j] += + acado_Ah_mat[run1 * 2]*acadoWorkspace.rk_kkk[tmp_index1 * 2];
acadoWorkspace.rk_xxx[j] += + acado_Ah_mat[run1 * 2 + 1]*acadoWorkspace.rk_kkk[tmp_index1 * 2 + 1];
}
acado_diffs( acadoWorkspace.rk_xxx, &(acadoWorkspace.rk_diffsTemp2[ run1 * 8 ]) );
for (j = 0; j < 2; ++j)
{
tmp_index1 = (run1 * 2) + (j);
acadoWorkspace.rk_A[tmp_index1 * 4] = + acado_Ah_mat[run1 * 2]*acadoWorkspace.rk_diffsTemp2[(run1 * 8) + (j * 4)];
acadoWorkspace.rk_A[tmp_index1 * 4 + 1] = + acado_Ah_mat[run1 * 2]*acadoWorkspace.rk_diffsTemp2[(run1 * 8) + (j * 4 + 1)];
if( 0 == run1 ) acadoWorkspace.rk_A[(tmp_index1 * 4) + (j)] -= 1.0000000000000000e+00;
acadoWorkspace.rk_A[tmp_index1 * 4 + 2] = + acado_Ah_mat[run1 * 2 + 1]*acadoWorkspace.rk_diffsTemp2[(run1 * 8) + (j * 4)];
acadoWorkspace.rk_A[tmp_index1 * 4 + 3] = + acado_Ah_mat[run1 * 2 + 1]*acadoWorkspace.rk_diffsTemp2[(run1 * 8) + (j * 4 + 1)];
if( 1 == run1 ) acadoWorkspace.rk_A[(tmp_index1 * 4) + (j + 2)] -= 1.0000000000000000e+00;
}
acado_rhs( acadoWorkspace.rk_xxx, acadoWorkspace.rk_rhsTemp );
acadoWorkspace.rk_b[run1 * 2] = acadoWorkspace.rk_kkk[run1] - acadoWorkspace.rk_rhsTemp[0];
acadoWorkspace.rk_b[run1 * 2 + 1] = acadoWorkspace.rk_kkk[run1 + 2] - acadoWorkspace.rk_rhsTemp[1];
}
det = acado_solve_dim4_system( acadoWorkspace.rk_A, acadoWorkspace.rk_b, acadoWorkspace.rk_dim4_perm );
for (j = 0; j < 2; ++j)
{
acadoWorkspace.rk_kkk[j] += acadoWorkspace.rk_b[j * 2];
acadoWorkspace.rk_kkk[j + 2] += acadoWorkspace.rk_b[j * 2 + 1];
}
}
}
for (i = 0; i < 5; ++i)
{
for (run1 = 0; run1 < 2; ++run1)
{
for (j = 0; j < 2; ++j)
{
acadoWorkspace.rk_xxx[j] = rk_eta[j];
tmp_index1 = j;
acadoWorkspace.rk_xxx[j] += + acado_Ah_mat[run1 * 2]*acadoWorkspace.rk_kkk[tmp_index1 * 2];
acadoWorkspace.rk_xxx[j] += + acado_Ah_mat[run1 * 2 + 1]*acadoWorkspace.rk_kkk[tmp_index1 * 2 + 1];
}
acado_rhs( acadoWorkspace.rk_xxx, acadoWorkspace.rk_rhsTemp );
acadoWorkspace.rk_b[run1 * 2] = acadoWorkspace.rk_kkk[run1] - acadoWorkspace.rk_rhsTemp[0];
acadoWorkspace.rk_b[run1 * 2 + 1] = acadoWorkspace.rk_kkk[run1 + 2] - acadoWorkspace.rk_rhsTemp[1];
}
acado_solve_dim4_system_reuse( acadoWorkspace.rk_A, acadoWorkspace.rk_b, acadoWorkspace.rk_dim4_perm );
for (j = 0; j < 2; ++j)
{
acadoWorkspace.rk_kkk[j] += acadoWorkspace.rk_b[j * 2];
acadoWorkspace.rk_kkk[j + 2] += acadoWorkspace.rk_b[j * 2 + 1];
}
}
for (run1 = 0; run1 < 2; ++run1)
{
for (j = 0; j < 2; ++j)
{
acadoWorkspace.rk_xxx[j] = rk_eta[j];
tmp_index1 = j;
acadoWorkspace.rk_xxx[j] += + acado_Ah_mat[run1 * 2]*acadoWorkspace.rk_kkk[tmp_index1 * 2];
acadoWorkspace.rk_xxx[j] += + acado_Ah_mat[run1 * 2 + 1]*acadoWorkspace.rk_kkk[tmp_index1 * 2 + 1];
}
acado_diffs( acadoWorkspace.rk_xxx, &(acadoWorkspace.rk_diffsTemp2[ run1 * 8 ]) );
for (j = 0; j < 2; ++j)
{
tmp_index1 = (run1 * 2) + (j);
acadoWorkspace.rk_A[tmp_index1 * 4] = + acado_Ah_mat[run1 * 2]*acadoWorkspace.rk_diffsTemp2[(run1 * 8) + (j * 4)];
acadoWorkspace.rk_A[tmp_index1 * 4 + 1] = + acado_Ah_mat[run1 * 2]*acadoWorkspace.rk_diffsTemp2[(run1 * 8) + (j * 4 + 1)];
if( 0 == run1 ) acadoWorkspace.rk_A[(tmp_index1 * 4) + (j)] -= 1.0000000000000000e+00;
acadoWorkspace.rk_A[tmp_index1 * 4 + 2] = + acado_Ah_mat[run1 * 2 + 1]*acadoWorkspace.rk_diffsTemp2[(run1 * 8) + (j * 4)];
acadoWorkspace.rk_A[tmp_index1 * 4 + 3] = + acado_Ah_mat[run1 * 2 + 1]*acadoWorkspace.rk_diffsTemp2[(run1 * 8) + (j * 4 + 1)];
if( 1 == run1 ) acadoWorkspace.rk_A[(tmp_index1 * 4) + (j + 2)] -= 1.0000000000000000e+00;
}
}
for (run1 = 0; run1 < 2; ++run1)
{
for (i = 0; i < 2; ++i)
{
acadoWorkspace.rk_b[i * 2] = - acadoWorkspace.rk_diffsTemp2[(i * 8) + (run1)];
acadoWorkspace.rk_b[i * 2 + 1] = - acadoWorkspace.rk_diffsTemp2[(i * 8) + (run1 + 4)];
}
if( 0 == run1 ) {
det = acado_solve_dim4_system( acadoWorkspace.rk_A, acadoWorkspace.rk_b, acadoWorkspace.rk_dim4_perm );
}
 else {
acado_solve_dim4_system_reuse( acadoWorkspace.rk_A, acadoWorkspace.rk_b, acadoWorkspace.rk_dim4_perm );
}
for (i = 0; i < 2; ++i)
{
acadoWorkspace.rk_diffK[i] = acadoWorkspace.rk_b[i * 2];
acadoWorkspace.rk_diffK[i + 2] = acadoWorkspace.rk_b[i * 2 + 1];
}
for (i = 0; i < 2; ++i)
{
acadoWorkspace.rk_diffsNew2[(i * 4) + (run1)] = (i == run1-0);
acadoWorkspace.rk_diffsNew2[(i * 4) + (run1)] += + acadoWorkspace.rk_diffK[i * 2]*(real_t)5.0000000000000003e-02 + acadoWorkspace.rk_diffK[i * 2 + 1]*(real_t)1.6666666666666666e-02;
}
}
for (run1 = 0; run1 < 2; ++run1)
{
for (i = 0; i < 2; ++i)
{
for (j = 0; j < 2; ++j)
{
tmp_index1 = (i * 2) + (j);
tmp_index2 = (run1) + (j * 4);
acadoWorkspace.rk_b[tmp_index1] = - acadoWorkspace.rk_diffsTemp2[(i * 8) + (tmp_index2 + 2)];
}
}
acado_solve_dim4_system_reuse( acadoWorkspace.rk_A, acadoWorkspace.rk_b, acadoWorkspace.rk_dim4_perm );
for (i = 0; i < 2; ++i)
{
acadoWorkspace.rk_diffK[i] = acadoWorkspace.rk_b[i * 2];
acadoWorkspace.rk_diffK[i + 2] = acadoWorkspace.rk_b[i * 2 + 1];
}
for (i = 0; i < 2; ++i)
{
acadoWorkspace.rk_diffsNew2[(i * 4) + (run1 + 2)] = + acadoWorkspace.rk_diffK[i * 2]*(real_t)5.0000000000000003e-02 + acadoWorkspace.rk_diffK[i * 2 + 1]*(real_t)1.6666666666666666e-02;
}
}
rk_eta[0] += + acadoWorkspace.rk_kkk[0]*(real_t)5.0000000000000003e-02 + acadoWorkspace.rk_kkk[1]*(real_t)1.6666666666666666e-02;
rk_eta[1] += + acadoWorkspace.rk_kkk[2]*(real_t)5.0000000000000003e-02 + acadoWorkspace.rk_kkk[3]*(real_t)1.6666666666666666e-02;
if( run == 0 ) {
for (i = 0; i < 2; ++i)
{
for (j = 0; j < 2; ++j)
{
tmp_index2 = (j) + (i * 2);
rk_eta[tmp_index2 + 2] = acadoWorkspace.rk_diffsNew2[(i * 4) + (j)];
}
for (j = 0; j < 2; ++j)
{
tmp_index2 = (j) + (i * 2);
rk_eta[tmp_index2 + 6] = acadoWorkspace.rk_diffsNew2[(i * 4) + (j + 2)];
}
}
}
else {
for (i = 0; i < 2; ++i)
{
for (j = 0; j < 2; ++j)
{
tmp_index2 = (j) + (i * 2);
rk_eta[tmp_index2 + 2] = + acadoWorkspace.rk_diffsNew2[i * 4]*acadoWorkspace.rk_diffsPrev2[j];
rk_eta[tmp_index2 + 2] += + acadoWorkspace.rk_diffsNew2[i * 4 + 1]*acadoWorkspace.rk_diffsPrev2[j + 4];
}
for (j = 0; j < 2; ++j)
{
tmp_index2 = (j) + (i * 2);
rk_eta[tmp_index2 + 6] = acadoWorkspace.rk_diffsNew2[(i * 4) + (j + 2)];
rk_eta[tmp_index2 + 6] += + acadoWorkspace.rk_diffsNew2[i * 4]*acadoWorkspace.rk_diffsPrev2[j + 2];
rk_eta[tmp_index2 + 6] += + acadoWorkspace.rk_diffsNew2[i * 4 + 1]*acadoWorkspace.rk_diffsPrev2[j + 6];
}
}
}
resetIntegrator = 0;
acadoWorkspace.rk_ttt += 3.3333333333333331e-01;
}
for (i = 0; i < 2; ++i)
{
}
if( det < 1e-12 ) {
error = 2;
} else if( det < 1e-6 ) {
error = 1;
} else {
error = 0;
}
return error;
}



