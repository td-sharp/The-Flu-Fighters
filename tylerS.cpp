using namespace std;
#include "fonts.h"
#include <GL/glx.h>
#include <ctime>

//extern double timeDiff(struct timespec *start, struct timespec *end);

void startMenu(int xres, int yres, int TitleScreenTexture)
{
    glBindTexture(GL_TEXTURE_2D, TitleScreenTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( xres, yres);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( xres, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f( 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f( 0.0f, yres);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}
void drawOverlay(int xres, int yres, int lives, int shipTexture)
{
    /*glBindTexture(GL_TEXTURE_2D, overlaidTexture);

    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( xres, 60.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( xres, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f( 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f( 0.0f, 60.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    */

    glColor3f(1.0f, 1.0f, 1.0f);
    glColor3ub(77, 166, 255);
	glPushMatrix();
	//glTranslatef( 50, 50, 0);
	//glRotatef(angle, 0.0f, 0.0f, 1.0f);
    //glTranslatef(-50, -50, 0);
    //angle = angle + 2.5;
	glBegin(GL_QUADS);
		glVertex2i(0  , 0);
        glVertex2i(xres, 0);
        glVertex2i(xres, 60);
        glVertex2i(0  , 60);
    glPopMatrix();
	glEnd();

    Rect r;
    r.bot = 20;
    r.left = 20;
    r.center = 0;
    ggprint16(&r, 16, 0xFB6AD0, "LIVES");
    for (int i = 0; i < lives; i++) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glPushMatrix();

        glTranslatef(70*(i+2), 30, 0.0f);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);

        glBindTexture(GL_TEXTURE_2D, shipTexture);
        glBegin(GL_QUADS);
            glTexCoord2f(1.0f, 0.0f); glVertex2f( 10.0f,  10.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex2f( 10.0f, -10.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -10.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f,  10.0f);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        glPopMatrix();
    }
}
void drawBullet(float posA, float posB, int bulletTexture)
{
    glPushMatrix();
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glTranslatef(posA, posB, 0);
    glBindTexture(GL_TEXTURE_2D, bulletTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 10.0f,  10.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 10.0f, -10.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -10.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f,  10.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}
void drawShip(float posA, float posB, float posC, int shipTexture)
{
    //glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glTranslatef(posA, posB, posC);
    glBindTexture(GL_TEXTURE_2D, shipTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 30.0f,  30.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 30.0f, -30.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-30.0f, -30.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-30.0f,  30.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void drawGBola(int GBolaTexture)
{
    //glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, GBolaTexture);
    //glColor4ub(0,0,0,0);

    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 80.0f,  80.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 80.0f, -80.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-80.0f, -80.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-80.0f,  80.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void drawSalmonella(int salmonellaTexture)
{
    glBindTexture(GL_TEXTURE_2D, salmonellaTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 80.0f,  80.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 80.0f, -80.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-80.0f, -80.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-80.0f,  80.0f);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

void drawWave1()
{
}
void drawWave2()
{
}
void drawWave3()
{

}
void drawWave4()
{

}
void drawWave5()
{

}
void drawTheBoss()
{

}
