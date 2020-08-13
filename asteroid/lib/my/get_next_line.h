/*
** EPITECH PROJECT, 2019
** get_nextline
** File description:
** Main for print
*/

#ifndef READ_SIZE
#define READ_SIZE (1)
#endif

char *get_next_line(int fd);

typedef struct ll{
    struct ll *next;
    char *data;
} ll_t;
