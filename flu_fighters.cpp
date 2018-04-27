//
//
//
//
//program: flu fighters
//authors:
//Tyler Sharp, Kyle Werts, Haley Hamer, Renee Romero
//date:    2014 - 2018
//mod spring 2015: added constructors
//mod spring 2018: X11 wrapper class
//This program is a game starting point for a 3350 project.
//
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include "fonts.h"
#include "log.h"
#include "haleyH.h"
#include "flu_fighters.h"
#include <ctime>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include <unistd.h>
//#include <GL/gl.h>
//#include <X11/Xutil.h>
//#include <GL/glu.h>

//defined types
typedef float Flt;
typedef float Vec[3];
typedef Flt	Matrix[4][4];

//macros
#define rnd() (((Flt)rand())/(Flt)RAND_MAX)
#define random(a) (rand()%(a))
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
			     (c)[1]=(a)[1]-(b)[1]; \
				 (c)[2]=(a)[2]-(b)[2]
//constants
const float TIMESLICE = 1.0f;
const float GRAVITY = -0.2f;
#define PI 3.141592653589793
#define ALPHA 1
const int MAX_BULLETS = 11;
const Flt MINIMUM_ASTEROID_SIZE = 60.0;

//-----------------------------------------------------------------------------
//Setup timers
const double OOBILLION = 1.0 / 1e9;
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Add Renee CPP
extern Gamestate State;
Gamestate gameState = STARTMENU;
extern void waves(struct Game *g, Gamestate gameState, Global gl);
//-----------------------------------------------------------------------------
//Add tylerS.cpp functions

int lives = 3;
extern void startMenu(int, int, int, int, int);
extern void waveMenu(int, int, int, int, int);
extern int drawPre(int);
extern int drawPost();
extern void drawShip(float, float, float, int);
extern void drawBullet(float, float, int);
extern void drawGBola(int, float);
extern void drawPowerUp(int);
extern void drawSnot(float, float,int);
extern void drawOverlay(int, int, int, int);
extern void drawTheBoss();
extern void drawSalmonella(int);
int cursorPos = 1;
//-----------------------------------------------------------------------------
// Add Kyle CPP
// Will take care of AMMO/Powerups in the future
extern void displayText();
//-----------------------------------------------------------------------------
// Create enemies from haleyH.cpp
void spawnGBola();
extern void moveGbola(Gbola *);
extern void moveSalmonella(Salmonella *);
extern void checkEnemyCollision(struct Game *);
extern void deleteGbola(struct Game *, Gbola *);
extern void deleteSalmonella(struct Game *, Salmonella *);
extern void shootG(Gbola *, int);


Shape s;

class Image {
public:
	int iWidth, iHeight;
	unsigned char *data;
	~Image() { delete [] data; }
	Image(const char *fname) {
		if (fname[0] == '\0')
			return;

		int ppmFlag = 0;
		char name[40];
		strcpy(name, fname);
		int slen = strlen(name);
		char ppmname[80];
		if (strncmp(name+(slen-4), ".ppm", 4) == 0)
			ppmFlag = 1;
		if (ppmFlag) {
			strcpy(ppmname, name);
		} else {
			name[slen-4] = '\0';
			sprintf(ppmname, "%s.ppm", name);

			char ts[100];

			sprintf(ts, "convert %s %s", fname, ppmname);
			system(ts);
		}
		FILE *fpi = fopen(ppmname, "r");
		if (fpi) {
			char line[200];
			fgets(line, 200, fpi);
			fgets(line, 200, fpi);
			while (line[0] == '#')
				fgets(line, 200, fpi);
			sscanf(line, "%i %i", &iWidth, &iHeight);
			fgets(line, 200, fpi);

			int n = iWidth * iHeight * 3;
			data = new unsigned char[n];
			for (int i=0; i<n; i++)
				data[i] = fgetc(fpi);
			fclose(fpi);
		} else {
			printf("ERROR opening image: %s\n", ppmname);
			exit(0);
		}
		if (!ppmFlag)
			unlink(ppmname);
	}
};
//PLACE IMAGES HERE, UPDATE LIST LENGTH-------------------------------------
Image img[8] = {
	"./ship.png", "./GBola.png", "./salmonella.png", "./TitleScreen.png",
	"./bullet.png", "./WaveScreen.png", "./powerUp.png", "./snot.png"
};

//DECLARE TEXTURE
GLuint shipTexture;
GLuint GBolaTexture;
GLuint salmonellaTexture;
GLuint TitleScreenTexture;
GLuint silhouetteTexture;
GLuint bulletTexture;
GLuint WaveScreenTexture;
GLuint powerUpTexture;
GLuint snotTexture;

//DECLARE IMAGE
Image *shipImage = NULL;
Image *GBolaImage = NULL;
Image *salmonellaImage = NULL;
Image *TitleScreenImage = NULL;
Image *bulletImage = NULL;
Image *WaveScreenImage = NULL;
Image *powerUpImage = NULL;
Image *snotImage = NULL;

Global::Global()
{
	thyme = 0.0;
	xres = 600;
	yres = 900;
	memset(keys, 0, 65536);
}

Global gl;

/*class Ship {
public:
	Vec dir;
	Vec pos;
	Vec vel;
	float angle;
	float color[3];
public:*/
Ship::Ship()
{
	VecZero(dir);
	pos[0] = (Flt)(gl.xres/2);
	pos[1] = (Flt)(gl.yres/2);
	pos[2] = 0.0f;
	VecZero(vel);
	angle = 0.0;
	//OPACITY
	color[0] = color[1] = color[2] = 1.0;
}

/*class Bullet {
public:
	Vec pos;
	Vec vel;
	float color[3];
	struct timespec time;
public:
	Bullet() { }
};*/
Bullet::Bullet() {}

/*Asteroid {
  public:
  Vec pos;
  Vec vel;
  int nverts;
  Flt radius;
  Vec vert[8];
  float angle;
  float rotate;
  float color[3];
  struct Asteroid *prev;
  struct Asteroid *next;
  public:*/
Asteroid::Asteroid() {
	prev = NULL;
	next = NULL;
}

/*class Game {
  public:
  Ship ship;
  Asteroid *ahead;
  Gbola *gbhead;
  Bullet *barr;
  int nasteroids;
  int nGbola;
  int nbullets;
  struct timespec bulletTimer;
  struct timespec mouseThrustTimer;
  bool mouseThrustOn;
  public:
  Game() {
  ahead = NULL;
  gbhead = NULL;
  barr = new Bullet[MAX_BULLETS];
  nasteroids = 0;
  nbullets = 0;
  nGbola = 0;
  mouseThrustOn = false;
//build 10 asteroids...
for (int j=0; j<3; j++) {
Asteroid *a = new Asteroid;
Gbola *gb = new Gbola((float)(rand() % (gl.xres-75)), 800.0f);
a->nverts = 8;
a->radius = rnd()*80.0 + 40.0;
Flt r2 = a->radius / 2.0;
Flt angle = 0.0f;
Flt inc = (PI * 2.0) / (Flt)a->nverts;
for (int i=0; i<a->nverts; i++) {
a->vert[i][0] = sin(angle) * (r2 + rnd() * a->radius);
a->vert[i][1] = cos(angle) * (r2 + rnd() * a->radius);
angle += inc;
}
a->pos[0] = (Flt)(rand() % gl.xres);
a->pos[1] = (Flt)(rand() % gl.yres);
a->pos[2] = 0.0f;
a->angle = 0.0;
a->rotate = rnd() * 4.0 - 2.0;
a->color[0] = 0.8;
a->color[1] = 0.8;
a->color[2] = 0.7;
a->vel[0] = (Flt)(rnd()*2.0-1.0);
a->vel[1] = (Flt)(rnd()*2.0-1.0);
//std::cout << "asteroid" << std::endl;
//add to front of linked list
a->next = ahead;
gb->next = gbhead;
if (ahead != NULL)
ahead->prev = a;
if (gbhead != NULL)
gbhead-> prev = gb;
ahead = a;
gbhead = gb;
++nasteroids;
++nGbola;
}
clock_gettime(CLOCK_REALTIME, &bulletTimer);
}
~Game() {
delete [] barr;
}
} g;*/
Game::Game()
{
	ahead = NULL;
	gbhead = NULL;
	shead = NULL;
	barr = new Bullet[MAX_BULLETS];
	nasteroids = 0;
	nbullets = 0;
	nGbola = 0;
	mouseThrustOn = false;
	//build 10 asteroids...

	//THIS CREATES GBOLA
	//if (gameState == WAVE1) {
		//for (int j=0; j<3; j++) {
			//Asteroid *a = new Asteroid;
		//	Gbola *gb = new Gbola((float)(rand() % (gl.xres-75)), 800.0f);
			//a->nverts = 8;
			//a->radius = rnd()*80.0 + 40.0;
			//Flt r2 = a->radius / 2.0;
			//Flt angle = 0.0f;
			//Flt inc = (PI * 2.0) / (Flt)a->nverts;
			//for (int i=0; i<a->nverts; i++) {
			//	a->vert[i][0] = sin(angle) * (r2 + rnd() * a->radius);
			//	a->vert[i][1] = cos(angle) * (r2 + rnd() * a->radius);
			//	angle += inc;
			//}
			//a->pos[0] = (Flt)(rand() % gl.xres);
			//a->pos[1] = (Flt)(rand() % gl.yres);
			//a->pos[2] = 0.0f;
			//a->angle = 0.0;
			//a->rotate = rnd() * 4.0 - 2.0;
			//a->color[0] = 0.8;
			//a->color[1] = 0.8;
			//a->color[2] = 0.7;
			//a->vel[0] = (Flt)(rnd()*2.0-1.0);
			//a->vel[1] = (Flt)(rnd()*2.0-1.0);
			//std::cout << "asteroid" << std::endl;
			//add to front of linked list
			//a->next = ahead;
		//	gb->next = gbhead;
			//if (ahead != NULL)
			//	ahead->prev = a;
		//	if (gbhead != NULL)
		//		gbhead-> prev = gb;
			//ahead = a;
		//	gbhead = gb;
			//++nasteroids;
		//	++nGbola;
		//}
	//}
	clock_gettime(CLOCK_REALTIME, &bulletTimer);

}

Game::~Game() {
	delete [] barr;
}

Game g;

void spawnGBola() {
	Gbola *gb = new Gbola((float)(rand() % (gl.xres-75)), 800.0f);
	gb->next = g.gbhead;
	if (g.gbhead != NULL)
		g.gbhead-> prev = gb;
	g.gbhead = gb;
	++g.nGbola;
}

void spawnSalmonella() {
	Salmonella *s = new Salmonella((float)(rand() % (gl.xres-75)), 800.0f);
	s->next = g.shead;
	if (g.shead != NULL)
		g.shead-> prev = s;
	g.shead = s;
	++g.nSalmonella;
}


//X Windows variables
class X11_wrapper {
private:
	Display *dpy;
	Window win;
	GLXContext glc;
public:
	X11_wrapper() {
		GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
		XSetWindowAttributes swa;
		setup_screen_res(gl.xres, gl.yres);
		dpy = XOpenDisplay(NULL);
		if (dpy == NULL) {
			std::cout << "\n\tcannot connect to X server" << std::endl;
			exit(EXIT_FAILURE);
		}
		Window root = DefaultRootWindow(dpy);
		XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
		if (vi == NULL) {
			std::cout << "\n\tno appropriate visual found\n" << std::endl;
			exit(EXIT_FAILURE);
		}
		Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
		swa.colormap = cmap;
		swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
			PointerMotionMask | MotionNotify | ButtonPress | ButtonRelease |
			StructureNotifyMask | SubstructureNotifyMask;
		win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
				vi->depth, InputOutput, vi->visual,
				CWColormap | CWEventMask, &swa);
		set_title();
		glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
		glXMakeCurrent(dpy, win, glc);
		show_mouse_cursor(0);
	}
	~X11_wrapper() {
		XDestroyWindow(dpy, win);
		XCloseDisplay(dpy);
	}
	void set_title() {
		//Set the window title bar.
		XMapWindow(dpy, win);
		XStoreName(dpy, win, "The Flu Fighters");
	}
	void check_resize(XEvent *e) {
		//The ConfigureNotify is sent by the
		//server if the window is resized.
		if (e->type != ConfigureNotify)
			return;
		XConfigureEvent xce = e->xconfigure;
		if (xce.width != gl.xres || xce.height != gl.yres) {
			//Window size did change.
			reshape_window(xce.width, xce.height);
		}
	}
	void reshape_window(int width, int height) {
		//window has been resized.
		setup_screen_res(width, height);
		glViewport(0, 0, (GLint)width, (GLint)height);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
		set_title();
	}
	void setup_screen_res(const int w, const int h) {
		gl.xres = w;
		gl.yres = h;
	}
	void swapBuffers() {
		glXSwapBuffers(dpy, win);
	}
	bool getXPending() {
		return XPending(dpy);
	}
	XEvent getXNextEvent() {
		XEvent e;
		XNextEvent(dpy, &e);
		return e;
	}
	void set_mouse_position(int x, int y) {
		XWarpPointer(dpy, None, win, 0, 0, 0, 0, x, y);
	}
	void show_mouse_cursor(const int onoff) {
		if (onoff) {
			//this removes our own blank cursor.
			XUndefineCursor(dpy, win);
			return;
		}
		//vars to make blank cursor
		Pixmap blank;
		XColor dummy;
		char data[1] = {0};
		Cursor cursor;
		//make a blank cursor
		blank = XCreateBitmapFromData (dpy, win, data, 1, 1);
		if (blank == None)
			std::cout << "error: out of memory." << std::endl;
		cursor = XCreatePixmapCursor(dpy, blank, blank, &dummy, &dummy, 0, 0);
		XFreePixmap(dpy, blank);
		//this makes you the cursor. then set it using this function
		XDefineCursor(dpy, win, cursor);
		//after you do not need the cursor anymore use this function.
		//it will undo the last change done by XDefineCursor
		//(thus do only use ONCE XDefineCursor and then XUndefineCursor):
	}
} x11;

//function prototypes
void init_opengl();
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void physics();
void render();

//==========================================================================
// M A I N
//==========================================================================
int main()
{
	logOpen();
	init_opengl();
	srand(time(NULL));
	//level_one();
	x11.set_mouse_position(100, 100);
	int done=0;
	while (!done) {
		while (x11.getXPending()) {
			XEvent e = x11.getXNextEvent();
			x11.check_resize(&e);
			check_mouse(&e);
			done = check_keys(&e);
		}
		physics();
		render();
		x11.swapBuffers();
	}
	cleanup_fonts();
	logClose();
	return 0;
}

unsigned char *buildAlphaData(Image *img)
{
	//add 4th component to RGB stream...
	int i;
	int a,b,c;
	unsigned char *newdata, *ptr;
	unsigned char *data = (unsigned char *)img->data;
	newdata = (unsigned char *)malloc(img->iWidth * img->iHeight * 4);
	ptr = newdata;
	for (i=0; i<img->iWidth * img->iHeight * 3; i+=3) {
		a = *(data+0);
		b = *(data+1);
		c = *(data+2);
		*(ptr+0) = a;
		*(ptr+1) = b;
		*(ptr+2) = c;
		//-----------------------------------------------
		//get largest color component...
		//*(ptr+3) = (unsigned char)((
		//		(int)*(ptr+0) +
		//		(int)*(ptr+1) +
		//		(int)*(ptr+2)) / 3);
		//d = a;
		//if (b >= a && b >= c) d = b;
		//if (c >= a && c >= b) d = c;
		//*(ptr+3) = d;
		//-----------------------------------------------
		//this code optimizes the commented code above.
		*(ptr+3) = (a|b|c);
		//-----------------------------------------------
		ptr += 4;
		data += 3;
	}
	return newdata;
}

void init_opengl()
{
	//OpenGL initialization
	glViewport(0, 0, gl.xres, gl.yres);
	//Initialize matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//This sets 2D mode (no perspective)
	glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
	//
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG);
	glDisable(GL_CULL_FACE);
	//
	//Clear the screen to black
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();
	//IMAGE STUFF-----------------------------------------------------
	glGenTextures(1, &silhouetteTexture);
	//SHIP STUFF------------------------------------------------------
	shipImage = &img[0];

	int sw = img[0].iWidth;
	int sh = img[0].iHeight;
	glGenTextures(1, &shipTexture);

	glBindTexture(GL_TEXTURE_2D, shipTexture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData = buildAlphaData(&img[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sw, sh, 0,
							GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	free(silhouetteData);

	//G_BOLA STUFF------------------------------------------------------
	GBolaImage = &img[1];
	int gw = img[1].iWidth;
	int gh = img[1].iHeight;
	glGenTextures(1, &GBolaTexture);

	glBindTexture(GL_TEXTURE_2D, GBolaTexture);
	//THIS WILL BE RGBA WITH TRANSPARENCY
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	silhouetteData = buildAlphaData(&img[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gw, gh, 0,
							GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	free(silhouetteData);
	//BULLET STUFF----------------------------------------------------------
	bulletImage = &img[4];
	int bw = img[4].iWidth;
	int bh = img[4].iHeight;
	glGenTextures(1, &bulletTexture);

	glBindTexture(GL_TEXTURE_2D, bulletTexture);
	//THIS WILL BE RGBA WITH TRANSPARENCY
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	silhouetteData = buildAlphaData(&img[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bw, bh, 0,
							GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	free(silhouetteData);

	//Salmonella STUFF------------------------------------------------------
	salmonellaImage = &img[2];
	int saw = img[1].iWidth;
	int sah = img[1].iHeight;
	glGenTextures(1, &salmonellaTexture);

	glBindTexture(GL_TEXTURE_2D, salmonellaTexture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	silhouetteData = buildAlphaData(&img[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, saw, sah, 0,
							GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);

	//TITLE SCREEN STUFF-----------------------------------------------
	TitleScreenImage = &img[3];
	int tw = img[3].iWidth;
	int th = img[3].iHeight;
	glGenTextures(1, &TitleScreenTexture);

	glBindTexture(GL_TEXTURE_2D, TitleScreenTexture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tw, th, 0,
		GL_RGB, GL_UNSIGNED_BYTE, img[3].data);

	//WAVE SCREEN STUFF---------------------------------------------------
	WaveScreenImage = &img[5];
	int ww = img[5].iWidth;
	int wh = img[5].iHeight;
	glGenTextures(1, &WaveScreenTexture);

	glBindTexture(GL_TEXTURE_2D, WaveScreenTexture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ww, wh, 0,
		GL_RGB, GL_UNSIGNED_BYTE, img[5].data);

	//POWER UP STUFF------------------------------------------------------
	powerUpImage = &img[6];
	int pw = img[6].iWidth;
	int ph = img[6].iHeight;
	glGenTextures(1, &powerUpTexture);

	glBindTexture(GL_TEXTURE_2D, powerUpTexture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	silhouetteData = buildAlphaData(&img[6]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pw, ph, 0,
							GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);

	//SNOT STUFF-----------------------------------------------------------
	snotImage = &img[7];
	int snw = img[7].iWidth;
	int snh = img[7].iHeight;
	glGenTextures(1, &snotTexture);

	glBindTexture(GL_TEXTURE_2D, snotTexture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	silhouetteData = buildAlphaData(&img[7]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, snw, snh, 0,
							GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
}
void normalize2d(Vec v)
{
	Flt len = v[0]*v[0] + v[1]*v[1];
	if (len == 0.0f) {
		v[0] = 1.0;
		v[1] = 0.0;
		return;
	}
	len = 1.0f / sqrt(len);
	v[0] *= len;
	v[1] *= len;
}

void check_mouse(XEvent *e)
{
	//Was a mouse button clicked?
	//static int savex = 0;
	//static int savey = 0;
	//static int ct=0;
	if (e->type != ButtonPress &&
			e->type != ButtonRelease &&
			e->type != MotionNotify)
		return;
	if (e->type == ButtonRelease)
		return;
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button is down
			//a little time between each bullet
			/*struct timespec bt;
			clock_gettime(CLOCK_REALTIME, &bt);
			double ts = timeDiff(&g.bulletTimer, &bt);
			if (ts > 0.1) {
				timeCopy(&g.bulletTimer, &bt);
				//shoot a bullet...
				if (g.nbullets < MAX_BULLETS) {
					Bullet *b = &g.barr[g.nbullets];
					timeCopy(&b->time, &bt);
					b->pos[0] = g.ship.pos[0];
					b->pos[1] = g.ship.pos[1];
					b->vel[0] = g.ship.vel[0];
					b->vel[1] = g.ship.vel[1];
					//convert ship angle to radians
					Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
					//convert angle to a vector
					Flt xdir = cos(rad);
					Flt ydir = sin(rad);
					b->pos[0] += xdir*20.0f;
					b->pos[1] += ydir*20.0f;
					b->vel[0] += xdir*6.0f + rnd()*0.1;
					b->vel[1] += ydir*6.0f + rnd()*0.1;
					b->color[0] = 1.0f;
					b->color[1] = 1.0f;
					b->color[2] = 1.0f;
					++g.nbullets;

				}
			}*/
		}
		if (e->xbutton.button==3) {
			//Right button is down
		}
	}
	if (e->type == MotionNotify) {/*
		if (savex != e->xbutton.x || savey != e->xbutton.y) {
			//Mouse moved
			int xdiff = savex - e->xbutton.x;
			int ydiff = savey - e->xbutton.y;
			if (++ct < 10)
				return;
			if (xdiff > 0) {
				//mouse moved along the x-axis.
				g.ship.angle += 0.05f * (float)xdiff;
				if (g.ship.angle >= 360.0f)
					g.ship.angle -= 360.0f;
			}
			else if (xdiff < 0) {
				g.ship.angle += 0.05f * (float)xdiff;
				if (g.ship.angle < 0.0f)
					g.ship.angle += 360.0f;
			}
			if (ydiff > 0) {
				//mouse moved along the y-axis.
				//apply thrust
				//convert ship angle to radians
				Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
				//convert angle to a vector
				Flt xdir = cos(rad);
				Flt ydir = sin(rad);
				g.ship.vel[0] += xdir * (float)ydiff * 0.001f;
				g.ship.vel[1] += ydir * (float)ydiff * 0.001f;
				Flt speed = sqrt(g.ship.vel[0]*g.ship.vel[0]+
					g.ship.vel[1]*g.ship.vel[1]);
				if (speed > 15.0f) {
					speed = 15.0f;
					normalize2d(g.ship.vel);
					g.ship.vel[0] *= speed;
					g.ship.vel[1] *= speed;
				}
				g.mouseThrustOn = true;
				clock_gettime(CLOCK_REALTIME, &g.mouseThrustTimer);
			}
			x11.set_mouse_position(100, 100);
			savex = savey = 100;
		}
	*/}
}

int check_keys(XEvent *e)
{
	//keyboard input?
	static int shift=0;
	if (e->type != KeyPress && e->type != KeyRelease)
		return 0;
	int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
	//Log("key: %i\n", key);
	if (e->type == KeyRelease) {
		gl.keys[key]=0;
		if (key == XK_Shift_L || key == XK_Shift_R)
			shift=0;
		return 0;
	}
	gl.keys[key]=1;
	if (key == XK_Shift_L || key == XK_Shift_R) {
		shift=1;
		return 0;
	}
	(void)shift;
	switch (key) {
		case XK_Escape:
			return 1;
		case XK_f:
			break;
		case XK_s:
			break;
		case XK_Down:
			break;
		case XK_equal:
			break;
		case XK_minus:
			break;
	}
	return 0;
}

void deleteAsteroid(Game *g, Asteroid *node)
{
	//Remove a node from doubly-linked list.
	//Must look at 4 special cases below.
	if (node->prev == NULL) {
		if (node->next == NULL) {
			//only 1 item in list.
			g->ahead = NULL;
		} else {
			//at beginning of list.
			node->next->prev = NULL;
			g->ahead = node->next;
		}
	} else {
		if (node->next == NULL) {
			//at end of list.
			node->prev->next = NULL;
		} else {
			//in middle of list.
			node->prev->next = node->next;
			node->next->prev = node->prev;
		}
	}
	delete node;
	node = NULL;
}

void buildAsteroidFragment(Asteroid *ta, Asteroid *a)
{
	//build ta from a
	ta->nverts = 8;
	ta->radius = a->radius / 2.0;
	Flt r2 = ta->radius / 2.0;
	Flt angle = 0.0f;
	Flt inc = (PI * 2.0) / (Flt)ta->nverts;
	for (int i=0; i<ta->nverts; i++) {
		ta->vert[i][0] = sin(angle) * (r2 + rnd() * ta->radius);
		ta->vert[i][1] = cos(angle) * (r2 + rnd() * ta->radius);
		angle += inc;
	}
	ta->pos[0] = a->pos[0] + rnd()*10.0-5.0;
	ta->pos[1] = a->pos[1] + rnd()*10.0-5.0;
	ta->pos[2] = 0.0f;
	ta->angle = 0.0;
	ta->rotate = a->rotate + (rnd() * 4.0 - 2.0);
	ta->color[0] = 0.8;
	ta->color[1] = 0.8;
	ta->color[2] = 0.7;
	ta->vel[0] = a->vel[0] + (rnd()*2.0-1.0);
	ta->vel[1] = a->vel[1] + (rnd()*2.0-1.0);
}

void physics()
{
	Flt d0,d1,dist;
	//Update ship position
	g.ship.pos[0] += g.ship.vel[0];
	g.ship.pos[1] += g.ship.vel[1];
	//Check for collision with window edges
	if (g.ship.pos[0] < 20.0) {
		g.ship.pos[0] += 4.0;
	}
	else if (g.ship.pos[0] > (float)gl.xres - 20) {
		g.ship.pos[0] -= 4.0;
	}
	else if (g.ship.pos[1] < 70.0) {
		g.ship.pos[1] += 4.0;
	}
	else if (g.ship.pos[1] > (float)gl.yres) {
		g.ship.pos[1] -= 4.0;
	}
	//
	//Update bullet positions
	struct timespec bt;
	clock_gettime(CLOCK_REALTIME, &bt);
	int i=0;
	while (i < g.nbullets) {
		Bullet *b = &g.barr[i];
		//How long has bullet been alive?
		double ts = timeDiff(&b->time, &bt);
		if (ts > 2.5) {
			//time to delete the bullet.
			memcpy(&g.barr[i], &g.barr[g.nbullets-1],
				sizeof(Bullet));
			g.nbullets--;
			//do not increment i.
			continue;
		}
		//move the bullet
		b->pos[0] += b->vel[0];
		b->pos[1] += b->vel[1];
		i++;
	}

	//Update snot positions

	int j=0;
	Gbola *gb = g.gbhead;
	while(gb)
	{
		struct timespec sbt;
		clock_gettime(CLOCK_REALTIME, &sbt);
		cout << "working on gbola " << j << endl;
		i=0;
		while (i < gb->nSbullets) {
			S_Bullet *sb = &(gb->sbarr[i]);
			//How long has bullet been alive?
			double ts = timeDiff(&sb->time, &sbt);
			if (ts > 12.0) {
				//time to delete the bullet.
				memcpy(&(gb->sbarr[i]), &(gb->sbarr[gb->nSbullets-1]),
					sizeof(S_Bullet));
				gb->nSbullets--;
				cout << "deleted snot" << endl;
				//do not increment i.
				//continue;
			}
			//move the snot bullet
			else {
				sb->pos[0] += sb->vel[0];
				sb->pos[1] += sb->vel[1];
				cout << "moved snot " << endl;
				i++;
			}
		}

		cout << "increment gbola" << endl;
		gb = gb->next;
		j++;
	}
	//Update asteroid positions
	//Update asteroid positions
	Asteroid *a = g.ahead;
	gb = g.gbhead;
	moveGbola(gb);

    //moveSnot(gb);
	while (a) {
		a->pos[0] += a->vel[0];
		a->pos[1] += a->vel[1];
		//Check for collision with window edges
		if (a->pos[0] < -100.0) {
			a->pos[0] += (float)gl.xres+200;
		}
		else if (a->pos[0] > (float)gl.xres+100) {
			a->pos[0] -= (float)gl.xres+200;
		}
		else if (a->pos[1] < -100.0) {
			a->pos[1] += (float)gl.yres+200;
		}
		else if (a->pos[1] > (float)gl.yres+100) {
			a->pos[1] -= (float)gl.yres+200;
		}
		a->angle += a->rotate;
		a = a->next;
	}
	//
	//Asteroid collision with bullets?
	//If collision detected:
	//   1. delete the bullet
	//   2. break the asteroid into pieces
	//      if asteroid small, delete it
	a = g.ahead;
	checkEnemyCollision(&g);
	while (a) {
		//is there a bullet within its radius?
		int i=0;
		while (i < g.nbullets) {
			Bullet *b = &g.barr[i];
			d0 = b->pos[0] - a->pos[0];
			d1 = b->pos[1] - a->pos[1];
			dist = (d0*d0 + d1*d1);
			if (dist < (a->radius*a->radius)) {
				//cout << "asteroid hit." << endl;
				//this asteroid is hit.
				if (a->radius > MINIMUM_ASTEROID_SIZE) {
					//break it into pieces.
					Asteroid *ta = a;
					buildAsteroidFragment(ta, a);
					int r = rand()%10+5;
					for (int k=0; k<r; k++) {
						//get the next asteroid position in the array
						Asteroid *ta = new Asteroid;
						buildAsteroidFragment(ta, a);
						//add to front of asteroid linked list
						ta->next = g.ahead;
						if (g.ahead != NULL)
							g.ahead->prev = ta;
						g.ahead = ta;
						g.nasteroids++;
					}
				} else {
					a->color[0] = 1.0;
					a->color[1] = 0.1;
					a->color[2] = 0.1;
					//asteroid is too small to break up
					//delete the asteroid and bullet
					Asteroid *savea = a->next;
					deleteAsteroid(&g, a);
					a = savea;
					g.nasteroids--;
				}
				//delete the bullet...
				memcpy(&g.barr[i], &g.barr[g.nbullets-1], sizeof(Bullet));
				g.nbullets--;
				if (a == NULL)
					break;
			}
			i++;
		}
		if (a == NULL)
			break;
		a = a->next;
	}
	//---------------------------------------------------
	//check keys pressed now
	if (gl.keys[XK_Left] && (gameState == WAVE1 || gameState == WAVE2
						 || gameState == WAVE3 || gameState == WAVE4
					 	 					   || gameState == WAVE5)) {
		if (g.ship.pos[0] < 0) {
			g.ship.pos[0] += 5.0;
		} else {
			g.ship.pos[0] -= 4.0;
		}
	}
	if (gl.keys[XK_Right] && (gameState == WAVE1 || gameState == WAVE2
						  || gameState == WAVE3 || gameState == WAVE4
					 	 					    || gameState == WAVE5)) {
		g.ship.pos[0] += 4.0;
	}
	if (gl.keys[XK_Up] && (gameState == WAVE1 || gameState == WAVE2
					   || gameState == WAVE3 || gameState == WAVE4
					 	 					 || gameState == WAVE5)) {
		g.ship.pos[1] += 4.0;
	} else if (gl.keys[XK_Up] && gameState == STARTMENU) {
		if (cursorPos >= 2) {
			cursorPos--;
			usleep(200000);
		} else {
			cursorPos = 3;
			usleep(200000);
		}
	} else if (gl.keys[XK_Up] && gameState == WAVEMENU) {
		if (cursorPos >= 2) {
			cursorPos--;
			usleep(200000);
		} else {
			cursorPos = 6;
			usleep(200000);
		}
	}
	if (gl.keys[XK_Down] && (gameState == WAVE1 || gameState == WAVE2
						 || gameState == WAVE3 || gameState == WAVE4
					 	 					   || gameState == WAVE5)) {
		g.ship.pos[1] -= 4.0;
	} else if (gl.keys[XK_Down] && gameState == STARTMENU) {
		if (cursorPos <= 2) {
			cursorPos++;
			usleep(200000);
		} else {
			cursorPos = 1;
			usleep(200000);
		}
	} else if (gl.keys[XK_Down] && gameState == WAVEMENU) {
		if (cursorPos <= 5) {
			cursorPos++;
			usleep(200000);
		} else {
			cursorPos = 1;
			usleep(200000);
		}
	}

	if (gl.keys[XK_space] && (gameState == WAVE1 || gameState == WAVE2
						  || gameState == WAVE3 || gameState == WAVE4
					 	 					    || gameState == WAVE5)) {
		//a little time between each bullet
		struct timespec bt;
		clock_gettime(CLOCK_REALTIME, &bt);
		double ts = timeDiff(&g.bulletTimer, &bt);
		if (ts > 0.5) {
			timeCopy(&g.bulletTimer, &bt);
			if (g.nbullets < MAX_BULLETS) {
				//shoot a bullet...
				//Bullet *b = new Bullet;
				Bullet *b = &g.barr[g.nbullets];
				timeCopy(&b->time, &bt);
				b->pos[0] = g.ship.pos[0];
				b->pos[1] = g.ship.pos[1];
				b->vel[0] = g.ship.vel[0];
				b->vel[1] = g.ship.vel[1];
				//convert ship angle to radians
				Flt rad = ((g.ship.angle+90.0) / 360.0f) * PI * 2.0;
				//convert angle to a vector
				Flt xdir = cos(rad);
				Flt ydir = sin(rad);
				b->pos[0] += xdir*20.0f;
				b->pos[1] += ydir*20.0f;
				b->vel[0] += xdir*6.0f + rnd()*0.1;
				b->vel[1] += ydir*6.0f + rnd()*0.1;
				b->color[0] = 1.0f;
				b->color[1] = 1.0f;
				b->color[2] = 1.0f;
				g.nbullets++;
			}
		}
	} else if (gl.keys[XK_space] && gameState == STARTMENU) {
		if (cursorPos == 1) {
			gameState = CUT0;
		} else if (cursorPos == 2) {
			usleep(500000);
			cursorPos = 1;
			gameState = WAVEMENU;
		} else if (cursorPos == 3) {
			exit(0);
		}
	} else if (gl.keys[XK_space] && gameState == WAVEMENU) {
		if (cursorPos == 1) {
			gameState = WAVE1;
		} else if (cursorPos == 2) {
			gameState = WAVE2;
		} else if (cursorPos == 3) {
			gameState = WAVE3;
		} else if (cursorPos == 4) {
			gameState = WAVE4;
		} else if (cursorPos == 5) {
			gameState = WAVE5;
		} else {
			usleep(500000);
			cursorPos = 2;
			gameState = STARTMENU;
		}
	}
	/*
	if (g.mouseThrustOn) {
		//should thrust be turned off
		struct timespec mtt;
		clock_gettime(CLOCK_REALTIME, &mtt);
		double tdif = timeDiff(&mtt, &g.mouseThrustTimer);
		if (tdif < -0.3)
			g.mouseThrustOn = false;
	}
	*/
}


void render()
{
	//TEXT IN THE TOP CORNER
	if (gameState == STARTMENU) {
		startMenu(gl.xres, gl.yres, TitleScreenTexture, GBolaTexture,
																	cursorPos);
	}
	if (gameState == WAVEMENU) {
		waveMenu(gl.xres, gl.yres, WaveScreenTexture, GBolaTexture,
																	cursorPos);
	}
	if (gameState == CUT0 || gameState == CUT1 || gameState == CUT2
			|| gameState == CUT3 || gameState == CUT4 || gameState == CUT5) {
		/*static double pthyme = 0.0;
 	    struct timespec fpthymeStart, fpthymeEnd;
		clock_gettime(CLOCK_REALTIME, &fpthymeStart);
		if (gameState == CUT0) {
			gameState++;
		} else if (gameState == CUT5) {
			gameState = STARTMENU;
		} else {
			//static double thyme = 0.0;
	 	    struct timespec fpthymeStart, fpthymeEnd;
			clock_gettime(CLOCK_REALTIME, &fpthymeStart);
			if (pthyme < 3.0) {
				drawPost();
			} else {
				gameState ++;
			}
			clock_gettime(CLOCK_REALTIME, &fpthymeEnd);
		    pthyme += timeDiff(&fpthymeStart, &fpthymeEnd);
		}

		clock_gettime(CLOCK_REALTIME, &fpthymeEnd);
	    pthyme += timeDiff(&fpthymeStart, &fpthymeEnd);*/

		if (gameState == CUT5) {
			gameState = STARTMENU;
		} else {
			int i = gameState;
			i++;
			clock_gettime(CLOCK_REALTIME, &gl.fthymeStart);
			gl.thyme = 0.0;
			gameState = static_cast<Gamestate>(i);
		}
	}
	if (gameState == WAVE1 || gameState == WAVE2
					   || gameState == WAVE3 || gameState == WAVE4
					 	 					 || gameState == WAVE5) {

		//static double thyme = 0.0;

 	    //struct timespec fthymeStart, fthymeEnd;
		//clock_gettime(CLOCK_REALTIME, &fthymeStart);
		glViewport(0, 0, gl.xres, gl.yres);
		//clear color buffer
		glClearColor(0.053f, .174f, .227f, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		//Draw the ship
		drawShip(g.ship.pos[0], g.ship.pos[1], g.ship.pos[2], shipTexture);

		waves(&g, gameState, gl);

		/*if (gl.thyme < 3.0) {
			if (gl.thyme < .5 || (gl.thyme > 1.0 && gl.thyme < 1.5) || (gl.thyme > 2.0
			 												&& gl.thyme < 2.5)) {
				drawPre(gameState);
			}
		}
		if (gl.thyme > 5000) {
			drawPost();
			if (gl.thyme > 5003) {
				//enemyCounter = 3;
				gameState ++;
				gl.thyme = 0;
			}
		}
		static int enemyCounter = 3;
		if (gl.thyme > 4) {
			while (enemyCounter > 0) {
				spawnGBola();
				enemyCounter --;
			}
		}
		*/
		//DRAW POWER UP

		//drawPowerUp(powerUpTexture);

		//DRAW SNOT

		//drawSnot(snotTexture);

		//Draw the enemies
		{
			//Asteroid *a = g.ahead;
			Gbola *gb = g.gbhead;
			/*	while (a) {
			//Log("draw asteroid...\n");
			glColor3fv(a->color);
			glPushMatrix();
			glTranslatef(a->pos[0], a->pos[1], a->pos[2]);
			//glTranslatef(gb->pos[0], gb->pos[1], gb->pos[2]);
			glRotatef(a->angle, 0.0f, 0.0f, 1.0f);
			//draw GBola
			drawGBola(GBolaTexture);
			a = a->next;
			//gb = gb->next;
			}*/
			while (gb)
			{
				glColor3fv(gb->color);
				glPushMatrix();
				glTranslatef(gb->pos[0], gb->pos[1], gb->pos[2]);
				glRotatef(gb->angle, 0.0f, 0.0f, 0.0f);

				drawGBola(GBolaTexture, gl.thyme);

				gb = gb->next;
			}
		}
		//----------------
		//Draw the bullets
		Bullet *b = &g.barr[0];
		for (int i=0; i<g.nbullets; i++) {
			//Log("draw bullet...\n");
			drawBullet(b->pos[0], b->pos[1], bulletTexture);
			/*glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_POINTS);
				glVertex2f(b->pos[0],      b->pos[1]);
				glVertex2f(b->pos[0]-1.0f, b->pos[1]);
				glVertex2f(b->pos[0]+1.0f, b->pos[1]);
				glVertex2f(b->pos[0],      b->pos[1]-1.0f);
				glVertex2f(b->pos[0],      b->pos[1]+1.0f);
				glColor3f(0.8, 0.8, 0.8);
				glVertex2f(b->pos[0]-1.0f, b->pos[1]-1.0f);
				glVertex2f(b->pos[0]-1.0f, b->pos[1]+1.0f);
				glVertex2f(b->pos[0]+1.0f, b->pos[1]-1.0f);
				glVertex2f(b->pos[0]+1.0f, b->pos[1]+1.0f);
			glEnd();*/
			++b;
		}

		Gbola *gb = g.gbhead;

  		shootG(gb, snotTexture);

		while (gb)
		{
			S_Bullet *sb = &(gb->sbarr[0]);
			for (int i=0; i<gb->nSbullets; i++)
			{
				//Log("draw bullet...\n");
				drawSnot(sb->pos[0], sb->pos[1], snotTexture);
				++sb;
				cout << "Drew a bullet" << endl;
			}

			gb = gb->next;
		}



		Rect r;
        r.bot = 500;
        r.left = 250;
        r.center = 0;
        ggprint16(&r, 16, 0xFB6AD0, "TIME: %f", gl.thyme);

		drawOverlay(gl.xres, gl.yres, lives, shipTexture);
        //CHANGE WAVES:
        if (gl.thyme > 10.0 && g.nGbola == 0 ) {
			gl.thyme = 5000;
			g.nGbola = 5;
			//enemyCounter = 3;
        	//gameState++;
		}

		clock_gettime(CLOCK_REALTIME, &gl.fthymeEnd);
	    gl.thyme = timeDiff(&gl.fthymeStart, &gl.fthymeEnd);
	}
}
