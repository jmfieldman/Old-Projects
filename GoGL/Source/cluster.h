#ifndef __cluster_h
#define __cluster_h

#include "effect.h"

extern int sparkleList;

#define sparklePerCluster 5

struct sparkleCluster {
	int active;
	float position[3];
	float breadth[3];
	float color[4];
	int numberLeft;
	int delay;
	int delayLeft;
	float sclspd;
	float maxscl;
	float sparkleData[sparklePerCluster][6];  //0,1,2 -> x,y,z ; 3 -> scale ; 4 -> speed scale ; 5 -> max scale
};

class Cluster : public Effect
{
private:

	sparkleCluster sparkle;

public:

	Cluster(float r, float g, float b, float a, 
				 float x, float y, float z, 
				 float bx, float by, float bz, 
				 int number, int delay, float sclspd, float maxscl);
	~Cluster();

	virtual int pulse();
	virtual int type();
	

};


void initClusters();


#endif