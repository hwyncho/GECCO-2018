/*
 * Created by 조휘연 on 2018. 01. 08.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GeneticAlgorithm
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing functions related to replacement operator.
 */

#include <math.h>
#include <stdlib.h>
#include "Replacement.h"

// function to implement worst replacement
chromosome **worstReplace(size_t populationSize, chromosome **population, replacementArgs args) {
    int i = 0;

    chromosome *tempIndividual = NULL;
    float worstFitness = 0.0;

    tempIndividual = population[0];
    worstFitness = population[0]->fitness;

    for (i = 1; i < populationSize; ++i) {
        if (worstFitness > population[i]->fitness) {
            tempIndividual = population[i];
            worstFitness = population[i]->fitness;
        }
    }

    population[tempIndividual->id] = args.child;
    args.child->id = tempIndividual->id;

    freeChromosome(tempIndividual);
    SAFE_FREE(args.parents);

    return population;
}

// function to implement similar replacement
chromosome **similarReplace(size_t populationSize, chromosome **population, replacementArgs args) {
    int i = 0;

    float distance = 0.0;
    chromosome *tempIndividual = NULL;

    distance = (float) fabs(population[0]->fitness - args.child->fitness);
    tempIndividual = population[0];

    for (i = 1; i < populationSize; ++i) {
        if ((float) fabs(population[i]->fitness - args.child->fitness) <= distance) {
            distance = (float) fabs(population[i]->fitness - args.child->fitness);
            tempIndividual = population[i];
        }
    }

    population[tempIndividual->id] = args.child;
    args.child->id = tempIndividual->id;

    freeChromosome(tempIndividual);
    SAFE_FREE(args.parents);

    return population;
}

// function to implement
chromosome **worstParentReplace(size_t populationSize, chromosome **population, replacementArgs args) {
    chromosome *tempIndividual = NULL;

    tempIndividual = (args.parents[0]->fitness <= args.parents[1]->fitness) ? (args.parents[0]) : (args.parents[1]);

    population[tempIndividual->id] = args.child;
    args.child->id = tempIndividual->id;

    freeChromosome(tempIndividual);
    SAFE_FREE(args.parents);

    return population;
}

// function to implement
chromosome **similarParentReplace(size_t populationSize, chromosome **population, replacementArgs args) {
    float distance1 = 0.0;
    float distance2 = 0.0;
    chromosome *tempIndividual = NULL;

    distance1 = (float) fabs(args.parents[0]->fitness - args.child->fitness);
    distance2 = (float) fabs(args.parents[1]->fitness - args.child->fitness);

    if (distance1 <= distance2) {
        tempIndividual = args.parents[0];
    } else {
        tempIndividual = args.parents[1];
    }

    population[tempIndividual->id] = args.child;
    args.child->id = tempIndividual->id;

    freeChromosome(tempIndividual);
    SAFE_FREE(args.parents);

    return population;
}