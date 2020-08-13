/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include <stdlib.h>

btr_t *btr_init(unsigned char branches, int (*cmp)(void *))
{
    btr_t *btr = malloc(sizeof(btr_t));
    btr->branches = branches;
    btr->brs = 0;
    btr->cmp = cmp;
    return (btr);
}
