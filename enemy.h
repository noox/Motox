
#include "ball.h"
#include "bullets.h"

void delete_enemies();
void add_enemy(const complex& pos,const complex& speed,float rad,int hp);
void move_enemies(float time);
void draw_enemies();
int try_to_damage_enemy(bullet& bull);
int enemies_left();
int ball_touches_enemy(ball& b);

