/*
 * Created by 조휘연 on 2018. 01. 23.
 * Copyright © 2018년 조휘연. All rights reserved.
 *
 * GitHub : https://github.com/hwyncho/GECCO-2018
 * e-mail : hwyn.cho@gmail.com
 *
 * A code containing functions related to NK-Model.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "NK.h"

float **nkTable = NULL;
size_t _N = 0;
size_t _K = 0;

int binary2Decimal(size_t length, const char *binary);

void initNkTable(size_t n, size_t k) {
    int i = 0;
    int j = 0;

    _N = n;
    _K = k;

    nkTable = (float **) calloc(n, sizeof(float *));

    if (nkTable) {
        for (i = 0; i < n; ++i) {
            nkTable[i] = (float *) calloc((size_t) pow(k, k + 1), sizeof(float));
        }

        for (i = 0; i < n; ++i) {
            for (j = 0; j < (size_t) pow(k, k + 1); ++j) {
                nkTable[i][j] = (float) (rand() % 1001 / 1000.0);
            }
        }
    } else {
        puts("Error: initNkTable(n, k, seed): NULL pointer");
        exit(-1);
    }
}

void freeNkTable(void) {
    int i = 0;

    for (i = 0; i < _N; ++i) {
        SAFE_FREE(nkTable[i]);
    }
    SAFE_FREE(nkTable);
}

float nk(chromosome *individual) {
    int i = 0;
    int j = 0;

    float fitness = 0.0;

    char *temp = NULL;
    temp = (char *) calloc((_K + 1) + 1, sizeof(char));

    if (temp) {
        for (i = 0; i < individual->size; ++i) {
            for (j = i; j < i + (_K + 1); ++j) {
                temp[i + (_K + 1) - j] = individual->genes[j % individual->size];
                //temp[i + (_K + 1) - j] = individual->genes[rand() % individual->size];
            }

            fitness += nkTable[i][binary2Decimal((_K + 1), temp)];
        }

        free(temp);

        return fitness;
    } else {
        puts("Error: nk(individual): NULL pointer");
        exit(-1);
    }
}

int binary2Decimal(size_t length, const char *binary) {
    int i = 0;

    int x = 0;
    int dec = 0;

    for (i = 0; i < length; ++i) {
        if (binary[i] == GENE_0) {
            x = 0;
        } else {
            x = 1;
        }

        dec += (x * pow(2, i));
    }

    return dec;
}