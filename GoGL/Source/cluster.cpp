
/* 


  Jason Fieldman
  Albert Chu

  CS184 Final Project: GoGL


  */


#include "GoGL.h"

extern int sparkleList = 0;

void drawPyramid(float b, float h)
{
	glBegin(GL_TRIANGLES);
	
	//near
	glNormal3f(b/2,0,h);
	glVertex3f(0,b/2,b/2); glVertex3f(0,b/(-2),b/2); glVertex3f(h,0,0);

	//far
	glNormal3f(b/2,0,-1 * h);
	glVertex3f(0,b/(-2),b/(-2)); glVertex3f(0,b/2,b/(-2)); glVertex3f(h,0,0);

	//top
	glNormal3f(b/2,h,0);
	glVertex3f(0,b/2,b/(-2)); glVertex3f(0,b/2,b/2); glVertex3f(h,0,0);

	//bottom
	glNormal3f(b/2,-1 * h,0);
	glVertex3f(0,b/(-2),b/2); glVertex3f(0,b/(-2),b/(-2)); glVertex3f(h,0,0);

	glEnd();
}

void drawSparkle()
{
	glPushMatrix();
	
	drawPyramid(1,3);	
	glRotatef(90,0,1,0);
	drawPyramid(1,3);	
	glRotatef(90,0,1,0);
	drawPyramid(1,3);	
	glRotatef(90,0,1,0);
	drawPyramid(1,3);	
	glRotatef(90,0,1,0);
	glRotatef(90,0,0,1);
	drawPyramid(1,3);	
	glRotatef(180,0,0,1);
	drawPyramid(1,3);
	
	glPopMatrix();
	
}	

int Cluster::type()
{
	return TYPE_CLUSTER;
}

void drawCluster(sparkleCluster * cluster)
{
	float scale;

	glDisable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glPushMatrix();
	glColor4f(cluster->color[0], cluster->color[1], cluster->color[2], cluster->color[3]);
	glTranslatef(cluster->position[0], cluster->position[1], cluster->position[2]);

	for (int x = 0; x < sparklePerCluster; x++)
	{
		if (cluster->sparkleData[x][3] > 0)
		{
			glPushMatrix();

			glTranslatef(cluster->sparkleData[x][0],cluster->sparkleData[x][1],cluster->sparkleData[x][2]);

			scale = cluster->sparkleData[x][3];
			glScalef(scale,scale,scale);

			glCallList(sparkleList);

			glPopMatrix();
		}
	}

	glPopMatrix();
	glDisable(GL_NORMALIZE);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}




Cluster::Cluster(float r, float g, float b, float a, 
				 float x, float y, float z, 
				 float bx, float by, float bz, 
				 int number, int delay, float sclspd, float maxscl) : Effect()
{

	sparkle.color[0] = r;
	sparkle.color[1] = g;
	sparkle.color[2] = b;
	sparkle.color[3] = a;

	sparkle.position[0] = x;
	sparkle.position[1] = y;
	sparkle.position[2] = z;

	sparkle.breadth[0] = bx;
	sparkle.breadth[1] = by;
	sparkle.breadth[2] = bz;

	sparkle.numberLeft = number;
	sparkle.delay = delay;
	sparkle.sclspd = sclspd;
	sparkle.maxscl = maxscl;

	for (int pos = 0; pos < sparklePerCluster; pos++)
	{
		sparkle.sparkleData[pos][3] = 0;
	}
}

Cluster::~Cluster()
{

}


int Cluster::pulse()
{
	//if (kos == 0) return 0;

	sparkleCluster* cluster = &sparkle;

	int x;
	for (x = 0; x < sparklePerCluster; x++)
	{
		cluster->sparkleData[x][3] += cluster->sparkleData[x][4];
		if (cluster->sparkleData[x][4] > 0 && cluster->sparkleData[x][3] > cluster->sparkleData[x][5]) cluster->sparkleData[x][4] *= -1;
		if (cluster->sparkleData[x][3] < 0) cluster->sparkleData[x][3] = 0;
	}
	if (cluster->numberLeft) cluster->delayLeft--;
	if (cluster->delayLeft < 0)
	{
		cluster->numberLeft--;
		cluster->delayLeft = cluster->delay;

		int found = 0;
		int pos = 0;
		while (!found)
		{
			if (cluster->sparkleData[pos][3] == 0)
			{
				cluster->sparkleData[pos][0] = cluster->breadth[0] * ((float)(rand() % 100) / (float)100);
				cluster->sparkleData[pos][1] = cluster->breadth[1] * ((float)(rand() % 100) / (float)100);
				cluster->sparkleData[pos][2] = cluster->breadth[2] * ((float)(rand() % 100) / (float)100);
				cluster->sparkleData[pos][4] = cluster->sclspd;
				cluster->sparkleData[pos][5] = cluster->maxscl * ((float)(rand() % 50) / (float)100 + 0.5);
				found = 1;
			}
			pos++;
			if (pos >= sparklePerCluster) found = 1;
		}
	}
	
	float scale;

	glDisable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glPushMatrix();
	glColor4f(cluster->color[0], cluster->color[1], cluster->color[2], cluster->color[3]);
	glTranslatef(cluster->position[0], cluster->position[1], cluster->position[2]);

	for (x = 0; x < sparklePerCluster; x++)
	{
		if (cluster->sparkleData[x][3] > 0)
		{
			glPushMatrix();

			glTranslatef(cluster->sparkleData[x][0],cluster->sparkleData[x][1],cluster->sparkleData[x][2]);

			scale = cluster->sparkleData[x][3];
			glScalef(scale,scale,scale);

			glCallList(sparkleList);

			glPopMatrix();
		}
	}

	glPopMatrix();
	glDisable(GL_NORMALIZE);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);

	
	return 1;
}

void initClusters()
{
	sparkleList = glGenLists(1);
	glNewList(sparkleList, GL_COMPILE);
		drawSparkle();
	glEndList();
}