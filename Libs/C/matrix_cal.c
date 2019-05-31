//#include "obl_macierzowe.h"
#include "matrix_cal.h"

void productaat(float **a,float **b,long a1,long a2)
//b=a*a', a(a1,a2), b(a1,a1)
{
	float sum;
	long i,j,k;
	for(i=1;i<=a1;i++)
	{
		for(j=1;j<=a1;j++)
		{
			sum=0.0;
			for(k=1;k<=a2;k++)
				sum=sum+a[i][k]*a[j][k];
			b[i][j]=sum;
		}
	}

}

void productata(float **a,float **b,long a1,long a2)
//b=a'*a, a(a1,a2), b(a2,a2)
{
	float sum;
	long i,j,k;

	for(i=1;i<=a2;i++)
	{
		for(j=1;j<=a2;j++)
		{
			sum=0.0;
			for(k=1;k<=a1;k++)
				sum=sum+a[k][i]*a[k][j];
			b[i][j]=sum;
		}
	}
}

void productab(float **a,float **b,float **c,long a1,long a2,long b1,long b2)
//c=a*b, a(a1,a2), b(b1,b2), c(a1,b2), varunek konieczny a2=b1
{
	float sum;
	long i,j,k;

	for(i=1;i<=a1;i++)
	{
		for(j=1;j<=b2;j++)
		{
			sum=0.0;
			for(k=1;k<=b1;k++)
				sum=sum+a[i][k]*b[k][j];
			c[i][j]=sum;
		}
	}
}

void productatb(float **a,float **b,float **c,long a1,long a2,long b1,long b2)
//c=a*b, a(a1,a2), b(b1,b2), c(a2,b2), varunek konieczny a1=b1
{
	float sum;
	long i,j,k;

	for(i=1;i<=a2;i++)
	{
		for(j=1;j<=b2;j++)
		{
			sum=0.0;
			for(k=1;k<=a1;k++)
				sum=sum+a[k][i]*b[k][j];
			c[i][j]=sum;
		}
	}
}

void productabt(float **a,float **b,float **c,long a1,long a2,long b1,long b2)
//c=a*b', a(a1,a2), b(b1,b2), c(a1,b1), varunek konieczny a2=b2
{
	float sum;
	long i,j,k;

	for(i=1;i<=a1;i++)
	{
		for(j=1;j<=b1;j++)
		{
			sum=0.0;
			for(k=1;k<=a2;k++)
				sum=sum+a[i][k]*b[j][k];
			c[i][j]=sum;
		}
	}
}


void productav(float **a,float *v,float *b,long a1,long a2,long v1)
//b=a*v, a(a1,a2), v(v1), b(a1), varunek konieczny a2=v1
{
	float sum;
	long i,k;

	for(i=1;i<=a1;i++)
	{
		sum=0.0;
		for(k=1;k<=v1;k++)
			sum=sum+a[i][k]*v[k];
		b[i]=sum;
	}
}

void sumvv(float *va,float *vb,float *vc,long v1,long sum)
//vc=va+vb gdy sum=1 lub vc=va-vb gdy sum=-1
//va,vb,vc(v1)
{
	long i;

	if(sum==1)
		for(i=1;i<=v1;i++)
			vc[i]=va[i]+vb[i];
	if(sum==-1)
		for(i=1;i<=v1;i++)
			vc[i]=va[i]-vb[i];
}

void sumaa(float **a,float **b,float **c,long a1,long a2,long sum)
//c=a+b gdy sum=1 lub c=a-b gdy sum=-1
//ab,c(a1,a2)
{
	long i,j;

	if(sum==1)
		for(i=1;i<=a1;i++)
			for(j=1;j<=a2;j++)
				c[i][j]=a[i][j]+b[i][j];
	if(sum==-1)
		for(i=1;i<=a1;i++)
			for(j=1;j<=a2;j++)
				c[i][j]=a[i][j]-b[i][j];
}

void productvvt(float *va,float *vb,float **vc,long v1,long v2)
//vc=va*vb', va(v1), vb(v2), vc(v1,v2)
{
	long i,j;

	for(i=1;i<=v1;i++)
		for(j=1;j<=v2;j++)
			vc[i][j]=va[i]*vb[j];
}

float productvtv(float *va,float *vb,long v1)
//c=va'*vb, va(v1), vb(v1), c - liczba
{
	float sum;
	long i;

	sum=0.0;
	for(i=1;i<=v1;i++)
		sum=sum+va[i]*vb[i];

	return(sum);
}

void productvta(float *va,float **b,float *vc,long v1,long b1,long b2)
//vc=va*b, va(v1), b(b1,b2), c(b2), varunek konieczny v1=b1
{
	float sum;
	long i,k;

	for(i=1;i<=b2;i++)
	{
		sum=0.0;
		for(k=1;k<=b1;k++)
			sum=sum+va[k]*b[k][i];
		vc[i]=sum;
	}
}


void productatv(float **a,float *vb,float *vc,long a1,long a2,long b1)
//vc=a'*vb, a(a1,a2), b(b1), vc(a2), varunek konieczny a1=b1
{
	float sum;
	long i,k;

	for(k=1;k<=a2;k++)
	{
		sum=0.0;
		for(i=1;i<=a1;i++)
			sum=sum+a[i][k]*vb[i];
		vc[k]=sum;
	}
}


void dividea(float **a,float b,float **c,long v1,long v2)
//c=a/b, a,c(v1,v2), b - liczba
{
	long i,j;

	for(i=1;i<=v1;i++)
		for(j=1;j<=v2;j++)
			c[i][j]=a[i][j]/b;
}

void producta(float **a,float b,float **c,long v1,long v2)
//c=a*b, a,c(v1,v2), b - liczba
{
	long i,j;

	for(i=1;i<=v1;i++)
		for(j=1;j<=v2;j++)
			c[i][j]=a[i][j]*b;
}

void productv(float *a,float b,float *c,long v1)
//c=a*b, a,c(v1), b - liczba
{
	long i;

	for(i=1;i<=v1;i++)
		c[i]=a[i]*b;
}
