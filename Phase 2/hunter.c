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
    Divided region into four parts, separation looks like wobbly 'H', so that if one player goes to hospital,
    another player would take its place if allocated area is far away
    */
    // TODO ...
    // Replace the line below by something better
    registerBestPlay("GE","I'm on holiday in Geneva");
}
