void iloczynaat(float **a,float **b,long a1,long a2);//b=a*a', a(a1,a2), b(a1,a1)
void iloczynata (float **a,float **b,long a1,long a2);//b=a'*a, a(a1,a2), b(a2,a2)
void iloczynab  (float **a,float **b,float **c,long a1,long a2,long b1,long b2); //c=a*b, a(a1,a2), b(b1,b2), c(a1,b2), warunek konieczny a2=b1
void iloczynatb (float **a,float **b,float **c,long a1,long a2,long b1,long b2); //c=a'*b, a(a1,a2), b(b1,b2), c(a2,b2), warunek konieczny a1=b1
void iloczynatbt(float **a,float **b,float **c,long a1,long a2,long b1,long b2); //c=a'*bt, a(a1,a2), b(b1,b2), c(a2,b1), warunek konieczny a1=b2
void iloczynabt (float **a,float **b,float **c,long a1,long a2,long b1,long b2); //c=a*b', a(a1,a2), b(b1,b2), c(a1,b1), warunek konieczny a2=b2
void iloczynaw  (float **a,float *wb,float * c,long a1,long a2,long w1);         //c=a*wb, a(a1,a2), wb(w1), c(a1), warunek konieczny a2=w1
void sumaww     (float *wa,float *wb,float *wc,long w1,long suma);               //wc=wa+wb gdy suma=1 lub wc=wa-wb gdy suma=-1
void sumaaa     (float **a,float **b,float **c,long a1,long a2,long suma);       //c=a+b gdy suma=1 lub c=a-b gdy suma=-1
void iloczynwwt (float *wa,float *wb,float **c,long w1,long w2);                 //c=wa*wb', wa(w1), wb(w2), c(w1,w2)
float iloczynwtw(float *wa,float *wb,long   w1);                                 //c=wa'*wb, wa(w1), wb(w1), c - liczba
void iloczynwta (float *wa,float **b,float *wc,long w1,long b1,long b2);         //wc=wa*b, wa(w1), b(b1,b2), c(b2), warunek konieczny w1=b1
void iloczynatw (float **a,float *wb,float *wc,long a1,long a2,long b1);         //wc=a'*wb, a(a1,a2), b(b1), wc(a2), warunek konieczny a1=b1
void iloraza    (float **a,float   b,float **c,long w1,long w2);                 //c=a/b, a,c(w1,w2), b - liczba
void iloczyna   (float **a,float   b,float **c,long w1,long w2);                 //c=a*b, a,c(w1,w2), b - liczba
void iloczynw   (float *wa,float   b,float *wc,long w1);                         //wc=wa*b, wa=(w1), b - liczba
