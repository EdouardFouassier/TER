#include "TER.h"

char* nomF(int i){
	int logi;
	char* nom;
	char* nomi;
	char* c;
	if(i==0)logi=1;
	else logi=log(i)+1;
	c=malloc(sizeof(int)*logi);
	nom="data/in";
	nomi=malloc((7+logi)*sizeof(char));
	strcpy(nomi,nom);
    sprintf(c,"%d",i);
	strcat(nomi,c);
	free(c);
	return nomi;
}

double multi(int algo,int nb,int periode,int nbTask){
	double cpt=0;
	TaskTab tasktab;
	double val=0;
	char* nom;
	for(int i=0;i<nb;i++){
		nom=nomF(i);
		tasktab=lireData(nom,nbTask);
		//afficheTab(tasktab);
		free(nom);
		if(algo==0)val+=completionFF(FirstFit(tasktab,periode,nbTask));
		else val+=completionFF(algoLourd(tasktab,periode,nbTask));
		if(val==100)cpt++;
		//printf("%f\n",val);
	}
	return (val/nb);
}

int main(int argc,char** argv){

	int periode=atoi(argv[1]),cycle=atoi(argv[3]),nb=atoi(argv[4]),nbTask=atoi(argv[2]);
	gen(periode,cycle,nb);
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
    printf("temps = %f\n", temps);
}