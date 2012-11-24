#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include <windowsx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include "equation.h"
#include "token.h"
#include "vector.h"
#include "complextoken.h"
#include "ComplexValue.h"
#include "pointlist.h"

#include "resource.h"

#define VIEW_GRAPH 0
#define VIEW_IMAGE 1

struct bounds {
	double left,right,top,bottom;
};

int lastx = 0,lasty = 0;

int mode = 0;

int PRECISION = 50;

RECT win1,win2;

HWND hMain;

HGLRC hRC1;		
HDC hDC1;

HGLRC hRC2;		
HDC hDC2;

Token* equation = NULL;
ComplexToken* complexequation = NULL;

PointList* upoints = NULL;

int currentwindow = -1;
int ww,wh;

bounds viewbounds[2];

void setActiveView(int view);
void drawGraphs();

int graphlist[2] = { 0,0 };

static	PIXELFORMATDESCRIPTOR pfd=
{
	sizeof(PIXELFORMATDESCRIPTOR),		
	1,									
	PFD_DRAW_TO_WINDOW |				
	PFD_SUPPORT_OPENGL |				
	PFD_DOUBLEBUFFER,					
	PFD_TYPE_RGBA,						
	16,									
	0, 0, 0, 0, 0, 0,					
	0,									
	0,									
	0,									
	0, 0, 0, 0,							
	16,									
	0,									
	0,									
	PFD_MAIN_PLANE,						
	0,									
	0, 0, 0								
};

void zifyequation(char* str)
{
	int pos = 0;
	while (str[pos] != 0)
	{
		if (str[pos] == 'z' || str[pos] == 'Z') str[pos] = 'x';
		pos++;
	}
}

void clearUserPoints()
{
	if (upoints != NULL) delete upoints;
	upoints = NULL;
}

void closeWindow()
{
	wglMakeCurrent(hDC1,NULL);
	wglDeleteContext(hRC1);

	//wglMakeCurrent(hDC2,NULL);
	//wglDeleteContext(hRC2);

	if (equation != NULL) delete equation;
	if (complexequation != NULL) delete complexequation;
	if (upoints != NULL) delete upoints;

	exit(0);
}

void Swap()
{
	setActiveView(0);
	SwapBuffers(hDC1);

	setActiveView(1);
	SwapBuffers(hDC2);
}

int isInWindow(int window, int x, int y)
{
	RECT* rect = &win1;
	if (window == 1) rect = &win2;

	if (x <= rect->right && x >= rect->left && y >= rect->top && y <= rect->bottom) return 1;
	return 0;
}

void resetGLWindowBounds()
{
	for (int x = 0; x < 2; x++)
	{
		setActiveView(x);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(viewbounds[x].left, viewbounds[x].right, viewbounds[x].bottom, viewbounds[x].top);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	drawGraphs();
}

void drawAxis()
{
	for (int x = 0; x < 2; x++)
	{
		setActiveView(x);

		int l = (int)viewbounds[x].left;
		int r = (int)viewbounds[x].right;
		int t = (int)viewbounds[x].top;
		int b = (int)viewbounds[x].bottom;

		glColor3d(0.75,0.75,0.75);

		glBegin(GL_LINES);

		for (int h = l; h <= r; h++)
		{
			glVertex2d(h,viewbounds[x].top);
			glVertex2d(h,viewbounds[x].bottom);
		}

		for (int v = b; v <= t; v++)
		{
			glVertex2d(viewbounds[x].left,v);
			glVertex2d(viewbounds[x].right,v);
		}

		glEnd();

		glColor3f(0,0,0);

		glLineWidth(2);

		glBegin(GL_LINES);

		glVertex2d(viewbounds[x].left,0);
		glVertex2d(viewbounds[x].right,0);

		glVertex2d(0,viewbounds[x].top);
		glVertex2d(0,viewbounds[x].bottom);

		glEnd();

		glLineWidth(1);
	}
}

void setActiveView(int view)
{
	if (!view)
	{
		if(!wglMakeCurrent(hDC1, hRC1))
		{
			MessageBox(0,"Can't activate GLRC.","Error",MB_OK|MB_ICONERROR);
			closeWindow();
		}
	}
	else
	{
		if(!wglMakeCurrent(hDC2, hRC2))
		{
			MessageBox(0,"Can't activate GLRC.","Error",MB_OK|MB_ICONERROR);
			closeWindow();
		}
	}
}

void drawLists()
{
	for (int x = 0; x < 2; x++)
	{
		setActiveView(x);

		//glClear(GL_COLOR_BUFFER_BIT);
		glLineWidth(4);
		glCallList(graphlist[x]);
		glLineWidth(1);
	}
}

void makeBlanketLists()
{

	mode = 0;

	PRECISION = 50;
	
	int numpoints = (PRECISION+1) * (PRECISION+1);

	pointData* points = new pointData[numpoints];

	double w = viewbounds[0].right - viewbounds[0].left;
	double h = viewbounds[0].top - viewbounds[0].bottom;
	double cellw = w / (double)PRECISION;
	double cellh = h / (double)PRECISION;

	{
	for (int x = 0; x <= PRECISION; x++)
	{
		for (int y = 0; y <= PRECISION; y++)
		{

			double xper = x / (double)(PRECISION+1);
			double yper = y / (double)(PRECISION+1);

			int pos = x + (y * (PRECISION+1));
	
			points[pos].x1 = viewbounds[0].left + (cellw * x);
			points[pos].y1 = viewbounds[0].bottom + (cellh * y);

			ComplexValue cv(points[pos].x1,points[pos].y1);

			ComplexValue* res = complexequation->evaluate(&cv);

			points[pos].x2 = res->getR();
			points[pos].y2 = res->getI();

			delete res;

			points[pos].r = xper;
			points[pos].g = yper;
			points[pos].b = 1-xper;

		}
	}
	}

	setActiveView(0);
	glDeleteLists(graphlist[0],1);	
	graphlist[0] = glGenLists(1);
	glNewList(graphlist[0],GL_COMPILE);

	glBegin(GL_QUADS);

	{
	for (int x = 0; x < PRECISION; x++)
	{
		for (int y = 0; y < PRECISION; y++)
		{
			int pos = x + (y * (PRECISION+1));

			glColor3d(points[pos].r,points[pos].g,points[pos].b);
			glVertex2d(points[pos].x1,points[pos].y1);

			glColor3d(points[pos+1].r,points[pos+1].g,points[pos+1].b);
			glVertex2d(points[pos+1].x1,points[pos+1].y1);

			glColor3d(points[pos+2+PRECISION].r,points[pos+2+PRECISION].g,points[pos+2+PRECISION].b);
			glVertex2d(points[pos+2+PRECISION].x1,points[pos+2+PRECISION].y1);

			glColor3d(points[pos+1+PRECISION].r,points[pos+1+PRECISION].g,points[pos+1+PRECISION].b);
			glVertex2d(points[pos+1+PRECISION].x1,points[pos+1+PRECISION].y1);
		}
	}
	}

	glEnd();

	glEndList();

	setActiveView(1);
	glDeleteLists(graphlist[1],1);	
	graphlist[1] = glGenLists(1);
	glNewList(graphlist[1],GL_COMPILE);

	glBegin(GL_QUADS);

	for (int x = 0; x < PRECISION; x++)
	{
		for (int y = 0; y < PRECISION; y++)
		{
			int pos = x + (y * (PRECISION+1));

			glColor3d(points[pos].r,points[pos].g,points[pos].b);
			glVertex2d(points[pos].x2,points[pos].y2);

			glColor3d(points[pos+1].r,points[pos+1].g,points[pos+1].b);
			glVertex2d(points[pos+1].x2,points[pos+1].y2);

			glColor3d(points[pos+2+PRECISION].r,points[pos+2+PRECISION].g,points[pos+2+PRECISION].b);
			glVertex2d(points[pos+2+PRECISION].x2,points[pos+2+PRECISION].y2);

			glColor3d(points[pos+1+PRECISION].r,points[pos+1+PRECISION].g,points[pos+1+PRECISION].b);
			glVertex2d(points[pos+1+PRECISION].x2,points[pos+1+PRECISION].y2);
		}
	}

	glEnd();

	glEndList();

	delete [] points;
}

void makeLineLists()
{
	mode = 1;
	
	PRECISION = 2500;

	int numpoints = (PRECISION+1);

	pointData* points = new pointData[numpoints];

	double w = viewbounds[0].right - viewbounds[0].left;	
	double cellw = w / (double)PRECISION;

	{
	for (int x = 0; x <= PRECISION; x++)
	{
		double xper = x / (double)(PRECISION+1);

		int pos = x;

		points[pos].x1 = viewbounds[0].left + (cellw * x);
		points[pos].y1 = equation->evaluate(points[pos].x1,0);

		ComplexValue cv(points[pos].x1,points[pos].y1);

		ComplexValue* res = complexequation->evaluate(&cv);

		points[pos].x2 = res->getR();
		points[pos].y2 = res->getI();

		delete res;

		points[pos].r = xper;
		points[pos].g = 0;
		points[pos].b = 1-xper;

	}
	}

	setActiveView(0);
	glDeleteLists(graphlist[0],1);	
	graphlist[0] = glGenLists(1);
	glNewList(graphlist[0],GL_COMPILE);

	glBegin(GL_LINES);

	{
	for (int x = 0; x < PRECISION; x++)
	{
		int pos = x;

		glColor3d(points[pos].r,points[pos].g,points[pos].b);
		glVertex2d(points[pos].x1,points[pos].y1);

		glColor3d(points[pos+1].r,points[pos+1].g,points[pos+1].b);
		glVertex2d(points[pos+1].x1,points[pos+1].y1);
	}
	}

	glEnd();

	glEndList();

	setActiveView(1);
	glDeleteLists(graphlist[1],1);	
	graphlist[1] = glGenLists(1);
	glNewList(graphlist[1],GL_COMPILE);

	glBegin(GL_LINES);

	for (int x = 0; x < PRECISION; x++)
	{
		int pos = x;

		glColor3d(points[pos].r,points[pos].g,points[pos].b);
		glVertex2d(points[pos].x2,points[pos].y2);

		glColor3d(points[pos+1].r,points[pos+1].g,points[pos+1].b);
		glVertex2d(points[pos+1].x2,points[pos+1].y2);
	}

	glEnd();

	glEndList();

	delete [] points;


}

void addPoint(int x1, int y1, int x2, int y2)
{
	double w = viewbounds[0].right - viewbounds[0].left;
	double h = viewbounds[0].top - viewbounds[0].bottom;

	double px1 = x1 - win1.left;
	double px2 = x2 - win1.left;

	double py1 = y1 - win1.top;
	double py2 = y2 - win1.top;

	double rx1 = px1 / (double)ww;
	double rx2 = px2 / (double)ww;

	double ry1 = py1 / (double)wh;
	double ry2 = py2 / (double)wh;

	double dx1 = viewbounds[0].left + (w * rx1);
	double dx2 = viewbounds[0].left + (w * rx2);

	double dy1 = viewbounds[0].top - (h * ry1);
	double dy2 = viewbounds[0].top - (h * ry2);

	ComplexValue cv1(dx1,dy1);
	ComplexValue cv2(dx2,dy2);

	ComplexValue* R1 = complexequation->evaluate(&cv1);
	ComplexValue* R2 = complexequation->evaluate(&cv2);

	pointData p1,p2;

	p1.x1 = dx1;
	p1.y1 = dy1;

	p2.x1 = R1->getR();
	p2.y1 = R1->getI();

	p1.x2 = dx2;
	p1.y2 = dy2;

	p2.x2 = R2->getR();
	p2.y2 = R2->getI();

	delete R1;
	delete R2;

	p1.r = 0.25; p1.g = 0.25; p1.b = 1;
	p2.r = 0.25; p2.g = 0.25; p2.b = 1;

	PointList* pl = new PointList();

	pl->setData(&p1,0);
	pl->setData(&p2,1);

	if (upoints == NULL) upoints = pl;
	else upoints->add(pl);
}

void moveBounds(int window, int dx, int dy)
{
	double w = viewbounds[window].right - viewbounds[window].left;
	double h = viewbounds[window].top - viewbounds[window].bottom;

	double ax = (double)dx / (double)ww;
	double ay = (double)dy / (double)wh;

	ax *= w;
	ay *= h;

	viewbounds[window].right += ax;
	viewbounds[window].left += ax;
	viewbounds[window].bottom += ay;
	viewbounds[window].top += ay;

	resetGLWindowBounds();
}

void zoomIn(int b)
{
	double w = viewbounds[b].right - viewbounds[b].left;
	double h = viewbounds[b].top - viewbounds[b].bottom;

	double cx = (viewbounds[b].right + viewbounds[b].left)/2;
	double cy = (viewbounds[b].top + viewbounds[b].bottom)/2;

	w /= 4.0;
	h /= 4.0;

	viewbounds[b].right = cx + w;
	viewbounds[b].left = cx - w;
	viewbounds[b].top = cy + h;
	viewbounds[b].bottom = cy - h;

	resetGLWindowBounds();
}

void zoomOut(int b)
{	
	double w = viewbounds[b].right - viewbounds[b].left;
	double h = viewbounds[b].top - viewbounds[b].bottom;

	double cx = (viewbounds[b].right + viewbounds[b].left)/2;
	double cy = (viewbounds[b].top + viewbounds[b].bottom)/2;
	
	viewbounds[b].right = cx + w;
	viewbounds[b].left = cx - w;
	viewbounds[b].top = cy + h;
	viewbounds[b].bottom = cy - h;

	resetGLWindowBounds();
}

void initGL()
{
	int PixelFormat = ChoosePixelFormat(hDC1, &pfd);		
	int PixelFormat2 = ChoosePixelFormat(hDC2, &pfd);		

	if (!PixelFormat || !PixelFormat2)
	{
		MessageBox(0,"Can't Find A Suitable PixelFormat.","Error",MB_OK|MB_ICONERROR);
		closeWindow();
	}

	if(!SetPixelFormat(hDC1,PixelFormat,&pfd) || !SetPixelFormat(hDC2,PixelFormat2,&pfd))
	{
		MessageBox(0,"Can't Set The PixelFormat.","Error",MB_OK|MB_ICONERROR);
		closeWindow();
	}

	hRC1 = wglCreateContext(hDC1);
	hRC2 = wglCreateContext(hDC2);
	
	if(!hRC1 || !hRC2)
	{
		MessageBox(0,"Can't Create A GL Rendering Context.","Error",MB_OK|MB_ICONERROR);
		closeWindow();
	}

	for (int i = 0; i < 2; i++)
	{
		viewbounds[i].right = 5;
		viewbounds[i].left = -5;
		viewbounds[i].top = 5;
		viewbounds[i].bottom = -5;
	}
	
	resetGLWindowBounds();

	for (int x = 0; x < 2; x++)
	{
		setActiveView(x);

		glClearColor(1,1,1,0);

		glClear(GL_COLOR_BUFFER_BIT);

	}
	
}

void drawGraphs()
{
	for (int x = 0; x < 2; x++)
	{
		setActiveView(x);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	if (mode == 0)
	{
		drawLists();
		drawAxis();
	}
	else
	{
		drawAxis();
		drawLists();
	}

	if (upoints != NULL) 
	{
		setActiveView(0);
		glLineWidth(2);
		upoints->draw(0);
		glLineWidth(1);
		setActiveView(1);
		glLineWidth(2);
		upoints->draw(1);
		glLineWidth(1);
	}
								
	Swap();	
}	

int CALLBACK DialogProc (HWND hwnd, UINT message,WPARAM wParam,LPARAM lParam)
{

	switch (message)
	{

		case WM_CLOSE:
    			
			closeWindow();
			PostQuitMessage(0);
			exit(0);
			break;

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:

			POINTS p = MAKEPOINTS(lParam);
			lastx = p.x + 3;
			lasty = p.y + 23;

			if (isInWindow(0,lastx,lasty)) currentwindow = 0;
			else if (isInWindow(1,lastx,lasty)) currentwindow = 1;
			else currentwindow = -1;

			drawGraphs();

			break;

		
		case WM_COMMAND:

			if (LOWORD(wParam) == ID_FILE_EXIT)
			{
				closeWindow();
			}

			if (LOWORD(wParam) == IDC_ERASE_USER)
			{
				clearUserPoints();
				drawGraphs();
			}

			if (LOWORD(wParam) == IDC_CALC)
			{
				clearUserPoints();

				char str[10000];
				char equ[10000];
				char error[10000];
				Edit_GetText(GetDlgItem(hwnd,IDC_EQUATION),str,10000);

				zifyequation(str);

				memcpy(equ,str,10000);
				cleanEquation(equ);

				if (equ[0] == 0) return 0;
				
				if (!checkParens(equ)) { sprintf(error,"(Invalid Parenthesis) %s",equ); Edit_SetText(GetDlgItem(hwnd,IDC_EQUATION),error); return 0; }
				if (!checkValidOps(equ)) { sprintf(error,"(Invalid Operations) %s",equ); Edit_SetText(GetDlgItem(hwnd,IDC_EQUATION),error); return 0; }
				if (!checkDecimalPoints(equ)) { sprintf(error,"(Invalid Decimals) %s",equ); Edit_SetText(GetDlgItem(hwnd,IDC_EQUATION),error); return 0; }
				if (!checkInvalidSymbols(equ)) { sprintf(error,"(Invalid Symbols) %s",equ); Edit_SetText(GetDlgItem(hwnd,IDC_EQUATION),error); return 0; }

				if (equation != NULL) { delete equation; equation = NULL; }
				if (complexequation != NULL) { delete complexequation; complexequation = NULL; }

				int len = 0; 
				while (equ[len] != 0) len++;
				infuseOrderOfOperations(equ,0,len);

				//Edit_SetText(GetDlgItem(hwnd,IDC_EQUATION),equ);

				complexequation = buildComplexTokenFromString(equ);
				
				Edit_GetText(GetDlgItem(hwnd,IDC_LINE_EDIT),str,10000);

				zifyequation(str);

				memcpy(equ,str,10000);
				cleanEquation(equ);

				if (equ[0] == 0)
				{
					makeBlanketLists();
					drawGraphs();
					return 0;
				}

				if (!checkParens(equ)) { sprintf(error,"(Invalid Parenthesis) %s",equ); Edit_SetText(GetDlgItem(hwnd,IDC_LINE_EDIT),error); return 0; }
				if (!checkValidOps(equ)) { sprintf(error,"(Invalid Operations) %s",equ); Edit_SetText(GetDlgItem(hwnd,IDC_LINE_EDIT),error); return 0; }
				if (!checkDecimalPoints(equ)) { sprintf(error,"(Invalid Decimals) %s",equ); Edit_SetText(GetDlgItem(hwnd,IDC_LINE_EDIT),error); return 0; }
				if (!checkInvalidSymbols(equ)) { sprintf(error,"(Invalid Symbols) %s",equ); Edit_SetText(GetDlgItem(hwnd,IDC_LINE_EDIT),error); return 0; }

				len = 0; 
				while (equ[len] != 0) len++;
				infuseOrderOfOperations(equ,0,len);

				equation = buildTokenFromString(equ);

				makeLineLists();
				drawGraphs();
			}

			if (LOWORD(wParam) == IDC_VIEW1ZOOMOUT) { zoomOut(0); }
			if (LOWORD(wParam) == IDC_VIEW1ZOOMIN) { zoomIn(0); }
			if (LOWORD(wParam) == IDC_VIEW1ZOOMRESET)
			{
				viewbounds[0].right = 5;
				viewbounds[0].left = -5;
				viewbounds[0].top = 5;
				viewbounds[0].bottom = -5;
				resetGLWindowBounds();
				
			}

			if (LOWORD(wParam) == IDC_VIEW2ZOOMOUT) { zoomOut(1); }
			if (LOWORD(wParam) == IDC_VIEW2ZOOMIN) { zoomIn(1); }
			if (LOWORD(wParam) == IDC_VIEW2ZOOMRESET)
			{
				viewbounds[1].right = 5;
				viewbounds[1].left = -5;
				viewbounds[1].top = 5;
				viewbounds[1].bottom = -5;
				resetGLWindowBounds();
			
			}
	
			break;


		case WM_MOUSEMOVE:

			{

			POINTS p = MAKEPOINTS(lParam);
			int curx = p.x + 3;
			int cury = p.y + 23;
				

			if (wParam & MK_RBUTTON)
			{
				
				if ( !(curx == lastx && cury == lasty) && currentwindow != -1)
				{
					moveBounds(currentwindow, lastx-curx, cury-lasty);
				}
	
			}
			else if (wParam & MK_LBUTTON)
			{
				if ( !(curx == lastx && cury == lasty) && currentwindow == 0 && complexequation != NULL)
				{
					addPoint(curx,cury,lastx,lasty);
					drawGraphs();
				}
			}

			lastx = curx;
			lasty = cury;

			}

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
	WndClass.lpszClassName = "Graphing Calculator";
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	
	if(!RegisterClass(&WndClass)) return 0;

	
	hMain = CreateDialog(hInstance,MAKEINTRESOURCE(IDD_MAIN),NULL,DialogProc);

	hDC1 = GetDC(GetDlgItem(hMain,IDC_VIEW1));
	hDC2 = GetDC(GetDlgItem(hMain,IDC_VIEW3));

	
	GetWindowRect(GetDlgItem(hMain,IDC_VIEW1),&win1);
	GetWindowRect(GetDlgItem(hMain,IDC_VIEW3),&win2);

	ww = win1.right-win1.left;
	wh = win1.bottom-win1.top;

	initGL();

	drawAxis();
	Swap();

	MSG Message;

	while(GetMessage(&Message, hMain, 0, 0))
	{	
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}


	return 0;

}






