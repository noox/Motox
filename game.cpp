
#include "game.h"

#include <GL/gl.h>
#include <math.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "main.h"
#include "ball.h"
#include "map.h"
#include "moto.h"
#include "enemy.h"
#include "bullets.h"
#include "particles.h"
#include "text.h"
#include "maplist.h"

complex cam;
float gametime;
static int gamestatus=0,spacehit,uphit,downhit,eschit,mapchosen=0;

//funkce pro cteni mapy ze souboru
void read_map_file(const string& fn) {
	fstream f(fn.c_str(),fstream::in);
	char c;
	string line;

	while(getline(f,line,'\n')) {
		stringstream ss(line);
		ss>>c;
		//cteni sten
		if(c=='w') {
			complex p1,p2;
			ss>>p1.x>>p1.y>>p2.x>>p2.y;
			add_wall(p1,p2);
		//cteni nepratel
		} else if(c=='e') {
			complex pos,speed;
			float rad;
			int hp;
			ss>>pos.x>>pos.y>>speed.x>>speed.y>>rad>>hp;
			add_enemy(pos,speed,rad,hp);
		}
	}

	f.close();
}

//funkce pro nacteni vybrane mapy
void init_map() {
	read_map_file(maplist_get_file_name(mapchosen));
}

//funkce pro deinicializaci vsech modulu
void clear_game() {
	delete_enemies();
	delete_bullets();
	delete_particles();
	delete_walls();
}

//resetovaci funkce na zacatku levelu
void reset_game() {
	clear_game();
	gametime=0;
	init_moto();
	init_map();
	get_moto_position(cam);
}

//inicializacni funkce pri zacatku hry
void init_game() {
	maplist_init();
//	reset_game();
}

//funkce pro kresleni hry 
void draw_game() {
	string m,m1,m2;
	char b[1024];
	if (gamestatus!=0) {
		glTranslatef(-cam.x,-cam.y,0);
		if (gamestatus!=3) draw_moto();
		draw_map();
		draw_enemies();
		draw_particles();
	}
	
	glLoadIdentity();
	
	switch (gamestatus) {
		case 0:
			//nacteni nazvu map pro posuvne menu
			m=maplist_get_name(mapchosen);
			if (mapchosen>0) m1=maplist_get_name(mapchosen-1);
			else m1[0]=0;
			if (mapchosen<(maplist_count()-1)) m2=maplist_get_name(mapchosen+1);
			else m2[0]=0;
			
			//kresleni uvodniho screenu
			glPushMatrix();
				glColor3f(0, 1, 0);
				glTranslatef(-text_length("MoToX")/2,1.7,0);
				draw_string("MoToX");
				glColor3f(0.3, 0.3, 1);
				glTranslatef(0.03, 0.03, 0);
				draw_string("MoToX");
			glPopMatrix();
			glPushMatrix();
				glColor3f(0, 1, 0);
				glScalef(0.3,0.3,0);
				glTranslatef(-text_length(m1.c_str())/2,3.5,0);
				draw_string(m1.c_str());
			glPopMatrix();
			glPushMatrix();
				glColor3f(0.3, 0.3, 1);
				glScalef(0.3,0.3,0);
				glTranslatef(-text_length(m.c_str())/2,2.5,0);
				draw_string(m.c_str());
			glPopMatrix();
			glPushMatrix();
				glColor3f(0, 1, 0);
				glScalef(0.3,0.3,0);
				glTranslatef(-text_length(m2.c_str())/2,1.5,0);
				draw_string(m2.c_str());
			glPopMatrix();
			glPushMatrix();
				glColor3f(0, 1, 0);
				glScalef(0.3,0.3,0);
				glTranslatef(-text_length("USE UP AND DOWN KEYS TO CHOOSE LEVEL")/2,-5,0);
				draw_string("USE UP AND DOWN KEYS TO CHOOSE LEVEL");
			glPopMatrix();
			glPushMatrix();
				glColor3f(0, 1, 0);
				glScalef(0.3,0.3,0);
				glTranslatef(-text_length("PRESS SPACE TO PLAY")/2,-6,0);
				draw_string("PRESS SPACE TO PLAY");
			glPopMatrix();
			break;
		case 1:
			//statistika hry v levem spodnim rohu
			glPushMatrix(); 
				sprintf(b,"TIME %3.3f",gametime);
				glColor3f(0,1,0);
				glTranslatef(-4,-3,0);
				glScalef(0.3,0.3,0);
				draw_string(b);
			glPopMatrix();
			glPushMatrix();
				sprintf(b,"%d ENEMIES LEFT",enemies_left());
				glColor3f(0,1,0);
				glTranslatef(4-text_length(b)*0.3,-3,0);
				glScalef(0.3,0.3,0);
				draw_string(b);
			glPopMatrix();
			break;
		case 2:
			//smesovani barev
			glEnable(GL_BLEND);
			
			//vyber blendovaci funkce
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
			
			//zesednuti pozadi
			glColor4f(0, 0, 0, 0.6);
			glBegin(GL_QUADS);
			glVertex2f(-4, -3);
			glVertex2f(4, -3);
			glVertex2f(4, 3);
			glVertex2f(-4, 3);
			glEnd();
			
			glDisable(GL_BLEND);

			//kresleni statistik hry na konci hry
			glPushMatrix();
				glColor3f(0, 1, 0);
				glTranslatef(-text_length("VICTORY")/2,1,0);
				draw_string("VICTORY");
				glColor3f(0.3, 0.3, 1);
				glTranslatef(0.03, 0.03, 0);
				draw_string("VICTORY");
			glPopMatrix();
			glPushMatrix();
				glColor3f(1, 1, 1);
				glScalef(0.3,0.3,0);
				sprintf(b,"TIME %03.3fs",gametime);
				glTranslatef(-text_length(b)/2,-1,0);
				draw_string(b);
			glPopMatrix();
			glPushMatrix();
				glScalef(0.3,0.3,0);
				glTranslatef(-text_length("PRESS SPACE TO RESTART")/2,-5,0);
				glColor3f(0, 1, 0);
				draw_string("PRESS SPACE TO RESTART");
			glPopMatrix();
			break;
		case 3:
			//smesovani barev
			glEnable(GL_BLEND);
			
			//vyber blendovaci funkce
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
			
			//zesednuti pozadi
			glColor4f(0, 0, 0, 0.6);
			glBegin(GL_QUADS);
			glVertex2f(-4, -3);
			glVertex2f(4, -3);
			glVertex2f(4, 3);
			glVertex2f(-4, 3);
			glEnd();
			
			glDisable(GL_BLEND);

			//kresleni statistik hry na konci hry
			glPushMatrix();
				glColor3f(0, 1, 0);
				glTranslatef(-text_length("GAME OVER")/2,1,0);
				draw_string("GAME OVER");
				glColor3f(0.3, 0.3, 1);
				glTranslatef(0.03, 0.03, 0);
				draw_string("GAME OVER");
			glPopMatrix();
			glPushMatrix();
				glColor3f(1, 1, 1);
				glScalef(0.3,0.3,0);
				sprintf(b,"TIME %03.3fs",gametime);
				glTranslatef(-text_length(b)/2,-1,0);
				draw_string(b);
			glPopMatrix();
			glPushMatrix();
				glScalef(0.3,0.3,0);
				glTranslatef(-text_length("PRESS SPACE TO RESTART")/2,-5,0);
				glColor3f(0, 1, 0);
				draw_string("PRESS SPACE TO RESTART");
			glPopMatrix();
			break;
	}
}

//funkce pro obnovovani a ovladani hry
void update(float time,int key_up,int key_down,int key_left,int key_right,int key_space,int key_shoot,int key_esc) {
	int spacejustpressed=0,upjustpressed=0,downjustpressed=0,escjustpressed=0;
	//proti sekvencim stisknutych tlacitek
	if (key_space) {
		if (!spacehit) spacejustpressed=spacehit=1;
	} else spacehit=0;
	
	if (key_up) {
		if (!uphit) upjustpressed=uphit=1;
	} else uphit=0;
	
	if (key_down) {
		if (!downhit) downjustpressed=downhit=1;
	} else downhit=0;

	if (key_esc) {
		if (!eschit) escjustpressed=eschit=1;
	} else eschit=0;

	switch (gamestatus) {
		//ve hre
		case 1: 
			//aktualizace casti hry
			get_moto_position(cam);
			update_moto(time,key_up,key_down,key_left,key_right,key_space,key_shoot);
			move_enemies(time);
			update_bullets(time);
			update_particles(time);
			//update casu hry
			gametime+=time;
			//pokud hrac spadne, zemre, stiskne esc: zmena statusu hry: prohra
			if (moto_out_of_map()||moto_touches_enemy()||(escjustpressed==1)) gamestatus=3;
			//pokud nezbydou nepratele: zmena statusu: vyhra
			if (enemies_left()==0) gamestatus=2;
			break;
		//v menu
		case 0: 
			//pri mezerniku: nova hra
			if (spacejustpressed) {
				reset_game();
				gamestatus=1;
			}
			//vyber mapy z menu
			if (upjustpressed) mapchosen--;
			if (downjustpressed) mapchosen++;
			//pro nepreteceni counteru
			if (mapchosen>(maplist_count()-1)) mapchosen=maplist_count()-1;
			if (mapchosen<0) mapchosen=0;
			//pri esc: konec hry
			if (escjustpressed) game_end();
			break;
		//vitezstvi
		case 2:
			//pri mezerniku: nova hra
			if (spacejustpressed) {
				reset_game();
				gamestatus=1;
			}
			//pri esc: konec hry
			if (escjustpressed) gamestatus=0;
			//pro zbyle vybuchy jeste upgrade particlu
			update_particles(time);
			break;
		//prohra
		case 3:
			//pri mezerniku: nova hra
			if (spacejustpressed) {
				reset_game();
				gamestatus=1;
			}
			//pri esc: konec hry
			if (escjustpressed) gamestatus=0;
			//pro zbyle vybuchy jeste upgrade particlu
			update_particles(time);
			break;
		default:
			break;
	}
}

