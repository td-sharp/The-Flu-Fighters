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
extern void deleteGbola(Game *game, Gbola *g);
extern void deleteSalmonella(Game *game, Salmonella *s);
extern void deleteCholora(Game *game, Cholora *c);
void spawnGBola(Game *, float);
void spawnSalmonella(Game *, float);
void spawnCholora(Game *, float);
void wave_one(Game *);
void wave_two(Game *);
void wave_three(Game *);
void wave_four(Game *);
void wave_five(Game *);
void wave_start(Gamestate gameState, State *s);
void wave_clear(Gamestate gameState, State *s);

int waves(Game *g, Gamestate gameState, int ship_lives)
{
		double tw;

		if(ship_lives == 0)
		{
			//if (g->go == NULL){
			//	g->go = new State;
			//}
			gameState = GAMEOVER;
			//struct timespec go_t;
			//clock_gettime(CLOCK_REALTIME, &go_t);
			//tw = timeDiff(&(g->go->stateTimer), &go_t);
			//wave_start(gameState, g->w1);
			//if(tw > 4)
			//	gameState = GAMEOVERC;
		}
		if(gameState == WAVE1){
			if (g->w1 == NULL){
				g->w1 = new State;
			}
			struct timespec w1_t;
			clock_gettime(CLOCK_REALTIME, &w1_t);
			tw = timeDiff(&(g->w1->stateTimer), &w1_t);
			wave_start(gameState, g->w1);
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
			wave_clear(gameState, g->c1);
			if(tw > 4){
				gameState = WAVE2;
				if (g->w2 == NULL)
					g->w2 = new State;
			}
		}else if (gameState == WAVE2){
			struct timespec w2_t;
			clock_gettime(CLOCK_REALTIME, &w2_t);
			tw = timeDiff(&(g->w2->stateTimer), &w2_t);
			wave_start(gameState, g->w2);
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
			wave_clear(gameState, g->c2);
			if(tw > 4){
				gameState = WAVE3;
				if (g->w3 == NULL)
					g->w3 = new State;
			}
		}else if (gameState == WAVE3){
			struct timespec w3_t;
			clock_gettime(CLOCK_REALTIME, &w3_t);
			tw = timeDiff(&(g->w3->stateTimer), &w3_t);
			wave_start(gameState, g->w3);
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
			wave_clear(gameState, g->c3);
			if(tw > 4){
				gameState = WAVE4;
				if (g->w4 == NULL)
					g->w4 = new State;
			}
		}else if (gameState == WAVE4){
			struct timespec w4_t;
			clock_gettime(CLOCK_REALTIME, &w4_t);
			tw = timeDiff(&(g->w4->stateTimer), &w4_t);
			wave_start(gameState, g->w4);
		 	if (tw > 4){
				wave_four(g);
			}
			if (g->nGbola == 0 && g->nSalmonella == 0 &&
				g->nCholora == 0 && tw > 4.5){
				gameState = CUT4;
				if (g->c4 == NULL)
					g->c4 = new State;
			}
		}else if( g->nGbola == 0 && g->nSalmonella == 0 &&
				  g->nCholora == 0 && gameState == CUT4){
			struct timespec c4_t;
			clock_gettime(CLOCK_REALTIME, &c4_t);
			tw = timeDiff(&(g->c4->stateTimer), &c4_t);
			wave_clear(gameState,g->c4);
			if(tw > 4){
				gameState = WAVE5;
				if (g->w5 == NULL)
					g->w5 = new State;
			}
		}else if (gameState == WAVE5){
			struct timespec w5_t;
			clock_gettime(CLOCK_REALTIME, &w5_t);
			tw = timeDiff(&(g->w5->stateTimer), &w5_t);
			wave_start(gameState, g->w5);
		 	if (tw > 4){
				wave_five(g);
			}
			if (g->nGbola == 0 && g->nSalmonella == 0 && tw > 4.5){
				gameState = CUT5;
				if (g->c5 == NULL)
					g->c5 = new State;
			}
		}else if( g->nGbola == 0 && g->nSalmonella == 0 &&
				  g->nCholora == 0 && gameState == CUT5){
			struct timespec c5_t;
			clock_gettime(CLOCK_REALTIME, &c5_t);
			tw = timeDiff(&(g->c5->stateTimer), &c5_t);
			wave_clear(gameState, g->c5);
			gameState = GAMEOVERC;
			//if(tw > 4){
			//	gameState = BOSS;
			//	if (g->wb == NULL)
			//		g->wb = new State;

		}else{
			gameState = GAMEOVER;
			//wave_start(gameState, gl);
		}
	return (int)gameState;
}

void wave_start(Gamestate gameState, State *st)
{
	struct timespec ws;
	clock_gettime(CLOCK_REALTIME, &ws);
	double tw = timeDiff(&(st->stateTimer), &ws);
	if (tw < 4){
		if (gameState == WAVE1 || gameState == WAVE2 || gameState == WAVE3 ||
			gameState == WAVE4 || gameState == WAVE5){
			if (tw < 0.5 || (tw >1.0 && tw  <  1.5) || (tw > 2.0 && tw < 3.5)){
				drawPre(gameState);
			}
		}
		clock_gettime(CLOCK_REALTIME, &ws);
		tw = timeDiff(&(st->stateTimer), &ws);
	}
}

void wave_clear(Gamestate gameState, State *s)
{
	struct timespec wc;
	clock_gettime(CLOCK_REALTIME, &wc);
	double tw = timeDiff(&(s->stateTimer), &wc);
	if (tw < 4){
		if (gameState == CUT1 || gameState == CUT2 || gameState == CUT3 ||
			gameState == CUT4 || gameState == CUT5) {
			//if (tw < 0.5 || (tw >1.0 && tw  <  1.5) || (tw > 2.0 && tw < 2.5)){
			drawPost();
			//}
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


void wave_four(Game *g)
{
	static int GbolaEnemyCounter = 3;
	static int SalmonellaEnemyCounter = 2;
	static int CholoraEnemyCounter = 3;
	float gx = 40.0f;
	float sx = 20.0f;
	float cx = 35.0f;
	float g_inc = 520.0f / 3.0f;
	float s_inc = 520.0f / 2.0f;
	float c_inc = 520.0f / 3.0f;


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
	while(CholoraEnemyCounter > 0)
	{
		spawnCholora(g, cx);
		CholoraEnemyCounter--;
		cx += c_inc;

	}
}

void wave_five(Game *g)
{
	static int GbolaEnemyCounter = 2;
	static int SalmonellaEnemyCounter = 4;
	static int CholoraEnemyCounter = 4;
	float gx = 40.0f;
	float sx = 20.0f;
	float cx = 35.0f;
	float g_inc = 520.0f / 2.0f;
	float s_inc = 520.0f / 4.0f;
	float c_inc = 520.0f / 4.0f;


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
	while(CholoraEnemyCounter > 0)
	{
		spawnCholora(g, cx);
		CholoraEnemyCounter--;
		cx += c_inc;

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
            	ship_lives--;
                memcpy(&(g->sbarr[i]), &(g->sbarr[g->nSbullets-1]),sizeof(S_Bullet));
                g->nSbullets--;
            }

            i++;
        }
        if ((game->ship.pos[0] - game->ship.radius > g->pos[0] - g->radius ||
        	 game->ship.pos[0] + game->ship.radius > g->pos[0] - g->radius)&&
            (game->ship.pos[0] - game->ship.radius < g->pos[0] + g->radius ||
             game->ship.pos[0] + game->ship.radius < g->pos[0] + g->radius) &&
            (game->ship.pos[1] - game->ship.radius > g->pos[1] - g->radius ||
             game->ship.pos[1] + game->ship.radius > g->pos[1] - g->radius) &&
            (game->ship.pos[1] - game->ship.radius < g->pos[1] + g->radius ||
             game->ship.pos[1] + game->ship.radius < g->pos[1] + g->radius)){
        	ship_lives--;
        	Gbola *saveg = g->next;
            deleteGbola(game,g);
            g = saveg;
            game->nGbola--;
        	if (g == NULL)
                    break;
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
            	ship_lives--;
                memcpy(&(s->sbarr[i]), &(s->sbarr[s->nSbullets-1]),sizeof(S_Bullet));
                s->nSbullets--;
            }

            i++;
        }
        if ((game->ship.pos[0] - game->ship.radius > s->pos[0] - s->xradius ||
        	 game->ship.pos[0] + game->ship.radius > s->pos[0] - s->xradius)&&
            (game->ship.pos[0] - game->ship.radius < s->pos[0] + s->xradius ||
             game->ship.pos[0] + game->ship.radius < s->pos[0] + s->xradius) &&
            (game->ship.pos[1] - game->ship.radius > s->pos[1] - s->yradius ||
             game->ship.pos[1] + game->ship.radius > s->pos[1] - s->yradius) &&
            (game->ship.pos[1] - game->ship.radius < s->pos[1] + s->yradius ||
             game->ship.pos[1] + game->ship.radius < s->pos[1] + s->yradius)){
        	ship_lives--;

            Salmonella *saves = s->next;
            deleteSalmonella(game,s);
            s = saves;
            game->nSalmonella--;
        	if (s== NULL)
                    break;
        }
        if (s == NULL)
            break;
        s = s->next;
    }

    Cholora *c;
	c = game->chead;
	while(c)
	{
        int i = 0;
        while (i < c->nSbullets)
        {
            S_Bullet *b = &(c->sbarr[i]);
            if (b->pos[0] > game->ship.pos[0] - game->ship.radius &&
            	b->pos[0] < game->ship.pos[0] + game->ship.radius &&
            	b->pos[1] > game->ship.pos[1] - game->ship.radius &&
            	b->pos[1] < game->ship.pos[1] + game->ship.radius ){
            	ship_lives--;
                memcpy(&(c->sbarr[i]), &(c->sbarr[c->nSbullets-1]),sizeof(S_Bullet));
                c->nSbullets--;
            }

            i++;
        }
        if ((game->ship.pos[0] - game->ship.radius > c->pos[0] - c->radius ||
        	 game->ship.pos[0] + game->ship.radius > c->pos[0] - c->radius)&&
            (game->ship.pos[0] - game->ship.radius < c->pos[0] + c->radius ||
             game->ship.pos[0] + game->ship.radius < c->pos[0] + c->radius) &&
            (game->ship.pos[1] - game->ship.radius > c->pos[1] - c->radius ||
             game->ship.pos[1] + game->ship.radius > c->pos[1] - c->radius) &&
            (game->ship.pos[1] - game->ship.radius < c->pos[1] + c->radius ||
             game->ship.pos[1] + game->ship.radius < c->pos[1] + c->radius)){
        	ship_lives--;
        	Cholora *savec = c->next;
            deleteCholora(game, c);
            c = savec;
            game->nCholora--;
        	if (c == NULL)
                    break;
        }

        if (c == NULL)
            break;
        c = c->next;
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
	Cholora *c = new Cholora(x, 850.0f);
	c->next = g->chead;
	if (g->chead != NULL)
		g->chead-> prev = c;
	g->chead = c;
	++g->nCholora;
}
