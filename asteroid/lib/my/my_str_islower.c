/*
** EPITECH PROJECT, 2019
** my_str_islower
** File description:
** hello
*/

int my_str_islower(char const *str)
{
    for (int i = 0; str[i] != 0; i++){
        if (!('a' <= str[i] && str[i] <= 'z')){
            return (0);
        }
    }
    return (1);
}
