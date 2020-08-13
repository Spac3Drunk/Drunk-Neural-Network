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

void my_draw_circle(framebuffer_t *buf, sfVector2i position, unsigned int size,
    sfColor *color)
{
    double max = pow((double)size, 2);
    for (int x = 0; x <= size; x++){
        double size_x = pow((double)x-size, 2);
        int y = 0;
        for (; (size_x + pow((double)y-size, 2)) > max; y++);
        for (; y <= size; y++){
            my_put_pixel(buf, (position.x-size + x)%buf->width,
            (position.y-size + y)%buf->height, *color);
            my_put_pixel(buf, (position.x+size - x)%buf->width,
            (position.y-size + y)%buf->height, *color);
            my_put_pixel(buf, (position.x-size + x)%buf->width,
            (position.y+size - y)%buf->height, *color);
            my_put_pixel(buf, (position.x+size - x)%buf->width,
            (position.y+size - y)%buf->height, *color);
        }
    }
}
