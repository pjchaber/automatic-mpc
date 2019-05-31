#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//#include "alokacja_nr.h"
//#include "obl_macierzowe.h"
//#include "pk.h"
#include "allocation_nr.h"
#include "matrix_cal.h"
#include "qp.h"

// Legacy stuff -- translation from Polish to English
#define piszkomunikat  writemessage
#define lwektor        lvector
#define ltablica       larray
#define dwektor        dvector
#define dtablica       darray
#define dtablica3      darray3
#define dwektorkasuj   dvectordelete
#define dtablicakasuj  darraydelete
#define dtablica3kasuj darray3delete
#define lwektorkasuj   lvectordelete
#define ltablicakasuj  larraydelete
#define wart_max       value_max
#define wart_min       value_min

#define iloczynaat     productaat
#define iloczynata     productata
#define iloczynab      productab
#define iloczynatb     productatb
#define iloczynatbt    productatbt
#define iloczynabt     productabt
#define iloczynaw      productav
#define sumaww         sumvv
#define sumaaa         sumaa
#define iloczynwwt     productvvt
#define iloczynwtw     productvtv
#define iloczynwta     productvta
#define iloczynatw     productatv
#define iloraza        dividea
#define iloczyna       producta
#define iloczynw       productv

static long pk_ilzm,pk_ilogr,pk_ilor,*pk_nrnzal;

static float *pkr_xr,*pkr_lambdar,**pkr_Gr,*pkr_tr,**pkr_S,**pkr_Z,**pkr_Ar,*pkr_br;
static float **qr_a,**qr_q,**qr_r;
static float **pk_A,*pk_b,*pk_x,*pk_lambda,**pk_G,*pk_t,pk_epsogr,pk_zero;
static long pk_ilograkt,*pk_akt,*pk_nrakt;
static float **lu_kopiama,**lu_ml,**lu_iloczyn,*lu_wy,*lu_wx,**lu_pusta;
static long *lu_ind;
static float *pk_wp1,*pk_wp2,*pk_wp3;
static float **pk_mp1,**pk_mp2,**pk_mp3;

void definevarnum(long ilzm_){
	pk_ilzm = ilzm_;
}
void defineconnum(long ilogr_){
	pk_ilogr = ilogr_;
}

float ** obtainA(void){     return pk_A;}
float *  obtainb(void){     return pk_b;}
float *  obtainx(void){     return pk_x;}
float *  obtainlambda(void){return pk_lambda;}
float ** obtainG(void){     return pk_G;}
float *  obtaint(void){     return pk_t;}
float    obtainepsogr(void){return pk_epsogr;}
float    obtainzero(void){  return pk_zero;}
long     obtainvarnum(void){  return pk_ilzm;}
long     obtainconnum(void){ return pk_ilogr;}

float rozklu(float **mac,long wym,float **macl,long *ind,float *znak) {
	float wartnajw,liczba,wynik;
	long i,j,w,nrnajw;
	*znak=1.0f;
	for(i=1;i<=wym;i++) {
		for(j=1;j<=wym;j++) {
			macl[i][j]=0.0f;
			if(i==j)
				macl[i][j]=1.0f;
		}
		ind[i]=i;
	}
	for(w=1;w<=wym-1;w++) {
		wartnajw=0.0f; nrnajw=w;
		for(i=w;i<=wym;i++) {
			if( fabs(mac[i][w])>wartnajw ) {
				wartnajw=fabs(mac[i][w]);
				nrnajw=i;
			}
		}
		if(nrnajw==w) {
		} else {
			*znak=*znak*(-1.0f);
			for(i=1;i<=wym;i++) {
				liczba=mac[w][i];
				mac[w][i]=mac[nrnajw][i];
				mac[nrnajw][i]=liczba;
			}
			j=ind[w]; ind[w]=ind[nrnajw]; ind[nrnajw]=j;
			for(j=1;j<=w-1;j++) {
				liczba=macl[w][j];
				macl[w][j]=macl[nrnajw][j];
				macl[nrnajw][j]=liczba;
			}
		}
		for(i=w+1;i<=wym;i++) {
			if(fabs(mac[w][w])>pk_zero) {
				macl[i][w]=mac[i][w]/mac[w][w];
			} else {
				macl[i][w]=0.0f;
			}
		}

		for(i=w+1;i<=wym;i++) {
			for(j=1;j<=wym;j++)
				mac[i][j]=mac[i][j]-mac[w][j]*macl[i][w];
		}
	}
	wynik=*znak;
	for(i=1;i<=wym;i++)
		wynik=wynik*mac[i][i];
	return(wynik);
}
long liczwyznmacodwr(float **ma,long wym,float **ma1,float *wyzn,int tryb) {

	float znak,wyznacznik;
	float b;
	long i,j,k;		

	for(i=1;i<=wym;i++) {
		for(j=1;j<=wym;j++) {
			lu_kopiama[i][j]=ma[i][j];
		}
	}

	wyznacznik=rozklu(ma,wym,lu_ml,lu_ind,&znak);
	
	*wyzn=wyznacznik;
	if(fabs(wyznacznik)>pk_zero && tryb==1) {
		for(k=1;k<=wym;k++) {
			if(k==1)
				lu_wy[1]=1.0f/lu_ml[1][1];
			else
				lu_wy[1]=0.0f;
			for(i=2;i<=wym;i++) {
				if(i==k)
					b=1.0f;
				else
					b=0.0f;
				lu_wy[i]=0.0f;
				for(j=1;j<=i-1;j++)
					lu_wy[i]=lu_wy[i]+lu_ml[i][j]*lu_wy[j];
				lu_wy[i]=(b-lu_wy[i])/lu_ml[i][i];
			}
			lu_wx[wym]=lu_wy[wym]/ma[wym][wym];
			for(i=wym-1;i>=1;i--) {
				lu_wx[i]=0.0f;
				for(j=i+1;j<=wym;j++)
					lu_wx[i]=lu_wx[i]+ma[i][j]*lu_wx[j];
				lu_wx[i]=(lu_wy[i]-lu_wx[i])/ma[i][i];
			}


			for(i=1;i<=wym;i++) {
				ma1[i][lu_ind[k]]=lu_wx[i];
			}

		}
		for(i=1;i<=wym;i++){
			for(j=1;j<=wym;j++){
				ma[i][j]=lu_kopiama[i][j];
			}
		}
		for(i=1;i<=wym;i++) {
			for(j=1;j<=wym;j++) {
				lu_iloczyn[i][j]=0.0f;
				for(k=1;k<=wym;k++){
					lu_iloczyn[i][j]=lu_iloczyn[i][j]+ma[i][k]*ma1[k][j];
				}
			}
		}
	}
	for(i=1;i<=wym;i++){
		for(j=1;j<=wym;j++){
			ma[i][j]=lu_kopiama[i][j];
		}
	}
	if(fabs(wyznacznik)<pk_zero && tryb==1){
		return(0);
	} else{
		return(1);
	}
}
float liczwyzn(float **ma,long wym) {
	float wyzn;
	liczwyznmacodwr(ma,wym,lu_pusta,&wyzn,0);
	return(wyzn);
}

float znak(float x) {
	if(x>=0.0f)	return( 1.0f);
	else		return(-1.0f);
}
void rozkqr(long ilw,long ilk) {
	long i,j,k,l;
	float na,nu,K;

	if(ilw>ilk) {
		for(i=1;i<=ilw;i++)
			for(j=ilk+1;j<=ilw;j++)
				qr_a[i][j]=0.0f;
	}

	for(k=1;k<=ilw-1;k++) {
		na=0.0f;
		for(i=k;i<=pk_ilzm;i++) {
			if(k==1) {
				pk_wp1[i-k+1]=qr_a[i][k];
				na=na+pk_wp1[i-k+1]*pk_wp1[i-k+1];
			} else {
				pk_wp1[i-k+1]=qr_r[i][k];
				na=na+pk_wp1[i-k+1]*pk_wp1[i-k+1];
			}
		}
		na=sqrt(na);
		nu=0.0f;
		pk_wp1[1]=pk_wp1[1]+znak(pk_wp1[1])*na;
		for(i=k;i<=pk_ilzm;i++) {
			nu=nu+pk_wp1[i-k+1]*pk_wp1[i-k+1];
		}
		if(nu>1.0e-10f)
			K=0.5f*nu;
		else
			nu=0.0f;

		nu=sqrt(nu);
		iloczynwwt(pk_wp1,pk_wp1,pk_mp1,pk_ilzm-k+1,pk_ilzm-k+1);

		for(i=1;i<=pk_ilzm-k+1;i++) {
			for(j=1;j<=pk_ilzm-k+1;j++) {
				if(nu!=0.0f)
					pk_mp1[i][j]=-pk_mp1[i][j]/K;
				else
					pk_mp1[i][j]=0.0f;
				if(i==j)
					pk_mp1[i][j]=pk_mp1[i][j]+1.0f;
			}
		}

		if(k==1)
			iloczynab(pk_mp1,qr_a,qr_r,pk_ilzm,pk_ilzm,pk_ilzm,pk_ilzm);
		else {
			for(i=1;i<=pk_ilzm;i++) {
				for(j=1;j<=pk_ilzm;j++) {
					if(i>=k && j>=k) {
						pk_mp3[i][j]=0.0f;
						for(l=1;l<=pk_ilzm-k+1;l++) {
							pk_mp3[i][j]=pk_mp3[i][j]+pk_mp1[i-k+1][l]*qr_r[l+k-1][j];
						}
					} else {
						pk_mp3[i][j]=qr_r[i][j];
					}

				}
			}
			for(i=1;i<=pk_ilzm;i++)
				for(j=1;j<=pk_ilzm;j++)
					qr_r[i][j]=pk_mp3[i][j];
		}
		if(k==1) {
			for(i=1;i<=pk_ilzm;i++)
				for(j=1;j<=pk_ilzm;j++)
					qr_q[i][j]=pk_mp1[i][j];
		} else {
			for(i=1;i<=pk_ilzm;i++) {
				for(j=1;j<=pk_ilzm;j++) {
					if(i<=k-1 && j<=k-1) {
						pk_mp3[i][j]=qr_q[i][j];
					} else {
						pk_mp3[i][j]=0.0f;
						if(j<k)
							pk_mp3[i][j]=qr_q[i][j];
						else {
							for(l=1;l<=pk_ilzm-k+1;l++) {
								pk_mp3[i][j]=pk_mp3[i][j]+qr_q[i][l+k-1]*pk_mp1[l][j-k+1];
							}
						}
					}
				}
			}
			for(i=1;i<=pk_ilzm;i++){
				for(j=1;j<=pk_ilzm;j++){
					qr_q[i][j]=pk_mp3[i][j];
				}
			}
		}
	}
	if(ilw==1) {
		for(i=1;i<=ilk;i++) {
			qr_q[1][i]=1.0f; qr_r[1][i]=qr_a[1][i];
		}
	}
}

int pkr(void) {
	long i,j,k,l,kasowanie,ilogrskas;
	float wyzn;
	kasowanie=0;
	if(pk_ilor!=0) {
		iloczynaat(pkr_Ar,pk_mp1,pk_ilor,pk_ilzm);
		ilogrskas=0;
		wyzn=liczwyzn(pk_mp1,pk_ilor);
		if(fabs(wyzn)<pk_zero) {
			kasowanie=1;
			for(i=1;i<=pk_ilzm;i++) {
				pk_mp1[1][i]=pkr_Ar[1][i];
				pk_wp1[1]=pkr_br[1];
				pk_nrnzal[1]=1;
			}
			k=1;
			for(l=2;l<=pk_ilor;l++) {
				for(i=1;i<=pk_ilzm;i++)
					pk_mp1[k+1][i]=pkr_Ar[l][i];
				iloczynaat(pk_mp1,pk_mp2,k+1,pk_ilzm);
				wyzn=liczwyzn(pk_mp2,k+1);
				if(fabs(wyzn)<pk_zero) {
					pk_nrnzal[l]=-l;
					ilogrskas++;
				} else {
					pk_wp1[k+1]=pkr_br[l];
					pk_nrnzal[l]=l;
					k++;
				}
			}
			pk_ilor=k;
			for(i=1;i<=pk_ilor;i++) {
				pkr_br[i]=pk_wp1[i];
			}
		}
	}

	if(pk_ilor==0) {
		wyzn=liczwyzn(pkr_Gr,pk_ilzm);
		if(fabs(wyzn)<pk_zero) {
			for(i=1;i<=pk_ilzm;i++) {
				for(j=1;j<=pk_ilzm;j++) {
					if(i!=j)
						if(fabs(pkr_Gr[i][j])>pk_zero) {
							return(-1);
						}
					}
				}

				for(i=1;i<=pk_ilzm;i++) {
					if(fabs(pkr_Gr[i][i])>pk_zero)
						pkr_xr[i]=-pkr_tr[i]/pkr_Gr[i][i];
					else
						pkr_xr[i]=0.0f;
				}
			} else {
			liczwyznmacodwr(pkr_Gr,pk_ilzm,pk_mp1,&wyzn,1);
			iloczynaw(pk_mp1,pkr_tr,pkr_xr,pk_ilzm,pk_ilzm,pk_ilzm);
			for(i=1;i<=pk_ilzm;i++)
				pkr_xr[i]=-pkr_xr[i];
		}

		return(1);
	}

	if(pk_ilor!=0) {
		if(pk_ilor==pk_ilzm) {
			if(fabs(liczwyzn(pkr_Ar,pk_ilzm))<pk_zero) {
				return(-1);
			}
			liczwyznmacodwr(pkr_Ar,pk_ilzm,pk_mp1,&wyzn,1);
			
			iloczynaw(pk_mp1,pkr_br,pkr_xr,pk_ilzm,pk_ilzm,pk_ilzm);
			
		}
		for(i=1;i<=pk_ilor;i++)
			for(j=1;j<=pk_ilzm;j++)
				qr_a[j][i]=pkr_Ar[i][j];

			rozkqr(pk_ilzm,pk_ilor);

			if(fabs(liczwyzn(qr_r,pk_ilor))<pk_zero) {
				return(-1);
			}

			liczwyznmacodwr(qr_r,pk_ilor,pk_mp1,&wyzn,1);

			iloczynabt(qr_q,pk_mp1,pkr_S,pk_ilzm,pk_ilor,pk_ilor,pk_ilor);

		if(pk_ilor!=pk_ilzm) {
			for(i=1;i<=pk_ilzm;i++) {
				for(j=1;j<=pk_ilzm-pk_ilor;j++) {
					pkr_Z[i][j]=qr_q[i][pk_ilor+j];
				}
			}
			iloczynaw(pkr_S,pkr_br,pk_wp1,pk_ilzm,pk_ilor,pk_ilor);
			iloczynatb(pkr_Z,pkr_Gr,pk_mp1,pk_ilzm,pk_ilzm-pk_ilor,pk_ilzm,pk_ilzm);
			iloczynab(pk_mp1,pkr_Z,pk_mp2,pk_ilzm-pk_ilor,pk_ilzm,pk_ilzm,pk_ilzm-pk_ilor);
			if(fabs(liczwyzn(pk_mp2,pk_ilzm-pk_ilor))<pk_zero) {
				return(-1);
			}

			liczwyznmacodwr(pk_mp2,pk_ilzm-pk_ilor,pk_mp1,&wyzn,1);
			iloczynab(pkr_Z,pk_mp1,pk_mp2,pk_ilzm,pk_ilzm-pk_ilor,pk_ilzm-pk_ilor,pk_ilzm-pk_ilor);
			iloczynabt(pk_mp2,pkr_Z,pk_mp1,pk_ilzm,pk_ilzm-pk_ilor,pk_ilzm,pk_ilzm-pk_ilor);
			iloczynaw(pkr_Gr,pk_wp1,pk_wp2,pk_ilzm,pk_ilzm,pk_ilzm);
			sumaww(pkr_tr,pk_wp2,pk_wp2,pk_ilzm,1);
			iloczynaw(pk_mp1,pk_wp2,pk_wp3,pk_ilzm,pk_ilzm,pk_ilzm);
			sumaww(pk_wp1,pk_wp3,pkr_xr,pk_ilzm,-1);
		}
		iloczynaw(pkr_Gr,pkr_xr,pk_wp1,pk_ilzm,pk_ilzm,pk_ilzm);
		sumaww(pkr_tr,pk_wp1,pk_wp2,pk_ilzm,1);
		iloczynatw(pkr_S,pk_wp2,pkr_lambdar,pk_ilzm,pk_ilor,pk_ilzm);

		if(kasowanie==1) {
			for(i=1;i<=pk_ilor;i++)
				pk_wp1[i]=pkr_lambdar[i];
			j=1;
			for(i=1;i<=pk_ilor+ilogrskas;i++) {
				if(pk_nrnzal[i]>0) {
					pkr_lambdar[i]=pk_wp1[j];
					j++;
				} else {
					pkr_lambdar[i]=0.0f;
				}
			}
			pk_ilor=pk_ilor+ilogrskas;
		}
		return(1);
	}
	return(-1);
}
void initializeqp(void) {
	long il;
	
	pk_epsogr=1.0e-3f; pk_zero=1.0e-10f;	
	if(pk_ilzm>pk_ilogr)
		il=pk_ilzm;
	else
		il=pk_ilogr;
	qr_a=dtablica(1,pk_ilzm,1,pk_ilzm);
	qr_q=dtablica(1,pk_ilzm,1,pk_ilzm);
	qr_r=dtablica(1,pk_ilzm,1,pk_ilzm);

	pkr_xr=dwektor(1,pk_ilzm);
	pkr_lambdar=dwektor(1,pk_ilogr);
	pkr_Gr=dtablica(1,pk_ilzm,1,pk_ilzm);
	pkr_tr=dwektor(1,pk_ilzm);
	pkr_Ar=dtablica(1,pk_ilogr,1,pk_ilzm);
	pkr_br=dwektor(1,pk_ilogr);
	pkr_S=dtablica(1,pk_ilzm,1,pk_ilzm);
	pkr_Z=dtablica(1,pk_ilzm,1,pk_ilzm);
	pk_nrnzal=lwektor(1,pk_ilogr);
	pk_A=dtablica(1,pk_ilogr,1,pk_ilzm);
	pk_b=dwektor(1,pk_ilogr);
	pk_x=dwektor(1,pk_ilzm);
	pk_lambda=dwektor(1,pk_ilogr);
	pk_G=dtablica(1,pk_ilzm,1,pk_ilzm);
	pk_t=dwektor(1,pk_ilzm);

	pk_akt=lwektor(1,pk_ilogr);
	pk_nrakt=lwektor(1,pk_ilogr);

	pk_wp1=dwektor(1,il);
	pk_wp2=dwektor(1,il);
	pk_wp3=dwektor(1,il);
	pk_mp1=dtablica(1,il,1,il);
	pk_mp2=dtablica(1,il,1,il);
	pk_mp3=dtablica(1,il,1,il);
	lu_kopiama=dtablica(1,il,1,il);
	lu_ml=dtablica(1,il,1,il);
	lu_iloczyn=dtablica(1,il,1,il);
	lu_ind=lwektor(1,il);
	lu_wx=dwektor(1,il);
	lu_wy=dwektor(1,il);
	lu_pusta=dtablica(1,il,1,il);
}
void koniecpk(void) {
	long il;
	if(pk_ilzm>pk_ilogr)
		il=pk_ilzm;
	else
		il=pk_ilogr;
	dtablicakasuj(qr_a,1,pk_ilzm,1,pk_ilzm);
	dtablicakasuj(qr_q,1,pk_ilzm,1,pk_ilzm);
	dtablicakasuj(qr_r,1,pk_ilzm,1,pk_ilzm);

	dwektorkasuj(pkr_xr,1,pk_ilzm);
	dwektorkasuj(pkr_lambdar,1,pk_ilogr);
	dtablicakasuj(pkr_Gr,1,pk_ilzm,1,pk_ilzm);
	dwektorkasuj(pkr_tr,1,pk_ilzm);
	dtablicakasuj(pkr_Ar,1,pk_ilogr,1,pk_ilzm);
	dwektorkasuj(pkr_br,1,pk_ilogr);
	dtablicakasuj(pkr_S,1,pk_ilzm,1,pk_ilzm);
	dtablicakasuj(pkr_Z,1,pk_ilzm,1,pk_ilzm);
	lwektorkasuj(pk_nrnzal,1,pk_ilogr);

	dtablicakasuj(pk_A,1,pk_ilogr,1,pk_ilzm);
	dwektorkasuj(pk_b,1,pk_ilogr);
	dwektorkasuj(pk_x,1,pk_ilzm);
	dwektorkasuj(pk_lambda,1,pk_ilogr);
	dtablicakasuj(pk_G,1,pk_ilzm,1,pk_ilzm);
	dwektorkasuj(pk_t,1,pk_ilzm);

	lwektorkasuj(pk_akt,1,pk_ilogr);
	lwektorkasuj(pk_nrakt,1,pk_ilogr);

	dwektorkasuj(pk_wp1,1,il);
	dwektorkasuj(pk_wp2,1,il);
	dwektorkasuj(pk_wp3,1,il);
	dtablicakasuj(pk_mp1,1,il,1,il);
	dtablicakasuj(pk_mp2,1,il,1,il);
	dtablicakasuj(pk_mp3,1,il,1,il);
	
	dtablicakasuj(lu_kopiama,1,il,1,il);
	dtablicakasuj(lu_ml,1,il,1,il);
	dtablicakasuj(lu_iloczyn,1,il,1,il);
	lwektorkasuj(lu_ind,1,il);
	dwektorkasuj(lu_wx,1,il);
	dwektorkasuj(lu_wy,1,il);	
	dtablicakasuj(lu_pusta,1,il,1,il);
}
int testogr(void) {
	float suma;
	long i,j,k;

	pk_ilograkt=0;
	for(i=1;i<=pk_ilogr;i++) {
		suma=0.0f;
		for(j=1;j<=pk_ilzm;j++)
			suma=suma+pk_A[i][j]*pk_x[j];

		suma=suma-pk_b[i];
		if(suma<-pk_epsogr) {
			return(0);
		} else {
			if(fabs(suma)<=pk_epsogr) {
				pk_ilograkt++;
				pk_akt[i]=1;
			} else {
				pk_akt[i]=0;
			}
		}
	}
	k=1; 
	for(i=1;i<=pk_ilogr;i++) {
		if(pk_akt[i]==1) {
			pk_nrakt[k]=i;
			k++;
		}
	}
	return(1);
}
int pomocniczezadpkr() {
	long i,j;

	for(i=1;i<=pk_ilzm;i++)
		for(j=1;j<=pk_ilzm;j++)
			pkr_Gr[i][j]=pk_G[i][j];
	for(i=1;i<=pk_ilzm;i++) {
		pkr_tr[i]=0.0f;
		for(j=1;j<=pk_ilzm;j++)
			pkr_tr[i]=pkr_tr[i]+pkr_Gr[i][j]*pk_x[j];
		pkr_tr[i]=pkr_tr[i]+pk_t[i];
	}
	pk_ilor=pk_ilograkt;
	for(i=1;i<=pk_ilor;i++) {
		pkr_br[i]=0.0f;
		for(j=1;j<=pk_ilzm;j++) {
			pkr_Ar[i][j]=pk_A[pk_nrakt[i]][j];
		}
	}
	return(pkr());
}
int qp() {
	long i,j,nrlmin,jestalfa,nralfamin;
	float norma,lmin,alfa,mian,licznik;

	if(testogr()==0) {
		return(-2);
	}

	while(1) {
		if(pomocniczezadpkr()==-1) {
			return(-1);
		}
		norma=0.0f;
		for(i=1;i<=pk_ilzm;i++) {
			norma=norma+pkr_xr[i]*pkr_xr[i];
		}

		if(norma<=pk_zero) {
			lmin=0.0f;
			for(i=1;i<=pk_ilor;i++) {
				if(pkr_lambdar[i]<lmin) {
					lmin=pkr_lambdar[i];
					nrlmin=pk_nrakt[i];
				}
			}

			if(lmin>=0.0f) {
				for(i=1;i<=pk_ilogr;i++)
					pk_lambda[i]=0.0f;
				for(i=1;i<=pk_ilor;i++)
					pk_lambda[pk_nrakt[i]]=pkr_lambdar[i];
				return(1);
			}
			pk_akt[nrlmin]=0;
			pk_ilograkt=pk_ilograkt-1;
			j=1; 
			for(i=1;i<=pk_ilogr;i++) {
				if(pk_akt[i]==1) {
					pk_nrakt[j]=i;
					j++;
				}
			}

			if(pomocniczezadpkr()==-1) {
				return(-1);
			}
		}
		jestalfa=0;
		for(i=1;i<=pk_ilogr;i++) {
			if(pk_akt[i]==0) {
				mian=0.0f;
				for(j=1;j<=pk_ilzm;j++)
					mian=mian+pk_A[i][j]*pkr_xr[j];
				if(mian<0) {
					licznik=pk_b[i];
					for(j=1;j<=pk_ilzm;j++)
						licznik=licznik-pk_A[i][j]*pk_x[j];;

					if(jestalfa==0) {
						alfa=licznik/mian;
						jestalfa=1;
						nralfamin=i;
					} else {
						if((licznik/mian)<alfa) {
							alfa=licznik/mian;
							nralfamin=i;
						}
					}
				}
			}
		}
		if(jestalfa==1)
			// alfa=fmin(1.0f,alfa);
			alfa=1.0f<alfa?1.0f:alfa;
		else
			alfa=1.0f;
		for(i=1;i<=pk_ilzm;i++) {
			pk_x[i]=pk_x[i]+alfa*pkr_xr[i];
		}
		if(alfa<1.0f) {
			pk_akt[nralfamin]=1;
			pk_ilograkt++;
			j=1; 
			for(i=1;i<=pk_ilogr;i++) {
				if(pk_akt[i]==1) {
					pk_nrakt[j]=i;
					j++;
				}
			}
		}
	}
}
