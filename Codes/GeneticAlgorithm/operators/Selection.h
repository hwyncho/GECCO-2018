/*
 * Created by 조휘연 on 2018. 01. 08.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GeneticAlgorithm
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing functions related to selection operator.
 */

#ifndef LIBGA_SELECTION_H
#define LIBGA_SELECTION_H

#include "../GA.h"

// function to implement roulette wheel selection
chromosome **rouletteWheel(size_t populationSize, chromosome **population, struct __selectionArgs args);

// function to implement scaled roulette wheel selection
chromosome **scaledRouletteWheel(size_t populationSize, chromosome **population, struct __selectionArgs args);

// function to implement rank based selection
chromosome **rankBased(size_t populationSize, chromosome **population, struct __selectionArgs args);

// function to implement tournament selection
chromosome **tournament(size_t populationSize, chromosome **population, struct __selectionArgs args);

#endif //LIBGA_SELECTION_H
