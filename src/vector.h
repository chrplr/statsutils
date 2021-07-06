/* a simple growable array
 *
 * -*- mode:c; c-default-style: linux; Time-stamp: <2021-07-05 13:22:20 christophe@pallier.org> -*-
 *
 * Copyright Christophe Pallier 2021
 * LICENCE: GNU GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007 <https://www.gnu.org/licenses/gpl-3.0.txt>
 *
 */

#ifndef _VECTOR_H
#define _VECTOR_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
     double *data;
     size_t size;
     size_t allocated;
} vector;

void init_vector(vector *vec, size_t initialSize);
void push_back_vector(vector *vec, double element);
void free_vector(vector vec);
void print_vector(vector vec, char *format, char *sep);
void read_vector(vector *vec, FILE *stream);

#endif
