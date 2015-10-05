#Makefile for "Fury of Dracula": The Hunt

# change these to suit your local C environment
CC = gcc
CFLAGS = -Wall -Werror
# do not change the following line
BINS = dracula hunter
# add any other *.o files that your system requires
# (and add their dependencies below after DracView.o)
# if you're not using Map.o or Places.o, you can remove them
OBJS = GameView.o Map.o Places.o Players.o stack.o
# add whatever system libraries you need here (e.g. -lm)
LIBS =

all : $(BINS)

dracula : dracPlayer.o dracula.o DracView.o $(OBJS) $(LIBS)
hunter : hunterPlayer.o hunter.o HunterView.o $(OBJS) $(LIBS)

dracPlayer.o : player.c Game.h DracView.h dracula.h
	$(CC) $(CFLAGS) -DI_AM_DRACULA -c player.c -o dracPlayer.o

hunterPlayer.o : player.c Game.h HunterView.h hunter.h
	$(CC) $(CFLAGS) -c player.c -o hunterPlayer.o

dracula.o : dracula.c Game.h DracView.h
hunter.o : hunter.c Game.h HunterView.h
Places.o : Places.c Places.h
Players.o : Players.c Players.h
stack.o : stack.c stack.h
Map.o : Map.c Map.h Places.o stack.h GameView.o
GameView.o : GameView.c Globals.h GameView.o Players.o
HunterView.o : HunterView.c Globals.h HunterView.h Players.o Places.o GameView.o
DracView.o : DracView.c Globals.h DracView.h Players.o Map.o GameView.o Places.o
# if you use other ADTs, add dependencies for them here

clean :
	rm -f $(BINS) *.o core
