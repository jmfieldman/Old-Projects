/* 


  Jason Fieldman
  Albert Chu

  CS184 Final Project: GoGL


  */

#define INITGUID
#include "GoGL.h"
#include <windows.h>

int fullscreen = 1;
int width = 1280;
int height = 960;
extern float xscale = (float)80 / (float)width;
extern float yscale = (float)60 / (float)height;
int depth = 16;
int refresh = 60;
extern float ratio = (float)height / (float)width;

LARGE_INTEGER frametime;
LARGE_INTEGER framefreq;

extern int view2D = 0;

extern int currentboardwidth = 19;
extern int boardtrans = -10;
extern int tilt = 0;
extern int rot = 20;

extern int mousex = 0;
extern int mousey = 0;
extern int movingboard = 0;

extern float framerate = 30;
extern float timeperframe = 0.1;

extern int whoseturn = 0;
extern int lockmove = 0;

extern int points[2] = {0,0};

int displayFR = 1;
int movedeciding = 0;

extern GoBoard* board = NULL;
extern EffectList* effectlist = NULL;

extern int redpiece = 0;

char textbuffer[1000];

float frtl = 0;
float frad = 0;

int menuang = 90;
int submenuang = 0;

int angdir = 0;

int menusel = 0;

extern int passed = 0;
extern int winner = 0;

void dealWithMenu(float x, float y)
{
	if ((x < 10 && y > 55) && submenuang < 90) angdir = -5;
	if ((x > 17 || y < 47) && submenuang > 0) angdir = 5;

	menuang += angdir;
	submenuang -= angdir;

	if (menuang == 0 || submenuang == 0) angdir = 0;

	if (menuang) 
	{			
		textout("Menu",1,60-(2*sinT(menuang)) );		
	}

	if (submenuang)
	{
		float disp = 10*sinT(submenuang);

		glColor3f(1,1,1); if (x > 1 && x < 17 && y > 57.9 && y < 59.1) { glColor3f(1,1,0); menusel = 1; }
		textout("Start New Game: 19x19",1,68-disp);
		glColor3f(1,1,1); if (x > 1 && x < 17 && y > 56.6 && y < 57.8) { glColor3f(1,1,0); menusel = 2; }
		textout("Start New Game: 13x13",1,66.7-disp);
		glColor3f(1,1,1); if (x > 1 && x < 17 && y > 55.3 && y < 56.5) { glColor3f(1,1,0); menusel = 3; }
		textout("Start New Game: 9x9",1,65.4-disp);
		glColor3f(1,1,1); if (x > 1 && x < 15 && y > 52.9 && y < 54.1) { glColor3f(1,1,0); menusel = 4; }
		textout("Toggle Framerate",1,63-disp);
		glColor3f(1,1,1); if (x > 1 && x < 8 && y > 49.1 && y < 51.1) { glColor3f(1,1,0); menusel = 5; }
		textout("Quit",1,60-disp);				
	}


	
		
}

void initGame()
{
	whoseturn = 0;
	points[0] = 0;
	points[1] = 0;
	winner = 0;
	passed = 0;
	kos = 0;
	delete effectlist;
	effectlist = new EffectList();
}

void displayMain(void)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if (view2D) push2DView();

	board->renderBoard();

	//begin interface
	pushInterfaceMatrix();

		//framerate
		LARGE_INTEGER newtime;
		QueryPerformanceCounter(&newtime);
		framerate = (float)framefreq.QuadPart/(float)(newtime.QuadPart-frametime.QuadPart);
		timeperframe = (float)1 / framerate;
		frtl -= timeperframe;

		if (displayFR)
		{
			if (frtl < 0)
			{
				frtl = 1;
				frad = framerate;
			}

			glColor3f(1,1,1);
			char frstr[1000];
			frstr[0] = 0;
			sprintf(frstr,"Framerate: %5.2f",frad);
			textout(frstr,34,3);			
		}
		frametime = newtime;
		//end framerate

		float mx,my;
		translateToXY(mousex,mousey,mx,my);
		
		glColor3f(1,1,1);
		dealWithMenu(mx,my);

		//scores
		glColor3f(1,1,1);
		if (whoseturn == 1) glColor3f(1,1,0);
		sprintf(textbuffer,"White: %d",points[1]);
		textout(textbuffer,70,3);
				
		glColor3f(1,1,1);
		if (whoseturn == 0) glColor3f(1,1,0);
		sprintf(textbuffer,"Black: %d",points[0]);
		textout(textbuffer,3,3);
		
		//end scores

		//pass
		
		if (mx > 70 && my > 55)
		{
			glDisable(GL_LIGHTING);
			glColor3f(0.2,0.2,0.2);
			glBegin(GL_QUADS);
				glVertex2f(70,60);
				glVertex2f(70,55);
				glVertex2f(80,55);				
				glVertex2f(80,60);				
			glEnd();			
		}

		glColor3f(1,1,1);
		if (!passed) textout("Pass",73.5,57); else textout("End Game",72,57);

		//end pass

		//winner
		if (winner)
		{
			glPushMatrix();
			if (winner == 1)
			{				
				glColor4f(0.6,0.6,0.6,0.5);
				glScalef(10,10,0);
				textout("Black Wins!",0.75,2.5);
			}
			else if (winner == 2)
			{				
				glColor4f(1.0,1.0,1.0,0.5);
				glScalef(10,10,0);
				textout("White Wins!",0.75,2.5);
			}
			else
			{
				glColor4f(0.0,1.0,1.0,0.5);
				glScalef(10,10,0);
				textout("Tie Game!",1.25,2.5);
			}

			glPopMatrix();
		}
		//endwinner

		//mouse
		glPushMatrix();
		glTranslatef(mx,my,0);
		printMouse();
		glPopMatrix();
		//end mouse

	popInterfaceMatrix();
	//end interface
	if (view2D) pop2DView();

	glutSwapBuffers();	
	
}

void idle(void)
{
	glutPostRedisplay();
}

void reshape(int x, int y)
{
	glViewport(0,0,x,y);	
	glutPostRedisplay();

	width = x;
	height = y;

	xscale = (float)80 / (float)width;
	yscale = (float)60 / (float)height;
	ratio = (float)height / (float)width;
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) 
	{		
		//allegro_exit();
		delete board;
		exit(0);
	}
	if (key == ' ') view2D = !view2D;
	if (key == 'f') displayFR = !displayFR;
	//if (key == '1') exampleLayout1();
	//if (key == '2') exampleLayout2();

	if (key == 'p' && !winner) 
	{
		if (passed) 
		{
			board->determineWinner();
			return;
		}
		whoseturn++;
		if (whoseturn == 2) whoseturn = 0;
		passed = 1;
	}
}

void passiveMouseMotion(int x, int y)
{
	mousex = x;
	mousey = height - y;

	menusel = 0;
}

void activeMouseMotion(int x, int y)
{
	y = height - y;

	if (movingboard)
	{
		if (x != mousex)
		{
			if (y < (height/2))
				rot += (float)(x - mousex)*(float)0.33;					
			else
				rot -= (float)(x - mousex)*(float)0.33;					
		}
		if (y != mousey)
		{
			tilt -= (float)(y - mousey)*(float)0.33;
			if (tilt > 52) tilt = 52;
			if (tilt < -12) tilt = -12;			
		}
	}

	mousex = x;
	mousey = y;
}

void mouseAction(int button, int state, int x, int y)
{
	
	if (button == GLUT_RIGHT_BUTTON)
	{
		movingboard = (state == GLUT_DOWN);
	}



	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !lockmove)
	{
		if (submenuang == 0)
		{
			if (posofcursor != -1 && !winner)
			{
				movedeciding = 1;
			}
			float mx,my;
			translateToXY(mousex,mousey,mx,my);
			if (mx > 70 && my > 55 && !winner)
			{
				if (passed) 
				{
					sound_endgame();
					board->determineWinner();
					return;
				}
				whoseturn++;
				if (whoseturn == 2) whoseturn = 0;
				passed = 1;
			}
		}
		else
		{
			switch (menusel) 
			{	
			case 1:  
					delete board;
					board = new GoBoard(19);
					initGame();
					break;
			case 2:  
					delete board;
					board = new GoBoard(13);					
					initGame();
					break;
			case 3:  
					delete board;
					board = new GoBoard(9);
					initGame();
					break;
			case 4: 
					displayFR = !displayFR;
					break;
			case 5:
					delete board;
					closeSound();
					exit(0);

			}
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && movedeciding)
	{
		if (posofcursor != -1)
		{
			if (board->placepiece())
			{
				Capture* cap = new Capture(posofcursor);
				effectlist->addEffect(cap);
			}			
		}

	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		if (posofcursor != -1)
		{
			int x = posofcursor % currentboardwidth;
			int y = posofcursor / currentboardwidth;

			Explosion* expl;
			
			int col = board->getPiece(posofcursor);

			if (col == BLACK_PIECE)
				expl = new Explosion(0.2,0.2,0.2,1, x,y,1, 300,20,-0.002,0.08);
			else if (col == WHITE_PIECE)
				expl = new Explosion(1,1,1,1, x,y,1, 300,20,-0.002,0.08);
			else return;

			effectlist->addEffect(expl);
			
			board->clearSpace(posofcursor);
		}
	}

	if (state == GLUT_UP)
	{
		movedeciding = 0;
	}

	mousex = x;
	mousey = height - y;
}

void readConfigFile()
{
	FILE* file = fopen(CONFIG_FILENAME,"rb");
	if (file == NULL) return;
	
	fscanf(file,"FULLSCREEN=%d\r\n",&fullscreen);
	fscanf(file,"WIDTH=%d\r\n",&width);
	fscanf(file,"HEIGHT=%d\r\n",&height);
	fscanf(file,"DEPTH=%d\r\n",&depth);
	fscanf(file,"REFRESH=%d\r\n",&refresh);

	xscale = (float)80 / (float)width;
	yscale = (float)60 / (float)height;
	ratio = (float)height / (float)width;

	fclose(file);
}

void initGameWindow()
{
	if (fullscreen)
	{
		char gamemode[30];
		sprintf(gamemode, "%dx%d:%d@%d", width, height, depth, refresh);
		glutGameModeString(gamemode);
		glutEnterGameMode();
	}
	else
	{
		glutInitWindowSize(width,height);
		glutInitWindowPosition(0,0);
		glutCreateWindow("GoGL");
	}
}

void glInit()
{
	glLineWidth(2);
		
	glClearColor(0,0,0,0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glDisable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);

	float ambient[4] = { 0.1, 0.1, 0.1, 0.1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	
	float diff[4] = {1,1,1,1};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	
	float spec[4] = {1,1,1,1};	
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
	
	
	float shin[4] = {100};
	//glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	//glMaterialfv(GL_FRONT, GL_SHININESS, shin);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective(60, (float)width / (float)height, 1, 80);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt( -15, -15, 15,   0, 0, 0,   0, 0, 1);

	//float pos[4] = { -0.5,-0.25,1,0 };
	float pos[4] = { 15,15,2,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	
}

int main(int argc, char ** argv)
//int WINAPI WinMain ( HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	readConfigFile();
	initGameWindow();
	initTrigTables();

	glInit();
	initFontSystem();	
	initClusters();
	initSound();

	QueryPerformanceFrequency(&framefreq);

	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseAction);
	glutMotionFunc(activeMouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);
	glutReshapeFunc(reshape);
	glutDisplayFunc(displayMain);
	glutIdleFunc(idle);
	glutSetCursor(GLUT_CURSOR_NONE);

	board = new GoBoard(19);
	//temp->setBoardToGO();

	effectlist = new EffectList();
	

	QueryPerformanceCounter(&frametime);
	
	glutMainLoop();

	closeSound();
	return 0;
}
//END_OF_MAIN() 

void translateToXY(int x, int y, float & newx, float & newy)
{
	newx = (float)x * xscale;
	newy = (float)y * yscale;
}

