/*
** EPITECH PROJECT, 2019
** my_strncpy
** File description:
** hello
*/

char *my_strncpy(char *dest, char const *scr, int n)
{
    int len = 0;

    for (len = len; scr[len] != '\0'; len++){
    }
    for (int i = 0; i < n; i++)
        dest[i] = scr[i];
    if (n > len)
        dest[n] = '\0';
    return (dest);
}
