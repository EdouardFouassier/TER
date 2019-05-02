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

        cptplace(tasktab, periodeMax, periode, cptAvant);
        Periode* newPeriode[2];
        copyPeriode(periode, newPeriode);

        for (int j = 0; j<tasktab.nbTask; j++) {

            if (tasktab.tab[j].place == -1) {
                for (int i = 0; i<periodeMax; i++) {
                    if(verifPeriode(newPeriode[0],i,tasktab.tab[j].cycle[0],periodeMax-1) && verifPeriode(newPeriode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1)) {
                        newPeriode[0]=coupePeriode(newPeriode[0],i,tasktab.tab[j].cycle[0],periodeMax-1);
                        newPeriode[1]=coupePeriode(newPeriode[1],(i+tasktab.tab[j].delay)%periodeMax,tasktab.tab[j].cycle[1],periodeMax-1);
                        i=periodeMax;
                    }
		        }

                int cptApres[tasktab.nbTask];
                cptplace(tasktab, periodeMax, newPeriode, cptApres);

                for (int i = 0; i < tasktab.nbTask; i++) {
                    gene[j] += cptAvant[i] - cptApres[i];
                }

                if (gene[min] > gene[j]) min = j; 
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

        gene[min] = periodeMax;

        free(newPeriode[0]);
        free(newPeriode[1]);
    }

    return tasktab;
}

/*int main(int argc,char** argv){
    printf("Tes morts\n");
    char* nom;
    nom=malloc(sizeof(char)*8);
    sprintf(nom,"data/in%d",0);
    printf("Truc %s\n",nom);
	TaskTab tasktab = lireData(nom, 35);
    free(nom);
    algoLourd(tasktab,50000);
    afficheTab(tasktab);
	free(tasktab.tab);
	return 0;
}*/
