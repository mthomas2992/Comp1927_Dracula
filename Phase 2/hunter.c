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
    5. 
    */
    // TODO ...
    // Replace the line below by something better
    //will rewrite areaOne
    char areaOne[15]={"MA","GR","AL","BA","SR","SN","LS","CA","GW","DU","ED","MN","LV","SW","LO","PL"}; //then DU, GW
    //make another array to keep track when drac trail is found to deviate??
    //if (giveMeTheRound(currentView) == 0) 
    char areaTwo[13]={"LE","NA","BR","PA","ST","NU","PR","BR","LI","FR","CO","HA","AM","BU"};
    char areaThree[13]={"FL","RO","BI","NP","GO","CG","MR","TO","BO","CF","GE","ZU","MI","VE"};
    char areaFour[15]={"AT","VA","SR","BE","SZ","ZA","VI","BD","KL","CD","GA","BC","CN","VR","SO","SA"};
    int round = getRound(currentView);
    if (whoAmI(currentView) == 0) {
        int i = round % 15;
        char place = areaOne[i]; //???
    } else if (whoAmI(currentView) == 1) {
    } else if (whoAmI(currentView) == 2) {
    } else {
        
    }
    
    registerBestPlay("GE","I'm on holiday in Geneva");
}
