#ifndef __utils_h
#define __utils_h


void initTrigTables();
float cosT(int a);
float sinT(int a);

void normalize(float * vector);
void dot(float * v1, float * v2, float * dest);
void cross(float * v1, float * v2, float * dest);

void glFlatQuad(float * p1, float * p2, float * p3, float * p4);

int getPosOfXY(int x, int y);

#endif