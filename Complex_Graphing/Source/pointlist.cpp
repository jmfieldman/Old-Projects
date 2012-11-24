#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "pointlist.h"

#include <GL/gl.h>
#include <GL/glu.h>

PointList::PointList()
{
	next = NULL;
}

PointList::~PointList()
{
	if (next != NULL) delete next;
}

void PointList::add(PointList* node)
{
	node->setNext(next);
	next = node;
}

void PointList::setNext(PointList* node)
{
	next = node;
}

void PointList::setData(pointData* p, int pos)
{
	memcpy(&(points[pos]),p,sizeof(pointData));
}

void PointList::draw(int window)
{
	glBegin(GL_LINES);

		glColor3d(points[window].r, points[window].g, points[window].b);
		glVertex2d(points[window].x1, points[window].y1);

		glColor3d(points[window].r, points[window].g, points[window].b);
		glVertex2d(points[window].x2, points[window].y2);

	glEnd();

	if (next != NULL) next->draw(window);
}

