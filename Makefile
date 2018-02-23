#
# Makefile for asteroids game
#
# Enter one of the following
#
# make
# make all
# make asteroids
# make clean
#
CFLAGS = -I ./include
#LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm
LFLAGS = -lrt -lX11 -lGL

all: asteroids

asteroids: asteroids.cpp log.cpp timers.cpp
	g++ $(CFLAGS) asteroids.cpp log.cpp timers.cpp \
	kyleW.cpp haleyH.cpp reneeR.cpp tylerS.cpp \
	libggfonts.a -Wall $(LFLAGS) -o asteroids

clean:
	rm -f asteroids
	rm -f *.o

