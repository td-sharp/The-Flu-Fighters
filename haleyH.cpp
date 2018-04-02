#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <GL/glx.h>
#include <ctime>
#include <cmath>
#include "fonts.h"
#include "haleyH.h"
#include "flu_fighters.h"

#define GBOLA_HEALTH  50;
#define SALMONELLA_HEALTH 100;
#define CHOLERA_HEALTH 150;
#define  rnd() (((float)rand())/(float)RAND_MAX)
#define PI  3.141592653589793


extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);

float xres = 600;
float yres = 900;


using namespace std;

Gbola::Gbola(float xpos, float ypos) 
{
	nverts = 8;
	radius = rnd()*80.0 + 40.0;
	float r2 = radius / 2.0;
	float angle = 0.0f;
	float inc = (PI * 2.0) / (float)nverts;
	for (int i=0; i<nverts; i++)
	{
		vert[i][0] = sin(angle) * (r2 + rnd() * radius);
		vert[i][1] = cos(angle) * (r2 + rnd() * radius);
		angle += inc;
	}
	pos[0] = xpos;
	pos[1] = ypos;
	pos[2] = 0.0;
	angle = 0.0f;
	color[0] = 0.8;
	color[1] = 0.8;
	color[2] = 0.7;
	vel[0] = 1;
	vel[1] = 0;
	health = GBOLA_HEALTH;
	prev = NULL;
	next = NULL;	
			
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


void moveGbola(Gbola *g)
{
	bool ispos = true;
	while(g)
	{	if (ispos)
		{
			g->pos[0]+= g->vel[0];
			if (g->pos[0] < 100)
			{
				g->pos[0] = 100;
				g->vel[0] = -g->vel[0];
			}
			else if (g->pos[0] > xres-100)
			{	
				g->pos[0] = xres-100;
				g->vel[0] = -g->vel[0];
			}
			ispos = false;
		}
		else
		{
			g->pos[0] -= g->vel[0];
			if (g->pos[0] < 100)
			{
				g->pos[0] = 100;
				g->vel[0] = -g->vel[0];
			}
			else if (g->pos[0] > xres-100)
			{	
				g->pos[0] = xres-100;
				g->vel[0] = -g->vel[0];
			}
			ispos = true;
		}

		g = g->next;				 
	}
} 

void deleteGbola(Game *game, Gbola *g)
{
	if (g->prev == NULL)
	{
		if (g->next == NULL)
			game->gbhead = NULL;
		else
		{
			g->next->prev = NULL;
			game->gbhead = g->next;
		}
	}
	else
	{
		if (g->next == NULL)
			g->prev->next = NULL;
		else
		{
			g->prev->next = g->next;
			g->next->prev = g->prev;
		}
	}

	delete g;
	g = NULL;
}

	
void checkGbolaCollision(Game *game)
{
	Gbola *g;
	g = game->gbhead;
	float d0, d1, dist;

	while(g)
	{
		int i = 0;
		while (i < game->nbullets)
		{
			Bullet *b = &(game->barr[i]);
			d0 = b->pos[0] - g->pos[0];
			d1 = b->pos[1] - g->pos[1];
			dist = (d0 * d0 + d1 * d1);
			if (dist < (g->radius * g->radius))
			{
				g->color[0] = 1.0;
				g->color[1] = 0.1;
				g->color[2] = 0.1;
				Gbola *saveg = g->next;
				deleteGbola(game,g);
				g = saveg;
				game->nGbola--;
				
				memcpy(&(game->barr[i]), &(game->barr[game->nbullets-1]),
					sizeof(Bullet));
				game->nbullets--;
				if (g == NULL)
					break;
			}
			i++;
		}
		if (g == NULL)
			break;
		g = g->next;
	}
} 
