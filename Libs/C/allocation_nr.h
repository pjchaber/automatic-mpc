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

//void piszkomunikat(char tekst[],int polecenie);
//long *lwektor(long nl, long nh);
//long **ltablica(long nrl, long nrh, long ncl, long nch);
//float *dwektor(long nl, long nh);
//float **dtablica(long nrl, long nrh, long ncl, long nch);
//float ***dtablica3(long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
//void dwektorkasuj(float *v, long nl, long nh);
//void dtablicakasuj(float **m, long nrl, long nrh, long ncl, long nch);
//void dtablica3kasuj(float ***t, long nrl, long nrh, long ncl, long nch,long ndl, long ndh);
//void lwektorkasuj(long *v, long nl, long nh);
//void ltablicakasuj(long **m, long nrl, long nrh, long ncl, long nch);
//long wart_max(long a, long b);
//long wart_min(long a, long b);

void writemessage(char text[],int exit);
long *lvector(long nl, long nh);
long **larray(long nrl, long nrh, long ncl, long nch);
float *dvector(long nl, long nh);
float **darray(long nrl, long nrh, long ncl, long nch);
float ***darray3(long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
void dvectordelete(float *v, long nl, long nh);
void darraydelete(float **m, long nrl, long nrh, long ncl, long nch);
void darray3delete(float ***t, long nrl, long nrh, long ncl, long nch,long ndl, long ndh);
void lvectordelete(long *v, long nl, long nh);
void larraydelete(long **m, long nrl, long nrh, long ncl, long nch);
long value_max(long a, long b);
long value_min(long a, long b);
