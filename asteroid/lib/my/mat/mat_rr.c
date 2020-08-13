/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include <math.h>
#include <stdlib.h>
#include "../my.h"

void mat3_rrx(float *mat_o, float a)
{
    float *mat = mat3_init();
    mat[5] = cos(a);
    mat[6] = -sin(a);
    mat[9] = sin(a);
    mat[10] = cos(a);
    float *mat_f = mat3_multiply(mat_o, mat);
    for (int i = 0; i < 16; i++)
        mat_o[i] = mat_f[i];
    free(mat_f);
    free(mat);
}

void mat3_rry(float *mat_o, float a)
{
    float *mat = mat3_init();
    mat[0] = cos(a);
    mat[2] = sin(a);
    mat[8] = -sin(a);
    mat[10] = cos(a);
    float *mat_f = mat3_multiply(mat_o, mat);
    for (int i = 0; i < 16; i++)
        mat_o[i] = mat_f[i];
    free(mat_f);
    free(mat);
}

void mat3_rrz(float *mat_o, float a)
{
    float *mat = mat3_init();
    mat[0] = cos(a);
    mat[1] = -sin(a);
    mat[4] = sin(a);
    mat[5] = cos(a);
    float *mat_f = mat3_multiply(mat_o, mat);
    for (int i = 0; i < 16; i++)
        mat_o[i] = mat_f[i];
    free(mat_f);
    free(mat);
}
