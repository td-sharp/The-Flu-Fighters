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

extern void makeParticle(float, float, int);
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
extern void drawSnot(int SnotTexture);

void shootC(Cholora *);

float xres = 600;
float yres = 900;


using namespace std;

S_Bullet::S_Bullet() {}

Gbola::Gbola(float xpos, float ypos) 
{
    radius = 35.0f;
    pos[0] = xpos;
    pos[1] = ypos;
    pos[2] = 0.0;
    color[0] = 0.8;
    color[1] = 0.8;
    color[2] = 0.7;
    vel[0] = 1;
    vel[1] = -1;
    health = 30;
    prev = NULL;
    next = NULL;
    nSbullets = 0;
    clock_gettime(CLOCK_REALTIME, &sbulletTimer);
    sbarr = new S_Bullet[3];    

}   

Gbola::~Gbola()
{
    delete [] sbarr;
}


Salmonella::Salmonella(float xpos, float ypos)
{
    xradius = 20.0f;
    yradius = 35.0f;
    pos[0] = xpos;
    pos[1] = ypos;
    pos[2] = 0.0f;
    color[0] = 0.8;
    color[1] = 0.8;
    color[2] = 0.7;
    vel[0] = 1;
    vel[1] = -1;
    health = 50;
    prev = NULL;
    next = NULL;
    nSbullets = 0;
    clock_gettime(CLOCK_REALTIME, &sbulletTimer);
    sbarr = new S_Bullet[3];    
}

Salmonella::~Salmonella()
{
    delete [] sbarr;
}

Cholora::Cholora(float xpos, float ypos)
{
    radius = 35.0f;
    pos[0] = xpos;
    pos[1] = ypos;
    xdest = (float)(rand() % 550) + 20.0f;
    ydest = (float)(rand() % 450) + 400.0f;
    pos[2] = 0.0;
    color[0] = 0.8;
    color[1] = 0.8;
    color[2] = 0.7;
    vel[0] = 1;
    vel[1] = -1;
    accelerate = 0;
	health = 70;
    prev = NULL;
    next = NULL;
    nSbullets = 0;
    clock_gettime(CLOCK_REALTIME, &sbulletTimer);
    sbarr = new S_Bullet[4];    

}

Cholora::~Cholora()
{
    delete [] sbarr;
}

void moveGbola(Gbola *g)
{
    bool ispos = true;
    while(g)
    {   if (ispos)
        {
            g->pos[0]+= g->vel[0];
            if (g->pos[0] < 40)
            {
                g->pos[0] = 40;
                g->vel[0] = -g->vel[0];
            }
            else if (g->pos[0] > xres-40)
            {   
                g->pos[0] = xres-40;
                g->vel[0] = -g->vel[0];
            }
            ispos = false;
        }
        else
        {
            g->pos[0] -= g->vel[0];
            if (g->pos[0] < 40)
            {
                g->pos[0] = 40;
                g->vel[0] = -g->vel[0];
            }
            else if (g->pos[0] > xres-40)
            {   
                g->pos[0] = xres-40;
                g->vel[0] = -g->vel[0];
            }
            ispos = true;
        }

        g = g->next;                 
    }
}

void shootG(Gbola *gb)
{
    while (gb)
    {
        struct timespec bt;
        clock_gettime(CLOCK_REALTIME, &bt);
        double ts = timeDiff(&gb->sbulletTimer, &bt);
        if (ts > 8.0)
        {
            timeCopy(&(gb->sbulletTimer), &bt);
            if (gb->nSbullets < 2)
            {
                S_Bullet *sb = &(gb->sbarr[gb->nSbullets]);
                timeCopy(&sb->time, &bt);
                timeCopy(&gb->sbulletTimer, &bt);
                sb->pos[0] = gb->pos[0];
                sb->pos[1] = gb->pos[1];
                sb->vel[0] = 0;
                sb->vel[1] = -2;
                sb->color[0] = 1.0f;
                sb->color[1] = 1.0f;
                sb->color[2] = 1.0f;
                gb->nSbullets++;
                //cout << "made a Snot Bullet" << endl;
                //cout << "now there are " << gb->nSbullets << " snots" << endl;
            }
        }
        gb = gb->next;
    }


}

void moveSalmonella(Salmonella *s)
{

    while(s)
    {   
        s->pos[0]+= s->vel[0];
        if (s->pos[0] < 20)
        {
             s->pos[0] = 20;
            s->vel[0] = -s->vel[0];
        }
        else if (s->pos[0] > xres-20)
        {   
            s->pos[0] = xres-20;
            s->vel[0] = -s->vel[0];
        }
            
        s->pos[1]-= s->vel[1];
        if (s->pos[1] < 300)
        {
            s->pos[1] = 300;
            s->vel[1] = -s->vel[1];
        }
        else if (s->pos[1] > yres-40)
        {
            s->pos[1] = yres-40;
            s->vel[1] = -s->vel[1];
        }

        s = s->next;                 
    } 
}

void shootS(Salmonella *s, Game *g)
{
    while (s)
    {
        struct timespec bt;
        clock_gettime(CLOCK_REALTIME, &bt);
        double ts = timeDiff(&s->sbulletTimer, &bt);
        if (ts > (rnd() + 4))
        {
            timeCopy(&(s->sbulletTimer), &bt);
            if (s->nSbullets < 3)
            {
                S_Bullet *sb = &(s->sbarr[s->nSbullets]);
                timeCopy(&sb->time, &bt);
                timeCopy(&s->sbulletTimer, &bt);
                sb->pos[0] = s->pos[0];
                sb->pos[1] = s->pos[1];
                float xdist = (g->ship.pos[0] - sb->pos[0]);
                float ydist = (g->ship.pos[1] - sb->pos[1]);
                float direction = atan2(ydist, xdist);
                float speed = 3.0f;
                sb->vel[0] = speed * cos(direction);
                sb->vel[1] = speed * sin(direction);                
                sb->color[0] = 1.0f;
                sb->color[1] = 1.0f;
                sb->color[2] = 1.0f;
                s->nSbullets++;
            }
        }
        s = s->next;    
    }
}

void moveCholora(Cholora *c)
{	
    while(c)
    {   
        struct timespec ct;
        clock_gettime(CLOCK_REALTIME, &ct);
        if (timeDiff(&c->waitTimer, &ct) > 1.0)
        { 
            if (abs(c->pos[0] - c->xdest) < 5 && abs(c->pos[1] == c->ydest) < 5)
            {
                c->xdest = (float)(rand() % 550) + 20.0f;
                c->ydest = (float)(rand() % 450) + 350.0f;
                clock_gettime(CLOCK_REALTIME, &c->waitTimer);
                shootC(c);
            }
            else 
            {
                float xdist = (c->xdest - c->pos[0]);
                float ydist = (c->ydest - c->pos[1]);
                float direction = atan2(ydist, xdist);
                float speedx = 4.0f;
                float speedy = 4.0f;
                c->vel[0] = speedx * cos(direction);
                c->vel[1] = speedy * sin(direction);
                c->pos[0] += c->vel[0];
                c->pos[1] += c->vel[1];   
            }
        }

        c = c->next;
    } 
}

void shootC(Cholora *c)
{
    struct timespec ct;
    clock_gettime(CLOCK_REALTIME, &ct);
    double ts = timeDiff(&c->sbulletTimer, &ct);
    if (ts > 3.0)
    {
        if (c->nSbullets < 4)
        {
            S_Bullet *sb = &(c->sbarr[c->nSbullets]);
            timeCopy(&sb->time, &ct);
            timeCopy(&c->sbulletTimer, &ct);
            sb->pos[0] = c->pos[0];
            sb->pos[1] = c->pos[1];
            sb->vel[0] = 0;
            sb->vel[1] = 0;
            sb->color[0] = 1.0f;
            sb->color[1] = 1.0f;
            sb->color[2] = 1.0f;
            c->nSbullets++;
            //cout << "made a Snot Bullet" << endl;
            //cout << "now there are " << gb->nSbullets << " snots" << endl;
        }
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
    for (int i=0; i<100; i++)
        makeParticle(g->pos[0], g->pos[1], 0);
    delete g;
    g = NULL;
}

void deleteSalmonella(Game *game, Salmonella *s)
{
    if (s->prev == NULL)
    {
        if (s->next == NULL)
            game->shead = NULL;
        else
        {
            s->next->prev = NULL;
            game->shead = s->next;
        }
    }
    else
    {
        if (s->next == NULL)
            s->prev->next = NULL;
        else
        {
            s->prev->next = s->next;
            s->next->prev = s->prev;
        }
    }
    for (int i=0; i<100; i++)
        makeParticle(s->pos[0], s->pos[1], 1);
    delete s;
    s = NULL;
}

void deleteCholora(Game *game, Cholora *c)
{
    if (c->prev == NULL)
    {
        if (c->next == NULL)
        {
            game->chead = NULL;
        }
        else
        {
            c->next->prev = NULL;
            game->chead = c->next;
        }
    }
    else
    {
        if (c->next == NULL)
            c->prev->next = NULL;
        else
        {
            c->prev->next = c->next;
            c->next->prev = c->prev;
        }
    }
    for (int i=0; i<100; i++)
        makeParticle(c->pos[0], c->pos[1], 2);
    delete c;
    c = NULL;
}

void checkEnemyCollision(Game *game)
{
    Gbola *g;
    g = game->gbhead;

    while(g)
    {
        int i = 0;
        while (i < game->nbullets)
        {
            Bullet *b = &(game->barr[i]);
            if (b->pos[0] > g->pos[0] - g->radius && b->pos[0] < g->pos[0] + g->radius &&
                b->pos[1] > g->pos[1] - g->radius && b->pos[1] < g->pos[1] + g->radius)
            {
                g->health = g->health - 10;

                if (g->health <= 0)
                {
                    g->color[0] = 1.0;
                    g->color[1] = 0.1;
                    g->color[2] = 0.1;
                    Gbola *saveg = g->next;
                    deleteGbola(game,g);
                    g = saveg;
                    game->nGbola--;
                }

                memcpy(&(game->barr[i]), 
                        &(game->barr[game->nbullets-1]),sizeof(Bullet));
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

    Salmonella *s;  
    s = game->shead;    

    while(s)
    {
        int i = 0;
        while (i < game->nbullets)
        {
            Bullet *b = &(game->barr[i]);
            if (b->pos[0] > s->pos[0] - s->xradius && b->pos[0] < s->pos[0] + s->xradius &&
                b->pos[1] > s->pos[1] - s->yradius && b->pos[1] < s->pos[1] + s->yradius)
            {
                s->health = s->health - 10;

                if (s->health <= 0)
                {
                    s->color[0] = 1.0;
                    s->color[1] = 0.1;
                    s->color[2] = 0.1;
                    Salmonella *saves = s->next;
                    deleteSalmonella(game,s);
                    s = saves;
                    game->nSalmonella--;
                }

                memcpy(&(game->barr[i]), 
                        &(game->barr[game->nbullets-1]), sizeof(Bullet));
                game->nbullets--;
                if (s == NULL)
                    break;
            }
            i++;
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
        while (i < game->nbullets)
        {
            Bullet *b = &(game->barr[i]);
            if (b->pos[0] > c->pos[0] - c->radius && b->pos[0] < c->pos[0] + c->radius &&
                b->pos[1] > c->pos[1] - c->radius && b->pos[1] < c->pos[1] + c->radius)
            {
                c->health = c->health - 10;

                if (c->health <= 0)
                {
                    c->color[0] = 1.0;
                    c->color[1] = 0.1;
                    c->color[2] = 0.1;
                    Cholora *savec = c->next;
                    deleteCholora(game,c);
                    c = savec;
                    game->nCholora--;
                }

                memcpy(&(game->barr[i]), 
                        &(game->barr[game->nbullets-1]), sizeof(Bullet));
                game->nbullets--;
                if (c == NULL)
                    break;
            }
            i++;
        }
        if (c == NULL)
            break;
        c = c->next;
    }
}
