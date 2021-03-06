
#include "FirstFit.h"

TaskTab FirstFit(TaskTab tasktab,int periodeMax,int nbTask){
	Periode* periode[2];
	int val;
	//printf("debut FF\n");
	periode[0]=initPeriode(0,periodeMax-1,NULL);
	periode[1]=initPeriode(0,periodeMax-1,NULL);
//	affichePeriode(periode[0]);
			//	affichePeriode(periode[1]);
	//afficheTab(tasktab);
	for(int j=0;j<tasktab.nbTask;j++){
	//	printf("j=%d\n",j);
		for(int i=0;i<periodeMax;i++){
		//	affichePeriode(periode[0]);

	//printf("\n");
		//	affichePeriode(periode[1]);
			//printf("i=%d\n",i);
			if(periode[0]==NULL || periode[1]==NULL){i=periodeMax;j=tasktab.nbTask;}
			else if(verifPeriode(periode[0],i,tasktab.tab[j].cycle[0],periodeMax-1) && verifPeriode(periode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1)) {
				//affichePeriode(periode[0]);
				//affichePeriode(periode[1]);
				periode[0]=coupePeriode(periode[0],i,tasktab.tab[j].cycle[0],periodeMax-1);
				//affichePeriode(periode[0]);
				//affichePeriode(periode[1]);
				periode[1]=coupePeriode(periode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1);
				//affichePeriode(periode[0]);
				//affichePeriode(periode[1]);
				tasktab.tab[j].place=i;
				i=periodeMax;
			}
		}
		//scanf("%d",&val);
	}
	freeChaine(periode[0]);
	freeChaine(periode[1]);
	//double cpt=completionFF(tasktab);
	//printf("%f\n",cpt );
	//afficheTab(tasktab);
	//freeChaine(liste);
	//freeChaine(place);
	return tasktab;
}

/*
int main(int argc,char** argv){
     clock_t t1, t2;
     float temps;
     srand(time(NULL));
	TaskTab tasktab=initData(50,1000,50000);
    t1 = clock();
    double completion=completionFF(FirstFit(tasktab,50000,50));
    t2 = clock();
    temps += (float)(t2-t1)/CLOCKS_PER_SEC;
    //afficheTab(tasktab);
    tasktab=resetData(tasktab);
     afficheTab(tasktab);
    printf("%f %f\n",completion,temps);
	free(tasktab.tab);
	return 0;
}*/