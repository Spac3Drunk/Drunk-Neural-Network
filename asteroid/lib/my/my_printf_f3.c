/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** print fonction
*/

#include <stdarg.h>
#include <stdlib.h>
#include "my.h"

int mod_p(va_list va)
{
    long int nb = va_arg(va, long int);
    int len = 2;

    my_putstr("0x");
    char *str2 = my_putnbr_base(nb, "0123456789abcdef");
    len += my_strlen(str2);
    my_putstr(str2);
    free(str2);
    return (len);
}

int mod_b(va_list va)
{
    long int nb = va_arg(va, long int);
    int len = 2;

    char *str2 = my_putnbr_base(nb, "01");
    len += my_strlen(str2);
    my_putstr(str2);
    free(str2);
    return (len);
}
