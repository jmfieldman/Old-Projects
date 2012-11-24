#ifndef __pointlist_h
#define __pointlist_h

struct pointData {
	double x1,y1,x2,y2;
	double r,g,b;
};

class PointList
{

private:

	PointList* next;

	pointData points[2];

public:

	PointList();
	~PointList();

	void add(PointList* node);
	void setNext(PointList* node);

	void setData(pointData* p, int pos);
	void draw(int window);

};





#endif