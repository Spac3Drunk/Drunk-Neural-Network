/*
** EPITECH PROJECT, 2019
** tab_to_lld
** File description:
** void ** -> lld_t *
*/

#include "../my.h"
#include <stdlib.h>

lld_t *lld_tab_to_lld(void **tab, int size)
{
    lld_t *lld = lld_init();
    if (size != -1){
        for (int i = 0; i < size; i++)
            lld_insert(lld, (u64)lld->data, tab[i]);
    } else {
        for (int i = 0; tab[i]; i++)
            lld_insert(lld, (u64)lld->data, tab[i]);
    }
    return (lld);
}
