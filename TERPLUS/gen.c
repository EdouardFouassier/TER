#include "gen.h"

void gen(int periode,int cycle,int nbFile ){ 
	FILE* f[100];
	int logi;
	char* nom;
	char* nomi;
	int val;
	srand(time(NULL));
	
	char* c;

	for(int i=0;i<nbFile;i++){
		if(i==0)logi=1;
		else logi=log(i)+1;
		c=malloc(sizeof(int)*logi);
		nom="data/in";
		nomi=malloc((7+logi)*sizeof(char));
		strcpy(nomi,nom);
        sprintf(c,"%d",i);
		strcat(nomi,c);
		f[i]=fopen(nomi,"w");
		free(nomi);
		free(c);
		fprintf(f[i],"%d\n",cycle);
		for(int j=0;j<periode;j++){

			val=rand()%periode;
			fprintf(f[i],"%d\n",val);
		}
		fclose(f[i]);
	}
}