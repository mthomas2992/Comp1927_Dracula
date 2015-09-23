// GameView.c ... GameView ADT implementation
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "Players.h"
#include "Map.h"

// #include "Map.h" ... if you decide to use the Map ADT
struct gameView {
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    //
    LocationID vampLoc;
    LocationID trapLocs[6];
    int trapNum;
    Round RoundNum;
    PlayerID CurrentPlayer;
    Map europe;

    Player Lord_Godalming;
    Player Dr_Seward;
    Player Van_Helsing;
    Player Mina_Harker;
    Player Dracula;

    int GameScore;    
};



// Creates a new GameView to summarise the current state of the game
GameView newGameView(char *pastPlays, PlayerMessage messages[])
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    GameView gameView = malloc(sizeof(struct gameView));
    // INITIALIZE ALL THE THINGS IN THE GAMEVIEW STRUCT
    // WILL FINISH THIS LAST
    gameView->RoundNum = 0;
    gameView->CurrentPlayer = 0;
    gameView->GameScore = GAME_START_SCORE;
    gameView->vampLoc = -1;
    gameView->trapNum = 0;
    gameView->trapLocs[0] = -1;
    gameView->europe = newMap();

    gameView->Lord_Godalming = initPlayer(PLAYER_LORD_GODALMING);
    gameView->Dr_Seward	     = initPlayer(PLAYER_DR_SEWARD);
    gameView->Van_Helsing    = initPlayer(PLAYER_VAN_HELSING);
    gameView->Mina_Harker    = initPlayer(PLAYER_MINA_HARKER);
    gameView->Dracula	     = initPlayer(PLAYER_DRACULA);

    int i;
    int scoreChange=0;

    //// HANDLING PAST PLAYS STRING
    //// We will probably do this a different way in the final thing,  (maybe)
    //// but for now it has to be like this because we can't add functions in 
    //// this ADT  ((  :(  ))
    for (i=0; pastPlays[i] != '\0' ; i+=7) {
	if (pastPlays[i] == ' ') i++;
	if (pastPlays[i] == 'G') {
            scoreChange = doPlayerTurn(gameView->Lord_Godalming, pastPlays+i);
        } else if (pastPlays[i] == 'S') {
            scoreChange = doPlayerTurn(gameView->Dr_Seward, pastPlays+i);
        } else if (pastPlays[i] == 'H') {
            scoreChange = doPlayerTurn(gameView->Van_Helsing, pastPlays+i);
        } else if (pastPlays[i] == 'M') {
            scoreChange = doPlayerTurn(gameView->Mina_Harker, pastPlays+i);
        } else if (pastPlays[i] == 'D') {
            scoreChange = doPlayerTurn(gameView->Dracula, pastPlays+i);
        }
        if (scoreChange <= 0) {
            gameView->GameScore += scoreChange;
        } else if (scoreChange == 10) deductHealth(gameView->Dracula, 10);
        else if (scoreChange == 4) {
            deductHealth(gameView->Dracula, 10);
            gameView->GameScore -= 6;
        }
	gameView->CurrentPlayer++;
	if (gameView->CurrentPlayer==5) {
	    gameView->CurrentPlayer = 0;
            gameView->RoundNum++;
        }
    }    

    return gameView;
}



// Frees all memory previously allocated for the GameView toBeDeleted
void disposeGameView(GameView toBeDeleted)
{
    //COMPLETE THIS IMPLEMENTATION
    // this should be pretty small, reasonably simple
    removePlayer( toBeDeleted->Lord_Godalming );
    removePlayer( toBeDeleted->Dr_Seward );
    removePlayer( toBeDeleted->Van_Helsing );
    removePlayer( toBeDeleted->Mina_Harker );
    removePlayer( toBeDeleted->Dracula );
    disposeMap( toBeDeleted->europe );
    free( toBeDeleted );

}


//// Functions to return simple information about the current state of the game

// Get the current round
Round getRound(GameView currentView)
{
    return currentView->RoundNum;
}

// Get the id of current player - ie whose turn is it?
PlayerID getCurrentPlayer(GameView currentView)
{
    return currentView->CurrentPlayer;
}

// Get the current score
int getScore(GameView currentView)
{
    return currentView->GameScore;
}

// Get the current health points for a given player
int getHealth(GameView currentView, PlayerID player)
{
    switch(player) {
	case PLAYER_LORD_GODALMING: return getPlayerHealth(currentView->Lord_Godalming);
	case PLAYER_DR_SEWARD: 	    return getPlayerHealth(currentView->Dr_Seward);
	case PLAYER_VAN_HELSING:    return getPlayerHealth(currentView->Van_Helsing);
	case PLAYER_MINA_HARKER:    return getPlayerHealth(currentView->Mina_Harker);
	case PLAYER_DRACULA: 	    return getPlayerHealth(currentView->Dracula);
	default: 		    return 0;
    }
}

// Get the current location id of a given player
LocationID getLocation(GameView currentView, PlayerID player)
{

    switch(player) {
	case 0: return getPlayerLocation(currentView->Lord_Godalming);
	case 1: return getPlayerLocation(currentView->Dr_Seward);
	case 2: return getPlayerLocation(currentView->Van_Helsing);
	case 3: return getPlayerLocation(currentView->Mina_Harker);
	case 4: return getPlayerLocation(currentView->Dracula);
	default: return 0;
    }
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void getHistory(GameView currentView, PlayerID player,
                            LocationID trail[TRAIL_SIZE])
{
    int i;
    for (i=0; i<=TRAIL_SIZE; i++){
        if (player == 0) trail[i] = getPlayerHistory(currentView->Lord_Godalming, i);
	else if (player == 1) trail[i] = getPlayerHistory(currentView->Dr_Seward, i);
	else if (player == 2) trail[i] = getPlayerHistory(currentView->Van_Helsing, i);
        else if (player == 3) trail[i] = getPlayerHistory(currentView->Mina_Harker, i);
	else if (player == 4) trail[i] = getPlayerHistory(currentView->Dracula, i);
    }
    // may need to add some robustness here

}

//// Functions that query the map to find information about connectivity

// Returns an array of LocationIDs for all directly connected locations

LocationID *connectedLocations(GameView currentView, int *numLocations,
                               LocationID from, PlayerID player, Round round,
                               int road, int rail, int sea)
{
    //REPLACE THIS WITH YOUR OWN IMPLEMENTATION
    // This should be easy enough to do with the week 7 code
    int i,n=0;    
    int *locations = malloc(71*sizeof(int));
    locations[n++] = from;

    for (i=0; i<=70; i++) {
        if (road && connections(currentView->europe, from, i, ROAD)) {
            locations[n++] = i;
        } else if (sea && connections(currentView->europe, from, i, BOAT)) {
            locations[n++] = i;
        } else if (rail && player!= 4 && connections(currentView->europe, from, i, RAIL)) {
            locations[n++] = i;
            // remember to update this for rail!!!
        }
    }
    *numLocations = n;
   
    return locations;
}
