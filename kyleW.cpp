/* Aurthor: Kyle Werts
 * Date: 2/23/2018
 * Flu Fighters Power up and ammo file 
 */ 
#include "Ammo.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>

void displayBox()
{
	Rect r;
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(-206.0, 512.0, 0.0);
	glBegin(GL_QUADS); 

	glVertex2i(412, -50);
	glVertex2i(412,  50);
	glVertex2i(512,  50);
	glVertex2i(512, -50);

	glEnd();
	glPopMatrix();

	r.bot = 620;
	r.left = 215;
	r.center = 0;
	ggprint8b(&r, 16, 0x00ff0000, "Kyle's Box");
	glEnd();

}