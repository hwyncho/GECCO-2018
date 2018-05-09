/*
 * Created by 조휘연 on 2018. 01. 08.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GECCO-2018
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing structures and functions related to genetic algorithm.
 */

#ifndef LIBGA_GA_H
#define LIBGA_GA_H

#include "Chromosome.h"

struct __selectionArgs {
    int scale;
    float k;
}; // structure containing the arguments of the selection operator

struct __crossoverArgs {
    int n;
    float p;
}; // structure containing the arguments of the crossover operator

struct __mutationArgs {
    int n;
    float rate;
}; // structure containing the arguments of the mutation operator

struct __replacementArgs {
    chromosome **parents;
    chromosome *child;
}; // structure containing the arguments of the replacement operator

typedef struct __selectionArgs selectionArgs;
typedef struct __crossoverArgs crossoverArgs;
typedef struct __mutationArgs mutationArgs;
typedef struct __replacementArgs replacementArgs;

struct __selection {
    chromosome **(*rouletteWheel)(size_t, chromosome **, selectionArgs);

    chromosome **(*scaledRouletteWheel)(size_t, chromosome **, selectionArgs);

    chromosome **(*rankBased)(size_t, chromosome **, selectionArgs);

    chromosome **(*tournament)(size_t, chromosome **, selectionArgs);
};

struct __crossover {
    chromosome *(*onePoint)(chromosome **, crossoverArgs);

    chromosome *(*multiPoint)(chromosome **, crossoverArgs);

    chromosome *(*uniform)(chromosome **, crossoverArgs);

    chromosome *(*arithmetic)(chromosome **, crossoverArgs);
};

struct __mutation {
    chromosome *(*onePointFlip)(chromosome *, mutationArgs);

    chromosome *(*multiPointFlip)(chromosome *, mutationArgs);

    chromosome *(*twoPointSwap)(chromosome *, mutationArgs);

    chromosome *(*scramble)(chromosome *, mutationArgs);
};

struct __replacement {
    chromosome **(*worstReplace)(size_t, chromosome **, replacementArgs);

    chromosome **(*similarReplace)(size_t, chromosome **, replacementArgs);

    chromosome **(*worstParentReplace)(size_t, chromosome **, replacementArgs);

    chromosome **(*similarParentReplace)(size_t, chromosome **, replacementArgs);
};

struct __selection *SELECTION;
struct __crossover *CROSSOVER;
struct __mutation *MUTATION;
struct __replacement *REPLACEMENT;

struct __ga {
    size_t populationSize;
    chromosome **population;

    chromosome **(*selection)(size_t, chromosome **, selectionArgs);

    chromosome *(*crossover)(chromosome **, crossoverArgs);

    chromosome *(*mutation)(chromosome *, mutationArgs);

    chromosome **(*replacement)(size_t, chromosome **, replacementArgs);
};

typedef struct __ga ga;

ga *initGA(size_t populationSize);

void freeGA(ga *pGA);

chromosome *runGA(ga *pGA, size_t generationSize, selectionArgs args1, crossoverArgs args2, mutationArgs args3);

chromosome *getBestChromosome(ga *pGA);

#endif //LIBGA_GA_H
