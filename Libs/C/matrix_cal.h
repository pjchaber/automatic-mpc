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

void productaat(float **a,float **b,long a1,long a2); //b=a*a', a(a1,a2), b(a1,a1)
void productata (float **a,float **b,long a1,long a2);//b=a'*a, a(a1,a2), b(a2,a2)
void productab  (float **a,float **b,float **c,long a1,long a2,long b1,long b2); //c=a*b, a(a1,a2), b(b1,b2), c(a1,b2), necessary condition a2=b1
void productatb (float **a,float **b,float **c,long a1,long a2,long b1,long b2); //c=a'*b, a(a1,a2), b(b1,b2), c(a2,b2), necessary condition a1=b1
void productatbt(float **a,float **b,float **c,long a1,long a2,long b1,long b2); //c=a'*bt, a(a1,a2), b(b1,b2), c(a2,b1), necessary condition a1=b2
void productabt (float **a,float **b,float **c,long a1,long a2,long b1,long b2); //c=a*b', a(a1,a2), b(b1,b2), c(a1,b1), necessary condition a2=b2
void productav  (float **a,float *vb,float * c,long a1,long a2,long v1);         //c=a*vb, a(a1,a2), vb(v1), c(a1), necessary condition a2=v1
void sumvv     (float *va,float *vb,float *vc,long v1,long sum);                 //vc=va+vb when sum=1 or vc=va-vb when sum=-1
void sumaa     (float **a,float **b,float **c,long a1,long a2,long sum);         //c=a+b when sum=1 or c=a-b when sum=-1
void productvvt (float *va,float *vb,float **c,long v1,long v2);                 //c=va*vb', va(v1), vb(v2), c(v1,v2)
float productvtv(float *va,float *vb,long   v1);                                 //c=va'*vb, va(v1), vb(v1), c - scalar
void productvta (float *va,float **b,float *vc,long v1,long b1,long b2);         //vc=va*b, va(v1), b(b1,b2), c(b2), necessary condition v1=b1
void productatv (float **a,float *vb,float *vc,long a1,long a2,long b1);         //vc=a'*vb, a(a1,a2), b(b1), vc(a2), necessary condition a1=b1
void dividea    (float **a,float   b,float **c,long v1,long v2);                 //c=a/b, a,c(v1,v2), b - scalar
void producta   (float **a,float   b,float **c,long v1,long v2);                 //c=a*b, a,c(v1,v2), b - scalar
void productv   (float *va,float   b,float *vc,long v1);                         //vc=va*b, va=(v1), b - scalar
