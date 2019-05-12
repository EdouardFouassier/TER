#ifndef BIBLI
#define BIBLI
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct task{
	int num;
	int delay;
	int cycle[2];
	int place;
}task;

typedef struct chaine{
	task* t;
	struct chaine* next;
}chaine;

typedef struct TaskTab{
	task* tab;
	int nbTask;
}TaskTab;

typedef struct stats{
	double tauxCompletion;
	double tauxReussite;
	double tauxMin;
	double tauxMax;
}stats;

typedef struct periode{
	struct periode* next;
	int begin;
	int end; // exclut
}Periode;

void copyPeriode(Periode* periode[2],Periode* periodecpy[2]);
Periode* initPeriode(int begin,int end,Periode* next);
Periode* coupePeriode(Periode* periode,int milieu,int cycle,int taille);
int verifPeriode(Periode* periode,int milieu,int cycle,int taille);
void affichePeriode(Periode* periode);
TaskTab lireData(char* nom,int nbTask);
void freeChaine(Periode* liste);
void afficheTab(TaskTab tasktab);
double completionFF(TaskTab tasktab);
int verifInter(Periode* periode[2],int milieu,int cycle,int delay,int taille);
TaskTab initData(int nbTask,int cycle,int periode);
TaskTab resetData(TaskTab tasktab);


#endif