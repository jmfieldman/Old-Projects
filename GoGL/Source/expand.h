#ifndef __expand_h
#define __expand_h

#include "GoGL.h"


class Expand : public Effect
{
private:
	
	int life;
	float scale;
	float r,b,g,a,x,y;

public:

	Expand(float r, float g, float b,
				float x, float y);
	~Expand();

	virtual int pulse();
	virtual int type();

};



#endif