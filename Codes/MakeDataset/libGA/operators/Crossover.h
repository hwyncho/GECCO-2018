/*
 * Created by 조휘연 on 2018. 01. 08.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GeneticAlgorithm
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing functions related to crossover operator.
 */

#ifndef LIBGA_CROSSOVER_H
#define LIBGA_CROSSOVER_H

#include "../GA.h"

// function to implement one point crossover
chromosome *onePoint(chromosome **parents, crossoverArgs args);

// function to implement n point crossover
chromosome *multiPoint(chromosome **parents, crossoverArgs args);

// function to implement uniform crossover
chromosome *uniform(chromosome **parents, crossoverArgs args);

// function to implement arithmetic crossover
chromosome *arithmetic(chromosome **parents, crossoverArgs args);

#endif //LIBGA_CROSSOVER_H
