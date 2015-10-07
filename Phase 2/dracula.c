// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"

#define POSSIBLE_ENCOUNTER 20
#define DEFINATE_ENCOUNTER 30
#define SEA_MOVE -20
#define REQUIRES_DOUBLEBACK -5000

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
	printf("+++++++========PRE-ALPHA========+++++++\n");
	if (giveMeTheRound(gameState)==0){
		registerBestPlay("MA","Matt is Awesome");
	} else {
		int RoadnumLocations=0;
		int SeanumLocations=0;

		//Remember to free the things below
		LocationID *roads;
		LocationID *seas;
		printf("+++++++========ALPHA========+++++++\n");
		roads=whereCanIgo(gameState,&RoadnumLocations,1,0); //find all kind of road connections
		seas=whereCanIgo(gameState,&SeanumLocations,0,1); //find all sea connection
		printf("+++++++========BETA========+++++++\n");

		LocationID *PossiblesID0;
		int PossiblesID0Size=0;
		LocationID *PossiblesID1;
		int PossiblesID1Size=0;
		LocationID *PossiblesID2;
		int PossiblesID2Size=0;
		LocationID *PossiblesID3;
		int PossiblesID3Size=0;
		printf("+++++++========CHARLIE========+++++++\n");
		PossiblesID0=whereCanTheyGo(gameState,&PossiblesID0Size,0,1,1,1);
		PossiblesID1=whereCanTheyGo(gameState,&PossiblesID1Size,1,1,1,1);
		PossiblesID2=whereCanTheyGo(gameState,&PossiblesID2Size,2,1,1,1);
		PossiblesID3=whereCanTheyGo(gameState,&PossiblesID3Size,3,1,1,1);
		printf("+++++++========OMEGA========+++++++\n");

		LocationID ID0Loc;
		LocationID ID1Loc;
		LocationID ID2Loc;
		LocationID ID3Loc;
		printf("+++++++========FOXTROT========+++++++\n");
		ID0Loc=whereIs(gameState,0);
		ID1Loc=whereIs(gameState,1);
		ID2Loc=whereIs(gameState,2);
		ID3Loc=whereIs(gameState,3);
		printf("+++++++========VICTOR========+++++++\n");

		LocationID Draculatrails[TRAIL_SIZE];
		//unsure if feed mem locaiton of draculatrails or not
		giveMeTheTrail(gameState,PLAYER_DRACULA,Draculatrails);
		printf("+++++++========ZULU========+++++++\n");

		int i=0;
		int currentmovescore=0;
		int bestmovescore=0; //assign score for teleporting here

		char*BestPlay;

		PossiblesID0Size=2;
		PossiblesID1Size=2;
		PossiblesID2Size=2;
		PossiblesID3Size=2;
		for (i=0;i<RoadnumLocations;i++){
			//if its possible that an encounter may occur
			if (comparelocationarrays(roads[i],PossiblesID0,PossiblesID0Size)==0&&
					comparelocationarrays(roads[i],PossiblesID1,PossiblesID1Size)==0&&
					comparelocationarrays(roads[i],PossiblesID2,PossiblesID2Size)==0&&
					comparelocationarrays(roads[i],PossiblesID3,PossiblesID3Size)==0){
				currentmovescore+=POSSIBLE_ENCOUNTER;
			}
			//check if move incident with any current player locations
			if (roads[i]!=ID0Loc||roads[i]!=ID1Loc||roads[i]!=ID2Loc||roads[i]!=ID3Loc){
				currentmovescore+=DEFINATE_ENCOUNTER;
			}
			//check if would require double back
			if (comparelocationarrays(roads[i],Draculatrails,TRAIL_SIZE)){
				currentmovescore+=REQUIRES_DOUBLEBACK;
			}
			//check if st johns or whatever to make sure its never chosen
			if (roads[i]==ST_JOSEPH_AND_ST_MARYS){
				currentmovescore=-5000;//ensure never happens
			}
			//set move
			if (currentmovescore>bestmovescore){
				BestPlay=idToAbbrev(roads[i]);
				bestmovescore=currentmovescore;
			}
			currentmovescore=0;
		}

		for (i=0;i<SeanumLocations;i++){
			currentmovescore=10;
			//check if would require double back
			if (comparelocationarrays(seas[i],Draculatrails,TRAIL_SIZE)){
				currentmovescore=0;
			}
			//check if st johns or whatever to make sure its never chosen
			if (seas[i]==ST_JOSEPH_AND_ST_MARYS){
				currentmovescore=0;//ensure never happens
			}
			//set move
			if (currentmovescore>bestmovescore){
				BestPlay=idToAbbrev(seas[i]);
				bestmovescore=currentmovescore;
			}
			currentmovescore=0;
		}
		registerBestPlay(BestPlay,"Matt is Awesome");
		free(PossiblesID0);
		free(PossiblesID1);
		free(PossiblesID2);
		free(PossiblesID3);
		free(roads);
		free(seas);
	}
	//printf ("best play is %s",BestPlay);
}
