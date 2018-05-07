/* Aurthor: Kyle Werts
 * Date: 05/06/2018
 * Flu Fighters Power up, Sound, Boss
 */

#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif

#include <time.h>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "fonts.h"
#include "log.h"
#include <iostream>


#define NUM_ENEMY_AMMO_TYPES 4;
#define AMMO_REFILL 150;
#define BigBadBoss_HEALTH 1000;
#define wobble 50;

using namespace std;

void displayText();
void drawSalmonella();

extern double timeDiff(struct timespec *start, struct timespec *end);
extern bool audio_on;

#ifdef USE_OPENAL_SOUND
ALuint alSource;
ALuint themeSource;
ALuint alBuffer; 

extern void initial_sounds() 
{
    alutInit(0, NULL);
    if ( alGetError() != AL_NO_ERROR ) {
        printf("Error initializing sound\n");
        return;
    }
    alGetError();
    float vec[6] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, vec);
    alListenerf(AL_GAIN, 1.0f);
}

extern void clean_sounds()
{
    ALCcontext *Context = alcGetCurrentContext();
    ALCdevice *Device = alcGetContextsDevice(Context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(Context);
    alcCloseDevice(Device);
}

extern void Laser_Gun_Shot()
{
    //ALuint alBuffer;
    alBuffer = alutCreateBufferFromFile("./Sounds/Laser_Gun_Shot.wav");

    //ALuint alSource;
    alGenSources(1, &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);
    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
        printf("Error, Sound Source is Incorrect\n");
        return;
    }
    alSourcePlay(alSource);
}

extern void SnotShot()
{
    //ALuint alBuffer;
    alBuffer = alutCreateBufferFromFile("./Sounds/SnotShot.wav");

    //ALuint alSource;
    alGenSources(1, &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);
    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
        printf("Error, Sound Source is Incorrect\n");
        return;
    }
    alSourcePlay(alSource);
}

extern void Enemy_Explosion()
{
    //ALuint alBuffer;
    alBuffer = alutCreateBufferFromFile("./Sounds/EnemyExplosion.wav");

    //ALuint alSource;
    alGenSources(1, &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);
    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
        printf("Error, Sound Source is Incorrect\n");
        return;
    }
    alSourcePlay(alSource);
}

extern void PowerUP_Sound()
{
    //ALuint alBuffer;
    alBuffer = alutCreateBufferFromFile("./Sounds/Power-UP.wav");

    //ALuint alSource;
    alGenSources(1, &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);
    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
        printf("Error, Sound Source is Incorrect\n");
        return;
    }

    alSourcePlay(alSource);
}

extern void Boss_Explosion()
{
    //ALuint alBuffer;
    alBuffer = alutCreateBufferFromFile("./Sounds/BossExplosion.wav");

    //ALuint alSource;
    alGenSources(1, &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);
    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
        printf("Error, Sound Source is Incorrect\n");
        return;
    }

    alSourcePlay(alSource);
}

extern void PlayTheme()
{
    //ALuint alBuffer;
    alBuffer = alutCreateBufferFromFile("./Sounds/ThemeMusic.wav");

    alGenSources(1, &themeSource);
    alSourcei(themeSource, AL_BUFFER, alBuffer);

    alSourcef(themeSource, AL_GAIN, .30f);
    alSourcef(themeSource, AL_PITCH, 1.0f);
    alSourcei(themeSource, AL_LOOPING, AL_TRUE);
    if (alGetError() != AL_NO_ERROR) {
    printf("Error, Sound Source is Incorrect\n");
    return;
    }

    alSourcePlay(themeSource);
}

extern void stoptheme() 
{
    alSourcePause(themeSource);
    return;
}

extern void continuetheme() 
{
    alSourcePlay(themeSource);
}

extern void PlayGameOver()
{
    //ALuint alBuffer;
    alBuffer = alutCreateBufferFromFile("./sounds/.wav");

    //ALuint alSource;
    alGenSources(1, &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);
    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
        printf("Error, Sound Source is Incorrect\n");
        return;
    }
    alSourcePlay(alSource);
}
#endif
/*
extern void end_credits(int xres, int yres) {

    creditsImage = ppm6GetImage("./images/credits.ppm");
    creditsTransImage = ppm6GetImage("./images/transparent.ppm");

    glGenTextures(1, &creditsTexture);

    glBindTexture(GL_TEXTURE_2D, creditsTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, creditsImage->width, creditsImage->height,
        0, GL_RGB, GL_UNSIGNED_BYTE, creditsImage->data);
    
    glBindTexture(GL_TEXTURE_2D, creditsTransTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    int w = creditsTransImage->width;
    int h = creditsTransImage->height;
    unsigned char *ftData = buildAlphaData(creditsTransImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, ftData);
    free(ftData);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    glBindTexture(GL_TEXTURE_2D, creditsTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
    glEnd();

    Rect r;

    r.bot = yres/2 + 90;
    r.left = xres/2;
    r.center = yres/2;

    unsigned int color = 0x9932CC;
    ggprint13(&r, 16, color, "Enemy Designer - Haley Hammer");
    ggprint13(&r, 16, color, "Level Designer - Renee Romero");
    ggprint13(&r, 16, color, "Sound Designer - Kyle Werts");
    ggprint13(&r, 16, color, "Menu Interface/Graphics Designer - Tyler Sharp");
} */