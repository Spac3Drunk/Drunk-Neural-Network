/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

int my_compute_power_rec(int nb, int p)
{
    long int result = nb;

    if (p == 0)
        return (1);
    if (p < 0)
        return (0);
    for (int i = 1; i < p; i++){
        result *= nb;
        if (result >= 2147483648 || result < -2147483648)
            return (0);
        }
    return (result);
}
