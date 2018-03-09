#include <stdlib.h>
#include <iostream>
#include <GL/glx.h>
#include <ctime>
#include "fonts.h"
#include "haleyH.h"

#define GBOLA_HEALTH  50;
#define SALMONELLA_HEALTH 100;
#define CHOLERA_HEALTH 150;

extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);

using namespace std;

Gbola::Gbola(float xpos, float ypos) 
{
	pos[0] = xpos;
	pos[1] = ypos;
	pos[2] = 0.0;
	health = GBOLA_HEALTH;		
}		
	

Salmonella::Salmonella(float xpos, float ypos, float rotation)
{
	pos[0] = xpos;
	pos[1] = ypos;
	pos[2] = 0.0f;
	angle = 0.0;
	rotate = rotation;
	health = SALMONELLA_HEALTH;
}

Cholera::Cholera(float xpos, float ypos, float rotation, float acceleration)
{
	pos[0] = xpos;
	pos[1] = ypos;
	pos[2] = 0.0f;
	angle = 0.0;
	rotate = rotation;
	accelerate = acceleration;
	health = CHOLERA_HEALTH;
}

double testHaleyFunc()
{
	float data;
	float arr[10];
	static double t = 0.0;
	struct timespec ftimeStart, ftimeEnd;
	clock_gettime(CLOCK_REALTIME, &ftimeStart);
	for (int i = 0; i < 10; i++)
	{
		data = 0.0325363456235326+i;
		arr[i] = data;
	}
	clock_gettime(CLOCK_REALTIME, &ftimeEnd);
	t += timeDiff(&ftimeStart, &ftimeEnd);
	return t;
}


double testHaleyFunc2()
{
	int data;
	int arr[10];
	static double t = 0.0;
	struct timespec ftimeStart, ftimeEnd;
	clock_gettime(CLOCK_REALTIME, &ftimeStart);
	for (int i = 0; i < 10; i++)
	{
		data = 0 + i;
		arr[i] = data;
	}
	clock_gettime(CLOCK_REALTIME, &ftimeEnd);
	t += timeDiff(&ftimeStart, &ftimeEnd);
	return t;
}

void drawHaleyTimer()
{
	Rect r;
	r.bot = 880;
	r.left = 400;
	r.center = 0;
	ggprint16(&r, 16, 0x00ff0000, "Haley's Timer");
	ggprint16(&r, 16, 0x00ff0000, "Option 1: %f", testHaleyFunc());
	ggprint16(&r, 16, 0x00ff0000, "Option 2: %f", testHaleyFunc2());
}




void moveGbola(int Gbolacount)
{	 	
	for (int i = 0; i < Gbolacount; i++)
	{
		// make them hover
	}
}

