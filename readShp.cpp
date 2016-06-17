#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include "Rio_IO.h"
#include "point.h"
#include "Polygon.h"
#include "PolyLine.h"
#include "test.h"
using namespace std;

int main()
{
	polygonTest<PolygonType> a;
	string fileName;
	cin >> fileName;
	shpHead_type shpHead;

	FILE* m_shpFile;

	if ((m_shpFile = fopen(fileName.c_str(), "rb")) == NULL) {
		exit(-1);
	}

	readShp(m_shpFile, shpHead);

	cout << shpHead.fileCode << endl;
	cout << shpHead.shapeType << endl;
	cout << shpHead.fileSize << endl;
	cout << shpHead.Xmax << endl;
	cout << shpHead.Xmin << endl;
	cout << shpHead.Ymax << endl;
	cout << shpHead.Ymin << endl;
	cout << shpHead.Zmax << endl;
	cout << shpHead.Zmin << endl;
	cout << shpHead.Mmax << endl;
	cout << shpHead.Mmin << endl;
	//return 0;
	

	shape* obj;

	if (shpHead.shapeType == 3)
		obj = new polyLine;
	else
		obj = new polygon;

	obj->getShape(m_shpFile);
	
	// cout << obj->getObjSet()->size() << endl;
	
	obj->draw();
	osgViewer::Viewer viewer;
	osg::Group * root = new osg::Group();
	root->addChild(obj->getGeode());
	viewer.setSceneData(root);
	viewer.realize();
	viewer.run();
	return 0;
}