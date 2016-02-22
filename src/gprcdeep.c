/*
 libgpr - a library for genetic programming
 Copyright (C) 2016  Bob Mottram <bob@robotics.uk.to>

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

#include "gprcdeep.h"

/* returns the number of sensors at the given layer */
int gprcdeep_layer_sensors(gprcdeep_function * f, int layer)
{
    int diff = f->sensors - f->actuators;
    int final_layer_sensors = f->actuators + (diff*2/10);
    return f->sensors - (layer * (final_layer_sensors) / f->layers);
}

/* returns the number of actuators for a given layer */
int gprcdeep_layer_actuators(gprcdeep_function * f, int layer)
{
    if (layer < f->layers-1) {
        return gprcdeep_layer_sensors(f, layer+1);
    }
    return f->actuators;
}

/* initialise */
void gprcdeep_init(gprcdeep_function * f,
                   int sensors, int actuators,
                   int layers,
                   unsigned int random_seed)
{
    int i;
    int islands = 4;
    int modules = 0;
    int migration_interval = 200;
    int population_per_island = 64;
    int connections_per_gene = GPRC_MAX_ADF_MODULE_SENSORS+1;
    int chromosomes = 3;
    float min_value = -100;
    float max_value = 100;
    int rows = 9, columns = 16;
    int data_size = 0, data_fields = 0;
    int integers_only = 0;
    int instruction_set[64], no_of_instructions=0;

    f->layers = layers;
    f->sensors = sensors;
    f->actuators = actuators;

    /* create an instruction set */
    no_of_instructions =
        gprc_dynamic_instruction_set((int*)instruction_set);

    /* create the layers */
    for (i = 0; i < f->layers; i++) {
        /* ensure a different random seed for each layer */
        f->random_seed[i] = random_seed++;

        /* initialise the layer */
        gprcm_init_system(&f->layer[i], islands,
                          population_per_island,
                          rows, columns,
                          gprcdeep_layer_sensors(f, i),
                          gprcdeep_layer_actuators(f, i),
                          connections_per_gene,
                          modules,
                          chromosomes,
                          min_value, max_value,
                          integers_only,
                          data_size, data_fields,
                          &f->random_seed[i],
                          instruction_set, no_of_instructions);
    }
}

void gprcdeep_free(gprcdeep_function * f)
{
    int i;

    for (i = 0; i < f->layers; i++) {
        gprcm_free_system(&f->layer[i]);
    }
}

int gprcdeep_save(gprcdeep_function * f, char * filename)
{
    int i;
    FILE * fp;

    fp  =fopen(filename, "w");
    if (!fp) return -1;

    fprintf(fp, "%d\n", f->layers);
    fprintf(fp, "%d\n", f->sensors);
    fprintf(fp, "%d\n", f->actuators);
    for (i = 0; i < f->layers; i++) {
        gprcm_save_system(&f->layer[i], fp);
    }

    fclose(fp);
    return 0;
}

int gprcdeep_load(gprcdeep_function * f, char * filename)
{
    FILE * fp = fopen(filename, "r");
    char line[256];
    int i, sensors=0, actuators=0, layers=0;
    int instruction_set[64], no_of_instructions=0;
    if (!fp) return -1;

    if (fgets(line, 255, fp) != NULL ) {
        layers = atoi(line);
    }
    if (fgets(line, 255, fp) != NULL ) {
        sensors = atoi(line);
    }
    if (fgets(line, 255, fp) != NULL ) {
        actuators = atoi(line);
    }
    if (layers == 0) return -2;
    if (sensors == 0) return -3;
    if (actuators == 0) return -4;

    /* create an instruction set */
    no_of_instructions =
        gprc_dynamic_instruction_set((int*)instruction_set);

    gprcdeep_init(f, sensors, actuators,
                  layers, (unsigned int)123);

    for (i = 0; i < layers; i++) {
        gprcm_load_system(&f->layer[i], fp,
                          instruction_set, no_of_instructions);
    }

    fclose(fp);

    return 0;
}
