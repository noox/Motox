
#include "enemy.h"

#include <stdlib.h>
#include <GL/gl.h>
#include <math.h>

#include <iostream>
#include <list>
using namespace std;

#include "ball.h"
#include "map.h"
#include "bullets.h"
#include "particles.h"

class enemy {
public:
	ball b;
	int hp,maxhp;
	
	enemy(const complex& Pos,const complex& Speed,float Rad,int Hp) {
		b.pos=Pos;
		b.speed=Speed;
		b.rad=Rad;
		hp=Hp;
		maxhp=Hp;
		b.slip=0.1;
		b.rotspd=0;
	}
	bool update(float time);
	void draw();
};

//update nepritele
bool enemy::update(float time) {
	//zmena polohy
	b.pos+=b.speed*time;

	//odpor prostredi
	b.speed*=powf(0.6,time);

	//gravitace
	b.speed.y-=1.8*time;

	collide_ball_with_walls(time,b);

	bool del=false;
	//pokud je mimo 'mapu', bude smazan
	if(out_of_map(b.pos)) 
		del=true;
	return del;
}

//nakresleni nepritele
void enemy::draw() {
	float t=(float)hp/(float)maxhp;
	glPushMatrix();
	glTranslatef(b.pos.x,b.pos.y,0);
	glBegin(GL_LINE_LOOP);

	//nepratele tmavnou, kdyz ztraci hp
	glColor3f(0.5+t*0.5,0.3*(1-t),0.3*(1-t));

	//zakladni tvar nepritele - cervena kruznice
	for(int i=0;i<360;++i)
		glVertex2f(cos(i*M_PI/180)*b.rad,sin(i*M_PI/180)*b.rad);
	glEnd();
	glPopMatrix();
}

list<enemy> enemies;

//funkce pro smazani vsechn nepratel
void delete_enemies() {
	enemies.clear();
}

//funkce pro pridani nepratel do listu
void add_enemy(const complex& pos,const complex& speed,float rad,int hp) {
	enemies.push_back(enemy(pos,speed,rad,hp));
}

//posun nepratel o casovy tik
void move_enemies(float time) {
	list<list<enemy>::iterator> todel;
	for(list<enemy>::iterator i=enemies.begin();i!=enemies.end();++i) {
		if(i->update(time)) todel.push_back(i);
	}
	//mazani nepotrebnych
	while(!todel.empty()) {
		enemies.erase(todel.front());
		todel.pop_front();
	}
}

//kresleni vsech nepratel
void draw_enemies() {
	for(list<enemy>::iterator i=enemies.begin();i!=enemies.end();++i)
		i->draw();
}

//zkousi vsechny nepratele proti vsem strelam na kolizi
int try_to_damage_enemy(bullet& bull) {
	int hit=0;
	list<list<enemy>::iterator> todel;
	for(list<enemy>::iterator i=enemies.begin();i!=enemies.end();++i) {
		
		//kdyz vzdalenost mezi nimi je mensi nez soucet velikosti
		if((i->b.pos-bull.b.pos).length()<(i->b.rad+bull.b.rad)) {
			i->hp-=bull.dmg;

			if(i->hp<=0) {
				//exploze nepritele
				big_explosion(i->b.pos);
				//pro smazani
				todel.push_back(i);
			}
			//zasah
			hit++;
		}
	}
	//mazani nepotrebnych
	while(!todel.empty()) {
		enemies.erase(todel.front());
		todel.pop_front();
	}
	//nepritel nezasazen
	return hit;
}

//zjistuje kolizi konkretniho kolecka se vsemi neprateli
int ball_touches_enemy(ball& b) {
	for(list<enemy>::iterator i=enemies.begin();i!=enemies.end();++i) 
		if((i->b.pos-b.pos).length()<=(i->b.rad+b.rad)) 
			return 1;
	return 0;
}

//vraci pocet zbylych nepratel ve hre
int enemies_left() {
	return enemies.size();
}
