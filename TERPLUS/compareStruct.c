#include "compareStruct.h"


double multi(int algo,int nb,int periode,int nbTask){
	TaskTab tasktab;
	int logi;
	char* nom;
	int i=0;
	chaine* liste;
	//#pragma omp for private (val,nom,i,tasktab)
	for(i=0;i<nb;i++){
		if(i==0)logi=1;
		else logi=log(i)+1;
		//printf("1 %d %d %d\n",nbTask,i,omp_get_thread_num());
		nom=malloc(sizeof(int)*logi+7);
		sprintf(nom,"data/in%d",i);
		
		
		if(algo==0){
			tasktab=lireData(nom,nbTask);
			FirstFit(tasktab,periode,nbTask);
		}
		else {
			liste=initChaine(nom,nbTask);
			oldFirstFit(periode,nbTask,liste);
		}
		free(nom);
	}
}

int main(int argc,char** argv){
	//affichePeriode(periodes[0]);
//	printf("\n");
	float temps;
    clock_t t1, t2;

    
	int periode=atoi(argv[1]),cycle=atoi(argv[3]),nb=atoi(argv[4]),nbTask=atoi(argv[2]);
	
	int maxTask=periode/cycle;
	gen(periode,cycle,nb);
	double tempsOld;
	double tempsNew;
	t1 = clock();
	for(int i=1;i<=maxTask;i++){
		multi(0,nb,periode,i);
	}
	t2 = clock();
	tempsNew=(double)(t2-t1)/CLOCKS_PER_SEC;
	t1 = clock();
	for(int i=1;i<=maxTask;i++){
		multi(1,nb,periode,i);
	}
	t2 = clock();
	tempsOld=(double)(t2-t1)/CLOCKS_PER_SEC;
	double acc=(tempsOld-tempsNew)/tempsOld;
	printf("TempsOld=%f\nTempsNew=%f\nacceleration=%f\n",tempsOld,tempsNew,acc);
}