#ifndef SPHRE_H
#define SPHRE_H


#include "RayTraceObject.h"
#include "Material.h"
class Sphere : public RayTraceObject
{
public:
	vec3 Center;
	float Radius;
	Material* m_pMaterial;

	Sphere();
	Sphere(vec3 cen, float r, Material* matPtr) : Center(cen), Radius(r), m_pMaterial(matPtr) {};
	

	virtual bool Hit(const ray& r, float t_min, float t_max, HitRecord& rec, RandomGenerator* RandGen)const;
};




#endif // !SPHRE
