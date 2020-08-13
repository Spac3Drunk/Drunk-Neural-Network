
#ifndef evolve
#define evolve
#endif

struct learning *learning_init(int *levels);
float *learning_run(struct learning *AI, float *input_neuron);
void learning_evolve(struct learning *AI, float fact_weight, float fact_bias);
void learning_free(struct learning *AI);
void learning_copy(struct learning *AI, struct learning *AI_o);
struct learning *learning_read(int fd);
void learning_write(int fd, struct learning *AI);

struct learning
{
    int *levels; //should always end with 0
    int levels_len;
    float ***tableau_weight;
    float **tableau_bias;
    float **tableau_val;
};
