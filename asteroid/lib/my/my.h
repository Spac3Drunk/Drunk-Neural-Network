/*
** EPITECH PROJECT, 2019
** my
** File description:
** Prototype all functions of libmy.a & define macros
*/

#ifndef _my_h_
#define _my_h_

typedef long unsigned int u64;
typedef unsigned int u32;

void my_putchar(char c);
//int my_isneg(int nb);
int my_put_nbr(int nb);
//void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src);
char my_revstr(char *str);
//char *my_strstr(char *str, char const *to_find);
char *my_strcat(char const *str1, char const *str2);
int my_strcmp(char const *s1, char const *s2);
//int my_strncmp(char const *s1, char const *s2, int n);
//char *my_strupcase(char *str);
//char *my_strlowcase(char *str);
//char *my_strcapitalize(char *str);
//int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
//int my_showstr(char const *str);
//char *my_strncat(char *dest, char const *src, int nb);
//int my_char_isnum(char c);
//int my_char_isalpha(char c);
//int my_show_word_array(char * const *tab);
//char **my_str_to_word_array(char const *str);
//int my_prime_copy(int nb);
//void rewrite_nbr(int nbr, long my_div);
//int get_str_len(char *str);
char *my_putnbr_base(int nbr, char const *base);
//char *concat_params_a(int ac, char **av);
//int get_len_dest(char *dest);
//int get_len_dest_c(char *dest);
//int my_strcmp2(char const *c);
char *my_strdup(char const *src);
//int get_my_len(char *str);
int my_find(char c, char *str);
int my_printf(char *str, ...);
int nmatch(char const *str, char const *reg_ex);



//matrice
float *mat3_init(void);
float *mat3_multiply(float *mat1, float *mat2);
float *mat3_init_x(float a);
float *mat3_init_y(float a);
float *mat3_init_z(float a);
float *mat3_init_scale(float s);
float *init_p(void);
float *mat3_point(float *mat, float *p);
float *mat3_copy(float *mat);

void mat3_rx(float *mat_o, float a);
void mat3_ry(float *mat_o, float a);
void mat3_rz(float *mat_o, float a);
void mat3_tx(float *mat_o, float t);
void mat3_ty(float *mat_o, float t);
void mat3_tz(float *mat_o, float t);

void mat3_ttx(float *mat_o, float t);
void mat3_tty(float *mat_o, float t);
void mat3_ttz(float *mat_o, float t);
void mat3_rrx(float *mat_o, float a);
void mat3_rry(float *mat_o, float a);
void mat3_rrz(float *mat_o, float a);

float *mat3_inv(float *mat);


//linked list (lld)
typedef struct lld
{
    void *data;
    struct lld *next;
    struct lld *prev;
} lld_t;

int lld_db(lld_t *lld);
void lld_free_r(lld_t *lld);
void lld_free(lld_t *lld);
lld_t *lld_init();
void lld_insert_node(lld_t *lld, int poss, lld_t *node);
void lld_insert(lld_t *lld, int pos, void *data);
int lld_len_db(lld_t *lld);
int lld_len(lld_t *lld);
void **lld_lld_to_tab(lld_t *lld);
void *lld_pop_node(lld_t *lld, int pos);
void *lld_pop(lld_t *lld, int pos);
void lld_print_int(lld_t *lld);
void lld_print_str(lld_t *lld);
void *lld_read(lld_t *lld, int poss);
void lld_sort(lld_t *list, int (*cmp)());
void *lld_write(lld_t *lld, int poss, void *data);
lld_t *lld_tab_to_lld(void **tab, int size);

//binary tree (btr)



typedef struct brs
{
    struct brs *brs;//if == 0 it's last
    struct brs *prev;//up in the tree
    void *data;// méeeh
    unsigned char branches;// nb of branches
    unsigned char depth; //how far we are in
} brs_t;

typedef struct btr
{
    int (*cmp)(void *);
    struct brs *brs;
    void *data;
    unsigned char branches;// nb of branches
} btr_t;

btr_t *btr_init(unsigned char size, int (*cmp)(void *));

//ucp
#ifndef _ucp_h_
#define _ucp_h_

#define IS_FLAG 0x8000000000000000
#define IS_SET(str) ((char *)((u64)str | (u64)0x8000000000000000))

int ucp(char *str, char *regex, ...);
char ***ucp_tab(char *str, char *regex, ...);
void ucp_free(char ***tab);

void *is_made1(char *str);
void *is_made2(char *str);
void *is_made3(char *str);
void *is_made4(char *str);
void *is_made5(char *str);


#endif


#endif
