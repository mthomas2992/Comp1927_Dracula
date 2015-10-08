// hunter.c
// Implementation of your "Fury of Dracula" hunter AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "HunterView.h"

void decideHunterMove(HunterView gameState)
{
    /*
    1.Divided region into four parts, separation looks like wobbly 'H', if one player goes to hospital,
    another player would take its place if allocated area is far away
    2.Lord Godalming takes leftmost region, inclu. sea; Dr Seward takes middle upper-half; Van Helsing takes middle
    lower-half; Mina Harker takes rightmost region
    3. atm did breadth-first search
    Need to do:
    4. Don't know how to hunt down Dracula
    5. Have hunters rest at ports (if possible) if blood points < 6(Dracula MAY less likely travel by sea [lose blood points])
    6.  need to implement what happens if in hospital
    */
 
    //Dublin and Galway visited twice
    char *areaOne[18]={"CA","GR","AL","BA","SR","SN","MA","LS","GW","DU","ED","MN","LO","SW","LV","PL","DU","GW"};
    //make anotherarray to keep track when drac trail is found to deviate??
    char *areaTwo[14]={"LE","NA","BR","PA","ST","NU","PR","BR","LI","FR","CO","HA","AM","BU"};
    char *areaThree[14]={"FL","RO","BI","NP","GO","CG","MR","TO","BO","CF","GE","ZU","MI","VE"};
    char *areaFour[16]={"AT","VA","SR","BE","SZ","ZA","VI","BD","KL","CD","GA","BC","CN","VR","SO","SA"};

    //previously used mod round number to determine which city player should
    //visit, but player needs to rest so use array, keep track of city
    
    //char place; Oliver: movement is a string. also i think your array size is 
    //too small. you want this instead:
    int locationNo[NUM_PLAYERS] = {0}; //Oliver: too big > too small
    char *move;
    
    if (whoAmI(gameState) == PLAYER_LORD_GODALMING) {

        if (locationNo[PLAYER_LORD_GODALMING] == 17) { //do you want me to get rid of magic no?
            locationNo[PLAYER_LORD_GODALMING] = 0;
        } else {
            locationNo[PLAYER_LORD_GODALMING]++;
        }
        int i = locationNo[PLAYER_LORD_GODALMING];
        move = areaOne[i];

    } else if (whoAmI(gameState) == PLAYER_DR_SEWARD) {

        if (locationNo[PLAYER_DR_SEWARD] == 13) {
            locationNo[PLAYER_DR_SEWARD] = 0;
        } else {
            locationNo[PLAYER_DR_SEWARD]++;
        }
        int i = locationNo[PLAYER_DR_SEWARD];
        move = areaTwo[i];

    } else if (whoAmI(gameState) == PLAYER_VAN_HELSING) {

        if (locationNo[PLAYER_VAN_HELSING] == 13) {
            locationNo[PLAYER_VAN_HELSING] = 0;
        } else {
            locationNo[PLAYER_VAN_HELSING]++;
        }
        int i = locationNo[PLAYER_VAN_HELSING];
        move = areaThree[i];

    } else {

        if (locationNo[PLAYER_MINA_HARKER] == 15) {
            locationNo[PLAYER_MINA_HARKER] = 0;
        } else {
            locationNo[PLAYER_MINA_HARKER]++;
        }
        int i = locationNo[PLAYER_MINA_HARKER];
        move = areaFour[i];
    }
    
    registerBestPlay(move,"I'm on holiday in Geneva");

    /*
    //Temporary random location code
    if (giveMeTheRound(gameState)==0){
		registerBestPlay("BC","Matt is super cool");
	} else {
      LocationID *Possibles;
      int PossiblesSize=0;
      Possibles=whereCanIgo(gameState,&PossiblesSize,1,1,0);
      char*BestPlay;
      BestPlay=idToAbbrev(Possibles[1]);
      registerBestPlay(BestPlay,"I'm on holiday in Geneva, jk");
    */
      
}
