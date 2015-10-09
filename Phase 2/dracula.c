// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

// Ash's comments
// 1. Moving to the place hunters are doesn't gaurantee an encounter, may not even do anything useful as if they don't stay where they are, they probably won't be back
// 2. I think the best way for Dracula to work is to make sure as best as possible that he NEVER encounters the hunters in a city, beacuse 10 BP loss is HUGE
//	the best draculas so far are winning by having average rounds well over 140, 150, meaning game score is at least as low as 200
// 3. We should try to add some behaviour based on blood points, get more conservative when we're low (maybe don't go to sea or something)
// 4. Matt tells me going to CD is dangerous as you get trapped, perhaps a teleport followed by a double back? Maybe this is the only time we use double backs?
// 5. Also suggest a slightly different strategy generally;
/*	Make sure we're in a city without a rail connection on turns 0, 13, 26, etc, all the ones we will place a vampire
	then for the following 5 or 6 turns start running around all over the place placing traps in adjacent cities
	maybe try and get a few in the city itself
	if the vampire dies, bail the hell out of there
        start to travel somewhere else
        if the hunters play well they'll chase the vampire and trigger the traps
	if the hunters play poorly they won't cahse the vampire and we'll win faster
        
*/



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
		registerBestPlay("AM","Matt is Awesome");
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
		PossiblesID0=whereCanTheyGo(gameState,&PossiblesID0Size,0,1,0,0);
		PossiblesID1=whereCanTheyGo(gameState,&PossiblesID1Size,1,1,0,0);
		PossiblesID2=whereCanTheyGo(gameState,&PossiblesID2Size,2,1,0,0);
		PossiblesID3=whereCanTheyGo(gameState,&PossiblesID3Size,3,1,0,0);
		printf("Size of 0 %d\n",PossiblesID0Size);
		printf("Size of 1 %d\n",PossiblesID1Size);
		printf("Size of 2 %d\n",PossiblesID2Size);
		printf("Size of 3 %d\n",PossiblesID3Size);
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

		char*BestPlay = NULL;

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
			//don't move to Castle Dracula unless forced to by a teleport
			if (roads[i]==CASTLE_DRACULA){
				currentmovescore=-5000;
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
		if (BestPlay == NULL) BestPlay = "CD";
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
