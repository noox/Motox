
#include "map.h"

#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
#include <list>
using namespace std;

#include "ball.h"

list<wall> walls;
static float bleft=0,bright=0,btop=0,bbottom=0;

//funkce pro smazani vsech sten
void delete_walls() {
	walls.clear();
}

//funkce pro pridani zdi do listu
void add_wall(const complex& p1,const complex& p2) {
	walls.push_back(wall(p1,p2));
	
	//upgrade borderu, pro detekci smrti apod.
	if(p1.x<bleft) bleft=p1.x;
	if(p2.x<bleft) bleft=p2.x;
	if(p1.x>bright) bright=p1.x;
	if(p2.x>bright) bright=p2.x;
	if(p1.y<bbottom) bbottom=p1.y;
	if(p2.y<bbottom) bbottom=p2.y;
	if(p1.y>btop) btop=p1.y;
	if(p2.y>btop) btop=p2.y;
}

//nakresleni mapy
void draw_map() {
	glPushMatrix();
	glColor3f(0.2,0.2,0.2);
	glBegin(GL_LINES);
	for(list<wall>::iterator i=walls.begin();i!=walls.end();++i) {
		glVertex2fv(i->p1.v);
		glVertex2fv(i->p2.v);
	}
	glEnd();
	glPopMatrix();
}

//funkce pro reseni kolize kola s mapou
int collide_ball_with_walls(float time,ball& b) {
	int r;
	for(list<wall>::iterator i=walls.begin();i!=walls.end();++i)
		r+=collision(time,b,*i);
	return r;
}

//funkce pro zjisteni, zda jsou souradnice 'mimo mapu'
int out_of_map(const complex& pos) {
	if(pos.x<bleft-5) return 1;
	if(pos.x>bright+5) return 1;
	if(pos.y<bbottom-5) return 1;
	if(pos.y>btop+5) return 1;
	return 0;
}

//funkce na zjisteni 'spodku' mapy
float map_bottom() {
	return bbottom;
}

