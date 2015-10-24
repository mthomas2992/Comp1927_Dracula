/**
 * Runs a player's game turn ...
 *
 * Can produce either a Hunter player or a Dracula player
 * depending on the setting of the I_AM_DRACULA #define
 *
 * This is a dummy version of the real player.c used when
 * you submit your AIs. It is provided so that you can
 * test whether your code is likely to compile ...
 *
 * Note that it used to drive both Hunter and Dracula AIs.
 * It first creates an appropriate view, and then invokes the
 * relevant decide-my-move function, which should use the
 * registerBestPlay() function to send the move back.
 *
 * The real player.c applies a timeout, so that it will halt
 * decide-my-move after a fixed amount of time, if it doesn't
 * finish first. The last move registered will be the one
 * used by the game engine. This version of player.c won't stop
 * your decide-my-move function if it goes into an infinite
 * loop. Sort that out before you submit.
 *
 * Based on the program by David Collien, written in 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#ifdef I_AM_DRACULA
#include "DracView.h"
#include "dracula.h"
#else
#include "HunterView.h"
#include "hunter.h"
#endif

// moves given by registerBestPlay are this long (including terminator)
#define MOVE_SIZE 3

// The minimum static globals I can get away with
static char latestPlay[MOVE_SIZE] = "";
static char latestMessage[MESSAGE_SIZE] = "";

int main(int argc, char *argv[])
{
#ifdef I_AM_DRACULA
   DracView gameState;
   char *plays = "GBC.... SBC.... HBC.... MBC.... DFR.V.."
                  "GCN.... SCN.... HCN.... MBE....";
   PlayerMessage msgs[9] = { "", "", "","","","","","","" };
   gameState = newDracView(plays,msgs);
   decideDraculaMove(gameState);
   disposeDracView(gameState);
#else
   HunterView gameState;
	char *plays = "GGW.... SNP.... HAT.... MMI.... DC?.V.. GAO.... STS.... HVA.... MVE.... DC?T... GLS.... SCG.... HSA.... MMU.... DC?T... GSN.... SMS.... HSO.... MNU.... DC?T... GSR.... SAO.... HVR.... MPR.... DMRT... GBO.... SCA.... HCN.... MBR.... DS?.... GNA.... SMA.... HGA.... MHA.... DD2T.V. GLE.... SGR.... HCD.... MLI.... DGOT.M. GEC.... SAL.... HKL.... MFR.... DHIT.M. GNS.... SBA.... HBD.... MCO.... DC?T.M. GED.... STO.... HVI.... MAM.... DMRT.M. GMN.... SMRTTD. HZA.... MBU.... DZUT... GLO.... SGOT... HSZ.... MST.... DD1T... GSW.... SJM.... HBC.... MPA.... DC?.V.. GLV.... SJM.... HBE.... MCF.... DC?T.M. GIR.... SJM.... HSJ.... MGE.... DC?T.M. GDU.... SJM.... HVA.... MZUTT.. DC?T... GGW.... SJM.... HSA.... MMI.... DC?T... GAO.... SJM.... HSO.... MVE.... DD1T... GLS.... SJM.... HVR.... MMU.... DC?T.V. GSN.... SJM.... HCN.... MNU.... DHIT.M. GSR.... SJM.... HGA.... MPR.... DC?T.M. GBO.... SJM.... HCD.... MBR.... DC?T.M. GNA.... SJM.... HKL.... MHA.... DC?T.M. GLE.... SJM.... HBD.... MLI.... DC?T.M. GEC.... SJM.... HVI.... MFR.... DC?T.M. GNS.... SJM.... HZA.... MCO.... DD4.VM. GED.... SJM.... HSZ.... MAM.... DVET.M. GMN.... SJM.... HBC.... MBU.... DHIT.M. GLO.... SJM.... HBE.... MST.... DMIT.M. GSW.... SJM.... HSJ.... MPA.... DC?T.M. GLV.... SJM.... HVA.... MCF.... DC?T.M. GIR.... SJM.... HSA.... MGE.... DD5T.V. GDU.... SJM.... HSO.... MZU.... DMUT.M. GGW.... SJM.... HVR.... MMIT... DC?T.M. GAO.... SJM.... HCN.... MVET... DC?T... GLS.... SJM.... HGA.... MMUT... DC?T.M. GSN.... SJM.... HCD....";
   PlayerMessage msgs[3] = { "", "", "" };
   gameState = newHunterView(plays,msgs);
   decideHunterMove(gameState);
   disposeHunterView(gameState);
#endif
   printf("Move: %s, Message: %s\n", latestPlay, latestMessage);
   return EXIT_SUCCESS;
}

// Saves characters from play (and appends a terminator)
// and saves characters from message (and appends a terminator)
void registerBestPlay (char *play, PlayerMessage message) {
   strncpy(latestPlay, play, MOVE_SIZE-1);
   latestPlay[MOVE_SIZE-1] = '\0';

   strncpy(latestMessage, message, MESSAGE_SIZE);
   latestMessage[MESSAGE_SIZE-1] = '\0';
}
