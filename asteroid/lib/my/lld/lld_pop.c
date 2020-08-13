/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include <stdlib.h>
#include <unistd.h>

void *lld_pop_start(lld_t *lld, void *pos)
{
    if (pos >= lld->data) write(2, "db lld pop < 0\n", 21);
    lld_t *lld_o = lld;
    lld->data -= 1;
    lld = lld->next;
    for (void *i = 0; pos > i; lld = lld->next, i++);
    if (lld->prev)
        lld->prev->next = lld->next;
    else
        lld_o->next = lld->next;
    if (lld->next)
        lld->next->prev = lld->prev;
    else
        lld_o->prev = lld->prev;
    void *data = lld->data;
    free(lld);
    return (data);
}

void *lld_pop_end(lld_t *lld, void *pos)
{
    if (pos >= lld->data) write(2, "db lld pop >= lld->data\n", 21);
    lld_t *lld_o = lld;
    lld->data -= 1;
    lld = lld->prev;
    for (void *i = lld_o->data; pos < i; lld = lld->prev, i--);
    if (lld->prev)
        lld->prev->next = lld->next;
    else
        lld_o->next = lld->next;
    if (lld->next)
        lld->next->prev = lld->prev;
    else
        lld_o->prev = lld->prev;
    void *data = lld->data;
    free(lld);
    return (data);
}

void *lld_pop(lld_t *lld, int poss)
{
    void *pos = (void *)(long int)poss;
    if ((long int)lld->data/2 >= (long int)pos){
        lld = lld_pop_start(lld, pos);
    } else {
        lld = lld_pop_end(lld, pos);
    }
    return (lld);
}
