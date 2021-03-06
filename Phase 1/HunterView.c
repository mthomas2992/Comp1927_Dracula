// HunterView.c ... HunterView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "HunterView.h"
//#include "Map.h"

struct hunterView {
   GameView gameView;
};

// Creates a new HunterView to summarise the current state of the game
HunterView newHunterView(char *pastPlays, PlayerMessage messages[])
{
   //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
   HunterView hunterView = malloc(sizeof(struct hunterView));

   hunterView->gameView = newGameView(pastPlays, messages);

   return hunterView;
}


// Frees all memory previously allocated for the HunterView toBeDeleted
void disposeHunterView(HunterView toBeDeleted)
{
   disposeGameView( toBeDeleted->gameView );
   free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(HunterView currentView)
{
   return getRound(currentView->gameView);
}

// Get the id of current player
PlayerID whoAmI(HunterView currentView)
{
   return getCurrentPlayer(currentView->gameView);
}

// Get the current score
int giveMeTheScore(HunterView currentView)
{
   return getScore(currentView->gameView);
}

// Get the current health points for a given player
int howHealthyIs(HunterView currentView, PlayerID player)
{
   return getHealth(currentView->gameView, player);
}

// Get the current location id of a given player
LocationID whereIs(HunterView currentView, PlayerID player)
{
   return getLocation(currentView->gameView, player);
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(HunterView currentView, PlayerID player,
   LocationID trail[TRAIL_SIZE])
{
   getHistory(currentView->gameView, player, trail);
}

//// Functions that query the map to find information about connectivity

// What are my possible next moves (locations)
LocationID *whereCanIgo(HunterView currentView, int *numLocations, int road, int rail, int sea)
{
   return connectedLocations(currentView->gameView, numLocations,
      whereIs(currentView, whoAmI(currentView)), whoAmI(currentView),
      getRound(currentView->gameView), road, rail, sea);
}

   // What are the specified player's next possible moves
LocationID *whereCanTheyGo(HunterView currentView, int *numLocations,
      PlayerID player, int road, int rail, int sea)
{
         //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
   return connectedLocations(currentView->gameView, numLocations,
         whereIs(currentView, player), player,getRound(currentView->gameView),
         road, rail, sea);
}
