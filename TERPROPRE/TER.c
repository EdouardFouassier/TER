#include "TER.h"
#include <omp.h>

double multi(int algo,int nb,int periode,int nbTask){
	double cpt=0;
	TaskTab tasktab;
	double val=0;
	int logi;
	char* nom;
	int i=0;
	//#pragma omp for private (val,nom,i,tasktab)
	for(i=0;i<nb;i++){
		if(i==0)logi=1;
		else logi=log(i)+1;
		//printf("1 %d %d %d\n",nbTask,i,omp_get_thread_num());
		nom=malloc(sizeof(int)*logi+7);
		sprintf(nom,"data/in%d",i);
		tasktab=lireData(nom,nbTask);
		free(nom);
		//afficheTab(tasktab);
		if(algo==0)val=completionFF(FirstFit(tasktab,periode,nbTask));
		else {	if (algo == 1) val=completionFF(algoLourd(tasktab,periode,nbTask));
				else val=completionFF(algoSuperLourd(tasktab,periode));
		}
		if(val==100)cpt++;
		//printf("%f\n",val);
		//free(tasktab.tab);
	//	printf("2 %d %d \n",nbTask,i);
	}

	return (cpt/nb)*100;
}

int main(int argc,char** argv){
	//affichePeriode(periodes[0]);
//	printf("\n");
	float temps1=0,temps2=0,temps3=0,moyenne1=0,moyenne2=0,moyenne3=0,acc1,acc2,amelio1,amelio2,eff1,eff2;
    clock_t t1, t2;

	int periode=atoi(argv[1]),cycle=atoi(argv[3]),nb=atoi(argv[4]),nbTask=atoi(argv[2]);
	
	int maxTask=periode/cycle;
	gen(periode,cycle,nb);
	double taux[3][maxTask];
	int i=1;
	
	#pragma omp parallel for private(i)
	for(i=1;i<=maxTask;i++){
		t1 = clock();
		taux[0][i-1]=multi(0,nb,periode,i);
		moyenne1+=taux[0][i-1];
		t2 = clock();
		temps1 += (float)(t2-t1)/CLOCKS_PER_SEC;
		taux[1][i-1]=multi(1,nb,periode,i);
		moyenne2+=taux[1][i-1];
		t1 = clock();
		temps2 += (float)(t1-t2)/CLOCKS_PER_SEC;
		taux[2][i-1]=multi(2,nb,periode,i);
		t2 = clock();
		temps3 += (float)(t2-t1)/CLOCKS_PER_SEC;
	}
	
	
	FILE* statout=fopen("stat.data","w");
	for(int i=1;i<=maxTask;i++){
		fprintf(statout,"%d	%f 	%f  %f\n",i,taux[0][i-1],taux[1][i-1], taux[2][i-1]);
	}
	fclose(statout);
   	temps1=temps1/maxTask;
   	temps2=temps2/maxTask;
   	temps2=temps2/maxTask;
   	moyenne1=moyenne1/maxTask;
   	moyenne2=moyenne2/maxTask;
   	moyenne3=moyenne3/maxTask;
   	acc1=(temps2/temps1);	
   	acc2=(temps3/temps1);	
   	amelio1=(moyenne2/moyenne1);
   	amelio2=(moyenne3/moyenne1);
   	eff1=amelio1/acc1;
   	eff2=amelio2/acc2;
    printf("temps FirstFit= %f \n temps algoLourd= %f \n temps algoSuperLourd= %f \n acceleration algoLourd= %f \n acceleration algoSuperLourd= %f \n reussite FirstFit= %f \n reussite algoLourd=%f \n reussite algoSuperLourd=%f \n amelioration algoLourd= %f \n amelioration algoSuperLourd= %f \n Efficacité algoLourd= %f \n Efficacité algoSuperLourd= %f \n ", temps1,temps2,temps3,acc1,acc2,moyenne1,moyenne2,moyenne3,amelio1,amelio2,eff1,eff2);
	/*
	float temps;
    clock_t t1, t2;

    t1 = clock();
    printf("FF %f\n",multi(0,nb,periode,nbTask));
	t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);

    t1 = clock();
    printf("AL %f\n",multi(1,nb,periode,nbTask));
  	t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);*/

}