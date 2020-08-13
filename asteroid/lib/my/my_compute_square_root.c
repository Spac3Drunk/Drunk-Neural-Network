/*
** EPITECH PROJECT, 2019
** my_compute_power_root
** File description:
** hello
*/

int my_compute_square_root(int nb)
{
    int i;

    if (nb < 0)
        return (0);
    for (i = 0; i * i < nb; i++){
    }
    if (i * i != nb)
        return (0);
    return (i);
}
