#ifndef __capture_h
#define __capture_h

#include "GoGL.h"

extern int kos;
extern int kopos[4][2];

struct CaptureNode {
	int x;
	int y;
	float distance;
	CaptureNode* next;
};


class Capture : public Effect
{

public:

	Capture(int pos);
	~Capture();

	virtual int pulse();
	virtual int type();

	void addNode(CaptureNode* node);

	int analyze(int x, int y);
	void capture(int x, int y);

	CaptureNode* list;

	int captorcolor;
	int victimcolor;
	float rgb;

	int adat[19][19];
	void clearAdat();

	int my,mx,mypos;

	float timepassed;
};


#endif