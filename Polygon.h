#include "shape.h"
#include <vector>
using namespace std;

class polygon : public shape
{
public:

	polygon() : shape(5, "polygon"), objSet(new vector<PolygonType*>) {}

	const vector<PolygonType*>* getObjSet();

	virtual void draw();

	virtual ~polygon() { delete objSet; }

protected:
	polygon(int x, const string& s) : shape(x, s), objSet(new vector<PolygonType*>) {}

	void __draw(int);

	virtual void getPoint(FILE*);

	vector<PolygonType*>* objSet;
};