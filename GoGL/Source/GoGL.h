#ifndef __gogl_h
#define __gogl_h

#define USE_CONSOLE

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "goboard.h"
#include "maindraw.h"
#include "font.h"

#include "effect.h"
#include "explosion.h"
#include "capture.h"
#include "Expand.h"
#include "cluster.h"

#include "sound.h"

#define CONFIG_FILENAME "gogl.cfg"


extern int currentboardwidth;
extern int boardtrans;
extern int tilt;
extern int rot;

extern float xscale;
extern float yscale;

extern int mousex;
extern int mousey;
extern int movingboard;

extern int view2D;
extern float ratio;
extern float framerate;
extern float timeperframe;

extern int whoseturn;
extern int winner;
extern int passed;
extern int lockmove;

extern int points[2];
extern int redpiece;

extern EffectList* effectlist;
extern GoBoard* board;

extern float standardLightPos;

void translateToXY(int x, int y, float & newx, float & newy);

void pushInterfaceMatrix();
void popInterfaceMatrix();
void push2DView();
void pop2DView();

#endif