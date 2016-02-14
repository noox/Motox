
#include "moto.h"

#include <GL/gl.h>
#include <math.h>

#include <vector>
using namespace std;

#include "ball.h"
#include "bullets.h"
#include "map.h"
#include "enemy.h"
#include "particles.h"

static float reload=0,spacehit=0;

vector<ball> b;

void init_moto() {
	b.resize(3);

	//ovladane kolecko
	b[0].pos.x=-0.25;
	b[0].pos.y=-0.4;
	b[0].speed.x=0;
	b[0].speed.y=0;
	b[0].rad=0.12;
	b[0].slip=1; //klouzavost
	b[0].rotspd=0; //rotacni rychlost
	
	//druhe kolecko
	b[1].pos.x=0.25;
	b[1].pos.y=-0.4;
	b[1].speed.x=0;
	b[1].speed.y=0;
	b[1].rad=0.12;
	b[1].slip=0;
	b[1].rotspd=0;
	
	//hlavicka
	b[2].pos.x=0;
	b[2].pos.y=0;
	b[2].speed.x=0;
	b[2].speed.y=0;
	b[2].rad=0.1;
	b[2].slip=0.0001;
	b[2].rotspd=0;

	reload=0;
}

//funkce pro nakresleni motorky
void draw_moto() {
	//kolecka motorky
	for(int i=0;i<3;++i) {
		glPushMatrix();
		glTranslatef(b[i].pos.x,b[i].pos.y,0);
		if(i!=2) glColor3f(1,1,1);
		else glColor3f(1,1,0.3);
		glBegin(GL_LINE_LOOP);
		int j;
		for(j=0;j<360;++j)
			glVertex2f(cos(j*M_PI/180)*b[i].rad,sin(j*M_PI/180)*b[i].rad);
		//dvojity obtah kolecek
		if(i!=2)
			for(j=0;j<360;++j)
				glVertex2f(cos(j*M_PI/180)*(b[i].rad-0.02),sin(j*M_PI/180)*(b[i].rad-0.02));
				
		glEnd();
		glPopMatrix();
	}

	//vektory bazickeho prostoru motorky
	complex v1,v2;
	v1=b[1].pos-b[0].pos;
	v2=b[2].pos-b[0].pos;

	//nakresleni tela motorky a prevedeni do jine baze
	#define motovertex(px,py) glVertex2f(b[0].pos.x+(px)*v1.x+(py)*v2.x,b[0].pos.y+(px)*v1.y+(py)*v2.y)
	glColor3f(0.3,0.3,1);
	glBegin(GL_LINE_LOOP);
		motovertex(0,0);
		motovertex(0.55,0);
		motovertex(0.85,0.5);
		motovertex(0.6,0.35);
		motovertex(1,0);
		motovertex(0.7,0.4);
		motovertex(0.45,0.7);
		motovertex(0.65,0.66);
		motovertex(0.65,0.74);
		motovertex(0.45,0.7);
		motovertex(0.58,0.37);
		motovertex(0.65,0.35);
		motovertex(0.25,0.35);
		motovertex(0.15,0.45);
		motovertex(-0.4,0.4);
		motovertex(0.07,0.3);
		motovertex(0.35,0);
		motovertex(0,0);
	glEnd();

	//..a nakresleni panacka - ridice
	glColor3f(0.3,1,0.3);
	glBegin(GL_LINE_LOOP);
		motovertex(0.06,0.32);
		motovertex(-0.1,0.72);
		motovertex(0,0.95);
		motovertex(0.2,0.7);
		motovertex(0.45,0.65);
		motovertex(0.2,0.7);
		motovertex(0.06,0.32);
		motovertex(0.27,0.3);
		motovertex(0.29,0.06);
		motovertex(0.27,0.3);
		motovertex(0.06,0.32);
	glEnd();
	#undef motovertex
}

//funkce pro 'posunuti hlavicky (a ostatnich)' podle ovladani balancovani
void rotate(ball& rb,ball& a1,ball& a2,float s,float time) {
	complex t;
	float tt;
	t=(a1.pos+a2.pos)/2;
	t=rb.pos-t;
	tt=t.y;
	t.y=t.x;
	t.x=-tt;
	rb.speed+=t*time*s;
}

//funkce na aktualizaci motorky ve hre a ovladani 
void update_moto(float time,int key_up,int key_down,int key_left,int key_right,int key_space,int key_shoot) {
	complex t,v,w;
	for(vector<ball>::iterator i=b.begin();i!=b.end();++i) {
		//pricteni rychlosti v case
		i->pos+=i->speed*time;

		//odpor prostredi
		i->speed*=powf(0.6,time);

		//gravitace
		i->speed.y-=1.8*time;
	}

	//ovladani
	ball tt;
	if(key_space) {
		if(!spacehit) {
			tt=b[0]; b[0]=b[1]; b[1]=tt;
			spacehit=1;
		}
	} else spacehit=0;
	
	if(key_left) {
		rotate(b[2],b[0],b[1],10,time);
		rotate(b[0],b[1],b[2],10,time);
		rotate(b[1],b[0],b[2],10,time);
	}
	if(key_right) {
		rotate(b[2],b[0],b[1],-10,time);
		rotate(b[0],b[1],b[2],-10,time);
		rotate(b[1],b[0],b[2],-10,time);
	}
	if(key_down) {
		b[0].rotspd=0;
		b[1].rotspd=0;
		b[0].slip=0.0001;
		b[1].slip=0.0001;
	} else {
		b[0].slip=1;
		b[1].slip=1;
	}
	if(key_up) {
		//rozpoznavani smeru natoceni motorky
		v=b[1].pos-b[0].pos;
		w=b[2].pos-b[0].pos;
		if(((v.x*w.y)-(v.y*w.x))>0) 
			b[0].rotspd=3;
		else b[0].rotspd=-3;
		b[0].slip=0.0001;
	} else {
		b[0].rotspd=0;
		b[0].slip=1;
	}
	
	reload+=time;

	if(key_shoot) {
		while(reload>=0) {
			add_bullet((b[1].pos+b[2].pos)/2+complex(0,0.09),(b[1].pos-b[0].pos)*10,10,0);
			reload-=0.2;
		}
	} else if(reload>0) reload=0;

	//pruzinovita souvislost mezi koly
	//(cas, distance, power, kolecko1, kolecko2)
	spring(time,0.5,1000,b[0],b[1]);
	spring(time,0.5,1000,b[0],b[2]);
	spring(time,0.5,1000,b[1],b[2]);

	for(vector<ball>::iterator i=b.begin();i!=b.end();++i)
		collide_ball_with_walls(time,*i);
}

//zjisti souradnice tela motorky
void get_moto_position(complex& a) {
	a=(b[0].pos+b[1].pos+b[2].pos)/3;
}

//funkce na zjisteni, zda je motorka 'mimo mapu'
int moto_out_of_map() {
	if (map_bottom()-10>b[2].pos.y) return 1;
	return 0;
}

//funkce na zjisteni, zda se nekolidovalo s neprateli
int moto_touches_enemy() {
	for(vector<ball>::iterator i=b.begin();i!=b.end();++i)
		if (ball_touches_enemy(*i)) {
			big_explosion((b[0].pos+b[1].pos+b[2].pos)/3);
			return 1;
		}
	return 0;
}

