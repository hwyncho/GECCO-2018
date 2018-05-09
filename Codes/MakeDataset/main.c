/*
 * Created by 조휘연 on 2018. 01. 05.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GECCO-2018
 * e-mail : hwyn.cho@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>

#include "libGA/GA.h"
#include "NK.h"

#define MAX_BUF_SIZE 1024
#define SEED 777

#define N CHROMOSOME_SIZE
#define K 4
#define GENERATION_SIZE 10000

#define DATASET_PATH "Dataset.arff"
#define DATASET_SIZE 10000

#define ARFF_HEADER "@RELATION ga\n@ATTRIBUTE POPULATION_SIZE NUMERIC\n@ATTRIBUTE SELECTION {0,1,2,3}\n@ATTRIBUTE CROSSOVER {0,1,2,3,4,5}\n@ATTRIBUTE MUTATION_RATE NUMERIC\n@ATTRIBUTE REPLACEMENT {0,1,2,3}\n@ATTRIBUTE BEST_FITNESS NUMERIC\n@DATA\n"

int main(int argc, char *argv[]) {
    int i = 0;

    char buf[MAX_BUF_SIZE] = {0,};
    FILE *fp = NULL;

    size_t populationSize = 0;
    int opSelection = 0;
    int opCrossover = 0;
    int mutationRate = 0;
    int opReplacement = 0;

    ga *myGA = NULL;
    chromosome *bestChromosome = NULL;

    selectionArgs args1 = {0,};
    crossoverArgs args2 = {0,};
    mutationArgs args3 = {0,};

    srand(SEED);

    fp = fopen(DATASET_PATH, "w");
    fputs(ARFF_HEADER, fp);
    fclose(fp);


    // define fitness function
    initNkTable(N, K);
    calcFitness = nk;
    
    for (i = 0; i < DATASET_SIZE; ++i) {
        populationSize = (size_t) (rand() % 4991 + 10);
        opSelection = rand() % 4;
        opCrossover = rand() % 6;
        mutationRate = rand() % 251;
        opReplacement = rand() % 4;

        // initialize GA
        myGA = initGA(populationSize);

        switch (opSelection) {
            case 0:
                myGA->selection = SELECTION->rouletteWheel;
                break;
            case 1:
                myGA->selection = SELECTION->scaledRouletteWheel;
                args1.scale = 3;
                break;
            case 2:
                myGA->selection = SELECTION->rankBased;
                break;
            case 3:
                myGA->selection = SELECTION->tournament;
                args1.k = 0.5;
                break;
            default:
                break;
        }

        switch (opCrossover) {
            case 0:
                myGA->crossover = CROSSOVER->uniform;
                args2.p = 0.5;
                break;
            case 1:
                myGA->crossover = CROSSOVER->onePoint;
                break;
            case 2:
                myGA->crossover = CROSSOVER->multiPoint;
                args2.n = 2;
                break;
            case 3:
                myGA->crossover = CROSSOVER->multiPoint;
                args2.n = 3;
                break;
            case 4:
                myGA->crossover = CROSSOVER->multiPoint;
                args2.n = 4;
                break;
            case 5:
                myGA->crossover = CROSSOVER->multiPoint;
                args2.n = 5;
                break;
            default:
                break;
        }

        myGA->mutation = MUTATION->onePointFlip;
        args3.rate = (float) (mutationRate / 1000.0);

        switch (opReplacement) {
            case 0:
                myGA->replacement = REPLACEMENT->worstReplace;
                break;
            case 1:
                myGA->replacement = REPLACEMENT->similarReplace;
                break;
            case 2:
                myGA->replacement = REPLACEMENT->worstParentReplace;
                break;
            case 3:
                myGA->replacement = REPLACEMENT->similarParentReplace;
                break;
            default:
                break;
        }

        // run GA
        bestChromosome = runGA(myGA, GENERATION_SIZE, args1, args2, args3);

        sprintf(buf, "%ld,%d,%d,%d,%d,%.3f\n", populationSize, opSelection, opCrossover, mutationRate, opReplacement, bestChromosome->fitness);

        fp = fopen(DATASET_PATH, "a");
        fputs(buf, fp);
        fclose(fp);

        // finalize GA
        freeGA(myGA);
    }

    freeNkTable();

    return 0;
}
