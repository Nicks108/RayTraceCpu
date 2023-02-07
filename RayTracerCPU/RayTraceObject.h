#ifndef RAYTRACEOBJECT_H
#define RAYTRACEOBJECT_H

#include "ray.h"
#include "vec3.h"
#include "RayTraceUtils.h"

class Material;

struct HitRecord {
	float t;
	vec3 p;
	vec3 normal;
	Material* matPtr;
};

class RayTraceObject
{
public:
	virtual bool Hit(const ray& r, float t_min, float t_max, HitRecord& rec, RandomGenerator* RandGen) const = 0;
};

#endif