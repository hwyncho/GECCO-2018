/*
 * Created by 조휘연 on 2018. 01. 08.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GeneticAlgorithm
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing functions related to crossover operator.
 */

#include <stdlib.h>
#include <string.h>
#include "./Crossover.h"

// function to implement one point crossover
chromosome *onePoint(chromosome **parents, crossoverArgs args) {
    int i = 0;

    int point = 0;
    char *tempGenes = NULL;
    chromosome *child = NULL;

    point = rand() % CHROMOSOME_SIZE;
    tempGenes = (char *) calloc(CHROMOSOME_SIZE + 1, sizeof(char));
    child = initChromosome();

    for (i = 0; i < CHROMOSOME_SIZE; ++i) {
        tempGenes[i] = (i <= point) ? (parents[0]->genes[i]) : (parents[1]->genes[i]);
    }

    strncpy(child->genes, tempGenes, CHROMOSOME_SIZE);
    child->fitness = calcFitness(child);

    SAFE_FREE(tempGenes);

    return child;
}

// function to implement n point crossover
chromosome *multiPoint(chromosome **parents, crossoverArgs args) {
    int i = 0;
    int j = 0;

    int *points = NULL;
    char *tempGenes = NULL;
    chromosome *child = NULL;

    points = (int *) calloc(args.n, sizeof(int));
    tempGenes = (char *) calloc(CHROMOSOME_SIZE + 1, sizeof(char));
    child = initChromosome();

    for (i = 1; i <= args.n; ++i) {
        points[i - 1] = rand() % (CHROMOSOME_SIZE / args.n) + (CHROMOSOME_SIZE * (i - 1) / args.n);
    }

    for (i = 0; i < CHROMOSOME_SIZE; ++i) {
        if (j % 2 == 0) {
            if (i < points[j]) {
                tempGenes[i] = parents[0]->genes[i];
            } else if (i == points[j]) {
                tempGenes[i] = parents[0]->genes[i];
                ++j;
            } else {
                tempGenes[i] = parents[1]->genes[i];
            }
        } else {
            if (i < points[j]) {
                tempGenes[i] = parents[1]->genes[i];
            } else if (i == points[j]) {
                tempGenes[i] = parents[1]->genes[i];
                ++j;
            } else {
                tempGenes[i] = parents[0]->genes[i];
            }
        }
    }

    strncpy(child->genes, tempGenes, CHROMOSOME_SIZE);
    child->fitness = calcFitness(child);

    SAFE_FREE(tempGenes);
    SAFE_FREE(points);

    return child;
}

// function to implement uniform crossover
chromosome *uniform(chromosome **parents, crossoverArgs args) {
    int i = 0;

    float *randoms = NULL;
    char *tempGenes = NULL;
    chromosome *child = NULL;

    randoms = (float *) calloc(CHROMOSOME_SIZE, sizeof(float));
    tempGenes = (char *) calloc(CHROMOSOME_SIZE + 1, sizeof(char));
    child = initChromosome();

    // generate a random number between 0 and 1 for each gene location
    for (i = 0; i < CHROMOSOME_SIZE; ++i) {
        randoms[i] = (float) (rand() % 1001 / 1000.0);
    }

    // if random is smaller than p, select gene of parent2
    // else random is bigger than p, select gene of parent1
    for (i = 0; i < CHROMOSOME_SIZE; ++i) {
        tempGenes[i] = (randoms[i] <= args.p) ? (parents[1]->genes[i]) : (parents[0]->genes[i]);
    }

    strncpy(child->genes, tempGenes, CHROMOSOME_SIZE);
    child->fitness = calcFitness(child);

    SAFE_FREE(tempGenes);
    SAFE_FREE(randoms);

    return child;
}

// function to implement arithmetic crossover
chromosome *arithmetic(chromosome **parents, crossoverArgs args) {
    int i = 0;

    char *tempGenes = NULL;
    chromosome *child = NULL;

    tempGenes = (char *) calloc(CHROMOSOME_SIZE + 1, sizeof(char));
    child = initChromosome();

    for (i = 0; i < CHROMOSOME_SIZE; ++i) {
        tempGenes[i] = ((parents[0]->genes[i] == GENE_1) && (parents[1]->genes[i] == GENE_1)) ? (GENE_1) : (GENE_0);
    }

    strncpy(child->genes, tempGenes, CHROMOSOME_SIZE);
    child->fitness = calcFitness(child);

    SAFE_FREE(tempGenes);

    return child;
}
