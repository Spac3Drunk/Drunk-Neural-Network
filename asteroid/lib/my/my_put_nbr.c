/*
** EPITECH PROJECT, 2019
** my_put_nbr
** File description:
** Print a number in console
*/

void my_putchar(char c);

int my_put_nbr(long int nb)
{
    unsigned long int count = 1000000000000000000;
    int len = 0;

    while (nb / count == 0 && count > 1){
        count = count / 10;
    }
    while (count != 0){
        my_putchar(48 + nb / count);
        len++;
        nb -= (nb/count) * count;
        count = count / 10;
    }
    return (len);
}
