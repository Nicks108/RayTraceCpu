#ifndef RAYTRACEOBJECTLIST_H
#define RAYTRACEOBJECTLIST_H

#include "RayTraceObject.h"
#include "RayTraceUtils.h"

class RayTraceObjectList :
	public RayTraceObject
{
public:
	RayTraceObject **List;
	int ListSize;
	RayTraceObjectList();
	RayTraceObjectList(RayTraceObject **l, int n) { List = l; ListSize = n; };
	~RayTraceObjectList();

	virtual bool Hit(const ray& r, float t_min, float t_max, HitRecord& rec, RandomGenerator* RandGen)const;
};

#endif //RAYTRACEOBJECTLIST_H