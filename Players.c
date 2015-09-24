// Players.c ... Players ADT
// Ash Thomas, COMP1927 15s2

#include <stdio.h>
#include <stdlib.h>
#include "Globals.h"
#include "Game.h"
#include "Places.h"
#include "Players.h"

//#include "GameView.h"


struct players{
    PlayerID player;
    int health;
    int Location;
    int Location_History[6];


};

// initializes a player struct at the beginning of the game, depending on player ID
Player initPlayer(PlayerID player)
{
    Player Someone = malloc(sizeof(struct players));
    Someone->player = player;
    if (player >= 0 && player < 4) Someone->health = GAME_START_HUNTER_LIFE_POINTS;
    else Someone->health = GAME_START_BLOOD_POINTS;

    Someone->Location = -1;

    Someone->Location_History[0] = -1;

    return Someone;
}

int doPlayerTurn(Player p, char* detail)
{
    int i;
    int scoreResult = 0;
    int locationModifier = 0;

    p->Location = abbrevToID(detail+1);
    updatePlayerHistory(p);
    if (p->player != 4) { //for hunters
        for (i=3; i<=6; i++) {
          //  while (detail[i] == '.') continue;
            if (detail[i] == 'T') p->health -= 2;
            else if (detail[i] == 'V') {

            } //vampire dies
            else if (detail[i] == 'D') {
                 p->health -= 4;
                 scoreResult += 10;
            }
        }
        //moved these out of for loop to prevent repeat execution MT
        if (p->health <= 0) { 
          p->Location = ST_JOSEPH_AND_ST_MARYS;
          scoreResult -= 6;
          p->health = 9;
        }
        if (p->Location==p->Location_History[1]){ //if rested
          p->health=p->health+3;
          if (p->health>9) p->health=9; //to ensure health never exceeds 9
        }
    }
    else if (p->player==4) {
        //vampire matured
        if (detail[5] == 'V' || detail[6] == 'V') {
            scoreResult -= 13;
        }
        scoreResult -= 1;
        if (p->Location == DOUBLE_BACK_1) locationModifier = 1;
        if (p->Location == DOUBLE_BACK_2) locationModifier = 2;
        if (p->Location == DOUBLE_BACK_3) locationModifier = 3;
        if (p->Location == DOUBLE_BACK_4) locationModifier = 4;
        if (p->Location == DOUBLE_BACK_5) locationModifier = 5;
        if (idToType(p->Location_History[locationModifier]) == SEA) p->health-=2;
        if (p->Location_History[locationModifier] == CASTLE_DRACULA) p->health += LIFE_GAIN_CASTLE_DRACULA;
    }
    return scoreResult;
}

int getPlayerHealth(Player p)
{
    return p->health;
}

int getPlayerLocation(Player p)
{
    return p->Location;
}

int getPlayerHistory(Player p, int i)
{
    return p->Location_History[i];
}

void updatePlayerHistory(Player p)
{
    int i;
    for (i=5; i>0; i--) {
        p->Location_History[i] = p->Location_History[i-1];
    }
    p->Location_History[0] = p->Location;

}
void removePlayer(Player p)
{
    free(p);
}

void deductHealth(Player p, int deficit)
{
    p->health -= deficit;
}
