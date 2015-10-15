// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

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
	/*printf("DSJDSADNSADNAUNIUNEIUFNEIUFNSIUFNSDIFUNDSUIFNSIDFUNDSIFUNS\n\n\n\n\n\n\n");
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
		int bestmovescore=0;
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
			if (currentmovescore>bestmovescore&&strcmp(idToAbbrev(options[i]),"JM")!=0){
				BestPlay=idToAbbrev(options[i]);
				bestmovescore=currentmovescore;
			}
			currentmovescore=0;
		}
		registerBestPlay(BestPlay,"MATT IS AMAZING");
	} else if (giveMeTheRound(gameState)==0) {
		registerBestPlay("FR","FirstMove");
	}*/
	if (giveMeTheRound(gameState)==0){
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
				registerBestPlay(idToAbbrev(Possibles[0]),"FALLBACK EVIL FALLBACK");
				found=1;
			}
		}
 }
	//registerBestPlay("FR","FirstMove");
}
