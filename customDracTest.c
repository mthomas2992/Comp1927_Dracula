// customDracTest.c ... test the ADTs more extensively

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "DracView.h"

int main()
{
    DracView gv;
 
    printf("\t\tTest From PastPlays in Bugfixes\n");

    printf("\n\tGame #0 samples, End of Round 1\n");
    PlayerMessage messages2[] = {"Hello", "There", "This", "Should", "Be Good", 
                                 "Yas", "I'm Getting", "A", "Bit" };
    gv = newDracView("GMN.... SPL.... HAM.... MPA.... DZU.V.. "
                     "GLV.... SLO.... HNS.... MST....", messages2);
    printf("Round/Score Tests\n");
    assert(giveMeTheRound(gv) == 1);
    assert(giveMeTheScore(gv) == 365);
    printf("passed\n");
    printf("Location History Tests\n");
    LocationID history[TRAIL_SIZE];
    giveMeTheTrail(gv, 0, history);
    assert(history[0] == LIVERPOOL);
    assert(history[1] == MANCHESTER); 
    assert(history[2] == UNKNOWN_LOCATION);
    giveMeTheTrail(gv,1,history);
    assert(history[0] == LONDON);
    assert(history[1] == PLYMOUTH);
    assert(history[2] == UNKNOWN_LOCATION);
    giveMeTheTrail(gv,2,history);
    assert(history[0] == NORTH_SEA);
    assert(history[1] == AMSTERDAM);
    assert(history[2] == UNKNOWN_LOCATION);
    giveMeTheTrail(gv,3,history);
    assert(history[0] == STRASBOURG);
    assert(history[1] == PARIS);
    assert(history[2] == UNKNOWN_LOCATION);
    giveMeTheTrail(gv,4,history);
    assert(history[0] == ZURICH);
    assert(history[1] == UNKNOWN_LOCATION);
    printf("Passed Location History Tests\n");
    printf("Vampire/Trap Location Tests\n");
    int nT, nV;
    whatsThere(gv, ADRIATIC_SEA, &nT, &nV);
    assert(nT == 0 && nV == 0);
    whatsThere(gv, ZURICH, &nT, &nV);
    assert(nT == 0 && nV == 1);
    whatsThere(gv, ZURICH, &nT, &nV);
    assert(nT == 0 && nV == 1);
    whatsThere(gv, MANCHESTER, &nT, &nV);
    assert(nT == 0 && nV == 0);
    printf("Passed Vampire/Trap Tests\n");
    disposeDracView(gv);

    printf("\n\tGame #1, Dracula's Turn, 5 complete Rounds\n");
    PlayerMessage messages3[]={""};
    gv = newDracView("GMN.... SPL.... HAM.... MPA.... DGA.V.. "
                     "GLV.... SLO.... HNS.... MST.... DHIT... "
                     "GIR.... SPL.... HAO.... MZU.... DCDT... "
                     "GSW.... SLO.... HNS.... MFR.... DKLT... "
                     "GLV.... SPL.... HAO.... MZU.... DBCT... "
                     "GSW.... SLO.... HNS.... MMR....", messages3);
    printf("Score And Round Number tests\n");
    assert(giveMeTheRound(gv) == 5);
    assert(giveMeTheScore(gv) == GAME_START_SCORE - 5);
    assert(howHealthyIs(gv, 4) == GAME_START_BLOOD_POINTS + LIFE_GAIN_CASTLE_DRACULA);
    printf("Passed Score/Round tests\n");
    printf("Location History Tests\n");
    giveMeTheTrail(gv,0,history);
    assert(history[0] == SWANSEA);
    assert(history[1] == LIVERPOOL);
    assert(history[2] == SWANSEA);
    assert(history[3] == IRISH_SEA);
    assert(history[4] == LIVERPOOL);
    assert(history[5] == MANCHESTER);
    
    giveMeTheTrail(gv,1,history);
    assert(history[0] == LONDON);
    assert(history[1] == PLYMOUTH);
    assert(history[2] == LONDON);
    assert(history[3] == PLYMOUTH);
    assert(history[4] == LONDON);
    assert(history[5] == PLYMOUTH);

    giveMeTheTrail(gv,2,history);
    assert(history[0] == NORTH_SEA);
    assert(history[1] == ATLANTIC_OCEAN);
    assert(history[2] == NORTH_SEA);
    assert(history[3] == ATLANTIC_OCEAN);
    assert(history[4] == NORTH_SEA);
    assert(history[5] == AMSTERDAM);

    giveMeTheTrail(gv,3,history);
    assert(history[0] == MARSEILLES);
    assert(history[1] == ZURICH);
    assert(history[2] == FRANKFURT);
    assert(history[3] == ZURICH);
    assert(history[4] == STRASBOURG);
    assert(history[5] == PARIS);

    giveMeTheTrail(gv,4,history);
    assert(history[0] == BUCHAREST);
    assert(history[1] == KLAUSENBURG);
    assert(history[2] == CASTLE_DRACULA);
    assert(history[3] == GALATZ);
    assert(history[4] == GALATZ);
    printf("Passed Location History Tests\n");
    
    printf("Vampire/Trap Location Tests\n");
    whatsThere(gv, GALATZ, &nT, &nV);
    assert(nT == 1 && nV == 1);
    whatsThere(gv, CASTLE_DRACULA, &nT, &nV);
    assert(nT == 1 && nV == 0); 
    whatsThere(gv, KLAUSENBURG, &nT, &nV);
    assert(nT == 1 && nV == 0);
    whatsThere(gv, BUCHAREST, &nT, &nV);
    assert(nT == 1 && nV == 0);
    whatsThere(gv, HAMBURG, &nT, &nV);
    assert(nT == nV && nV == 0);
    printf("passed Vampire/Trap Location Tests\n");
    disposeDracView(gv);

    printf(" ================= LEGENDARY ===============\n");
    return 0;
}


