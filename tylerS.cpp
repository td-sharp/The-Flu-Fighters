using namespace std;
#include "fonts.h"
#include <GL/glx.h>
#include <ctime>
#include <unistd.h>
#include <iostream>

extern double timeDiff(struct timespec *start, struct timespec *end);

void startMenu(int xres, int yres, int TitleScreenTexture, int Cursor,
                                                                int cursorPos)
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
    //CURSOR
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    if (cursorPos == 1) {
        glTranslatef(350, 440, 0.0f);
    } else if (cursorPos == 2) {
        glTranslatef(350, 380, 0.0f);
    } else {
        glTranslatef(350, 300, 0.0f);
    }
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);

    glBindTexture(GL_TEXTURE_2D, Cursor);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 35.0f,  35.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 35.0f, -35.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-35.0f, -35.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-35.0f,  35.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

}
void waveMenu(int xres, int yres, int WaveScreenTexture, int Cursor,
                                                                int cursorPos)
{
    glBindTexture(GL_TEXTURE_2D, WaveScreenTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( xres, yres);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( xres, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f( 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f( 0.0f, yres);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    //CURSOR
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    if (cursorPos == 1) {
        glTranslatef(360, 470, 0.0f);
    } else if (cursorPos == 2) {
        glTranslatef(360, 400, 0.0f);
    } else if (cursorPos == 3) {
        glTranslatef(360, 330, 0.0f);
    } else if (cursorPos == 4) {
        glTranslatef(360, 260, 0.0f);
    } else if (cursorPos == 5) {
        glTranslatef(360, 190, 0.0f);
    } else {
        glTranslatef(360, 120, 0.0f);
    }
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);

    glBindTexture(GL_TEXTURE_2D, Cursor);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 35.0f,  35.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 35.0f, -35.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-35.0f, -35.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-35.0f,  35.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

}

void drawPre(int gameState)
{
        //Draw the ship
        //drawShip(g.ship.pos[0], g.ship.pos[1], g.ship.pos[2], shipTexture);
        Rect r;
        r.bot = 800;
        r.center = 0;
        Rect s;
        s.bot = 780;
        s.center = 0;
        if (gameState == 3) {
            r.left = 170;
            ggprint16(&r, 16, 0xFB6AD0, "LET'S GET A PHYSICAL");
        } else if (gameState == 5) {
            r.left = 100;
            ggprint16(&r, 16, 0xFB6AD0, "DEFRIBILLATOR? I 'ARDLY EVEN KNOW 'ER!");
        } else if (gameState == 7) {
            r.left = 170;
            ggprint16(&r, 16, 0xFB6AD0, "URINE A LOT OF TROUBLE");
        } else if (gameState == 9) {
            r.left = 168;
            ggprint16(&r, 16, 0xFB6AD0, "TIME TO PRACTICE MEDICINE");
            s.left = 184;
            ggprint16(&s, 16, 0xFB6AD0, "AND CHEW BUBBLEGUM");
        } else if (gameState == 11) {
            r.left = 170;
            ggprint16(&r, 16, 0xFB6AD0, "IT'S GOING TIBIA BAD DAY");
        } else if (gameState == 13) {
            r.left = 120;
            ggprint16(&r, 16, 0xFB6AD0, "THE DISEASES RULE ALL..GAME OVER");
        }
    //sleep(1);
    //return 1;
}
void drawPost()
{
    Rect r;
    r.bot = 800;
    r.center = 0;
    r.left = 185;
    ggprint16(&r, 16, 0xFB6AD0, "WAVE COMPLETE!");
}
void drawOverlay(int xres, int yres, int lives, int shipTexture)
{
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
    glColor3f(1.0f, 1.0f, 1.0f);
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
    glColor3f(1.0f, 1.0f, 1.0f);
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

void drawGBola(int GBolaTexture, float thyme)
{
    //glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, GBolaTexture);
    //glColor4ub(0,0,0,0);
    float GHeight;
    if ((int)thyme % 2 != 0) {
        GHeight = 35.0;
    } else {
        GHeight = 40.0;
    }
    float GWidth = 40.0;
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( GWidth,  GHeight);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( GWidth, -GHeight);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-GWidth, -GHeight);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-GWidth,  GHeight);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void drawSalmonella(int salmonellaTexture, float thyme)
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, salmonellaTexture);
    float SHeight;
    if ((int)thyme % 2 != 0) {
        SHeight = 35.0;
    } else {
        SHeight = 40.0;
    }
    float SWidth = 40.0;
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( SWidth,  SHeight);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( SWidth, -SHeight);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-SWidth, -SHeight);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-SWidth,  SHeight);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

void drawPowerUp(int powerUpTexture)
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, powerUpTexture);
    float PHeight = 20.0;
    float PWidth = 20.0;
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( PWidth,  PHeight);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( PWidth, -PHeight);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-PWidth, -PHeight);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-PWidth,  PHeight);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

void drawSnot(float posA, float posB, int snotTexture)
{
    glPushMatrix();
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f); 
    glTranslatef(posA, posB, 0);
    glBindTexture(GL_TEXTURE_2D, snotTexture);
    float SnHeight = 10.0;
    float SnWidth = 10.0;
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( SnWidth,  SnHeight);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( SnWidth, -SnHeight);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-SnWidth, -SnHeight);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-SnWidth,  SnHeight);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}
