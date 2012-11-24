#ifndef __board_h
#define __board_h


#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PACKETSIZE 1024

#define BOARDSIZE 8
#define BOARDCUTSPACE 0.5
#define BOARDARRAYSIZE (BOARDSIZE*BOARDSIZE)

#define TOPX 11
#define TOPY 11
#define BOTX 563
#define BOTY 517
#define SCRW BOTX-TOPX
#define SCRH BOTY-TOPY

extern HDC hDC;
extern int lightang;

extern int scores[2];
extern int board[BOARDARRAYSIZE];

extern int player;
extern int makemove;

void genLists();
void unGenLists();
void renderBoard(float tilt, float rot);

float sintable(int ang);
float costable(int ang);

extern int lastxpos,lastypos;

void clearGameInfo();

extern int blinkang;

int getPosOfXY(int x, int y);
void convertXY(int & x, int & y);
int shouldDrawSelection(int & x, int & y);
void addText(char* str);
void handlePlayerMove(int pos);
void updateTurn();
void latchNewPiece(int player, int x, int y);

struct square {
	int x[4];
	int y[4];
	int player;
};

#endif