#include "bibli.h"


Periode* initPeriode(int begin,int end,Periode* next){

	Periode* periode=calloc(1,sizeof(Periode));
	periode->begin=begin;
	periode->end=end;
	periode->next=next;
	return periode;
}

void copyPeriode(Periode* periode[2],Periode* periodecpy[2]){
	int aff=0;
	//if(aff)printf("check 5\n");
	Periode* tmp=periode[0];
	//if(aff)printf("check -4\n");
	Periode* tmp2;
	//if(aff)printf("check -3\n");
	Periode* tmp3=NULL;
	//if(aff)printf("check -2\n");
	tmp2=initPeriode(tmp->begin,tmp->end,NULL);
	//if(aff)printf("check -1\n");
	periodecpy[0]=tmp2;
	//if(aff)printf("check 0\n");
	if(tmp->next!=NULL){
		//if(aff)printf("check 1\n");
		tmp2->next=tmp3;
		//if(aff)printf("check 2\n");
		tmp=tmp->next;
		//if(aff)printf("check 3\n");
		tmp3=initPeriode(tmp->begin,tmp->end,NULL);
		//if(aff)printf("check 4\n");
	
	while(tmp!=NULL){
		//if(aff)printf("check 5\n");
		tmp2->next=tmp3;
		tmp2=tmp2->next;
		//if(aff)printf("check 6\n");
		//if(aff)printf("check 6.5\n");
		if(tmp->next!=NULL){
			tmp=tmp->next;
			tmp3=initPeriode(tmp->begin,tmp->end,NULL);
		}
		else {
			tmp=tmp->next;
			tmp3=NULL;
		}
		//if(aff)printf("check 7\n");
	}
	}	
	//if(aff)printf("check2 5\n");
	tmp=periode[1];
	//if(aff)printf("check2 -4\n");

	//if(aff)printf("check2 -3\n");
	tmp3=NULL;
	//if(aff)printf("check2 -2\n");
	tmp2=initPeriode(tmp->begin,tmp->end,NULL);
	//if(aff)printf("check2 -1\n");
	periodecpy[1]=tmp2;
	//if(aff)printf("check2 0\n");
	if(tmp->next!=NULL){
		//if(aff)printf("check2 1\n");
		tmp2->next=tmp3;
		//if(aff)printf("check2 2\n");
		tmp=tmp->next;
		//if(aff)printf("check2 3\n");
		tmp3=initPeriode(tmp->begin,tmp->end,NULL);
		//if(aff)printf("check2 4\n");
	
	while(tmp!=NULL){
		//if(aff)printf("check2 5\n");
		tmp2->next=tmp3;
		tmp2=tmp2->next;
		//if(aff)printf("check2 6\n");
		//if(aff)printf("check2 6.5\n");
		if(tmp->next!=NULL){
			tmp=tmp->next;
			tmp3=initPeriode(tmp->begin,tmp->end,NULL);
		}
		else {
			tmp=tmp->next;
			tmp3=NULL;
		}
		//if(aff)printf("check2 7\n");
	}
	}
}

Periode* coupePeriode(Periode* periode,int milieu,int cycle,int taille){ 
//	affichePeriode(periode);
	////printf("coupe %d %d\n",milieu,cycle);
	Periode* tmp=periode;
	Periode* prec=NULL;
	int itmp,b=1;
	////printf("coupe %d %d\n",milieu,cycle);
	while(tmp!=NULL){
		//if(b==1 && milieu==839){//printf("lol %d",tmp->begin);b=0;}
		////printf("%d\n",tmp->begin);
		if(tmp->begin<milieu){	
			//printf("<");
			if(milieu+cycle<=tmp->end){
				//printf("<");
				tmp->next=initPeriode(milieu+cycle,tmp->end,tmp->next);
				tmp->end=milieu-1;
				tmp=NULL;
				return periode;
			}
			else if((milieu+cycle)==(tmp->end)+1) {
				//printf("=");
				tmp->end=milieu-1;
				tmp=NULL;
				return periode;
			}
			else if(milieu+cycle>tmp->end && tmp->end==taille && periode->begin==0){
				//printf(">");
				itmp=cycle-(tmp->end-milieu)-1;
				if(((periode->end-periode->begin)+1)>itmp){
					//printf(">");
					tmp->end=milieu-1;
					periode->begin+=itmp;
					tmp=NULL;
					return periode;
				}else if(((periode->end-periode->begin)+1)==itmp){
					//printf("=");
					if(tmp==periode){
						//printf("1");
						
						periode=NULL;
					}
					else {
						//printf("2");
						tmp->end=milieu-1;
						tmp=periode;
						periode=periode->next;
					}
					free(tmp);
					return periode;
				}
			}
			//printf("lol");
		}
		else if(tmp->begin==milieu){
				//printf("=");
				if(milieu+cycle<=tmp->end){
					//printf("<");
					tmp->begin=milieu+cycle;
					tmp=NULL;
					return periode;
				}
				else if(milieu+cycle==(tmp->end+1)){
					//printf("=");
					if(prec!=NULL) prec->next=tmp->next;
					else periode=periode->next;
					free(tmp);
					return periode;
				}
				else if(milieu+cycle>tmp->end && tmp->end==taille && periode->begin==0){
					//printf(">");
					itmp=cycle-tmp->end-tmp->begin-1;
					if(((periode->end-periode->begin)+1)>itmp){
						//printf(">");
						if(prec!=NULL) prec->next=tmp->next;
						else periode=periode->next;
						
						free(tmp);
						tmp=periode;
						periode->begin+=itmp;
						free(tmp);
						tmp=NULL;
						return periode;
					}else if(((periode->end-periode->begin)+1)==itmp){
						//printf("=");
						if(tmp==periode)periode=NULL;
						else {
							prec->next=tmp->next;
							free(tmp);
							tmp=periode;
							periode=periode->next;
						}
						free(tmp);
						return periode;
					}
				}
		}
		prec=tmp;
		tmp=tmp->next;
		//printf("|\n");
	}
	//printf("lol");
	return periode;
}

int verifPeriode(Periode* periode,int milieu,int cycle,int taille){
	int aff=0;
	//if(aff)printf("verif %d %d\n",milieu,cycle);
	Periode* tmp=periode;
	int itmp;
	while(tmp!=NULL){
		if(tmp->begin<milieu){	
			//if(aff)printf("<");
			if(milieu+cycle<=tmp->end){
				//if(aff)printf("<");
				return 1;
			}
			else if((milieu+cycle)==(tmp->end)+1) {
				//if(aff)printf("=");
				return 1;
			}
			else if(milieu+cycle>tmp->end && tmp->end==taille && periode->begin==0){
					//if(aff)printf(">");
					itmp=cycle-(tmp->end-milieu)-1;
					if(((periode->end-periode->begin)+1)>itmp){
						return 1;
					}else if(((periode->end-periode->begin)+1)==itmp){
						return 1;
					}
				}
		}
		else if(tmp->begin==milieu){
				//if(aff)printf("=");
				if(milieu+cycle<=tmp->end){
					//if(aff)printf("<");
					return 1;
				}
				else if(milieu+cycle==(tmp->end+1)){
					//if(aff)printf("=");
					return 1;
				}
				else if(milieu+cycle>tmp->end && tmp->end==taille && periode->begin==0){
					//if(aff)printf(">");
					itmp=cycle-tmp->end-tmp->begin-1;
					if(((periode->end-periode->begin)+1)>itmp){
					}else if(((periode->end-periode->begin)+1)==itmp){
						return 1;
					}
				}
		}
		tmp=tmp->next;
		//if(aff)printf("|\n");
	}
	
	return 0;
}

int comptePeriode(Periode* periode[2],task t,int taille){
	int cpt=0;
	int tmp=periode[0]->begin+t.delay;
	Periode* tmpP1=periode[1];
	Periode* tmpP0=periode[0];
	int min=0;
	if(tmpP0->end-tmpP0->begin+1>=t.cycle[0]){
		while(tmpP1->begin<=tmp || tmpP1==NULL)tmpP0=tmpP0->next;//tmpP0->end-tmpP0->begin-tmP0.cycle[0]+2
		if(tmpP1!=NULL && (tmpP1->end-tmp+1>=t.cycle[0])){
			if(tmpP0->end-tmpP0->begin-t.cycle[0]+2>tmpP1->end-tmp+1-t.cycle[0]+2) cpt+=tmpP1->end-tmp+1-t.cycle[0]+2;
			else tmpP0->end-tmpP0->begin-t.cycle[0]+2;
		}	
		
	}
	return 0;
}

int verifInter(Periode* periode[2],int milieu,int cycle,int delay,int taille){
//	//printf("verif %d %d\n",milieu,cycle);
	Periode* tmp[2];
	tmp[0]=periode[0];
	tmp[1]=periode[1];
	int itmp;
	int a;
	int b;
	int cpt=0;
	if(periode[0]==NULL || periode[1]==NULL)return cpt;
	while(tmp!=NULL){
		tmp[1]=periode[1];
		while(tmp[1]!=NULL && tmp[1]->begin<=((tmp[0]->begin+delay)%taille+1)){
				tmp[1]=tmp[1]->next;
		}
		if(tmp[1]!=NULL){
		b=((tmp[0]->begin+delay)%taille+1);
		for(a=tmp[0]->begin;a<=tmp[0]->end-cycle;a++){
			if(b+cycle<=tmp[1]->end)cpt++;
			b++;
			if(b>tmp[1]->end && tmp[1]->end==taille && periode[1]->begin==0){
				b=0;
				tmp[1]=periode[1];
			}
			else if(b>tmp[1]->end && tmp[1]->next!=NULL){
				itmp=tmp[1]->end;
				tmp[1]=tmp[1]->next;
				b=tmp[1]->begin;
				a=a+tmp[1]->begin-itmp;
			}else if(b>tmp[1]->end && tmp[1]->next!=NULL)return cpt;


		}}
		tmp[0]=tmp[0]->next;
		////printf("|\n");
	}
	
	return cpt;
}

void affichePeriode(Periode* periode){
	Periode* tmp=periode;
	while(tmp!=NULL){
		printf("(%d , %d) ",tmp->begin,tmp->end);
		tmp=tmp->next;
	}
	printf("\n");
}

TaskTab lireData(char* nom,int nbTask){
	//if(nbTask>1000)return NULL;
	int cycle=0;
	//printf("%s\n",nom);
	FILE* f=fopen(nom,"r");
	//if(f==NULL)printf("NULL");
	if(fscanf(f,"%d\n",&cycle)==1);
	//printf("%d\n",cycle);
	TaskTab tasktab;
	tasktab.nbTask=nbTask;
	tasktab.tab=malloc(sizeof(task)*nbTask);
	int val;
	for(int i=0;i<nbTask;i++){
		if(fscanf(f,"%d\n",&val)==1);
		tasktab.tab[i].num=i;
		//printf("%d\n",val);
		tasktab.tab[i].delay=val;
		tasktab.tab[i].cycle[0]=cycle;
		tasktab.tab[i].cycle[1]=cycle;
		tasktab.tab[i].place=-1;
	}
	fclose(f);
	return tasktab;
}

TaskTab initData(int nbTask,int cycle,int periode){
	TaskTab tasktab;
	tasktab.nbTask=nbTask;
	tasktab.tab=malloc(sizeof(task)*nbTask);
	int val;
	for(int i=0;i<nbTask;i++){
		tasktab.tab[i].num=i;
		tasktab.tab[i].delay=rand()%periode;
		tasktab.tab[i].cycle[0]=cycle;
		tasktab.tab[i].cycle[1]=cycle;
		tasktab.tab[i].place=-1;
	}
	return tasktab;
}

TaskTab resetData(TaskTab tasktab){
	TaskTab new;
	//afficheTab(tasktab);
	new.nbTask=tasktab.nbTask;
	new.tab=malloc(sizeof(task)*tasktab.nbTask);
	for(int i=0;i<tasktab.nbTask;i++){
		new.tab[tasktab.tab[i].num].num=tasktab.tab[i].num;
		new.tab[tasktab.tab[i].num].delay=tasktab.tab[i].delay;
		new.tab[tasktab.tab[i].num].cycle[0]=tasktab.tab[i].cycle[0];
		new.tab[tasktab.tab[i].num].cycle[1]=tasktab.tab[i].cycle[1];
		new.tab[tasktab.tab[i].num].place=-1;
	}
	//free(tasktab.tab);
	return new;
}

chaine* initChaine(char* nom,int nbTask){
	chaine* liste=NULL;
	FILE* f=fopen(nom,"r");
	chaine* tmp;
	int cycle;
	int val;
	if(fscanf(f,"%d\n",&cycle)==1);
	for(int i=0;i<nbTask;i++){
		if(fscanf(f,"%d\n",&val)==1);
		tmp=malloc(sizeof(chaine));
		tmp->t=malloc(sizeof(task));
		tmp->t->num=nbTask-i;
		tmp->t->delay=val;
		tmp->t->cycle[0]=cycle;
		tmp->t->cycle[1]=cycle;
		tmp->next=liste;
		liste=tmp;
	}
	return liste;
}

void freeChaine(Periode* liste){
	Periode* tmp;
	while(liste!=NULL){
		tmp=liste;
		liste=liste->next;
		free(tmp);
	}
}

int compte(TaskTab tasktab){
	int cpt=0;
	for(int i=0;i<tasktab.nbTask;i++){
		if(tasktab.tab->place!=-1)cpt++;
	}
	return cpt;
}


void afficheTab(TaskTab tasktab){
	for(int i=0;i< tasktab.nbTask;i++)printf("Tache: %d, delay: %d, cycle: %d, place %d.\n",tasktab.tab[i].num,tasktab.tab[i].delay,tasktab.tab[i].cycle[0],tasktab.tab[i].place);
}


double completionFF(TaskTab tasktab) {
	double cpt=0;
	for(int i=0;i< tasktab.nbTask;i++) {
		if(tasktab.tab[i].place>=0)cpt++;
	}
	//printf("%f\n",(cpt*100)/tasktab.nbTask);
	//afficheTab(tasktab);
	//free(tasktab.tab);
	return (cpt*100)/tasktab.nbTask;
}
