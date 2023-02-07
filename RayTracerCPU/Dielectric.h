#ifndef  DIELECTRIC_H
#define DIELECTRIC_H


#include "Material.h"
#include <math.h>
#include <random>
class Dielectric :
	public Material
{
public:
	Dielectric(float refracitonIndex) : m_RefracitonIndex(refracitonIndex) {};

	// Inherited via Material
	virtual bool Scatter(const ray & rayIn, const HitRecord & hit, vec3 & attenuation, ray & scattered, RandomGenerator* RandGen) const override;

	

	float m_RefracitonIndex;
private:
	bool Refraction(const vec3& v, const vec3& n, float refractionIndex, vec3& refracted) const;
	float Schlick(float cosine, float refractionIndex) const;
	
	
};

#endif // ! DIELECTRIC_H