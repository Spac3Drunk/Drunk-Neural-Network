/*
** EPITECH PROJECT, 2019
** get_nextline
** File description:
** Main for print
*/

#include <fcntl.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char *get_str(ll_t *l_b, int size)
{
    static int p_p = 0;
    char *str = malloc(size * READ_SIZE+1); if (str == 0) return (0);
    int str_p = 0;
    while (1){
        if (p_p >= READ_SIZE){
            p_p = 0;
            ll_t *tmp_free = l_b->next;
            l_b->next = l_b->next->next;
            free(tmp_free->data), free(tmp_free);
        }
        if (l_b->next->data[p_p] == '\n'){
            p_p++;
            break;
        }
        str[str_p] = l_b->next->data[p_p];
        p_p++, str_p++;
    }
    str[str_p] = 0;
    return (str);
}

char *get_next_line(int fd)
{
    if (READ_SIZE <= 0 || fd < 0) return (0);
    static ll_t *l_b = 0; l_b == 0 ? l_b = malloc(sizeof(ll_t)) : 0;
    if (l_b == 0) return (0);
    static ll_t *l_m = 0; l_m == 0 ? l_m = l_b : 0;
    static int n_count = 0;
    int size_m = 1;
    while (n_count <= 0){
        size_m++;
        l_m->next = malloc(sizeof(ll_t)); if (!l_m->next) return (0);
        l_m = l_m->next;
        l_m->data = malloc(READ_SIZE+1); if (!l_m->data) return (0);
        int size = read(fd, l_m->data, READ_SIZE);
        if (size <= 0) return (0);
        l_m->data[size] = 0;
        for (int i = 0; i < size; i++)
            l_m->data[i] == '\n' ? n_count++ : 0;
    }
    l_m->next = 0;
    n_count -= 1;
    return (get_str(l_b, size_m));
}
