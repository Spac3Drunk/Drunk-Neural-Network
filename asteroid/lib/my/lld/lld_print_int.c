/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include "../my.h"
#include <unistd.h>

void lld_print_int(lld_t *lld)
{
    for (lld = lld->next; lld; lld = lld->next){
        my_put_nbr((long int)lld->data);
        write(1, " ", 1);
    }
    write(1, "\n", 1);
}
