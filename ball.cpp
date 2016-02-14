
#include "ball.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

#include <iostream>
using namespace std;

#include "map.h"

//vykoliduje kulicku s primkou zadanou rovnici nx*x+ny*y=c
int wall_collision(float time,ball& b,const complex& n,float c) {
	
	//cilova rychlost kulicky pri rotaci
	float d=((n.x*b.pos.x)+(n.y*b.pos.y))-c;
	if((d>=b.rad)||(d<=-b.rad)) return 0;

	//vzdalenost vektoru rychlosti od vysledneho vektoru rychlosti
	float r=(n.x*b.speed.x)+(n.y*b.speed.y);

	//kdyz kulicka leti _proti_ primce, projekce rychlosti na plochu
	if((r*d)<0) b.speed-=r*n;

	//vektor pozadovane rychlosti zpusobene rotaci
	complex ts(n.y*b.rotspd,-n.x*b.rotspd);

	//pokud kulicka koliduje zespoda
	if(d<0) ts*=-1;

	b.speed-=ts;

	//odpor plochy dopadu
	b.speed*=powf(b.slip,time);

	b.speed+=ts;

	//uprava polohy kulicky
	b.pos-=d*n;
	if(d>0) b.pos+=b.rad*n;
	else b.pos-=b.rad*n;

	return 1;
}

//funkce pro reseni kolize kulicky se svetem
int collision(float time,ball& b,wall& w) {
	float s1=((w.p2.x-w.p1.x)*(b.pos.x-w.p1.x))+((w.p2.y-w.p1.y)*(b.pos.y-w.p1.y));
	float s2=((w.p1.x-w.p2.x)*(b.pos.x-w.p2.x))+((w.p1.y-w.p2.y)*(b.pos.y-w.p2.y));
	float c;

	//pripad kolize s primkou
	if((s1>0)&&(s2>0)) {
		complex n(w.p1.y-w.p2.y,w.p2.x-w.p1.x);
		n=n.normal();
		c=(n.x*w.p1.x)+(n.y*w.p1.y);
		return wall_collision(time,b,n,c);
	}

	//pripad kolize s bodem x2,y2
	else if(s1>0) {
		complex n(b.pos.x-w.p2.x,b.pos.y-w.p2.y);
		n=n.normal();
		c=(n.x*w.p2.x)+(n.y*w.p2.y);
		return wall_collision(time,b,n,c);
	}	

	//pripad kolize s bodem x1,y1
	else {
		complex n(b.pos.x-w.p1.x,b.pos.y-w.p1.y);
		n=n.normal();
		c=(n.x*w.p1.x)+(n.y*w.p1.y);
		return wall_collision(time,b,n,c);
	}
}

//funkce pro udrzeni vsech kulicek a pruzeni
void spring(float time,float dist,float power,ball& a,ball& b) {
	
	//soucasna vzdalenost kulicek
	float bd=powf(powf(a.pos.x-b.pos.x,2)+powf(a.pos.y-b.pos.y,2),0.5);
	if(bd==0) return;

	float temp=bd-dist;

	//vsechny pruzinky tahnou stejne
	temp/=dist;

	//zjisteni, zda se kulicky priblizuji nebo ne
	float approach=((b.pos.x-a.pos.x)*(a.speed.x-b.speed.x))+((b.pos.y-a.pos.y)*(a.speed.y-b.speed.y));

	//pokud jsou kulicky moc blizko a priblizuji se, nebo jsou moc daleko a oddaluji se, prida se vice sily na jejich zestabilneni
	if((temp*approach)<0) power*=2;

	temp*=fabs(temp); //pri deleni 10 = ghost mode :D:D

	//zmena rychlosti v zavislosti na vzdalenosti kulicek
	a.speed.x+=temp*((b.pos.x-a.pos.x)/bd)*time*power;
	a.speed.y+=temp*((b.pos.y-a.pos.y)/bd)*time*power;
	b.speed.x+=temp*((a.pos.x-b.pos.x)/bd)*time*power;
	b.speed.y+=temp*((a.pos.y-b.pos.y)/bd)*time*power;
}

