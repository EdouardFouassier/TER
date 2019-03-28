#include "TER.h"

void  nomF(int i,char nom[]){
	int logi;
	if(i==0)logi=1;
	else logi=log(i)+1;
	char nomi[logi];
	
	strcpy(nom,"data/in");
    sprintf(nomi,"%d",i);
	strcat(nom,nomi);
}

typedef struct entree{
	int algo;
	int nb;
	int periode;
	int nbTask;
}entree;

void* multi(void* in){
	entree* vals=(entree *)in;
	double cpt=0;
	TaskTab tasktab;
	double val=0;
	int algo=vals->algo;
	int nb=vals->nb;
	int periode=vals->periode;
	int nbTask=vals->nbTask;
	char nom[50];
	for(int i=0;i<nb;i++){
		printf("%d %d \n",nbTask,i);
		nomF(i,nom);
		tasktab=lireData(nom,nbTask);
		//afficheTab(tasktab);
		if(algo==0)val+=completionFF(FirstFit(tasktab,periode,nbTask));
		else val+=completionFF(algoLourd(tasktab,periode,nbTask));
		if(val==100)cpt++;
		//printf("%f\n",val);
		//free(tasktab.tab);
	}
	double* res=malloc(sizeof(double));
	res[0]=(cpt/nb)*100;
	return (void*)res;
}

int main(int argc,char** argv){
	//affichePeriode(periodes[0]);
	printf("\n");
	int periode=atoi(argv[1]),cycle=atoi(argv[3]),nb=atoi(argv[4]),nbTask=atoi(argv[2]);
	
	int maxTask=periode/cycle;
	gen(periode,cycle,nb);
	double taux[2][maxTask];
	pthread_t thread[2][maxTask];
	entree* vals=malloc(sizeof(entree));
	vals->algo=0;
	vals->nb=nb;
	vals->periode=periode;
	for(int i=1;i<=maxTask;i++){

		vals->nbTask=i;
		pthread_create( &thread[0][i], NULL, multi, (void*) vals);
		//taux[0][i-1]=multi(0,nb,periode,i);
		//taux[1][i-1]=multi(1,nb,periode,i);
	}
	for(int i=1;i<=maxTask;i++){
		void* res;
		pthread_join(thread[0][i],res);
		taux[0][i]=(double)res;
		printf("%d %f\n",i,taux[0][i]);
	}
	/*FILE* FFout=fopen("FirstFit.data","w");
	FILE* ALout=fopen("AlgoLourd.data","w");
	for(int i=1;i<=maxTask;i++){
		fprintf(FFout,"%d 	%f \n",i,taux[0][i-1]);
		fprintf(ALout,"%d 	%f \n",i,taux[1][i-1]);
	}
	fclose(FFout);
	fclose(ALout);*/

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