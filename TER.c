
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

typedef struct stats{
	double tauxCompletion;
	double tauxReussite;
	double tauxMin;
	double tauxMax;
}stats;


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

// Fontion a chier mais je savais pas comment faire autrement
double completionFF(double cpt, int nbTask) {
	return ((cpt*100)/((double)nbTask));
}

double FirstFit(int periode,int nbTask,int delayMin,int delayMax){
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
	double cpt=completionFF((double)compte(liste,nbTask),nbTask);
	//afficheTab(periode,tab);
	freeChaine(liste);
	freeChaine(place);
	return cpt;
}

double ReverseFirstFit(int periode,int nbTask,int delayMin,int delayMax){
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
	for(int i=0;i<periode;i++){
		b=0;c=0;
		tmp=liste;
		last=NULL;
		while(tmp!=NULL){
			b=0;c=0;
			if(tab[0][i]==NULL && tab[1][(i+tmp->t->delay)%periode]==NULL) {
				tab[0][i]=tmp->t;
				tab[1][(i+tmp->t->delay)%periode]=tmp->t;
				if(last==NULL){liste=tmp->next;b=1;ftmp=tmp;}
				else {
					last->next=tmp->next;
					tmp->next=NULL;
					ftmp=tmp;
					tmp=last;
				}
				ftmp->next=place;place=ftmp;
				tmp=NULL;
			}
			else{
				if(!b)last=tmp;
				tmp=tmp->next;
			}
		}
		
	}
	double cpt=completionFF((double)compte(liste,nbTask),nbTask);
	//afficheTab(periode,tab);
	freeChaine(liste);
	freeChaine(place);
	return cpt;
}

stats multiFF(int algo,int nb,int periode,double taux,int delayMin,int delayMax){
	double moy=0,val,reussite=0,min=100,max=0;
	stats stat;
	int tmpP;
	srand(time(NULL));
	for(int i=0;i<nb;i++){
		tmpP=10+rand()%(periode*2);
		if(algo==0)val=FirstFit(tmpP,tmpP*taux,delayMin,delayMax);
		else val=ReverseFirstFit(tmpP,tmpP*taux,delayMin,delayMax);
		moy+=val;
		if(val<min)min=val;
		if(val>max)max=val;
		if(val==100)reussite++;
	}
	reussite=(reussite/nb)*100;
	moy=((double)moy/(double)nb);
	stat.tauxCompletion=moy;
	stat.tauxReussite=reussite;
	stat.tauxMin=min;
	stat.tauxMax=max;
	return stat;
}

int main(int argc,char** argv){
//	ReverseFirstFit(100,100,0,100);
	float temps;
    clock_t t1, t2;
 
    t1 = clock();
    printf("\nAlgo First Fit:\n");
    stats stat=multiFF(0,1000000,100,1.0,0,100);
	printf("A 100/100 :\nTaux de completion : %f\nTaux de reussite : %f\nTaux minimum : %f\nTaux maximum : %f\n",stat.tauxCompletion,stat.tauxReussite,stat.tauxMin,stat.tauxMax);
	stat=multiFF(0,1000000,100,0.75,0,100);
	printf("A 75/100 :\nTaux de completion : %f\nTaux de reussite : %f\nTaux minimum : %f\nTaux maximum : %f\n",stat.tauxCompletion,stat.tauxReussite,stat.tauxMin,stat.tauxMax);
	stat=multiFF(0,1000000,100,0.50,0,100);
	printf("A 50/100 :\nTaux de completion : %f\nTaux de reussite : %f\nTaux minimum : %f\nTaux maximum : %f\n",stat.tauxCompletion,stat.tauxReussite,stat.tauxMin,stat.tauxMax);
	t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);

    t1 = clock();
    printf("\nAlgo Reverse First Fit:\n");
    stat=multiFF(1,1000000,100,1.0,0,100);
	printf("A 100/100 :\nTaux de completion : %f\nTaux de reussite : %f\nTaux minimum : %f\nTaux maximum : %f\n",stat.tauxCompletion,stat.tauxReussite,stat.tauxMin,stat.tauxMax);
	stat=multiFF(1,1000000,100,0.75,0,100);
	printf("A 75/100 :\nTaux de completion : %f\nTaux de reussite : %f\nTaux minimum : %f\nTaux maximum : %f\n",stat.tauxCompletion,stat.tauxReussite,stat.tauxMin,stat.tauxMax);
	stat=multiFF(1,1000000,100,0.50,0,100);
	printf("A 50/100 :\nTaux de completion : %f\nTaux de reussite : %f\nTaux minimum : %f\nTaux maximum : %f\n",stat.tauxCompletion,stat.tauxReussite,stat.tauxMin,stat.tauxMax);
  	t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);
}