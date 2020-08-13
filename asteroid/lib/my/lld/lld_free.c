/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include <unistd.h>
#include <stdlib.h>

void lld_free(lld_t *lld)
{
    lld_t *lld_n = lld->next;
    for (; lld_n; lld = lld_n, lld_n = lld_n->next)
        free(lld);
    free(lld);
}
