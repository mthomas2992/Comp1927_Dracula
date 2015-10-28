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
#include "Map.h"

#define ILLEGAL_MOVE -2 //must be less then INITIAL & AVOID_MOVE
#define INITIAL -1 //must be less then avoid move
#define AVOID_MOVE 0 //must be less then BAD_MOVE
#define BAD_MOVE 1

#define DANGERZONE -6
#define DISTANCE_CAP 8

int comparelocationarrays(int ID,LocationID array[], int arraysize){
	int index=0;
	for (index=0;index<arraysize;index++){
		if (array[index]==ID){
			return 1; //found
		}
	}
	return 0;
}

int findtrailref(int ID,LocationID array[], int arraysize){
	int index=0;
	for (index=0;index<arraysize;index++){
		if (array[index]==ID){
			return index;
		}
	}
	return 0;
}

void decideDraculaMove(DracView gameState){
	printf("called\n"); //forcing update
	int round = giveMeTheRound(gameState);
	if (round>0){
		int optionssisze=0;
		printf("I think I am at %s\n",idToAbbrev(whereIs(gameState,PLAYER_DRACULA)));
		LocationID *options = whereCanIgo(gameState,&optionssisze,1,1); //find all possible moves
		printf("all possible locations are:\n");
		int test=0;
		while(test<optionssisze){
			printf("options[%d] %s\n",test,idToAbbrev(options[test]));
			test++;
		}
		printf("optionssisze is %d\n",optionssisze);
		LocationID *myTrail=malloc(sizeof(int)*TRAIL_SIZE);
		giveMeTheTrail(gameState,PLAYER_DRACULA,myTrail);
		int trailsize = (round <= 6) ? round : TRAIL_SIZE;
		//determine if hide or double back has occurred
		int HideInTrail=haveHide(gameState);
		int DoubleBackInTrail=havedoubled(gameState);
		printf("think I am hided? %d\n",HideInTrail);
		printf("think I am doubled? %d\n\n",DoubleBackInTrail);
		int i=0;
		if (idToType(whereIs(gameState,PLAYER_DRACULA))==SEA) HideInTrail=1;
		//here best move is set to initial, which is larger then what an illegal move
		//can recieve as a score, so if only illegal moves are availible TP will occur
		int bestmovescore=INITIAL;
		int currentmovescore=0;
		int doublebackrequired=0;
		char *BestPlay;
		int bestfound=0;
		int isHide=0;
		for(i=0;i<optionssisze;i++){
			//Score based on distance of each hunter ONLY WHEN LAND
			currentmovescore=0;
			doublebackrequired=0;
			isHide=0;
			printf("Assesing move %s\n",idToAbbrev(options[i]));
			printf("My health is %d\n",howHealthyIs(gameState,PLAYER_DRACULA));
			if (idToType(options[i])==LAND){
				//score distance
				printf("Land move\n");
				int x=0;
				for (x=0;x<PLAYER_DRACULA;x++){ //iterate through hunters
					int movedistance=howManyMoves(DraculaReturnMap(gameState),whereIs(gameState,x),options[i],giveMeTheRound(gameState),x);
					printf("distance from hunter %d is %d\n",x,currentmovescore);
					if (movedistance>DISTANCE_CAP) movedistance=DISTANCE_CAP; //Cap at 8 to prevent unbalanced
					if (movedistance==1) currentmovescore+=DANGERZONE; //if moving into immediate danger consider effects
					else if (movedistance==0) currentmovescore=AVOID_MOVE;
					else	currentmovescore+=movedistance; //else just add the distance to the score
					if (currentmovescore<AVOID_MOVE) currentmovescore=AVOID_MOVE; //don't let it go below
				}
			} else if (idToType(options[i])==SEA){
				//determine score to add based on health
				printf("Sea move\n");
				int myhealth=howHealthyIs(gameState,PLAYER_DRACULA);
				if (myhealth>=16){
					if (myhealth%4==0){ //make sure divisible
						currentmovescore+=myhealth/4;
					} else {
						myhealth-=myhealth%4;
						currentmovescore+=myhealth/4;
					}
				} else if (myhealth>=(LIFE_LOSS_DRACULA_ENCOUNTER+1)){
					currentmovescore+=1;
				} else { //avoid suicides please
					printf("**avoiding suicide**\n");
					currentmovescore=AVOID_MOVE;
				}
			}
			//================BELOW THIS LINE MUST EXECUTE LAST=================
			//Check if double back, if double back check if its legal, if not score NULL
			int moveintrail=0;
			if (options[i]!=whereIs(gameState,PLAYER_DRACULA)){
				moveintrail=comparelocationarrays(options[i],myTrail,trailsize);
			} else {
				if (HideInTrail&&DoubleBackInTrail){
					printf("\n**Illegal hide move detected**\n");
					currentmovescore=ILLEGAL_MOVE;
				} else if (HideInTrail==0){
					isHide=1;
				} else if (DoubleBackInTrail==0){
					printf("\n**Potential 1 step doubleback detected\n");
					doublebackrequired=1;
					currentmovescore-=3;
				}
			}
			if (DoubleBackInTrail&&moveintrail){
				printf("\n**illegal move detected**\n");
				currentmovescore=ILLEGAL_MOVE;
			} else if (moveintrail&&(DoubleBackInTrail==0)){
				printf("\n**Potential double back detected**\n");
				currentmovescore-=3;
				doublebackrequired=1;
				if (currentmovescore<AVOID_MOVE) currentmovescore=AVOID_MOVE;
			}
			printf ("move assessed to be %d\n\n",currentmovescore);
			//if best score set move
			if ((currentmovescore>bestmovescore)&&(options[i]!=ST_JOSEPH_AND_ST_MARYS)/*&&(options[i]!=whereIs(gameState,PLAYER_DRACULA))*/){
				if (isHide==1) {
					BestPlay=idToAbbrev(HIDE);
					bestmovescore=currentmovescore;
				} else if (doublebackrequired==1) {
					if ((DOUBLE_BACK_1+findtrailref(options[i],myTrail,trailsize))>=TELEPORT){
						BestPlay=idToAbbrev(options[i]);
					} else {
						BestPlay=idToAbbrev(DOUBLE_BACK_1+findtrailref(options[i],myTrail,trailsize));
					}
					bestmovescore=currentmovescore;
				} else {
					BestPlay=idToAbbrev(options[i]);
					bestmovescore=currentmovescore;
				}
				bestfound=1;
				printf("best play is %s\n\n",BestPlay);
			}
		}
		//After all scoring if best move is null set to TP
		if (BestPlay==NULL||bestfound==0){
			registerBestPlay("TP","No choice, well played");
		} else {
			registerBestPlay(BestPlay,"Haha I am still winning");
		}
		optionssisze=0;
		free(options);
		free(myTrail);
	} else if (giveMeTheRound(gameState)==0) {
		registerBestPlay("FR","FirstMove");
	}
}
