
#ifndef _BULLETS_H_
#define _BULLETS_H_

#include "ball.h"

class bullet {
public:
	ball b;
	//pozice, rychlost, sila strely, pratelskost;
	int dmg,from;
	float reload;

	bullet() {
	}

	bullet(const complex& Pos,const complex& Speed,int Dmg,int From) {
		b=ball(Pos,Speed,0.05,0,0);
		dmg=Dmg;
		from=From;
		reload=0;
	}
	bool update(float time);
};

void delete_bullets();
void add_bullet(const complex& pos,const complex& speed,int dmg,int from);
void update_bullets(float time);

#endif

