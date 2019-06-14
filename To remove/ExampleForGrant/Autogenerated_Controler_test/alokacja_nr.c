//alokacja pamiêci jak w ksiazce Numerical Recipes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NR_END 1
#define FREE_ARG char*
  	
void piszkomunikat(char tekst[],int wyjscie)
{
	printf("%s",tekst);
	if (wyjscie==1)
		while(1);
}

long *lwektor(long nl, long nh)
{
	long *v;

	v=(long *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(long)));
	if (!v) piszkomunikat("brak pamiêci",1);
	return v-nl+NR_END;
}

void lwektorkasuj(long *v, long nl, long nh)
{
	free((FREE_ARG) (v+nl-NR_END));
}

float *dwektor(long nl, long nh)
{
	float *v;

	v=(float *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(float)));
	if (!v) piszkomunikat("brak pamiêci",1);
	return v-nl+NR_END;
}

void dwektorkasuj(float *v, long nl, long nh)
{
	free((FREE_ARG) (v+nl-NR_END));
}

long **ltablica(long nrl, long nrh, long ncl, long nch)
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	long **m;

	m=(long **) malloc((size_t)((nrow+NR_END)*sizeof(long*)));
	if (!m) piszkomunikat("brak pamiêci",1);
	m += NR_END;
	m -= nrl;

	m[nrl]=(long *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(long)));
	if (!m[nrl]) piszkomunikat("brak pamiêci",1);
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	return m;
}

void ltablicakasuj(long **m, long nrl, long nrh, long ncl, long nch)
{
	free((FREE_ARG) (m[nrl]+ncl-NR_END));
	free((FREE_ARG) (m+nrl-NR_END));
}

float **dtablica(long nrl, long nrh, long ncl, long nch)
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	float **m;

	m=(float **) malloc((size_t)((nrow+NR_END)*sizeof(float*)));
	if (!m) piszkomunikat("brak pamiêci",1);
	m += NR_END;
	m -= nrl;

	m[nrl]=(float *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float)));
	if (!m[nrl]) piszkomunikat("brak pamiêci",1);
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	return m;
}

void dtablicakasuj(float **m, long nrl, long nrh, long ncl, long nch)
{
	free((FREE_ARG) (m[nrl]+ncl-NR_END));
	free((FREE_ARG) (m+nrl-NR_END));
}

float ***dtablica3(long nrl, long nrh, long ncl, long nch, long ndl, long ndh)
{
	long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1,ndep=ndh-ndl+1;
	float ***t;

	t=(float ***) malloc((size_t)((nrow+NR_END)*sizeof(float**)));
	if (!t) piszkomunikat("brak pamiêci",1);
	t += NR_END;
	t -= nrl;

	t[nrl]=(float **) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float*)));
	if (!t[nrl]) piszkomunikat("brak pamiêci",1);
	t[nrl] += NR_END;
	t[nrl] -= ncl;

	t[nrl][ncl]=(float *) malloc((size_t)((nrow*ncol*ndep+NR_END)*sizeof(float)));
	if (!t[nrl][ncl]) piszkomunikat("brak pamiêci",1);
	t[nrl][ncl] += NR_END;
	t[nrl][ncl] -= ndl;

	for(j=ncl+1;j<=nch;j++) t[nrl][j]=t[nrl][j-1]+ndep;
	for(i=nrl+1;i<=nrh;i++) {
		t[i]=t[i-1]+ncol;
		t[i][ncl]=t[i-1][ncl]+ncol*ndep;
		for(j=ncl+1;j<=nch;j++) t[i][j]=t[i][j-1]+ndep;
	}

	return t;
}

void dtablica3kasuj(float ***t, long nrl, long nrh, long ncl, long nch,
	long ndl, long ndh)
{
	free((FREE_ARG) (t[nrl][ncl]+ndl-NR_END));
	free((FREE_ARG) (t[nrl]+ncl-NR_END));
	free((FREE_ARG) (t+nrl-NR_END));
}

long wart_max(long a, long b)
{
	if(a>=b)
		return a;
	else
		return b;
}

long wart_min(long a, long b)
{
	if(a>=b)
		return b;
	else
		return a;
}

