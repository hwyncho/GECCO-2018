/*
 * Created by 조휘연 on 2018. 01. 23.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GeneticAlgorithm
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing functions related to one-max.
 */
#include <stdio.h>
#include <stdlib.h>

#include "OneMax.h"

float oneMax(chromosome *individual) {
    int i = 0;

    float fitness = 0.0;

    if (individual) {
        for (i = 0; i < individual->size; ++i) {
            fitness = (individual->genes[i] == GENE_1) ? (++fitness) : (fitness);
        }

        return fitness;
    } else {
        puts("Error: oneMax(individual): NULL pointer");
        exit(-1);
    }
}
