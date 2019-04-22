#include "algoLourd.h"

TaskTab algoLourd(TaskTab tasktab,int periodeMax,int nbTask){
	Periode* periode[2];
	TaskTab res;
	res.tab=malloc(sizeof(task)*nbTask);
	res.nbTask=0;
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
			res.tab[res.nbTask]=tasktab.tab[postask];
			res.nbTask++;
			tasktab.tab[postask]=tasktab.tab[tasktab.nbTask-1];
			tasktab.nbTask--;
		}
	}
	for(int j=0;j<tasktab.nbTask;j++){
		res.tab[res.nbTask]=tasktab.tab[j];
		res.nbTask++;
	}
	free(tasktab.tab);
	//double cpt=completionFF(tasktab);
	//printf("%f\n",cpt );
	//afficheTab(res);
	//freeChaine(liste);
	//freeChaine(place);
	freeChaine(periode[0]);
	freeChaine(periode[1]);
	return res;
}
/*
int main(int argc,char** argv){
	if(argc!=4)return 0;
	TaskTab tasktab=lireData(argv[1],atoi(argv[3]));
	if(completionFF(algoLourd(tasktab,atoi(argv[2]),atoi(argv[3])))==100)printf("1");
	else printf("0");
	free(tasktab.tab);
	return 0;
}*/