/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** print fonction
*/

#include <stdarg.h>
#include <stdlib.h>

int my_find(char c, char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            return (i);
    return (-1);
}
