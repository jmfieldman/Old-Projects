#include "vector.h"
#include "math.h"


float vlength(float* v)
{
	return (float)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void normalize(float* v)
{
	float length = (float)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	
	v[0] /= length;
	v[1] /= length;
	v[2] /= length;
}

float dot(float* v1, float* v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

void cross(float* v1, float* v2, float* dest)
{
	dest[0] = v1[1]*v2[2] - v1[2]*v2[1];
	dest[1] = v1[2]*v2[0] - v1[0]*v2[2];
	dest[2] = v1[0]*v2[1] - v1[1]*v2[0];
}