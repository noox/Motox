
#include "bullets.h"

#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>

#include <list>
using namespace std;

#include "enemy.h"
#include "game.h"
#include "ball.h"
#include "particles.h"
#include "frand.h"

list<bullet> bullets;

//posun strely od casovy tik
bool bullet::update(float time) {
	//zmena polohy strely
	b.pos+=b.speed*time;

	//odpor prostredi
	b.speed*=powf(0.4,time);

	//gravitace
	b.speed.y-=time;

	//pro casovani chrleni partiklu
	reload+=time;

	while(reload>=0) {
		add_particle(b.pos,complex(DFRAND/4,DFRAND/4),0.5,0.5,0.3,0.05,3);
		reload-=0.001;
	}
	bool del=false;

	//pokud bullet koliduje, bude smazan
	if(collide_ball_with_walls(time,b)) {
		del=true;
		small_explosion(b.pos);
	}

	//pokud je bullet pryc z 'mapy', bude smazan
	if(out_of_map(b.pos)) del=true;

	//pokud zasahl nepritele, bude smazan
	if(try_to_damage_enemy(*this)) del=true;
	return del;
}

//funkce pro smazani vsech strel pri konci hry
void delete_bullets() {
	bullets.clear();
}

//funkce pro pridavani strel
void add_bullet(const complex& pos,const complex& speed,int dmg,int from) {
	bullets.push_back(bullet(pos,speed,dmg,from));
}

//funkce pro update vsech bulletu
void update_bullets(float time) {
	list<list<bullet>::iterator> todel;
	for(list<bullet>::iterator i=bullets.begin();i!=bullets.end();++i)
		if(i->update(time)) todel.push_back(i);
	//smazani nepotrebnych
	while(!todel.empty()) {
		bullets.erase(todel.front());
		todel.pop_front();
	}
}

