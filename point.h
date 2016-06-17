#include "shape.h"
#include <vector>
using namespace std;

class Point : public shape 
{
public:

	Point() : shape(1, "Point"), objSet(new vector<PointType>){

	}

	const vector<PointType>* getObjSet();

	virtual void draw();

	virtual ~Point() { delete objSet; }
private:
	virtual void getPoint(FILE*);

	vector<PointType>* objSet;
};