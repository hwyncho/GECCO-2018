/*
 * Created by 조휘연 on 2018. 01. 08.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GECCO-2018
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing structures and functions related to chromosomes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "./Chromosome.h"

// function to initialize chromosome
chromosome *initChromosome() {
    chromosome *individual = NULL;
    individual = (chromosome *) calloc(1, sizeof(chromosome));

    if (individual) {
        individual->id = -1;
        individual->size = CHROMOSOME_SIZE;
        individual->genes = (char *) calloc(CHROMOSOME_SIZE + 1, sizeof(char));
        individual->fitness = 0.0;

        return individual;
    } else {
        ERROR_EXIT("Error: initChromosome(): NULL pointer");
    }
}

// function to finalize chromosome
void freeChromosome(chromosome *individual) {
    SAFE_FREE(individual->genes);
    SAFE_FREE(individual);
}

// function to print genes of chromosome
void printChromosome(chromosome *individual) {
    if (individual) {
        printf("id: %d, genes: %s, fitness: %.3f\n", individual->id, individual->genes, individual->fitness);
    } else {
        puts("Error: printChromosome(individual): NULL pointer");
        exit(-1);
    }
}
