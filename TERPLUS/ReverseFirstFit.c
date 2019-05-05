
#include "bibli.c"


double ReverseFirstFit(chaine* liste,int periode,int nbTask){
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

int main(int argc,char** argv){
	if(argc!=3)return 0;
	if(ReverseFirstFit(lireData(argv[1],atoi(argv[2]),1),1000,atoi(argv[2]))==100)printf("1");
	else printf("0");
	return 0;
}