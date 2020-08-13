/*
** EPITECH PROJECT, 2019
** match
** File description:
** hello
*/

int find_reg3(char const *str, char const *reg_ex, int str_p, int reg_p)
{
    int total = 0;
    int i;

    if (reg_ex[reg_p] == '*'){
        for (i = 0; str[i+str_p]; i++)
            total += find_reg3(str, reg_ex, str_p+i, reg_p+1);
        total += find_reg3(str, reg_ex, str_p+i, reg_p+1);
    } else {
        while (reg_ex[reg_p] == str[str_p]){
            if (!reg_ex[reg_p] && !str[str_p])
                return (1);
            reg_p++;
            str_p++;
        }
        if (reg_ex[reg_p] == '*')
            total += find_reg3(str, reg_ex, str_p, reg_p);
    }
    return (total);
}

int nmatch(char const *str, char const *reg_ex)
{
    return (find_reg3(str, reg_ex, 0, 0));
}
