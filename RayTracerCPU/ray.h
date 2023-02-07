#ifndef RAY_H
#define RAY_H


#include "vec3.h"
//#include "RayTraceObject.h"
#include <float.h>

class ray
{
public:
	ray();
	ray(const vec3 &a, const vec3 &b) { A = a; B = b; };
	~ray();
	vec3 Origin() const { return A; }
	vec3 Direction() const{ return B; }
	vec3 PointAtPerameter(float t) const {return A + t * B;}

	vec3 A;
	vec3 B;
};
//vec3 Color(const ray& r, RayTraceObject *world);
//vec3 Color(const ray& r);
//float HitSphere(const vec3& center, float radius, const ray& r);
#endif // !RAY_H