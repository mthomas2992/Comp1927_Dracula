// hunter.c
// Implementation of your "Fury of Dracula" hunter AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "HunterView.h"
#include "Map.h"
#include "Places.h"
#include <string.h>

void decideHunterMove(HunterView gameState)
{
    /*
    1.Divided region into four parts, separation looks like wobbly 'H', if one player goes to hospital,
    another player would take its place if allocated area is far away
    2.Lord Godalming takes leftmost region, inclu. sea; Dr Seward takes middle upper-half; Van Helsing takes middle
    lower-half; Mina Harker takes rightmost region
    */

    // the real slim shady starts here

	// Round 0: start positions
	
    char *LocationMatrix[4][18]=
    {
	{"GW","AO","LS","SN","SR","BO","NA","LE","EC","NS","ED","MN","LO","SW","LV","IR","DU","ZZ"},
	{"NP","TS","CG","MS","AO","CA","MA","GR","AL","SR","TO","MR","GO","FL","RO","NP","BI","ZZ"},
	{"AT","VA","SA","SO","VR","CN","BC","GA","CD","KL","BD","VI","ZA","SZ","BE","SJ","VA","ZZ"},
	{"MI","VE","MU","NU","PR","BR","HA","LI","FR","CO","AM","BU","ST","PA","CF","GE","ZU","ZZ"},
    };
    PlayerID who = whoAmI(gameState);
    LocationID where = whereIs(gameState, who);
	if (where == -1) {
		registerBestPlay(LocationMatrix[who][0], "I am here, click me!"); 
		return;
	}

	printf("I AM %d\n", who);
	printf("I AM IN %s\n", idToAbbrev(where));
//--------------------------------------------REST LOW HEALTH ----------------------------------------------
	// if we can't win in 1 move
	if (howHealthyIs(gameState, 4) >= 10) {
		if (howHealthyIs(gameState, who) <= 3) {
			registerBestPlay(idToAbbrev(where), "Heal me!, Quickly!");
			return;
		}
	}

//----------------------------------------- RESPONSE TO DRACULA --------------------------------------------
	
	Round round = giveMeTheRound(gameState);
    Map europe = newMap();
    int i=0, j=0;
	int min;
	int job;
    char *place;
	int nums[4];
	LocationID *whitelist;
	int wsize=0;
	LocationID trail[TRAIL_SIZE];
	
	giveMeTheTrail(gameState, 4, trail);
	if (trail[0] < NUM_MAP_LOCATIONS && trail[0] >= 0) {
		if (where == trail[0]) {
			// we know where Drac was LAST turn AND we are the hunter who found him
			registerBestPlay(idToAbbrev(where), "Patience is everything");
			disposeMap(europe);
			return;
		}
		// we know where Drac was LAST turn. go to the closest connecting city as quick as possible
		whitelist = whereCanTheyGo(gameState, &wsize, 4, 1,0,0);
		int distances[wsize];
		int min=70;
		int dest_id;
		for (i=0;i<wsize;i++) {
			distances[i] = howManyMoves(europe,where,whitelist[i], round, who);
			if (distances[i] < min) {
				dest_id = whitelist[i];
				min = distances[i];
			}
		}
		place = idToAbbrev(shortestPath(europe,where,dest_id,round,who));
		registerBestPlay(place, "Target in my sights");
		disposeMap(europe);
		return;
	}
	int trailsize = (round <= 6) ? round : TRAIL_SIZE;
	for (i=0; i<trailsize; i++) {
		if (trail[i] < NUM_MAP_LOCATIONS && trail[0] >= 0) {
			// we know where drac was, go to any place we don't know he has been
			// search for vamps: find out who is closest, if we are, then go! otherwise do something else
			if ((round - i)%13 == 0) {
				min = 70;
				for (j=0;j<=3;j++) {
					nums[j] = howManyMoves(europe,whereIs(gameState,j),trail[i],round,j);
				}
				for (j=0;j<=3;j++) {
					if (nums[j] < min) min = j;
					nums[j] = -1;
				}
				job = min;
				if (job==who) {
					place=idToAbbrev(shortestPath(europe,where,trail[i],round,who));
					registerBestPlay(place, "Eatin' Steak Tonight!");
					disposeMap(europe);
					return;
				}
			}
			// otherwise if we know where drac has been we can head towards there and try to reveal more
			place = idToAbbrev(shortestPath(europe,where,trail[i],round,who));
			registerBestPlay(place, "The Chase is on");
			disposeMap(europe);
			return;
		}		
	}			


//----------------------------------------------- PATROL ---------------------------------------------------
	i=0;


	// find current loc in matrix and prepare to move to next
    while(strcmp(idToAbbrev(where), LocationMatrix[who][i])!=0 
						&& strcmp(LocationMatrix[who][i],"ZZ")!=0) {
	i++;
//	printf("%d\n", i);
    }
	// reset loop if at end
    if (i == 16) {
		i=0;
		place = LocationMatrix[who][i];
		registerBestPlay(place, "Restarting!");
	// get back to loop if not at loop
	} else if (i == 17) {
		place = idToAbbrev(shortestPath(europe, where, abbrevToID(LocationMatrix[who][0]), 
										round, who));
		registerBestPlay(place, "Get me back into the fight!");
	} else {
		i++;
		place = LocationMatrix[who][i];
		registerBestPlay(place, "he'll never hear me comin'");
	}
	disposeMap(europe);
}

    //Temporary random location code
/*    if (giveMeTheRound(gameState)==0){
		registerBestPlay("BC","Matt is super cool");
	} else {
      LocationID *Possibles;
      int PossiblesSize=0;
      Possibles=whereCanIgo(gameState,&PossiblesSize,1,1,0);
      char*BestPlay;
      BestPlay=idToAbbrev(Possibles[1]);
      registerBestPlay(BestPlay,"I'm on holiday in Geneva, jk");
   }
}*/

