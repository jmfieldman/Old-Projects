#include "board.h"

#include <windows.h>
#include <windowsx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include <stdlib.h>
#include <stdio.h>

#include "resource.h"

#include "socket.h"

#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else /* UNIX */
#define PATH_SEPARATOR ':'
#endif

static HGLRC hRC;		
extern HDC hDC = NULL;

extern int lightang = 0;
extern int scores[2] = { 0, 0 };

extern int maxscore = 150;

float tilt = 20;
float rot = 0;

int lastx = 0;
int lasty = 0;

HWND hMain;

char textbuf[32000];

int serverrunning = 0;
int client = 0;

extern int player = 0;

int curx,cury;

int turn = -1;

extern int lastxpos = 0;
extern int lastypos = 0;

POINTS p;

extern int makemove = 0;

extern int blinkang = 0;

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

void addText(char* str)
{
	int pos = 0;
	while (textbuf[pos] != 0) pos++;
	if (pos > 10000) 
		sprintf(textbuf,"%s%s",textbuf+1000,str);
	else
		sprintf(textbuf,"%s%s",textbuf,str);
	Edit_SetText(GetDlgItem(hMain,IDC_TEXT),textbuf);
	Edit_Scroll(GetDlgItem(hMain,IDC_TEXT),SB_PAGEDOWN,0);
	for (int x = 0; x < 10; x++)
	{
		Edit_Scroll(GetDlgItem(hMain,IDC_TEXT),SB_LINEUP,0);
	}

}

void setEditText(char* str)
{
	Edit_SetText(GetDlgItem(hMain,IDC_TEXT),str);
	UpdateWindow(hMain);
}

void CleanUpAndExit()
{
	unGenLists();
	closeSockets();
	exit(0);
}

void handlePlayerMove(int pos)
{
	if (pos == -1 || board[pos] != 0 || turn != player) return;
	board[pos] = player+1;

	latchNewPiece(player,pos%BOARDSIZE,pos/BOARDSIZE);
	lastxpos = pos%BOARDSIZE;
	lastypos = pos/BOARDSIZE;
	char packet[PACKETSIZE];
	sprintf(packet,"MOVE%c",pos);
	sendData(packet);
	if (player == 0) turn = 1; else turn = 0;
	updateTurn();
}

void initGL()
{
	addText("Initializing openGL... ");

	int PixelFormat = ChoosePixelFormat(hDC, &pfd);		


	if (!PixelFormat)
	{
		MessageBox(0,"Can't Find A Suitable PixelFormat.","Error",MB_OK|MB_ICONERROR);
		CleanUpAndExit();
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))
	{
		MessageBox(0,"Can't Set The PixelFormat.","Error",MB_OK|MB_ICONERROR);
		CleanUpAndExit();
	}

	hRC = wglCreateContext(hDC);
	if(!hRC)
	{
		MessageBox(0,"Can't Create A GL Rendering Context.","Error",MB_OK|MB_ICONERROR);
		CleanUpAndExit();
	}

	if(!wglMakeCurrent(hDC, hRC))
	{
		MessageBox(0,"Can't activate GLRC.","Error",MB_OK|MB_ICONERROR);
		CleanUpAndExit();
	}	

	addText("done\n");

	glClearColor(0,0,0,0);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)552/ (float)506, 0.25, 30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	

	gluLookAt(-6,-6,6,0,0,0,0,0,1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);

	genLists();

	
	renderBoard(tilt,rot);

}

void updateTurn()
{
	char move1[20] = {0};
	char move2[20] = {0};

	if (turn == 0) sprintf(move1,"-->"); else sprintf(move2,"-->");

	Static_SetText(GetDlgItem(hMain,IDC_MOVE1),move1);
	Static_SetText(GetDlgItem(hMain,IDC_MOVE2),move2);

	sprintf(move1,"%d",scores[0]);
	sprintf(move2,"%d",scores[1]);

	Static_SetText(GetDlgItem(hMain,IDC_SCORE1),move1);
	Static_SetText(GetDlgItem(hMain,IDC_SCORE2),move2);

	if (scores[0] >= maxscore || scores[1] >= maxscore)
	{
		turn = -1;
		char name[50],output[1000];
		if (scores[0] >= maxscore)
			Static_GetText(GetDlgItem(hMain,IDC_NAME1),name,50);
		else
			Static_GetText(GetDlgItem(hMain,IDC_NAME2),name,50);
		if (scores[0] >= maxscore)
			sprintf(output,"%s wins with %d points.  Press the Connect button to play again.\n",name,scores[0]);
		else
			sprintf(output,"%s wins with %d points.  Press the Connect button to play again.\n",name,scores[1]);
		addText(output);
	}	
}

int shouldDrawSelection(int & x, int & y)
{
	x = curx;
	y = cury;
	convertXY(x,y);
	if (turn != player) return 0;	
	return 1;
}

int label(char* str, char* lab)
{
	for (int x = 0; x < 4; x++)
	{
		if (str[x] != lab[x]) return 0;
	}
	return 1;
}

void sendChat(char* text)
{
	char name[50];
	char addtext[PACKETSIZE+200];
	
	if (player == 0) 
		Static_GetText(GetDlgItem(hMain,IDC_NAME1),name,50);
	else
		Static_GetText(GetDlgItem(hMain,IDC_NAME2),name,50);

	sprintf(addtext,"<%s> %s\n",name,text);

	addText(addtext);
	
	sprintf(addtext,"CHAT%s",text);
	sprintf(text,"%s",addtext);
	sendData(text);
}

void handlePacket(char* packet)
{
	if (label(packet,"NAME"))
	{
		char name[50];
		int pos = 4;
		while (packet[pos-1] != 0)
		{
			name[pos-4] = packet[pos];
			pos++;
		}
		if (player == 0) 
			Static_SetText(GetDlgItem(hMain,IDC_NAME2),name);
		else
			Static_SetText(GetDlgItem(hMain,IDC_NAME1),name);
	}
	else if (label(packet,"CHAT"))
	{
		char name[50];
		char addtext[PACKETSIZE+200];
		if (player == 1) 
			Static_GetText(GetDlgItem(hMain,IDC_NAME1),name,50);
		else
			Static_GetText(GetDlgItem(hMain,IDC_NAME2),name,50);

		sprintf(addtext,"<%s> %s\n",name,packet+4);

		addText(addtext);
	}
	else if (label(packet,"MOVE"))
	{
		int pos = packet[4];
		int piece = 1;
		if (player == 0) piece = 2;

		board[pos] = piece;
		lastxpos = pos%BOARDSIZE;
		lastypos = pos/BOARDSIZE;
		latchNewPiece(piece-1,pos%BOARDSIZE,pos/BOARDSIZE);
		if (turn == 0) turn = 1; else turn = 0;
		updateTurn();
	}
	else if (label(packet,"DISC"))
	{
		addText("Opponent has disconnected.\n");
		turn = -1;
	}
	else if (label(packet,"NEWG"))
	{
		clearGameInfo();
		turn = player;

		updateTurn();
	}
}

void beginConnection()
{
	char name[50];
	Edit_GetText(GetDlgItem(hMain,IDC_NAMEEDIT),name,50);
	name[15] = 0;

	if (player == 0) 
		Static_SetText(GetDlgItem(hMain,IDC_NAME1),name);
	else
		Static_SetText(GetDlgItem(hMain,IDC_NAME2),name);

	char packet[PACKETSIZE];
	sprintf(packet,"NAME%s",name);
	sendData(packet);

	client = 1;
	turn = 0;

	char playingto[1000];
	sprintf(playingto,"Playing to %d points.\n",maxscore);
	addText(playingto);

}

void initiateNewGame()
{
	clearGameInfo();
	if (player == 0) turn = 1; else turn = 0;

	char pack[PACKETSIZE];
	pack[0] = 'N'; pack[1] = 'E'; pack[2] = 'W'; pack[3] = 'G'; 
	sendData(pack);

	updateTurn();
}

int CALLBACK DialogProc (HWND hwnd, UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{

		case WM_CLOSE:
			CleanUpAndExit();
			break;

		case WM_COMMAND:

			if (LOWORD(wParam) == IDC_SERVEBUTTON && client == 0)
			{
				char name[50];
				name[0] = 0;
				Edit_GetText(GetDlgItem(hMain,IDC_NAMEEDIT),name,50);
				if (name[0] == 0) 
				{
					MessageBox(0,"Enter Name","Error",MB_OK);
					return 0;
				}

				player = 0;
				startServer();
				Sleep(750);
				clientConnect("127.0.0.1");
				beginConnection();
			}

			if (LOWORD(wParam) == IDC_CONNECT && turn == -1 && client == 1)
			{
				initiateNewGame();
				return 0;
			}

			if (LOWORD(wParam) == IDC_CONNECT && client == 0)
			{
				char name[50];
				name[0] = 0;
				Edit_GetText(GetDlgItem(hMain,IDC_NAMEEDIT),name,50);
				if (name[0] == 0) 
				{
					MessageBox(0,"Enter Name","Error",MB_OK);
					return 0;
				}
				
				char addr[20];
				addr[0] = 0;
				Edit_GetText(GetDlgItem(hMain,IDC_IPEDIT),addr,20);
				if (addr[0] == 0) 
				{
					MessageBox(0,"Enter IP","Error",MB_OK);
					return 0;
				}

				player = 1;
				clientConnect(addr);
				beginConnection();
			}

			break;

		case WM_KEYDOWN:

			//if (LOWORD(wParam) == IDC_CHATEDIT)
			//{
				addText("oo");
			//}/

			break;

		
		case WM_RBUTTONUP:
		case WM_RBUTTONDOWN:

			POINTS p = MAKEPOINTS(lParam);
			lastx = p.x;
			lasty = p.y;
			

			break;

		case WM_LBUTTONUP:

			makemove = 1;

			break;

		case WM_MOUSEMOVE:

			p = MAKEPOINTS(lParam);
			curx = p.x;
			cury = p.y;

			if ((wParam & MK_RBUTTON))// && (LOWORD(wParam) == IDC_VIEW) )
			{
				
				if (curx != lastx)
				{
					if (cury < ( (BOTY-TOPY)/2 ))
						rot -= (float)(curx - lastx)*(float)0.33;					
					else
						rot += (float)(curx - lastx)*(float)0.33;					
				}
				if (cury != lasty)
				{
					tilt += (float)(cury - lasty)*(float)0.33;
					if (tilt > 52) tilt = 52;
					if (tilt < -12) tilt = -12;
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
	textbuf[0] = 0;

	LoadLibrary("RichEd32.dll");

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

	initGL();

	initSockets();	

	MSG Message;

	long pulse = 0;

	while(1)
	{	
		pulse++;
		if (PeekMessage(&Message, hMain, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);

			if (Message.message == WM_KEYDOWN && Message.wParam == VK_RETURN && client == 1)
			{
				char text[PACKETSIZE+5];
				Edit_GetText(GetDlgItem(hMain,IDC_CHATEDIT),text,PACKETSIZE);
				Edit_SetText(GetDlgItem(hMain,IDC_CHATEDIT),"");
				if (text[0] != 0) sendChat(text);
			}
		}

		if (pulse % 10 == 0) {lightang++; }
		if (lightang >= 360) lightang = 0;

		blinkang += 5;
		if (blinkang >= 360) blinkang = 0;

		Sleep(10);
		renderBoard(tilt,rot);
	}


	return 0;

}
