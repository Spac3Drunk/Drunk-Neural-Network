/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** menu
*/

#include <stdlib.h>
#include <SFML/Graphics.h>
#include "../screen.h"
#include "../my.h"
#include "../menu.h"

win_t *my_win_init(win_t *up, int *pos_size)
{
    win_t *win = malloc(sizeof(win_t));
    char *char_win = (char *)win;
    for (int i = 0; i < sizeof(win_t); i++)
        char_win[i] = 0;
    win->on = 1;
    win->pos_size = pos_size;
    win->lld_win = lld_init();
    return (win);
}

int my_win_draw(framebuffer_t *buf, win_t *win)
{
    if (!win->on)
        return (0);
    my_draw_rect(buf, win->pos_size, win->color);
    lld_t *mov = win->lld_win;
    my_printf("ok\n");
    for (mov = mov->next; mov; mov = mov->next){
        my_printf("  ok\n");
        my_win_draw(buf, mov->data);
    }
}
