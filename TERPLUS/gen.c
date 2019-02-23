#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int main(int argc,char** argv){
	FILE* f[100];
	int logi;
	char* nom;
	char* nomi;
	int val;
	srand(time(NULL));
	
	char* c;
	int cycle=1;
	if(argc==2)cycle=atoi(argv[1]);
	for(int i=0;i<100;i++){
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
		for(int j=0;j<1000;j++){

			val=rand()%1000;
			fprintf(f[i],"%d\n",val);
		}
	}
}