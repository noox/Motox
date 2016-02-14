
#include "particles.h"

#include <GL/gl.h>
#include <stdlib.h>

#include <list>
using namespace std;

#include "frand.h"

class particle {
public:
	//pozice a rychlost, zivotnost, soucasne stari, barvy, typ particlu
	complex pos,speed;
	float life,age,red,green,blue;
	int type;

	particle(const complex& Pos,const complex& Speed,float Life,float Red,float Green,float Blue,int Type) {
		pos=Pos;
		speed=Speed;
		life=Life;
		red=Red;
		green=Green;
		blue=Blue;
		type=Type;
		age=0;
	}

	bool update(float time);
	void draw();
};

//funkce pro posunuti a zestarnuti particlu
bool particle::update(float time) {
	pos+=speed*time;
	age+=time;
	bool del=false;
	if(age>life) del=true;
	return del;
}

//funkce pro vykresleni particlu podle jeho typu
void particle::draw() {
	switch(type) {
		case 1:
			glBegin(GL_LINES);
			glColor4f(red,green,blue,1-age/life);
			glVertex2fv(pos.v);
			glColor4f(0,0,0,0);
			glVertex2fv((pos-1.1*speed).v);
			glEnd();
			break;
		case 2:
			glBegin(GL_LINES);
			glColor4f(red,green,blue,1-age/life);
			glVertex2fv(pos.v);
			glColor4f(0,0,0,0);
			glVertex2fv((pos-0.1*speed).v);
			glEnd();
			break;
		case 3:
			glBegin(GL_TRIANGLE_FAN);
			glColor4f(red,green,blue,1-age/life);
			glVertex3fv(pos.v);
			glColor4f(0,0,0,0);
			glVertex2fv((pos+complex(0.05,0)).v);
			glVertex2fv((pos+complex(0,-0.05)).v);
			glVertex2fv((pos+complex(-0.05,0)).v);
			glVertex2fv((pos+complex(0,0.05)).v);
			glVertex2fv((pos+complex(0.05,0)).v);
			glEnd();
			break;
		default:
			break;
	}
}

list<particle> particles;

//funkce pro smazani particlu
void delete_particles() {
	particles.clear();
}

//funkce pro pridani particlu
void add_particle(const complex& pos,const complex& speed,float life,float red,float green,float blue,int type) {
	particles.push_back(particle(pos,speed,life,red,green,blue,type));
}

//funkce pro update vsech particlu
void update_particles(float time) {
	list<list<particle>::iterator> todel;
	for(list<particle>::iterator i=particles.begin();i!=particles.end();++i) {
		if(i->update(time)) todel.push_back(i);
	}
	//mazani starych particlu
	while(!todel.empty()) {
		particles.erase(todel.front());
		todel.pop_front();
	}
}

//funkce pro vykresleni vsech particlu
void draw_particles() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	for(list<particle>::iterator i=particles.begin();i!=particles.end();++i)
		i->draw();
	glDisable(GL_BLEND);
}

//mala exploze :D
void small_explosion(const complex& pos) {
	int i;
	for(i=0;i<160;++i)
		add_particle(pos,complex(DFRAND/3,DFRAND/3),2*FRAND,1,FRAND,0.1,1);
	for(i=0;i<115;++i)
		add_particle(pos+complex(DFRAND/10,DFRAND/10),complex(DFRAND/20,DFRAND/20),6*FRAND,0.5,0.5,0.5,3);
	for(i=0;i<160;++i)
		add_particle(pos,complex(DFRAND/5,DFRAND/5),2*FRAND,1,0.5*FRAND,0.1,3);
}

//velka exploze
void big_explosion(const complex& pos) {
	int i;
	for(i=0;i<160;++i)
		add_particle(pos,complex(DFRAND,DFRAND),2*FRAND,1,FRAND,0.1,1);
	for(i=0;i<110;++i)
		add_particle(pos,complex(DFRAND/5,DFRAND/5),3*FRAND,1,FRAND,0.5,2);
	for(i=0;i<115;++i)
		add_particle(pos+complex(DFRAND/5,DFRAND/5),complex(DFRAND,DFRAND),6*FRAND,0.5,0.5,0.5,3);
	for(i=0;i<160;++i)
		add_particle(pos,complex(DFRAND,DFRAND),2*FRAND,1,0.5*FRAND,0.1,3);
}

