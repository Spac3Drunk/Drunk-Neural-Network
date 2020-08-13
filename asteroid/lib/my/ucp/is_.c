/*
** EPITECH PROJECT, 2019
** ucp (universal_c_parseur)
** File description:
** main file for ucp
*/

int is_space(char *str)
{
    for (; *str == ' '; str++);
    return (!*str);
}

int is_num(char *str)
{
    for (; *str >= '0' && *str <= '9'; str++);
    return (!*str);
}

int is_printable(char *str)
{
    for (; *str >= 33 && *str <= 126; str++);
    return (!*str);
}

int is_alphabet(char *str)
{
    for (; (*str >= 'A' && *str <= 'Z') ||
    (*str >= 'a' && *str <= 'z'); str++);
    return (!*str);
}
