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
    const char *areaOne[18]={"CA","GR","AL","BA","SR","SN","MA","LS","GW","DU","ED","MN","LO","SW","LV","PL","DU","GW"};
    //make anotherarray to keep track when drac trail is found to deviate??
    const char *areaTwo[14]={"LE","NA","BR","PA","ST","NU","PR","BR","LI","FR","CO","HA","AM","BU"};
    const char *areaThree[14]={"FL","RO","BI","NP","GO","CG","MR","TO","BO","CF","GE","ZU","MI","VE"};
    const char *areaFour[16]={"AT","VA","SR","BE","SZ","ZA","VI","BD","KL","CD","GA","BC","CN","VR","SO","SA"};
    
    //previously used mod round number to determine which city player should
    //visit, but player needs to rest so use array, keep track of city
    int locationNo[NUM_PLAYERS-2] = {0};
    char place;
    
    if (whoAmI(gameState) == PLAYER_LORD_GODALMING) {
        
        if (locationNo[PLAYER_LORD_GODALMING] == 17) {
            locationNo[PLAYER_LORD_GODALMING] = 0;	
        } else {
            locationNo[PLAYER_LORD_GODALMING]++;
        }
        int i = locationNo[PLAYER_LORD_GODALMING];
        place = *areaOne[i]; 
        
    } else if (whoAmI(gameState) == PLAYER_DR_SEWARD) {
        
        if (locationNo[PLAYER_DR_SEWARD] == 13) {
            locationNo[PLAYER_DR_SEWARD] = 0;	
        } else {
            locationNo[PLAYER_DR_SEWARD]++;
        }
        int i = locationNo[PLAYER_DR_SEWARD];
        place = *areaTwo[i]; 
        
    } else if (whoAmI(gameState) == PLAYER_VAN_HELSING) {
        
        if (locationNo[PLAYER_VAN_HELSING] == 13) {
            locationNo[PLAYER_VAN_HELSING] = 0;	
        } else {
            locationNo[PLAYER_VAN_HELSING]++;
        }
        int i = locationNo[PLAYER_VAN_HELSING];
        place = *areaThree[i];
        
    } else {
        
        if (locationNo[PLAYER_MINA_HARKER] == 15) {
            locationNo[PLAYER_MINA_HARKER] = 0;	
        } else {
            locationNo[PLAYER_MINA_HARKER]++;
        }
        int i = locationNo[PLAYER_MINA_HARKER];
        place = *areaFour[i];
    }

    registerBestPlay(place,"I'm on holiday in Geneva");
}
