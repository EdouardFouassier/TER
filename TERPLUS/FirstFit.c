
#include "bibli.c"

double FirstFit(TaskTab tasktab,int periodeMax,int nbTask){
	Periode* periode[2];
	int val;
	periode[0]=initPeriode(0,periodeMax-1,NULL);
	periode[1]=initPeriode(0,periodeMax-1,NULL);
	for(int j=0;j<tasktab.nbTask;j++){
	//	printf("j=%d\n",j);
		for(int i=0;i<periodeMax;i++){
		//	affichePeriode(periode[0]);

	//printf("\n");
		//	affichePeriode(periode[1]);
			//printf("i=%d\n",i);
			if(periode[0]==NULL || periode[1]==NULL){i=periodeMax;j=tasktab.nbTask;}
			else if(verifPeriode(periode[0],i,tasktab.tab[j].cycle[0],periodeMax-1) && verifPeriode(periode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1)) {
				//printf("coupe1\n");
				periode[0]=coupePeriode(periode[0],i,tasktab.tab[j].cycle[0],periodeMax-1);
				//printf("coupe2\n");
				periode[1]=coupePeriode(periode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1);
				//printf("coupe3\n");
				tasktab.tab[j].place=i;
				i=periodeMax;
			}
		}
		//scanf("%d",&val);
	}
	freeChaine(periode[0]);
	freeChaine(periode[1]);
	double cpt=completionFF(tasktab);
	//printf("%f\n",cpt );
	//afficheTab(tasktab);
	//freeChaine(liste);
	//freeChaine(place);
	return cpt;
}

int main(int argc,char** argv){
	if(argc!=3)return 0;
	TaskTab tasktab=lireData(argv[1],atoi(argv[2]));
	if(FirstFit(tasktab,1000,atoi(argv[2]))==100)printf("1");
	else printf("0");
	free(tasktab.tab);
	return 0;
}