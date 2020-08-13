/*
** EPITECH PROJECT, 2019
** my_print_alpha
** File description:
** hello
*/

void my_putchar(char);

void my_print_alpha(void)
{
    int n = 0;

    while (n != 26){
        my_putchar(n + 97);
        n += 1;
    }
}
