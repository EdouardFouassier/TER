#include "bibli.c"

int oldFirstFit(int periode,int nbTask,chaine* liste){
	chaine* tmp;

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