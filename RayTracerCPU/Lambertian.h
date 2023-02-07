#ifndef LAMBERTIAN
#define LAMBERTIAN

#include "Material.h"
#include "Sphere.h"
#include "RayTraceUtils.h"

class Lambertian :
	public Material
{
public:
	Lambertian(const vec3& albedo) : Albedo(albedo) {};
	vec3 Albedo;

	

	// Inherited via Material
	virtual bool Scatter(const ray & rayIn, const HitRecord & hit, vec3 & attenuation, ray & scattered, RandomGenerator* RandGen) const override;

};

#endif // !LAMBERTIAN