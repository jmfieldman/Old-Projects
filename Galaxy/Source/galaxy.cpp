#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gl/glut.h>
#include <math.h>
#include <windows.h>

#define NUM_STARS 100000
int curstars = 5500;

LARGE_INTEGER mstime;

float cord[NUM_STARS][3];
float starsize[NUM_STARS];

int fullscreen = 1;

int width = 1024;
int height = 728;

int crappycolor = 0;

int mousex;
int mousey;
int movingboard;

int speed = 10;

float rot = 0;
float tilt = 0;

#define mypi ((float)3.1415926535)

float getnormrand()
{
	return (float)(rand() % 10000) / (float)10000;
}

float getheightfromrad(float radius)
{
	float norm = 0.75;
	float max;

	if (radius > mypi)
	{
		max = norm;
	}
	else
	{
		max = cos(radius)*0.5 + 1.25 + norm;
	}

	float sqnorm = getnormrand();
	sqnorm *= sqnorm * sqnorm;
	float ret = sqnorm * max;
	if (rand() % 2 == 0) ret = ret * -1;
	return ret;
}

void initstars()
{
	for (int s = 0; s < NUM_STARS; s++)
	{

		float normal_radius = getnormrand();
		normal_radius *= normal_radius;
		float radius = normal_radius * 12;

		if (radius < 0.5) radius = getnormrand();

		if (radius < 1) radius += (getnormrand() - 0.5) * 2;

		if (radius > 7) radius += (getnormrand() - 0.5) * 6;

		//if (rand() % 100 == 0) radius = getnormrand() * 15;

		float angle = (float)(getnormrand() * 360) * (((float)3.14159265) / 180);

		cord[s][0] = radius * cos(angle);
		cord[s][1] = radius * sin(angle);
		
		cord[s][2] = getheightfromrad(radius);

		if (radius < 0.25 && cord[s][2] > 1)
		{
			radius = getnormrand();
			cord[s][2] = getheightfromrad(radius);
		}

		starsize[s] = getnormrand() + 0.5;
		if (rand() % 100 == 0) 
			starsize[s] = getnormrand() + 2;
	}
}

void drawstars()
{	
	float offs = 0.4;

	for (int s = 0; s < curstars; s++)
	{
		glPointSize(starsize[s]);
		glBegin(GL_POINTS);		
		glColor4f(1,1,1,1);
		glVertex3f(cord[s][0],cord[s][1],cord[s][2]);		
		glEnd();
	
		
		if (crappycolor)
		{
			glBegin(GL_QUADS);
			glColor4f(0.2,0,1,0.05);		
			glVertex3f(cord[s][0]+offs,cord[s][1]+offs,cord[s][2]);
			glVertex3f(cord[s][0]+offs,cord[s][1]-offs,cord[s][2]);
			glVertex3f(cord[s][0]-offs,cord[s][1]-offs,cord[s][2]);
			glVertex3f(cord[s][0]-offs,cord[s][1]+offs,cord[s][2]);
			glEnd();
		}
		
	}
		
}

void displayMain(void)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();

	
	glRotatef(tilt,1,-1,0);
	glRotatef(rot,0,0,1);
	

	drawstars();


	glPopMatrix();

	glutSwapBuffers();	
}


void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) 
	{		
		exit(0);
	}

	if (key == 'a')
	{
		curstars += 100;
		if (curstars > NUM_STARS) curstars = NUM_STARS;
	}

	if (key == 'z')
	{
		curstars -= 100;
		if (curstars < 0) curstars = 0;
	}

	if (key == 'l') { rot += 2; };
	if (key == 'k') { rot -= 2; };

	if (key == 's' && speed < 100) speed++;
	if (key == 'x' && speed > 0) speed--;

	if (key == 'c') crappycolor = !crappycolor;

	printf("Stars: %d\n",curstars);
}

void idle(void)
{
	LARGE_INTEGER newt;
	QueryPerformanceCounter(&newt);

	rot += ((newt.QuadPart - mstime.QuadPart)/10000000.0)*speed;

	mstime.QuadPart = newt.QuadPart;
	glutPostRedisplay();
}

void passiveMouseMotion(int x, int y)
{
	mousex = x;
	mousey = height - y;
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
			if (tilt < -33) tilt = -33;			
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

	mousex = x;
	mousey = height - y;
}

int main(int argc, char** argv)
{
	srand(time(0));

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	if (fullscreen)
	{
		glutGameModeString("1024x768:32@75");
		glutEnterGameMode();
	}
	else
	{
		glutInitWindowSize(width,height);
		glutInitWindowPosition(0,0);
		glutCreateWindow("GoGL");
	}

	initstars();

	glClearColor(0,0,0,0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glDisable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	glDepthFunc(GL_LEQUAL);
	glDisable(GL_DEPTH_TEST);
	
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	gluPerspective(60, (float)width / (float)height, 1, 80);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt( -15, -15, 14,   0, 0, -1,   0, 0, 1);


	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(displayMain);
	glutMouseFunc(mouseAction);
	glutMotionFunc(activeMouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);

	QueryPerformanceCounter(&mstime);

	glutMainLoop();

	return 0;
}