/* 


  Jason Fieldman
  Albert Chu

  CS184 Final Project


  */



#include "font.h"
#include <stdio.h>

extern float mousecolor[3] = { 1,0,0 };

/*

........
........
........
........
........
........
........
........


*/

#define SOFF 0
#define BOFF 1

extern int moomoo = 1;

GLubyte normalFont[128][8];
int normalFontParam[128][3];  //0 = vert off, 1 = width, 2 = x off
void initNormalFont();

#define DATASIZE 64*4
#define TOTALDATA DATASIZE*128

unsigned char texdataarray[TOTALDATA];
unsigned int texhandles[128];

void textout(char * s)
{

	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	int strpos = 0;
	unsigned char letter;
	while (s[strpos] != '\0')
	{
		letter = s[strpos];
		//glBitmap(normalFontParam[letter][1], 8, 0, normalFontParam[letter][0], normalFontParam[letter][2], 0, normalFont[letter]);

		glBindTexture(GL_TEXTURE_2D, texhandles[letter]);
		
		float YOFF = (float)normalFontParam[letter][0] / (float)8;
		
		glBegin(GL_QUADS);

			glTexCoord2f(SOFF,SOFF);
			glVertex2f(SOFF,SOFF-YOFF);

			glTexCoord2f(BOFF,SOFF);
			glVertex2f(BOFF,SOFF-YOFF);

			glTexCoord2f(BOFF,BOFF);
			glVertex2f(BOFF,BOFF-YOFF);

			glTexCoord2f(SOFF,BOFF);
			glVertex2f(SOFF,BOFF-YOFF);			

		glEnd();

		glTranslatef((float)normalFontParam[letter][2] / (float)8,0,0);

		strpos++;
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glFlush();
	
}

void textout(char * s, float x, float y)
{
	glPushMatrix();
	glTranslatef(x,y,0);
	textout(s);
	glPopMatrix();
}

void initFontSystem()
{	
	
	initNormalFont();

	for (int i = 0; i < TOTALDATA; i++) texdataarray[i] = 0;

	for (int let = 0; let < 128; let++)
	{
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				int xypos = x + (y * 8);
				int xyoff = xypos * 4;
				int position = let * DATASIZE + xyoff;

				int color = ((normalFont[let][y] >> (7-x)) & 1) * 255;

				texdataarray[position+0] = color;
				texdataarray[position+1] = color;
				texdataarray[position+2] = color;
				texdataarray[position+3] = color;
			}
		}
	}

	glGenTextures(128,texhandles);
	for (int x = 0; x < 128; x++)
	{
		glBindTexture(GL_TEXTURE_2D, texhandles[x]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(texdataarray[x*DATASIZE]));

		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 8, 8, GL_RGBA, GL_UNSIGNED_BYTE, &(texdataarray[x*DATASIZE]));	
	}
	

}

void printMouse()
{
	glTranslatef(0,-1,0);
	char mouse1[2] = " ";
	mouse1[0] = 1;
	mouse1[1] = '\0';

	char mouse2[2] = " ";
	mouse2[0] = 2;
	mouse2[1] = '\0';

	glColor3fv(mousecolor);
	textout(mouse1);
	glTranslatef(-1,0,0);
	glColor3f(0,0,0);
	textout(mouse2);
}

GLubyte bin2dec(char* str)
{
	GLubyte val = 128;
	GLubyte total = 0;
	for (int x = 0; x < 8; x++)
	{
		if (str[x] == 'X')
		{
			total += val;
		}
		val /= 2;
	}
	return total;
}

void initNormalFont()
{
	for (int x = 0; x < 128; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			normalFont[x][y] = 0;
		}

		normalFontParam[x][0] = 0;
		normalFontParam[x][1] = 5;
		normalFontParam[x][2] = 6;
	}

	int tempBase = 'A';

	normalFont[tempBase][7] = bin2dec("XXX     ");
	normalFont[tempBase][6] = bin2dec("X  X    ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("XXXXX   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec("X   X   ");
							 

	tempBase = 'B';

	normalFont[tempBase][7] = bin2dec("XXX     ");
	normalFont[tempBase][6] = bin2dec("X  X    ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("XXXX    ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec("XXXX    ");

	tempBase = 'C';

	normalFont[tempBase][7] = bin2dec(" XX     ");
	normalFont[tempBase][6] = bin2dec("X  X    ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("X       ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = 'D';

	normalFont[tempBase][7] = bin2dec("XXX     ");
	normalFont[tempBase][6] = bin2dec("X  X    ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec("XXXX    ");

	tempBase = 'E';

	normalFont[tempBase][7] = bin2dec("XXXXX   ");
	normalFont[tempBase][6] = bin2dec("X       ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec("XXXX    ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec("XXXXX   ");

	tempBase = 'F';

	normalFont[tempBase][7] = bin2dec("XXXXX   ");
	normalFont[tempBase][6] = bin2dec("X       ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec("XXXX    ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec("X       ");

	tempBase = 'G';

	normalFont[tempBase][7] = bin2dec(" XX     ");
	normalFont[tempBase][6] = bin2dec("X  X    ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec("X XXX   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = 'H';

	normalFont[tempBase][7] = bin2dec("X   X   ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("XXXXX   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec("X   X   ");

	tempBase = 'I';

	normalFont[tempBase][7] = bin2dec("XXXXX   ");
	normalFont[tempBase][6] = bin2dec("  X     ");
	normalFont[tempBase][5] = bin2dec("  X     ");
	normalFont[tempBase][4] = bin2dec("  X     ");
	normalFont[tempBase][3] = bin2dec("  X     ");
	normalFont[tempBase][2] = bin2dec("  X     ");
	normalFont[tempBase][1] = bin2dec("  X     ");
	normalFont[tempBase][0] = bin2dec("XXXXX   ");

	tempBase = 'J';

	normalFont[tempBase][7] = bin2dec("  XXX   ");
	normalFont[tempBase][6] = bin2dec(" X  X   ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("    X   ");
	normalFont[tempBase][3] = bin2dec("    X   ");
	normalFont[tempBase][2] = bin2dec("    X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = 'K';

	normalFont[tempBase][7] = bin2dec("X  X    ");
	normalFont[tempBase][6] = bin2dec("X X     ");
	normalFont[tempBase][5] = bin2dec("XX      ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec("XX      ");
	normalFont[tempBase][2] = bin2dec("X X     ");
	normalFont[tempBase][1] = bin2dec("X  X    ");
	normalFont[tempBase][0] = bin2dec("X   X   ");

	tempBase = 'L';

	normalFont[tempBase][7] = bin2dec("X       ");
	normalFont[tempBase][6] = bin2dec("X       ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec("X       ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec("XXXXX   ");

	tempBase = 'M';

	normalFont[tempBase][7] = bin2dec("X   X   ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("XX XX   ");
	normalFont[tempBase][4] = bin2dec("X X X   ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec("X   X   ");

	tempBase = 'N';

	normalFont[tempBase][7] = bin2dec("X   X   ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("XX  X   ");
	normalFont[tempBase][4] = bin2dec("X X X   ");
	normalFont[tempBase][3] = bin2dec("X  XX   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec("X   X   ");

	tempBase = 'O';

	normalFont[tempBase][7] = bin2dec(" XX     ");
	normalFont[tempBase][6] = bin2dec("X  X    ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = 'P';

	normalFont[tempBase][7] = bin2dec("XXX     ");
	normalFont[tempBase][6] = bin2dec("X  X    ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("XXXX    ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec("X       ");

	tempBase = 'Q';

	normalFont[tempBase][7] = bin2dec(" XX     ");
	normalFont[tempBase][6] = bin2dec("X  X    ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec("X X X   ");
	normalFont[tempBase][1] = bin2dec("X  X    ");
	normalFont[tempBase][0] = bin2dec(" XX X   ");

	tempBase = 'R';

	normalFont[tempBase][7] = bin2dec("XXX     ");
	normalFont[tempBase][6] = bin2dec("X  X    ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("XXXX    ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec("X   X   ");

	tempBase = 'S';

	normalFont[tempBase][7] = bin2dec(" XX     ");
	normalFont[tempBase][6] = bin2dec("X  X    ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec(" XXX    ");
	normalFont[tempBase][2] = bin2dec("    X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = 'T';

	normalFont[tempBase][7] = bin2dec("XXXXX   ");
	normalFont[tempBase][6] = bin2dec("  X     ");
	normalFont[tempBase][5] = bin2dec("  X     ");
	normalFont[tempBase][4] = bin2dec("  X     ");
	normalFont[tempBase][3] = bin2dec("  X     ");
	normalFont[tempBase][2] = bin2dec("  X     ");
	normalFont[tempBase][1] = bin2dec("  X     ");
	normalFont[tempBase][0] = bin2dec("  X     ");

	tempBase = 'U';

	normalFont[tempBase][7] = bin2dec("X   X   ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = 'V';

	normalFont[tempBase][7] = bin2dec("X   X   ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec(" X  X   ");
	normalFont[tempBase][1] = bin2dec("  X X   ");
	normalFont[tempBase][0] = bin2dec("   X    ");

	tempBase = 'W';

	normalFont[tempBase][7] = bin2dec("X   X   ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec("X X X   ");
	normalFont[tempBase][1] = bin2dec("X X X   ");
	normalFont[tempBase][0] = bin2dec(" X X    ");

	tempBase = 'X';

	normalFont[tempBase][7] = bin2dec("X   X   ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec(" X X    ");
	normalFont[tempBase][4] = bin2dec("  X     ");
	normalFont[tempBase][3] = bin2dec("  X     ");
	normalFont[tempBase][2] = bin2dec(" X X    ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec("X   X   ");

	tempBase = 'Y';

	normalFont[tempBase][7] = bin2dec("X   X   ");
	normalFont[tempBase][6] = bin2dec(" X  X   ");
	normalFont[tempBase][5] = bin2dec("  X X   ");
	normalFont[tempBase][4] = bin2dec("   X    ");
	normalFont[tempBase][3] = bin2dec("   X    ");
	normalFont[tempBase][2] = bin2dec("   X    ");
	normalFont[tempBase][1] = bin2dec("   X    ");
	normalFont[tempBase][0] = bin2dec("   X    ");

	tempBase = 'Z';

	normalFont[tempBase][7] = bin2dec("XXXXX   ");
	normalFont[tempBase][6] = bin2dec("    X   ");
	normalFont[tempBase][5] = bin2dec("   X    ");
	normalFont[tempBase][4] = bin2dec("  X     ");
	normalFont[tempBase][3] = bin2dec(" X      ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec("XXXXX   ");

	tempBase = 'a';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec(" XX X   ");
	normalFont[tempBase][3] = bin2dec("X  XX   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X  XX   ");
	normalFont[tempBase][0] = bin2dec(" XX X   ");
							 

	tempBase = 'b';

	normalFont[tempBase][7] = bin2dec("X       ");
	normalFont[tempBase][6] = bin2dec("X       ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("X XX    ");
	normalFont[tempBase][3] = bin2dec("XX  X   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("XX  X   ");
	normalFont[tempBase][0] = bin2dec("X XX    ");

	tempBase = 'c';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec(" XXX    ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = 'd';

	normalFont[tempBase][7] = bin2dec("    X   ");
	normalFont[tempBase][6] = bin2dec("    X   ");
	normalFont[tempBase][5] = bin2dec("    X   ");
	normalFont[tempBase][4] = bin2dec(" XX X   ");
	normalFont[tempBase][3] = bin2dec("X  XX   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X  XX   ");
	normalFont[tempBase][0] = bin2dec(" XX X   ");

	tempBase = 'e';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec(" XXX    ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec("XXXX    ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec(" XXXX   ");

	tempBase = 'f';

	normalFont[tempBase][7] = bin2dec("  XX    ");
	normalFont[tempBase][6] = bin2dec(" X  X   ");
	normalFont[tempBase][5] = bin2dec(" X      ");
	normalFont[tempBase][4] = bin2dec(" X      ");
	normalFont[tempBase][3] = bin2dec("XXXX    ");
	normalFont[tempBase][2] = bin2dec(" X      ");
	normalFont[tempBase][1] = bin2dec(" X      ");
	normalFont[tempBase][0] = bin2dec(" X      ");

	tempBase = 'g';
	normalFontParam[tempBase][0] = 3;

	normalFont[tempBase][7] = bin2dec(" XXX    ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X  XX   ");
	normalFont[tempBase][3] = bin2dec(" XX X   ");
	normalFont[tempBase][2] = bin2dec("    X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = 'h';

	normalFont[tempBase][7] = bin2dec("X       ");
	normalFont[tempBase][6] = bin2dec("X       ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("X XX    ");
	normalFont[tempBase][3] = bin2dec("XX  X   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec("X   X   ");

	tempBase = 'i';
	normalFontParam[tempBase][1] = 1;
	normalFontParam[tempBase][2] = 2;

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("X       ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec("X       ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec("X       ");

	tempBase = 'j';
	normalFontParam[tempBase][0] = 1;
	normalFontParam[tempBase][1] = 3;
	normalFontParam[tempBase][2] = 4;

	normalFont[tempBase][7] = bin2dec("  X     ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("  X     ");
	normalFont[tempBase][4] = bin2dec("  X     ");
	normalFont[tempBase][3] = bin2dec("  X     ");
	normalFont[tempBase][2] = bin2dec("  X     ");
	normalFont[tempBase][1] = bin2dec("  X     ");
	normalFont[tempBase][0] = bin2dec("XX      ");

	tempBase = 'k';
	normalFontParam[tempBase][1] = 4;
	normalFontParam[tempBase][2] = 5;

	normalFont[tempBase][7] = bin2dec("X       ");
	normalFont[tempBase][6] = bin2dec("X       ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("X  X    ");
	normalFont[tempBase][3] = bin2dec("X X     ");
	normalFont[tempBase][2] = bin2dec("XX      ");
	normalFont[tempBase][1] = bin2dec("X X     ");
	normalFont[tempBase][0] = bin2dec("X  X    ");

	tempBase = 'l';
	normalFontParam[tempBase][1] = 1;
	normalFontParam[tempBase][2] = 2;

	normalFont[tempBase][7] = bin2dec("X       ");
	normalFont[tempBase][6] = bin2dec("X       ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec("X       ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec("X       ");

	tempBase = 'm';
	normalFontParam[tempBase][1] = 6;
	normalFontParam[tempBase][2] = 7;

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("X X X   ");
	normalFont[tempBase][3] = bin2dec("XX X X  ");
	normalFont[tempBase][2] = bin2dec("X  X X  ");
	normalFont[tempBase][1] = bin2dec("X  X X  ");
	normalFont[tempBase][0] = bin2dec("X    X  ");

	tempBase = 'n';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("X XX    ");
	normalFont[tempBase][3] = bin2dec("XX  X   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec("X   X   ");

	tempBase = 'o';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec(" XXX    ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = 'p';
	normalFontParam[tempBase][0] = 3;
	
	normalFont[tempBase][7] = bin2dec("X XX    ");
	normalFont[tempBase][6] = bin2dec("XX  X   ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("XX  X   ");
	normalFont[tempBase][3] = bin2dec("X XX    ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec("X       ");

	tempBase = 'q';
	normalFontParam[tempBase][0] = 3;

	normalFont[tempBase][7] = bin2dec(" XX X   ");
	normalFont[tempBase][6] = bin2dec("X  XX   ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X  XX   ");
	normalFont[tempBase][3] = bin2dec(" XX X   ");
	normalFont[tempBase][2] = bin2dec("    X   ");
	normalFont[tempBase][1] = bin2dec("  XXX   ");
	normalFont[tempBase][0] = bin2dec("    X   ");

	tempBase = 'r';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("X XX    ");
	normalFont[tempBase][3] = bin2dec("XX  X   ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec("X       ");

	tempBase = 's';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec(" XXX    ");
	normalFont[tempBase][3] = bin2dec("X       ");
	normalFont[tempBase][2] = bin2dec(" XXX    ");
	normalFont[tempBase][1] = bin2dec("    X   ");
	normalFont[tempBase][0] = bin2dec("XXXX    ");

	tempBase = 't';
	
	normalFont[tempBase][7] = bin2dec(" X      ");
	normalFont[tempBase][6] = bin2dec(" X      ");
	normalFont[tempBase][5] = bin2dec(" X      ");
	normalFont[tempBase][4] = bin2dec("XXXX    ");
	normalFont[tempBase][3] = bin2dec(" X      ");
	normalFont[tempBase][2] = bin2dec(" X      ");
	normalFont[tempBase][1] = bin2dec(" X  X   ");
	normalFont[tempBase][0] = bin2dec("  XX    ");

	tempBase = 'u';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = 'v';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec(" X  X   ");
	normalFont[tempBase][1] = bin2dec("  X X   ");
	normalFont[tempBase][0] = bin2dec("   X    ");

	tempBase = 'w';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("X   X   ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X X X   ");
	normalFont[tempBase][0] = bin2dec(" X X    ");

	tempBase = 'x';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec(" X X    ");
	normalFont[tempBase][2] = bin2dec("  X     ");
	normalFont[tempBase][1] = bin2dec(" X X    ");
	normalFont[tempBase][0] = bin2dec("X   X   ");

	tempBase = 'y';
	normalFontParam[tempBase][0] = 3;
	
	normalFont[tempBase][7] = bin2dec(" X  X   ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec(" XXXX   ");
	normalFont[tempBase][2] = bin2dec("    X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = 'z';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("XXXXX   ");
	normalFont[tempBase][3] = bin2dec("   X    ");
	normalFont[tempBase][2] = bin2dec("  X     ");
	normalFont[tempBase][1] = bin2dec(" X      ");
	normalFont[tempBase][0] = bin2dec("XXXXX   ");

	

	tempBase = '1';

	normalFont[tempBase][7] = bin2dec("  X     ");
	normalFont[tempBase][6] = bin2dec(" XX     ");
	normalFont[tempBase][5] = bin2dec("X X     ");
	normalFont[tempBase][4] = bin2dec("  X     ");
	normalFont[tempBase][3] = bin2dec("  X     ");
	normalFont[tempBase][2] = bin2dec("  X     ");
	normalFont[tempBase][1] = bin2dec("  X     ");
	normalFont[tempBase][0] = bin2dec("XXXXX   ");

	tempBase = '2';

	normalFont[tempBase][7] = bin2dec(" XXX    ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("    X   ");
	normalFont[tempBase][4] = bin2dec("   X    ");
	normalFont[tempBase][3] = bin2dec("  X     ");
	normalFont[tempBase][2] = bin2dec(" X      ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec("XXXXX   ");

	tempBase = '3';

	normalFont[tempBase][7] = bin2dec(" XXX    ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("    X   ");
	normalFont[tempBase][4] = bin2dec("    X   ");
	normalFont[tempBase][3] = bin2dec("   X    ");
	normalFont[tempBase][2] = bin2dec("    X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = '4';

	normalFont[tempBase][7] = bin2dec("  XX    ");
	normalFont[tempBase][6] = bin2dec(" X X    ");
	normalFont[tempBase][5] = bin2dec("X  X    ");
	normalFont[tempBase][4] = bin2dec("X  X    ");
	normalFont[tempBase][3] = bin2dec("XXXXX   ");
	normalFont[tempBase][2] = bin2dec("   X    ");
	normalFont[tempBase][1] = bin2dec("   X    ");
	normalFont[tempBase][0] = bin2dec("   X    ");

	tempBase = '5';

	normalFont[tempBase][7] = bin2dec("XXXXX   ");
	normalFont[tempBase][6] = bin2dec("X       ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec("XXXX    ");
	normalFont[tempBase][2] = bin2dec("    X   ");
	normalFont[tempBase][1] = bin2dec("    X   ");
	normalFont[tempBase][0] = bin2dec("XXXX    ");

	tempBase = '6';

	normalFont[tempBase][7] = bin2dec("  XX    ");
	normalFont[tempBase][6] = bin2dec(" X      ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec("XXXX    ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = '7';

	normalFont[tempBase][7] = bin2dec("XXXXX   ");
	normalFont[tempBase][6] = bin2dec("    X   ");
	normalFont[tempBase][5] = bin2dec("    X   ");
	normalFont[tempBase][4] = bin2dec("   X    ");
	normalFont[tempBase][3] = bin2dec("   X    ");
	normalFont[tempBase][2] = bin2dec("  X     ");
	normalFont[tempBase][1] = bin2dec("  X     ");
	normalFont[tempBase][0] = bin2dec("  X     ");

	tempBase = '8';

	normalFont[tempBase][7] = bin2dec(" XXX    ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec(" XXX    ");
	normalFont[tempBase][2] = bin2dec("X   X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = '9';

	normalFont[tempBase][7] = bin2dec(" XXX    ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec(" XXXX   ");
	normalFont[tempBase][2] = bin2dec("    X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = '0';

	normalFont[tempBase][7] = bin2dec(" XXX    ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("X   X   ");
	normalFont[tempBase][4] = bin2dec("X   X   ");
	normalFont[tempBase][3] = bin2dec("X  XX   ");
	normalFont[tempBase][2] = bin2dec("XXX X   ");
	normalFont[tempBase][1] = bin2dec("X   X   ");
	normalFont[tempBase][0] = bin2dec(" XXX    ");

	tempBase = '.';
	normalFontParam[tempBase][1] = 1;
	normalFontParam[tempBase][2] = 2;

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("        ");
	normalFont[tempBase][3] = bin2dec("        ");
	normalFont[tempBase][2] = bin2dec("        ");
	normalFont[tempBase][1] = bin2dec("        ");
	normalFont[tempBase][0] = bin2dec("X       ");

	tempBase = ',';
	normalFontParam[tempBase][0] = 1;
	normalFontParam[tempBase][1] = 2;
	normalFontParam[tempBase][2] = 3;
	
	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("        ");
	normalFont[tempBase][3] = bin2dec("        ");
	normalFont[tempBase][2] = bin2dec("        ");
	normalFont[tempBase][1] = bin2dec(" X      ");
	normalFont[tempBase][0] = bin2dec("X       ");

	tempBase = ':';
	normalFontParam[tempBase][1] = 1;
	normalFontParam[tempBase][2] = 2;

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("        ");
	normalFont[tempBase][3] = bin2dec("X       ");
	normalFont[tempBase][2] = bin2dec("        ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec("        ");

	tempBase = ';';
	normalFontParam[tempBase][0] = 1;
	normalFontParam[tempBase][1] = 2;
	normalFontParam[tempBase][2] = 3;

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("        ");
	normalFont[tempBase][3] = bin2dec(" X      ");
	normalFont[tempBase][2] = bin2dec("        ");
	normalFont[tempBase][1] = bin2dec(" X      ");
	normalFont[tempBase][0] = bin2dec("X       ");

	tempBase = '!';
	normalFontParam[tempBase][1] = 1;
	normalFontParam[tempBase][2] = 2;

	normalFont[tempBase][7] = bin2dec("X       ");
	normalFont[tempBase][6] = bin2dec("X       ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec("X       ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("        ");
	normalFont[tempBase][0] = bin2dec("X       ");

	tempBase = '?';

	normalFont[tempBase][7] = bin2dec(" XXX    ");
	normalFont[tempBase][6] = bin2dec("X   X   ");
	normalFont[tempBase][5] = bin2dec("    X   ");
	normalFont[tempBase][4] = bin2dec("   X    ");
	normalFont[tempBase][3] = bin2dec("  X     ");
	normalFont[tempBase][2] = bin2dec("  X     ");
	normalFont[tempBase][1] = bin2dec("        ");
	normalFont[tempBase][0] = bin2dec("  X     ");

	tempBase = '\'';
	normalFontParam[tempBase][1] = 2;
	normalFontParam[tempBase][2] = 3;

	normalFont[tempBase][7] = bin2dec(" X      ");
	normalFont[tempBase][6] = bin2dec(" X      ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("        ");
	normalFont[tempBase][3] = bin2dec("        ");
	normalFont[tempBase][2] = bin2dec("        ");
	normalFont[tempBase][1] = bin2dec("        ");
	normalFont[tempBase][0] = bin2dec("        ");

	tempBase = '\"';
	normalFontParam[tempBase][1] = 3;
	normalFontParam[tempBase][2] = 4;

	normalFont[tempBase][7] = bin2dec("X X     ");
	normalFont[tempBase][6] = bin2dec("X X     ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("        ");
	normalFont[tempBase][3] = bin2dec("        ");
	normalFont[tempBase][2] = bin2dec("        ");
	normalFont[tempBase][1] = bin2dec("        ");
	normalFont[tempBase][0] = bin2dec("        ");

	tempBase = '-';
	normalFontParam[tempBase][1] = 5;
	normalFontParam[tempBase][2] = 6;

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("        ");
	normalFont[tempBase][3] = bin2dec("        ");
	normalFont[tempBase][2] = bin2dec("XXXXX   ");
	normalFont[tempBase][1] = bin2dec("        ");
	normalFont[tempBase][0] = bin2dec("        ");

	tempBase = '@';
	normalFontParam[tempBase][1] = 6;
	normalFontParam[tempBase][2] = 7;

	normalFont[tempBase][7] = bin2dec(" XXXX   ");
	normalFont[tempBase][6] = bin2dec("X    X  ");
	normalFont[tempBase][5] = bin2dec("X XX X  ");
	normalFont[tempBase][4] = bin2dec("X X  X  ");
	normalFont[tempBase][3] = bin2dec("X X  X  ");
	normalFont[tempBase][2] = bin2dec("X XXX   ");
	normalFont[tempBase][1] = bin2dec("X    X  ");
	normalFont[tempBase][0] = bin2dec(" XXXX   ");

	tempBase = 1;
	normalFontParam[tempBase][1] = 7;
	normalFontParam[tempBase][2] = 8;
	
	normalFont[tempBase][7] = bin2dec("X       ");
	normalFont[tempBase][6] = bin2dec("XX      ");
	normalFont[tempBase][5] = bin2dec("XXX     ");
	normalFont[tempBase][4] = bin2dec("XXXX    ");
	normalFont[tempBase][3] = bin2dec("XXXXX   ");
	normalFont[tempBase][2] = bin2dec("XXXXXX  ");
	normalFont[tempBase][1] = bin2dec("XXXXX   ");
	normalFont[tempBase][0] = bin2dec("XXXX    ");

	tempBase = 2;
	normalFontParam[tempBase][1] = 6;
	normalFontParam[tempBase][2] = 7;
	
	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec(" X      ");
	normalFont[tempBase][3] = bin2dec(" XX     ");
	normalFont[tempBase][2] = bin2dec(" X X    ");
	normalFont[tempBase][1] = bin2dec(" X      ");
	normalFont[tempBase][0] = bin2dec("        ");

	tempBase = '[';
	normalFontParam[tempBase][1] = 4;
	normalFontParam[tempBase][2] = 5;

	normalFont[tempBase][7] = bin2dec("XXXX    ");
	normalFont[tempBase][6] = bin2dec("X       ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec("X       ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec("X       ");
	normalFont[tempBase][0] = bin2dec("XXXX    ");

	tempBase = ']';
	normalFontParam[tempBase][1] = 4;
	normalFontParam[tempBase][2] = 5;

	normalFont[tempBase][7] = bin2dec("XXXX    ");
	normalFont[tempBase][6] = bin2dec("   X    ");
	normalFont[tempBase][5] = bin2dec("   X    ");
	normalFont[tempBase][4] = bin2dec("   X    ");
	normalFont[tempBase][3] = bin2dec("   X    ");
	normalFont[tempBase][2] = bin2dec("   X    ");
	normalFont[tempBase][1] = bin2dec("   X    ");
	normalFont[tempBase][0] = bin2dec("XXXX    ");

	tempBase = '(';
	normalFontParam[tempBase][1] = 3;
	normalFontParam[tempBase][2] = 4;

	normalFont[tempBase][7] = bin2dec("  X     ");
	normalFont[tempBase][6] = bin2dec(" X      ");
	normalFont[tempBase][5] = bin2dec("X       ");
	normalFont[tempBase][4] = bin2dec("X       ");
	normalFont[tempBase][3] = bin2dec("X       ");
	normalFont[tempBase][2] = bin2dec("X       ");
	normalFont[tempBase][1] = bin2dec(" X      ");
	normalFont[tempBase][0] = bin2dec("  X     ");

	tempBase = ')';
	normalFontParam[tempBase][1] = 3;
	normalFontParam[tempBase][2] = 4;

	normalFont[tempBase][7] = bin2dec("X       ");
	normalFont[tempBase][6] = bin2dec(" X      ");
	normalFont[tempBase][5] = bin2dec("  X     ");
	normalFont[tempBase][4] = bin2dec("  X     ");
	normalFont[tempBase][3] = bin2dec("  X     ");
	normalFont[tempBase][2] = bin2dec("  X     ");
	normalFont[tempBase][1] = bin2dec(" X      ");
	normalFont[tempBase][0] = bin2dec("X       ");

	tempBase = '\\';
	normalFontParam[tempBase][1] = 4;
	normalFontParam[tempBase][2] = 5;

	normalFont[tempBase][7] = bin2dec("X       ");
	normalFont[tempBase][6] = bin2dec("X       ");
	normalFont[tempBase][5] = bin2dec(" X      ");
	normalFont[tempBase][4] = bin2dec(" X      ");
	normalFont[tempBase][3] = bin2dec("  X     ");
	normalFont[tempBase][2] = bin2dec("  X     ");
	normalFont[tempBase][1] = bin2dec("   X    ");
	normalFont[tempBase][0] = bin2dec("   X    ");

	tempBase = ' ';

	normalFont[tempBase][7] = bin2dec("        ");
	normalFont[tempBase][6] = bin2dec("        ");
	normalFont[tempBase][5] = bin2dec("        ");
	normalFont[tempBase][4] = bin2dec("        ");
	normalFont[tempBase][3] = bin2dec("        ");
	normalFont[tempBase][2] = bin2dec("        ");
	normalFont[tempBase][1] = bin2dec("        ");
	normalFont[tempBase][0] = bin2dec("        ");


}