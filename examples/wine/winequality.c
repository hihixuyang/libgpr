/*
  Estimating wine quality
  Copyright (C) 2013  Bob Mottram <bob@robotics.uk.to>

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

#include <stdio.h>
#include <time.h>
#include "libgpr/globals.h"
#include "libgpr/gprcm.h"

#define MAX_EXAMPLES 5000
#define MAX_TEST_EXAMPLES 200
#define MAX_FIELDS   16

#define RUN_STEPS 2

float wine_data[MAX_EXAMPLES*MAX_FIELDS];
float test_data[MAX_TEST_EXAMPLES*MAX_FIELDS];
float * current_data_set;

int no_of_examples = 0;
int fields_per_example = 0;

/* create a test data set from the original data.
   The test data can be used to calculate a final fitness
   value, because it was not seen during training and so
   provides an indication of how well the system has generalised */
static int create_test_data(float * training_data,
							int * no_of_training_examples,
							int fields_per_example,
							float * test_data)
{
	int i,j,k,index;
	int no_of_test_examples = 0;
	unsigned int random_seed = (unsigned int)time(NULL);

	for (i = 0; i < MAX_TEST_EXAMPLES; i++) {
		/* pick an example from the loaded data set */
		index =
			rand_num(&random_seed)%(*no_of_training_examples);

		/* increase the number of test examples */
		for (j = 0; j < fields_per_example; j++) {
			test_data[no_of_test_examples*
					  fields_per_example + j] =
				training_data[index*fields_per_example + j];
		}
		no_of_test_examples++;

		/* reshuffle the original data set */
		for (j = index+1; j < (*no_of_training_examples); j++) {
			for (k = 0; k < fields_per_example; k++) {
				training_data[(j-1)*fields_per_example + k] = 
					training_data[j*fields_per_example + k];
			}
		}
		/* decrease the number of training data examples */
		*no_of_training_examples = *no_of_training_examples - 1;
	}

	return no_of_test_examples;
}
							

static int load_data(char * filename, float * training_data,
					 int max_examples,
					 int * fields_per_example)
{
	int i, field_number, ctr, examples_loaded = 0;
	FILE * fp;
	char line[2000],valuestr[256],*retval;
	float value;
	int training_data_index = 0;

	fp = fopen(filename,"r");
	if (!fp) return 0;

	while (!feof(fp)) {
		retval = fgets(line,1999,fp);
		if (retval) {
			if (strlen(line)>0) {
				field_number = 0;
				ctr = 0;
				for (i = 0; i < strlen(line); i++) {
					if ((line[i]==',') || (line[i]==';') ||
						(i==strlen(line)-1)) {
						if (i==strlen(line)-1) {
							valuestr[ctr++]=line[i];
						}
						valuestr[ctr]=0;
						ctr=0;

						/* get the value from the string */
						value = 0;
						if (valuestr[0]!='?') {
							if ((valuestr[0]>='0') &&
								(valuestr[0]<='9')) {
								value = atof(valuestr);
							}
						}

						/* insert value into the array */
						training_data[training_data_index] =
							value;
						field_number++;
						training_data_index++;
					}
					else {
						/* update the value string */
						valuestr[ctr++]=line[i];
					}
				}
				*fields_per_example = field_number;
				examples_loaded++;
				if (examples_loaded >= max_examples) {
					fclose(fp);
					return examples_loaded;
				}
			}
		}
	}

	fclose(fp);

	return examples_loaded;
}

static float evaluate_features(int trials,
							   gprcm_population * population,
							   int individual_index,
							   int custom_command)
{
	int i,j,n,itt;
	float diff=0,v,quality,error,fitness;
	float dropout_rate = 0.1f;
	gprcm_function * f =
		&population->individual[individual_index];

	if (custom_command!=0) dropout_rate=0;

	for (i = 0; i < trials; i++) {
		/* clear the state */
		gprcm_clear_state(f,
						  population->rows, population->columns,
						  population->sensors, population->actuators);

		n = i;

		for (j = 0; j < fields_per_example - 1; j++) {
			gprcm_set_sensor(f, j,
							 current_data_set[n*
											  fields_per_example+j]);
		}
		for (itt=0;itt<RUN_STEPS;itt++) {
			/* run the program */
			gprcm_run(f, population, dropout_rate, 0, 0);
		}
		/* how close is the output to the actual quality? */
		quality =
			0.01f + current_data_set[n*fields_per_example+
									 fields_per_example-1];
		
		v = 0.01f + fabs(gprcm_get_actuator(f,0,
											population->rows,
											population->columns,
											population->sensors));
		error = (v - quality)/quality;
		diff += error*error;
	}
	diff = (float)sqrt(diff/trials)*100;
	fitness = 100.0f - diff;
	if (fitness < 0) fitness = 0;
	return fitness;
}

static void wine_quality()
{
	int islands = 4;
	int migration_interval = 250;
	int population_per_island = 64;
	int rows = 9, columns = 16;
	int i, gen=0;
	int connections_per_gene = GPRC_MAX_ADF_MODULE_SENSORS+1;
	int modules = 0;
	int chromosomes = 3;
	gprcm_system sys;
 	float min_value = -100;
	float max_value = 100;
	float elitism = 0.2f;
	float mutation_prob = 0.2f;
	int trials = 100;
	int use_crossover = 1;
	unsigned int random_seed = (unsigned int)time(NULL);
	int sensors, actuators=1;
	int integers_only = 0;
	int no_of_test_examples;
	float test_performance;
	FILE * fp;
	int data_size=0, data_fields=0;
	char compile_command[256];
	int instruction_set[64], no_of_instructions=0;
	char * sensor_names[] = {
		"Fixed Acidity",
		"Volatile Acidity",
		"Citric Acid",
		"Residual Sugar",
		"Chlorides",
		"Free Sulphur Dioxide",
		"Total Sulfur Dioxide",
		"Density",
		"pH",
		"Sulphates",
		"Alcohol"
	};
	char * actuator_names[] = {
		"Quality"
	};

	/* load the data */
	no_of_examples =
		load_data("winequality-white.csv",
				  wine_data, MAX_EXAMPLES,
				  &fields_per_example);

	/* create a test data set */
	no_of_test_examples = create_test_data(wine_data,
										   &no_of_examples,
										   fields_per_example,
										   test_data);

	sensors = fields_per_example-1;
	trials = no_of_examples;

	printf("Number of training examples: %d\n",no_of_examples);
	printf("Number of test examples: %d\n",no_of_test_examples);
	printf("Number of fields: %d\n",fields_per_example);

	/* create an instruction set */
	no_of_instructions =
		gprcm_equation_instruction_set((int*)instruction_set);

	/* create a population */
	gprcm_init_system(&sys, islands,
					  population_per_island,
					  rows, columns,
					  sensors, actuators,
					  connections_per_gene,
					  modules,
					  chromosomes,
					  min_value, max_value,
					  integers_only,
					  data_size, data_fields,
					  &random_seed,
					  instruction_set, no_of_instructions);

	gpr_xmlrpc_server("server.rb","wine",3573,
					  "./agent",
					  sensors, actuators);

	test_performance = 0;
	while (test_performance < 99) {
		/* use the training data */
		current_data_set = wine_data;

		/* evaluate each individual */
		gprcm_evaluate_system(&sys,
							  trials,0,
							  (*evaluate_features));
		/* produce the next generation */
		gprcm_generation_system(&sys,
								migration_interval,
								elitism,
								mutation_prob,
								use_crossover, &random_seed,
								instruction_set,
								no_of_instructions);

		/* evaluate the test data set */
		current_data_set = test_data;
		test_performance =
			evaluate_features(no_of_test_examples,
							  &sys.island[0], 0, 1);

		/* show the best fitness value calculated from
		   the test data set */
		printf("Generation %05d  Fitness %.2f/%.2f%% ",
			   gen, gprcm_best_fitness(&sys.island[0]),
			   test_performance);
		for (i = 0; i < islands; i++) {
			printf("  %.3f",
				   gprcm_average_fitness(&sys.island[i]));
		}
		printf("\n");

		if (((gen % 50 == 0) && (gen>0)) ||
			(test_performance > 99)) {
			gprcm_draw_population("population.png",
								  640, 640, &sys.island[0]);

			gprcm_plot_history_system(&sys,
									  GPR_HISTORY_FITNESS,
									  "fitness.png",
									  "Wine Quality " \
									  "Estimation Performance",
									  640, 480);

			gprcm_plot_history_system(&sys,
									  GPR_HISTORY_AVERAGE,
									  "fitness_average.png",
									  "Wine Quality Estimation " \
									  "Average Performance",
									  640, 480);

			gprcm_plot_history_system(&sys,
									  GPR_HISTORY_DIVERSITY,
									  "diversity.png",
									  "Wine Quality " \
									  "Estimation Diversity",
									  640, 480);

			gprcm_plot_fitness(&sys.island[0],
							   "fitness_histogram.png",
							   "Wine Quality Estimation " \
							   "Fitness Histogram",
							   640, 480);

			fp = fopen("agent.c","w");
			if (fp) {
				/* save the best program */
				gprcm_c_program(&sys,
								gprcm_best_individual_system(&sys),
								RUN_STEPS, 0, fp);
				fclose(fp);

				/* compile the program */
				sprintf(compile_command,
						"gcc -Wall -std=c99 -pedantic " \
						"-o agent agent.c -lm");
				assert(system(compile_command)==0);
			}

			fp = fopen("fittest.dot","w");
			if (fp) {
				gprcm_dot(gprcm_best_individual_system(&sys),
						  &sys.island[0],
						  sensor_names,  actuator_names,
						  fp);
				fclose(fp);
			}

		}

		if (test_performance > 99) break;
		gen++;
	}

	/* free memory */
	gprcm_free_system(&sys);
}

int main(int argc, char* argv[])
{	
	wine_quality();
	return 1;
}

