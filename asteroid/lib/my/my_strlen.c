/*
** EPITECH PROJECT, 2019
** my_strlen
** File description:
** hello
*/

int my_strlen(char const *str)
{
    int i;

    for (i = 0; str[i]; i++);
    return (i);
}
