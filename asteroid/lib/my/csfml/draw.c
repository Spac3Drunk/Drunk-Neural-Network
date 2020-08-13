/*
** EPITECH PROJECT, 2019
** my_compute_power_it
** File description:
** hello
*/

#include <SFML/Graphics.h>
#include "../screen.h"
#include "../my.h"

framebuffer_t *draw(void)
{
    static sfVideoMode mode = {1024, 1024, 32};
    static sfSprite *sprite = 0; !sprite ? sprite = sfSprite_create() : 0;
    static sfTexture *texture = 0;
    !texture ? texture = sfTexture_create(mode.width, mode.height) : 0;
    static framebuffer_t *fb = 0;
    !fb ? fb = framebuffer_create(mode.width, mode.height) : 0;
    static sfRenderWindow *window = 0;
    !window ? window = sfRenderWindow_create(mode, "hi", sfClose, 0) : 0;
    static char first = 0;
    for (; !first; first = 1){
        sfRenderWindow_setFramerateLimit(window, 30);
        sfSprite_setTexture(sprite, texture, sfTrue);
    }
    sfTexture_updateFromPixels(texture, fb->pixels, mode.width,
    mode.height, 0, 0);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, sprite, 0);
    sfRenderWindow_display(window);
    return (fb);
}
