/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include <unistd.h>
#include <stdlib.h>

void lld_free_r(lld_t *lld)
{
    lld_t *mov = lld->next;

    free(lld);
    if (mov){
        for (; mov->next; mov = mov->next)
            free(mov->prev->data), free(mov->prev);
        free(mov->data);
    }
    free(mov);
}
