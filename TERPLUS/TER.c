
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ReverseFirstFit.c"

stats multiFF(int algo,int nb,int periode,double taux,int delayMin,int delayMax){
	double moy=0,val,reussite=0,min=100,max=0;
	stats stat;
	int tmpP;
	srand(time(NULL));
	for(int i=0;i<nb;i++){
		tmpP=10+rand()%(periode*2);
		if(algo==0)val=FirstFit(tmpP,tmpP*taux,delayMin,delayMax);
		else val=ReverseFirstFit(tmpP,tmpP*taux,delayMin,delayMax);
		moy+=val;
		if(val<min)min=val;
		if(val>max)max=val;
		if(val==100)reussite++;
	}
	reussite=(reussite/nb)*100;
	moy=((double)moy/(double)nb);
	stat.tauxCompletion=moy;
	stat.tauxReussite=reussite;
	stat.tauxMin=min;
	stat.tauxMax=max;
	return stat;
}

int main(int argc,char** argv){
//	ReverseFirstFit(100,100,0,100);
	float temps;
    clock_t t1, t2;
 
  /*  t1 = clock();
    printf("\nAlgo First Fit:\n");
    stats stat=multiFF(0,1000000,100,1.0,0,100);
	printf("A 100/100 :\nTaux de completion : %f\nTaux de reussite : %f\nTaux minimum : %f\nTaux maximum : %f\n",stat.tauxCompletion,stat.tauxReussite,stat.tauxMin,stat.tauxMax);
	stat=multiFF(0,1000000,100,0.75,0,100);
	printf("A 75/100 :\nTaux de completion : %f\nTaux de reussite : %f\nTaux minimum : %f\nTaux maximum : %f\n",stat.tauxCompletion,stat.tauxReussite,stat.tauxMin,stat.tauxMax);
	stat=multiFF(0,1000000,100,0.50,0,100);
	printf("A 50/100 :\nTaux de completion : %f\nTaux de reussite : %f\nTaux minimum : %f\nTaux maximum : %f\n",stat.tauxCompletion,stat.tauxReussite,stat.tauxMin,stat.tauxMax);
	t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);

    t1 = clock();
    printf("\nAlgo Reverse First Fit:\n");
    stat=multiFF(1,1000000,100,1.0,0,100);
	printf("A 100/100 :\nTaux de completion : %f\nTaux de reussite : %f\nTaux minimum : %f\nTaux maximum : %f\n",stat.tauxCompletion,stat.tauxReussite,stat.tauxMin,stat.tauxMax);
	stat=multiFF(1,1000000,100,0.75,0,100);
	printf("A 75/100 :\nTaux de completion : %f\nTaux de reussite : %f\nTaux minimum : %f\nTaux maximum : %f\n",stat.tauxCompletion,stat.tauxReussite,stat.tauxMin,stat.tauxMax);
	stat=multiFF(1,1000000,100,0.50,0,100);
	printf("A 50/100 :\nTaux de completion : %f\nTaux de reussite : %f\nTaux minimum : %f\nTaux maximum : %f\n",stat.tauxCompletion,stat.tauxReussite,stat.tauxMin,stat.tauxMax);
  	t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);*/


}