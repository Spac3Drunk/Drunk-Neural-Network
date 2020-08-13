/*
** EPITECH PROJECT, 2019
** lld_to_tab
** File description:
** lld_t * -> void **
*/

#include "../my.h"
#include <stdlib.h>

void **lld_lld_to_tab(lld_t *lld)
{
    void **tab = malloc(sizeof(void *) * ((u64)lld->data + 1));
    tab[(u64)lld->data] = 0;
    int i = 0;
    for (lld = lld->next; lld; lld = lld->next, i++)
        tab[i] = lld->data;
    return (tab);
}
