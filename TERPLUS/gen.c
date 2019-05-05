#include "gen.h"

void gen(int periode,int cycle,int nbFile ){ 
	FILE* f[nbFile];
	int logi;
	char* nom;
	int val;
	srand(time(NULL));
	
	for(int i=0;i<nbFile;i++){
		if(i==0)logi=1;
		else logi=log(i)+1;
		nom=malloc(sizeof(int)*logi+7);
        sprintf(nom,"data/in%d",i);
		f[i]=fopen(nom,"w");
		free(nom);
		fprintf(f[i],"%d\n",cycle);
		for(int j=0;j<periode;j++){

			val=rand()%periode;
			fprintf(f[i],"%d\n",val);
		}
		fclose(f[i]);
	}
}