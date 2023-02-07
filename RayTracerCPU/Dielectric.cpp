#include "Dielectric.h"

bool Dielectric::Scatter(const ray & rayIn, const HitRecord & hit, vec3 & attenuation, ray & scattered, RandomGenerator* RandGen) const
{
	vec3 outwardNormal;
	vec3 reflected = Reflect(rayIn.Direction(), hit.normal);

	float refractionIndex;

	attenuation = vec3(1.0, 1.0, 1.0);

	vec3 refracted;

	float reflectionProb;
	float cosine;

	if (dot(rayIn.Direction(), hit.normal) > 0)
	{
		outwardNormal = -hit.normal;
		refractionIndex = m_RefracitonIndex;
		cosine = refractionIndex * dot(rayIn.Direction(), hit.normal) / rayIn.Direction().Length();
	}
	else
	{
		outwardNormal = hit.normal;
		refractionIndex = 1.0 / m_RefracitonIndex;
		cosine = -dot(rayIn.Direction(), hit.normal) / rayIn.Direction().Length();
	}
	

	if (Refraction(rayIn.Direction(), outwardNormal, refractionIndex, refracted))
	{
		reflectionProb = Schlick(cosine, refractionIndex);
	}
	else
	{
		scattered = ray(hit.p, reflected);
		reflectionProb = 1.0;
	}

	/*std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<float> dist(0.0, 1.0);*/

	//should we relect or refract?
	float rand = RandGen->GetRandomeFloat();
	if (rand > reflectionProb)
	{
		scattered = ray(hit.p, refracted);
	}
	else
	{
		scattered = ray(hit.p, reflected);
	}

	return true;
}


bool Dielectric::Refraction(const vec3& v, const vec3& n, float refractionIndex, vec3& refracted) const
{
	vec3 uv = UnitVector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - refractionIndex * refractionIndex * (1 - dt * dt);

	if (discriminant > 0)
	{
		refracted = refractionIndex * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}

float Dielectric::Schlick(float cosine, float refractionIndex) const
{
	float r0 = (1 - refractionIndex) / (1 + refractionIndex);
	r0 = r0 * r0;
	return r0 + (1-r0)*pow((1-cosine),5);
}
