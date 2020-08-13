/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include <stdlib.h>
#include <math.h>
#include "../my.h"

// 0  1  2  3
// 4  5  6  7
// 8  9 10 11
//12 13 14 15

float mat3_calc_pivot(float *mat)
{
    float pivot = 0;

    for (int y = 0; y < 3; y++){
        pivot += mat[y%3]*mat[(y+1)%3+4]*mat[(y+2)%3+8];
        pivot -= mat[8+y%3]*mat[4+(y+1)%3]*mat[0+(y+2)%3];
    }
    return (pivot);
}

float *mat3_inv(float *mat)
{
    float pivot = 1 / mat3_calc_pivot(mat);
    float *mat_inv = mat3_init();

    for (int y = 0; y < 3; y++){
        for (int x = 0; x < 3; x++){
            mat_inv[y+x*4] = (mat[(x+1)%3+(y+1)%3*4]*mat[(x+2)%3+(y+2)%3*4] -
            mat[(x+2)%3+(y+1)%3*4]*mat[(x+1)%3+(y+2)%3*4])*pivot;
        }
    }
    return (mat_inv);
}
