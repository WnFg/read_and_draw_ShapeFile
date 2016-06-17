#ifndef __SHAPE_H
#define __SHAPE_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
using namespace std;

struct PointType
{
	double x, y;
	PointType(double x, double y) : x(x), y(y) {}
};

struct PointZType
{
	double x, y, z;
	PointZType(double x, double y, double z) : x(x), y(y), z(z) {}
};

template <class T, int x>
struct PolyType
{
	double box[x];
	int numParts;
	int numPoints;
	vector<int> Parts;
	vector<T> Points;
};

typedef PolyType<PointType, 4> PolyLineType;

typedef PolyLineType PolygonType;

typedef PolyType<PointZType, 6> PolygonZType;

class shape
{
public:
	typedef int shapeType;
	
	shape(shapeType a, const string& name) : shape_type(a), name(name), geod(new osg::Geode){}

	virtual void draw() = 0;

	void getShape(FILE*);

	string getName();

	int getShapeType();

	virtual ~shape() {};
	
	osg::ref_ptr<osg::Geode> getGeode() {
		return geod;
	}
protected:
	osg::ref_ptr<osg::Geode> geod;

	string name;

	shapeType shape_type;

	virtual void getPoint(FILE*) = 0;
};

#endif