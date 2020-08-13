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

void my_draw_square(framebuffer_t *buf, sfVector2u position, unsigned int size,
    sfColor color)
{
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++)
            my_put_pixel(buf, position.x+x, position.y+y, color);
}
