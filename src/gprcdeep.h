/*
  libgpr - a library for genetic programming
  Copyright (C) 2016  Bob Mottram <bob@robotics.uk.to>

  NOTE: a deep learning type of approach with autocoders is
  on hold. This requires an evaluation function to invert every
  individual in the population, and relative to an ANN that could
  be quite slow.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
  3. Neither the name of the University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
  .
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE HOLDERS OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef GPRCDEEP_H
#define GPRCDEEP_H

#define PNG_DEBUG 3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <omp.h>
#include "globals.h"
#include <zlib.h>
#include "pnglite.h"
#include "gprcm.h"

#define GPRCDEEP_MAX_LAYERS 32

struct gprcdeep_func {
    /* The number of layers */
    int layers;

    /* each layer is a cartesian genetic programming system */
    gprcm_system layer[GPRCDEEP_MAX_LAYERS];

    /* number of sensors and actuators */
    int sensors, actuators;

    /* random number seed */
    unsigned int random_seed[GPRCDEEP_MAX_LAYERS];
};
typedef struct gprcdeep_func gprcdeep_function;


int gprcdeep_layer_sensors(gprcdeep_function * f, int layer);
int gprcdeep_layer_actuators(gprcdeep_function * f, int layer);
void gprcdeep_init(gprcdeep_function * f,
                   int sensors, int actuators,
                   int layers,
                   unsigned int random_seed);
void gprcdeep_free(gprcdeep_function * f);
int gprcdeep_save(gprcdeep_function * f, char * filename);
int gprcdeep_load(gprcdeep_function * f, char * filename);

#endif
