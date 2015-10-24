// Testshortestpath.c ... A program to test the shortest path function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "Places.h"

int main (int argc, char **argv)
{
	if (argc!=5) {
		printf("Usage: ./pathtest LocationID1 LocationID2\n");
		exit(1);
	}
	int start = atoi(argv[1]);
	int end = atoi(argv[2]);
	int player = atoi(argv[3]);
	int round = atoi(argv[4]);
	int truth = (start<=71) && (start>=0) && (end>=0) && (end<=71);
	
	if (!truth) {
		printf("Usage: ./pathtest LocationID1 LocationID2\n");
		exit(1);
	}
	Map europe = newMap();
	printf("First move is %s\n", idToName(shortestPath(europe, start,end,player,round)));
	return 0;
}
