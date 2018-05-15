/*
 * Created by 조휘연 on 2018. 01. 08.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GeneticAlgorithm
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing functions related to mutation operator.
 */

#ifndef LIBGA_MUTATION_H
#define LIBGA_MUTATION_H

#include "../GA.h"

// function to implement one point flip mutation
chromosome *onePointFlip(chromosome *individual, mutationArgs args);

// function to implement multi point flip mutation
chromosome *multiPointFlip(chromosome *individual, mutationArgs args);

// function to implement two point swap mutation
chromosome *twoPointSwap(chromosome *individual, mutationArgs args);

// function to implement scramble mutation
chromosome *scramble(chromosome *individual, mutationArgs args);

#endif //LIBGA_MUTATION_H
