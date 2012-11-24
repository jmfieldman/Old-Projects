/* 


  Jason Fieldman
  Albert Chu

  CS184 Final Project


  */



#include "expand.h"

#define EXPANDLIFE 50
#define SCALEADD 0.15
#define ALPHAFADE 0.10

Expand::Expand(float r, float g, float b, float x, float y) : Effect()
{
	this->r = r;
	this->g = g;
	this->b = b;
	a = 1.0;
	this->x = x;
	this->y = y;
	this->life = EXPANDLIFE;
	this->scale = 1;
}

int Expand::type()
{
	return TYPE_EXPAND;
}

Expand::~Expand()
{

}

int Expand::pulse()
{
	life--;
	if (life <= 0) return 0;

	glPushMatrix();

	glColor4f(r,g,b,a);
	glEnable(GL_BLEND);

	glTranslatef(boardMarginWidthHalf,boardMarginWidthHalf,1.2);
	glTranslatef(x,y,0);
	glScalef(scale,scale,scale);

	glCallList(board->stoneList);

	glDisable(GL_BLEND);
	glPopMatrix();

	scale += SCALEADD;
	a -= ALPHAFADE;

	return 1;
}