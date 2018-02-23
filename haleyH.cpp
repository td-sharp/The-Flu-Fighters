#include <stdlib.h>
#include <iostream>

using namespace std;

class G_coli {
public: 
	float pos[3];
	float vel[3];
	int health;
};

G_coli gcoli[10];

void buildG_coli()
{

	float vfactor = rand() % 5 + 3;
	float xpos = (float)(rand() % 600/2 - 300);
	float ypos = (float)(rand() % 900/2 + 150);
	
	cout << "Building G_coli enemies from haleyH.cpp" << endl;	

	int i;
	for (i = 0; i < 10; i++)
	{
		gcoli[i].pos[0] = xpos;
		gcoli[i].pos[1] = ypos;
		gcoli[i].pos[2] = 0.00;

		gcoli[i].vel[0] = vfactor;
		gcoli[i].vel[1] = -vfactor / 1.5;
		gcoli[i].vel[2] = 0.00;
	}
	
	cout << i << " enemies built" << endl;
}

void moveG_coli()
{	 	
	for (int i = 0; i < 10; i++)
	{
		gcoli[i].pos[0] += gcoli[i].vel[0];
		gcoli[i].pos[1] += gcoli[i].vel[1];

		cout << "G-Coli Enemy " << i << " New Position: x - " << gcoli[i].pos[0] <<
			" y - " << gcoli[i].pos[1] << endl; 		

		if ((gcoli[i].pos[0] < -600/2 && gcoli[i].vel[0] < 0) || 
	    		(gcoli[i].pos[0] > 600/2 && gcoli[i].vel[0] > 0))
				gcoli->vel[0] = -gcoli->vel[0]; 
	}

}
