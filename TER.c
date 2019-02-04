
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

chaine* initChaine(int var){
	srand(time(NULL));
	chaine* liste=NULL;
	chaine* tmp;
	for(int i=0;i<var;i++){

		tmp=malloc(sizeof(chaine));
		tmp->t=malloc(sizeof(task));
		tmp->t->num=var-i;
		tmp->t->delay=rand()%10;
		tmp->t->cycle[0]=1;
		tmp->t->cycle[1]=1;
		tmp->next=liste;
		liste=tmp;

	}
	return liste;
}

int FirstFit(int var){
	chaine* tmp;
	chaine* liste=initChaine(var);
	/*for(int i=0;i<var;i++){
		printf("task: %d / delay: %d / cycle1: %d / cycle2: %d\n",tab[i].num,tab[i].delay,tab[i].cycle[0],tab[i].cycle[1]);
	}*/

	task* FF[2][var];
	for(int i=0;i<var;i++){
		FF[0][i]=NULL;
		FF[1][i]=NULL;
		
	}
	tmp=liste;
	chaine* last=NULL;
	int b=0,c;
	chaine* ftmp;
	int cpt=0;
	while(tmp!=NULL){
		b=0;c=0;
		for(int i=0;i<var;i++){
			if(FF[0][i]==NULL && FF[1][(i+tmp->t->delay)%var]==NULL) {
				FF[0][i]=tmp->t;
				FF[1][(i+tmp->t->delay)%var]=tmp->t;
				i=var;
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
		//printf("%d\n",tmp->t->num);

		tmp=tmp->next;
		if(c){free(ftmp);}
		//printf("%d ",cpt);
		cpt++;
		
		//printf("%d\n",tmp->t->num);
	}

/*	for(int i=0;i<var;i++){
		printf("%d :",i);
		if(FF[0][i]==NULL) printf("no | ");
		else printf(" %d | ",FF[0][i]->num);
		if(FF[1][i]==NULL) printf("no 	 \n");
		else printf("%d \n",FF[1][i]->num);
	}*/
	tmp=liste;
	if(liste==NULL){ /*printf("Tout les elements ont été placé\n");*/free(liste);free(tmp);
	for(int i=0;i<var;i++){
		if(FF[0][i]!=NULL){
			free(FF[0][i]);
		}
	} return var;}
	else{
		int i=0;
		chaine* ftmp;
		//printf("reste : ");
		while(tmp!=NULL){
		//	printf("%d ",tmp->t->num );
			ftmp=tmp;
			tmp=tmp->next;
			i++;
			free(ftmp->t);
			free(ftmp);
		}
		//printf("\n");
		for(int i=0;i<var;i++){
		if(FF[0][i]!=NULL){
			free(FF[0][i]);
		}
	}
		return var-i;
	}
}

float multiFF(int nb,int var){
	float cpt=0;
	for(int i=0;i<nb;i++){
		cpt+=FirstFit(var);

		printf("%d / %d \n",i,nb);
	}
	cpt=cpt/(float)nb;
	cpt=((float)cpt/(float)var)*100;
	return cpt;


}

int main(int argc,char** argv){
	
	FirstFit(20);
	printf("%f\n",multiFF(100000,100));
	return 0;
}