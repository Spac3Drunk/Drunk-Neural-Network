/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include <stdlib.h>

int lld_len_db(lld_t *lld)
{
    lld_t *lld_o = lld;
    lld_o->data = 0;
    for (lld = lld->next; lld; lld = lld->next, lld_o->data++);
    return ((long int)lld_o->data);
}
