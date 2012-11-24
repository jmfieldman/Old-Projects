#ifndef __explosion_h
#define __explosion_h

#include "effect.h"

#define shardsPerExplosion 30

struct explosionStruct {
	int active;
	int life;
	float color[4];
	float position[3];
	float gravity;
	float shardData[shardsPerExplosion][11];
		//0,1,2 -> x,y,z
		//3,4,5 -> velocity
		//6,7,8,9,10 -> rotation vector (x,y,z), angle, angleDelta		
};


class Explosion : public Effect
{
private:

	explosionStruct expl;

public:

	Explosion(float r, float g, float b, float a,
				float x, float y, float z,
				int life, float mAD, float grav, float speed);
	~Explosion();

	virtual int pulse();
	virtual int type();
	float getRed();

};





#endif