using namespace std;
#include "fonts.h"
#include <GL/glx.h>
#include <ctime>

extern double timeDiff(struct timespec *start, struct timespec *end);

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
/*void drawOverlay(int xres, int yres, int lives, int overlaidTexture,
                                                    int shipTexture)
{
    glBindTexture(GL_TEXTURE_2D, overlaidTexture);
    static float angle = 0.0;
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    angle = angle + 2.5;

    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( xres, 60.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( xres, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f( 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f( 0.0f, 60.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    
    Rect r;
    r.bot = 20;
    r.left = 20;
    r.center = 0;
    ggprint16(&r, 16, 0xFB6AD0, "LIVES");
    for (int i = 0; i < lives; i++) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glPushMatrix();

        glTranslatef(70*(i+2), 30, 0.0f);

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
} */

double drawShip(float posA, float posB, float posC, int shipTexture)
{
    static float angle = 0.0;
    static double thyme = 0.0;
    struct timespec fthymeStart, fthymeEnd;
    clock_gettime(CLOCK_REALTIME, &fthymeStart);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(posA, posB, posC);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(50, 50, 0);
    angle = angle + 2.5;
    glBindTexture(GL_TEXTURE_2D, shipTexture);
    //glRotatef(g.ship.angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 30.0f,  30.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 30.0f, -30.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-30.0f, -30.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-30.0f,  30.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    clock_gettime(CLOCK_REALTIME, &fthymeEnd);
    thyme += timeDiff(&fthymeStart, &fthymeEnd);
    return thyme;
}

double drawShipOPTIMIZED(float posA, float posB, float posC, int shipTexture)
{
    //static float move = 0.0;
    static double thyme = 0.0;
    struct timespec fthymeStart, fthymeEnd;
    clock_gettime(CLOCK_REALTIME, &fthymeStart);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(posA+60, posB, posC);
    //glRotatef(angle, 0.0f, 0.0f, 1.0f);

    //angle = angle + 2.5;
    glBindTexture(GL_TEXTURE_2D, shipTexture);
    //glRotatef(g.ship.angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 30.0f,  30.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 30.0f, -30.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-30.0f, -30.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-30.0f,  30.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    clock_gettime(CLOCK_REALTIME, &fthymeEnd);
    thyme += timeDiff(&fthymeStart, &fthymeEnd);
    return thyme;
}

void drawGBola(int GBolaTexture)
{
    glBindTexture(GL_TEXTURE_2D, GBolaTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 80.0f,  80.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 80.0f, -80.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-80.0f, -80.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-80.0f,  80.0f);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnd();
    glPopMatrix();
}

/*void drawSalmonella(int salmonellaTexture)
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
}*/
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
