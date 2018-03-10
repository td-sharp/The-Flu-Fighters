/* 
   Renee Romero
   CMPS 3350
   Lab 5
   02-25-18
   Displays the amount of life available currently for the ship
*/

#include <iostream>
using namespace std;
#include <stdio.h>
#include "fonts.h"

void printReneeFile()
{
	cout<<"Renee's CPP file is present!" << endl;	
//	return 0;	
}
/* 
   Renee Romero
   CMPS 3350
   Lab 5
   02-25-18
   Layout of Levels
*/

#include <iostream>
using namespace std;
#include <stdio.h>
#include "fonts.h"
#include <stdlib.h>
#include <ctime>
const float GBOLA_TOTAL = 30;
extern double timeDiff(struct timespec *start, struct timespec *end);

void printReneeFile()
{
	cout<<"Renee's CPP file is present!" << endl;	
}
double ReneeTime()
{
	static double t = 0; 
	timespec timeStart;
	timespec timeEnd;
	clock_gettime(CLOCK_REALTIME,&timeStart);
	int a = 200, b = 300, c = 400;
	for (int i = 0; i<10;i++)
	{
		b = (a&15) - (b&7) - (c&3);
		c = (b&31) - (a&7) - (c&3);
	}	
	clock_gettime(CLOCK_REALTIME,&timeEnd);
	t += timeDiff(&timeStart, &timeEnd);
	return t;
}
void level_one()
{	
	for ( int i = 0; i < GBOLA_TOTAL; i++)
	{
		float mob_x = rand();
		float mob_y = rand();		
	      //  Gbola(mob_x, mob_y);
		
	}	
}

void draw_ReneeTime()
{
	Rect r;
	r.bot = 150;
	r.left = 15;
	r.center = 0;
	ggprint16(&r, 16, 0x00ffff00, "Renee Time: %f", ReneeTime());
}
void level_two()
{

}
