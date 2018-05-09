/*
 * Created by 조휘연 on 2018. 01. 08.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GeneticAlgorithm
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing functions related to mutation operator.
 */

#include <stdlib.h>
#include "Mutation.h"

void shuffle(char arr[], int n);

// function to implement one point flip mutation
chromosome *onePointFlip(chromosome *individual, mutationArgs args) {
    int i = 0;

    int random = 0;

    random = rand() % 1001;
    if (random <= (args.rate * 1000)) {
        i = rand() % CHROMOSOME_SIZE;
        individual->genes[i] = (individual->genes[i] == GENE_0) ? (GENE_1) : (GENE_0);

        individual->fitness = calcFitness(individual);
    }

    return individual;
}

// function to implement multi point flip mutation
chromosome *multiPointFlip(chromosome *individual, mutationArgs args) {
    int i = 0;

    int random = 0;
    int idx = 0;

    random = rand() % 1001;
    if (random <= (args.rate * 1000)) {
        for (i = 0; i < args.n; ++i) {
            idx = rand() % CHROMOSOME_SIZE;
            individual->genes[idx] = (individual->genes[idx] == GENE_0) ? (GENE_1) : (GENE_0);
        }

        individual->fitness = calcFitness(individual);
    }

    return individual;
}

// function to implement two point swap mutation
chromosome *twoPointSwap(chromosome *individual, mutationArgs args) {
    int random = 0;
    int idx[2] = {0,};
    char tempGene = 0;

    random = rand() % 1001;
    if (random <= (args.rate * 1000)) {
        idx[0] = rand() % CHROMOSOME_SIZE;
        idx[1] = rand() % CHROMOSOME_SIZE;

        tempGene = individual->genes[idx[0]];
        individual->genes[idx[0]] = individual->genes[idx[1]];
        individual->genes[idx[1]] = tempGene;

        individual->fitness = calcFitness(individual);
    }

    return individual;
}

// function to implement scramble mutation
chromosome *scramble(chromosome *individual, mutationArgs args) {
    int i = 0;

    int random = 0;
    int idx[2] = {0,};

    int start = 0;
    int end = 0;
    int length = 0;
    char *temp = NULL;

    random = rand() % 1001;
    if (random <= (args.rate * 1000)) {
        idx[0] = rand() % CHROMOSOME_SIZE;
        idx[1] = rand() % CHROMOSOME_SIZE;

        if (idx[0] <= idx[1]) {
            start = idx[0];
            end = idx[1];
        } else {
            start = idx[1];
            end = idx[0];
        }

        length = (end - start) + 1;
        temp = (char *) calloc((size_t) (length + 1), sizeof(char));
        for (i = 0; i < length; ++i) {
            temp[i] = individual->genes[i + start];
        }

        shuffle(temp, length);

        for (i = 0; i < length; ++i) {
            individual->genes[i + start] = temp[i];
        }

        individual->fitness = calcFitness(individual);

        SAFE_FREE(temp);
    }

    return individual;
}

void shuffle(char *arr, int n) {
    int i = 0;

    int random = 0;
    char temp = 0;

    for (i = n - 1; i > 0; --i) {
        random = rand() % (i + 1);

        temp = arr[i];
        arr[i] = arr[random];
        arr[random] = temp;
    }
}
