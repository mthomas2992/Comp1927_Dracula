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
#include <string.h>
#include "Game.h"
#include "DracView.h"

#define DEGREE_1_IMPOS 10

int comparelocationarrays(int ID,LocationID array[], int arraysize){
	printf("compare called\n");
	int index=0;
	for (index=0;index<arraysize-1;index++){
		if (array[index]==ID){
			return 1; //found
		}
		//printf("LocationID[%d]==%d",index,LocationID[index]);
	}
	return 0;
}

void decideDraculaMove(DracView gameState){
	printf("called\n");
	//printf("DSJDSADNSADNAUNIUNEIUFNEIUFNSIUFNSDIFUNDSUIFNSIDFUNDSIFUNS\n\n\n\n\n\n\n");
	if (giveMeTheRound(gameState)>0){
		int optionssisze=0;
		LocationID *options = whereCanIgo(gameState,&optionssisze,1,1); //find all possible moves

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

		LocationID myTrail[TRAIL_SIZE];
		giveMeTheTrail(gameState,PLAYER_DRACULA,myTrail);
		int i =0;
		int bestmovescore=-2;
		int currentmovescore=0;
		char *BestPlay;
		for(i=0;i<optionssisze;i++){
			//printf("looping, at id %d\n",options[i]);
			if (comparelocationarrays(options[i],PossiblesID0,PossiblesID0Size)==0&&
					comparelocationarrays(options[i],PossiblesID1,PossiblesID1Size)==0&&
					comparelocationarrays(options[i],PossiblesID2,PossiblesID2Size)==0&&
					comparelocationarrays(options[i],PossiblesID3,PossiblesID3Size)==0){
				currentmovescore+=DEGREE_1_IMPOS;
			}
			//printf("still looping\n");
			if (comparelocationarrays(options[i],myTrail,TRAIL_SIZE)==1){
				currentmovescore=-1;
			}
			printf("prior to if\n");
			if (currentmovescore>bestmovescore&&strcmp(idToAbbrev(options[i]),"JM")!=0){
				printf("options selected is %d\n",options[i]);
				BestPlay=idToAbbrev(options[i]);
				bestmovescore=currentmovescore;
			}
			currentmovescore=0;
		}
		registerBestPlay(BestPlay,"MATT IS AMAZING");
		//registerBestPlay(idToAbbrev(whereIs(gameState,PLAYER_DRACULA)+1),"Moving up");
		/*if (strcmp(idToAbbrev(whereIs(gameState,PLAYER_DRACULA)),"FR")==0){
			registerBestPlay("CO","Tots not in cologne");
		} else if (strcmp(idToAbbrev(whereIs(gameState,PLAYER_DRACULA)),"CO")==0){
			registerBestPlay("BU","Not in Brussels at all");
		} else if (strcmp(idToAbbrev(whereIs(gameState,PLAYER_DRACULA)),"BU")==0){
			registerBestPlay("LE","LE is a horible city");
		} else if (strcmp(idToAbbrev(whereIs(gameState,PLAYER_DRACULA)),"LE")==0){
			registerBestPlay("NA","This city has a weird name");
		} else if (strcmp(idToAbbrev(whereIs(gameState,PLAYER_DRACULA)),"NA")==0){
			registerBestPlay("CF","Lake something");
		} else if (strcmp(idToAbbrev(whereIs(gameState,PLAYER_DRACULA)),"CF")==0){
			registerBestPlay("PA","I couldn't read this city on the map");
		} else if (strcmp(idToAbbrev(whereIs(gameState,PLAYER_DRACULA)),"PA")==0){
			registerBestPlay("ST","Meat");
		} else if (strcmp(idToAbbrev(whereIs(gameState,PLAYER_DRACULA)),"ST")==0){
			registerBestPlay("NU","flipping");
		} else if (strcmp(idToAbbrev(whereIs(gameState,PLAYER_DRACULA)),"NU")==0){
			registerBestPlay("LI","flipping again");
		} else if (strcmp(idToAbbrev(whereIs(gameState,PLAYER_DRACULA)),"LI")==0){
			registerBestPlay("FR","flipping again");
		}*/
	} else if (giveMeTheRound(gameState)==0) {
		registerBestPlay("FR","FirstMove");
	}
	/*if (giveMeTheRound(gameState)==0){
		registerBestPlay("FR","Matt is frustrated");
	} else {
		LocationID *Possibles;
		int PossiblesSize=0;
		Possibles=whereCanIgo(gameState,&PossiblesSize,1,0);
		LocationID myTrail[TRAIL_SIZE];
		giveMeTheTrail(gameState,PLAYER_DRACULA,myTrail);
		int found=0;
		int x=0;
		while (found==0){
			if (x<PossiblesSize){
				if (comparelocationarrays(Possibles[x],myTrail,TRAIL_SIZE)==0){
					registerBestPlay(idToAbbrev(Possibles[x]),"EVIL");
					found=1;
				} else {
					x++;
				}
			} else {
				registerBestPlay("CD","FALLBACK EVIL FALLBACK");
				found=1;
			}
		}
	}*/
}
