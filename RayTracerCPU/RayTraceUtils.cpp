#include "RayTraceUtils.h"

vec3 RandomInUnitSphereRejection()
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<> dist(0, 1);
	vec3 p;
	do
	{
		p = 2.0 * vec3(dist(gen), dist(gen), dist(gen)) - vec3(1, 1, 1);
	} while (p.SquareLength() >= 1.0);
	return p;
}

vec3 RandomInUnitSphere(RandomGenerator* RandGen)
{
	vec3 output;
	
	/*std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<> dist(0, 1);*/
	float u = RandGen->GetRandomeFloat();

	float x1 = RandGen->GetRandomeFloat();
	float x2 = RandGen->GetRandomeFloat();
	float x3 = RandGen->GetRandomeFloat();

	float mag = sqrt(x1*x1 + x2 * x2 + x3 * x3);
	x1 /= mag;
	x2 /= mag;
	x3 /= mag;

	float c = cbrt(u);
	output = vec3(x1*c, x2*c, x3* c);

	return output;
}

vec3 RandomInUnitDisk(RandomGenerator* RandGen)
{
	vec3 output;

	/*std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0, 1);*/
	float u = RandGen->GetRandomeFloat();

	float x1 = RandGen->GetRandomeFloat();
	float x2 = RandGen->GetRandomeFloat();
	//float x3 = dist(gen);

	float mag = sqrt(x1*x1 + x2 * x2 + 0);
	x1 /= mag;
	x2 /= mag;
	//x3 /= mag;

	float c = cbrt(u);
	output = vec3(x1*c, x2*c, 0);

	return output;
}