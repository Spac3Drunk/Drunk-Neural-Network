/*
** EPITECH PROJECT, 2019
** my_getnbr
** File description:
** hello
*/

int my_getnbr(const char *str)
{
    int i = 0;
    long int nbr = 0;
    int moin = 0;

    for (i = i; str[i] != '\0' && (str[i] < 48 || str[i] > 58) ; i++)
        if (str[i] == '-')
            moin += 1;
    for (i = i; str[i] != '\0' && (str[i] > 47 && str[i] < 59); i++){
        nbr *= 10;
        nbr += (str[i] - '0');
        if (nbr > 2147483648)
            return (0);
    }
    if (moin % 2 == 1)
        nbr = -nbr;
    if (nbr >= 2147483648 || nbr < -2147483648)
        return (0);
    return (nbr);
}
