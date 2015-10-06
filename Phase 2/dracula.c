// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"

void decideDraculaMove(DracView gameState)
{
	int* RoadnumLocations=0;
	//int* SeanumLocations=0;
	LocationID *roads;
	//LocationID *seas;
	roads=whereCanIgo(gameState,RoadnumLocations,1,0); //find all kind of road connections
	//seas=whereCanIgo(gameState,SeanumLocations,0,1); //find all sea connection
	registerBestPlay((char*)roads[0],"Matt is Awesome");
}
