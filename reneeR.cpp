/* 
   Renee Romero
   CMPS 3350
   Lab 5
   02-25-18
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
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void spawnGBola();
extern int drawPre(int);
extern int drawPost();
extern void spawnGBola();
extern void spawnSalmonella();

void wave_one();
void wave_two();
void check_time(Gamestate gameState, Global gl);

void waves(Game *g, Gamestate gameState, Global gl)
{	
		check_time(gameState, gl);
		if(gameState == WAVE1 && gl.thyme > 4)
		{
			wave_one();
			gameState = WAVE2;
		
			/*
			static int enemyCounter = 4;
			while(enemyCounter > 0)
			{
				spawnGBola();	
				enemyCounter--;	
			}
			*/	
		}
		check_time(gameState, gl);
		if(gameState == WAVE2 && gl.thyme > 4 && g->nGbola == 0)
		{
			wave_two();
			gameState = WAVE3;
		}
		/*
		check_time();
		if(gameState == WAVE3 && thyme > 4 && g->nGbola == 0 && g->nSalmonella == 0)
		{
			wave_threee();
			gameState = WAVE4;
		}
		*/

}
void check_time(Gamestate gameState, Global gl)
{
	if (gl.thyme < 3.0) 
	{
		if (gl.thyme < .5 || (gl.thyme > 1.0 && gl.thyme < 1.5) || (gl.thyme > 2.0
			 												&& gl.thyme < 2.5)) {
				drawPre(gameState);
			}
		}
		if (gl.thyme > 5000) {
			drawPost();
			if (gl.thyme > 5003) {
				//enemyCounter = 3;
				int i = gameState;
				i++;
				gameState = static_cast<Gamestate>(i);
				gl.thyme = 0;
			}
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
//	static int SalmonellaEnemyCounter = 4;
	while(GbolaEnemyCounter > 0)
	{
		spawnGBola();
		GbolaEnemyCounter--;

	}
//	while(SalmonellaEnemyCounter > 0)
//	{
//		spawnSalmonella();
//		SalmonellaEnemyCounter--;

//	}
}
/*
void wave_threee()
{
static int GbolaEnemyCounter = 4;
	static int SalmonellaEnemyCounter = 7;
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
*/
