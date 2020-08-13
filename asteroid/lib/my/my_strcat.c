/*
** EPITECH PROJECT, 2019
** my_str_islower
** File description:
** hello
*/

#include <stdlib.h>

int my_strlen(char const *str);

char *my_strcat(char const *str1, char const *str2)
{
    char *str3 = malloc(sizeof(char) * (my_strlen(str1) + my_strlen(str2)+1));
    int x = 0;

    for (int i = 0; str1[i]; i++, x++) str3[x] = str1[i];
    for (int i = 0; str2[i]; i++, x++) str3[x] = str2[i];
    str3[x] = 0;
    return (str3);
}
