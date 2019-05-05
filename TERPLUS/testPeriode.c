#include "bibli.h"

int main(int argc,char** argv){
	Periode* periode[2];
	Periode* periodecpy[2];
	periode[0]=initPeriode(0,19,NULL);
	periode[1]=initPeriode(0,19,NULL);
	int val,delay;
	/*TaskTab* tasktabp=malloc(sizeof(TaskTab));
	TaskTab tasktab= lireData("data/in0",10);
	tasktabp=&tasktab;
	printf("%d %d",tasktab.tab[0].delay,tasktabp->tab[0].delay);*/
		copyPeriode(periode,periodecpy);
		affichePeriode(periode[0]);
		affichePeriode(periode[1]);
		affichePeriode(periodecpy[0]);
		affichePeriode(periodecpy[1]);
		freeChaine(periodecpy[0]);
		freeChaine(periodecpy[1]);
		printf("\n");
		
		periode[0]=coupePeriode(periode[0],4,3,19);
		periode[1]=coupePeriode(periode[1],6,3,19);
		copyPeriode(periode,periodecpy);
		affichePeriode(periode[0]);
		affichePeriode(periode[1]);

		affichePeriode(periodecpy[0]);
		affichePeriode(periodecpy[1]);

		freeChaine(periodecpy[0]);
		freeChaine(periodecpy[1]);
		printf("\n");
		periode[0]=coupePeriode(periode[0],9,3,19);
		periode[1]=coupePeriode(periode[1],17,3,19);
		copyPeriode(periode,periodecpy);
			affichePeriode(periode[0]);
		affichePeriode(periode[1]);

		affichePeriode(periodecpy[0]);
		affichePeriode(periodecpy[1]);

		freeChaine(periodecpy[0]);
		freeChaine(periodecpy[1]);
		printf("\n");
		periode[0]=coupePeriode(periode[0],14,3,19);
		periode[1]=coupePeriode(periode[1],14,3,19);
		copyPeriode(periode,periodecpy);

	while(1){
		affichePeriode(periode[0]);
		affichePeriode(periode[1]);

		affichePeriode(periodecpy[0]);
		affichePeriode(periodecpy[1]);

		freeChaine(periodecpy[0]);
		freeChaine(periodecpy[1]);
		printf("\n");
		scanf("%d %d",&val,&delay);
		periode[0]=coupePeriode(periode[0],val,3,19);
		periode[1]=coupePeriode(periode[1],(val+delay)%20,3,19);
		copyPeriode(periode,periodecpy);
	}
	return 0;
}	 