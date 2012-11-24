/* 


  Jason Fieldman
  Albert Chu

  CS184 Final Project


  */



#include "GoGL.h"

extern float standardLightPos = 9;

void drawStone()
{
	glPushMatrix();
	glEnable(GL_NORMALIZE);
	glScalef(1,1,0.5);
	glutSolidSphere(boardMarginWidthHalf, PIECELONGS,  PIECELATS);
	glDisable(GL_NORMALIZE);
	glPopMatrix();
}


void drawPrism(float x, float y, float z, int omit)
{
	
	glBegin(GL_QUADS);
	//top of cube
	glNormal3f(0.0, 0.0, 1.0);

	glVertex3f(x,   0.0, z);
	glVertex3f(x,   y,   z);
	glVertex3f(0.0, y,   z);
	glVertex3f(0.0, 0.0, z);

	

	//left side
	if (omit != 1)
	{
	glNormal3f(-1.0, 0.0, 0.0);

	glVertex3f(0.0, 0.0, z);
	glVertex3f(0.0, y,   z);
	glVertex3f(0.0, y,   0.0);
	glVertex3f(0.0, 0.0, 0.0);
	}

	//right side
	if (omit != 2)
	{
	glNormal3f(1.0, 0.0, 0.0);

	glVertex3f(x, 0.0, 0.0);
	glVertex3f(x, y,   0.0);
	glVertex3f(x, y,   z);
	glVertex3f(x, 0.0, z);
	}

	//up side
	if (omit != 3)
	{
	glNormal3f(0.0, 1.0, 0.0);

	glVertex3f(0.0, y,   z);
	glVertex3f(x,   y,   z);
	glVertex3f(x,   y, 0.0);
	glVertex3f(0.0, y, 0.0);
	}
	
	//down side
	if (omit != 4)
	{
	glNormal3f(0.0, -1.0, 0.0);

	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(x,   0.0, 0.0);
	glVertex3f(x,   0.0,   z);
	glVertex3f(0.0, 0.0,   z);
	}

	glEnd();
}

void drawHQBoard(int size)
{
	//draw board of size size.  each square is 1.0 

	float farcoord = size;//+1;


	//layer black	
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_LIGHTING);
	glColor4f(0.0, 0.0, 0.0,0.0);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);

	glVertex3f(farcoord-0.1, 0.1,      boardBaseHeight+0.18);
	glVertex3f(farcoord-0.1, farcoord-0.1, boardBaseHeight+0.18);
	glVertex3f(0.1,      farcoord-0.1, boardBaseHeight+0.18);
	glVertex3f(0.1,      0.1,      boardBaseHeight+0.18);
	
	glEnd();
	glEnable(GL_LIGHTING);
	//glDepthFunc(GL_LEQUAL);
	
	
	glColor3f(BOARD_R, BOARD_G, BOARD_B);

	glPushMatrix();

	//move up to top of base



	for (int z = 0; z < size; z++)
	{
		glPushMatrix();
		glTranslatef(0, z * boardMarginWidth, 0);
		drawPrism(boardMarginWidthMinusSpaceHalf, boardMarginWidth, boardHeight, 2);
		glTranslatef(farcoord - boardMarginWidthMinusSpaceHalf, 0, 0);
		drawPrism(boardMarginWidthMinusSpaceHalf, boardMarginWidth, boardHeight, 1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(z * boardMarginWidth, 0, 0);
		drawPrism(boardMarginWidth, boardMarginWidthMinusSpaceHalf, boardHeight, 3);
		glTranslatef(0,farcoord - boardMarginWidthMinusSpaceHalf, 0);
		drawPrism(boardMarginWidth, boardMarginWidthMinusSpaceHalf, boardHeight, 4);
		glPopMatrix();
	}

	glTranslatef(0.0, 0.0, boardBaseHeight);
	//draw inner squares

	for (int x = 0; x < size-1; x++)
	{
		for (int y = 0; y < size-1; y++)
		{
			glPushMatrix();
			glTranslatef(boardMarginWidth - boardMarginWidthMinusSpaceHalf + (x * boardMarginWidth), boardMarginWidth - boardMarginWidthMinusSpaceHalf + (y * boardMarginWidth), 0);
			//drawPrism(boardMarginWidthMinusSpace, boardMarginWidthMinusSpace, boardTopHeight, 0);

			glBegin(GL_QUADS);
			
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(boardMarginWidthMinusSpace,   0.0, boardTopHeight);
			glVertex3f(boardMarginWidthMinusSpace,   boardMarginWidthMinusSpace,   boardTopHeight);
			glVertex3f(0.0, boardMarginWidthMinusSpace,   boardTopHeight);
			glVertex3f(0.0, 0.0, boardTopHeight);

			glEnd();
			glPopMatrix();
		}
	}

	glPopMatrix();
	
}

