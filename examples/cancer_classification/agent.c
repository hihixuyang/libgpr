/* Cartesian Genetic Program
   Evolved using libgpr
   https://launchpad.net/libgpr

   To compile:
     gcc -Wall -std=c99 -pedantic -o agent agent.c -lm
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

const int sensors = 30;
const int actuators = 1;
const int rows = 9;
const int columns = 10;
const int connections_per_gene = 11;
float * genome[1];
float * state[1];
int tick = 0;

/* Genome for ADF_module 0 */
float gene0[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,95.700,27,14,32,20,27,28,18,24,21,7,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,53.246,6,20,6,22,8,7,15,13,37,32,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,31,-81.020,45,47,26,19,19,6,3,6,39,37,36,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,56};

/* State array for ADF_module 0 */
float state0[121];

void get_inputs(int argc, char* argv[])
{
  int i;

  for (i = 0; i < argc; i++) {
    state[0][i] = atof(argv[i]);
  }
}

void run(int ADF_module)
{
  int row,col,n=0,i=0,j,k,g,ctr,src,dest,block_from,block_to,no_of_args;
  int sens,act;
  float * gp;

  if (ADF_module == 0) {
    sens = sensors;
    act = actuators;
  }
  else {
    sens = 10;
    act = 1;
  }

  for (col = 0; col < columns; col++) {
    for (row = 0; row < rows; row++, i++,n+=13) {
      if (genome[ADF_module][n] < 0) continue;
      gp = &genome[ADF_module][n];
      switch((int)gp[0]) {
      case 46: {
        break;
      }
      case 23: {
        j = abs((int)state[ADF_module][(int)gp[2]] + (int)state[ADF_module][(int)gp[3]])
            %(rows*columns);
        state[ADF_module][sens+i] = state[ADF_module][sens+j];
        break;
      }
      case 22: {
        j = abs((int)state[ADF_module][(int)gp[3]])
            %(rows*columns);
        state[ADF_module][sens+i] = gp[1]*state[ADF_module][(int)gp[2]];
        state[ADF_module][sens+j] = state[ADF_module][sens+i];

        if (state[ADF_module][sens+j] > 4096) {
          state[ADF_module][sens+j] = 4096;
        }
        if (state[ADF_module][sens+j] < -4096) {
          state[ADF_module][sens+j] = -4096;
        }
        break;
      }
      case 1: {
        state[ADF_module][sens+i] = (int)gp[1];
        break;
      }
      case 32: {
        no_of_args = 1 + (abs((int)gp[1])%10);
        state[ADF_module][sens+i] = 0;
        for (j = 0; j < no_of_args; j++) {
          state[ADF_module][sens+i] += state[ADF_module][(int)gp[2+j]];
        }
        state[ADF_module][sens+i] = 1.0f / (1.0f + exp(state[ADF_module][sens+i]));
        break;
      }
      case 2: {
        no_of_args = 1 + (abs((int)gp[1])%10);
        state[ADF_module][sens+i] = 0;
        for (j = 0; j < no_of_args; j++) {
          state[ADF_module][sens+i] += state[ADF_module][(int)gp[2+j]];
        }
        break;
      }
      case 3: {
        no_of_args = 1 + (abs((int)gp[1])%10);
        state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]];
        for (j = 0; j < no_of_args; j++) {
          state[ADF_module][sens+i] -= state[ADF_module][(int)gp[2+j]];
        }
        break;
      }
      case 4: {
        state[ADF_module][sens+i] = -(int)state[ADF_module][(int)gp[2]];
        break;
      }
      case 5: {
        no_of_args = 1 + (abs((int)gp[1])%10);
        state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]];
        for (j = 0; j < no_of_args; j++) {
          state[ADF_module][sens+i] *= state[ADF_module][(int)gp[2+j]];
        }
        break;
      }
      case 6: {
        state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]] * gp[1];
        break;
      }
      case 7: {
        if (state[ADF_module][(int)gp[3]] == 0) {
          state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]];
        }
        else {
          state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]] / state[ADF_module][(int)gp[3]];
        }
        break;
      }
      case 8: {
        if ((int)state[ADF_module][(int)gp[3]] == 0) {
          state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]];
        }
        else {
          state[ADF_module][sens+i] = (int)state[ADF_module][(int)gp[2]] % (int)state[ADF_module][(int)gp[3]];
        }
        break;
      }
      case 9: {
        state[ADF_module][sens+i] = floor(state[ADF_module][(int)gp[2]]);
        break;
      }
      case 10: {
        no_of_args = 1 + (abs((int)gp[1])%10);
        state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]];
        for (j = 1; j < no_of_args; j++) {
          state[ADF_module][sens+i] += state[ADF_module][(int)gp[2+j]];
        }
        state[ADF_module][sens+i] /= no_of_args;
        break;
      }
      case 11: {
        state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]];
        break;
      }
      case 12: {
        state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]];
        break;
      }
      case 13: {
        state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]];
        break;
      }
      case 14: {
        state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]];
        break;
      }
      case 15: {
        if (state[ADF_module][(int)gp[2]] > state[ADF_module][(int)gp[3]]) {
          state[ADF_module][sens+i] = (int)gp[1];
        }        else {          state[ADF_module][sens+i] = 0;
        }        break;
      }
      case 16: {
        if (state[ADF_module][(int)gp[2]] < state[ADF_module][(int)gp[3]]) {
          state[ADF_module][sens+i] = (int)gp[1];
        }
        else {
          state[ADF_module][sens+i] = 0;
        }
        break;
      }
      case 17: {
        if (state[ADF_module][(int)gp[2]] == state[ADF_module][(int)gp[3]]) {
          state[ADF_module][sens+i] = (int)gp[1];
        }
        else {
          state[ADF_module][sens+i] = 0;
        }
        break;
      }
      case 18: {
        if ((state[ADF_module][(int)gp[2]]>0) &&
            (state[ADF_module][(int)gp[3]]>0)) {
          state[ADF_module][sens+i] = (int)gp[1];
        }
        else {
          state[ADF_module][sens+i] = 0;
        }
        break;
      }
      case 19: {
        if ((state[ADF_module][(int)gp[2]]>0) ||
            (state[ADF_module][(int)gp[3]]>0)) {
          state[ADF_module][sens+i] = (int)gp[1];
        }
        else {
          state[ADF_module][sens+i] = 0;
        }
        break;
      }
      case 20: {
        if ((state[ADF_module][(int)gp[2]]>0) !=
            (state[ADF_module][(int)gp[3]]>0)) {
          state[ADF_module][sens+i] = (int)gp[1];
        }
        else {
          state[ADF_module][sens+i] = 0;
        }
        break;
      }
      case 21: {
        if (((int)state[ADF_module][(int)gp[2]]) !=
            ((int)state[ADF_module][(int)gp[3]])) {
          state[ADF_module][sens+i] = (int)gp[1];
        }
        else {
          state[ADF_module][sens+i] = 0;
        }
        break;
      }
      case 43: {
          state[ADF_module][sens+i] = 0.10 * state[ADF_module][(int)gp[2]] * state[ADF_module][(int)gp[3]];
        break;
      }
      case 24: {
        state[ADF_module][sens+i] = (float)exp(state[ADF_module][(int)gp[2]]);
        break;
      }
      case 25: {
        state[ADF_module][sens+i] = (float)sqrt(fabs(state[ADF_module][(int)gp[2]]));
        break;
      }
      case 26: {
        state[ADF_module][sens+i] = (float)fabs(state[ADF_module][(int)gp[2]]);
        break;
      }
      case 27: {
        state[ADF_module][sens+i] = (float)(sin(state[ADF_module][(int)gp[2]])*256);
        break;
      }
      case 28: {
        state[ADF_module][sens+i] = (float)asin(state[ADF_module][(int)gp[2]]);
        break;
      }
      case 29: {
        state[ADF_module][sens+i] = (float)(cos(state[ADF_module][(int)gp[2]])*256);
        break;
      }
      case 30: {
        state[ADF_module][sens+i] = (float)acos(state[ADF_module][(int)gp[2]]);
        break;
      }
      case 31: {
        state[ADF_module][sens+i] = (float)pow(state[ADF_module][(int)gp[2]],state[ADF_module][(int)gp[3]]);
        break;
      }
      case 33: {
        no_of_args = 1 + (abs((int)gp[1])%10);
        state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]];
        for (j = 1; j < no_of_args; j++) {
          if (state[ADF_module][(int)gp[2+j]] < state[ADF_module][sens+i]) {
            state[ADF_module][sens+i] = state[ADF_module][(int)gp[2+j]];
          }
        }
        break;
      }
      case 34: {
        no_of_args = 1 + (abs((int)gp[1])%10);
        state[ADF_module][sens+i] = state[ADF_module][(int)gp[2]];
        for (j = 1; j < no_of_args; j++) {
          if (state[ADF_module][(int)gp[2+j]] > state[ADF_module][sens+i]) {
            state[ADF_module][sens+i] = state[ADF_module][(int)gp[2+j]];
          }
        }
        break;
      }
      case 35: {
        if (((int)gp[2] > sens) && ((int)gp[3] > sens)) {
          src = ((int)gp[2]-sens)*13;
          dest = ((int)gp[3]-sens)*13;
          genome[ADF_module][dest] = genome[ADF_module][src];
        }
        break;
      }
      case 36: {
        if (((int)gp[2] > sens) && ((int)gp[3] > sens)) {
          src = ((int)gp[2]-sens)*13;
          dest = ((int)gp[3]-sens)*13;
          genome[ADF_module][dest+1] = genome[ADF_module][src+1];
        }
        break;
      }
      case 37: {
        state[ADF_module][(int)gp[3]] = state[ADF_module][(int)gp[2]];
        break;
      }
      case 38: {
        block_from = (int)gp[2];
        block_to = (int)gp[3];
        if (block_from<block_to) {
          block_from = (int)gp[3];
          block_to = (int)gp[2];
        }
        k = block_to - 2;
        for (j = block_from - 2;
             j <= block_from + 2; j++,k++) {
          if ((j>sens) &&
              (k>sens) &&
              (j<i) && (k<i)) {
            for (g = 0; g < 13; g++) {
              genome[ADF_module][(j-sens)*13 + g] =
                genome[ADF_module][(k-sens)*13 + g];
            }
          }
        }
        break;
      }
      case 39: {
        if (gp[2] > sens) {
          src = ((int)gp[2] - sens) * 13;
          gp[3] = genome[ADF_module][src+2];
        };
        break;
      }
      case 40: {
        if (gp[3] > sens) {
          src = ((int)gp[3] - sens) * 13;
          gp[2] = genome[ADF_module][src+2];
        };
        break;
      }
      case 41: {
        if (gp[3] > sens) {
          src = ((int)gp[3] - sens) * 13;
          gp[2] = genome[ADF_module][src+3];
        };
        break;
      }
      case 42: {
        if (gp[2] > sens) {
          src = ((int)gp[2] - sens) * 13;
          gp[3] = genome[ADF_module][src+3];
        };
        break;
      }
      }
      /* prevent values from going out of range */
      if ((isnan(state[ADF_module][sens+i])) || (isinf(state[ADF_module][sens+i]))) {
        state[ADF_module][sens+i] = 0;
      }
      if (state[ADF_module][sens+i] > 4096) {
        state[ADF_module][sens+i] = 4096;
      }
      if (state[ADF_module][sens+i] < -4096) {
        state[ADF_module][sens+i] = -4096;
      }
    }
  }

  /* set the actuator values */
  ctr = sens + i;
  for (i = 0; i < act; i++, ctr++, n++) {
    state[ADF_module][ctr] = state[ADF_module][(int)genome[ADF_module][n]];
  }
}

void set_outputs()
{
  int i;

  for (i = 0; i < actuators; i++) {
    if (i > 0) printf(" ");
    printf("%.3f",state[0][sensors+(rows*columns)+i]);
  }
  printf("\n");
}

static void setup()
{
  int i,j;


  /* Clear the state array */
  for (i = 0; i < sensors + (rows*columns) + actuators; i++) {
    for (j = 0; j < 0; j++) {
      state[j][i] = 0;
    }
  }

}

static int read_stdin_args(char *argv[])
{
  char argstr[1024], value[1024], *retval;
  int i,ctr=0,field_index=0;
  FILE * fp = fopen("stdin","r");

  if (!fp) return 0;
  while (!feof(fp)) {
    retval = fgets(argstr,1023,fp);
    if (retval) {
      for (i = 0; i < strlen(argstr); i++) {
        if ((argstr[i]==' ') ||
            (argstr[i]==',') ||
            (argstr[i]==';') ||
            (i == strlen(argstr)-1)) {
          if (i == strlen(argstr)-1) {
            value[ctr++] = argstr[i];
          }
          value[ctr] = 0;
          ctr = 0;
          argv[field_index] = (char*)malloc(strlen(value)+2);
          sprintf(argv[field_index++],"%s",value);
        }
        else {
          value[ctr++] = argstr[i];
        }
      }
    }
  }
  fclose(fp);
  return field_index;
}

int main(int argc, char* argv[])
{
  char * stdin_args[1024];
  int i,no_of_stdin_args = read_stdin_args(stdin_args);

  setup();

  if (no_of_stdin_args>0) {
    if (no_of_stdin_args != sensors) {
      printf("Invalid number of arguments %d/%d\n",no_of_stdin_args,sensors);
      for (i = 0; i < no_of_stdin_args; i++) {
        free(stdin_args[i]);
      }
      return -1;
    }
    get_inputs(no_of_stdin_args,stdin_args);
    for (i = 0; i < no_of_stdin_args; i++) {
      free(stdin_args[i]);
    }
  }
  else {
    if (argc-1 != sensors) {
      printf("Invalid number of arguments %d/%d\n",argc-1,sensors);
      return -1;
    }
    get_inputs(argc-1,&argv[1]);
  }

  for (i = 0; i < 2; i++) {
    run(0);
  }
  set_outputs();

  /* Increment the time step */
  tick++;
  if (tick>32000) tick=0;

  return 0;
}
