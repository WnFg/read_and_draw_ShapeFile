#include "shape.h"
#include <vector>
using namespace std;

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>

class polyLine : public shape
{
public:
	polyLine() : shape(3, "polyLine"), objSet(new vector<PolyLineType*>) {}

	const vector<PolyLineType*>* getObjSet();

	virtual void draw();

	virtual ~polyLine() { delete objSet; }

private:
	void __draw(int);
	
	virtual void getPoint(FILE*);

	vector<PolyLineType*>* objSet;
};