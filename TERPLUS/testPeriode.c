#include "bibli.h"

int main(int argc,char** argv){
	Periode* periode[2];
	periode[0]=initPeriode(0,19,NULL);
	periode[1]=initPeriode(0,19,NULL);
	int val,delay;
	/*TaskTab* tasktabp=malloc(sizeof(TaskTab));
	TaskTab tasktab= lireData("data/in0",10);
	tasktabp=&tasktab;
	printf("%d %d",tasktab.tab[0].delay,tasktabp->tab[0].delay);*/
		affichePeriode(periode[0]);
		affichePeriode(periode[1]);
		printf("\n");
		
		periode[0]=coupePeriode(periode[0],4,3,19);
		periode[1]=coupePeriode(periode[1],6,3,19);

			affichePeriode(periode[0]);
		affichePeriode(periode[1]);
		printf("\n");
		periode[0]=coupePeriode(periode[0],9,3,19);
		periode[1]=coupePeriode(periode[1],17,3,19);

			affichePeriode(periode[0]);
		affichePeriode(periode[1]);
		printf("\n");
		periode[0]=coupePeriode(periode[0],14,3,19);
		periode[1]=coupePeriode(periode[1],14,3,19);


	while(1){
			affichePeriode(periode[0]);
		affichePeriode(periode[1]);
		printf("\n");
		scanf("%d %d",&val,&delay);
		printf("%d\n",verifInter(periode,val,3,delay,19));
	}
	return 0;
}	 