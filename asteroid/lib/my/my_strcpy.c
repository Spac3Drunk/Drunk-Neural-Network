/*
** EPITECH PROJECT, 2019
** my_strcpy
** File description:
** hello
*/

char *my_strcpy(char *dest, char const *src)
{
    int ii;

    for (ii = 0; src[ii] != '\0'; ii++) {
        dest[ii] = src[ii];
    }
    dest[ii] = '\0';
    return (dest);
}
