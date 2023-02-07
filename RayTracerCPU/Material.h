#ifndef MATERIAL
#define MATERIAL


#include "RayTraceUtils.h"
#include "RayTraceObject.h"


class Material
{
public:
	virtual bool Scatter(const ray& rayIn, const HitRecord& hit, vec3& attenuation, ray& scattered, RandomGenerator* RandGen) const = 0;
};

#endif // !MATERIAL