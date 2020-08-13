/*
** EPITECH PROJECT, 2019
** my_strdu
** File description:
** hello
*/

#include <stdlib.h>

int my_strlen(const char *);

char *my_strdup(char const *scr)
{
    char *dest;
    int len = my_strlen(scr);
    int i;

    dest = malloc(sizeof(char) * (len+1));
    for (i = 0; scr[i] != '\0'; i++)
        dest[i] = scr[i];
    dest[i] = '\0';
    return (dest);
}
