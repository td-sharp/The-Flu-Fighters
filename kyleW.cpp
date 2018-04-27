/* Aurthor: Kyle Werts
 * Date: 2/23/2018
 * Flu Fighters Power up, ammo, boss
 
#include "kyleW.h"
#include <time.h>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "flu_fighters.h"

#define NUM_ENEMY_AMMO_TYPES 4;
#define AMMO_REFILL 150;
#define BigBadBoss_HEALTH 1000;

using namespace std;

extern double timeDiff(struct timespec *start, struct timespec *end);

BigBadBoss::BigBadBoss(float xpos, float ypos, float rotation, float acceleration, float SpecialPower) 
{
    nverts = 8;
    radius = rnd()*80.0 + 40.0;
    float r2 = radius / 2.0;
    float angle = 0.0f;
    float inc = (PI * 2.0) / (float)nverts;
    for (int i=0; i <nverts; i++) {
        vert[i][0] = sin(angle) * (r2 + rnd() * radius);
        vert[i][1] = cos(angle) * (r2 + rnd() * radius);
        angle += inc;
    }

    pos[0] = xpos;
    pos[1] = ypos;
    pos[2] = 0.0f;
    angle = 0.0;
    color[0] = 0.8;
    color[1] = 0.8;
    color[2] = 0.7;
    vel[0] = 1;
    vel[1] = -1;
    SpecPower = SpecialPower;
    rotate = rotation;
    accelerate = acceleration;
    health = BigBadBoss_HEALTH;
    prev = NULL;
    next = NULL;
}
 Not yet working. Will continue after Gordon's Progress Report

void BossAmmo::addAmmo(int type, float pos[3], float vel[3])
{
    //Need to add different varients of ammo


}
// firing rates cannot be adjusted by game->speedAdj -- still needs testing

void BigBadBoss::update()
{
    float v[3] = { 0.0, -0.2, 0.0 };
    float *hpos = game->hero->getPos();
    float a = hpos[0]-pos[0];
    float b = hpos[1]-pos[1];
    float dist;
    float ammoSpeed = 0.35*game->speedAdj;

    //update age
    age++;
    shootInterval--;

    pos[0] += secondaryMove[0]*game->speedAdj;
    pos[1] += secondaryMove[1]*game->speedAdj;
    float s = (1.0-game->speedAdj)+(game->speedAdj*0.7);
    secondaryMove[0] *= s;
    secondaryMove[1] *= s;
    move();

    float p[3] = { pos[0], pos[1], pos[2] };

    //Main Snot gun
    if (fabs(a) < 1.6) { 
    
        v[1] = -0.6;
        p[1] = pos[1]-1.7;
        game->BossAmmo->addAmmo(3, p, v);
    }
    // Side Snot guns
    if (!(age%5)) { 
    
        shootSwap++;
        shootSwap %= 15;

        if (shootSwap < 6) {
            v[1] = -0.2;
            p[1] = pos[1]-1.9;
            p[0] = pos[0]+2.0+((shootSwap%3)*0.4);
            game->BossAmmo->addAmmo(0, p, v);
            p[0] = pos[0]-2.0-((shootSwap%3)*0.4);
            game->BossAmmo->addAmmo(0, p, v);
        }
    }
    if (!((age-1)%7)) {
        dist = fabs(a) + fabs(b);
        shootVec[0] = ammoSpeed*a/dist;
        shootVec[1] = ammoSpeed*b/dist;
    }
    // Snomni shooters
    if (!((age/200)%2)) { 
        
        if (!((age/100)%2)) {

            if (!((age/50)%2)) {

                p[1] = pos[1]-0.45;
                p[0] = pos[0]-1.1;
                game->BossAmmo->addAmmo(1, p, shootVec);
                p[0] = pos[0]+1.1;
                game->BossAmmo->addAmmo(1, p, shootVec);
            }
            preFire = (age%100)/100.0f;
        }
        else if (!(age%10)) {

            p[1] = pos[1]-0.45;
            b = hpos[1]-p[1];

            p[0] = pos[0]-1.1;
            a = hpos[0]-p[0];
            dist = fabs(a) + fabs(b);
            shootVec[0] = 2.0*ammoSpeed*a/dist;
            shootVec[1] = 2.0*ammoSpeed*b/dist;
            game->BossAmmo->addAmmo(2, p, shootVec);
            p[0] = pos[0]+1.1;
            a = hpos[0]-p[0];
            dist = fabs(a) + fabs(b);
            shootVec[0] = 2.0*ammoSpeed*a/dist;
            shootVec[1] = 2.0*ammoSpeed*b/dist;
            game->BossAmmo->addAmmo(2, p, shootVec);
            preFire -= 0.4;

            if (preFire < 0.0)
                preFire = 0.0;
        }
        else
            preFire += 0.035;
    }
    else
        preFire = 0.0;
}


float *BigBadBoss::getPos()
{
    epos[0] =  pos[0];
    epos[1] =  pos[1];
    epos[2] =  pos[2];
    return epos;
}

void BigBadBoss::move()
{
    float *hpos;
    if (target) {
        hpos = target->getPos();
    }
    else
        hpos = pos;
    float diff[2] = { hpos[0]-pos[0], hpos[1]-pos[1] };

    //I want this to be based off difficulty and gameSkill
    float approachDist;

    approachDist = 7.0*(2.0-game->gameSkill);
    if (fabs(diff[1]) < (approachDist+0.0*sin(game->frame*0.05)) ) {
        diff[1] = diff[1] * diff[1]/approachDist;
    }
    diff[0] += 5.0*sin(age*0.1);
    lastMoveX = (0.98*lastMoveX)+(0.0005*game->gameSkill*diff[0]);
    lastMoveY = (0.90*lastMoveY)+(0.001*game->gameSkill*diff[1]);
    pos[0] += game->speedAdj*(lastMoveX);
    pos[1] += game->speedAdj*(lastMoveY+vel[1]);

}

void BigBadBoss::calcShootInterval()
{
    shootInterval = 1;
}

void deleteBigBadBoss (Game *game, BigBadBoss *bbb)
{
    if (BigBadBoss_HEALTH = 0) {
        delete bbb; 
        bbb = NULL;
    }
}
*/
