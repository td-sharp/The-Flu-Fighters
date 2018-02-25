/* Aurthor: Kyle Werts
 * Date: 2/23/2018
 * Flu Fighters Power up and ammo file 
 */ 
#include "Ammo.h"
using namespace std;

void displayText()
{
	Rect r;
	int yres = 900;
	glClear(GL_COLOR_BUFFER_BIT);

	r.bot = yres - 100;
	r.left = 10;
	r.center = 0;
	ggprint8b(&r, 16, 0xFF00FF00, "kwerts");
}
