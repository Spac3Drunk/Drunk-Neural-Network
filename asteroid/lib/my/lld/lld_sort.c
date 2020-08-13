/*
** EPITECH PROJECT, 2019
** my_sort_list
** File description:
** really bad sort
*/

#include <stdlib.h>
#include <stdio.h>
#include "../my.h"

void lld_sort(lld_t *list, int (*cmp)())
{
    int mv = 1;
    while (mv > 0){
        mv = 0;
        for (int i = 0; i < (long int)list->data - 1; i++){
            if ((*cmp)(lld_read(list, i), lld_read(list, i+1)) > 0){
                lld_insert_node(list, i+1, lld_pop_node(list, i));
                mv++;
            }
        }
    }
}
