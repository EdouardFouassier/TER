#include "algoSuperLourd.h"

void cptplace(TaskTab tasktab,int periodeMax, Periode* periode[2], int cpt[tasktab.nbTask]) {

    for (int i=0; i<tasktab.nbTask; i++) {
        cpt[i] = 0;
        for (int j = 0; j<periodeMax; j++) {
            if(verifPeriode(periode[0],j,tasktab.tab[i].cycle[0],periodeMax-1) && verifPeriode(periode[1],(j+tasktab.tab[i].delay)%periodeMax,tasktab.tab[i].cycle[1],periodeMax-1)){
                cpt[i]++;
            }
        }
    }
}

TaskTab algoSuperLourd(TaskTab tasktab,int periodeMax) {
    Periode* periode[2];
    int aff=0;
    periode[0]=initPeriode(0,periodeMax-1,NULL);
	periode[1]=initPeriode(0,periodeMax-1,NULL);

    int cptAvant[tasktab.nbTask];
    int gene[tasktab.nbTask];

    for (int k = 0; k<tasktab.nbTask /*|| plus de tache*/; k++) {
       // printf("%d\n",k);
        //if(aff)printf("check1\n");
        int min = 0;
        int genemin=periodeMax*tasktab.nbTask+1;
        cptplace(tasktab, periodeMax, periode, cptAvant);
        Periode* newPeriode[2];
         int cptApres[tasktab.nbTask];
         int j,i;
        //if(aff)printf("check2\n");
        //#pragma omp parallel for private(i,j,newPeriode,cptApres)
        for (j = 0; j<tasktab.nbTask; j++) {
        //if(aff)printf("check2.1\n");
            gene[j]=0;
       //if(aff) printf("check2.2\n");
            if (tasktab.tab[j].place == -1) {
        //if(aff)printf("check2.3\n");
                copyPeriode(periode, newPeriode);
        //if(aff)printf("check2.4\n");
                for (i = 0; i<periodeMax; i++) {
        //if(aff)printf("check3\n");
                    if(verifPeriode(newPeriode[0],i,tasktab.tab[j].cycle[0],periodeMax-1) && verifPeriode(newPeriode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1)) {
                        
        //if(aff)printf("check3.1\n");

                        newPeriode[0]=coupePeriode(newPeriode[0],i,tasktab.tab[j].cycle[0],periodeMax-1);
                        
        //if(aff)printf("check3.2\n");
                        newPeriode[1]=coupePeriode(newPeriode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1);
                        
        //if(aff)printf("check3.3\n");
                        i=periodeMax;
                    }

        //if(aff)printf("check3.4\n");
		        }

                cptplace(tasktab, periodeMax, newPeriode, cptApres);

                for (int i = 0; i < tasktab.nbTask; i++) {
                    gene[j] += cptAvant[i] - cptApres[i];
                }
        //if(aff)printf("check5\n");

                if (genemin > gene[j]){
                    min = j; 
                    genemin=gene[j];
                } 
        //if(aff)printf("check6\n");
                free(newPeriode[0]);
                free(newPeriode[1]);
                //printf("tache %d gene %d gene min %d min %d\n",j,gene[j],gene[min],min);
            }           
        }

        //if(aff)printf("chec7k\n");
        for (int i = 0; i<periodeMax; i++) {
            if(verifPeriode(periode[0],i,tasktab.tab[min].cycle[0],periodeMax-1) && verifPeriode(periode[1],(i+tasktab.tab[min].delay)%periodeMax,tasktab.tab[min].cycle[1],periodeMax-1)) {
                periode[0]=coupePeriode(periode[0],i,tasktab.tab[min].cycle[0],periodeMax-1);
                periode[1]=coupePeriode(periode[1],(i+tasktab.tab[min].delay)%periodeMax,tasktab.tab[min].cycle[1],periodeMax-1);
                tasktab.tab[min].place=i;
                i=periodeMax;
            }
        //if(aff)printf("check8\n");
		}
        //if(aff)printf("check9\n");
        if(tasktab.tab[min].place==-1)tasktab.tab[min].place=-2;

        //if(aff)printf("check10\n");
        gene[min] = periodeMax*tasktab.nbTask;

        
    }
   // for (int k = 0; k<tasktab.nbTask; k++) if(tasktab.tab[k].place==-2)tasktab.tab[k].place=-1;
    return tasktab;
}
/*
int main(int argc,char** argv){
     clock_t t1, t2;
     float temps;
    TaskTab tasktab = lireData("data/in0", 20);
    t1 = clock();
    double completion=completionFF(algoSuperLourd(tasktab,50000));
    t2 = clock();
    temps += (float)(t2-t1)/CLOCKS_PER_SEC;
    afficheTab(tasktab);
    printf("%f %f\n",completion,temps);
    free(tasktab.tab);
    return 0;
}
*/