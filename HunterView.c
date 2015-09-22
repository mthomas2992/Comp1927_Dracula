// HunterView.c ... HunterView ADT implementation

#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "HunterView.h"
#include "Map.h"

struct hunterView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    LocationID CurrentLocation; //for second last function
    Map map;
    int turns;
    int score;
    int HP[NUM_PLAYERS];
    int ID[NUM_PLAYERS];
};


// Creates a new HunterView to summarise the current state of the game
HunterView newHunterView(char *pastPlays, PlayerMessage messages[])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    HunterView hunterView = malloc(sizeof(struct hunterView));
    hunterView->CurrentLocation=LONDON; //need to fix this as it just assumes started
    hunterView->map=newMap();

    return hunterView;
}


// Frees all memory previously allocated for the HunterView toBeDeleted
void disposeHunterView(HunterView toBeDeleted)
{
    //COMPLETE THIS IMPLEMENTATION
    free( toBeDeleted );
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(HunterView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return (currentView->turns);
}

// Get the id of current player
PlayerID whoAmI(HunterView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    int currPlayer = 0;
    currPlayer = (currentView->turns % NUM_PLAYERS) - 1; //player id starts at 0
    return currPlayer;
}

// Get the current score
int giveMeTheScore(HunterView currentView)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->score;
}

// Get the current health points for a given player
int howHealthyIs(HunterView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return currentView->HP[player];
}

// Get the current location id of a given player
LocationID whereIs(HunterView currentView, PlayerID player)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    //assuming turns counted from 1 not 0
    /*if (player < turns) {
       return UNKNOWN_LOCATION;
    } else {
    return currentView->ID[player];
  }*/
  return 0;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(HunterView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
}

//// Functions that query the map to find information about connectivity

// What are my possible next moves (locations)
LocationID *whereCanIgo(HunterView currentView, int *numLocations, int road, int sea)
{
    //completed in dracview, will copy over when tested properly
    return NULL;
}

// What are the specified player's next possible moves
LocationID *whereCanTheyGo(HunterView currentView, int *numLocations,
                           PlayerID player, int road, int rail, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    return NULL;
}
