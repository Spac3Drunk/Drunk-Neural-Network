/*
** EPITECH PROJECT, 2019
** my_is_prime
** File description:
** hello
*/

int my_is_primea(int nb)
{
    if (nb <= 1)
        return (0);
    for (int i = 2; i < nb; i++)
        if (nb % i == 0)
            return (0);
    return (1);
}

int my_find_prime_sup(int nb)
{
    if (nb < 0)
        return (0);
    for (; 1; nb++)
        if (my_is_primea(nb) == 1)
            return (nb);
}
