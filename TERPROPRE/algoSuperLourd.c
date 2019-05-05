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
    periode[0]=initPeriode(0,periodeMax-1,NULL);
	periode[1]=initPeriode(0,periodeMax-1,NULL);

    int cptAvant[tasktab.nbTask];
    int gene[tasktab.nbTask];

    for (int k = 0; k<tasktab.nbTask /*|| plus de tache*/; k++) {
        //printf("%d\n",k);
        int min = 0;
        int genemin=periodeMax*tasktab.nbTask+1;
        cptplace(tasktab, periodeMax, periode, cptAvant);
        Periode* newPeriode[2];
         int cptApres[tasktab.nbTask];
         int j,i;
        //#pragma omp parallel for private(i,j,newPeriode,cptApres)
        for (j = 0; j<tasktab.nbTask; j++) {
            gene[j]=0;
            if (tasktab.tab[j].place == -1) {
                copyPeriode(periode, newPeriode);
                for (i = 0; i<periodeMax; i++) {
                    if(verifPeriode(newPeriode[0],i,tasktab.tab[j].cycle[0],periodeMax-1) && verifPeriode(newPeriode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1)) {
                        newPeriode[0]=coupePeriode(newPeriode[0],i,tasktab.tab[j].cycle[0],periodeMax-1);
                        newPeriode[1]=coupePeriode(newPeriode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1);
                        i=periodeMax;
                    }
		        }

               
                cptplace(tasktab, periodeMax, newPeriode, cptApres);

                for (int i = 0; i < tasktab.nbTask; i++) {
                    gene[j] += cptAvant[i] - cptApres[i];
                }

                if (genemin > gene[j]){
                    min = j; 
                    genemin=gene[j];
                } 
                free(newPeriode[0]);
                free(newPeriode[1]);
                //printf("tache %d gene %d gene min %d min %d\n",j,gene[j],gene[min],min);
            }           
        }

        for (int i = 0; i<periodeMax; i++) {
            if(verifPeriode(periode[0],i,tasktab.tab[min].cycle[0],periodeMax-1) && verifPeriode(periode[1],(i+tasktab.tab[min].delay)%periodeMax,tasktab.tab[min].cycle[1],periodeMax-1)) {
                periode[0]=coupePeriode(periode[0],i,tasktab.tab[min].cycle[0],periodeMax-1);
                periode[1]=coupePeriode(periode[1],(i+tasktab.tab[min].delay)%periodeMax,tasktab.tab[min].cycle[1],periodeMax-1);
                tasktab.tab[min].place=i;
                i=periodeMax;
            }
		}
        if(tasktab.tab[min].place==-1)tasktab.tab[min].place=-2;

        gene[min] = periodeMax*tasktab.nbTask;

        
    }
   // for (int k = 0; k<tasktab.nbTask; k++) if(tasktab.tab[k].place==-2)tasktab.tab[k].place=-1;
    return tasktab;
}
/*
int main(int argc,char** argv){
    char* nom;
    nom=malloc(sizeof(char)*8);
    sprintf(nom,"data/in%d",0);
	TaskTab tasktab = lireData(nom, 50);
    free(nom);
    double completion=completionFF(algoSuperLourd(tasktab,50000));
    afficheTab(tasktab);
    printf("%f\n",completion);
	free(tasktab.tab);
	return 0;
}
*/