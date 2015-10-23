// Map.h ... interface to Map data type

#ifndef MAP_H
#define MAP_H

#include "GameView.h"
#include "Places.h"

typedef struct edge{
    LocationID  start;
    LocationID  end;
    TransportID type;
} Edge;

// graph representation is hidden 
typedef struct MapRep *Map; 

// operations on graphs 
Map  newMap();  
void disposeMap(Map g); 
void showMap(Map g); 
int  numV(Map g);
int  numE(Map g, TransportID t);
int connections(Map g, LocationID start, LocationID end, int type);
int railConnections(Map g, LocationID start, int maxstep, LocationID locs[], int *numLocs);
LocationID shortestPath(Map g, LocationID start, LocationID end, Round round, PlayerID player);
#endif
