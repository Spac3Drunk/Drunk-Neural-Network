/*
** EPITECH PROJECT, 2019
** my
** File description:
** Prototype all functions of libmy.a & define macros
*/

//csfml
#include "my.h"
#include "screen.h"
#include <SFML/Graphics.h>

#ifndef _menu_h_
#define _menu_h_

typedef struct win
{
    char on;
    // 0 or 1
    int *pos_size;
    //{posx, posy, sizex, sizey}
    void *(*exe)(struct win *win, float x, float y);
    // if exe == 0 transfer to children
    sfTexture *texture;
    // if != 0
    sfSprite *sprite;
    //if != 0
    sfColor color;
    //if !texture || !sprite menu use color
    lld_t *lld_win;
    //table of sub win // end with 0
} win_t;

win_t *my_win_init(win_t *up, int *pos_size);
int my_win_draw(framebuffer_t *buf, win_t *win);

#endif
