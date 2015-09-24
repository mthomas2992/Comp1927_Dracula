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
    return 0;
}


