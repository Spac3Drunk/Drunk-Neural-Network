/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include <SFML/Graphics.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../my.h"
#include "../screen.h"

void my_draw_rect(framebuffer_t *buf, int *pos_size, sfColor color)
{
    for (int x = 0; x < pos_size[2]; x++)
        for (int y = 0; y < pos_size[3]; y++)
            my_put_pixel(buf, (pos_size[0]+x)%1024, (pos_size[1]+y)%1024, color);
}
