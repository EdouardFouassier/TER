#include "bibli.c"

int main(int argc,char** argv){
	Periode* periode=initPeriode(0,19,NULL);
	int val;
	while(1){
		affichePeriode(periode);
		printf("\n");
		scanf("%d",&val);
		periode=coupePeriode(periode,val,3,19);
	}
	return 0;
}