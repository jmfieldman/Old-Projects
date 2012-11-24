/* 


  Jason Fieldman
  Albert Chu

  CS184 Final Project: GoGL

  

  */


#include <math.h>
#include "GoGL.h"


float sintable[360];
float costable[360];


float sinT(int a)
{
	return sintable[a];
}	

float cosT(int a)
{
	return costable[a];
}	

void initTrigTables()
{
	for (int x = 0; x < 360; x++)
	{
		sintable[x] = (float)sin( x * (3.14159265 / 180) );
		costable[x] = (float)cos( x * (3.14159265 / 180) );
	}
}



void normalize(float * v)
{
	float length = (float)sqrt( (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]) );
	
	v[0] = v[0] / length;
	v[1] = v[1] / length;
	v[2] = v[2] / length;
}

float dot(float * v1, float * v2)
{
	float ret = 0;
	for (int x = 0; x < 3; x++) ret += (v1[x] * v2[x]);
	return ret;
}

void cross(float * v1, float * v2, float * d)
{
	d[0] = ( v1[1] * v2[2] ) - (v1[2] * v2[1] );
	d[1] = ( v1[2] * v2[0] ) - (v1[0] * v2[2] );
	d[2] = ( v1[0] * v2[1] ) - (v1[1] * v2[0] );
}


void glFlatQuad(float * p1, float * p2, float * p3, float * p4)
{
	float v1[3] = { p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2] };
	float v2[3] = { p3[0] - p2[0], p3[1] - p2[1], p3[2] - p2[2] };
	float d[3];
	cross(v1,v2,d);
	normalize(d);

	glBegin(GL_QUADS);

		glNormal3fv(d);
		glVertex3fv(p1);
		glVertex3fv(p2);
		glVertex3fv(p3);
		glVertex3fv(p4);
		
	glEnd();
}

void pushInterfaceMatrix()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,80,0,60,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void popInterfaceMatrix()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();	
}

void push2DView()
{
	float buffer = currentboardwidth * 0.2;
	float bufferw = ((( buffer + buffer + currentboardwidth ) / ratio) - currentboardwidth) / 2;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-bufferw,currentboardwidth+bufferw,-buffer,currentboardwidth+buffer,-50,50);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void pop2DView()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

int getPosOfXY(int x, int y)
{
	double modelview[16];
	double projection[16];
	int viewport[4];

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	double x1,x2,y1,y2,z1,z2;
	double dx, dy, dz, t, rx, ry;

	gluUnProject(x,y,1, modelview,projection,viewport, &x1, &y1, &z1);
	gluUnProject(x,y,0, modelview,projection,viewport, &x2, &y2, &z2);

	dx = x1 - x2;
	dy = y1 - y2;
	dz = z1 - z2;

	//plane:   z = 1.2
	//z1 + dz(t) = 1.2
	//t = (1.2 - z1) / dz

	t = (0 - z1) / dz;

	rx = x1 + (dx * t);
	ry = y1 + (dy * t);

	int ix;
	int iy;

	if (view2D)
	{
		ix = (int)(rx+0.5);
		iy = (int)(ry+0.5);
	}
	else
	{
		ix = (int)(rx+0.5);
		iy = (int)(ry+0.5);
	}

	if (ix >= 0 && ix < currentboardwidth && iy >= 0 && iy < currentboardwidth) return (ix + (iy * currentboardwidth));
	else return -1;
	
}