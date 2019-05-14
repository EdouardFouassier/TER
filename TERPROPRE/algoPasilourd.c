
#include "algoPasilourd.h"

TaskTab algoPasilourd(TaskTab tasktab,int periodeMax,int nbTask){
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
	tasktab.tab[place[nbTask-1]].place=((periodeMax-val[nbTask-1])-tasktab.tab[place[nbTask-1]].delay)%periodeMax;
	periode[0]=coupePeriode(periode[0],((periodeMax-val[nbTask-1])-tasktab.tab[place[nbTask-1]].delay)%periodeMax,tasktab.tab[place[nbTask-1]].cycle[0],periodeMax-1);
	periode[1]=coupePeriode(periode[1],(periodeMax-val[nbTask-1])%periodeMax,tasktab.tab[place[nbTask-1]].cycle[1],periodeMax-1);
	int a=(periodeMax-val[nbTask-1])%periodeMax;
	int b=((periodeMax-val[nbTask-1])-tasktab.tab[place[nbTask-1]].delay)%periodeMax;
	printf("a %d b %d %d\n",a,b,tasktab.tab[place[nbTask-1]].delay);
	affichePeriode(periode[0]);
	affichePeriode(periode[1]);
	//printf("%d\n",tasktab.tab[place[nbTask-1]].place);
	int nPlace=1;
	for(int j=0;j<nbTask;j++){
	for(int i=nbTask-1;i>=0;i--){
		a=((periodeMax-val[i])+nPlace*cycle)%periodeMax;
		b=((periodeMax-val[i])-tasktab.tab[place[i]].delay+nPlace*cycle)%periodeMax;
		printf("a %d b %d\n",a,b);
		if(tasktab.tab[place[i]].place==-1 && verifPeriode(periode[0],((periodeMax-val[i])-tasktab.tab[place[i]].delay+nPlace*cycle)%periodeMax,tasktab.tab[place[i]].cycle[0],periodeMax-1) && verifPeriode(periode[1],((periodeMax-val[i])+nPlace*cycle)%periodeMax,tasktab.tab[place[i]].cycle[1],periodeMax-1)){
			periode[0]=coupePeriode(periode[0],((periodeMax-val[i])-tasktab.tab[place[i]].delay+nPlace*cycle)%periodeMax,tasktab.tab[place[i]].cycle[0],periodeMax-1);
			periode[1]=coupePeriode(periode[1],((periodeMax-val[i])+nPlace*cycle)%periodeMax,tasktab.tab[place[i]].cycle[1],periodeMax-1);
			tasktab.tab[place[i]].place=((periodeMax-val[i])-tasktab.tab[place[i]].delay+nPlace*cycle)%periodeMax;
			affichePeriode(periode[0]);
			affichePeriode(periode[1]);
			i=0;
		}
	}
	nPlace++;
	}
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

int verif(TaskTab res,int cycle,int periode){
	int val;
	for(int i=0;i<res.nbTask;i++){
		val=(res.tab[i].place+res.tab[i].delay)%periode;
		if(res.tab[i].place!=-1)
		for(int j=i+1;j<res.nbTask;j++){
			if(res.tab[j].place!=-1 && abs(val-(res.tab[j].place+res.tab[j].delay)%periode)<cycle){printf("%d %d\n",i,j);return 1;}
		}
	}
	for(int i=0;i<res.nbTask;i++){
		val=(res.tab[i].place)%periode;
		if(res.tab[i].place!=-1)
		for(int j=i+1;j<res.nbTask;j++){
			if(res.tab[j].place!=-1 && abs(val-(res.tab[j].place)%periode)<cycle){printf("%d %d\n",i,j);return 1;}
		}
	}
	return 0;
}


int main(int argc,char** argv){
    clock_t t1, t2;
     float temps;
     srand(time(NULL));
     int cycle=1000;
     int periode=50000;
     int nb=50;
	TaskTab tasktab=initData(nb,cycle,periode);
    t1 = clock();
    TaskTab res=algoPasilourd(tasktab,periode,nb);
    double completion=completionFF(res);
    t2 = clock();
    for(int i=0;i<nb;i++)if(res.tab[i].place!=-1)printf("%d %d %d\n",i,res.tab[i].place,(res.tab[i].place+res.tab[i].delay)%periode);
    temps += (float)(t2-t1)/CLOCKS_PER_SEC;
    //afficheTab(tasktab);
	
    tasktab=resetData(tasktab);
     afficheTab(res);
    printf("\ncompletion %f temps %f\n",completion,temps);
	free(tasktab.tab);
	if(verif(res,cycle,periode))printf("ERROR !!!!\n");
	else printf("GOOD :)\n");
	return 0;
}