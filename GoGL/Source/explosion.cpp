
/* 


  Jason Fieldman
  Albert Chu

  CS184 Final Project: GoGL


  */


#include "GoGL.h"




Explosion::Explosion(float r, float g, float b, float a,
				float x, float y, float z,
				int life, float mAD, float grav, float speed) : Effect()
{
	expl.life = life;	
	expl.gravity = grav;

	expl.color[0] = r;
	expl.color[1] = g;
	expl.color[2] = b;
	expl.color[3] = a;

	expl.position[0] = x;
	expl.position[1] = y;
	expl.position[2] = z;

	for (int e = 0; e < shardsPerExplosion; e++)
	{
		expl.shardData[e][0] = ((float)(rand() % 100) / (float)100);
		expl.shardData[e][1] = ((float)(rand() % 100) / (float)100);
		expl.shardData[e][2] = ((float)(rand() % 100) / (float)100);

		expl.shardData[e][3] = (-0.5 + expl.shardData[e][0]) * speed;
		expl.shardData[e][4] = (-0.5 + expl.shardData[e][1]) * speed;
		expl.shardData[e][5] = (-0.5 + expl.shardData[e][2]) * speed * 2;
		
		expl.shardData[e][6] = ((float)(rand() % 200) / (float)100) - 1;
		expl.shardData[e][7] = ((float)(rand() % 200) / (float)100) - 1;
		expl.shardData[e][8] = ((float)(rand() % 200) / (float)100) - 1;

		expl.shardData[e][9] = 0;

		expl.shardData[e][10] = ((float)(rand() % 100) / (float)100) * mAD;
	}
}

Explosion::~Explosion()
{

}


int Explosion::pulse()
{
	expl.life--;
	if (expl.life < 0) return 0;
	int e;

	for (e = 0; e < shardsPerExplosion; e++)
	{
		expl.shardData[e][0] += expl.shardData[e][3];
		expl.shardData[e][1] += expl.shardData[e][4];
		expl.shardData[e][2] += expl.shardData[e][5];
		
		float x = expl.shardData[e][0] + expl.position[0];
		float y = expl.shardData[e][1] + expl.position[1];
		if (expl.shardData[e][2] < 0 && expl.shardData[e][5] < 0 && 
			(x > 0 && x < currentboardwidth && y > 0 && y < currentboardwidth) )
		{
			expl.shardData[e][5] *= -0.7;
			expl.shardData[e][3] *= 0.4;
			expl.shardData[e][4] *= 0.4;
			expl.shardData[e][10] *= 0.3;
		}

		expl.shardData[e][5] += expl.gravity;

		expl.shardData[e][9] += expl.shardData[e][10];
	}

	glPushMatrix();
	glTranslatef(expl.position[0],expl.position[1],expl.position[2]);
	glColor4f(expl.color[0],expl.color[1],expl.color[2],expl.color[3]);
	for (e = 0; e < shardsPerExplosion; e++)
	{
		glPushMatrix();
		glTranslatef(expl.shardData[e][0],expl.shardData[e][1],expl.shardData[e][2]);
		glRotatef(expl.shardData[e][9],expl.shardData[e][6],expl.shardData[e][7],expl.shardData[e][8]);
		glBegin(GL_TRIANGLES);
			glNormal3f(0,0,1);
			glVertex3f(0,0.15,0); glVertex3f(0,-0.15,0); glVertex3f(0.30,0,0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();


	return 1;
}

int Explosion::type()
{
	return TYPE_EXPLOSION;
}

float Explosion::getRed()
{
	return expl.color[0];
}