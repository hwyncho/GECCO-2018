/*
 * Created by 조휘연 on 2018. 01. 08.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GeneticAlgorithm
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing functions related to selection operator.
 */

#include <math.h>
#include <stdlib.h>
#include "../GA.h"
#include "Selection.h"

void quickSort(chromosome **population, int start, int end);

// function to implement roulette wheel selection
chromosome **rouletteWheel(size_t populationSize, chromosome **population, struct __selectionArgs args) {
    int i = 0;
    int j = 0;

    int point = 0;
    float sum = 0.0;

    float sumOfFitness = 0.0;
    chromosome **parents = NULL;

    // calculate the total fitness of chromosomes
    for (i = 0; i < populationSize; ++i) {
        sumOfFitness += population[i]->fitness;
    }

    parents = (chromosome **) calloc(2, sizeof(chromosome *));
    parents[0] = population[rand() % populationSize];
    parents[1] = population[rand() % populationSize];

    for (i = 0; i < 2; ++i) {
        point = rand() % (int) sumOfFitness;
        for (j = 0; j < populationSize; ++j) {
            sum += population[j]->fitness;

            if (sum >= point) {
                parents[i] = population[j];
                sum = 0.0;
                break;
            }
        }
    }

    return parents;
}

// function to implement scaled roulette wheel selection
chromosome **scaledRouletteWheel(size_t populationSize, chromosome **population, struct __selectionArgs args) {
    int i = 0;
    int j = 0;

    int point = 0;
    float sum = 0.0;

    float fitness = 0.0;
    float worstFitness = 0.0;
    float bestFitness = 0.0;
    float sumOfFitness = 0.0;

    chromosome **parents = NULL;

    worstFitness = population[0]->fitness;
    bestFitness = population[0]->fitness;
    // calculate the total fitness of chromosomes
    for (i = 0; i < populationSize; ++i) {
        if (worstFitness >= population[i]->fitness) {
            worstFitness = population[i]->fitness;
        }

        if (bestFitness <= population[i]->fitness) {
            bestFitness = population[i]->fitness;
        }

        sumOfFitness += population[i]->fitness;
    }

    sumOfFitness /= args.scale;

    parents = (chromosome **) calloc(2, sizeof(chromosome *));
    parents[0] = population[rand() % populationSize];
    parents[1] = population[rand() % populationSize];

    for (i = 0; i < 2; ++i) {
        point = rand() % (int) sumOfFitness;
        for (j = 0; j < populationSize; ++j) {
            fitness = (float) (fabs(population[i]->fitness - worstFitness) +
                               (fabs(bestFitness - worstFitness) / (args.scale - 1)));
            sum += fitness;

            if (sum >= point) {
                parents[i] = population[j];
                sum = 0.0;
                break;
            }
        }
    }

    return parents;
}

// function to implement rank based selection
chromosome **rankBased(size_t populationSize, chromosome **population, struct __selectionArgs args) {
    int i = 0;
    int j = 0;

    int point = 0;
    float sum = 0.0;
    int sumOfRank = 0;

    chromosome **parents = NULL;

    // sort population by fitness of chromosomes
    quickSort(population, 0, (int) populationSize - 1);

    // calculate the total ranks of chromosomes
    for (i = 0; i < populationSize; ++i) {
        population[i]->id = i;
        sumOfRank += i;
    }

    parents = (chromosome **) calloc(2, sizeof(chromosome *));
    parents[0] = population[rand() % populationSize];
    parents[1] = population[rand() % populationSize];

    for (i = 0; i < 2; ++i) {
        point = rand() % sumOfRank;
        for (j = 0; j < populationSize; ++j) {
            sum += population[j]->fitness;

            if (sum >= point) {
                parents[i] = population[j];
                sum = 0.0;
                break;
            }
        }
    }

    return parents;
}

// function to implement tournament selection
chromosome **tournament(size_t populationSize, chromosome **population, struct __selectionArgs args) {
    int i = 0;

    float point = 0.0;

    chromosome *temp1 = NULL;
    chromosome *temp2 = NULL;

    chromosome **parents = (chromosome **) calloc(2, sizeof(chromosome *));
    parents[0] = population[rand() % populationSize];
    parents[1] = population[rand() % populationSize];

    for (i = 0; i < 2; ++i) {
        // select two chromosomes randomly.
        temp1 = population[rand() % populationSize];
        temp2 = population[rand() % populationSize];

        // if point is bigger than k, select chromosome that has worse fitness
        // else point is smaller than k, select chromosome that has better fitness
        point = (float) (rand() % 1001 / 1000.0);
        if (point >= args.k) {
            if (temp1->fitness <= temp2->fitness) {
                parents[i] = temp1;
            } else {
                parents[i] = temp2;
            }
        } else {
            if (temp1->fitness >= temp2->fitness) {
                parents[i] = temp1;
            } else {
                parents[i] = temp2;
            }
        }
    }

    return parents;
}

void quickSort(chromosome **population, int left, int right) {
    int i = left;
    int j = right;

    chromosome *pivot = population[(left + right) / 2];
    chromosome *temp = NULL;

    do {
        while (population[i]->fitness < pivot->fitness) {
            i++;
        }

        while (population[j]->fitness > pivot->fitness) {
            j--;
        }

        if (i <= j) {
            temp = population[i];
            population[i] = population[j];
            population[j] = temp;

            i++;
            j--;
        }
    } while (i <= j);

    if (left < j) {
        quickSort(population, left, j);
    }

    if (i < right) {
        quickSort(population, i, right);
    }
}
