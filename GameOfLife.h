#pragma once
//#include <windows.graphics.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable:4996)


typedef char* string;

typedef enum{true = 1, false = !true}bool, *boolp;


typedef struct points{
	int x;
	int y;
}point, *p, **pp;

typedef struct structure{
	p points;
	int size;

}struc, *sp;


#define GRID_SIZE 25

#define SHIP 1
#define BOAT 2
#define QUEEN 3
#define PULSAR 4

#define GET_IS_ALIVE(type,y,x) (type == SHIP) ? shipPoints[y][x] == 1 : type == BOAT ? boatPoints[y][x] == 1 : type == QUEEN ? queenPoints[y][x] == 1 : type == PULSAR ? pulsarPoints[y][x] == 1 : 0

#define SIZEX(type) (type == SHIP || type == BOAT || type == PULSAR) ? 3 : (type == QUEEN) ? 4 : 0
#define SIZEY(type) (type == SHIP || type == BOAT) ? 3 : (type == QUEEN) ? 7 : (type == PULSAR) ? 5 : 0


const int shipPoints[SIZEY(SHIP)][SIZEX(SHIP)] = {
					{1,1,0},
					{1,0,1},
					{0,1,1}};

const int boatPoints[SIZEY(BOAT)][SIZEX(BOAT)] = {
					{0,1,0},
					{1,0,1},
					{0,1,1}	};

const int queenPoints[SIZEY(QUEEN)][SIZEX(QUEEN)] = {
					{1,1,0,0},
					{0,0,1,0},
					{0,0,0,1},
					{0,0,0,1},
					{0,0,0,1},
					{0,0,1,0},
					{1,1,0,0},
					};

const int pulsarPoints[SIZEY(PULSAR)][SIZEX(PULSAR)] = {
					{0,1,0},
					{1,1,1},
					{1,0,1},
					{1,1,1},
					{0,1,0}	};
/*
Just a beautiful pattern from an attempt to make a circle
Returns a boolean array, true: cell alive, false: cell not alive 
*/
boolp initBeautifulPattern();

/*
Init a circle 
Return array of booleans indicating a live cell if true
*/
boolp initCircle();

sp constructLivePointsStruct(int wanted);

void freePattern(sp to_free);

boolp initWantedPattern(int wanted);

void printPattern(boolp result);

boolp copyPattern(boolp dst, boolp src, int size);

int getNeighbor(boolp pattern, int y, int x, int dy, int dx, int size);
int isAlive(boolp pattern, int y, int x, int size);

bool beAlive(boolp pattern, int y, int x, int size);

boolp changePattern(boolp pattern, int size);

void delay(int time_limit);

void start_game();

void mainGameOfLifeLoop();

int main();