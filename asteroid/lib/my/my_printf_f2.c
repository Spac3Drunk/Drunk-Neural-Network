/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** print fonction
*/

#include <stdlib.h>
#include <stdarg.h>
#include "my.h"

int mod_mod(va_list va)
{
    my_putchar('%');
    va++;
    va--;
    return (1);
}

int mod_u(va_list va)
{
    int a = va_arg(va, int);

    return (my_put_nbr(a));
}

int mod_x(va_list va)
{
    long int nb = va_arg(va, int);
    int neg = 0;
    int len = 0;

    nb < 0 ? nb += 2147483648, neg = 1 : 0;
    char *str2 = my_putnbr_base(nb, "0123456789abcdef");
    neg == 1 ? str2[0] = 'f' : 0;
    len += my_strlen(str2);
    my_putstr(str2);
    free(str2);
    return (len);
}

int mod_xx(va_list va)
{
    long int nb = va_arg(va, int);
    int len = 0;
    int neg = 0;

    nb < 0 ? nb += 2147483648, neg = 1 : 0;
    char *str2 = my_putnbr_base(nb, "0123456789ABCDEF");
    neg == 1 ? str2[0] = 'F' : 0;
    len += my_strlen(str2);
    my_putstr(str2);
    free(str2);

    return (len);
}

int mod_o(va_list va)
{
    long int nb = va_arg(va, int);
    int neg = 0;
    int len = 0;

    nb < 0 ? nb += 2147483648, neg = 1 : 0;
    char *str2 = my_putnbr_base(nb, "01234567");
    len += my_strlen(str2);
    neg == 1 ? str2[0] = '3' : 0;
    my_putstr(str2);
    free(str2);
    return (len);
}
