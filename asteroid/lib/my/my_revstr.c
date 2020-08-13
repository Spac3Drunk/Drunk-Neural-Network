/*
** EPITECH PROJECT, 2019
** my_revstr
** File description:
** hello
*/

char *my_revstr(char *str)
{
    int i;
    int temp;

    for (i = 0; str[i] != '\0'; i++){
    }
    i -= 1;
    for (int n = 0; n <= i / 2; n++){
        temp = str[n];
        str[n] = str[i - n];
        str[i - n] = temp;
    }
    return (str);
}
