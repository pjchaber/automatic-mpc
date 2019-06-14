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

float rozklu(float **mac,long wym,float **macl,long *ind,float *znak);
long liczwyznmacodwr(float **ma,long wym,float **ma1,float *wyzn,int tryb);
float liczwyzn(float **ma,long wym);
float znak(float x);
void rozkqr(long ilw,long ilk);
int pkr(void);
void koniecpk(void);
int testogr(void);
int pomocniczezadpkr(void);

void definevarnum(long ilzm_);
void defineconnum(long ilogr_);
int qp(void);

void initializeqp(void);
float ** obtainA(void);
float * obtainb(void);
float * obtainx(void);
float * obtainlambda(void);
float ** obtainG(void);
float * obtaint(void);
float obtainepsogr(void);
float obtainzero(void);
long obtainvarnum(void);
long obtainconnum(void);
