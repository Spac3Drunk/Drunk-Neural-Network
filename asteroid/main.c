#include "include/my.h"
#include "include/screen.h"
#include "include/menu.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <math.h>
#include <SFML/Window/Export.h>
#include <SFML/Window/Keyboard.h>
#include "include/evolve.h"
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>

#define WINDOW_SIZE 1024
#define PI 3.14159265358979323846
#define max(x, y) (x < y ? y : x)
#define min(x, y) (x < y ? x : y)

typedef long int i64;

typedef struct asteroid
{
    float x, y;
    float vx, vy;
    float size;
} as_as;

typedef struct gen_tree
{
    char c;
    char r;
    char g;
    char b;
    struct gen_tree **child;
} as_gen_tree;

typedef struct player
{
    float x, y;
    float vx, vy;
    float a;
    int load;
    struct learning *AI;
    float score;
    float turning_power;
    float forward_power;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    float mem[32];
    as_gen_tree *gen_tree;
} as_player;

typedef struct proj
{
    float x, y;
    float vx, vy;
    int life;
    int player;
} as_proj;

typedef struct game
{
    as_player *player;
    lld_t *as;
    lld_t *proj;
    lld_t *lld_tmp;
} as_game;

int draw_gen_tree(as_gen_tree *root, float x, float y, framebuffer_t *fb, sfVector2i *pl)
{
    static float size = 6;
    static char returning = 0;
    static sfColor alive_c[] = {100, 100, 100, 255};
    static sfColor alive_child_c[] = {160, 160, 160, 255};
    //if (x > WINDOW_SIZE || y > WINDOW_SIZE)
    //    return (y);
    static float xe = 0;
    static float ye = 0;
    static float xo = WINDOW_SIZE/2;
    static float yo = WINDOW_SIZE/2;
    static float focus = 0;
    if (x == -1 && y == -1){
        x = WINDOW_SIZE/2 + xo - xe;
        y = WINDOW_SIZE/2 + yo - ye;
        x = x*0.03+xo*0.97;
        y = y*0.03+yo*0.97;
        xo = x;
        yo = y;
        pl->x = x;
        pl->y = y;
        xe = 0;
        focus = 0;
    }
    if ((root->c && root->child[0]) || (!root->c && lld_len(root->child))){

        returning = 0;
        sfVector2i p[] = {x, y};
        int child_nb = 0;

        if (root->c)
            for (int i = 0; root->child[i]; i++)
                root->child[i]->c == 0 ? child_nb++ : 0;
        else {
            lld_t *mv = root->child;
            for (mv = mv->next; mv; mv = mv->next)
            ((as_gen_tree *)mv->data)->c == 0 ? child_nb++ : 0;
        }
        //amputate tree for better performance
        if (child_nb == 0 && root->c == 1){
            int p = 0;
            for (int i = 0; root->child[i]; i++)
                if (root->child[i]->child[0])
                    root->child[p++] = root->child[i];
            root->child[p] = 0;
            root->c = 1;
        }
        if (focus < child_nb){
            focus = child_nb;
            xe = x;
            ye = y;
        }

        if (x > 0 && y < WINDOW_SIZE && y > 0 && x < WINDOW_SIZE){

            int tab[] = {(int)(x-size*2), (int)(y-size*2), (int)(size*4), (int)(size*4)};



            if (root->c)
                my_draw_rect(fb, tab, sfBlack);
            else
                my_draw_rect(fb, tab, *alive_c);
            tab[1] += size/3;
            tab[3] -= size/3*2;
            tab[0] += tab[2];
            tab[2] = child_nb;
            my_draw_rect(fb, tab, *alive_child_c);

            my_draw_line2(fb, pl, p, sfWhite);

            sfVector2i p1[] = {cos(0 - 135/180.0*PI)*size + x, sin(0 - 135/180.0*PI)*size + y};
            sfVector2i p2[] = {cos(0)*size + x, sin(0)*size + y};
            sfVector2i p3[] = {cos(0 + 135/180.0*PI)*size + x, sin(0 + 135/180.0*PI)*size + y};
            sfVector2i p4[] = {cos(0 - 135/180.0*PI)*size*2 + x, sin(0 - 135/180.0*PI)*size*2 + y};
            sfVector2i p5[] = {cos(0)*size*2 + x, sin(0)*size*2 + y};
            sfVector2i p6[] = {cos(0 + 135/180.0*PI)*size*2 + x, sin(0 + 135/180.0*PI)*size*2 + y};
            sfVector2i *lines[7] = {p1, p2, p3, p4, p5, p6, p1};

            sfColor color[] = {root->r, root->g, root->b, 255};
            my_draw_lines(fb, lines, 7, *color);
        }
        if (root->c)
            for (int i = 0; root->child[i]; i++)
                y = draw_gen_tree(root->child[i], x+size*8, y, fb, p);
        else {
            lld_t *mv = root->child;
            for (mv = mv->next; mv; mv = mv->next)
                y = draw_gen_tree(mv->data, x+size*8, y, fb, p);
        }


        if (!returning){
            y += size*3.5;
            returning = 1;
        }
    }
    return (y);
}

void add_asteroid(as_game *game, float size)
{
    as_as *as = malloc(sizeof(as_as));
    int r = rand()%(WINDOW_SIZE*2);
    as->x = 0;
    as->y = 0;
    if (r < WINDOW_SIZE)
        as->x = r;
    else
        as->y = r - WINDOW_SIZE;
    as->vx = ((rand()%100)/100.0-0.5)*5;
    as->vy = ((rand()%100)/100.0-0.5)*5;
    as->size = rand()%100;
    lld_insert(game->as, 0, as);
}

void db_as(as_game *game)
{
    printf("x       y       vx      vy      size\n");
    for (lld_t *mv = game->as->next; mv; mv = mv->next){
        as_as *as = (as_as *)mv->data;
        printf("%#+-03.f  %#+-03.f  %#+-03.f  %#+-03.f  %#+-03.f\n", as->x, as->y, as->vx, as->vy, as->size);
    }
}

float *raycasts(as_game *game, as_player *pl, framebuffer_t *fb, as_player *best, int frame, int skip)
{
    int view_d = WINDOW_SIZE/2;
    int rays = 16;
    static float *out = 0; out == 0 ? out = malloc(sizeof(int)*(rays*2+32)) : 0;

    for (int a = 0; a < rays; a++){
        float rx = cos(pl->a + a*1.0/rays*PI);
        float ry = sin(pl->a + a*1.0/rays*PI);

        for (lld_t *mv = game->as->next; mv; mv = mv->next){
            as_as *as = (as_as *)mv->data;
            float dx = pl->x - as->x;
            float dy = pl->y - as->y;
            float as_x = as->x;
            float as_y = as->y;
            if (dx > WINDOW_SIZE/2)
                as_x += WINDOW_SIZE;
            else if (dx < -WINDOW_SIZE/2)
                as_x -= WINDOW_SIZE;

            if (dy > WINDOW_SIZE/2)
                as_y += WINDOW_SIZE;
            else if (dy < -WINDOW_SIZE/2)
                as_y -= WINDOW_SIZE;

            float a = (pow(rx, 2) + pow(ry, 2)); //(r1² + r2²);
            float b = (rx*(pl->x-as_x) + ry*(pl->y-as_y))*2; //((r1*(x1-x0) + r2*(y1-y0))*2);
            float c = -(pow(as->size, 2) - pow(pl->x-as_x, 2) - pow(pl->y-as_y, 2)); //- (d² - (x1-x0)² - (y1-y0)²);
            float d = pow(b, 2) - 4*a*c;
            if (d < 0)
                continue;
            lld_insert(game->lld_tmp, 0, (void *)(i64)((-b-pow(d, 0.5)) / (2*a)));
            lld_insert(game->lld_tmp, 0, (void *)(i64)((-b+pow(d, 0.5)) / (2*a)));
        }
        int tmax = view_d;
        int tmin = -view_d;
        for (lld_t *mv = game->lld_tmp->next; mv; mv = mv->next){
            if ((i64)mv->data > 0 && (i64)mv->data < tmax)
                tmax = (i64)mv->data;
            if ((i64)mv->data < 0 && (i64)mv->data > tmin)
                tmin = (i64)mv->data;
        }


        while (game->lld_tmp->data)
            lld_pop(game->lld_tmp, 0);

        out[a] = view_d-tmin;
        out[a+rays] = view_d+tmax;
        if (pl == best && !(frame % skip) && 0){
            sfVector2i pos1 = {pl->x + tmin * rx, pl->y + tmin * ry};
            sfVector2i pos2 = {pl->x + tmax * rx, pl->y + tmax * ry};
            sfColor color = {122, 122, 122, 255};
            my_draw_line(fb, &pos1, &pos2, color);
            my_draw_circle(fb, pos1, 5, &sfGreen);
            my_draw_circle(fb, pos2, 5, &sfGreen);
        }
    }

    memcpy(out+32, &pl->mem, sizeof(float)*32);
    memcpy(&pl->mem, out, sizeof(float)*32);
    return (out);
}

//int nb_players = 512;
int nb_players = 512;

int skip = 2;
//int skip = 1;

int main(int ac, char **av, char **env)
{
    //srand(time(0));
    as_game game[1];

    game->player = malloc(sizeof(as_player)*(nb_players+1));

    game->as = lld_init();
    game->proj = lld_init();
    game->lld_tmp = lld_init();

    //create root of gen_tree
    as_gen_tree *root = malloc(sizeof(as_gen_tree));
    root->child = lld_init();
    root->r = 255;
    root->g = 255;
    root->b = 255;
    root->c = 0;

    int levels[] = {64, 32, 32, 32, 0};

    lld_t *tree_compil = lld_init();

    for (int i = 0; i < nb_players; i++){

        if (1){
            game->player[i].AI = learning_init(levels);
            learning_evolve(game->player[i].AI, 1, 0.1);
        }else {
            printf("loading...\n");
            int fd = open("save.eve", O_RDONLY);
            if (fd == -1)
                printf("load fail\n"), exit(84);
            game->player[i].AI = learning_read(fd);
            close(fd);
        }

        game->player[i].x = rand()%WINDOW_SIZE;
        game->player[i].y = rand()%WINDOW_SIZE;
        game->player[i].vx = 0;
        game->player[i].vy = 0;
        game->player[i].a = rand()%WINDOW_SIZE;
        game->player[i].score = 0;
        game->player[i].turning_power = 0;
        game->player[i].forward_power = 0;
        game->player[i].load = 1;
        game->player[i].r = rand()%128 + 64;
        game->player[i].g = rand()%128 + 64;
        game->player[i].b = rand()%128 + 64;
        memset(game->player[i].mem, 0, sizeof(float)*32);

        game->player[i].gen_tree = malloc(sizeof(as_gen_tree));
        game->player[i].gen_tree->child = lld_init();
        game->player[i].gen_tree->r = game->player[i].r;
        game->player[i].gen_tree->g = game->player[i].g;
        game->player[i].gen_tree->b = game->player[i].b;
        game->player[i].gen_tree->c = 0;
        lld_insert(root->child, 0, game->player[i].gen_tree);
    }
    {
        //compile root gen_tree
        float *tab = lld_lld_to_tab(root->child);
        lld_free(root->child);
        root->child = tab;
        root->c = 1;
    }

    lld_t *lld_dead = lld_init();
    float accuracy = 0;
    framebuffer_t *fb;
    while (1){
        int alive = nb_players;

        for (int frame = 0; alive; frame++){

            if (!(frame % 15) && game->as->data < 25)
                add_asteroid(game, 1);

            if (!(frame % skip)){
                //draw gen_tree
                if (frame){
                    sfVector2i p1[] = {0, 0};
                    draw_gen_tree(root, -1, -1, fb, p1);

                }
                //
                fb = draw();
                //my_blur_buffer(fb, 0.95);
                my_fill_buffer(fb, sfBlack);
            }

            //draw as
            for (lld_t *mv = game->as->next; mv; mv = mv->next){
                as_as *as = (as_as *)mv->data;
                sfVector2i pos = {as->x, as->y};
                if (!(frame % skip))
                    my_draw_circle(fb, pos, as->size, &sfRed);
            }

            as_player *players = game->player;

            as_player *best;
            int max = 0;
            float tot_score = 0;
            as_gen_tree *gen_tree_b;
            for (int i = 0; i < nb_players; i++){
                tot_score += players[i].score;
                if (players[i].score >= max){
                    max = players[i].score;
                    best = &players[i];
                    gen_tree_b = best->gen_tree;
                }
            }
            if (!(frame % 60))
                printf("best %f moy %f acc %f\n", best->score, tot_score/nb_players, accuracy);

            //save network
            if (!(frame % 6000)){
                printf("SAVING...\n");
                int fd = open("save.eve", O_WRONLY | O_TRUNC | O_CREAT, 0644);
                if (fd == -1){
                    printf("save faild\n");
                    continue;
                }
                learning_write(fd, best->AI);
                close(fd);
                printf("saved\n");
            }

            for (int i = 0; i < nb_players; i++){
                //if (players[i].score == 1)
                //    continue;

                //draw player
                if (!(frame % skip)){

                    sfVector2i p1[] = {cos(players[i].a - 135/180.0*PI)*10 + players[i].x, sin(players[i].a - 135/180.0*PI)*10 + players[i].y};
                    sfVector2i p2[] = {cos(players[i].a)*10 + players[i].x, sin(players[i].a)*10 + players[i].y};
                    sfVector2i p3[] = {cos(players[i].a + 135/180.0*PI)*10 + players[i].x, sin(players[i].a + 135/180.0*PI)*10 + players[i].y};
                    sfVector2i p4[] = {cos(players[i].a - 135/180.0*PI)*20 + players[i].x, sin(players[i].a - 135/180.0*PI)*20 + players[i].y};
                    sfVector2i p5[] = {cos(players[i].a)*20 + players[i].x, sin(players[i].a)*20 + players[i].y};
                    sfVector2i p6[] = {cos(players[i].a + 135/180.0*PI)*20 + players[i].x, sin(players[i].a + 135/180.0*PI)*20 + players[i].y};
                    sfVector2i *lines[7] = {p1, p2, p3, p4, p5, p6, p1};

                    //printf("%i\n", lines[0]->x);
                    float ratio = max(players[i].score*1.0/max, 0.2);
                    sfColor color[] = {ratio*players[i].r, ratio*players[i].g, ratio*players[i].b, 255};
                    my_draw_lines(fb, lines, 7, *color);

                }
                //players[i].score++;
                players[i].x += players[i].vx;
                players[i].y += players[i].vy;
                players[i].vx *= 0;
                players[i].vy *= 0;
                players[i].x < 0 ? players[i].x += WINDOW_SIZE : 0;
                players[i].x > WINDOW_SIZE ? players[i].x -= WINDOW_SIZE : 0;
                players[i].y < 0 ? players[i].y += WINDOW_SIZE : 0;
                players[i].y > WINDOW_SIZE ? players[i].y -= WINDOW_SIZE : 0;
                //players[i].a += 0.01;


                //input
                float *action = learning_run(players[i].AI, raycasts(game, &players[i], fb, best, frame, skip));


                //players[i].forward_power = 1 + players[i].forward_power * 0.9;
                players[i].forward_power = 1000 + players[i].forward_power * 0.9;

                float move = action[0] - action[1];

                if (fabsf(move) > players[i].forward_power)
                    if (move > 0)
                        move = players[i].forward_power;
                    else
                        move = -players[i].forward_power;

                if (move < 0)
                    move /= 100;
                players[i].forward_power -= fabsf(move);
                players[i].vx += cos(players[i].a)*move*10;
                players[i].vy += sin(players[i].a)*move*10;


                players[i].turning_power = 0.5 + players[i].turning_power * 0.9;
                //players[i].turning_power = 10 + players[i].turning_power * 0.9;

                float turn = action[2] - action[3];
                if (fabsf(turn) > players[i].turning_power)
                    if (turn > 0)
                        turn = players[i].turning_power;
                    else
                        turn = -players[i].turning_power;

                players[i].turning_power -= fabsf(turn);

                players[i].a += turn;

                players[i].score -= fabsf(turn)*100;
                players[i].score += fabsf(players[i].vx);
                players[i].score += fabsf(players[i].vy);

                //players[i].score += players[i].vx;
                //players[i].score *= 0.995;

                players[i].load += 1/300;

                for (lld_t *mv = game->as->next; mv; mv = mv->next){
                    as_as *as = (as_as *)mv->data;
                    float dx = ((int)as->x - (int)players[i].x);
                    float dy = ((int)as->y - (int)players[i].y);

                    if (dx > WINDOW_SIZE/2)
                        dx -= WINDOW_SIZE;
                    else if (dx < -WINDOW_SIZE/2)
                        dx += WINDOW_SIZE;

                    if (dy > WINDOW_SIZE/2)
                        dy -= WINDOW_SIZE;
                    else if (dy < -WINDOW_SIZE/2)
                        dy += WINDOW_SIZE;


                    if (dx*dx + dy*dy < as->size*as->size){


                        //add to the best
                        best->score *= 0.999;

                        float factor = (rand()%1000)/1000.0;

                        learning_copy(players[i].AI, best->AI);
                        learning_evolve(players[i].AI, factor, factor/10);
                        players[i].x = rand()%WINDOW_SIZE;
                        players[i].y = rand()%WINDOW_SIZE;
                        players[i].vx = 0;
                        players[i].vy = 0;
                        players[i].a = 0;
                        players[i].load = 1;
                        players[i].score = 0;
                        players[i].turning_power = 0;
                        players[i].forward_power = 0;
                        players[i].a = (rand()%1000/3.14);
                        players[i].r = (unsigned char)min(max(best->r + ((rand() % 10000)-5000)/100.0*factor, 0), 255);
                        players[i].g = (unsigned char)min(max(best->g + ((rand() % 10000)-5000)/100.0*factor, 0), 255);
                        players[i].b = (unsigned char)min(max(best->b + ((rand() % 10000)-5000)/100.0*factor, 0), 255);
                        memset(game->player[i].mem, 0, sizeof(float)*32);


                        //create new tree_node
                        lld_insert(tree_compil, 0, players[i].gen_tree);
                        players[i].gen_tree = malloc(sizeof(as_gen_tree));
                        players[i].gen_tree->child = lld_init();
                        players[i].gen_tree->r = players[i].r;
                        players[i].gen_tree->g = players[i].g;
                        players[i].gen_tree->b = players[i].b;
                        players[i].gen_tree->c = 0;
                        lld_insert(gen_tree_b->child, lld_len(best->gen_tree->child), players[i].gen_tree);
                        break;
                    }
                }
            }
            //compile tree_nodes
            while (tree_compil->data){
                as_gen_tree *tmp = lld_pop(tree_compil, 0);
                float *tab = lld_lld_to_tab(tmp->child);
                lld_free(tmp->child);
                tmp->child = tab;
                tmp->c = 1;
            }

            //destroy OBJ
            int n = 0;
            for (lld_t *mv = game->proj->next; mv; mv = mv->next){
                as_proj *proj = (as_proj *)mv->data;
                if (proj->life < 0){
                    if (proj->life <= -10){
                        accuracy += 1.0/nb_players;
                        players[proj->player].load += 1.2;
                        players[proj->player].score += 300;
                    }
                    lld_insert(game->lld_tmp, 0, (void *)(i64)n);
                }
                n++;
            }


            while (game->lld_tmp->data)
                free(lld_pop(game->proj, (u64)lld_pop(game->lld_tmp, 0)));

            n = 0;
            for (lld_t *mv = game->as->next; mv; mv = mv->next){
                as_as *as = (as_as *)mv->data;
                if (as->size < 20){
                    lld_insert(game->lld_tmp, 0, (void *)(i64)n);
                }
                n++;
            }
            while (game->lld_tmp->data)
                free(lld_pop(game->as, (u64)lld_pop(game->lld_tmp, 0)));


            //physique step proj
            for (lld_t *mv = game->proj->next; mv; mv = mv->next){
                as_proj *proj = (as_proj *)mv->data;
                sfVector2i pos1[] = {proj->x, proj->y};
                sfVector2i pos2[] = {proj->x + proj->vx, proj->y + proj->vy};
                if (!(frame % skip))
                    my_draw_line(fb, pos1, pos2, sfGreen);
                proj->life--;
                proj->x += proj->vx;
                proj->y += proj->vy;
                proj->x < 0 ? proj->x += WINDOW_SIZE : 0;
                proj->x > WINDOW_SIZE ? proj->x -= WINDOW_SIZE : 0;
                proj->y < 0 ? proj->y += WINDOW_SIZE : 0;
                proj->y > WINDOW_SIZE ? proj->y -= WINDOW_SIZE : 0;

                //collision detection
                for (lld_t *mv = game->as->next; mv; mv = mv->next){
                    as_as *as = (as_as *)mv->data;
                    float dx = as->x - proj->x;
                    float dy = as->y - proj->y;

                    if (dx*dx + dy*dy < as->size*as->size){
                        proj->life = -10;
                        as->size = pow(as->size*as->size/2, 0.5);
                        as_as *as2 = malloc(sizeof(as_as));
                        memcpy(as2, as, sizeof(as_as));
                        float vx = rand()%200/100.0-1;
                        float vy = rand()%200/100.0-1;
                        as2->vx += vx;
                        as2->vy += vy;
                        as->vx -= vx;
                        as->vy -= vy;
                        lld_insert(game->as, 0, as2);
                        break;
                    }
                }
            }

            //physique step as
            for (lld_t *mv = game->as->next; mv; mv = mv->next){
                as_as *as = (as_as *)mv->data;
                as->x += as->vx;
                as->y += as->vy;
                //colllision with roof/floor...
                as->x < 0 ? as->x += WINDOW_SIZE : 0;
                as->x > WINDOW_SIZE ? as->x -= WINDOW_SIZE : 0;
                as->y < 0 ? as->y += WINDOW_SIZE : 0;
                as->y > WINDOW_SIZE ? as->y -= WINDOW_SIZE : 0;

                //collision between player / asteroid

                //player vison & AI
            }




        }
        printf("5\n");
        /*
        //end of the bach
        while (game->as->data)
            free(lld_pop(game->as, 0));
        printf("4\n");

        while (game->proj->data)
            free(lld_pop(game->proj, 0));
            printf("3\n");

        as_player *winner = lld_pop(lld_dead, 0);
        while (lld_dead->data)
            lld_pop(lld_dead, 0);
        printf("2\n");

        for (int i = 0; i < nb_players; i++)
            learning_copy(game->player[i].AI, winner->AI);
        printf("1\n");
        for (int i = 0; i < nb_players; i++){
            learning_evolve(game->player[i].AI, i*1.0/nb_players, i*.1/nb_players);

            game->player[i].x = WINDOW_SIZE/2;
            game->player[i].y = WINDOW_SIZE/2;
            game->player[i].vx = 0;
            game->player[i].vy = 0;
            game->player[i].a = 0;
            game->player[i].score = 0;
            game->player[i].turning_power = 0;
            game->player[i].forward_power = 0;
            */
    }
    lld_free(lld_dead);
    lld_free_r(game->as);
    lld_free(game->proj);
    lld_free(game->lld_tmp);
}
