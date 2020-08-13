/*
** EPITECH PROJECT, 2019
** my_print_revalpha
** File description:
** hello
*/

void my_putchar(char);

void my_print_revalpha(void)
{
    int n = 25;

    while (n != -1){
        my_putchar(n + 97);
        n += -1;
    }
}
