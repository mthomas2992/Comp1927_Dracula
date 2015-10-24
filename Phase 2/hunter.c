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

    //Dublin and Galway visited twice
    //make anotherarray to keep track when drac trail is found to deviate??
    // original location matrix
   /* char* LocationMatrix[4][20]=
    {
        {"CA","GR","AL","BA","SR","SN","MA","LS","AO","GW","DU","ED","MN","LO","SW","LV","PL","DU","GW","ZZ"},
        {"LE","NA","BO","PA","ST","NU","PR","BR","LI","FR","CO","HA","AM","BU","ZZ","ZZ","ZZ","ZZ","ZZ"},
        {"FL","RO","BI","NP","GO","CG","MR","TO","BO","CF","GE","ZU","MI","VE","ZZ","ZZ","ZZ","ZZ","ZZ"},
        {"AT","VA","SR","BE","SZ","ZA","VI","BD","KL","CD","GA","BC","CN","VR","SO","SA","ZZ","ZZ","ZZ"}

    };*/
    // the real slim shady starts here


    char *LocationMatrix[4][18]=
    {
	{"GW","AO","LS","SN","SR","BO","NA","LE","EC","NS","ED","MN","LO","SW","LV","IR","DU","ZZ"},
	{"CA","MA","GR","AL","BA","TO","MR","GO","FL","RO","NP","BI","NP","TS","CG","MS","AO","ZZ"},
	{"VA","AT","VA","SA","SO","VR","CN","GA","CD","KL","BD","VI","ZA","SZ","BC","BE","SJ","ZZ"},
	{"MI","VE","MU","NU","PR","BR","HA","LI","FR","CO","AM","BU","ST","PA","CF","GE","ZU","ZZ"},
    };
    int i=0;
    int who = whoAmI(gameState);
    int where = whereIs(gameState, who);
    char *place;
    Map europe = newMap();


	if (where == -1) {
		registerBestPlay(LocationMatrix[who][0], "I am here, click me!"); 
	}

	printf("I AM %d\n", who);
	printf("I AM IN %s\n", idToAbbrev(where));

    while(strcmp(idToAbbrev(where), LocationMatrix[who][i])!=0 
						&& strcmp(LocationMatrix[who][i],"ZZ")!=0) {
	i++;
	printf("%d\n", i);
    }
    if (i == 17) {
		i=0;
		place = LocationMatrix[who][i];
	} else if (i == 18) {
		place = idToAbbrev(shortestPath(europe, where, abbrevToID(LocationMatrix[who][0]), 
										giveMeTheRound(gameState), who));
		registerBestPlay(place, "Get me back into the fight!");
	} else {
		place = LocationMatrix[who][i];
		registerBestPlay(place, "he'll never hear me comin'");
	}
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
