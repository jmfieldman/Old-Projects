#include "board.h"

#define BOARDTRANS -3.5
#define LINEWIDTH 0.05

#define BOARDR 255
#define BOARDG 204
#define BOARDB 102

#define PIECEANGLE 30
#define PIECERAD 0.25
#define PIECEHEIGHT 0.6

int pieceList;
int boardList;

int genlist = 0;

float sint[361];
float cost[361];

float sintable(int x) { return sint[x]; }
float costable(int x) { return cost[x]; }

extern int board[BOARDARRAYSIZE] = {0};

#define MAXSQUARES 1000
square squares[MAXSQUARES];
int numsquares = 0;

void addSquare(int player, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	squares[numsquares].player = player;
	squares[numsquares].x[0] = x1;
	squares[numsquares].x[1] = x2;
	squares[numsquares].x[2] = x3;
	squares[numsquares].x[3] = x4;
	squares[numsquares].y[0] = y1;
	squares[numsquares].y[1] = y2;
	squares[numsquares].y[2] = y3;
	squares[numsquares].y[3] = y4;
	numsquares++;
}

void setupLight()
{
	float ambient[4] = { (float)0.1, (float)0.1, (float)0.1, (float)0.1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	float diff[4] = {1,1,1,1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);

	float spec[4] = {1,1,1,1};
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
}

void moveLight(int ang)
{
	float pos[4] = { sint[ang], cost[ang], 1, 0 };
	glEnable(GL_NORMALIZE);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glDisable(GL_NORMALIZE);
}

void convertXY(int & x, int & y)
{
	x -= TOPX;
	y -= TOPY;
	y = SCRH - y;
}

inline int boardVal(int* board, int x, int y)
{
	if (x < 0 || x >= BOARDSIZE || y < 0 || y >= BOARDSIZE) return 0;
	return board[(x + (y * BOARDSIZE))];
}

inline void setBoardVal(int* board, int x, int y, int val)
{
	board[(x + (y * BOARDSIZE))] = val;
}

inline int absval(int x)
{
	if (x < 0) return (x * -1);
	return x;
}

int findSquares(int* board, int x, int y, int plyr)
{
	int score = 0;

	int vecx,vecy,tvecx,tvecy,addscore;

	for (int xpos = 0; xpos < BOARDSIZE; xpos++)
	{
		for (int ypos = 0; ypos < BOARDSIZE; ypos++)
		{
			if (boardVal(board,xpos,ypos) && !(xpos == x && ypos == y) )
			{
				vecx = xpos - x;
				vecy = ypos - y;

				addscore = absval(vecx)+absval(vecy) + 1;
				addscore *= addscore;

				tvecx = vecy;
				tvecy = -(vecx);
		
				if (boardVal(board,x+tvecx,y+tvecy) && boardVal(board,xpos+tvecx,ypos+tvecy))
				{
					if (!(boardVal(board,x,y) == 2 && boardVal(board,xpos,ypos) == 2 && boardVal(board,x+tvecx,y+tvecy) == 2 && boardVal(board,xpos+tvecx,ypos+tvecy) == 2))
					{
						//addText("SQUARE!1\n");

						/*char shit[100];
						sprintf(shit,"%d %d %d %d %d %d\n",x,y,xpos,ypos,tvecx,tvecy);
						addText(shit);*/

						score += addscore;
						setBoardVal(board,x,y,2);
						setBoardVal(board,xpos,ypos,2);
						setBoardVal(board,x+tvecx,y+tvecy,2);
						setBoardVal(board,xpos+tvecx,ypos+tvecy,2);
						addSquare(plyr,x,y,x+tvecx,y+tvecy,xpos,ypos,xpos+tvecx,ypos+tvecy);
					}		
				}

				tvecx = -(vecy);
				tvecy = vecx;
		
				if (boardVal(board,x+tvecx,y+tvecy) && boardVal(board,xpos+tvecx,ypos+tvecy))
				{
					if (!(boardVal(board,x,y) == 2 && boardVal(board,xpos,ypos) == 2 && boardVal(board,x+tvecx,y+tvecy) == 2 && boardVal(board,xpos+tvecx,ypos+tvecy) == 2))
					{
						//addText("SQUARE!2\n");
						score += addscore;
						setBoardVal(board,x,y,2);
						setBoardVal(board,xpos,ypos,2);
						setBoardVal(board,x+tvecx,y+tvecy,2);
						setBoardVal(board,xpos+tvecx,ypos+tvecy,2);
						addSquare(plyr,x,y,x+tvecx,y+tvecy,xpos,ypos,xpos+tvecx,ypos+tvecy);
					}		
				}
			}
		}
	}

	return score;
}

void latchNewPiece(int plyr, int x, int y)
{
	//addText("LATCHING\n");
	board[x + (y * BOARDSIZE)] = plyr+1;
	int newboard[BOARDARRAYSIZE];
	for (int i = 0; i < BOARDARRAYSIZE; i++)
	{
		newboard[i] = 0;
		if (board[i] == (plyr+1)) newboard[i] = 1;
	}

	int score = findSquares(newboard,x,y,plyr);
	scores[plyr] += score;
}

void drawBoard()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glNormal3f(0,0,1);
	glColor3ub(BOARDR, BOARDG, BOARDB);
	
	glBegin(GL_QUADS);
	for (float y = -0.5; y <= ((BOARDSIZE-1)-0.0); y += BOARDCUTSPACE)
	{
		
		for (float x = -0.5; x <= ((BOARDSIZE-1)-0.0); x += BOARDCUTSPACE )
		{
			glVertex3f(x,y,0);
			glVertex3f(x+(float)BOARDCUTSPACE,y,0);
			glVertex3f(x+(float)BOARDCUTSPACE,y+(float)BOARDCUTSPACE,0);
			glVertex3f(x,y+(float)BOARDCUTSPACE,0);
		}
		
	}
	
	glNormal3d(-0.7,-0.7,0); glVertex3f(-0.5,-0.5,0); glVertex3f(-0.5,-0.5,-0.5); glNormal3d(0.7,-0.7,0); glVertex3f(7.5,-0.5,-0.5); glVertex3f(7.5,-0.5,0);
	glNormal3d(-0.7,0.7,0); glVertex3f(-0.5,7.5,0); glNormal3d(0.7,0.7,0); glVertex3f(7.5,7.5,0); glVertex3f(7.5,7.5,-0.5); glNormal3d(-0.7,0.7,0); glVertex3f(-0.5,7.5,-0.5); 
	
	glNormal3d(-0.7,-0.7,0); glVertex3f(-0.5,-0.5,-0.5); glVertex3f(-0.5,-0.5,0); glNormal3d(-0.7,0.7,0); glVertex3f(-0.5,7.5,0); glVertex3f(-0.5,7.5,-0.5);
	glNormal3d(0.7,-0.7,0); glVertex3f(7.5,-0.5,0); glVertex3f(7.5,-0.5,-0.5); glNormal3d(0.7,0.7,0); glVertex3f(7.5, 7.5,-0.5); glVertex3f(7.5,7.5,0);

	glEnd();

	
	
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
		
	glColor3f(0,0,0);

	glBegin(GL_QUADS);
	glColor3f((float)0.3,(float)0.15,(float)0.12);
	for (float lx = 0; lx < BOARDSIZE; lx++)
	{
		glVertex3f((float)lx-(float)(LINEWIDTH/2), (float)-(LINEWIDTH/(float)2), (float)0.05);
		glVertex3f((float)lx-(float)(LINEWIDTH/2)+(float)LINEWIDTH, (float)-(LINEWIDTH/(float)2), (float)0.05);
		glVertex3f((float)lx-(float)(LINEWIDTH/2)+(float)LINEWIDTH, (float)-(LINEWIDTH/(float)2)+BOARDSIZE-1, (float)0.05);
		glVertex3f((float)lx-(float)(LINEWIDTH/2), (float)-(LINEWIDTH/(float)2)+BOARDSIZE-1, (float)0.05);

		glVertex3f((float)-(LINEWIDTH/(float)2), (float)lx-(float)(LINEWIDTH/2), (float)0.05);
		glVertex3f((float)-(LINEWIDTH/(float)2)+(float)BOARDSIZE-(float)1, (float)lx-((float)LINEWIDTH/(float)2), (float)0.05);
		glVertex3f((float)-(LINEWIDTH/(float)2)+(float)BOARDSIZE-(float)1, (float)lx-((float)LINEWIDTH/(float)2)+(float)LINEWIDTH, (float)0.05);
		glVertex3f((float)-(LINEWIDTH/(float)2), (float)lx-(float)(LINEWIDTH/2)+(float)LINEWIDTH, (float)0.05);
	}
	glEnd();

	
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			glBegin(GL_TRIANGLE_FAN);

			glVertex3f((float)x,(float)y,(float)0.05);
			
			for (int z = 0; z <= 360; z+= 30)
			{
				glVertex3f((float)x+ ((float)0.12 * cost[z]),(float)y+ ((float)0.12 * sint[z]), (float)0.05); 
			}

			glEnd();
		}
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	
}

void drawPiece()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	for (int ang = 0; ang <= 360; ang += PIECEANGLE)
	{
		float xcor1 = (float)(PIECERAD * cost[ang]);
		float ycor1 = (float)(PIECERAD * sint[ang]);
		float xcor2 = (float)(PIECERAD * cost[ang+PIECEANGLE]);
		float ycor2 = (float)(PIECERAD * sint[ang+PIECEANGLE]);

		glBegin(GL_QUADS);

			glNormal3f(cost[ang],sint[ang],0);
			glVertex3f(xcor1,ycor1,(float)PIECEHEIGHT);
			glVertex3f(xcor1,ycor1,0);

			glNormal3f(cost[ang+PIECEANGLE],sint[ang+PIECEANGLE],0);
			glVertex3f(xcor2,ycor2,0);
			glVertex3f(xcor2,ycor2,(float)PIECEHEIGHT);

		glEnd();
	}

	glNormal3f(0,0,1);
	glBegin(GL_TRIANGLE_FAN);

		glVertex3f(0,0,(float)PIECEHEIGHT);
			
		for (int z = 0; z <= 360; z+= PIECEANGLE)
		{
			//glEnable(GL_NORMALIZE);
			//glNormal3f(cost[z],sint[z],(float));
			//glDisable(GL_NORMALIZE);
			glVertex3f((float)PIECERAD * cost[z],(float)PIECERAD * sint[z], (float)PIECEHEIGHT); 
		}

	glEnd();

	glDisable(GL_BLEND);

}

void genLists()
{
	if (genlist) return;
	genlist = 1;
	
	for (int i = 0; i < BOARDARRAYSIZE; i++)
	{
		board[i] = 0;
	}
	
	for (int x = 0; x < 361; x++)
	{
		sint[x] = (float)sin( double((float)3.14159265 / (float)180) * (double)x );
		cost[x] = (float)cos( double((float)3.14159265 / (float)180) * (double)x );
	}

	boardList = glGenLists(1);
	glNewList(boardList, GL_COMPILE);
		drawBoard();
	glEndList();


	pieceList = glGenLists(1);
	glNewList(pieceList, GL_COMPILE);
		drawPiece();
	glEndList();
}

void unGenLists()
{
	if (!genlist) return;
	genlist = 0;

	glDeleteLists(boardList,1);
	glDeleteLists(pieceList,1);
}

void setEditText(char* str);

int getPosOfXY(int x, int y)
{
	double modelview[16];
	double projection[16];
	int viewport[4];

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	double x1,x2,y1,y2,z1,z2;
	double dx, dy, dz, t, rx, ry;

	gluUnProject(x,y,1, modelview,projection,viewport, &x1, &y1, &z1);
	gluUnProject(x,y,0.9, modelview,projection,viewport, &x2, &y2, &z2);

	dx = x1 - x2 - 0.5;
	dy = y1 - y2 - 0.5;
	dz = z1 - z2;

	//plane:   z = 1.2
	//z1 + dz(t) = 1.2
	//t = (1.2 - z1) / dz

	t = (0.0 - z1) / dz;

	rx = x1 + (dx * t);
	ry = y1 + (dy * t);

	int ix = (int)floor(rx);
	int iy = (int)floor(ry);

	if (ix >= 0 && ix < BOARDSIZE && iy >= 0 && iy < BOARDSIZE)	return (ix + (iy * BOARDSIZE));
	else return -1;
	
}
void clearGameInfo()
{
	for (int x = 0; x < BOARDARRAYSIZE; x++)
	{
		board[x] = 0;
	}

	numsquares = 0;
	scores[0] = 0;
	scores[1] = 0;
}


void renderBoard(float tilt, float rot)
{	

	glPushMatrix();

	glRotatef(tilt,1,-1,0);
	glRotatef(rot,0,0,1);
	
	moveLight(lightang);
	
	glTranslatef(BOARDTRANS,BOARDTRANS,0);

	glCallList(boardList);

	for (int i = 0; i < BOARDARRAYSIZE; i++)
	{
		int col = board[i];
		if (col)
		{
			glPushMatrix();
			glTranslatef((float)(i%BOARDSIZE),(float)(i/BOARDSIZE),0);
	
			glColor3f( col == 1 ? (float)0.8 : (float)0.0, 0, col == 1 ? (float)0.0 : (float)0.8);
			glCallList(pieceList);

			glPopMatrix();
		}
	}

	glDisable(GL_LIGHTING);
	for (int s = 0; s < numsquares; s++)
	{
		
		square sq = squares[s];

		if(sq.player == 0)
		{glColor3f( (float)0.8, 0, 0 ); if (s == (numsquares-1)) { glColor3f(1.0,(float)0.6,(float)0.6); }}
		else
		{glColor3f( 0, 0, (float)0.8 ); if (s == (numsquares-1)) { glColor3f((float)0.6,(float)0.6,1.0); }}
		
		glLineWidth(2);
		if (s == (numsquares-1)) glLineWidth(4);

		
		glBegin(GL_LINE_LOOP);

			glVertex3f((float)sq.x[0],(float)sq.y[0],0.25);
			glVertex3f((float)sq.x[1],(float)sq.y[1],0.25);
			glVertex3f((float)sq.x[3],(float)sq.y[3],0.25);
			glVertex3f((float)sq.x[2],(float)sq.y[2],0.25);

		glEnd();
		
	}
	glEnable(GL_LIGHTING);
	
	int px = 0,py = 0;
	
	if (shouldDrawSelection(px,py))
	{
		int pos = getPosOfXY(px,py);
		if (board[pos] == 0) 
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			
			glPushMatrix();
			glTranslatef((float)(pos%BOARDSIZE),(float)(pos/BOARDSIZE),0);
	
			if(player == 0)
				glColor4f( 1.0, 0, 0, 0.25);	
			else
				glColor4f( 0, 0, 1.0, 0.25);

			glCallList(pieceList);

			glPopMatrix();
	
			glDisable(GL_BLEND);
		}
	}
	
	if (boardVal(board,lastxpos,lastypos))
	{
		glEnable(GL_BLEND);

		glColor4f(1,1,0.7,float(sint[blinkang]+2)/(float)4);

		glPushMatrix();
		glTranslatef((float)(lastxpos),(float)(lastypos),0);
	
		glCallList(pieceList);

		glPopMatrix();

		glDisable(GL_BLEND);
	}

	if (makemove)
	{
		makemove = 0;
		handlePlayerMove(getPosOfXY(px,py));
	}
	
	glFinish();
	SwapBuffers(hDC);
		
	glPopMatrix();
}