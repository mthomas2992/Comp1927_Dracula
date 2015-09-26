// Players.h
// Header file containing definitions which relate to players
// Ash Thomas, COMP1927 15s2

#ifndef PLAYERS_H
#define PLAYERS_H

#include "Globals.h"
#include "Game.h"
#include "Places.h"

typedef struct players *Player;

// initializes a player struct at the beginning of the game, depending on player ID
Player initPlayer(PlayerID player);

int getPlayerHealth(Player);

int getPlayerLocation(Player);

int getPlayerHistory(Player, int);

int doPlayerTurn(Player, char*);

void updatePlayerHistory(Player);

void removePlayer(Player);

void deductHealth(Player, int);
#endif
