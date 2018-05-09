/*
   Renee Romero
   Layout of Levels
*/

#include <iostream>
using namespace std;
#include <stdio.h>
#include <string.h>
#include "fonts.h"
#include <stdlib.h>
#include <ctime>
#include "haleyH.h"
#include "flu_fighters.h"
extern void makeParticle(float, float, int);
extern struct timespec timeStart, timeCurrent;
extern void gameOver(int, int, int);
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
extern int drawPre(int);
extern int drawPost();
void spawnGBola(Game *, float);
void spawnSalmonella(Game *, float);
void wave_one(Game *);
void wave_two(Game *);
void wave_three(Game *);
void wave_start(Gamestate gameState, Global *gl, State *s);
void wave_clear(Gamestate gameState, Global *gl, State *s);

int waves(Game *g, Gamestate gameState, Global *gl, int ship_lives)
{
		double tw;

		if(ship_lives == 0)
		{

			//gameState = GAMEOVER;
		}
		if(gameState == WAVE1){
			if (g->w1 == NULL){
				g->w1 = new State;
			}
			struct timespec w1_t;
			clock_gettime(CLOCK_REALTIME, &w1_t);
			tw = timeDiff(&(g->w1->stateTimer), &w1_t);
			wave_start(gameState, gl, g->w1);
			if(tw > 4){
				wave_one(g);
			}
			if (g->nGbola == 0 && tw > 4.5){
				gameState = CUT1;
				if (g->c1 == NULL)
					g->c1 = new State;
			}
		}else if( g->nGbola == 0 && gameState == CUT1){
			struct timespec c1_t;
			clock_gettime(CLOCK_REALTIME, &c1_t);
			tw = timeDiff(&(g->c1->stateTimer), &c1_t);
			wave_clear(gameState, gl, g->c1);
			if(tw > 4){
				gameState = WAVE2;
				if (g->w2 == NULL)
					g->w2 = new State;
			}
		}else if (gameState == WAVE2){
			struct timespec w2_t;
			clock_gettime(CLOCK_REALTIME, &w2_t);
			tw = timeDiff(&(g->w2->stateTimer), &w2_t);
			wave_start(gameState, gl, g->w2);
		 	if (tw > 4){
				wave_two(g);
			}
			if (g->nGbola == 0 && g->nSalmonella == 0 && tw > 4.5){
				gameState = CUT2;
				if (g->c2 == NULL)
					g->c2 = new State;
			}
		}else if( g->nGbola == 0 && g->nSalmonella == 0 && gameState == CUT2){
			struct timespec c2_t;
			clock_gettime(CLOCK_REALTIME, &c2_t);
			tw = timeDiff(&(g->c2->stateTimer), &c2_t);
			wave_clear(gameState, gl, g->c2);
			if(tw > 4){
				gameState = WAVE3;
				if (g->w3 == NULL)
					g->w3 = new State;
			}
		}else if (gameState == WAVE3){
			struct timespec w3_t;
			clock_gettime(CLOCK_REALTIME, &w3_t);
			tw = timeDiff(&(g->w3->stateTimer), &w3_t);
			wave_start(gameState, gl, g->w3);
		 	if (tw > 4){
				wave_three(g);
			}
			if (g->nGbola == 0 && g->nSalmonella == 0 && tw > 4.5){
				gameState = CUT3;
				if (g->c3 == NULL)
					g->c3 = new State;
			}
		}else if( g->nGbola == 0 && g->nSalmonella == 0 && gameState == CUT3){
			struct timespec c3_t;
			clock_gettime(CLOCK_REALTIME, &c3_t);
			tw = timeDiff(&(g->c3->stateTimer), &c3_t);
			wave_clear(gameState, gl, g->c3);
			if(tw > 4){
				gameState = WAVE3;
				if (g->w3 == NULL)
					g->w3 = new State;
			}
		}else{
			gameState = GAMEOVER;
			//wave_start(gameState, gl);
		}
	return (int)gameState;
}

void wave_start(Gamestate gameState, Global *gl, State *st)
{
	struct timespec ws;
	clock_gettime(CLOCK_REALTIME, &ws);
	double tw = timeDiff(&(st->stateTimer), &ws);
	if (tw < 4){
		if (gameState == WAVE1 || gameState == WAVE2 || gameState == WAVE3){
			if (tw < 0.5 || (tw >1.0 && tw  <  1.5) || (tw > 2.0 && tw < 3.5)){
				drawPre(gameState);
			}
		}
		clock_gettime(CLOCK_REALTIME, &ws);
		tw = timeDiff(&(st->stateTimer), &ws);
	}
}

void wave_clear(Gamestate gameState, Global *gl, State *s)
{
	struct timespec wc;
	clock_gettime(CLOCK_REALTIME, &wc);
	double tw = timeDiff(&(s->stateTimer), &wc);
	if (tw < 4){
		if (gameState == CUT1 || gameState == CUT2 || gameState == CUT3) {
		//	if (tw < 0.5 || (tw >1.0 && tw  <  1.5) || (tw > 2.0 && tw < 2.5)){
				drawPost();
		//	}
		}
		clock_gettime(CLOCK_REALTIME, &wc);
		tw = timeDiff(&(s->stateTimer), &wc);
	}
}

void wave_one(Game *g)
{

	static int GbolaEnemyCounter = 4;
	float gx = 40.0f;
	float inc = 520.0f / 4.0f;

	while(GbolaEnemyCounter > 0)
	{
		//cout << "gx: " << gx << endl;
		//cout << "inc: " << inc << endl;
		spawnGBola(g, gx);
		GbolaEnemyCounter--;
		gx += inc;
	}
}

void wave_two(Game *g)
{
	static int GbolaEnemyCounter = 2;
	static int SalmonellaEnemyCounter = 3;
	float gx = 40.0f;
	float sx = 20.0f;
	float g_inc = 520.0f / 2.0f;
	float s_inc = 520.0f / 3.0f;


	while(GbolaEnemyCounter > 0)
	{
		spawnGBola(g, gx);
		GbolaEnemyCounter--;
		gx += g_inc;

	}
	while(SalmonellaEnemyCounter > 0)
	{
		spawnSalmonella(g, sx);
		SalmonellaEnemyCounter--;
		sx += s_inc;

	}
}

void wave_three(Game *g)
{
	static int GbolaEnemyCounter = 3;
	static int SalmonellaEnemyCounter = 4;
	float gx = 40.0f;
	float sx = 20.0f;
	float g_inc = 520.0f / 3.0f;
	float s_inc = 520.0f / 4.0f;


	while(GbolaEnemyCounter > 0)
	{
		spawnGBola(g, gx);
		GbolaEnemyCounter--;
		gx += g_inc;

	}
	while(SalmonellaEnemyCounter > 0)
	{
		spawnSalmonella(g, sx);
		SalmonellaEnemyCounter--;
		sx += s_inc;

	}
}

int check_ship_collisions(Game *game, int ship_lives)
{
	Gbola *g;
	g = game->gbhead;
	while(g)
	{
        int i = 0;
        while (i < g->nSbullets)
        {
            S_Bullet *b = &(g->sbarr[i]);
            if (b->pos[0] > game->ship.pos[0] - game->ship.radius &&
            	b->pos[0] < game->ship.pos[0] + game->ship.radius &&
            	b->pos[1] > game->ship.pos[1] - game->ship.radius &&
            	b->pos[1] < game->ship.pos[1] + game->ship.radius ){
				for (int j = 0; j < 30; j++) {
					makeParticle(game->ship.pos[0], game->ship.pos[1], 2);
				}
            	ship_lives--;
                memcpy(&(g->sbarr[i]), &(g->sbarr[g->nSbullets-1]),sizeof(S_Bullet));
                g->nSbullets--;
                if (g == NULL)
                    break;
            }

            i++;
        }

        if (g == NULL)
            break;
        g = g->next;
    }

    Salmonella *s;
	s = game->shead;
	while(s)
	{
        int i = 0;
        while (i < s->nSbullets)
        {
            S_Bullet *b = &(s->sbarr[i]);
            if (b->pos[0] > game->ship.pos[0] - game->ship.radius &&
            	b->pos[0] < game->ship.pos[0] + game->ship.radius &&
            	b->pos[1] > game->ship.pos[1] - game->ship.radius &&
            	b->pos[1] < game->ship.pos[1] + game->ship.radius ){
				for (int j = 0; j < 30; j++) {
					makeParticle(game->ship.pos[0], game->ship.pos[1], 2);
				}
            	ship_lives--;
                memcpy(&(s->sbarr[i]), &(s->sbarr[s->nSbullets-1]),sizeof(S_Bullet));
                s->nSbullets--;
                if (s == NULL)
                    break;
            }

            i++;
        }

        if (s == NULL)
            break;
        s = s->next;
    }

	return ship_lives;

}

void spawnGBola(Game *g, float x) {
	Gbola *gb = new Gbola(x, 800.0f);
	gb->next = g->gbhead;
	if (g->gbhead != NULL)
		g->gbhead-> prev = gb;
	g->gbhead = gb;
	++g->nGbola;
	cout << "x pos: " << x << endl;
}

void spawnSalmonella(Game *g, float x) {
	Salmonella *s = new Salmonella(x, 800.0f);
	s->next = g->shead;
	if (g->shead != NULL)
		g->shead-> prev = s;
	g->shead = s;
	++g->nSalmonella;
}

void spawnCholora(Game *g, float x) {
	Cholora *c = new Cholora(x, 850.0f, 0, 0);
	c->next = g->chead;
	if (g->chead != NULL)
		g->chead-> prev = c;
	g->chead = c;
	++g->nCholora;
}
