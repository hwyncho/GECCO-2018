/*
 * Created by 조휘연 on 2018. 01. 08.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GeneticAlgorithm
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing functions related to replacement operator.
 */

#ifndef LIBGA_REPLACEMENT_H
#define LIBGA_REPLACEMENT_H

#include "../GA.h"

// function to implement worst replacement
chromosome **worstReplace(size_t populationSize, chromosome **population, replacementArgs args);

// function to implement similar replacement
chromosome **similarReplace(size_t populationSize, chromosome **population, replacementArgs args);

// function to implement
chromosome **worstParentReplace(size_t populationSize, chromosome **population, replacementArgs args);

// function to implement
chromosome **similarParentReplace(size_t populationSize, chromosome **population, replacementArgs args);

#endif //LIBGA_REPLACEMENT_H
