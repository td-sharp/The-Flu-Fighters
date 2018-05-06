using namespace std;
#include "fonts.h"
#include <GL/glx.h>
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <cstdlib>

typedef float Flt;
typedef float Vec[3];

struct Shape {
	float width, height;
	float radius;
	Vec center;
};

struct Particle {
	Shape s;
	Vec velocity;
};

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

void gameOver(int xres, int yres, int gameOverTexture)
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, gameOverTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( xres, yres);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( xres, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f( 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex2f( 0.0f, yres);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void drawPre(int gameState)
{
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

void drawShip(float posA, float posB, float posC, int shipTexture, int lives)
{
    glPushMatrix();
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
	switch (lives) {
		case (3) : glColor3f(1.0f, 1.0f, 1.0f); break;
		case (2) : glColor3f(1.0f, 0.4f, 0.8f); break;
		case (1) : glColor3f(0.8f, 0.2f, 0.3f); break;
		default : glColor3f(1.0f, 1.0f, 1.0f);
	}
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
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBindTexture(GL_TEXTURE_2D, GBolaTexture);
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

void drawSalmonella(int salmonellaTexture, int salmonella2Texture, float thyme)
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    if ((int)thyme % 2 != 0) {
        glBindTexture(GL_TEXTURE_2D, salmonellaTexture);
    } else {
        glBindTexture(GL_TEXTURE_2D, salmonella2Texture);
    }
    float SHeight = 40.0;
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

void drawCholora(int choloraTexture, float thyme)
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, choloraTexture);
    float CHeight = 40.0;
    float CWidth = 40.0;
    glBegin(GL_QUADS);
	if ((int)thyme % 2 != 0) {
		glTexCoord2f(1.0f, 0.0f); glVertex2f( CWidth,  CHeight);
		glTexCoord2f(1.0f, 1.0f); glVertex2f( CWidth, -CHeight);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-CWidth, -CHeight);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-CWidth,  CHeight);
	} else {
		glTexCoord2f(1.0f, 0.0f); glVertex2f(-CWidth,  CHeight);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(-CWidth, -CHeight);
		glTexCoord2f(0.0f, 1.0f); glVertex2f( CWidth, -CHeight);
		glTexCoord2f(0.0f, 0.0f); glVertex2f( CWidth,  CHeight);
	}
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

float w = 2;
float h = 2;
const int MAX_PARTICLES = 1000;
int n;
int flag;
Particle particle[MAX_PARTICLES];

void makeParticle(float x, float y, int fl)
{
	flag = fl;
	if (n >= MAX_PARTICLES)
		return;
	Particle *p = &particle[n];
	p->s.center[0] = x;
	p->s.center[1] = y;
	float xVel = (float) (rand() % 50) - 25;
    float yVel = (float) (rand() % 50) - 25;
	p->velocity[1] = yVel;
	p->velocity[0] = xVel;
	++n;
}

float fakeTime = 0;
float yVel = 2.0f;
void drawCredits(int xres, int yres, int GBolaTexture, int salmonellaTexture,
	int salmonella2Texture, int choloraTexture)
{
	if ((int) yVel % 100 == 0 ) {
		fakeTime += 1;
	}

	Rect r;
    r.bot = yVel;
    r.left = xres/2 - 90;
    r.center = 0;
    ggprint16(&r, 16, 0xFB6AD0, "Thanks for playing!");

	Rect s;
    s.bot = yVel - 500;
    s.left = xres/2 - 70;
    s.center = 0;
    ggprint16(&s, 16, 0xFB6AD0, "Starring:");

	Rect g;
    g.bot = yVel - 700;
    g.left = xres/2 - 200;
    g.center = 0;
    ggprint16(&g, 16, 0xFB6AD0, "\"The G\" G-Bola");

	glPushMatrix();
	glTranslatef(xres/2 + 10, yVel - 700, 0);

	drawGBola(GBolaTexture, fakeTime);

	Rect sa;
    sa.bot = yVel - 1000;
    sa.left = xres/2 - 200;
    sa.center = 0;
    ggprint16(&sa, 16, 0xFB6AD0, "\"Sassy\" Salmonella");

	glPushMatrix();
	glTranslatef(xres/2 + 10, yVel - 1000, 0);

	drawSalmonella(salmonellaTexture, salmonella2Texture, fakeTime);

	Rect c;
    c.bot = yVel - 1300;
    c.left = xres/2 - 200;
    c.center = 0;
    ggprint16(&c, 16, 0xFB6AD0, "Cholo-ra");

	glPushMatrix();
	glTranslatef(xres/2 + 10, yVel - 1300, 0);

	drawCholora(choloraTexture, fakeTime);

	Rect h;
    h.bot = yVel - 1700;
    h.left = 100;
    h.center = 0;
    ggprint16(&h, 16, 0xFB6AD0,
		"Haley Hamer: Enemies");

	Rect re;
    re.bot = yVel - 1800;
    re.left = 100;
    re.center = 0;
    ggprint16(&re, 16, 0xFB6AD0,
		"Renee Romero: Waves");

	Rect t;
    t.bot = yVel - 1900;
    t.left = 100;
    t.center = 0;
    ggprint16(&t, 16, 0xFB6AD0,
		"Tyler Sharp: Graphics");
	yVel += 2.0;
}

void moveParticle(int xres, int yres)
{
	if (n > 0) {
		for (int i = 0; i < n; i++) {
			Particle *p = &particle[i];
			p->s.center[0] += p->velocity[0];
			p->s.center[1] += p->velocity[1];
			if (p->s.center[1] < 0.0 || p->s.center[1] > yres ||
							p->s.center[0] < 0.0 || p->s.center[0] > xres) {
				particle[i] = particle[ --n ];
			}
		}
	}
}

void drawBlood()
{
	for (int i = 0; i < n; i++) {
		float px = particle[i].s.center[0];
		float py = particle[i].s.center[1];
        glPushMatrix();
		if (flag == 0) {
        	glColor3f(0.016f, 0.019f, 0.94f);
		} else if (flag == 1) {
			glColor3f(0.94f, 0.019f, 0.016f);
		} else if (flag == 2) {
			glColor3f(0.0f, 1.0f, 0.0f);
		}
		glBegin(GL_QUADS);
            glVertex2i(px-w, py-h);
            glVertex2i(px-w, py+h);
            glVertex2i(px+w, py+h);
            glVertex2i(px+w, py-h);
        glEnd();
        glPopMatrix();
    }
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

void drawBackgroundThing(int backgroundThingTexture,
	int backgroundThing2Texture, int xres, float yBGVel, float size)
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
	float color = 20/size;
	glColor3f(color, color, color);
	if ((int) size % 3 == 0) {
		glBindTexture(GL_TEXTURE_2D, backgroundThing2Texture);
	} else {
		glBindTexture(GL_TEXTURE_2D, backgroundThingTexture);
	}
    float BHeight = size;
    float BWidth = size;
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( BWidth,  BHeight);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( BWidth, -BHeight);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-BWidth, -BHeight);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-BWidth,  BHeight);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}
