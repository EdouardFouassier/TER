#include "bibli.c"

int main(int argc,char** argv){
	Periode* periode=initPeriode(0,9,NULL);
	int val;
	/*TaskTab* tasktabp=malloc(sizeof(TaskTab));
	TaskTab tasktab= lireData("data/in0",10);
	tasktabp=&tasktab;
	printf("%d %d",tasktab.tab[0].delay,tasktabp->tab[0].delay);*/
	while(1){
		affichePeriode(periode);
		printf("\n");
		scanf("%d",&val);
		printf("%d\n",verifPeriode(periode,val,1,9));
		periode=coupePeriode(periode,val,1,9);
	}
	return 0;
}	 