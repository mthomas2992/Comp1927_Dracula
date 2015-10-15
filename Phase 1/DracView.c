// DracView.c ... DracView ADT implementation
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Globals.h"
#include "Game.h"
#include "GameView.h"
#include "DracView.h"
#include "Map.h"

#define CHARACTERS_IN_ROUND 40
#define LONGEST_GAME 366*40 //the longest the past plays string could ever be is 366 rounds long

struct dracView {
   LocationID vampLoc;
   LocationID trapLocs[6];
   int trapNum;

   GameView gameView;
};


// Creates a new DracView to summarise the current state of the game
DracView newDracView(char *pastPlays, PlayerMessage messages[])
{
   DracView dracView = malloc(sizeof(struct dracView));
   char *pastplays = malloc(LONGEST_GAME); //modified
   strcpy(pastplays, pastPlays);
   dracView->vampLoc = -1;
   dracView->trapNum = 0;
   dracView->trapLocs[0] = -1;
   int i,j,k,found;
   //parse the pastPlays String to edit any Dracula Location and update trap/vamp locs
   for (i=0; pastPlays[i] != '\0'; i+=7) {
      if (pastPlays[i] == ' ') i++;
      if (pastPlays[i] != 'D' && pastPlays[i+3] != '.') {
         //handle hunters encountering traps or vampire
         j=3;
         found=0;
         while (pastPlays[i+j] != ' ') {
            if (pastPlays[i+j] == 'T') {
               // remove trap from array in particular location
               for (k=0; k<=dracView->trapNum; k++) {
                  if (found) dracView->trapLocs[k-1] = dracView->trapLocs[k];
                  if (dracView->trapLocs[k] == abbrevToID(&(pastPlays[i+1]))) found = 1;
               }
               dracView->trapNum -= found;
            }
            else if (pastPlays[i+j] == 'V') {
               dracView->vampLoc = -1;
            }
            j++;
         }
      }
      else if (pastPlays[i] == 'D') {
         if (abbrevToID(&(pastplays[i+1])) == HIDE) {
            pastplays[i+1] = pastplays[i+1-CHARACTERS_IN_ROUND];
            pastplays[i+2] = pastplays[i+2-CHARACTERS_IN_ROUND];
         } else if (abbrevToID(&(pastplays[i+1])) == DOUBLE_BACK_1) {
            pastplays[i+1] = pastplays[i+1-2*CHARACTERS_IN_ROUND];
            pastplays[i+2] = pastplays[i+2-2*CHARACTERS_IN_ROUND];
         } else if (abbrevToID(&(pastplays[i+1])) == DOUBLE_BACK_2) {
            pastplays[i+1] = pastplays[i+1-3*CHARACTERS_IN_ROUND];
            pastplays[i+2] = pastplays[i+2-3*CHARACTERS_IN_ROUND];
         } else if (abbrevToID(&(pastplays[i+1])) == DOUBLE_BACK_3) {
            pastplays[i+1] = pastplays[i+1-4*CHARACTERS_IN_ROUND];
            pastplays[i+2] = pastplays[i+2-4*CHARACTERS_IN_ROUND];
         } else if (abbrevToID(&(pastplays[i+1])) == DOUBLE_BACK_4) {
            pastplays[i+1] = pastplays[i+1-5*CHARACTERS_IN_ROUND];
            pastplays[i+2] = pastplays[i+2-5*CHARACTERS_IN_ROUND];
         } else if (abbrevToID(&(pastplays[i+1])) == DOUBLE_BACK_5) {
            pastplays[i+1] = pastplays[i+1-6*CHARACTERS_IN_ROUND];
            pastplays[i+2] = pastplays[i+2-6*CHARACTERS_IN_ROUND];
         } else if (abbrevToID(&(pastplays[i+1])) == TELEPORT) {
            pastplays[i+1] = 'C';
            pastplays[i+2] = 'D';
         }
         // handle Dracula placing traps/vampires, traps expiring and vampires maturing
         if (pastplays[i+3] == 'T') {
            dracView->trapLocs[dracView->trapNum++] = abbrevToID(&(pastplays[i+1]));
         }
         if (pastplays[i+4] == 'V') {
            dracView->vampLoc = abbrevToID(&(pastplays[i+1]));
         }
         if (pastplays[i+5] == 'M'){
           printf("entered if\n");
            for (k=1; k!= dracView->trapNum; k++) {
              if (k<6){ //seg fault here
                printf("K is %d\n",k);
                dracView->trapLocs[k-1] = dracView->trapLocs[k];
              }
            }
            dracView->trapNum--;
            printf("after M\n");
         } else if (pastplays[i+5] == 'V' || pastplays[i+6] == 'V') {
            dracView->vampLoc = -1;
         }
         printf("after traps\n");
      }
   }
   printf("end loop\n");
   dracView->gameView = newGameView(pastplays, messages);
   free(pastplays);
   return dracView;
}


// Frees all memory previously allocated for the DracView toBeDeleted
void disposeDracView(DracView toBeDeleted)
{
   disposeGameView( toBeDeleted->gameView );
   free(toBeDeleted);
}


//// Functions to return simple information about the current state of the game

// Get the current round
Round giveMeTheRound(DracView currentView)
{
   return getRound( currentView->gameView );
}

// Get the current score
int giveMeTheScore(DracView currentView)
{
   return getScore( currentView->gameView);
}

// Get the current health points for a given player
int howHealthyIs(DracView currentView, PlayerID player)
{
   return getHealth( currentView->gameView, player);
}

// Get the current location id of a given player
LocationID whereIs(DracView currentView, PlayerID player)
{
   return getLocation( currentView->gameView, player);
}

// Get the most recent move of a given player
void lastMove(DracView currentView, PlayerID player,
   LocationID *start, LocationID *end)
{
   LocationID trail[6] ={};
   getHistory(currentView->gameView, player, trail);
   *start = trail[1];
   *end = trail[0];
   return;
}

   // Find out what minions are placed at the specified location
void whatsThere(DracView currentView, LocationID where,
   int *numTraps, int *numVamps)
{
   int i;
   int Vamps=0, Traps=0;
   if (currentView->vampLoc == where) Vamps++;
   for (i=0; i<currentView->trapNum; i++) {
      if (currentView->trapLocs[i] == where) {
         Traps++;
      }
   }
   *numTraps = Traps;
   *numVamps = Vamps;
   return;
}

//// Functions that return information about the history of the game

// Fills the trail array with the location ids of the last 6 turns
void giveMeTheTrail(DracView currentView, PlayerID player,
   LocationID trail[TRAIL_SIZE])
{
   getHistory(currentView->gameView, player, trail);
}

//// Functions that query the map to find information about connectivity

// What are my (Dracula's) possible next moves (locations)
LocationID *whereCanIgo(DracView currentView, int *numLocations, int road, int sea)
{
   return connectedLocations(currentView->gameView, numLocations,
      whereIs(currentView, 4), 4, giveMeTheRound(currentView), road, 0, sea);
}

   // What are the specified player's next possible moves
LocationID *whereCanTheyGo(DracView currentView, int *numLocations,
   PlayerID player, int road, int rail, int sea)
{
   return connectedLocations(currentView->gameView, numLocations,
      whereIs(currentView, player), player, giveMeTheRound(currentView), road, rail, sea);
}
