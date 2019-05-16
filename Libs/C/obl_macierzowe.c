//mnozenie macierzy i wektorow
void iloczynaat(float **a,float **b,long a1,long a2)
//b=a*a', a(a1,a2), b(a1,a1)
{
	float suma;
	long i,j,k;
	for(i=1;i<=a1;i++)
	{
		for(j=1;j<=a1;j++)
		{
			suma=0.0;
			for(k=1;k<=a2;k++)
				suma=suma+a[i][k]*a[j][k];
			b[i][j]=suma;
		}
	}

}

void iloczynata(float **a,float **b,long a1,long a2)
//b=a'*a, a(a1,a2), b(a2,a2)
{
	float suma;
	long i,j,k;

	for(i=1;i<=a2;i++)
	{
		for(j=1;j<=a2;j++)
		{
			suma=0.0;
			for(k=1;k<=a1;k++)
				suma=suma+a[k][i]*a[k][j];
			b[i][j]=suma;
		}
	}
}

void iloczynab(float **a,float **b,float **c,long a1,long a2,long b1,long b2)
//c=a*b, a(a1,a2), b(b1,b2), c(a1,b2), warunek konieczny a2=b1
{
	float suma;
	long i,j,k;

	for(i=1;i<=a1;i++)
	{
		for(j=1;j<=b2;j++)
		{
			suma=0.0;
			for(k=1;k<=b1;k++)
				suma=suma+a[i][k]*b[k][j];
			c[i][j]=suma;
		}
	}
}

void iloczynatb(float **a,float **b,float **c,long a1,long a2,long b1,long b2)
//c=a*b, a(a1,a2), b(b1,b2), c(a2,b2), warunek konieczny a1=b1
{
	float suma;
	long i,j,k;

	for(i=1;i<=a2;i++)
	{
		for(j=1;j<=b2;j++)
		{
			suma=0.0;
			for(k=1;k<=a1;k++)
				suma=suma+a[k][i]*b[k][j];
			c[i][j]=suma;
		}
	}
}

void iloczynabt(float **a,float **b,float **c,long a1,long a2,long b1,long b2)
//c=a*b', a(a1,a2), b(b1,b2), c(a1,b1), warunek konieczny a2=b2
{
	float suma;
	long i,j,k;

	for(i=1;i<=a1;i++)
	{
		for(j=1;j<=b1;j++)
		{
			suma=0.0;
			for(k=1;k<=a2;k++)
				suma=suma+a[i][k]*b[j][k];
			c[i][j]=suma;
		}
	}
}


void iloczynaw(float **a,float *w,float *b,long a1,long a2,long w1)
//b=a*w, a(a1,a2), w(w1), b(a1), warunek konieczny a2=w1
{
	float suma;
	long i,k;

	for(i=1;i<=a1;i++)
	{
		suma=0.0;
		for(k=1;k<=w1;k++)
			suma=suma+a[i][k]*w[k];
		b[i]=suma;
	}
}

void sumaww(float *wa,float *wb,float *wc,long w1,long suma)
//wc=wa+wb gdy suma=1 lub wc=wa-wb gdy suma=-1
//wa,wb,wc(w1)
{
	long i;

	if(suma==1)
		for(i=1;i<=w1;i++)
			wc[i]=wa[i]+wb[i];
	if(suma==-1)
		for(i=1;i<=w1;i++)
			wc[i]=wa[i]-wb[i];
}

void sumaaa(float **a,float **b,float **c,long a1,long a2,long suma)
//c=a+b gdy suma=1 lub c=a-b gdy suma=-1
//ab,c(a1,a2)
{
	long i,j;

	if(suma==1)
		for(i=1;i<=a1;i++)
			for(j=1;j<=a2;j++)
				c[i][j]=a[i][j]+b[i][j];
	if(suma==-1)
		for(i=1;i<=a1;i++)
			for(j=1;j<=a2;j++)
				c[i][j]=a[i][j]-b[i][j];
}

void iloczynwwt(float *wa,float *wb,float **wc,long w1,long w2)
//wc=wa*wb', wa(w1), wb(w2), wc(w1,w2)
{
	long i,j;

	for(i=1;i<=w1;i++)
		for(j=1;j<=w2;j++)
			wc[i][j]=wa[i]*wb[j];
}

float iloczynwtw(float *wa,float *wb,long w1)
//c=wa'*wb, wa(w1), wb(w1), c - liczba
{
	float suma;
	long i;

	suma=0.0;
	for(i=1;i<=w1;i++)
		suma=suma+wa[i]*wb[i];

	return(suma);
}

void iloczynwta(float *wa,float **b,float *wc,long w1,long b1,long b2)
//wc=wa*b, wa(w1), b(b1,b2), c(b2), warunek konieczny w1=b1
{
	float suma;
	long i,k;

	for(i=1;i<=b2;i++)
	{
		suma=0.0;
		for(k=1;k<=b1;k++)
			suma=suma+wa[k]*b[k][i];
		wc[i]=suma;
	}
}


void iloczynatw(float **a,float *wb,float *wc,long a1,long a2,long b1)
//wc=a'*wb, a(a1,a2), b(b1), wc(a2), warunek konieczny a1=b1
{
	float suma;
	long i,k;

	for(k=1;k<=a2;k++)
	{
		suma=0.0;
		for(i=1;i<=a1;i++)
			suma=suma+a[i][k]*wb[i];
		wc[k]=suma;
	}
}


void iloraza(float **a,float b,float **c,long w1,long w2)
//c=a/b, a,c(w1,w2), b - liczba
{
	long i,j;

	for(i=1;i<=w1;i++)
		for(j=1;j<=w2;j++)
			c[i][j]=a[i][j]/b;
}

void iloczyna(float **a,float b,float **c,long w1,long w2)
//c=a*b, a,c(w1,w2), b - liczba
{
	long i,j;

	for(i=1;i<=w1;i++)
		for(j=1;j<=w2;j++)
			c[i][j]=a[i][j]*b;
}

void iloczynw(float *a,float b,float *c,long w1)
//c=a*b, a,c(w1), b - liczba
{
	long i;

	for(i=1;i<=w1;i++)
		c[i]=a[i]*b;
}
