#include "vec3.h"



vec3::vec3()
{
}


vec3::~vec3()
{
}



//Friends
 std::istream & operator>>(std::istream & is, vec3 & t)
{
	is >> t.x() >> t.y() >> t.z();
	return is;
}
 std::ostream& operator << (std::ostream& os, vec3 &t)
{
	os << t.x()<< t.y() << t.z();
	return os;
}

 vec3 operator+(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[0]+v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}
 vec3 operator-(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}
 vec3 operator*(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}
 vec3 operator/(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}
 vec3 operator/(const vec3 v1, const float t)
{
	return vec3(v1.e[0] / t, v1.e[1] / t, v1.e[2] / t );
}
 vec3 operator*(const vec3 v1, const float t)
{
	return vec3(v1.e[0] * t, v1.e[1] * t, v1.e[2] * t);
}
 vec3 operator*(const float t, const vec3 v1)
{
	return vec3(v1.e[0] * t, v1.e[1] * t, v1.e[2] * t);
}
 float dot(const vec3 &v1, const vec3 &v2)
{
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}
 vec3 cross(const vec3 v1, const vec3 v2)
{
	return vec3(
		(v1.e[1] * v2.e[2] - v1.e[2]* v2.e[1]),
		(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0])
	);
}
//end Friends



 const vec3 & vec3::operator+=(const vec3 & v2)
{
	e[0] += v2.e[0];
	e[1] += v2.e[1];
	e[2] += v2.e[2];
	return *this;
}

 const vec3 & vec3::operator-=(const vec3 & v2)
{
	e[0] -= v2.e[0];
	e[1] -= v2.e[1];
	e[2] -= v2.e[2];
	return *this;
}

 const vec3 & vec3::operator*=(const vec3 & v2)
{
	e[0] *= v2.e[0];
	e[1] *= v2.e[1];
	e[2] *= v2.e[2];
	return *this;
}

 const vec3 & vec3::operator/=(const vec3 & v2)
{
	e[0] /= v2.e[0];
	e[1] /= v2.e[1];
	e[2] /= v2.e[2];
	return *this;
}

 const vec3 & vec3::operator*=(const float t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

 const vec3 & vec3::operator/=(const float t)
{
	e[0] /= t;
	e[1] /= t;
	e[2] /= t;
	return *this;
}



 void vec3::MakeUnitVector()
{
	float k = 1.0f / SquareLength();
	x() *= k, y() *= k, z() *= k;
}

 vec3 UnitVector(vec3 vec)
{
	return vec / vec.Length();
}


 vec3 vec3::Red = vec3(1,0,0);
 vec3 vec3::Blue = vec3(0, 1, 0);;
 vec3 vec3::Green = vec3(0, 0, 1);;
 vec3 vec3::White = vec3(1, 1, 1);;
 vec3 vec3::Black = vec3(0, 0, 0);;

 vec3 Reflect(const vec3& v, const vec3& n)
 {
	 return v - 2 * dot(v, n)*n;
 }