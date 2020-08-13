/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include <unistd.h>

void lld_print_str(lld_t *lld)
{
    for (lld = lld->next; lld; lld = lld->next){
        write(1, lld->data, my_strlen(lld->data));
        write(1, " | ", 3);
    }
    write(1, "\n", 1);
}
