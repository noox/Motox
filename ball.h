
#ifndef _BALL_H_
#define _BALL_H_

#include "complex.h"

class ball {
public:
	complex pos,speed;
	float rad,slip,rotspd;

	ball() {
	}

	ball(const complex& Pos,const complex& Speed,float Rad,float Slip,float Rotspd) {
		pos=Pos;
		speed=Speed;
		rad=Rad;
		slip=Slip;
		rotspd=Rotspd;
	}
	void update(float time);
};

#include "map.h"

int collision(float time,ball& b,wall& w);
void spring(float time,float dist,float power,ball& a,ball& b);

#endif

