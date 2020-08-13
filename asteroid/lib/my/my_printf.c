/*
** EPITECH PROJECT, 2019
** my_printf
** File description:
** Main for print
*/

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int mod_d(va_list va);
int mod_i(va_list va);
int mod_ss(va_list va);
int mod_s(va_list va);
int mod_c(va_list va);
int mod_mod(va_list va);
int mod_u(va_list va);
int mod_x(va_list va);
int mod_xx(va_list va);
int mod_o(va_list va);
int mod_p(va_list va);
int mod_b(va_list va);
int my_find(char c, char *str);

int my_printf(char *str, ...)
{
    char ta[] = {"diSsc%uxXopb\0"};
    int(*fonc[])(va_list) = {&mod_d, &mod_i, &mod_ss, &mod_s, &mod_c, &mod_mod,
    &mod_u, &mod_x, &mod_xx, &mod_o, &mod_p, &mod_b, 0};
    va_list va;
    va_start(va, str);
    int len = 0;
    int ok = 0;
    for (int str_p = 0; str[str_p]; str_p++){
        if (str[str_p] == '%'){
            for (str_p++; my_find(str[str_p], ta) == -1 && str[str_p]; str_p++);
            for (int i = 0; ta[i]; i++)
                ta[i] == str[str_p] ? len += fonc[i](va), ok = 1 : 0;
            ok == 0 ? write(1, "%", 1), len++ : 1, ok = 0;
        } else {
            write(1, &str[str_p], 1);
            len++;
        }
    }
    va_end(va);
    return (len);
}
