#include "Lambertian.h"

bool Lambertian::Scatter(const ray & rayIn, const HitRecord & hit, vec3 & attenuation, ray & scattered, RandomGenerator* RandGen) const
{
	vec3 target = hit.p + hit.normal + RandomInUnitSphere(RandGen);
	scattered = ray(hit.p, target - hit.p);
	attenuation = Albedo;
	return true;
}
