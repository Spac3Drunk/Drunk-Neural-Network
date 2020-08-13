/*
** EPITECH PROJECT, 2019
** ucp (universal_c_parseur)
** File description:
** main file for ucp
*/

#include "../my.h"

void *is_made1(char *str)
{
    static char *list = 0;
    if ((u64)str & (u64)IS_FLAG){
        list = (char *)((u64)str & (u64)~IS_FLAG);
        return (is_made1);
    }
    for (; *str; str++){
        for (int i = 0; ; i++){
            if (list[i] == *str) break;
            if (list[i] == 0) return (0);
        }
    }
    return ((void *) 1);
}

void *is_made2(char *str)
{
    static char *list = 0;
    if ((u64)str & (u64)IS_FLAG){
        list = (char *)((u64)str & (u64)~IS_FLAG);
        return (is_made2);
    }
    for (; *str; str++){
        for (int i = 0; ; i++){
            if (list[i] == *str) break;
            if (list[i] == 0) return (0);
        }
    }
    return ((void *) 1);
}

void *is_made3(char *str)
{
    static char *list = 0;
    if ((u64)str & (u64)IS_FLAG){
        list = (char *)((u64)str & (u64)~IS_FLAG);
        return (is_made3);
    }
    for (; *str; str++){
        for (int i = 0; ; i++){
            if (list[i] == *str) break;
            if (list[i] == 0) return (0);
        }
    }
    return ((void *) 1);
}

void *is_made4(char *str)
{
    static char *list = 0;
    if ((u64)str & (u64)IS_FLAG){
        list = (char *)((u64)str & (u64)~IS_FLAG);
        return (is_made4);
    }
    for (; *str; str++){
        for (int i = 0; ; i++){
            if (list[i] == *str) break;
            if (list[i] == 0) return (0);
        }
    }
    return ((void *) 1);
}

void *is_made5(char *str)
{
    static char *list = 0;
    if ((u64)str & (u64)IS_FLAG){
        list = (char *)((u64)str & (u64)~IS_FLAG);
        return (is_made5);
    }
    for (; *str; str++){
        for (int i = 0; ; i++){
            if (list[i] == *str) break;
            if (list[i] == 0) return (0);
        }
    }
    return ((void *) 1);
}
