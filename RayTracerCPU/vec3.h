#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <iostream>
#include <stdlib.h>

class vec3
{
public:
	vec3();
	~vec3();

	vec3(float X, float Y, float Z) { e[0] = X; e[1] = Y; e[2] = Z; }
	inline float& x() { return e[0]; }
	inline float& y()  { return e[1]; }
	inline float& z()  { return e[2]; }
	inline float& r()  { return e[0]; }
	inline float& g()  { return e[1]; }
	inline float& b()  { return e[2]; }

	/*inline float x(float X) { e[0] + X; return e[0]; }
	inline float y(float Y) { e[1] + Y; return e[1]; }
	inline float z(float Z) { e[2] + Z; return e[2]; }
	inline float r(float R) { e[0] + R; return e[0]; }
	inline float g(float G) { e[1] + G; return e[1]; }
	inline float b(float B) { e[2] + B; return e[2]; }*/

	 const vec3& operator+() const { return *this; }
	 vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	 float operator[] (int i) const { return e[i]; }
	 float& operator[] (int i) { return e[i]; }

	 const vec3& operator+= (const vec3 &v2);
	 const vec3& operator-= (const vec3 &v2);
	 const vec3& operator*= (const vec3 &v2);
	 const vec3& operator/= (const vec3 &v2);
	 const vec3& operator*= (const float t);
	 const vec3& operator/= (const float t);

	friend  std::istream & operator>>(std::istream & is, vec3 & t);
	friend  std::ostream& operator << (std::ostream& os, vec3 &t);
	friend  vec3 operator+(const vec3 &v1, const vec3 &v2);
	friend  vec3 operator-(const vec3 &v1, const vec3 &v2);
	friend  vec3 operator*(const vec3 &v1, const vec3 &v2);
	friend  vec3 operator/(const vec3 &v1, const vec3 &v2);
	friend  vec3 operator/(const vec3 v1, const float t);
	friend  vec3 operator*(const vec3 v1, const float t);
	friend  vec3 operator*(const float t, const vec3 v1);
	friend  float dot(const vec3 &v1, const vec3 &v2);
	friend  vec3 cross(const vec3 v1, const vec3 v2);

	friend  vec3 UnitVector(vec3 vec);


	float Length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
	float SquareLength() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
	void MakeUnitVector();


	float e[3];

	static vec3 Red;
	static vec3 Blue;
	static vec3 Green;
	static vec3 White;
	static vec3 Black;

	friend vec3 Reflect(const vec3& v, const vec3& n);
};







#endif // !VEC3