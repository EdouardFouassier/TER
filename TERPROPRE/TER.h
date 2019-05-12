#ifndef TER
#define TER

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoLourd.h"
#include "algoSuperLourd.h"
#include "FirstFit.h"
#include "gen.h"
#include "bibli.h"
#include "algoYannou.h"


#include<omp.h>



void nomF(int i,char nom[]);
stats multi(int algo,int nb,int periode,int nbTask,TaskTab tasktab[nb]);

#endif
