/*
 * Created by 조휘연 on 2018. 01. 05.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GECCO-2018
 * e-mail : hwyn.cho@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libGA/GA.h"

#define MAX_BUF_SIZE 2048
#define SEED 777

#define GENERATION_SIZE 20000
#define POPULATION_SIZE 1000
#define OPTIMAL_SIZE 100

#define MODEL_PATH "SMOreg.model"
#define OPTIMAL_PATH "Optimal.arff"
#define WEKA_INPUT_PATH "WekaInput.arff"
#define WEKA_OUTPUT_PATH "WekaOutput.txt"

#define JAVA_PATH "java"
#define WEKA_PATH "weka.jar"

#define DELIMITER " "
#define ARFF_HEADER "@RELATION ga\n@ATTRIBUTE POPULATION_SIZE NUMERIC\n@ATTRIBUTE SELECTION {0,1,2,3}\n@ATTRIBUTE CROSSOVER {0,1,2,3,4,5}\n@ATTRIBUTE MUTATION_RATE NUMERIC\n@ATTRIBUTE REPLACEMENT {0,1,2,3}\n@ATTRIBUTE BEST_FITNESS NUMERIC\n@DATA\n"

float SMOreg(chromosome *individual);

int main(int argc, char *argv[]) {
    int i = 0;

    char buf[MAX_BUF_SIZE] = {0,};
    FILE *fp = NULL;

    ga *myGA = NULL;
    chromosome *bestChromosome = NULL;

    selectionArgs args1 = {0,};
    crossoverArgs args2 = {0,};
    mutationArgs args3 = {0,};

    // define fitness function
    calcFitness = SMOreg;

    args2.p = 0.5;
    args3.rate = 0.05;

    srand(SEED);

    fp = fopen(OPTIMAL_PATH, "w");
    fputs(ARFF_HEADER, fp);
    fclose(fp);
    
    for (i = 0; i < OPTIMAL_SIZE; ++i) {
        // initialize GA
        myGA = initGA(POPULATION_SIZE);

        myGA->selection = SELECTION->rankBased;
        myGA->crossover = CROSSOVER->uniform;
        myGA->mutation = MUTATION->onePointFlip;
        myGA->replacement = REPLACEMENT->worstReplace;

        // run GA
        bestChromosome = runGA(myGA, GENERATION_SIZE, args1, args2, args3);

        fp = fopen(OPTIMAL_PATH, "a");
        sprintf(buf, "%d,%d,%d,%d,%d,%.3f\n",
                bestChromosome->genes[0], bestChromosome->genes[1],
                bestChromosome->genes[2], bestChromosome->genes[3],
                bestChromosome->genes[4], bestChromosome->fitness);
        fputs(buf, fp);
        fclose(fp);

        // finalize GA
        freeGA(myGA);
    }

    return 0;
}

float SMOreg(chromosome *individual) {
    int i = 0;

    char buf[1024] = {0,};
    FILE *fpInput = NULL;
    
    char line[1024] = {0,};
    char *tok = NULL;
    char *params[4] = {0,};
    FILE *fpOutput = NULL;

    float fitness = 0.0;

    sprintf(buf, "%s%d,%d,%d,%d,%d,?\n",
            ARFF_HEADER, individual->genes[0],
            individual->genes[1], individual->genes[2],
            individual->genes[3], individual->genes[4]);

    fpInput = fopen(WEKA_INPUT_PATH, "w");
    fputs(buf, fpInput);
    fclose(fpInput);

    sprintf(buf, "%s -cp %s weka.classifiers.functions.SMOreg -l %s -T %s -p 0 > %s",
            JAVA_PATH, WEKA_PATH, MODEL_PATH, WEKA_INPUT_PATH, WEKA_OUTPUT_PATH);
    system(buf);

    // parse WEKA Result
    fpOutput = fopen(WEKA_OUTPUT_PATH, "r");
    fgets(line, sizeof(line), fpOutput);
    tok = strstr(line, "1");
    
    while (tok == NULL) {
        fgets(line, sizeof(line), fpOutput);
        tok = strstr(line, "1");
    }

    i = 0;
    tok = NULL;

    tok = strtok(line, DELIMITER);
    while (tok != NULL) {
        params[i] = tok;
        tok = strtok(NULL, " ");
        ++i;
    }

    fitness = strtof(params[2], NULL);

    fclose(fpOutput);

    return fitness;
}
