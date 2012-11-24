#ifndef __font_h
#define __font_h

#include <GL/glut.h>

extern float mousecolor[3];

void textout(char * s);
void textout(char * s, float x, float y);
void initFontSystem();
void printMouse();

#endif