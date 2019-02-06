
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct task{
	int num;
	int delay;
	int cycle[2];
}task;

typedef struct chaine{
	task* t;
	struct chaine* next;
}chaine;

chaine* initChaine(int nbTask,int delayMin,int delayMax){
	srand(time(NULL));
	chaine* liste=NULL;
	chaine* tmp;
	for(int i=0;i<nbTask;i++){
		tmp=malloc(sizeof(chaine));
		tmp->t=malloc(sizeof(task));
		tmp->t->num=nbTask-i;
		tmp->t->delay=(rand()%delayMax)+delayMin;
		tmp->t->cycle[0]=1;
		tmp->t->cycle[1]=1;
		tmp->next=liste;
		liste=tmp;
	}
	return liste;
}

void freeChaine(chaine* liste){
	chaine* tmp;
	while(liste!=NULL){
		tmp=liste;
		liste=liste->next;
		free(tmp->t);
		free(tmp);
	}
}

int compte(chaine* liste,int nbTask){
	int cpt=0;
	chaine* tmp=liste;
	while(tmp!=NULL){
		tmp=tmp->next;
		cpt++;
	}
	return nbTask-cpt;
}


void afficheTab(int periode,task* tab[2][periode]){
	for(int i=0;i<periode;i++){
		printf("%d :",i);
		if(tab[0][i]==NULL) printf("no | ");
		else printf(" %d | ",tab[0][i]->num);
		if(tab[1][i]==NULL) printf("no 	 \n");
		else printf("%d \n",tab[1][i]->num);
	}
}

int FirstFit(int periode,int nbTask,int delayMin,int delayMax){
	chaine* tmp;
	chaine* liste=initChaine(nbTask,delayMin,delayMax);

	task* tab[2][periode];
	for(int i=0;i<periode;i++){
		tab[0][i]=NULL;
		tab[1][i]=NULL;
	}
	tmp=liste;
	chaine* last=NULL;
	int b=0,c;
	chaine* ftmp;
	chaine* place=NULL;
	while(tmp!=NULL){
		b=0;c=0;
		for(int i=0;i<periode;i++){
			if(tab[0][i]==NULL && tab[1][(i+tmp->t->delay)%periode]==NULL) {
				tab[0][i]=tmp->t;
				tab[1][(i+tmp->t->delay)%periode]=tmp->t;
				i=periode;
				if(last==NULL){liste=tmp->next;b=1;ftmp=tmp;}
				else {
					last->next=tmp->next;
					tmp->next=NULL;
					ftmp=tmp;
					tmp=last;
				}
				c=1;
			}
		}
		if(!b)last=tmp;
		tmp=tmp->next;
		if(c){ftmp->next=place;place=ftmp;}
	}
	int cpt=compte(liste,nbTask);
	//afficheTab(periode,tab);
	freeChaine(liste);
	freeChaine(place);
	return cpt;
}

// Fontion a chier mais je savais pas comment faire autrement
float completionFF(float cpt, int nb, int nbTask) {
	return (cpt*100)/((float)nbTask*(float)nb);
}

float multiFF(int nb,int periode,int nbTask,int delayMin,int delayMax){
	float cpt=0;
	for(int i=0;i<nb;i++){
		cpt+=FirstFit(periode,nbTask,delayMin,delayMax);
		//printf("%d / %d \n",i+1,nb);
	}
	//printf("%f \n",cpt);
	return completionFF(cpt, nb, nbTask);
}

int main(int argc,char** argv){
	FirstFit(1000,1000,0,100);
	printf("Taux de completion a 100/100 : %f \n",multiFF(1000000,100,100,0,100));
	//printf("Taux de completion a 75/100 : %f \n",multiFF(10000,100,75,0,100));
	//printf("Taux de completion a 50/100 : %f \n",multiFF(10000,100,50,0,100));
	return 0;
}