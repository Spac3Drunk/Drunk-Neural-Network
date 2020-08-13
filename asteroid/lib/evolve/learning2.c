#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "evolve.h"
#include <unistd.h>

#define E 2.7182818

float sigmoid(float x)
{
    return(1/(1+pow(E, -x)));
}


float sigmoid_d(float x)
{
    return(sigmoid(x)*(1-sigmoid(x)));
}


float ReLU(float x)
{
    if (x < 0)
        return (0);
    else
        return (x);
}

struct learning *learning_init(int *levels)
{
    struct learning *AI = malloc(sizeof(struct learning));
    int levels_len =  0;
    for (; levels[levels_len]; levels_len++);

    AI->levels_len = levels_len;

    AI->levels = malloc((AI->levels_len+1)*sizeof(float));
    for (int i = 0; levels[i]; i++)
        AI->levels[i] = levels[i];
    AI->levels[AI->levels_len] = 0;

    //init tableau_weight
    AI->tableau_weight = malloc(AI->levels_len*sizeof(float **));
    for (int lv = 1; AI->levels[lv]; lv++){
        AI->tableau_weight[lv] = malloc((AI->levels[lv])*sizeof(float *));
        for (int i = 0; i < AI->levels[lv]; i++){
            AI->tableau_weight[lv][i] = malloc(AI->levels[lv-1]*sizeof(float));
            memset(AI->tableau_weight[lv][i], 0, AI->levels[lv-1]*sizeof(float));
        }
    }

    //init tableau_bias
    AI->tableau_bias = malloc(AI->levels_len*sizeof(float *));
    for (int lv = 0; AI->levels[lv]; lv++){
        AI->tableau_bias[lv] = malloc((AI->levels[lv])*sizeof(float));
        memset(AI->tableau_bias[lv], 0, AI->levels[lv]*sizeof(float));
    }

    //init tableau_val
    AI->tableau_val = malloc(AI->levels_len*sizeof(float *));
    for (int lv = 0; AI->levels[lv]; lv++){
        AI->tableau_val[lv] = malloc((AI->levels[lv])*sizeof(float));
        memset(AI->tableau_val[lv], 0, AI->levels[lv]*sizeof(float));
    }
    return (AI);
}

float *learning_run(struct learning *AI, float *input_neuron)
{
    //clear tableau_val
    for (int lv = 0; AI->levels[lv]; lv++)
        memset(AI->tableau_val[lv], 0, AI->levels[lv]*sizeof(float));

    //set first layer to input
    for (int i = 0; AI->levels[0] > i; i++)
        AI->tableau_val[0][i] = input_neuron[i] + AI->tableau_bias[0][i];
        //AI->tableau_val[0][i] = 1/(1+pow(2.71828182846, -input_neuron[i] + AI->tableau_bias[0][i]));


        //AI->tableau_val[0][i] = input_neuron[i] + AI->tableau_bias[0][i];

    //calculate
    for (int lv = 1; AI->levels[lv]; lv++){
        //printf("layer %i\n", lv);
        for (int neur = 0; AI->levels[lv] > neur; neur++){
            for (int weight = 0; AI->levels[lv-1] > weight; weight++){
                AI->tableau_val[lv][neur] += AI->tableau_weight[lv][neur][weight]*AI->tableau_val[lv-1][weight];
            }
            //printf("%e\n", AI->tableau_val[lv][neur]);
            //printf("\n%e\n\n", AI->tableau_val[lv][neur]);
            AI->tableau_val[lv][neur] /= AI->levels[lv-1];
            AI->tableau_val[lv][neur] += AI->tableau_bias[lv][neur];
            //AI->tableau_val[lv][neur] = 1/(1+pow(2.71828182846, -(AI->tableau_val[lv][neur])));
            AI->tableau_val[lv][neur] = ReLU(-(AI->tableau_val[lv][neur]));
        }
    }
    return (AI->tableau_val[AI->levels_len-1]);
}

void learning_evolve(struct learning *AI, float fact_weight, float fact_bias)
{
    //evolve bias
    if (fact_bias != 0){
        for (int lv = 0; AI->levels[lv]; lv++){
            for (int neur = 0; AI->levels[lv] > neur; neur++){
                AI->tableau_bias[lv][neur] += (rand()/2147483648.0-0.5)*fact_bias;
                //if (AI->tableau_bias[lv][neur] > 1)
                //    AI->tableau_bias[lv][neur] = 1
                //if (AI->tableau_bias[lv][neur] < -1)
                //    AI->tableau_bias[lv][neur] = 0
            }
        }
    }
    //evolve weight
    if (fact_weight != 0){
        for (int lv = 1; AI->levels[lv]; lv++){
            for (int neur = 0; AI->levels[lv] > neur; neur++){
                for (int weight = 0; AI->levels[lv-1] > weight; weight++){
                    AI->tableau_weight[lv][neur][weight] += (rand()/2147483648.0-0.5)*fact_weight;
                    //if (AI->tableau_bias[lv][neur][weight] > 1)
                    //    AI->tableau_bias[lv][neur][weight] = 1
                    //if (AI->tableau_bias[lv][neur][weight] < -1)
                    //    AI->tableau_bias[lv][neur][weight] = 0
                }
            }
        }
    }
}

void learning_free(struct learning *AI)
{
    //free tableau_weight
    for (int lv = 1; AI->levels[lv]; lv++){
        for (int i = 0; i < AI->levels[i]; i++){
            free(AI->tableau_weight[lv][i]);
        }
        free(AI->tableau_weight[lv]);
    }
    free(AI->tableau_weight);

    //free tableau_bias
    for (int lv = 0; AI->levels[lv]; lv++){
        free(AI->tableau_bias[lv]);
    }
    free(AI->tableau_bias);

    //free tableau_val
    for (int lv = 0; AI->levels[lv]; lv++){
        free(AI->tableau_val[lv]);
    }
    free(AI->tableau_val);
    free(AI->levels);
    free(AI);
}

void learning_copy(struct learning *AI, struct learning *AI_o)
{

    //init tableau_weight
    for (int lv = 1; AI->levels[lv]; lv++){
        for (int i = 0; i < AI->levels[lv]; i++){
            for (int ii = 0; ii < AI->levels[lv-1]; ii++)
                AI->tableau_weight[lv][i][ii] = AI_o->tableau_weight[lv][i][ii];
        }
    }

    //init tableau_bias
    for (int lv = 0; AI->levels[lv]; lv++){
        for (int ii = 0; ii < AI->levels[lv]; ii++)
            AI->tableau_bias[lv][ii] = AI_o->tableau_bias[lv][ii];
    }
}
/*
struct learning
{
    int *levels; //should always end with 0
    int levels_len;
    float ***tableau_weight;
    float **tableau_bias;
    float **tableau_val;
};
*/

void learning_write(int fd, struct learning *AI)
{
    write(fd, &AI->levels_len, sizeof(int));
    write(fd, AI->levels, sizeof(int)*(AI->levels_len+1));
    for (int lv = 1; AI->levels[lv]; lv++){
        for (int i = 0; i < AI->levels[i]; i++){
            write(fd, AI->tableau_weight[lv][i], AI->levels[lv]*sizeof(float));
        }
    }
    for (int lv = 0; AI->levels[lv]; lv++){
        write(fd, AI->tableau_bias[lv], AI->levels[lv]*sizeof(float));
    }
}

struct learning *learning_read(int fd)
{
    int levels_len;
    read(fd, &levels_len, 4);
    int *levels = malloc(sizeof(int) * (levels_len+1));
    read(fd, levels, sizeof(int) * (levels_len+1));
    struct learning *AI = learning_init(levels);
    for (int lv = 1; AI->levels[lv]; lv++){
        for (int i = 0; i < AI->levels[i]; i++){
            read(fd, AI->tableau_weight[lv][i], AI->levels[lv]*sizeof(float));
        }
    }
    for (int lv = 0; AI->levels[lv]; lv++){
        read(fd, AI->tableau_bias[lv], AI->levels[lv]*sizeof(float));
    }

    return (AI);
}

/*
void learning_renforce(struct learning *AI, float *got, float *expected)
{

    int lv_max = len(levels);
    for (int i = 0; i < AI->levels[lv_max]; i++)
        float bias_dif = expected[i] - AI->tableau_bias[lv_max][i];
    for (int lv = 1; AI->levels[lv]; lv++){
        for (int i = 0; i < AI->levels[lv]; i++){

            for (int ii = 0; ii < AI->levels[lv-1]; ii++){
                AI->tableau_weight[lv][i][ii] = AI_o->tableau_weight[lv][i][ii];

            }
        }
    }
}

/*
void main(void)
{
    //srand(time(0));
    float mid = 0;
    int levels[] = {9*9, 9*9, 9*9, 9*9, 0};
    struct learning *ai = learning_init(levels);
    float input[] = {1, 2, 3, 4, 5};
    float input2[] = {5, 4, 3, 2, 1};
    learning_evolve(ai, 1, 1);

    float *a = learning_run(ai, input);
    printf("result\n");
    for (int i = 0; ai->levels[ai->levels_len-1] > i; i++)
        printf("%e\n", a[i]);
    printf("######################################\n");
    a = learning_run(ai, input2);
    printf("result\n");
    for (int i = 0; ai->levels[ai->levels_len-1] > i; i++)
        printf("%e\n", a[i]);

    learning_free(ai);
}
*/
