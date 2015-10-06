// hunter.c
// Implementation of your "Fury of Dracula" hunter AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "HunterView.h"

void decideHunterMove(HunterView gameState)
{
    /*
    Hunters
- In beginning of game, have hunters patrol 4 different areas respectively until finds Dracula trail
- Have one hunter stationed near castle Dracula at all times (prevent Dracula from healing)
- Hunter rest when life points less than 4? (or 6 since max traps is 3 --> means can lose 6 HP; esp. since score decreases by 6 if teleported to hospital)
- If found Dracula’s trail, how to decide which direction to take? Have all hunters move to possible locations of Dracula?
- Have all hunters rest if haven’t found Dracula in (first six) rounds of game? Or if all hunters have HP less than ____?
- Hunters should co-ordinate search through breadth-first search/ depth-first search/ something else?
    1.Divided region into four parts, separation looks like wobbly 'H', if one player goes to hospital,
    another player would take its place if allocated area is far away
    2.Lord Godalming takes leftmost region, inclu. sea; Dr Seward takes middle upper-half; Van Helsing takes middle
    lower-half; Mina Harker takes rightmost region  
    3. Don't know how to hunt down Dracula
    4. Have hunters rest at ports (if possible) if blood points < 6(Dracula MAY less likely travel by sea [lose blood points])
    5. atm did breadth-first search
    6.  need to implement what happens if in hospital
    */
    // TODO ...
    // Replace the line below by something better
    //WILL DEBUG THIS PART FIRST THEN ADD IF HP IS LESS THAN 6, WILL REST
    
    //Dublin and Galway visited twice
    char areaOne[17]={"CA","GR","AL","BA","SR","SN","MA","LS","GW","DU","ED","MN","LO","SW","LV","PL","DU","GW"};
    //make another array to keep track when drac trail is found to deviate??
    char areaTwo[13]={"LE","NA","BR","PA","ST","NU","PR","BR","LI","FR","CO","HA","AM","BU"};
    char areaThree[13]={"FL","RO","BI","NP","GO","CG","MR","TO","BO","CF","GE","ZU","MI","VE"};
    char areaFour[15]={"AT","VA","SR","BE","SZ","ZA","VI","BD","KL","CD","GA","BC","CN","VR","SO","SA"};
    
    //previously used mod round number to determine which city player should
    //visit, but player needs to rest so use array, keep track of city
    int locationNo[NUM_PLAYERS-2] = {0};
    
    //if(giveMeRound(gameState) < 5) {
    //int i = 0;
    //}
    
    if (whoAmI(gameState) == PLAYER_LORD_GODALMING) {
        
        if (locationNo[PLAYER_LORD_GODALMING] == 17) {
            locationNo[PLAYER_LORD_GODALMING] = 0;	
        } else {
            locationNo[PLAYER_LORD_GODALMING]++;
        }
        int i = locationNo[PLAYER_LORD_GODALMING];
        char place = areaOne[i]; //???
        
    } else if (whoAmI(gameState) == PLAYER_DR_SEWARD) {
        
        if (locationNo[PLAYER_DR_SEWARD] == 17) {
            locationNo[PLAYER_DR_SEWARD] = 0;	
        } else {
            locationNo[PLAYER_DR_SEWARD]++;
        }
        int i = locationNo[PLAYER_DR_SEWARD];
        char place = areaTwo[i]; //???
        
    } else if (whoAmI(gameState) == PLAYER_VAN_HELSING) {
        
        if (locationNo[PLAYER_VAN_HELSING] == 17) {
            locationNo[PLAYER_VAN_HELSING] = 0;	
        } else {
            locationNo[PLAYER_VAN_HELSING]++;
        }
        int i = locationNo[PLAYER_VAN_HELSING];
        char place = areaThree[i]; //???
        
    } else {
        
        if (locationNo[PLAYER_MINA_HARKER] == 17) {
            locationNo[PLAYER_MINA_HARKER] = 0;	
        } else {
            locationNo[PLAYER_MINA_HARKER]++;
        }
        int i = locationNo[PLAYER_MINA_HARKER];
        char place = areaFour[i]; //???
    }
    /*
    if (howHealthyIs(gameState, PLAYER_LORD_GODALMING) <= 6) {
    	 
    }
    */
    registerBestPlay(place,"I'm on holiday in Geneva");
}
