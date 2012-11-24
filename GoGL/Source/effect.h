#ifndef __effect_h
#define __effect_h

#include "GoGL.h"

#define TYPE_NONE 0
#define TYPE_CAPTURE 1
#define TYPE_EXPLOSION 2
#define TYPE_CLUSTER 3
#define TYPE_EXPAND 4


class Effect
{
public:

	Effect();
	~Effect();

	virtual int pulse();
	virtual int type();

	Effect* next;
};


class EffectList
{

private:

	Effect* list;	

public:

	EffectList();
	~EffectList();

	void addEffect(Effect* e);
	void pulse();
	
};


#endif