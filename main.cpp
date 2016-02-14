
#include <GL/glut.h>
#include <GL/gl.h>

#include <iostream>
using namespace std;

#include "game.h"

bool key_esc=false,key_up=false,key_down=false,key_left=false,key_right=false,key_space=false,key_shoot=false;
int lasttime=0;

//inicializase nemenneho pozadi
void init() {
	//smesovani barev
	glEnable(GL_SMOOTH);

	glClearColor(0,0,0,0);

	//nastaveni presnosti vypoctu (realne)
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	
	init_game();
}

//funkce zjisti cas od posledniho zavolani (snimku)
float get_time_diff() {
	int newtime;
	float diff;

	//cas v ms od minuleho snimku
	newtime=glutGet(GLUT_ELAPSED_TIME);

	//rozdil casu + prevod na sekundy
	diff=(newtime-lasttime)*0.001;
	
	lasttime=newtime;

	//pro preteceni
	if (diff<=0) diff=0.000001;
	
	//zpomaleni hry pri malem fps
	if (diff>0.1) diff=0.1;
	
	return diff;
}

//periodicke prekreslovani sceny
void display(int _data) { 
	float time;
	int i, fi;
	time=get_time_diff();

	update(time,key_up,key_down,key_left,key_right,key_space,key_shoot,key_esc);

	//vycisteni snimku
	glClear(GL_COLOR_BUFFER_BIT); 
	
	//reset na souradnice 0, 0, 0
	glLoadIdentity();
	
	draw_game();
	
	//z double bufferingu, prehozeni snimku
	glutSwapBuffers();
	glutTimerFunc(10,display,0);
}

void reshape(int s, int v) {
	//fyzicka plocha, kde kreslim
	glViewport(0,0,s,v); 
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//prakticky urcuji 'rozliseni hry'
	glOrtho(-4,4,-3,3,-1,1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard_down(unsigned char key, int x, int y) {
	switch (key) {
		//kdyz Esc > konec hry
		case 27: key_esc=true; break;
		case ' ': key_space=true; break;
		case 'x': key_shoot=true; break;
		default: break;
	}
}

void keyboard_up(unsigned char key, int x, int y) {
	switch (key) {
		case 27: key_esc=false; break;
		case ' ': key_space=false; break;
		case 'x': key_shoot=false; break;
		default: break;
	}
}

void special_keys_down(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: key_left=true; break; 
		case GLUT_KEY_RIGHT: key_right=true; break;
		case GLUT_KEY_UP: key_up=true; break;
		case GLUT_KEY_DOWN: key_down=true; break;
		default: break;
	}
}

void special_keys_up(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT: key_left=false; break; 
		case GLUT_KEY_RIGHT: key_right=false; break;
		case GLUT_KEY_UP: key_up=false; break;
		case GLUT_KEY_DOWN: key_down=false; break;
		default: break;
	}
}

//funkce spoustena pri skonceni hry
void game_end() {
	clear_game();	
//	glutLeaveMainLoop();
	exit(0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	init();

	//double buffering
	glutInitDisplayMode(GLUT_DOUBLE);
	
	glutInitWindowSize(640,480);
	glutCreateWindow("MoToX");
	
	//callbacky
	glutReshapeFunc(reshape);
	
	//zachyceni vstupu z klavesnice
	glutKeyboardFunc(keyboard_down);
	glutKeyboardUpFunc(keyboard_up);

	//zachyceni vstupu z klavesnice - na netisknutelne znaky
	glutSpecialFunc(special_keys_down);
	glutSpecialUpFunc(special_keys_up);

	//za 0 ms, prekreslovani
	glutTimerFunc(0,display,0);
	
	//zahajeni hlavniho cyklu
	glutMainLoop();

	return 0;
}

