#include "Sphere.h"



Sphere::Sphere()
{
}

bool Sphere::Hit(const ray & r, float t_min, float t_max, HitRecord & rec, RandomGenerator* RandGen) const
{
	vec3 oc = r.Origin() - Center;
	vec3 RayDirecton = r.Direction();
	float a = dot(RayDirecton, RayDirecton);
	float b = dot(oc, RayDirecton);
	float c = dot(oc, oc) - Radius*Radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		rec.matPtr = m_pMaterial;
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.PointAtPerameter(rec.t);
			rec.normal = (rec.p - Center) / Radius;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.PointAtPerameter(rec.t);
			rec.normal = (rec.p - Center) / Radius;
			return true;
		}
	}

	return false;
}
