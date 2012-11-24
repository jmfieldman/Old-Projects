/* 


  Jason Fieldman
  Albert Chu

  CS184 Final Project: GoGL


  */


#include "GoGL.h"
#include <math.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define capturespeedup 5

extern int kos = 0;
extern int kopos[4][2] = { {0,0} , {0,0} ,{0,0} ,{0,0} };

Capture::Capture(int pos) : Effect()
{
	lockmove = 1;
	list = NULL;

	int x = pos % currentboardwidth;
	int y = pos / currentboardwidth;

	mx = x;
	my = y;
	mypos = pos;

	captorcolor = board->getPiece(pos);
	victimcolor = captorcolor + 1;
	if (victimcolor == 3) victimcolor = 1;

	clearAdat();
	int a1 = analyze(x+1,y);clearAdat();
	int a2 = analyze(x-1,y);clearAdat();
	int a3 = analyze(x,y+1);clearAdat();
	int a4 = analyze(x,y-1);

	kos = 0;
	
	if (a1) 
		if ( board->getPiece(x+2,y) != victimcolor &&
			 board->getPiece(x+1,y+1) != victimcolor &&
			 board->getPiece(x+1,y-1) != victimcolor)
		{
			kopos[kos][0] = x+1;
			kopos[kos][1] = y;
			kos++;
		}
	if (a2) 
		if ( board->getPiece(x-2,y) != victimcolor &&
			 board->getPiece(x-1,y+1) != victimcolor &&
			 board->getPiece(x-1,y-1) != victimcolor)
		{
			kopos[kos][0] = x-1;
			kopos[kos][1] = y;
			kos++;
		}
	if (a3) 
		if ( board->getPiece(x,y+2) != victimcolor &&
			 board->getPiece(x+1,y+1) != victimcolor &&
			 board->getPiece(x-1,y+1) != victimcolor)
		{
			kopos[kos][0] = x;
			kopos[kos][1] = y+1;
			kos++;
		}
	if (a4) 
		if ( board->getPiece(x,y-2) != victimcolor &&
			 board->getPiece(x+1,y-1) != victimcolor &&
			 board->getPiece(x-1,y-1) != victimcolor)
		{
			kopos[kos][0] = x;
			kopos[kos][1] = y-1;
			kos++;
		}


	clearAdat();
	if (a1) capture(x+1,y);clearAdat();
	if (a2) capture(x-1,y);clearAdat();
	if (a3) capture(x,y+1);clearAdat();
	if (a4) capture(x,y-1);

	timepassed = 0;

	rgb = 0.2;
	if (victimcolor == WHITE_PIECE) rgb = 1;

	//printf("VC: %d | CC: %d | MX: %d | MY: %d | MYPOS: %d\n",victimcolor,captorcolor,mx,my,mypos);
}


Capture::~Capture()
{
	
}


void Capture::clearAdat()
{
	for (int x = 0; x < 19; x++)
	{
		for (int y = 0; y < 19; y++) adat[x][y] = 0;
	}
}

int Capture::pulse()
{
	if (list == NULL) 
	{
		lockmove = 0;
		return 0;
	}

	timepassed += timeperframe * capturespeedup;

	//printf("%f %f\n",timepassed,list->distance);

	if (list->distance < timepassed)
	{
		Explosion* expl = new Explosion(rgb,rgb,rgb,1, list->x,list->y,1, 300,20,-0.002,0.08);
		effectlist->addEffect(expl);

		sound_capture();
		
		board->clearSpace(list->x,list->y);

		if (expl->getRed() > 0.5) points[0]++; else points[1]++;

		CaptureNode* temp = list;
		list = list->next;
		delete temp;
	}

	return 1;
}

int Capture::type()
{
	return TYPE_CAPTURE;
}

int Capture::analyze(int x, int y)
{
	if (x < 0 || x >= currentboardwidth || y < 0 || y >= currentboardwidth) return 1;
	
	if (adat[x][y]) return 1;
	adat[x][y] = 1;

	int piece = board->getPiece(x,y);

	if (piece == captorcolor) return 1;
	if (piece == EMPTY_PIECE) return 0;

	return ( analyze(x+1,y) && 
			 analyze(x-1,y) && 
			 analyze(x,y+1) && 
			 analyze(x,y-1) );
			
}

void Capture::capture(int x, int y)
{
	if (x < 0 || x >= currentboardwidth || y < 0 || y >= currentboardwidth) return;
	if (adat[x][y]) return;
	adat[x][y] = 1;

	int piece = board->getPiece(x,y);

	if (piece == captorcolor || piece == EMPTY_PIECE) return;

	if (piece == victimcolor)
	{
		CaptureNode* cn = new CaptureNode();
		cn->next = NULL;
		cn->x = x;
		cn->y = y;
		cn->distance = sqrt( (mx-x) * (mx-x) + (my-y) * (my-y) );
		addNode(cn);

		capture(x+1,y);
		capture(x-1,y);
		capture(x,y+1);
		capture(x,y-1);
	}

}

void Capture::addNode(CaptureNode* node)
{
	CaptureNode* listptr = list;

	if (listptr == NULL) { list = node; list->next = NULL; return; }
	
	if (listptr->x == node->x && listptr->y == node->y)
	{
		delete node;
		return;
	}

	if (listptr->distance > node->distance)
	{
		node->next = list;
		list = node;
		return;
	}

	while (1)
	{
		if (listptr->x == node->x && listptr->y == node->y)
		{
			delete node;
			return;
		}

		if (listptr->next == NULL)
		{
			listptr->next = node;
			return;
		}

		if (listptr->next->distance > node->distance)
		{
			node->next = listptr->next;
			listptr->next = node;
			return;
		}

		listptr = listptr->next;
	}
	return;
}