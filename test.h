#include "shape.h"
#include <vector>
using namespace std;

template <class T>
class traits;

template <>
class traits<PolygonType>
{
public:
	static const bool typeValue = true;
};

template <>
class traits<PolygonZType>
{
public:
	static const bool typeValue = false;
};

template<class T>
class polygonTest : public shape
{
public:
	static const bool mark = traits<T>::typeValue;

	polygonTest() : shape(mark == true ? 3 : 15, 
	mark == true ? "polygon" : "polygonZ"), objSet(new vector<T*>) {}

	const vector<T*>* getObjSet(){
		return objSet;
	};

	virtual void draw() {
		for (int i = 0; i < objSet->size(); i++)
			__draw(i);
	}

	virtual ~polygonTest() { delete objSet; }

protected:
	template <class T1>
	void func(T1*, double*);

	template <>
	void func<PolygonType>(PolygonType* ret, double* c) {
		ret->Points.push_back(PointType(c[0], c[1]));
	}

	template <>
	void func<PolygonZType>(PolygonZType* ret, double* c) {
		ret->Points.push_back(PointZType(c[0], c[1], c[2]));
	}

	template <class T1>
	osg::Vec3 getVec3(T1*, int);

	template <>
	osg::Vec3 getVec3<PolygonType>(PolygonType* obj, int j) {
		return osg::Vec3(obj->Points[j].x, obj->Points[j].y, 0);
	}

	template <>
	osg::Vec3 getVec3<PolygonZType>(PolygonZType* obj, int j) {
		return osg::Vec3(obj->Points[j].x, obj->Points[j].y, obj->Points[j].z);
	}
	void __draw(int i) {
		T* obj = (*objSet)[i];
		obj->Parts.push_back(obj->numPoints);
		for (int i = 0; i < obj->numParts; i++) {
			osg::Vec3Array* ret = new osg::Vec3Array;
			osg::Geometry* geom = new osg::Geometry;
			geom->setVertexArray(ret);

			for (int j = obj->Parts[i]; j < obj->Parts[i + 1]; j++) {
					ret->push_back(getVec3(obj, j));
			}

			geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, ret->size()));
			geod->addDrawable(geom);
		}
		obj->Parts.pop_back();
	}

	virtual void getPoint(FILE* file) {
		int shapeType;
		readRecord(&shapeType, file);
		T *ret = new T;
		if (mark)
			readRecord((char*)ret, file, 56);
		else
			readRecord((char*)ret, file, 40);

		int a;
		for (int i = 0; i < ret->numParts; i++) {
			readRecord(&a, file);
			ret->Parts.push_back(a);
		}

		double cord[mark == true ? 2 : 3];
		for (int i = 0; i < ret->numPoints; i++) {
			if (mark == true) {
				readRecord(cord, file, 2);
		//		ret->Points.push_back(PointType(cord[0], cord[1]));
			}
			else {
				readRecord(cord, file, 3);
		//		ret->Points.push_back(PointZType(cord[0], cord[1], cord[2]));
			}
			func(ret, cord);
		}

		objSet->push_back(ret);
	}

	vector<T*>* objSet;
};