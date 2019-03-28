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

double multi(int algo,int nb,int periode,int nbTask){
	double cpt=0;
	TaskTab tasktab;
	double val=0;
	
	char nom[50];
	for(int i=0;i<nb;i++){
		printf("%d %d \n",nbTask,i);
		nomF(i,nom);
		tasktab=lireData(nom,nbTask);
		//afficheTab(tasktab);
		if(algo==0)val=completionFF(FirstFit(tasktab,periode,nbTask));
		else val=completionFF(algoLourd(tasktab,periode,nbTask));
		if(val==100)cpt++;
		//printf("%f\n",val);
		//free(tasktab.tab);
	}
	return (cpt/nb)*100;
}

int main(int argc,char** argv){
	//affichePeriode(periodes[0]);
	printf("\n");
	int periode=atoi(argv[1]),cycle=atoi(argv[3]),nb=atoi(argv[4]),nbTask=atoi(argv[2]);
	
	int maxTask=periode/cycle;
	gen(periode,cycle,nb);
	double taux[2][maxTask];
	for(int i=1;i<=maxTask;i++){

		taux[0][i-1]=multi(0,nb,periode,i);
		taux[1][i-1]=multi(1,nb,periode,i);
	}
	FILE* statout=fopen("stat.data","w");
	for(int i=1;i<=maxTask;i++){
		fprintf(statout,"%d	%f 	%f \n",i,taux[0][i-1],taux[1][i-1]);
	}
	fclose(statout);

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