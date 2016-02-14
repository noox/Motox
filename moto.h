
#include "complex.h"

void init_moto();
void draw_moto();
void update_moto(float time,int key_up,int key_down,int key_left,int key_right,int key_space,int key_shoot);
void get_moto_position(complex& a);
int moto_out_of_map();
int moto_touches_enemy();

