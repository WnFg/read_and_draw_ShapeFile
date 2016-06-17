#include "point.h"
#include "Rio_IO.h"

void Point::getPoint(FILE* file) {
	int x;
	readRecord(&x, file);
	double cord[2];
	readRecord(cord, file, 2);
	objSet->push_back(PointType(cord[0], cord[1]));
}

const vector<PointType>* Point::getObjSet() {
	return objSet;
}

void Point::draw() {
	
}