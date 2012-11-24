#ifndef __goboard_h
#define __goboard_h

#include "GoGL.h"
#include "maindraw.h"

#define MYPI 3.1415926535

#define EMPTY_PIECE 0
#define BLACK_PIECE 1
#define WHITE_PIECE 2
#define NOT_BLACK_PIECE 3
#define NOT_WHITE_PIECE 4

#define BOARD_R 1.0
#define BOARD_G 0.8
#define BOARD_B 0.4

#define BOARD_HEIGHT 1.0
#define boardHeight 1.0
#define boardTopHeight 0.2
#define boardBaseHeight 0.8

#define boardMarginWidth 1.0
#define boardMarginSpace 0.15
#define boardMarginWidthHalf (boardMarginWidth / 2)
#define boardMarginSpaceHalf (boardMarginSpace / 2)
#define boardMarginWidthMinusSpace (boardMarginWidth - boardMarginSpace)
#define boardMarginWidthMinusSpaceHalf (boardMarginWidthMinusSpace / 2)


#define PIECELATS 6
#define PIECELONGS 12

extern int posofcursor;

void exampleLayout1();
void exampleLayout2();


class GoBoard
{
private:

	int boardWidth;
	int boardSize;

	int* data;	

	int adat[19][19];

public:

	int boardList;
	int stoneList;


	GoBoard(int boardwidth);
	~GoBoard();

	void clearBoard();

	void generateBoardList();
	void renderBoard();

	int getBoardWidth();
	int getBoardSize();
	
	void determineWinner();

	int isSquareEmpty(int pos);
	int isSquareEmpty(int x, int y);
	int putPiece(int x, int y, int color);
	int getPiece(int pos);
	int getPiece(int x, int y);
	int getPiece2(int x, int y);
	void clearSpace(int pos);
	void clearSpace(int x, int y);

	int convertXYtoBoard(int x, int y);

	void setBoardToChar(char* str, int level);
	void setBoardToGO();

	int placepiece();

	void clearAdat();
	int analyze(int x, int y, int captorcolor, int victimcolor,int first);
};



#endif