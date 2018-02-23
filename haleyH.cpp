#include <stdlib.h>

class G_coli {
public: 
	Vec pos;
	Vec vel;
	int health;
};

void buildG_coli(G_coli gc[])
{
	int loops = sizeof gc / sizeof gc[0]; 
	float vfactor = rand() % 5 + 3;
	float xpos = (float)rand() % gl.xres/2 - 300;
	float ypos = (float)rand() % gl.yres/2 + 150;
	
	for (int i = 0; i < loops; i++)
	{
		gc[i].pos[0] = xpos;
		gc[i].pos[1] = ypos;
		gc[i].pos[2] = 0.00;

		gc[i].vel[0] = factor;
		gc[i].vel[1] = -factor / 1.5;
		gc[i].vel[2] = 0.00;
	}

}

void moveG_coli(G_coli gc[])
{
	int loops = sizeof gc / sizeof gc[0]; 
	
	for (int i = 0; i < loops; i++)
	{
		gc->pos[0] += gc->vel[0];
		gc->pos[1] += gc->vel[1];

		if ((gc->pos[0] < -gl.xres/2 && gc->vel[0] < 0) || 
	    		(gc->pos[0] > gl.xres/2 && gc->vel[0] > 0))
				gc->vel[0] = -gc->vel[0]; 
	}

}
