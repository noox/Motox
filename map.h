
#ifndef _MAP_H_
#define _MAP_H_

#include "complex.h"

class wall {
public:
	complex p1,p2;

	wall(const complex& P1,const complex& P2) {
		p1=P1;
		p2=P2;
	}
};

void add_wall(const complex& p1,const complex& p2);
void draw_map();

#include "ball.h"

int collide_ball_with_walls(float time,ball& b);
int out_of_map(const complex& pos);
void delete_walls();
float map_bottom();

#endif

