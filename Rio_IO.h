#include <iostream>
#include <cstring>
#include <string>
using namespace std;

template <class T>
int readRecord(T* a, FILE* file, int num = 1) {
	return fread(a, sizeof(T), num, file);
}

struct shpHead_type
{
	int fileCode;
	int unused[5];
	int fileSize;
	int version;
	int shapeType;
	double Xmin;
	double Ymin;
	double Xmax;
	double Ymax;
	double Zmin;
	double Zmax;
	double Mmin;
	double Mmax;
};

void changeByteOrder(void* p, int size);

bool readShp(FILE*, shpHead_type& shpHead);