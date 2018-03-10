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

all: flu_fighters

flu_fighters: flu_fighters.cpp log.cpp timers.cpp tylerS.cpp \
	 		reneeR.cpp haleyH.cpp kyleW.cpp
	g++ $(CFLAGS) flu_fighters.cpp log.cpp timers.cpp \
	kyleW.cpp haleyH.cpp reneeR.cpp tylerS.cpp \
	libggfonts.a -Wall $(LFLAGS) -o flu_fighters

clean:
	rm -f flu_fighters
	rm -f *.o
