#include "RayTraceObjectList.h"



RayTraceObjectList::RayTraceObjectList()
{
}


RayTraceObjectList::~RayTraceObjectList()
{
}

bool RayTraceObjectList::Hit(const ray & r, float t_min, float t_max, HitRecord & rec, RandomGenerator* RandGen) const
{
	HitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = t_max;

	for (int i = 0; i < ListSize; i++)
	{
		if (List[i]->Hit(r, t_min, closestSoFar, tempRec, RandGen))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}
