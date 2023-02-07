#include "MetalMaterial.h"

bool MetalMaterial::Scatter(const ray & rayIn, const HitRecord & hit, vec3 & attenuation, ray & scattered, RandomGenerator* RandGen) const
{
	vec3 reflected = Reflect(UnitVector(rayIn.Direction()), hit.normal);
	scattered = ray(hit.p, reflected + fuzz* RandomInUnitSphere(RandGen));
	attenuation = Albedo;

	return (dot(scattered.Direction(), hit.normal)>0);
}
