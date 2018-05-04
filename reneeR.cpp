/*
   Layout of Levels
*/

#include <iostream>
using namespace std;
#include <stdio.h>
#include "fonts.h"
#include <stdlib.h>
#include <ctime>
#include "haleyH.h"
#include "flu_fighters.h"
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
extern void spawnGBola();
extern int drawPre(int);
extern int drawPost();
extern void spawnGBola();
extern void spawnSalmonella();
double temp = 0.0;

void wave_one();
void wave_two();
void wave_three();
void wave_start(Gamestate gameState, Global *gl, State *s);
void wave_clear(Gamestate gameState, Global *gl, State *s);

int waves(Game *g, Gamestate gameState, Global *gl)
{
		double tw;
		if(gameState == WAVE1){
			////cout << "IN WAVE 1 w address: " << g->w1 << endl;
			if (g->w1 == NULL){
				////cout << "spawned a wave" << endl;
				g->w1 = new State;
				////cout << "w1 address: " << g->w1 << endl;
			}
			struct timespec w1_t;
			clock_gettime(CLOCK_REALTIME, &w1_t);
			tw = timeDiff(&(g->w1->stateTimer), &w1_t);
			wave_start(gameState, gl, g->w1);
			////cout << "TW: " << tw << endl;
			if(tw > 4){
				wave_one();
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
			////cout << "wave clear in here\n";
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
				////cout << "in wave two" << endl;
				wave_two();
			}
			if (g->nGbola == 0 && g->nSalmonella == 0 && tw > 4.5){
				gameState = CUT2;
				//cout << "leaving wave two" << endl;
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
				//cout << "in wave three" << endl;
				wave_three();
			}
			if (g->nGbola == 0 && g->nSalmonella == 0 && tw > 4.5){
				gameState = CUT3;
				//cout << "leaving wave two" << endl;
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
	//cout << "gameState as gameState from waves: " << gameState << endl;
	//cout << "gameState as int from waves: " << (int)gameState << endl;
	return (int)gameState;
}

void wave_start(Gamestate gameState, Global *gl, State *st)
{
	//cout << "in wave start " << endl;
	struct timespec ws;
	clock_gettime(CLOCK_REALTIME, &ws);
	double tw = timeDiff(&(st->stateTimer), &ws);
	//cout << "TW in WAVE START: " << tw << endl;
	if (tw < 4){
		if (gameState == WAVE1 || gameState == WAVE2 || gameState == WAVE3){
			if (tw < 0.5 || (tw >1.0 && tw  <  1.5) || (tw > 2.0 && tw < 2.5)) {
				drawPre(gameState);
			}
		}
		clock_gettime(CLOCK_REALTIME, &ws);
		tw = timeDiff(&(st->stateTimer), &ws);
		//cout << "TW in while: " << tw << endl;
	}
}

void wave_clear(Gamestate gameState, Global *gl, State *s)
{
	struct timespec wc;
	clock_gettime(CLOCK_REALTIME, &wc);
	double tw = timeDiff(&(s->stateTimer), &wc);
	if (tw < 4){
		if (gameState == CUT1 || gameState == CUT2 || gameState == CUT3) {
			//if (tw < 0.5 || (tw >1.0 && tw  <  1.5) || (tw > 2.0 && tw < 2.5)){
				////cout << "in clear\n";
				drawPost();
			//}
		}
		clock_gettime(CLOCK_REALTIME, &wc);
		tw = timeDiff(&(s->stateTimer), &wc);
	}
}

void wave_one()
{

	static int enemyCounter = 4;
	while(enemyCounter > 0)
	{
		spawnGBola();
		enemyCounter--;
	}
}

void wave_two()
{
	static int GbolaEnemyCounter = 2;
	static int SalmonellaEnemyCounter = 3;
	while(GbolaEnemyCounter > 0)
	{
		spawnGBola();
		GbolaEnemyCounter--;

	}
	while(SalmonellaEnemyCounter > 0)
	{
		spawnSalmonella();
		SalmonellaEnemyCounter--;

	}
}

void wave_three()
{
	static int GbolaEnemyCounter = 3;
	static int SalmonellaEnemyCounter = 4;
	while(GbolaEnemyCounter > 0)
	{
		spawnGBola();
		GbolaEnemyCounter--;

	}
	while(SalmonellaEnemyCounter > 0)
	{
		spawnSalmonella();
		SalmonellaEnemyCounter--;

	}
}
