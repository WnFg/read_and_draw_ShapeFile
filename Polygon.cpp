#include "Polygon.h"
#include "Rio_IO.h"

void polygon::getPoint(FILE* file) {
	int shapeType;
	readRecord(&shapeType, file);
	PolygonType *ret = new PolygonType;
	readRecord((char*)ret, file, 40);

	int a;
	for (int i = 0; i < ret->numParts; i++) {
		readRecord(&a, file);
		ret->Parts.push_back(a);
	}

	double cord[2];
	for (int i = 0; i < ret->numPoints; i++) {
		readRecord(cord, file, 2);
		ret->Points.push_back(PointType(cord[0], cord[1]));
	}

	objSet->push_back(ret);
}

const vector<PolygonType*>* polygon::getObjSet() {
	return objSet;
}

void polygon::__draw(int i) {
	PolygonType* obj = (*objSet)[i];
	obj->Parts.push_back(obj->numPoints);
	for (int i = 0; i < obj->numParts; i++) {
		osg::Vec3Array* ret = new osg::Vec3Array;
		osg::Geometry* geom = new osg::Geometry;
		geom->setVertexArray(ret);

		for (int j = obj->Parts[i]; j < obj->Parts[i + 1]; j++) {
			ret->push_back(osg::Vec3(obj->Points[j].x, obj->Points[j].y, 0));
		}

		geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, ret->size()));
		geod->addDrawable(geom);
	}
	obj->Parts.pop_back();
}

void polygon::draw() {
	for (int i = 0; i < objSet->size(); i++)
		__draw(i);
}