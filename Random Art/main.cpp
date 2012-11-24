/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Mon Oct 28 20:11:11 PST 2002
    copyright            : (C) 2002 by Jason Fieldman
    email                : jmfieldman@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "jpeg.h"
#include "token.h"

#define MAX_DEPTH 10

void removespaces(char* str)
{
	int pos = 0;

	while (str[pos] != 0)
	{
		if (str[pos] == ' ')
		{
			int pos2 = pos;
			while (str[pos2] != 0)
			{
				str[pos2] = str[pos2+1];
				pos2++;
			}
			pos--;
		}
		pos++;
	}
}

int drawImage(Token* randomart, int w, int h, char* filename)
{
	unsigned char* buffer = new unsigned char[w*h*3];
	
	ColorValue* cv;
	
	double dx = (double)2.0 / (double)w;
	double dy = (double)2.0 / (double)h;
	
	double xpos = (double)-1.0;
	double ypos = (double)-1.0;
	
	for (int x = 0; x < w; x++)
	{
		ypos = (double)-1.0;
	 	for (int y = 0; y < h; y++)
	 	{
	 		cv = randomart->getValue(xpos,ypos);
			
			int r = (int)(cv->r*128+128);
			int g = (int)(cv->g*128+128);
			int b = (int)(cv->b*128+128);

			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;

			putpixel(buffer,w,h,x,y,r,g,b);
	 	
	 		ypos += dy;
	 	}
	 	xpos += dx;
	}
	
	int ret = createjpeg(buffer,w,h,filename);
	
	delete[] buffer;
	
	return ret;
}

void HandleEquationGeneration(int argc, char** argv)
{
	if (argc != 3) return;
	
	if (strcasecmp("depth",argv[1])) return;
	
	int depth = atoi(argv[2]);

	if (depth < 2) depth = 2;
	if (depth > MAX_DEPTH) depth = MAX_DEPTH;

	setMaxDepth(depth);
	
	Token* randomart = createToken(0);

	FILE* tmpf = tmpfile();

	randomart->save(tmpf);
	
	delete randomart;
	
	rewind(tmpf);
	char ch;
	while (EOF != fscanf(tmpf, "%c", &ch))
	{
		printf("%c",ch);
	}
	fclose(tmpf);

	exit(0);
}

int main(int argc, char *argv[])
{
	srand(time(0));
		
	HandleEquationGeneration(argc,argv);

	printf("Content-Type: image/jpeg\n\n");

	Token* randomart = NULL;

	int w = 300;
	int h = 300;
	
	//setMaxDepth(3);
	FILE* tmpf = tmpfile();
	char* ev = getenv("QUERY_STRING");
	
	if (ev == NULL) return 1;

	if (ev[0] == '*')
	{
		switch (ev[1])
		{
		case '0': w = 640; h = 480; break;
		case '1': w = 800; h = 600; break;
		case '2': w = 1024; h = 768; break;
		case '3': w = 1280; h = 1024; break;
		case '4': w = 1600; h = 1200; break;
		case '5': w = 75; h = 75; break;
		}
		ev += 2;
	}

	int slen = strlen(ev);
	for (int spos = 0; spos < slen; spos++)
	{
		ev[spos] = toupper(ev[spos]);
	}
	//removespaces(ev);
	
	fprintf(tmpf, "%s", ev);
	
	rewind(tmpf);
	randomart = createTokenFromFile(tmpf);
	fclose(tmpf);
	
	char eightname[9];	
	eightname[8] = 0;
	for (int pos = 0; pos < 8; pos++)
	{
	 	eightname[pos] = (rand()%26) + 65;
	}
	
	char filename[256];
	sprintf(filename, "./pics/%s.jpg", eightname);
	
	drawImage(randomart, w, h, filename);
	
	FILE* file = fopen(filename, "rb");

	char ch;

	while (fscanf(file, "%c", &ch)!=EOF)
		printf("%c",ch);
	
	fclose(file);
	
	char syscmd[256];

	sprintf(syscmd, "rm -rf %s", filename);
	system(syscmd);	
	
	return 0;
}
