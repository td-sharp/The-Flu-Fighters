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

extern void Player_Explosion()
{
    //ALuint alBuffer;
    alBuffer = alutCreateBufferFromFile("./Sounds/PlayerExplosion.wav");

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
    alBuffer = alutCreateBufferFromFile("./Sounds/GameOver.wav");

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
