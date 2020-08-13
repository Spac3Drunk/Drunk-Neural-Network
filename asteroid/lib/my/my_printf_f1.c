/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** print fonction
*/

#include <stdarg.h>
#include <stdlib.h>
#include "my.h"

int mod_d(va_list va)
{
    long int nb = va_arg(va, int);
    int neg = 0;

    nb < 0 ? nb *= -1, neg = 1, my_putchar('-') : 0;
    char *str = my_putnbr_base(nb, "0123456789");
    int len = my_putstr(str);
    free(str);
    return (len+neg);
}

int mod_i(va_list va)
{
    long int nb = va_arg(va, int);
    char *str = my_putnbr_base(nb, "0123456789");
    int len = my_putstr(str);
    free(str);
    return (len);
}

int mod_s(va_list va)
{
    char *str = va_arg(va, char *);
    if (str == 0) return (0);
    return (my_putstr(str));
}

int mod_ss(va_list va)
{
    int len = 0;
    char *str = va_arg(va, char *);
    if (str == 0) return (0);

    for (int i = 0; str[i]; i++){
        if (32 <= str[i] && str[i] <= 126){
            my_putchar(str[i]);
            len++;
        } else {
            my_putchar('\\');
            long int nb = str[i];
            char *str2 = my_putnbr_base(nb, "01234567");
            for (int i = 2; str2[i] == 0; i--)
                my_putchar('0');
            my_putstr(str2);
            free(str2);
            len += 4;
        }
    }
    return (len);
}

int mod_c(va_list va)
{
    my_putchar((char)va_arg(va, int));
    return (1);
}
