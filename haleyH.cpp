#include <stdlib.h>
#include <iostream>

using namespace std;

class G_coli {
public: 
	Vec pos;
	Vec vel;
	int health;
};

G_coli gcoli[10];

void buildG_coli()
{

	float vfactor = rand() % 5 + 3;
	float xpos = (float)rand() % gl.xres/2 - 300;
	float ypos = (float)rand() % gl.yres/2 + 150;
	
	cout << "Building G_coli enemies from haleyH.cpp" << endl;	

	for (int i = 0; i < 10; i++)
	{
		gc[i].pos[0] = xpos;
		gc[i].pos[1] = ypos;
		gc[i].pos[2] = 0.00;

		gc[i].vel[0] = factor;
		gc[i].vel[1] = -factor / 1.5;
		gc[i].vel[2] = 0.00;
	}
	
	cout << i << " enemies built" << endl;
}

void moveG_coli()
{	 	
	for (int i = 0; i < 10; i++)
	{
		gc[i].pos[0] += gc->vel[0];
		gc[i].pos[1] += gc->vel[1];

		cout << "G-Coli Enemy " i << " New Position: x - " << gc[i].pos[0] <<
			" y - " << gc[i].pos[1] << endl; 		

		if ((gc[i].pos[0] < -gl.xres/2 && gc[i].vel[0] < 0) || 
	    		(gc[i].pos[0] > gl.xres/2 && gc[i].vel[0] > 0))
				gc->vel[0] = -gc->vel[0]; 
	}

}
