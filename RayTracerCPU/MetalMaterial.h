#ifndef METALMATERIAL_H
#define METALMATERIAL_H


#include "Material.h"
#include "RayTraceUtils.h"

class MetalMaterial :
	public Material
{
public:
	MetalMaterial(const vec3& albedo, float f) : Albedo(albedo) { if (f < 1) fuzz = f; else fuzz = 1; };
	vec3 Albedo;
	float fuzz;

	

	// Inherited via Material
	virtual bool Scatter(const ray & rayIn, const HitRecord & hit, vec3 & attenuation, ray & scattered, RandomGenerator* RandGen) const override;

};

#endif // !METALMATERIAL_H