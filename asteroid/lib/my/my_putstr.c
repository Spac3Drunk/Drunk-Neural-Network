/*
** EPITECH PROJECT, 2019
** my_putstr
** File description:
** hello
*/

#include "my.h"

int my_putstr(char const *str)
{
    int len = 0;

    for (int i = 0; str[i] != '\0'; i++){
        my_putchar(str[i]);
        len++;
    }
    return (len);
}
