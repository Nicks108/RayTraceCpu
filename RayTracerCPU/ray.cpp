#include "ray.h"



ray::ray()
{
}


ray::~ray()
{
}

////////////////////////////////////////////////////////////////////////////
//vec3 Color(const ray& r)
//{
//	if (HitSphere(vec3(0, 0, -1), 0.5, r))
//		return vec3::Red;
//	vec3 unit_direction = UnitVector(r.Direction());
//	float t = 0.5 * (unit_direction.y() + 1);
//	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
//}
//
//bool HitSphere(const vec3 & center, float radius, const ray & r)
//{
//	vec3 oc = r.Origin() - center;
//	float a = dot(r.Direction(), r.Direction());
//	float b = 2.0 * dot(oc, r.Direction());
//	float c = dot(oc, oc) - radius*radius;
//	float discriminant = b * b - 4 * a*c;
//	return (discriminant > 0);
//}
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//vec3 Color(const ray& r)
//{
//	float t = (HitSphere(vec3(0, 0, -1), 0.5, r));
//	if (t > 0.0)
//	{
//		vec3 N = UnitVector(r.PointAtPerameter(t) - vec3(0, 0, -1));
//		return 0.5* vec3(N.x() + 1, N.y() + 1, N.z() + 1);
//	}
//	vec3 unit_direction = UnitVector(r.Direction());
//	float peramiter = 0.5 * (unit_direction.y() + 1);
//	return (1.0 - peramiter) * vec3(1.0, 1.0, 1.0) + peramiter * vec3(0.5, 0.7, 1.0);
//}
//
//float HitSphere(const vec3 & center, float radius, const ray & r)
//{
//	vec3 oc = r.Origin() - center;
//	float a = dot(r.Direction(), r.Direction());
//	float b = 2.0 * dot(oc, r.Direction());
//	float c = dot(oc, oc) - radius * radius;
//	float discriminant = b * b - 4 * a*c;
//	if (discriminant < 0)
//	{
//		return -1.0;
//	}
//	else
//	{
//		return (-b - sqrt(discriminant)) / (2.0*a);
//	}
//}
////////////////////////////////////////////////////////////////////////////