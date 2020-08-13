/*
** EPITECH PROJECT, 2019
** my_str_isprintable
** File description:
** hello
*/

int my_str_isprintable(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++){
        if (!(33 <= str[i] && str[i] <= 126)){
            return (0);
        }
    }
    return (1);
}
