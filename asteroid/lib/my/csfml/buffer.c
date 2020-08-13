/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include <SFML/Graphics.h>
#include <string.h>
#include <stdlib.h>
#include "../my.h"
#include "../screen.h"

framebuffer_t *framebuffer_create(unsigned int width, unsigned int height)
{
    framebuffer_t *buf = malloc(sizeof(struct framebuffer));

    buf->width = width;
    buf->height = height;
    buf->pixels = malloc(width*height*sizeof(sfUint8)*4);
    memset(buf->pixels, 0, width*height*sizeof(sfUint8)*4);
    return (buf);
}

void framebuffer_destroy(framebuffer_t *framebuffer)
{
    free(framebuffer->pixels);
    free(framebuffer);
}

void my_put_pixel(framebuffer_t *framebuffer, int x, int y,
    sfColor color)
{
    if (x >= 0 && x < framebuffer->width && y >= 0 && y < framebuffer->height){
        framebuffer->pixels[(y*framebuffer->width + x)*4] = color.r;
        framebuffer->pixels[(y*framebuffer->width + x)*4 + 1] = color.g;
        framebuffer->pixels[(y*framebuffer->width + x)*4 + 2] = color.b;
        framebuffer->pixels[(y*framebuffer->width + x)*4 + 3] = color.a;
    }
}

void my_fill_buffer(framebuffer_t *buf, sfColor color)
{
    for (int x = 0; x < buf->width; x++)
        for (int y = 0; y < buf->height; y++)
            my_put_pixel(buf, x, y, color);
}

void my_blur_buffer(framebuffer_t *buf, float ratio)
{
    int len = buf->width*buf->height*sizeof(sfUint8)*4;

    for (int i = 0; i < len; i++)
        buf->pixels[i] *= ratio;
}
