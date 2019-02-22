#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char** argv){
	FILE* f[10];
	char* nom;
	int val;
	srand(time(NULL));
	nom=malloc(3*sizeof(char));
	nom[0]='i';
	nom[1]='n';
	int cycle=3;
	if(argc==2)cycle=atoi(argv[1]);
	for(int i=0;i<10;i++){

		nom[2]=(char)(i+48);

		f[i]=fopen(nom,"w");
		fprintf(f[i],"%d\n",cycle);
		for(int j=0;j<1000;j++){

			val=rand()%1000;
			fprintf(f[i],"%d\n",val);
		}
	}
}