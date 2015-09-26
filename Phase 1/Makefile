CC = gcc
CFLAGS = -Wall -Werror -g
BINS = testGameView testHunterView testDracView #customViewTest customDracTest

all : $(BINS)

#customViewTest :  customViewTest.o GameView.o Map.o Places.o Players.o stack.o
#customViewTest.o : customViewTest.c Globals.h Game.h

#customDracTest : customDracTest.o GameView.o DracView.o Map.o Places.o Players.o stack.o
#customDracTest.o : customDracTest.c Globals.h Game.h

testGameView : testGameView.o GameView.o Map.o Places.o Players.o stack.o
testGameView.o : testGameView.c Globals.h Game.h 

testHunterView : testHunterView.o HunterView.o Map.o Places.o Players.o GameView.o stack.o
testHunterView.o : testHunterView.c Map.c Places.h

testDracView : testDracView.o DracView.o Map.o Places.o Players.o GameView.o stack.o
testDracView.o : testDracView.c DracView.o

Places.o : Places.c Places.h
Players.o : Players.c Players.h
stack.o : stack.c stack.h
Map.o : Map.c Map.h Places.o stack.o GameView.o
GameView.o : GameView.c GameView.h Players.o
HunterView.o : HunterView.c HunterView.h GameView.o Players.o Places.o
DracView.o : DracView.c DracView.h GameView.o Places.o Map.o Players.o


clean :
	rm -f $(BINS) *.o core

