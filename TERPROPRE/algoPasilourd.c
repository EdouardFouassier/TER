
#include "algoPasilourd.h"

TaskTab algoYannou(TaskTab tasktab,int periodeMax,int nbTask){
	Periode* periode[2];
	int cycle=tasktab.tab[0].cycle[0];
	periode[0]=initPeriode(0,periodeMax-1,NULL);
	periode[1]=initPeriode(0,periodeMax-1,NULL);
	int val[nbTask];
	int decal=0;
	int place[nbTask];
	for(int i=0;i<nbTask;i++){
		int tmpval=tasktab.tab[i].delay%cycle;
		//printf("calcule %d mod %d = %d \n",tasktab.tab[i].delay,cycle,tmpval);
		int j=0;
		while(j<i && val[j]<tmpval) {
			//printf("passe  %d \n",j);
			j++;
		}
		int tmp;
		int tmpplace=i;
		for(;j<=i;j++){
			tmp=place[j];
			place[j]=tmpplace;
			tmpplace=tmp;
			

			tmp=val[j];
			val[j]=tmpval;
			tmpval=tmp;
		}
		/*for(j=0;j<=i;j++){
		printf("tour %d : %d %d \n",i,j,val[j]);
		}*/
	}
	/*printf("\n");
	for(int i=0;i<nbTask;i++){
		printf("%d %d %d\n",val[i],place[i],tasktab.tab[i].delay%cycle);
	}*/
	tasktab.tab[place[nbTask-1]].place=((periodeMax-val[nbTask-1])+tasktab.tab[place[nbTask-1]].delay)%periodeMax;
	periode[0]=coupePeriode(periode[0],((periodeMax-val[nbTask-1])+tasktab.tab[place[nbTask-1]].delay)%periodeMax,tasktab.tab[place[nbTask-1]].cycle[0],periodeMax-1);
	periode[1]=coupePeriode(periode[1],periodeMax-val[nbTask-1],tasktab.tab[place[nbTask-1]].cycle[1],periodeMax-1);
				
	//printf("%d\n",tasktab.tab[place[nbTask-1]].place);
	int nPlace=1;
	for(int j=0;j<nbTask;j++){
	for(int i=nbTask-1;i>=0;i--){
		if(tasktab.tab[place[i]].place==-1 && verifPeriode(periode[0],((periodeMax-val[i])+tasktab.tab[place[i]].delay+nPlace*cycle)%periodeMax,tasktab.tab[place[i]].cycle[0],periodeMax-1) && verifPeriode(periode[1],((periodeMax-val[i])+nPlace*cycle)%periodeMax,tasktab.tab[place[i]].cycle[1],periodeMax-1)){
			periode[0]=coupePeriode(periode[0],((periodeMax-val[i])+tasktab.tab[place[i]].delay+nPlace*cycle)%periodeMax,tasktab.tab[place[i]].cycle[0],periodeMax-1);
			periode[1]=coupePeriode(periode[1],((periodeMax-val[i])+nPlace*cycle)%periodeMax,tasktab.tab[place[i]].cycle[1],periodeMax-1);
			tasktab.tab[place[i]].place=((periodeMax-val[i])+tasktab.tab[place[i]].delay+nPlace*cycle)%periodeMax;
			nPlace++;
			i=0;
		}
	}}
	for(int j=0;j<tasktab.nbTask;j++){
		if(tasktab.tab[j].place==-1){
		for(int i=0;i<periodeMax;i++){
			if(periode[0]==NULL || periode[1]==NULL){i=periodeMax;j=tasktab.nbTask;}
			else if(verifPeriode(periode[0],i,tasktab.tab[j].cycle[0],periodeMax-1) && verifPeriode(periode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1)) {
				
				periode[0]=coupePeriode(periode[0],i,tasktab.tab[j].cycle[0],periodeMax-1);
				
				periode[1]=coupePeriode(periode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1);
				
				tasktab.tab[j].place=i;
				i=periodeMax;
			}
		}
		}
	}
	return tasktab;
}

/*
int main(int argc,char** argv){
    clock_t t1, t2;
     float temps;
     srand(time(NULL));
	TaskTab tasktab=initData(50,1000,50000);
    t1 = clock();
    TaskTab res=algoPasilourd(tasktab,50000,50);
    double completion=completionFF(res);
    t2 = clock();
    temps += (float)(t2-t1)/CLOCKS_PER_SEC;
    //afficheTab(tasktab);
    tasktab=resetData(tasktab);
     afficheTab(res);
    printf("\ncompletion %f temps %f\n",completion,temps);
	free(tasktab.tab);
	return 0;
}*/