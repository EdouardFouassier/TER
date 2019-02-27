#include "bibli.h"


Periode* initPeriode(int begin,int end,Periode* next){

	Periode* periode=malloc(sizeof(Periode));
	periode->begin=begin;
	periode->end=end;
	periode->next=next;
	return periode;
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
//	//printf("verif %d %d\n",milieu,cycle);
	Periode* tmp=periode;
	int itmp;
	while(tmp!=NULL){
		if(tmp->begin<milieu){	
			////printf("<");
			if(milieu+cycle<=tmp->end){
			//	//printf("<");
				return 1;
			}
			else if((milieu+cycle)==(tmp->end)+1) {
				////printf("=");
				return 1;
			}
			else if(milieu+cycle>tmp->end && tmp->end==taille && periode->begin==0){
					////printf(">");
					itmp=cycle-(tmp->end-milieu)-1;
					if(((periode->end-periode->begin)+1)>itmp){
						return 1;
					}else if(((periode->end-periode->begin)+1)==itmp){
						return 1;
					}
				}
		}
		else if(tmp->begin==milieu){
				////printf("=");
				if(milieu+cycle<=tmp->end){
					////printf("<");
					return 1;
				}
				else if(milieu+cycle==(tmp->end+1)){
				//	//printf("=");
					return 1;
				}
				else if(milieu+cycle>tmp->end && tmp->end==taille && periode->begin==0){
				//	//printf(">");
					itmp=cycle-tmp->end-tmp->begin-1;
					if(((periode->end-periode->begin)+1)>itmp){
					}else if(((periode->end-periode->begin)+1)==itmp){
						return 1;
					}
				}
		}
		tmp=tmp->next;
		////printf("|\n");
	}
	
	return 0;
}

void affichePeriode(Periode* periode){
	Periode* tmp=periode;
	while(tmp!=NULL){
		//printf("(%d , %d) ",tmp->begin,tmp->end);
		tmp=tmp->next;
	}
	//printf("\n");
}

TaskTab lireData(char* nom,int nbTask){
	//if(nbTask>1000)return NULL;
	int cycle=0;
	//printf("%s\n",nom);
	FILE* f=fopen(nom,"r");
	//if(f==NULL)printf("NULL");
	fscanf(f,"%d\n",&cycle);
	//printf("%d\n",cycle);
	TaskTab tasktab;
	tasktab.nbTask=nbTask;
	tasktab.tab=malloc(sizeof(task)*nbTask);
	int val;
	for(int i=0;i<nbTask;i++){
		fscanf(f,"%d\n",&val);
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
/*
TaskTab initChaine(int nbTask,int delayMin,int delayMax){
	srand(time(NULL));
	TaskTab tasktab;
	tasktab.nbTask=nbTask;	
	tasktab.tab=malloc(sizeof(task)*nbTask);
	for(int i=0;i<nbTask;i++){
		tasktab.tab[i].num=i;
		tasktab.tab[i].delay=(rand()%delayMax)+delayMin;
		tasktab.tab[i].cycle[0]=1;
		tasktab.tab[i].cycle[1]=1;
	}
	return tasktab;
}
*/
void freeChaine(Periode* liste){
	Periode* tmp;
	while(liste!=NULL){
		tmp=liste;
		liste=liste->next;
		free(tmp);
	}
}
/*
int compte(tasktab tasktab){
	int cpt=0;
	for(int i=0;i<tasktab.nbTask;i++){
		if(tasktab.tab.place!=-1)cpt++;
	}
	return cpt;
}*/


void afficheTab(TaskTab tasktab){
	for(int i=0;i< tasktab.nbTask;i++)printf("Tache: %d, delay: %d, cycle: %d, place %d.\n",tasktab.tab[i].num,tasktab.tab[i].delay,tasktab.tab[i].cycle[0],tasktab.tab[i].place);
}


double completionFF(TaskTab tasktab) {
	double cpt=0;
	for(int i=0;i< tasktab.nbTask;i++) if(tasktab.tab[i].place!=-1)cpt++;
	return cpt*100/tasktab.nbTask;
}
