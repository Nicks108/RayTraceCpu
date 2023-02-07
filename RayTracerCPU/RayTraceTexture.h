#ifndef RayTraceTexture_H
#define RayTraceTexture_H

#include <SDL.h>
#include <iostream>
#include "vec3.h"
class RayTraceTexture
{
public:
	RayTraceTexture(SDL_Renderer* renderer, Uint32 Format, Uint32 ScreenWidth, Uint32 ScreenHeight);
	virtual ~RayTraceTexture();

	void Lock();
	void Unlock();

	void Draw();

	void* MPixels;
	int MPitch;

	void* GetPixles();

	//get pitch is width of image in bytes
	int GetPitch();

	Uint32 GetPixelCount();

	void SetPixel(Uint32 X, Uint32 Y, vec3 C);
	void SetPixel(Uint32 X, Uint32 Y, SDL_Color C);

	void AddPixels(Uint32 X, Uint32 Y, SDL_Color C);
	void AddPixels(Uint32 X, Uint32 Y, vec3 C);

	SDL_Color GetPixelSDLColor(int X, int Y);
	vec3 GetPixelVec3Color(int X, int Y);
	Uint32 GetPixel(int X, int Y);

private:
	//SDL_Surface* m_pRaytraceSurface;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;

	bool bLocked;

	Uint32 m_ScreenHeight;

	Uint32 m_Format;

	SDL_PixelFormat* m_MappingFormat;
};

#endif // RayTraceTexture_H