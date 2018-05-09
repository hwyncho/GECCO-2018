/*
 * Created by 조휘연 on 2018. 01. 08.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GECCO-2018
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing structures and functions related to genetic algorithm.
 */

#include <stdio.h>
#include <stdlib.h>
#include "GA.h"
#include "operators/Selection.h"
#include "operators/Crossover.h"
#include "operators/Mutation.h"
#include "operators/Replacement.h"

void initOperator(void);        // function to initialize operators
void freeOperator(void);        // function to finalize operators

// function to initialize population & function to finalize population
chromosome **initPopulation(size_t populationSize);

void freePopulation(size_t populationSize, chromosome **population);

ga *initGA(size_t populationSize) {
    ga *newGA = NULL;
    newGA = (ga *) calloc(1, sizeof(ga));

    if (newGA) {
        newGA->populationSize = populationSize;
        newGA->population = initPopulation(populationSize);

        initOperator();

        return newGA;
    } else {
        puts("Error: initGA(populationSize): NULL pointer");
        exit(-1);
    }
}

void freeGA(ga *pGA) {
    if (pGA) {
        freeOperator();

        freePopulation(pGA->populationSize, pGA->population);
        SAFE_FREE(pGA);
    } else {
        puts("Error: freeGA(pGA): NULL pointer");
        exit(-1);
    }
}

chromosome *runGA(ga *pGA, size_t generationSize, selectionArgs args1, crossoverArgs args2, mutationArgs args3) {
    int i = 0;

    chromosome **parents = NULL;
    chromosome *child = NULL;

    replacementArgs args4 = {0,};

    for (i = 0; i < generationSize; ++i) {
        parents = pGA->selection(pGA->populationSize, pGA->population, args1);
        child = pGA->crossover(parents, args2);
        child = pGA->mutation(child, args3);

        args4.parents = parents;
        args4.child = child;
        pGA->population = pGA->replacement(pGA->populationSize, pGA->population, args4);
    }

    return getBestChromosome(pGA);
}

chromosome *getBestChromosome(ga *pGA) {
    int i = 0;

    chromosome *bestIndividual = NULL;
    float bestFitness = 0.0;

    if (pGA) {
        bestIndividual = pGA->population[0];
        bestFitness = pGA->population[0]->fitness;

        for (i = 0; i < pGA->populationSize; ++i) {
            if (bestFitness < pGA->population[i]->fitness) {
                bestIndividual = pGA->population[i];
                bestFitness = pGA->population[i]->fitness;
            }
        }

        return bestIndividual;
    } else {
        puts("Error: getBestChromosome(pGA): NULL pointer");
        exit(-1);
    }
}

void initOperator(void) {
    SELECTION = (struct __selection *) calloc(1, sizeof(struct __selection));
    if (SELECTION) {
        SELECTION->rouletteWheel = rouletteWheel;
        SELECTION->scaledRouletteWheel = scaledRouletteWheel;
        SELECTION->rankBased = rankBased;
        SELECTION->tournament = tournament;
    } else {
        puts("Error: initOperator(): SELECTION: NULL pointer");
        exit(-1);
    }

    CROSSOVER = (struct __crossover *) calloc(1, sizeof(struct __crossover));
    if (CROSSOVER) {
        CROSSOVER->onePoint = onePoint;
        CROSSOVER->multiPoint = multiPoint;
        CROSSOVER->uniform = uniform;
        CROSSOVER->arithmetic = arithmetic;
    } else {
        puts("Error: initOperator(): CROSSOVER: NULL pointer");
        exit(-1);
    }

    MUTATION = (struct __mutation *) calloc(1, sizeof(struct __mutation));
    if (MUTATION) {
        MUTATION->onePointFlip = onePointFlip;
        MUTATION->multiPointFlip = multiPointFlip;
        MUTATION->twoPointSwap = twoPointSwap;
        MUTATION->scramble = scramble;
    } else {
        puts("Error: initOperator(): MUTATION: NULL pointer");
        exit(-1);
    }

    REPLACEMENT = (struct __replacement *) calloc(1, sizeof(struct __replacement));
    if (REPLACEMENT) {
        REPLACEMENT->worstReplace = worstReplace;
        REPLACEMENT->similarReplace = similarReplace;
        REPLACEMENT->worstParentReplace = worstParentReplace;
        REPLACEMENT->similarParentReplace = similarParentReplace;
    } else {
        puts("Error: initOperator(): REPLACEMENT: NULL pointer");
        exit(-1);
    }
}

void freeOperator(void) {
    SAFE_FREE(REPLACEMENT);
    SAFE_FREE(MUTATION);
    SAFE_FREE(CROSSOVER);
    SAFE_FREE(SELECTION);
}

chromosome **initPopulation(size_t populationSize) {
    int i = 0;
    int j = 0;

    chromosome **population = NULL;
    population = (chromosome **) calloc(populationSize, sizeof(chromosome *));

    if (population) {
        // initialize chromosomes
        for (i = 0; i < populationSize; ++i) {
            population[i] = initChromosome();

            population[i]->id = i;

            for (j = 0; j < CHROMOSOME_SIZE; ++j) {
                population[i]->genes[j] = (rand() % 2 == 0) ? (GENE_0) : (GENE_1);
            }

            population[i]->fitness = calcFitness(population[i]);
        }

        return population;
    } else {
        puts("Error: initPopulation(): NULL pointer");
        exit(-1);
    }
}

void freePopulation(size_t populationSize, chromosome **population) {
    // finalize chromosomes
    for (int i = 0; i < populationSize; ++i) {
        freeChromosome(population[i]);
    }
}
