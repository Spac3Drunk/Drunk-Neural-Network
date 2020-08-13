/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include <stdlib.h>

int lld_db(lld_t *lld)
{
    lld_t *lld_o = lld;
    lld_t *lld_l = lld;
    void *len = 0;
    for (lld = lld->next; lld; lld = lld->next, len++)
        if (len > lld_o->data) return (2);
    if (len != lld_o->data) return (1);
    lld = lld_o;
    if (lld->next == 0 && lld->prev == 0) return (0);
    int db_nb = 0;
    lld = lld->next, lld_l = lld_l->next;
    for (lld = lld->next; lld; lld_l = lld, lld = lld->next, db_nb++){
        if (lld != lld_l->next) return (-db_nb-1);
        if (lld->prev != lld_l) return (-db_nb-1);
    }
    return (0);
}
