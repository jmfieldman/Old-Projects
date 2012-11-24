/* 


  Jason Fieldman
  Albert Chu

  CS184 Final Project: GoGL


  */

#include <GL/glut.h>
#include "GoGL.h"

float spec1[4] = {1,1,1,1};	
float shin1[4] = {100};
float spec0[4] = {0,0,0,0};	
float shin0[4] = {0};

extern int posofcursor = -1;

GoBoard::GoBoard(int bw)
{
	boardWidth = bw;
	boardSize = bw * bw;

	currentboardwidth = bw;
	boardtrans = -1 * ((bw / 2) + 1);

	standardLightPos = bw / 2.0;

	data = new int[boardSize];

	for (int x = 0; x < boardSize; x++) data[x] = EMPTY_PIECE;

	boardList = glGenLists(1);
	glNewList(boardList, GL_COMPILE);
		generateBoardList();
	glEndList();

	stoneList = glGenLists(1);
	glNewList(stoneList, GL_COMPILE);
		drawStone();
	glEndList();

	float poscam = bw * 0.80;
	glLoadIdentity();
	gluLookAt( -poscam, -poscam, poscam,   0, 0, 0,   0, 0, 1);
}



GoBoard::~GoBoard()
{
	delete [] data;
	glDeleteLists(boardList,1);
}


void GoBoard::generateBoardList()
{
	drawHQBoard(boardWidth);	
}



void GoBoard::renderBoard()
{
	glPushMatrix();

	if (!view2D)
	{
		glRotatef(tilt,1,-1,0);
		glRotatef(rot,0,0,1);
		glTranslatef(boardtrans,boardtrans,0);
	}	

	float pos[4] = { standardLightPos, standardLightPos, standardLightPos / 2.0, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	
	glDisable(GL_BLEND);
	glCallList(boardList);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec1);
	glMaterialfv(GL_FRONT, GL_SHININESS, shin1);

	int color, highlight;

	glPushMatrix();
	glTranslatef(boardMarginWidthHalf,boardMarginWidthHalf,1.2);

	posofcursor = getPosOfXY(mousex,mousey);
	
	for (int x = 0; x < boardWidth; x++)
	{
		for (int y = 0; y < boardWidth; y++)
		{
			color = data[x + (y * boardWidth)];
			
			highlight = 0;

			if (x + (y * currentboardwidth) == posofcursor && data[posofcursor] == EMPTY_PIECE && !winner)
			{
				if (whoseturn)
					color = WHITE_PIECE;
				else
					color = BLACK_PIECE;
				highlight = 1;
			}
			
			if (color == WHITE_PIECE || color == BLACK_PIECE)
			{
				if (color == WHITE_PIECE) glColor4f(1.0,1.0,1.0,0.5); else glColor4f(0.2,0.2,0.2,0.5);				

				if (highlight) glEnable(GL_BLEND);

				glPushMatrix();
				glTranslatef(x * boardMarginWidth, y * boardMarginWidth, 0);
				glCallList(stoneList);
				glPopMatrix();
				
				glDisable(GL_BLEND);
			}
		}	
	}	

	glPopMatrix();
	
	effectlist->pulse();

	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_SPECULAR, spec0);
	glMaterialfv(GL_FRONT, GL_SHININESS, shin0);
}

int GoBoard::analyze(int x, int y, int captorcolor, int victimcolor, int first)
{
	//printf("%d %d %d %d\n",x,y,captorcolor,victimcolor);

	if (x < 0 || x >= currentboardwidth || y < 0 || y >= currentboardwidth) return 1;
	
	if (adat[x][y]) return 1;
	adat[x][y] = 1;

	int piece = board->getPiece(x,y);

	if (piece == captorcolor) return 1;
	if (piece == EMPTY_PIECE && !first) return 0;

	return ( analyze(x+1,y,captorcolor,victimcolor,0) &&
			 analyze(x-1,y,captorcolor,victimcolor,0) && 
			 analyze(x,y+1,captorcolor,victimcolor,0) && 
			 analyze(x,y-1,captorcolor,victimcolor,0) );

}

void GoBoard::clearAdat()
{
	for (int x = 0; x < 19; x++)
	{
		for (int y = 0; y < 19; y++) adat[x][y] = 0;
	}
}

int GoBoard::getPiece(int pos)
{
	return data[pos];
}

void GoBoard::clearSpace(int pos)
{
	data[pos] = EMPTY_PIECE;
}

void GoBoard::clearBoard()
{
	for (int x = 0; x < boardSize; x++)
	{	
		data[x] = 0;
	}
}

int GoBoard::convertXYtoBoard(int x, int y)
{
	return ( x + (y * boardWidth));
}

int GoBoard::isSquareEmpty(int pos)
{
	return (data[pos] == EMPTY_PIECE);
}

int GoBoard::isSquareEmpty(int x, int y)
{
	return ( data[convertXYtoBoard(x,y)] == EMPTY_PIECE );
}

int GoBoard::putPiece(int x, int y, int color)
{
	data[convertXYtoBoard(x,y)] = color;
	return 0;
}

int GoBoard::getPiece(int x, int y)
{
	if (x < 0 || x >= currentboardwidth || y < 0 || y >= currentboardwidth) return -1;
	return data[convertXYtoBoard(x,y)];
}

int GoBoard::getPiece2(int x, int y)
{
	if (x < 0 || x >= currentboardwidth || y < 0 || y >= currentboardwidth) return 0;
	return data[convertXYtoBoard(x,y)];
}

void GoBoard::clearSpace(int x, int y)
{
	data[convertXYtoBoard(x,y)] = 0;
}

int GoBoard::getBoardSize()
{
	return boardSize;
}

int GoBoard::getBoardWidth()
{
	return boardWidth;
}

void GoBoard::setBoardToChar(char* str, int level)
{
	int pos = level * boardWidth;
	for (int x = 0; x < boardWidth; x++)
	{
		int p = 0;
		if (str[x] == '1') p = 1;
		if (str[x] == '2') p = 2;
		if (str[x] == '3') p = 3;
		if (str[x] == '4') p = 4;
		data[pos] = p;
		pos++;
	}
}

int GoBoard::placepiece()
{
	if (posofcursor == -1) return 0;
	if (!isSquareEmpty(posofcursor)) return 0;

	for (int i = 0; i < kos; i++)
	{
		if (convertXYtoBoard(kopos[i][0],kopos[i][1]) == posofcursor) return 0;
	}

	int piece = whoseturn + 1;
	int captorpiece = 1;
	if (!whoseturn) captorpiece = 2;

	int x = posofcursor % currentboardwidth;
	int y = posofcursor / currentboardwidth;

	clearAdat();
	//printf("----\n");
	if (analyze(x, y, captorpiece, piece,1))
	{
		data[posofcursor] = piece;
		clearAdat();
		int a1 = analyze(x+1,y,piece,captorpiece,1) && getPiece(x+1,y) == captorpiece; clearAdat();
		int a2 = analyze(x-1,y,piece,captorpiece,1) && getPiece(x-1,y) == captorpiece; clearAdat();
		int a3 = analyze(x,y+1,piece,captorpiece,1) && getPiece(x,y+1) == captorpiece; clearAdat();
		int a4 = analyze(x,y-1,piece,captorpiece,1) && getPiece(x,y-1) == captorpiece;

		if (!a1 && !a2 && !a3 && !a4) 
		{
			data[posofcursor] = EMPTY_PIECE;
			return 0;
		}
	}

	//printf("may move\n");

	data[posofcursor] = piece;	

	sound_placement();

	float col = 1.0;
	if (piece == 1) col = 0.2;

	Expand* exp = new Expand(col,col,col,x,y);
	effectlist->addEffect(exp);

	whoseturn = whoseturn + 1;
	if (whoseturn == 2) whoseturn = 0;

	passed = 0;	

	return 1;
}

int fstat[19][19];

int getfstat(int x, int y)
{
	if (x < 0 || x >= currentboardwidth || y < 0 || y >= currentboardwidth) return 0;
	return fstat[x][y];
}

void GoBoard::determineWinner()
{
	int x,y,z;

	int i = currentboardwidth;

	for (x = 0; x < currentboardwidth; x++)
	{
		for (y = 0; y < currentboardwidth; y++)
		{
			fstat[x][y] = board->getPiece(x,y);
		}
	}

	for (z = 0; z < i; z++)
	{
		for (x = 0; x < currentboardwidth; x++)
		{
			for (y = 0; y < currentboardwidth; y++)
			{
				

				if (board->getPiece(x,y) == EMPTY_PIECE) 
					fstat[x][y] = fstat[x][y] | 
								getfstat(x+1,y) | 
								getfstat(x-1,y) | 
								getfstat(x,y+1) | 
								getfstat(x,y-1);
			}
		}
	}

	Cluster* cluster;

	for (x = 0; x < currentboardwidth; x++)
	{
		for (y = 0; y < currentboardwidth; y++)
		{
			int piece = fstat[x][y];
			if ( (piece & 1) && !(piece & 2) && board->getPiece(x,y) == EMPTY_PIECE)
			{
				points[0]++;
				cluster = new Cluster(0.2,0.2,0.2,0.5, x,y,1, 1,1,0.6, -1,1,0.005,0.1);
				effectlist->addEffect(cluster);
				//printf("BLACK: %d %d\n",x,y);
			}
			else
			if ( (piece & 2) && !(piece & 1) && board->getPiece(x,y) == EMPTY_PIECE)
			{
				points[1]++;
				cluster = new Cluster(1.0,1.0,1.0,0.5, x,y,1, 1,1,0.6, -1,1,0.005,0.1);
				effectlist->addEffect(cluster);
				//printf("WHITE: %d %d\n",x,y);
			}
		}
	}

	if (points[0] > points[1]) winner = 1;
	if (points[1] > points[0]) winner = 2;
	if (!winner) winner = 3;
}

void GoBoard::setBoardToGO()
{
	setBoardToChar(".1122...........221",18);
	setBoardToChar("11.12............21",17);
	setBoardToChar("21112............11",16);
	setBoardToChar("2222..........1...2",15);
	setBoardToChar("1........111.1.....",14);
	setBoardToChar("1.......1.111......",13);
	setBoardToChar(".......11....1.....",12);
	setBoardToChar(".......1.1...1.....",11);
	setBoardToChar("...222.2..111......",10);
	setBoardToChar("..2...22.........11",9);
	setBoardToChar("..2....2........221",8);
	setBoardToChar("...2..222.......122",7);
	setBoardToChar("....22.2.2.....2211",6);
	setBoardToChar(".......2.2......111",5);
	setBoardToChar(".......2.2.......22",4);
	setBoardToChar("........2.........2",3);
	setBoardToChar("1..2............112",2);
	setBoardToChar("12212...........212",1);
	setBoardToChar("111122.........2211",0);
}

void exampleLayout1()
{
	board->setBoardToChar("...................",18);
	board->setBoardToChar("...................",17);
	board->setBoardToChar("...................",16);
	board->setBoardToChar("...................",15);
	board->setBoardToChar("...................",14);
	board->setBoardToChar("...................",13);
	board->setBoardToChar("...................",12);
	board->setBoardToChar("...................",11);
	board->setBoardToChar("...................",10);
	board->setBoardToChar("...................",9);
	board->setBoardToChar("...................",8);
	board->setBoardToChar("...................",7);
	board->setBoardToChar("...................",6);
	board->setBoardToChar("...................",5);
	board->setBoardToChar("...................",4);
	board->setBoardToChar("...................",3);
	board->setBoardToChar("...................",2);
	board->setBoardToChar("...................",1);
	board->setBoardToChar("...................",0);
	
}

void exampleLayout2()
{
	board->setBoardToChar("...................",18);
	board->setBoardToChar("...................",17);
	board->setBoardToChar("...................",16);
	board->setBoardToChar(".......11111.......",15);
	board->setBoardToChar(".....112222211.....",14);
	board->setBoardToChar("....12222222221....",13);
	board->setBoardToChar("...1222222222221...",12);
	board->setBoardToChar("...1222222222221...",11);
	board->setBoardToChar("...122222.222221...",10);
	board->setBoardToChar("...1222222222221...",9);
	board->setBoardToChar("...1222222222221...",8);
	board->setBoardToChar("....11222222211....",7);
	board->setBoardToChar("......1222221......",6);
	board->setBoardToChar(".......11111.......",5);
	board->setBoardToChar("...................",4);
	board->setBoardToChar("...................",3);
	board->setBoardToChar("...................",2);
	board->setBoardToChar("...................",1);
	board->setBoardToChar("...................",0);
	
}

