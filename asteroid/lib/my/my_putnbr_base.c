/*
** EPITECH PROJECT, 2019
** my_putnbr_base
** File description:
** hello
*/

#include <string.h>
#include <stdlib.h>

int my_strlen(char const *str);

char *my_putnbr_base(long int nbr, char *base)
{
    int len = my_strlen(base);
    int i;
    char *to_print = malloc(64);
    char *to_print2 = malloc(64);

    nbr < 0 ? nbr += 256 : 0;
    for (int i = 0; i < 64; to_print[i] = 0, to_print2[i] = 0, i++);
    for (len = 0; base[len]; len++);
    for (i = 0; nbr != 0; i++){
        to_print[i] = base[nbr%len];
        nbr /= len;
    }
    int a = 0;
    for (i = i-1; i >= 0; i--, a++)
        to_print2[a] = to_print[i];
    to_print2[0] == 0 ? to_print2[0] = base[0] : 0;
    free(to_print);
    return (to_print2);
}
