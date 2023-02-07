#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include "RayTraceUtils.h"

struct CameraData
{
	vec3 horizontal;
	float padding1;
	vec3 vertical;
	float padding2;
	vec3 lower_left_corner;
	float AspectRatio;
	vec3 m_Position;
	float padding3;
	vec3 m_Target;
	float padding4;
	vec3 m_Up;
	float M_LenseRadius;
	vec3 m_u;
	float padding5;
	vec3 m_v;
	float padding6;
	vec3 m_w;
	float padding7;
};

class Camera
{
public:
	vec3 horizontal;
	vec3 vertical;
	vec3 lower_left_corner;
	float AspectRatio;
	vec3 m_Position;
	vec3 m_Target;
	vec3 m_Up;
	float M_LenseRadius;

	vec3 m_u, m_v, m_w;

	Camera(vec3 position, vec3 lookat, vec3 up, float vfov, float Aspect, float focusDist)
	{
		M_LenseRadius = Aspect / 2;
		AspectRatio = Aspect;

		m_Position = position;
		m_Target = lookat;
		m_Up = up;

		
		float theta = vfov * M_PI / 180;
		float halfHeight = tan(theta / 2);
		float halfWidth = Aspect * halfHeight;
		//lower_left_corner = vec3(-halfWidth, -halfHeight, -1.0);
		//horizontal = vec3(2 * halfWidth, 0.0, 0.0);
		//vertical = vec3(0.0, 2* halfHeight, 0.0);
		//m_Position = vec3(0.0, 0.0, 0.0);
		m_w = UnitVector(m_Position - m_Target);
		m_u = UnitVector(cross(m_Up, m_w));
		m_v = cross(m_w, m_u);

		lower_left_corner = m_Position - halfWidth*focusDist * m_u - halfHeight * focusDist*m_v - focusDist*m_w;
		horizontal = 2 * halfWidth *focusDist * m_u;
		vertical = 2 * halfHeight *focusDist *m_v;

		/*AspectRatio = Aspect;
		horizontal = vec3(AspectRatio*4.0, 0.0, 0.0);
		vertical = vec3(0.0, 4.0, 0.0);
		lower_left_corner = vec3(horizontal.x() / -2, vertical.y() / -2, -1.0);
		origin = vec3(0.0, 0.0, 0.0);*/
	}
	
	~Camera();

	ray GetRay(float u, float v, RandomGenerator* RandGen )
	{ 
		vec3 rd = M_LenseRadius * RandomInUnitDisk(RandGen);
		vec3 offset = m_u * rd.x() + m_v * rd.y();
		return ray(m_Position +offset, lower_left_corner + u * horizontal + v * vertical - m_Position-offset);
	}
	CameraData GetCameraData()
	{
		CameraData CamData; 
		CamData.horizontal = this->horizontal;
		CamData.vertical = this->vertical;
		CamData.lower_left_corner = this->lower_left_corner;
		CamData.AspectRatio = this->AspectRatio;
		CamData.m_Position = this->m_Position;
		CamData.m_Target = this->m_Target;
		CamData.m_Up = this->m_Up;
		CamData.M_LenseRadius =this->M_LenseRadius;
		CamData.m_u = this->m_u;
		CamData.m_v = this->m_v;
		CamData.m_w = this->m_w;

		return CamData;

	}

};

#endif // CAMERA_H