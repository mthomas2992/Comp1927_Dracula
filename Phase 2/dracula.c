// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"

#define POSSIBLE_ENCOUNTER -10
#define DEFINATE_ENCOUNTER -10
#define SEA_MOVE -20
#define REQUIRES_DOUBLEBACK -50

int comparelocationarrays(int ID,LocationID array[], int arraysize){
	int index=0;
	for (index=0;index<arraysize;index++){
		if (array[index]==ID){
			return 1; //found
		}
		//printf("LocationID[%d]==%d",index,LocationID[index]);
	}
	return 0;
}

void decideDraculaMove(DracView gameState)
{
	int RoadnumLocations=0;
	int SeanumLocations=0;

	//Remember to free the things below
	LocationID *roads;
	LocationID *seas;
	roads=whereCanIgo(gameState,&RoadnumLocations,1,0); //find all kind of road connections
	seas=whereCanIgo(gameState,&SeanumLocations,0,1); //find all sea connection

	LocationID *PossiblesID0;
	int PossiblesID0Size=0;
	LocationID *PossiblesID1;
	int PossiblesID1Size=0;
	LocationID *PossiblesID2;
	int PossiblesID2Size=0;
	LocationID *PossiblesID3;
	int PossiblesID3Size=0;
	PossiblesID0=whereCanTheyGo(gameState,&PossiblesID0Size,0,1,1,1);
	PossiblesID1=whereCanTheyGo(gameState,&PossiblesID1Size,1,1,1,1);
	PossiblesID2=whereCanTheyGo(gameState,&PossiblesID2Size,2,1,1,1);
	PossiblesID3=whereCanTheyGo(gameState,&PossiblesID3Size,3,1,1,1);

	LocationID ID0Loc;
	LocationID ID1Loc;
	LocationID ID2Loc;
	LocationID ID3Loc;
	ID0Loc=whereIs(gameState,0);
	ID1Loc=whereIs(gameState,1);
	ID2Loc=whereIs(gameState,2);
	ID3Loc=whereIs(gameState,3);

	LocationID Draculatrails[TRAIL_SIZE];
	//unsure if feed mem locaiton of draculatrails or not
	giveMeTheTrail(gameState,PLAYER_DRACULA,Draculatrails);

	int i=0;
	int currentmovescore=0;
	int bestmovescore=0; //assign score for teleporting here

	char*BestPlay;

	for (i=0;i<RoadnumLocations;i++){
		//if its possible that an encounter may occur
		if (comparelocationarrays(roads[i],PossiblesID0,PossiblesID0Size)==1||
				comparelocationarrays(roads[i],PossiblesID1,PossiblesID1Size)==1||
				comparelocationarrays(roads[i],PossiblesID2,PossiblesID2Size)==1||
				comparelocationarrays(roads[i],PossiblesID3,PossiblesID3Size)==1){
			currentmovescore+=POSSIBLE_ENCOUNTER;
		}
		//check if move incident with any current player locations
		if (roads[i]==ID0Loc||roads[i]==ID1Loc||roads[i]==ID2Loc||roads[i]==ID3Loc){
			currentmovescore+=DEFINATE_ENCOUNTER;
		}
		//check if would require double back
		if (comparelocationarrays(roads[i],Draculatrails,TRAIL_SIZE)){
			currentmovescore+=REQUIRES_DOUBLEBACK;
		}
		//check if st johns or whatever to make sure its never chosen
		if (roads[i]==ST_JOSEPH_AND_ST_MARYS){
			currentmovescore=-5000; //make sure this move never happens
		}
		//set move
		if (currentmovescore>bestmovescore){
			BestPlay=idToName(roads[i]);
			bestmovescore=currentmovescore;
		}
	}

	for (i=0;i<SeanumLocations;i++){
		if (comparelocationarrays(seas[i],PossiblesID0,PossiblesID0Size)==1||
				comparelocationarrays(seas[i],PossiblesID1,PossiblesID1Size)==1||
				comparelocationarrays(seas[i],PossiblesID2,PossiblesID2Size)==1||
				comparelocationarrays(seas[i],PossiblesID3,PossiblesID3Size)==1){
			currentmovescore+=POSSIBLE_ENCOUNTER;
		}
		//check if move incident with any current player locations

		//check if would require double back
		if (comparelocationarrays(seas[i],Draculatrails,TRAIL_SIZE)){
			currentmovescore+=REQUIRES_DOUBLEBACK;
		}
		//check if st johns or whatever to make sure its never chosen
		if (seas[i]==ST_JOSEPH_AND_ST_MARYS){
			currentmovescore=-5000; //make sure this move never happens
		}
		currentmovescore+=SEA_MOVE; //sea penalty
		//set move
		if (currentmovescore>bestmovescore){
			BestPlay=idToName(seas[i]);
			bestmovescore=currentmovescore;
		}
	}
	registerBestPlay(BestPlay,"Matt is Awesome");

	//printf ("best play is %s",BestPlay);
}
