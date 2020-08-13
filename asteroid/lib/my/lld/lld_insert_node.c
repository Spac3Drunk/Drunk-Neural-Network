/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include <stdlib.h>

void lld_insert_node_start(lld_t *lld, lld_t *tmp, void *pos)
{
    lld_t *lld_o = lld;
    lld->data += 1;
    for (void *i = 0; pos > i; lld = lld->next, i++);
    tmp->next = lld->next;
    if (pos)
        tmp->prev = lld;
    else
        tmp->prev = 0;
    lld->next = tmp;
    if (tmp->next != 0)
        tmp->next->prev = tmp;
    else
        lld_o->prev = tmp;
}

void lld_insert_node_end(lld_t *lld, lld_t *tmp, void *pos)
{
    lld_t *lld_o = lld;
    lld->data += 1;
    for (void *i = lld->data; pos < i; lld = lld->prev, i--);
    tmp->next = lld->next;
    if (pos)
        tmp->prev = lld;
    else
        tmp->prev = 0;
    lld->next = tmp;
    if (tmp->next != 0)
        tmp->next->prev = tmp;
    else
        lld_o->prev = tmp;
}

void lld_insert_node(lld_t *lld, int poss, lld_t *node)
{
    void *pos = (void *)(long int)poss;
    if ((long int)lld->data/2 >= (long int)pos)
        lld_insert_node_start(lld, node, pos);
    else
        lld_insert_node_end(lld, node, pos);
}
