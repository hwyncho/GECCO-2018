/*
 * Created by 조휘연 on 2018. 01. 23.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GeneticAlgorithm
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing functions related to NK-Model.
 */

#ifndef GENETICALGORITHM_NK_H
#define GENETICALGORITHM_NK_H

#include "libGA/Chromosome.h"

void initNkTable(size_t n, size_t k);

void freeNkTable(void);

float nk(chromosome *individual);

#endif //GENETICALGORITHM_NK_H
