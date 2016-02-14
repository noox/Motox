
#include "text.h"

#include <GL/gl.h>
#include <stdio.h>

#include <iostream>
using namespace std;

//funkce pro kresleni jednotlivych znaku (charu)
void draw_char(char c) {
	glPushMatrix();
	//prevod na mala pismenka
	if ((c>='a')&&(c<='z')) {
		c-='a'-'A';
		glScalef(1,0.7,1);
	}
	glBegin(GL_LINES);
	switch (c) {
		case '0': 
			glVertex2f(2,1);
			glVertex2f(1,2);
			glVertex2f(1,2);
			glVertex2f(1,5);
			glVertex2f(1,5);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			glVertex2f(4,5);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(2,1);
			glVertex2f(2,3);
			glVertex2f(3,4);
			break;
		case '1':	
			glVertex2f(3,1);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(1,4);
			break;
		case '2':
			glVertex2f(1,5);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			glVertex2f(4,5);
			glVertex2f(4,4);
			glVertex2f(4,4);
			glVertex2f(1,1);
			glVertex2f(1,1);
			glVertex2f(4,1);
			break;
		case '3':
			glVertex2f(1,5);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			glVertex2f(4,5);
			glVertex2f(4,4);
			glVertex2f(4,4);
			glVertex2f(3,3.5);
			glVertex2f(3,3.5);
			glVertex2f(4,3);
			glVertex2f(4,3);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(2,1);
			glVertex2f(2,1);
			glVertex2f(1,2);
			glVertex2f(1,2);
			break;
		case '4':
			glVertex2f(3,1);
			glVertex2f(3,5);
			glVertex2f(4,3);
			glVertex2f(1,3);
			glVertex2f(1,3);
			glVertex2f(1,6);
			break;	
		case '5':
			glVertex2f(1,2);
			glVertex2f(2,1);
			glVertex2f(2,1);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(4,3);
			glVertex2f(4,3);
			glVertex2f(3,4);
			glVertex2f(3,4);
			glVertex2f(1,4);
			glVertex2f(1,4);
			glVertex2f(1,6);
			glVertex2f(1,6);
			glVertex2f(4,6);
			break;
		case '6':
			glVertex2f(4,5);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(1,5);
			glVertex2f(1,5);
			glVertex2f(1,2);
			glVertex2f(1,2);
			glVertex2f(2,1);
			glVertex2f(2,1);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(4,3);
			glVertex2f(4,3);
			glVertex2f(3,4);
			glVertex2f(3,4);
			glVertex2f(2,4);
			glVertex2f(2,4);
			glVertex2f(1,3);
			break;
		case '7':
			glVertex2f(2,1);
			glVertex2f(4,5);
			glVertex2f(4,5);
			glVertex2f(4,6);
			glVertex2f(4,6);
			glVertex2f(1,6);
			break;
		case '8':
			glVertex2f(2,3.5);
			glVertex2f(1,3);
			glVertex2f(1,3);
			glVertex2f(1,2);
			glVertex2f(1,2);
			glVertex2f(2,1);
			glVertex2f(2,1);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(4,3);
			glVertex2f(4,3);
			glVertex2f(3,3.5);
			glVertex2f(3,3.5);
			glVertex2f(2,3.5);
			glVertex2f(2,3.5);
			glVertex2f(1,4);
			glVertex2f(1,4);
			glVertex2f(1,5);
			glVertex2f(1,5);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			glVertex2f(4,5);
			glVertex2f(4,4);
			glVertex2f(4,4);
			glVertex2f(3,3.5);
			break;
		case '9':
			glVertex2f(1,2);
			glVertex2f(2,1);
			glVertex2f(2,1);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(4,5);
			glVertex2f(4,5);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(1,5);
			glVertex2f(1,5);
			glVertex2f(1,4);
			glVertex2f(1,4);
			glVertex2f(2,3);
			glVertex2f(2,3);
			glVertex2f(3,3);
			glVertex2f(3,3);
			glVertex2f(4,4);
			break;
		case 'A':
			glVertex2f(1,1);
			glVertex2f(1,5);
			glVertex2f(1,5);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			glVertex2f(4,5);
			glVertex2f(4,1);
			glVertex2f(1,3.5);
			glVertex2f(4,3.5);
			break;
		case 'B':
			glVertex2f(1,1);
			glVertex2f(1,6);
			glVertex2f(1,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			glVertex2f(4,5);
			glVertex2f(4,4);
			glVertex2f(4,4);
			glVertex2f(3,3.5);
			glVertex2f(3,3.5);
			glVertex2f(1,3.5);
			glVertex2f(1,3.5);
			glVertex2f(3,3.5);
			glVertex2f(3,3.5);
			glVertex2f(4,3);
			glVertex2f(4,3);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(1,1);
			break;
		case 'C':
			glVertex2f(4,2);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(2,1);
			glVertex2f(2,1);
			glVertex2f(1,2);
			glVertex2f(1,2);
			glVertex2f(1,5);
			glVertex2f(1,5);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			break;
		case 'D':
			glVertex2f(1,1);
			glVertex2f(1,6);
			glVertex2f(1,6);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(4,4);
			glVertex2f(4,4);
			glVertex2f(4,3);
			glVertex2f(4,3);
			glVertex2f(2,1);
			glVertex2f(2,1);
			glVertex2f(1,1);
			break;
		case 'E':
			glVertex2f(4,1);
			glVertex2f(1,1);
			glVertex2f(1,1);
			glVertex2f(1,6);
			glVertex2f(1,6);
			glVertex2f(4,6);
			glVertex2f(1,3.5);
			glVertex2f(3,3.5);
			break;
		case 'F':
			glVertex2f(1,1);
			glVertex2f(1,6);
			glVertex2f(1,6);
			glVertex2f(4,6);
			glVertex2f(1,3.5);
			glVertex2f(3,3.5);
			break;
		case 'G':
			glVertex2f(2,3);
			glVertex2f(4,3);
			glVertex2f(4,3);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(2,1);
			glVertex2f(2,1);
			glVertex2f(1,2);
			glVertex2f(1,2);
			glVertex2f(1,5);
			glVertex2f(1,5);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			break;
		case 'H':
			glVertex2f(1,1);
			glVertex2f(1,6);
			glVertex2f(4,1);
			glVertex2f(4,6);
			glVertex2f(1,3.5);
			glVertex2f(4,3.5);
			break;
		case 'I':
			glVertex2f(2,1);
			glVertex2f(3,1);
			glVertex2f(2.5,1);
			glVertex2f(2.5,6);
			glVertex2f(2,6);
			glVertex2f(3,6);
			break;
		case 'J':
			glVertex2f(4,6);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(2,1);
			glVertex2f(2,1);
			glVertex2f(1,3);
			break;
		case 'K':
			glVertex2f(1,1);
			glVertex2f(1,6);
			glVertex2f(1,3.5);
			glVertex2f(2,3.5);
			glVertex2f(2,3.5);
			glVertex2f(4,6);
			glVertex2f(2,3.5);
			glVertex2f(4,1);
			break;
		case 'L':
			glVertex2f(1,6);
			glVertex2f(1,1);
			glVertex2f(1,1);
			glVertex2f(4,1);
			break;
		case 'M':
			glVertex2f(1,1);
			glVertex2f(1,6);
			glVertex2f(1,6);
			glVertex2f(2.5,4);
			glVertex2f(2.5,4);
			glVertex2f(4,6);
			glVertex2f(4,6);
			glVertex2f(4,1);
			break;
		case 'N':
			glVertex2f(1,1);
			glVertex2f(1,6);
			glVertex2f(1,6);
			glVertex2f(4,1);
			glVertex2f(4,1);
			glVertex2f(4,6);
			break;
		case 'O':
			glVertex2f(2,1);
			glVertex2f(1,2);
			glVertex2f(1,2);
			glVertex2f(1,5);
			glVertex2f(1,5);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			glVertex2f(4,5);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(2,1);
			break;
		case 'P':
			glVertex2f(1,1);
			glVertex2f(1,6);
			glVertex2f(1,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			glVertex2f(4,5);
			glVertex2f(4,4);
			glVertex2f(4,4);
			glVertex2f(3,3);
			glVertex2f(3,3);
			glVertex2f(1,3);
			break;
		case 'Q':
			glVertex2f(2,1);
			glVertex2f(1,2);
			glVertex2f(1,2);
			glVertex2f(1,5);
			glVertex2f(1,5);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			glVertex2f(4,5);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(2,1);
			glVertex2f(2,3);
			glVertex2f(4,1);
			break;
		case 'R':
			glVertex2f(1,1);
			glVertex2f(1,6);
			glVertex2f(1,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			glVertex2f(4,5);
			glVertex2f(4,4);
			glVertex2f(4,4);
			glVertex2f(3,3);
			glVertex2f(3,3);
			glVertex2f(1,3);
			glVertex2f(2.5,3);
			glVertex2f(4,1);
			break;
		case 'S':
			glVertex2f(1,2);
			glVertex2f(2,1);
			glVertex2f(2,1);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(4,3);
			glVertex2f(4,3);
			glVertex2f(3,3.5);
			glVertex2f(3,3.5);
			glVertex2f(2,3.5);
			glVertex2f(2,3.5);
			glVertex2f(1,4);
			glVertex2f(1,4);
			glVertex2f(1,5);
			glVertex2f(1,5);
			glVertex2f(2,6);
			glVertex2f(2,6);
			glVertex2f(3,6);
			glVertex2f(3,6);
			glVertex2f(4,5);
			break;
		case 'T':
			glVertex2f(1,6);
			glVertex2f(4,6);
			glVertex2f(2.5,1);
			glVertex2f(2.5,6);
			break;
		case 'U':
			glVertex2f(1,6);
			glVertex2f(1,2);
			glVertex2f(1,2);
			glVertex2f(2,1);
			glVertex2f(2,1);
			glVertex2f(3,1);
			glVertex2f(3,1);
			glVertex2f(4,2);
			glVertex2f(4,2);
			glVertex2f(4,6);
			break;
		case 'V':
			glVertex2f(1,6);
			glVertex2f(1,4);
			glVertex2f(1,4);
			glVertex2f(2.5,1);
			glVertex2f(2.5,1);
			glVertex2f(4,4);
			glVertex2f(4,4);
			glVertex2f(4,6);
			glVertex2f(4,6);
			break;
		case 'W':
			glVertex2f(1,6);
			glVertex2f(1.5,1);
			glVertex2f(1.5,1);
			glVertex2f(2.5,4);
			glVertex2f(2.5,4);
			glVertex2f(3.5,1);
			glVertex2f(3.5,1);
			glVertex2f(4,6);
			break;
		case 'X':
			glVertex2f(1,1);
			glVertex2f(4,6);
			glVertex2f(1,6);
			glVertex2f(4,1);
			break;
		case 'Y':
			glVertex2f(2.5,1);
			glVertex2f(2.5,4);
			glVertex2f(2.5,4);
			glVertex2f(4,6);
			glVertex2f(2.5,4);
			glVertex2f(1,6);
			break;
		case 'Z':
			glVertex2f(1,6);
			glVertex2f(4,6);
			glVertex2f(4,6);
			glVertex2f(1,1);
			glVertex2f(1,1);
			glVertex2f(4,1);
			glVertex2f(4,1);
			break;
		case '.':
			glVertex2f(2.5,1);
			glVertex2f(3,1.5);
			glVertex2f(3,1.5);
			glVertex2f(2.5,2);
			glVertex2f(2.5,2);
			glVertex2f(2,1.5);
			glVertex2f(2,1.5);
			glVertex2f(2.5,1);
		case ' ':
			break;
		default: 
			glVertex2f(0,0);
			glVertex2f(5,7);
			glVertex2f(5,0);
			glVertex2f(0,7);
			break;
	}
	glEnd();
	glPopMatrix();
}

//kresli text do hry
void draw_string(const char* s) {
	glPushMatrix();

	//scale pro dobrou praci s chary
	glScalef(0.125,0.125,1);

	for(;*s;s++) { //s++: adresa++
		draw_char(*s);
		glTranslatef(5,0,0);
	}
	glPopMatrix();
}

//zjisti delku stringu
float text_length(const char *s) {
	int len;
	for(len=0;*s;len++,s++);
	return len*0.625;
}

//predelava cisla na chary
void draw_int(int n) {
	char buffer[64];
	sprintf(buffer,"%d",n);
draw_string(buffer);
}

