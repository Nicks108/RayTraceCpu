#ifndef RAYTRACEUTILS_H
#define RAYTRACEUTILS_H
#include <random>
#include "vec3.h"

struct RandomGenerator
{
	std::random_device rd;
	std::mt19937_64 gen;
	std::uniform_real_distribution<float> dist;

	RandomGenerator()
	{
		gen = std::mt19937_64(rd());
		dist = std::uniform_real_distribution<float>(0, 1);
	}

	float GetRandomeFloat()
	{
		return dist(gen);
	}
};



vec3 RandomInUnitSphere(RandomGenerator* RandGen);
vec3 RandomInUnitSphereRejection();

vec3 RandomInUnitDisk(RandomGenerator* RandGen);



#endif // !RAYTRACEUTILS_H
