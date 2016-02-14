
#include "complex.h"

void delete_particles();
void add_particle(const complex& pos,const complex& speed,float life,float r,float g,float b,int type);
void update_particles(float time);
void draw_particles();
void small_explosion(const complex& pos);
void big_explosion(const complex& pos);

