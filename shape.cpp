#include "shape.h"
#include "Rio_IO.h"

void shape::getShape(FILE* file) {
	int recordNumber;
	int contentLenth;

	/*while(fread(&recordNumber, sizeof(int), 1, file) != 0) {
		++num;
	}*/

	while(readRecord(&recordNumber, file) != 0) {
		readRecord(&contentLenth, file);
		getPoint(file);
	}
}

string shape::getName() {
	return name;
}

int shape::getShapeType() {
	return shape_type;
}


