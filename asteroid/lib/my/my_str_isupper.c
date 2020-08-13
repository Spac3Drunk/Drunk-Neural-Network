/*
** EPITECH PROJECT, 2019
** my_str_isupper
** File description:
** hello
*/

int my_str_isupper(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++){
        if (!('A' <= str[i] && str[i] <= 'Z')){
            return (0);
        }
    }
    return (1);
}
