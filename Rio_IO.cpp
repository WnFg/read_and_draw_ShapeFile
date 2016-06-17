#include "Rio_IO.h"
void changeByteOrder(void* p, int size) {
	char* ret = (char*)p;

	for(int i = 0; i < size / 2; i++) {
		char c = ret[i];
		ret[i] = ret[size - i - 1];
		ret[size - i - 1] = c;
	}
}

bool readShp(FILE* m_shpFile, shpHead_type& shpHead) {

	fread(&shpHead.fileCode, sizeof(int), 1, m_shpFile);
	fread(shpHead.unused, sizeof(int), 5, m_shpFile);
	fread(&shpHead.fileSize, sizeof(int), 1, m_shpFile);
	fread(&shpHead.version, sizeof(int), 1, m_shpFile);
	fread(&shpHead.shapeType, sizeof(int), 1, m_shpFile);

	fread(&shpHead.Xmin, sizeof(double), 1, m_shpFile);
	fread(&shpHead.Ymin, sizeof(double), 1, m_shpFile);
	fread(&shpHead.Xmax, sizeof(double), 1, m_shpFile);
	fread(&shpHead.Ymax, sizeof(double), 1, m_shpFile);
	fread(&shpHead.Zmin, sizeof(double), 1, m_shpFile);
	fread(&shpHead.Zmax, sizeof(double), 1, m_shpFile);
	fread(&shpHead.Mmin, sizeof(double), 1, m_shpFile);
	fread(&shpHead.Mmax, sizeof(double), 1, m_shpFile);

	changeByteOrder(&shpHead.fileCode, sizeof(int));
	changeByteOrder(&shpHead.fileSize, sizeof(int));
	return true;
}