#include <stdio.h>
#include <allegro.h>
#include <winalleg.h>
#include <windowsx.h>
#include <math.h>
#include <shellapi.h>

#include "resource.h"

#define XOFF 35
#define YOFF 46

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCRRES (SCREEN_WIDTH*SCREEN_HEIGHT)

#define MAX_DIVERGENCE 100
#define MAX_DIVERGENCE_NEG -100


#define STARTX1 -2.5
#define STARTY1 -2
#define STARTX2 1.5
#define STARTY2 2

HWND hMain;
HDC hDC;

BITMAP* screenbitmap;
BITMAP* secondbuffer;

int MAX_DEPTH = 75;

int curpal = 3;
int palette[6][768];

_inline double intensity(int d)
{
	return ((double)d / (double)MAX_DEPTH);
}

_inline void squareCoord(double * pos, double * sq)
{
	sq[0] = (pos[0] * pos[0]) - (pos[1] * pos[1]);
	sq[1] = 2 * pos[0] * pos[1];
}

_inline int delvePoint(double * pos, double * base, int depth)
{
	if (depth == MAX_DEPTH) return MAX_DEPTH;

	double sq[2];

	squareCoord(pos,sq);
	pos[0] = sq[0] + base[0];
	pos[1] = sq[1] + base[1];

	if (pos[0] > MAX_DIVERGENCE || pos[0] < MAX_DIVERGENCE_NEG || pos[1] > MAX_DIVERGENCE || pos[1] < MAX_DIVERGENCE_NEG)
		return depth;

	return delvePoint(pos,base,depth+1);
}

int intens[SCREEN_WIDTH][SCREEN_HEIGHT];
int gdepth = 0;

double xlength;
double ylength;

double begx;
double begy;

double endx;
double endy;

double lbegx;
double lbegy;

double lendx;
double lendy;

_inline int pal(int d)
{
	d = (int) ( (double) 255 * ((double) d / (double) gdepth) );
	return makecol(palette[curpal][d*3],palette[curpal][d*3+1],palette[curpal][d*3+2]);
}

void updateText()
{
	char text[1000];
	text[0] = 0;
	sprintf(text,"Top-Left: (%f,%f)   Bottom-Right: (%f,%f)",begx,-begy,endx,-endy);
	Static_SetText(GetDlgItem(hMain,IDC_COORDS),text);
}


_inline void drawMandelbrot(double x1, double y1, double x2, double y2)
{
	xlength = (x2 - x1) / (double)SCREEN_WIDTH;
	ylength = (y2 - y1) / (double)SCREEN_HEIGHT;

	lbegx = begx;
	lbegy = begy;

	lendx = endx;
	lendy = endy;

	begx = x1;
	begy = y1;

	endx = x2;
	endy = y2;

	double pos[2];
	double base[2];
	
	gdepth = 0;

	blit(screenbitmap,secondbuffer,0,0,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	int scrtot = 0;

	for (int xscreenpos = 0; xscreenpos < SCREEN_WIDTH; xscreenpos++)
	{
		for (int yscreenpos = 0; yscreenpos < SCREEN_HEIGHT; yscreenpos++)
		{
			pos[0] = (xscreenpos * xlength) + x1;
			base[0] = pos[0];

			pos[1] = (yscreenpos * ylength) + y1;
			base[1] = pos[1];
			
			int depth = delvePoint(pos,base,0);

			if (depth > gdepth) gdepth = depth;
			intens[xscreenpos][yscreenpos] = depth;
			//putpixel(screenbitmap,xscreenpos,yscreenpos,pal(  (int)(  (double)255*((double)depth/(double)MAX_DEPTH))  ) );

			scrtot++;

			if (scrtot % 10000 == 0)
			{
				int scrx = (int)(((double)scrtot / (double)SCRRES) * SCREEN_WIDTH);

				rectfill(secondbuffer,0,SCREEN_HEIGHT-10,scrx,SCREEN_HEIGHT,makecol(255,0,0));
				
				draw_to_hdc(hDC, secondbuffer, 0, 0);			
			}
		}
			
	}

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			putpixel(screenbitmap,x,y,pal(intens[x][y]) );
		}
	}
	

	draw_to_hdc(hDC, screenbitmap, 0, 0);
	updateText();

}

void undo()
{
	drawMandelbrot(lbegx,lbegy,lendx,lendy);
}

void realign()
{
	double ratio = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;
	double centerx = (begx + endx) / 2;
	double centery = (begy + endy) / 2;
	
	double xdis = centerx - begx;
	double ydis = xdis / ratio;

	begy = centery - ydis;
	endy = centery + ydis;

	drawMandelbrot(begx,begy,endx,endy);
}

void zoom(double mult)
{
	double centerx = (begx + endx) / 2;
	double centery = (begy + endy) / 2;
	
	double xdis = (centerx - begx) * mult;
	double ydis = (centery - begy) * mult;

	begx = centerx - xdis;
	endx = centerx + xdis;

	begy = centery - ydis;
	endy = centery + ydis;

	drawMandelbrot(begx,begy,endx,endy);	
}

_inline void newbox(int x1, int y1, int x2, int y2)
{
	x1 -= XOFF;
	x2 -= XOFF;
	y1 -= YOFF;
	y2 -= YOFF;

	if (x1 == x2 || y1 == y2) return;
	if (x2 < x1) 
	{
		int temp = x2;
		x2 = x1;
		x1 = temp;
	}
	if (y2 < y1) 
	{
		int temp = y2;
		y2 = y1;
		y1 = temp;
	}

	
	double newx1 = ( x1 * xlength ) + begx;
	double newx2 = ( x2 * xlength ) + begx;

	double newy1 = ( y1 * ylength ) + begy;
	double newy2 = ( y2 * ylength ) + begy;

	drawMandelbrot(newx1,newy1,newx2,newy2);		

}

_inline void showbox(int x1, int y1, int x2, int y2)
{
	x1 -= XOFF;
	y1 -= YOFF;
	x2 -= XOFF;
	y2 -= YOFF;


	int col = makecol(255,255,255);
	blit(screenbitmap,secondbuffer,0,0,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	
	line(secondbuffer,x1,y1,x1,y2,col);
	line(secondbuffer,x2,y1,x2,y2,col);
	line(secondbuffer,x1,y1,x2,y1,col);
	line(secondbuffer,x1,y2,x2,y2,col);

	draw_to_hdc(hDC, secondbuffer, 0, 0);
}


int firstx;
int firsty;

int down = 0;

int ready = 0;

int CALLBACK DialogProc (HWND hwnd, UINT message,WPARAM wParam,LPARAM lParam)
{
	POINTS p;
	
	int px,py;

	switch (message)
	{

		case WM_CLOSE:
			allegro_exit();
			exit(0);
			break;

		case WM_SHOWWINDOW:
			//if (ready) drawMandelbrot(begx,begy,endx,endy);
			break;

		case WM_COMMAND:

			if (LOWORD(wParam) == IDM_RESTART) 
				drawMandelbrot(STARTX1,STARTY1,STARTX2,STARTY2);
			else 
			if (LOWORD(wParam) == IDM_QUIT)
			{				
				destroy_bitmap(screenbitmap);
				destroy_bitmap(secondbuffer);
				allegro_exit();
				exit(0);
			}
			else 
			if (LOWORD(wParam) == IDM_REALIGN) 
				realign();
			else
			if (LOWORD(wParam) == IDM_ZOOMO2)
				zoom(2);
			else
			if (LOWORD(wParam) == IDM_ZOOMO5)
				zoom(5);
			else
			if (LOWORD(wParam) == IDM_ZOOMO10)
				zoom(10);
			else
			if (LOWORD(wParam) == IDM_UNDO)
				undo();			
			else
			if (LOWORD(wParam) == IDM_RES25)
				{ MAX_DEPTH = 25; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RES50)
				{ MAX_DEPTH = 50; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RES100)
				{ MAX_DEPTH = 75; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RES200)
				{ MAX_DEPTH = 100; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RES400)
				{ MAX_DEPTH = 125; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RES800)
				{ MAX_DEPTH = 150; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RES1600)
				{ MAX_DEPTH = 175; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RES3200)
				{ MAX_DEPTH = 200; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RES6400)
				{ MAX_DEPTH = 250; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RES12800)
				{ MAX_DEPTH = 300; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RES25600)
				{ MAX_DEPTH = 400; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RESA)
				{ MAX_DEPTH = 800; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RESB)
				{ MAX_DEPTH = 1600; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RESC)
				{ MAX_DEPTH = 3200; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RESD)
				{ MAX_DEPTH = 6400; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RESE)
				{ MAX_DEPTH = 12800; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RESF)
				{ MAX_DEPTH = 25600; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_BLUE)
			{ curpal = 0;  drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RED)
			{ curpal = 1; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_GREEN)
			{ curpal = 2; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_YELLOW)
			{ curpal = 4; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_GRAY)
			{ curpal = 3; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_RAINBOW)
			{ curpal = 5; drawMandelbrot(begx,begy,endx,endy);}			
			else
			if (LOWORD(wParam) == IDM_WEB)
				ShellExecute(NULL, "open", "http://www.warped.nu/~wyv", NULL, NULL, SW_SHOWNORMAL);
			else
			if (LOWORD(wParam) == IDM_WEB2)
				ShellExecute(NULL, "open", "http://www.warped.nu/~wyv/mandelbrot", NULL, NULL, SW_SHOWNORMAL);
			
			down = 0;
	
			break;

		case WM_LBUTTONDOWN:

			p = MAKEPOINTS(lParam);
			firstx = p.x;
			firsty = p.y;
			
			down = 1;

			break;

		case WM_LBUTTONUP:

			p = MAKEPOINTS(lParam);

			px = p.x;
			py = p.y;

			down = 0;

			if (px == firstx && py == firsty) draw_to_hdc(hDC, screenbitmap, 0, 0);
			else
				newbox(px,py,firstx,firsty);

			break;

		case WM_MOUSEMOVE:
			p = MAKEPOINTS(lParam);

			if (down) showbox(p.x,p.y,firstx,firsty);
			break;


	}

	
	return 0;
}



LRESULT CALLBACK WndProc(HWND hWnd, unsigned int iMessage, WPARAM wParam, LPARAM lParam)
{

	switch (iMessage)
	{
	case WM_CLOSE:

		exit(0);

		break;

	
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}


void loadPalettes()
{
	FILE* file = fopen("palettes.pal","rb");

	int pos = 0;
	int syc = 0;
	
	pos=0;
	while (pos < 768)
	{
		fscanf(file,"%c",&(palette[0][pos]));
		palette[0][pos] *= 8;
		if (palette[0][pos] > 255) palette[0][pos] = 255;
		pos++;		
	}

	pos=0;
	while (pos < 768)
	{
		fscanf(file,"%c",&(palette[1][pos]));
		palette[1][pos] *= 8;
		if (palette[1][pos] > 255) palette[1][pos] = 255;
		pos++;		
	}

	pos=0;
	while (pos < 768)
	{
		fscanf(file,"%c",&(palette[2][pos]));
		palette[2][pos] *= 8;
		if (palette[2][pos] > 255) palette[2][pos] = 255;
		pos++;		
	}
	pos=0;
	while (pos < 768)
	{
		fscanf(file,"%c",&(palette[3][pos]));
		palette[3][pos] *= 8;
		if (palette[3][pos] > 255) palette[3][pos] = 255;
		pos++;		
	}
	pos=0;
	while (pos < 768)
	{
		fscanf(file,"%c",&(palette[4][pos]));
		palette[4][pos] *= 8;
		if (palette[4][pos] > 255) palette[4][pos] = 255;
		pos++;		
	}
	pos=0;
	while (pos < 768)
	{
		fscanf(file,"%c",&(palette[5][pos]));
		palette[5][pos] *= 8;
		if (palette[5][pos] > 255) palette[5][pos] = 255;
		pos++;		
	}
	
	fclose(file);
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

	WNDCLASS WndClass;

	memset(&WndClass, 0, sizeof(WndClass));
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, NULL);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = "Squares";
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	
	if(!RegisterClass(&WndClass)) return 0;

	
	hMain = CreateDialog(hInstance,MAKEINTRESOURCE(IDD_FORMVIEW),NULL,DialogProc);

	hDC = GetDC(GetDlgItem(hMain,IDC_VIEW));

	loadPalettes();

	install_allegro(SYSTEM_NONE,&errno,atexit);
	set_color_depth(32);
	set_gfx_mode(GFX_GDI,640,480,640,480);
	set_gdi_color_format();

	MSG Message;

	screenbitmap = create_bitmap(SCREEN_WIDTH,SCREEN_HEIGHT);
	secondbuffer = create_bitmap(SCREEN_WIDTH,SCREEN_HEIGHT);

	drawMandelbrot(STARTX1,STARTY1,STARTX2,STARTY2);	

	ready = 1;

	lbegx = begx;
	lbegy = begy;
	lendx = endx;
	lendy = endy;

	while(GetMessage(&Message, hMain, 0, 0))
	{	
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}


	return 0;

}


