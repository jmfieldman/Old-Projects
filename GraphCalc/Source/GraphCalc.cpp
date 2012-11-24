#include "equation.h"
#include "token.h"
#include "vector.h"

#include <windows.h>
#include <windowsx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include <stdlib.h>
#include <stdio.h>

#include "resource.h"

#define RES 75
int zoom = 5;
int dispzoom = 14;

static HGLRC hRC;		
static HDC hDC;

int lastx = -1;
int lasty = -1;

Token* equation;

float heights[RES][RES];
float normals[RES][RES][3];

int graphlist = 0;

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

void setNormals()
{
	float len = (float)zoom/(float)RES;

	normals[RES-1][RES-1][0] = 0; normals[RES-1][RES-1][1] = 0; normals[RES-1][RES-1][2] = 1;

	for (int x = 0; x < RES-1; x++)
	{
		for (int y = 0; y < RES-1; y++)
		{
			float v1[3] = { len, 0, heights[x+1][y]	- heights[x][y] };
			float v2[3] = { 0, len, heights[x][y+1]	- heights[x][y] };

			float norm[3];
			cross(v1,v2,norm);
			normalize(norm);

			normals[x][y][0] = norm[0];
			normals[x][y][1] = norm[1];
			normals[x][y][2] = norm[2];
		}

		
	}	

	for (int i = 0; i < RES-1; i++)
	{
		normals[i][RES-1][0] = normals[i][RES-2][0]; normals[i][RES-1][1] = normals[i][RES-2][1]; normals[i][RES-1][2] = normals[i][RES-2][2];
		normals[RES-1][i][0] = normals[RES-2][i][0]; normals[RES-1][i][1] = normals[RES-2][i][1]; normals[RES-1][i][2] = normals[RES-2][i][2];
	}
}

void drawGraph()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glDisable(GL_LIGHTING);
	
	glBegin(GL_LINES);
		glColor3f(0,1,0);
		glVertex3f( 0, 0, 0);
		glVertex3f( ((float)dispzoom/(float)2)+2, 0, 0);

		glColor3f(1,0,0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, ((float)dispzoom/(float)2)+2, 0);

		glColor3f(0,0,1);
		glVertex3f(0,0, 0);
		glVertex3f(0,0, ((float)dispzoom/(float)2)+2);

	glEnd();
	
	glEnable(GL_LIGHTING);

	float rat = (float)dispzoom / (float)RES;
	float orat = 2*((float)zoom / (float)dispzoom);
	
	float inf2 = 0;
	float inf = (float)1 / (float)inf2;
	float infn = (float)-1 / (float)inf2;

	float xc = ((-1* (RES/2)) * rat)+rat;
	for (int x = 0; x < RES-1; x++)
	{
		float yc = ((-1* (RES/2)) * rat)+rat;
		for (int y = 0; y < RES-1; y++)
		{
			if ( ((int)(xc*orat+10000) + (int)(yc*orat+10000)) % 2 == 0) glColor3f((float)0.9, (float)0.7, 0.5); else glColor3f(0.25,0.25,0.25);

			if ( heights[x][y] != inf && heights[x+1][y] != inf && heights[x+1][y+1] != inf && heights[x][y+1] != inf )
			{
			if ( heights[x][y] != infn && heights[x+1][y] != infn && heights[x+1][y+1] != infn && heights[x][y+1] != infn )
			{

			glBegin(GL_QUADS);
			glNormal3f(normals[x][y][0],normals[x][y][1],normals[x][y][2]);
			glVertex3f(xc,yc,heights[x][y]);
			
			glNormal3f(normals[x][y+1][0],normals[x][y+1][1],normals[x][y+1][2]);
			glVertex3f(xc,yc+rat,heights[x][y+1]);
			
			glNormal3f(normals[x+1][y+1][0],normals[x+1][y+1][1],normals[x+1][y+1][2]);
			glVertex3f(xc+rat,yc+rat,heights[x+1][y+1]);
			
			glNormal3f(normals[x+1][y][0],normals[x+1][y][1],normals[x+1][y][2]);
			glVertex3f(xc+rat,yc,heights[x+1][y]);
			glEnd();

			}
			}

			yc += rat;
		}
		xc += rat;
	}

}

void closeWindow()
{
	ChangeDisplaySettings(NULL, 0);

	wglMakeCurrent(hDC,NULL);
	wglDeleteContext(hRC);

}

void initGL()
{
	int PixelFormat = ChoosePixelFormat(hDC, &pfd);		


	if (!PixelFormat)
	{
		MessageBox(0,"Can't Find A Suitable PixelFormat.","Error",MB_OK|MB_ICONERROR);
		closeWindow();
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))
	{
		MessageBox(0,"Can't Set The PixelFormat.","Error",MB_OK|MB_ICONERROR);
		closeWindow();
	}

	hRC = wglCreateContext(hDC);
	if(!hRC)
	{
		MessageBox(0,"Can't Create A GL Rendering Context.","Error",MB_OK|MB_ICONERROR);
		closeWindow();
	}

	if(!wglMakeCurrent(hDC, hRC))
	{
		MessageBox(0,"Can't activate GLRC.","Error",MB_OK|MB_ICONERROR);
		closeWindow();
	}	

	glClearColor(1,1,1,0);

	glClear(GL_COLOR_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)640 / (float)480, 0.25, 30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	float pos[4] = { 0, 0,1 ,0};
	

	
	gluLookAt( 10, 10, 10,   0, 0, 0,   0, 0, 1);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);

	float ambient[4] = { (float)0.1, (float)0.1, (float)0.1, (float)0.1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	float diff[4] = {1,1,1,1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);

	float spec[4] = {1,1,1,1};
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);

}

int CALLBACK DialogProc (HWND hwnd, UINT message,WPARAM wParam,LPARAM lParam)
{

	switch (message)
	{

		case WM_CLOSE:
    
			if (equation != NULL) delete equation;
			closeWindow();
			PostQuitMessage(0);
			exit(0);
			break;

		
		case WM_COMMAND:
		
			if (LOWORD(wParam) == IDC_GRAPH)
			{
				char str[10000];
				char equ[10000];
				char error[10000];
				Edit_GetText(GetDlgItem(hwnd,IDC_EQUATION),str,10000);

				memcpy(equ,str,10000);
				cleanEquation(equ);
				
				if (!checkParens(equ)) { sprintf(error,"(Invalid Parenthesis) %s",str); Edit_SetText(GetDlgItem(hwnd,IDC_EQUATION),error); return 0; }
				if (!checkValidOps(equ)) { sprintf(error,"(Invalid Operations) %s",str); Edit_SetText(GetDlgItem(hwnd,IDC_EQUATION),error); return 0; }
				if (!checkDecimalPoints(equ)) { sprintf(error,"(Invalid Decimals) %s",str); Edit_SetText(GetDlgItem(hwnd,IDC_EQUATION),error); return 0; }
				if (!checkInvalidSymbols(equ)) { sprintf(error,"(Invalid Symbols) %s",str); Edit_SetText(GetDlgItem(hwnd,IDC_EQUATION),error); return 0; }

				if (equation != NULL) delete equation;

				int len = 0; 
				while (equ[len] != 0) len++;
				infuseOrderOfOperations(equ,0,len);

				equation = buildTokenFromString(equ);

				//Edit_SetText(GetDlgItem(hwnd,IDC_EQUATION),equ);

				for (int x = 0; x < RES; x++)
				{
					for (int y = 0; y < RES; y++)
					{
						float vx = (x - (RES/2)) * ((float)zoom/(float)RES);
						float vy = (y - (RES/2)) * ((float)zoom/(float)RES);
						heights[x][y] = (float)equation->evaluate(vx,vy);
					}
				}

				setNormals();

				glDeleteLists(graphlist,1);
				graphlist = glGenLists(1);
				glNewList(graphlist,GL_COMPILE_AND_EXECUTE);
					drawGraph();
				glEndList();

				SwapBuffers(hDC);
			}

			break;

		case WM_LBUTTONDOWN:

			POINTS p = MAKEPOINTS(lParam);
			lastx = p.x;
			lasty = p.y;

			break;

		case WM_MOUSEMOVE:

			if (wParam & MK_LBUTTON)
			{
				POINTS p = MAKEPOINTS(lParam);
				int curx = p.x;
				int cury = p.y;
				
				if (curx != lastx)
				{
					glRotatef((float)(curx - lastx)*(float)0.25, 0,0,1);
					glCallList(graphlist);
					SwapBuffers(hDC);
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

	
	HWND hwnd = CreateDialog(hInstance,MAKEINTRESOURCE(IDD_MAIN),NULL,DialogProc);

	hDC = GetDC(GetDlgItem(hwnd,IDC_VIEW2));

	initGL();

	SwapBuffers(hDC);

	MSG Message;

	while(GetMessage(&Message, hwnd, 0, 0))
	{	
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}


	return 0;

}


int main()
{

	char str[10000];

	printf("\n\n--------------------------\n\nEnter equation: ");

	char ch = 0;
	int pos = 0;

	while (ch = getchar())
	{
		if (ch == 10 || ch == 13) ch = 0;
		str[pos] = ch;
		if (ch == 0) break;
		pos++;
	}
	
	printf("\n");

	condenseFunctionNames(str);	
	printf("Condensing function names.. \"%s\"\n",str);
	
	killWhiteSpace(str);
	printf("Killing whitespace.. \"%s\"\n",str);

	expandConstants(str);
	printf("Expanding constants.. \"%s\"\n",str);
	
	fixDecimals(str);
	printf("Fixing Decimals.. \"%s\"\n",str);
	
	findNegates(str);
	printf("Finding negation functions.. \"%s\"\n",str);
	
	fixImplicitMultiplication(str);
	printf("Inserting implicit multiplication.. \"%s\"\n",str);

	
	printf("\n\nFinal: \"%s\"\n",str);
	
	printf("\n\nFunction validation:\n");

	int passed = 1;

	printf("Checking parenthesis... ");
	if (checkParens(str)) printf("passed\n"); else { printf("FAILED\n"); passed = 0; }
	
	printf("Checking for invalid operators... ");
	if (checkValidOps(str)) printf("passed\n"); else { printf("FAILED\n"); passed = 0; }
	
	printf("Checking for invalid decimals... ");
	if (checkDecimalPoints(str)) printf("passed\n"); else { printf("FAILED\n"); passed = 0; }
	
	printf("Checking for invalid symbols... ");
	if (checkInvalidSymbols(str)) printf("passed\n"); else { printf("FAILED\n"); passed = 0; }
	
	if (passed)
	{

		int length = 0;
		while (str[length] != 0) length++;
		infuseOrderOfOperations(str,0,length);

		printf("\n\nAfter OrOfOp: %s\n\n",str);

	}

	Token* token = buildTokenFromString(str);

	printf("\n\n--> %f\n",token->evaluate(1,1));

	delete token;

	printf("\n---------------------------------\n");

	return 0;
}