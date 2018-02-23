/* Aurthor: Kyle Werts
 * Date: 2/23/2018
 * Flu Fighters Power up and ammo file 
 */ 
#include "Ammo.h"
#include <stdio.h>

int ActiveAmmo::ammoCount = 0;

ActiveAmmo::ActiveAmmo()
{
	next = 0;
	prev = 0;
	ammoCount++;
}

ActiveAmmo::~ActiveAmmo()
{
	ammoCount--;
}

void ActiveAmmo::init(float p[3], float v[3], float d)
{
	pos[0] = p[0];
	pos[1] = p[1];
	pos[2] = p[2];
	vel[0] = v[0];
	vel[1] = v[1];
	vel[2] = v[2];

	damage = d;
	next = 0;
	prev = 0;
}