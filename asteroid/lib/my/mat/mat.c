/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include <stdlib.h>
#include <math.h>

float *mat3_init(void)
{
    float *mat = malloc(sizeof(float) * 16);
    for (int i = 0; i < 16; i++)
        mat[i] = 0;
    mat[0] = 1;
    mat[5] = 1;
    mat[10] = 1;
    mat[15] = 1;
    return (mat);
}

float *mat3_multiply(float *mat1, float *mat2)
{
    float *mat = malloc(sizeof(float) * 16);
    for (int i = 0; i < 16; i++)
        mat[i] = 0;
    for (int y = 0; y < 4; y++){
        for (int x = 0; x < 4; x++){
            for (int i = 0; i < 4; i++){
                mat[x+y*4] += mat1[i+y*4] * mat2[x+i*4];
            }
        }
    }
    return (mat);
}

float *mat3_copy(float *mat)
{
    float *matt = malloc(sizeof(float) * 16);
    for (int i = 0; i < 16; i++)
        matt[i] = mat[i];
    return (matt);
}
