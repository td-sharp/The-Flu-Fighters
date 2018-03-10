/* Aurthor: Kyle Werts
 * Date: 2/23/2018
 * Flu Fighters Power up and ammo file 
 */ 
#include "Ammo.h"
#include <time.h>
#include <ctime>
using namespace std;

extern double timeDiff(struct timespec *start, struct timespec *end);

void displayText()
{
	Rect r;
	int yres = 900;
	glClear(GL_COLOR_BUFFER_BIT);

	r.bot = yres - 100;
	r.left = 10;
	r.center = 0;
	ggprint8b(&r, 16, 0xFF00FF00, "kyleW");
}

double drawSalmonella(int salmonellaTexture)
{
    static double sec = 0.0;
    struct timespec ftimeStart, ftimeEnd;
    int timetotal = 0.0;

    glBindTexture(GL_TEXTURE_2D, salmonellaTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 80.0f,  80.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 80.0f, -80.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-80.0f, -80.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-80.0f,  80.0f);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();  

    clock_gettime(CLOCK_REALTIME, &ftimeStart);
    for (int i=0; i<10000; i++) {
    	timetotal += i/2;
    }

    clock_gettime(CLOCK_REALTIME, &ftimeEnd);
    Rect rec;
    rec.bot = 400;
    rec.left = 10;
    rec.center = 0;
    ggprint8b(&rec, 16, 0xFF00FF00, "kyleW Timer: %lf", sec);
    sec += timeDiff(&ftimeStart, &ftimeEnd);  
    return sec;
}
double drawSalmonellaMathy(int salmonellaTexture)
{
    static double sec = 0.0;
    struct timespec ftimeStart, ftimeEnd;
    int prev = 1, curr = 1, next = 1;

    glBindTexture(GL_TEXTURE_2D, salmonellaTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 180.0f, 180.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 180.0f, 30.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f( 30.0f,  30.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f( 30.0f,  180.0f);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();  

    clock_gettime(CLOCK_REALTIME, &ftimeStart);
    for (int i=3; i<10000; i++) {
    	next = curr + prev;
	prev = curr;
	curr = next;
    }

    clock_gettime(CLOCK_REALTIME, &ftimeEnd);
    Rect rec;
    rec.bot = 450;
    rec.left = 10;
    rec.center = 0;
    ggprint8b(&rec, 16, 0xFF00FF00, "kyleW Optimize Timer: %lf", sec);
    sec += timeDiff(&ftimeStart, &ftimeEnd);  
    return sec;
}






