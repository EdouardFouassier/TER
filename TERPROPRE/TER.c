#include "TER.h"
#include <omp.h>
int cptavcmt=0;
int cptavcmtAL=0;
int cptavcmtFF=0;
int cptavcmtAY=0;
int cptavcmtASL=0;
int maxTask=0;
stats multi(int algo,int nb,int periode,int nbTask,TaskTab taskta[nb]){
	//printf("algo %d\n",algo);
	double cpt=0;
	double val=0;
	int i=0;
	int sum=0;
	double min=100;
	double max=0;
	//afficheTab(tasktab);
	#pragma omp parallel for private (val)
	for(i=0;i<nb;i++){
		
		TaskTab tasktab=resetData(taskta[i]);
		if(i==0 )afficheTab(tasktab);
		if(algo==0)val=completionFF(FirstFit(tasktab,periode,nbTask));
		if(algo==1)val=completionFF(algoLourd(tasktab,periode,nbTask));
		if(algo==2)val=completionFF(algoSuperLourd(tasktab,periode));
		if(algo==3)val=completionFF(algoPasilourd(tasktab,periode,nbTask));
		
		//printf("chexk\n");
		if(val==100)cpt++;
		if(val<min)min=val;
		if(val>max)max=val;
		sum+=val;
		//printf("%f\n",val);
		//free(tasktab.tab);
	//	printf("2 %d %d \n",nbTask,i);
		cptavcmt++;
		if(algo==0)cptavcmtFF++;
		if(algo==1)cptavcmtAL++;
		if(algo==2)cptavcmtASL++;
		if(algo==3)cptavcmtAY++;
		printf("Total:%d/%d FF:%d/%d AL:%d/%d ASL:%d/%d AY:%d/%d\n",cptavcmt,nb*4*maxTask,cptavcmtFF,nb*maxTask,cptavcmtAL,nb*maxTask,cptavcmtASL,nb*maxTask,cptavcmtAY,nb*maxTask);
		free(tasktab.tab);
	}
	stats s;
	s.tauxReussite=((cpt*1.0)/(nb*1.0))*100;
	s.tauxCompletion=(sum/nb);
	s.tauxMin=min;
	s.tauxMax=max;
	//printf("fin multi %d\n",algo);
	return s;
}

int main(int argc,char** argv){
	//affichePeriode(periodes[0]);
//	printf("\n");
	float temps1=0,temps2=0,temps3=0,temps4=0,moyenne1=0,moyenne2=0,moyenne3=0,moyenne4=0,acc1,acc2,acc3,amelio1,amelio2,amelio3,eff1,eff2,eff3;
    clock_t t1, t2;
    srand(time(NULL));
	int periode=atoi(argv[1]),cycle=atoi(argv[3]),nb=atoi(argv[4]),nbTask=atoi(argv[2]);
	TaskTab tasktab[nb];
	 maxTask=(periode/cycle)/5;
    float temps[4][maxTask];
	double taux[4][maxTask];
	double completion[4][maxTask];
	double min[4][maxTask];
	double max[4][maxTask];
	int i=1;
	stats s;
	int cpt=0;
	int aff=1;

	//#pragma omp parallel for private(i)
	for(i=1;i<=maxTask;i++){
		for(int j=0;j<nb;j++)tasktab[j]=initData(i*5,cycle,periode);
		//afficheTab(tasktab[i-1]);
		//if(aff)printf("check 1 %d\n",i);
		t1 = clock();
		//if(aff)printf("check 2\n");
		s=multi(0,nb,periode,i*5,tasktab);
		//if(aff)printf("check 3\n");
		taux[0][i-1]=s.tauxReussite;
		//if(aff)printf("check 4\n");
		completion[0][i-1]=s.tauxCompletion;
		min[0][i-1]=s.tauxMin;
		max[0][i-1]=s.tauxMax;
		//if(aff)printf("check 5\n");
		moyenne1+=taux[0][i-1];
		//if(aff)printf("check 6\n");
		t2 = clock();
		//if(aff)printf("check 7\n");
		temps[0][i-1]=((float)(t2-t1)/CLOCKS_PER_SEC)/nb;
		//if(aff)printf("check 8\n");
		temps1 +=temps[0][i-1];
		//if(aff)printf("check 9\n");
		s=multi(1,nb,periode,i*5,tasktab);
		//if(aff)printf("check 10\n");
		taux[1][i-1]=s.tauxReussite;
		//if(aff)printf("check 11\n");
		completion[1][i-1]=s.tauxCompletion;
		min[1][i-1]=s.tauxMin;
		max[1][i-1]=s.tauxMax;
		//if(aff)printf("check 12\n");
		moyenne2+=taux[1][i-1];
		//if(aff)printf("check 13\n");
		t1 = clock();
		//if(aff)printf("check 14\n");
		temps[1][i-1]=((float)(t1-t2)/CLOCKS_PER_SEC)/nb;
		//if(aff)printf("check 15\n");
		temps2 +=temps[1][i-1];
		//if(aff)printf("check 16\n");
		s=multi(2,nb,periode,i*5,tasktab);
		//if(aff)printf("check 17\n");
		taux[2][i-1]=s.tauxReussite;
		//if(aff)printf("check 18\n");
		completion[2][i-1]=s.tauxCompletion;
		min[2][i-1]=s.tauxMin;
		max[2][i-1]=s.tauxMax;
		//if(aff)printf("check 19\n");
		moyenne3+=taux[2][i-1];
		//if(aff)printf("check 20\n");
		t2 = clock();
		//if(aff)printf("check 21\n");
		temps[2][i-1]=((float)(t2-t1)/CLOCKS_PER_SEC)/nb;
		//if(aff)printf("check 22\n");
		temps3 +=temps[2][i-1];

		s=multi(3,nb,periode,i*5,tasktab);
		//if(aff)printf("check 17\n");
		taux[3][i-1]=s.tauxReussite;
		//if(aff)printf("check 18\n");
		completion[3][i-1]=s.tauxCompletion;
		min[3][i-1]=s.tauxMin;
		max[3][i-1]=s.tauxMax;
		//if(aff)printf("check 19\n");
		moyenne4+=taux[2][i-1];
		//if(aff)printf("check 20\n");
		t1 = clock();
		//if(aff)printf("check 21\n");
		temps[3][i-1]=((float)(t1-t2)/CLOCKS_PER_SEC)/nb;
		//if(aff)printf("check 22\n");
		temps4 +=temps[3][i-1];
		for(int j=0;j<nb;j++)free(tasktab[j].tab);
	}
	
	
	FILE* statout=fopen("stat.data","w");
	FILE* statout2=fopen("stat2.data","w");
	FILE* statout3=fopen("stat3.data","w");
	

	for(int i=0;i<maxTask;i++){
		fprintf(statout,"%d	%f 	%f  %f  %f \n",(i+1)*10,taux[0][i],taux[1][i], taux[2][i],taux[3][i]);
		fprintf(statout2,"%d %f  %f  %f %f  %f  %f %f  %f  %f %f  %f  %f \n",(i+1)*10,completion[0][i],completion[1][i], completion[2][i],completion[3][i],min[0][i],min[1][i], min[2][i],min[3][i],max[0][i],max[1][i], max[2][i],max[3][i]);
		fprintf(statout3,"%d %f  %f  %f %f \n",(i+1)*10,temps[0][i],temps[1][i], temps[2][i],temps[3][i]);
	}
	fclose(statout);
	fclose(statout2);
	fclose(statout3);
   	temps1=temps1/maxTask;
   	temps2=temps2/maxTask;
   	temps3=temps3/maxTask;
   	temps4=temps4/maxTask;
   	moyenne1=moyenne1/maxTask;
   	moyenne2=moyenne2/maxTask;
   	moyenne3=moyenne3/maxTask;
   	moyenne4=moyenne4/maxTask;
   	acc1=(temps2/temps1);	
   	acc2=(temps3/temps1);	
   	acc3=(temps4/temps1);	
   	amelio1=(moyenne2/moyenne1);
   	amelio2=(moyenne3/moyenne1);
   	amelio3=(moyenne4/moyenne1);
   	eff1=amelio1/acc1;
   	eff2=amelio2/acc2;
   	eff3=amelio3/acc3;
    printf("\
    	temps FirstFit= %f \n temps algoLourd= %f \n temps algoSuperLourd= %f \n temps algoYannou= %f \n\
     	acceleration algoLourd= %f \n acceleration algoSuperLourd= %f \n acceleration algoYannou= %f \n\
      	reussite FirstFit= %f \n reussite algoLourd=%f \n reussite algoSuperLourd=%f \n reussite algoYannou=%f \n\
       	amelioration algoLourd= %f \n amelioration algoSuperLourd= %f \n amelioration algoYannou= %f \n \
       	Efficacité algoLourd= %f \n Efficacité algoSuperLourd= %f \n Efficacité algoYannou= %f \n"
       , temps1,temps2,temps3,temps4
       ,acc1,acc2,acc3
       ,moyenne1,moyenne2,moyenne3,moyenne4
       ,amelio1,amelio2,amelio3
       ,eff1,eff2,eff3
       );
	/*
	float temps;
    clock_t t1, t2;

    t1 = clock();
    printf("FF %f\n",multi(0,nb,periode,nbTask));
	t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);

    t1 = clock();
    printf("AL %f\n",multi(1,nb,periode,nbTask));
  	t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);*/

}