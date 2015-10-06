// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"

void decideDraculaMove(DracView gameState)
{
	int* numLocations
	LocationID roads[];
	roads=whereCanIgo(gameState,numLocations,1,0); //find all kind of road connections


	registerBestPlay(roads[0],"Matt is Awesome");
}
