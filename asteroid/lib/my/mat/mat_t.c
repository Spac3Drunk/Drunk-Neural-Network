/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include <math.h>
#include <stdlib.h>
#include "../my.h"

void mat3_tx(float *mat_o, float t)
{
    float *mat = mat3_init();
    mat[3] = t;
    float *mat_f = mat3_multiply(mat, mat_o);
    for (int i = 0; i < 16; i++)
        mat_o[i] = mat_f[i];
    free(mat_f);
    free(mat);
}

void mat3_ty(float *mat_o, float t)
{
    float *mat = mat3_init();
    mat[7] = t;
    float *mat_f = mat3_multiply(mat, mat_o);
    for (int i = 0; i < 16; i++)
        mat_o[i] = mat_f[i];
    free(mat_f);
    free(mat);
}

void mat3_tz(float *mat_o, float t)
{
    float *mat = mat3_init();
    mat[11] = t;
    float *mat_f = mat3_multiply(mat, mat_o);
    for (int i = 0; i < 16; i++)
        mat_o[i] = mat_f[i];
    free(mat_f);
    free(mat);
}
