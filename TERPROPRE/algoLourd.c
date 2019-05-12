#include "algoLourd.h"

TaskTab algoLourd(TaskTab tasktab,int periodeMax,int nbTask){
	Periode* periode[2];
	
	int val,cpt,min=periodeMax,postask=0,posper,tmpposper=-1;
	periode[0]=initPeriode(0,periodeMax-1,NULL);
	periode[1]=initPeriode(0,periodeMax-1,NULL);

	for(int k=0;k<nbTask;k++){
			min=periodeMax;
			postask=-1;
			posper=-1;
			tmpposper=-1;
		for(int j=0;j<tasktab.nbTask;j++){
		//	printf("j=%d\n",j);
			cpt=0;
			if(tasktab.tab[j].place==-1){
				for(int i=0;i<periodeMax;i++){
					//printf(" %d %d %d\n",i,verifPeriode(periode[0],i,tasktab.tab[j].cycle[0],periodeMax-1),verifPeriode(periode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1));
					if(verifPeriode(periode[0],i,tasktab.tab[j].cycle[0],periodeMax-1) && verifPeriode(periode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1)){
						tmpposper=i;
						cpt++;
						//printf("i %d\n",i);
					}
				}
				//printf("%d %d\n",j,cpt);
				if(cpt!=0 && cpt<=min){
					posper=tmpposper;
					min=cpt;
					postask=j;
				}
			}
		}
		if(postask!=-1){
			//affichePeriode(periode[0]);
			//affichePeriode(periode[1]);
			tasktab.tab[postask].place=posper;
			periode[0]=coupePeriode(periode[0],posper,tasktab.tab[postask].cycle[0],periodeMax-1);
			periode[1]=coupePeriode(periode[1],(posper+tasktab.tab[postask].delay)%periodeMax,tasktab.tab[postask].cycle[1],periodeMax-1);
			
		}
	}
	
	//double cpt=completionFF(tasktab);
	//printf("%f\n",cpt );
	//afficheTab(res);
	//freeChaine(liste);
	//freeChaine(place);
	freeChaine(periode[0]);
	freeChaine(periode[1]);
	//printf("fin algoLourd\n");
	return tasktab;
}
/*
int main(int argc,char** argv){
    clock_t t1, t2;
     float temps;
     srand(time(NULL));
	TaskTab tasktab=initData(50,1000,50000);
    t1 = clock();
    TaskTab res=algoLourd(tasktab,50000,50);
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