/*
 * Created by 조휘연 on 2018. 01. 08.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GECCO-2018
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing structures and functions related to chromosomes.
 */

#ifndef LIBGA_CHROMOSOME_H
#define LIBGA_CHROMOSOME_H

#include <stddef.h>

#define SAFE_FREE(p) if (p) { free(p); p = NULL; }
#define ERROR_EXIT(message) if (message) { puts(message); exit(-1); }

#define CHROMOSOME_SIZE 50
#define GENE_0 '0'
#define GENE_1 '1'

// structure that define chromosome
struct _chromosome {
    int id;             // id of chromosome
    size_t size;        // size of genes
    char *genes;        // genes that constitute chromosome
    float fitness;      // fitness of chromosome
};
typedef struct _chromosome chromosome;

chromosome *initChromosome();                       // function to initialize chromosome
void freeChromosome(chromosome *individual);        // function to finalize chromosome
void printChromosome(chromosome *individual);       // function to print genes of chromosome

float (*calcFitness)(
        chromosome *individual);       // function pointer to store function that calculate fitness of chromosome.

#endif //LIBGA_CHROMOSOME_H
