/*
** EPITECH PROJECT, 2019
** ucp (universal_c_parseur)
** File description:
** main file for ucp
*/

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "../my.h"

lld_t *ucp_get_recursiv(char **str, int (**fonc)(char *));

void ucp_get_recursiv2(char **str, int (**fonc)(char *), lld_t *lld_split)
{
    int i = 0;
    do {
        str[1][i] = 0;
        if (fonc[0](str[1])){
            lld_insert(lld_split, (u64)lld_split->data, my_strdup(str[1]));
            str[1][i] = str[0][i];
            char *str2[3] = {str[0]+i, str[1]+i, str[2]+1};
            ucp_get_recursiv(str2, fonc+1);
            char *data = lld_pop(lld_split, (u64)lld_split->data-1);
            (u64)data & (u64)IS_FLAG ? 0 : free(data);
        } else
            str[1][i] = str[0][i];
    } while (str[0][i++]);
}

lld_t *ucp_get_recursiv(char **str, int (**fonc)(char *))
{
    static lld_t *lld_split = 0; !lld_split ? lld_split = lld_init() : 0;
    static lld_t *soluce = 0;
    (u64)fonc[0] == (u64) - 1 ? soluce = lld_init(), fonc++ : 0;
    if (*str[2] == '*'){
        ucp_get_recursiv2(str, fonc, lld_split);
    } else {
        while (*str[2] == *str[0]){
            if (!*str[2] && !*str[0]){
                for (lld_t *mv = lld_split->next; mv; mv = mv->next)
                    mv->data = (void *)((u64)mv->data | (u64)IS_FLAG);
                lld_insert(soluce, (u64)soluce, lld_lld_to_tab(lld_split));
                return (soluce);
            }
            str[2]++, str[0]++, str[1]++;
        }
        *str[2] == '*' ? ucp_get_recursiv(str, fonc) : 0;
    }
    return (soluce);
}

char ***ucp_tab(char *str, char *regex, ...)
{
    va_list va;
    lld_t *lld_fonc = lld_init();
    lld_insert(lld_fonc, 0, (void *)-1);
    char *buf = my_strdup(str);
    va_start(va, regex);
    for (int i = 0; regex[i]; i++)
        if (regex[i] == '*')
            lld_insert(lld_fonc, (u64)lld_fonc->data, va_arg(va, void *));
    int (**fonc)(char *) = (void *)lld_lld_to_tab(lld_fonc);
    lld_free(lld_fonc);
    char *str2[3] = {str, buf, regex};
    lld_t *lld = ucp_get_recursiv(str2, fonc);
    char ***tab = (char ***)lld_lld_to_tab(lld);
    lld_free(lld), free(buf), free(fonc);
    for (int i = 0; tab[i]; i++)
        for (int j = 0; tab[i][j]; j++)
            tab[i][j] = (char *)((u64)tab[i][j] & ~IS_FLAG);
    return (tab);
}

void ucp_free(char ***tab)
{
    for (int i = 0; tab[i]; i++){
        for (int j = 0; tab[i][j]; j++){
            if (tab[i+1] == 0 || tab[i][j] != tab[i+1][j])
                free(tab[i][j]);
        }
        free(tab[i]);
    }
    free(tab);
}
