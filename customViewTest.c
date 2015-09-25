// customViewTest.c ... test the ADTs more extensively

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "GameView.h"

int main()
{
    GameView gv;
    int i;
    int size, seen[NUM_MAP_LOCATIONS], *edges;

    printf("\t\tTest From PastPlays in Bugfixes\n");
    printf("\n\tGame #0 samples, Start of Round 1\n");
    PlayerMessage messages1[] = {"Hello", "There", "This", "Should", "Be Good"};
    gv = newGameView("GMN.... SPL.... HAM.... MPA.... DC?.V..", messages1);
    printf("Turn/Score Tests\n");
    assert(getCurrentPlayer(gv) == PLAYER_LORD_GODALMING);
    assert(getRound(gv) == 1);
    assert(getScore(gv) == GAME_START_SCORE -1);
    printf("Passed Score Tests\n");
    printf("Location Tests\n");
    assert(getLocation(gv,PLAYER_LORD_GODALMING) == MANCHESTER);
    assert(getLocation(gv,PLAYER_DR_SEWARD) == 	PLYMOUTH);
    assert(getLocation(gv,PLAYER_VAN_HELSING) == AMSTERDAM);
    assert(getLocation(gv,PLAYER_MINA_HARKER) == PARIS);
    assert(getLocation(gv,PLAYER_DRACULA) == CITY_UNKNOWN);
    printf("Passed Location Tests\n");
    disposeGameView(gv);

    printf("\n\tGame #0 samples, End of Round 1\n");
    PlayerMessage messages2[] = {"Hello", "There", "This", "Should", "Be Good",
                                 "Yas", "I'm Getting", "A", "Bit", "Excited"};
    gv = newGameView("GMN.... SPL.... HAM.... MPA.... DC?.V.. "
                     "GLV.... SLO.... HNS.... MST.... DC?T...", messages2);
    printf("Location History Tests\n");
    LocationID history[TRAIL_SIZE];
    getHistory(gv, 0, history);
    assert(history[0] == LIVERPOOL);
    assert(history[1] == MANCHESTER);
    assert(history[2] == UNKNOWN_LOCATION);
    getHistory(gv,1,history);
    assert(history[0] == LONDON);
    assert(history[1] == PLYMOUTH);
    assert(history[2] == UNKNOWN_LOCATION);
    getHistory(gv,2,history);
    assert(history[0] == NORTH_SEA);
    assert(history[1] == AMSTERDAM);
    assert(history[2] == UNKNOWN_LOCATION);
    getHistory(gv,3,history);
    assert(history[0] == STRASBOURG);
    assert(history[1] == PARIS);
    assert(history[2] == UNKNOWN_LOCATION);
    getHistory(gv,4,history);
    assert(history[0] == CITY_UNKNOWN);
    assert(history[1] == CITY_UNKNOWN);
    assert(history[2] == UNKNOWN_LOCATION);
    printf("Passed Location History Tests\n");
    disposeGameView(gv);

    printf("\n\tGame #1, Mina's Turn, 5 complete Rounds\n");
    PlayerMessage messages3[]={""};
    gv = newGameView("GMN.... SPL.... HAM.... MPA.... DC?.V.. "
                     "GLV.... SLO.... HNS.... MST.... DC?T... "
                     "GIR.... SPL.... HAO.... MZU.... DCDT... "
                     "GSW.... SLO.... HNS.... MFR.... DC?T... "
                     "GLV.... SPL.... HAO.... MZU.... DC?T... "
                     "GSW.... SLO.... HNS....", messages3);
    printf("Score And Round Number tests\n");
    assert(getRound(gv) == 5);
    assert(getScore(gv) == GAME_START_SCORE - 5);
    assert(getCurrentPlayer(gv) == PLAYER_MINA_HARKER);
    assert(getHealth(gv, 4) == GAME_START_BLOOD_POINTS + LIFE_GAIN_CASTLE_DRACULA);
    printf("Passed Score/Round tests\n");
    printf("Location History Tests\n");
    getHistory(gv,0,history);
    assert(history[0] == SWANSEA);
    assert(history[1] == LIVERPOOL);
    assert(history[2] == SWANSEA);
    assert(history[3] == IRISH_SEA);
    assert(history[4] == LIVERPOOL);
    assert(history[5] == MANCHESTER);

    getHistory(gv,1,history);
    assert(history[0] == LONDON);
    assert(history[1] == PLYMOUTH);
    assert(history[2] == LONDON);
    assert(history[3] == PLYMOUTH);
    assert(history[4] == LONDON);
    assert(history[5] == PLYMOUTH);

    getHistory(gv,2,history);
    assert(history[0] == NORTH_SEA);
    assert(history[1] == ATLANTIC_OCEAN);
    assert(history[2] == NORTH_SEA);
    assert(history[3] == ATLANTIC_OCEAN);
    assert(history[4] == NORTH_SEA);
    assert(history[5] == AMSTERDAM);

    getHistory(gv,3,history);
    assert(history[0] == ZURICH);
    assert(history[1] == FRANKFURT);
    assert(history[2] == ZURICH);
    assert(history[3] == STRASBOURG);
    assert(history[4] == PARIS);

    getHistory(gv,4,history);
    assert(history[0] == CITY_UNKNOWN);
    assert(history[1] == CITY_UNKNOWN);
    assert(history[2] == CASTLE_DRACULA);
    assert(history[3] == CITY_UNKNOWN);
    assert(history[4] == CITY_UNKNOWN);
    disposeGameView(gv);
    printf("Passed Location History Tests\n");

    printf("\n\tChecking Empty Game Rail Connections for Paris\n");
    gv = newGameView("", messages1);
    printf("Checking Paris rail connections for Godalming Rd 0 (up to 0 steps)\n");
    edges = connectedLocations(gv, &size, PARIS, PLAYER_LORD_GODALMING, 0,0,1,0);
    memset(seen, 0, NUM_MAP_LOCATIONS*sizeof(int));
    for (i=0; i < size; i++) seen[edges[i]] = 1;
    assert(size = 1);
    assert(seen[PARIS]);
    free(edges);
    printf("passed\n");

    printf("Checking Paris rail connections for Seward Rd 0 (up to 1 steps)\n");
    edges = connectedLocations(gv, &size, PARIS, PLAYER_DR_SEWARD, 0,0,1,0);
    memset(seen, 0, NUM_MAP_LOCATIONS*sizeof(int));
    for (i=0; i < size; i++) seen[edges[i]] = 1;
    assert(size = 5); assert(seen[BORDEAUX]); assert(seen[MARSEILLES]);
    assert(seen[LE_HAVRE]); assert(seen[BRUSSELS]); assert(seen[PARIS]);
    free(edges);
    printf("passed\n");

    printf("Checking Paris rail connections for Helsing  Rd 0 (up to 2 steps)\n");
    edges = connectedLocations(gv, &size, PARIS, PLAYER_VAN_HELSING, 0,0,1,0);
    memset(seen, 0, NUM_MAP_LOCATIONS*sizeof(int));
    for (i=0; i < size; i++) seen[edges[i]] = 1;
    assert(size = 7); assert(seen[BORDEAUX]); assert(seen[MARSEILLES]);
    assert(seen[LE_HAVRE]); assert(seen[BRUSSELS]); assert(seen[PARIS]);
    assert(seen[COLOGNE]); assert(seen[SARAGOSSA]);
    free(edges);
    printf("passed\n");

    printf("Checking Paris rail connections for Mina Rd 0 (up to 3 steps)\n");
    edges = connectedLocations(gv, &size, PARIS, PLAYER_MINA_HARKER, 0,0,1,0);
    memset(seen, 0, NUM_MAP_LOCATIONS*sizeof(int));
    for (i=0; i < size; i++) seen[edges[i]] = 1;
    assert(size = 10); assert(seen[BORDEAUX]); assert(seen[MARSEILLES]);
    assert(seen[LE_HAVRE]); assert(seen[BRUSSELS]); assert(seen[PARIS]);
    assert(seen[COLOGNE]); assert(seen[SARAGOSSA]);
    assert(seen[BARCELONA]); assert(seen[MADRID]); assert(seen[FRANKFURT]);
    free(edges);
    printf("passed\n");
    disposeGameView(gv);

    printf("\n\tGame #2, Godalmings Turn, 7 rounds\n");
    PlayerMessage messages4[] = {""};
    gv = newGameView("GED.... SGE.... HZU.... MCA.... DCF.V.. "
                   "GMN.... SCFVD.. HGE.... MLS.... DBOT... "
                   "GLO.... SMR.... HCF.... MMA.... DC?T... "
                   "GPL.... SMS.... HMR.... MGR.... DBAT... "
                   "GLO.... SBATD.. HMS.... MMA.... DC?T... "
                   "GPL.... SSJ.... HBA.... MGR.... DC?T... "
                   "GPL.... SSJ.... HBA.... MGR.... DC?T...", messages4);
    printf("Score And Round Tests\n");
    assert(getRound(gv) == 7);
    assert(getCurrentPlayer(gv) == 0);
    assert(getScore(gv) == (GAME_START_SCORE - 7 - 6));
    printf("passed\n");
    printf("Health Tests\n");
    assert(getHealth(gv, 0) == 9);
    assert(getHealth(gv, 1) == 9);
    assert(getHealth(gv, 2) == 9);
    assert(getHealth(gv, 3) == 9);
    assert(getHealth(gv, 4) == 20);
    disposeGameView(gv);
    printf("passed\n");

    printf("\n\tGame #3, Godalmings Turn, 1 round\n");
    gv=newGameView("GEDT... SGET... HZUT... MCAT... DCF.V..", messages4);
    printf("Score And Round Tests\n");
    assert(getRound(gv) == 1); //unsure if this is right
    assert(getCurrentPlayer(gv) == 0);
    assert(getScore(gv) == (GAME_START_SCORE-1));
    printf("Health Tests\n");
    assert(getHealth(gv, 0) == 7);
    assert(getHealth(gv, 1) == 7);
    assert(getHealth(gv, 2) == 7);
    assert(getHealth(gv, 3) == 7);
    assert(getHealth(gv, 4) == 40);
    disposeGameView(gv);
    printf ("passed\n");

    printf("\n\tGame #4, Godalmings Turn, 2 rounds\n");
    gv=newGameView("GEDT... SGET... HZUT... MCAT... DCF.V.. "
                  "GED.... SGE.... HZU.... MCA.... DAS..V.", messages4);
    printf("Score And Round Tests\n");
    assert(getRound(gv) == 2);
    assert(getCurrentPlayer(gv) == 0);
    assert(getScore(gv) == (GAME_START_SCORE-15)); //2 for round 13 for matured
    printf("Health Tests\n");
    assert(getHealth(gv, 0) == 9); //should be healed from resting
    assert(getHealth(gv, 1) == 9); //test to ensure does not exceed
    assert(getHealth(gv, 2) == 9);
    assert(getHealth(gv, 3) == 9);
    assert(getHealth(gv, 4) == 38); // lost two due to ending in sea
    disposeGameView(gv);
    printf("passed\n");

    printf("\n\tGame #5, Godalmings Turn, 3 rounds\n");
    gv=newGameView("GEDT... SGET... HZUT... MCAT... DCF.V.. "
                  "GMNT... SPLT... HNST... MPAT... DAS..V. "
                  "GMN.... SPL.... HNS.... MPA.... DC?....", messages4);
    printf("Score And Round Tests\n");
    assert(getRound(gv) == 3);
    assert(getCurrentPlayer(gv) == 0);
    assert(getScore(gv) == (GAME_START_SCORE-16)); //3 for round 13 for matured
    printf("Health Tests\n");
    assert(getHealth(gv, 0) == 8); //loose 4 to two traps
    assert(getHealth(gv, 1) == 8); //Gain 3 from one rest
    assert(getHealth(gv, 2) == 8);
    assert(getHealth(gv, 3) == 8);
    assert(getHealth(gv, 4) == 38); // lost two due to ending in sea
    disposeGameView(gv);
    printf("passed\n");

    printf("\n\tGame #6, Godalmings Turn, 7 rounds\n");
    gv=newGameView("GEDT... SGET... HZUT... MCAT... DCF.V.. "
                  "GMNT... SPLT... HNST... MPAT... DAS..V. "
                  "GMN.... SPL.... HNS.... MPA.... DC?.... " //health at 8
                  "GEDT... SGET... HZUT... MCAT... DC?.... " //6
                  "GMNT... SPLT... HNST... MPAT... DC?.... "//4
                  "GEDT... SGET... HZUT... MCAT... DC?.... "//2
                  "GMNT... SPLT... HNST... MPAT... DC?....", messages4);
    printf("Score And Round Tests\n");
    assert(getRound(gv) == 7);
    assert(getCurrentPlayer(gv) == 0);
    assert(getScore(gv) == (GAME_START_SCORE-44)); //7 for round 13 for matured 6*4 for hunter deaths
    printf("Health Tests\n");
    assert(getHealth(gv, 0) == 9); //should now be reset to 9
    assert(getHealth(gv, 1) == 9);
    assert(getHealth(gv, 2) == 9);
    assert(getHealth(gv, 3) == 9);
    assert(getHealth(gv, 4) == 38); // lost two due to ending in sea
    printf("Location Tests\n"); //locations should be reset
    assert(getLocation(gv,0)==ST_JOSEPH_AND_ST_MARYS);
    assert(getLocation(gv,1)==ST_JOSEPH_AND_ST_MARYS);
    assert(getLocation(gv,2)==ST_JOSEPH_AND_ST_MARYS);
    assert(getLocation(gv,3)==ST_JOSEPH_AND_ST_MARYS);
    disposeGameView(gv);
    printf("passed\n");
    return 0;
}
