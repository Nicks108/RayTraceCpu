#include "RayTraceTexture.h"



RayTraceTexture::RayTraceTexture(SDL_Renderer* renderer, Uint32 Format, Uint32 ScreenWidth, Uint32 ScreenHeight)
{
	m_pRenderer = renderer;
	m_ScreenHeight = ScreenHeight;
	m_Format = Format;
	m_MappingFormat = SDL_AllocFormat(m_Format);

	m_pTexture = SDL_CreateTexture(m_pRenderer, Format, SDL_TEXTUREACCESS_STREAMING, ScreenWidth, ScreenHeight);
	if (m_pTexture == NULL)
	{
		std::cerr << "unable to create Texture " << SDL_GetError()<< std::endl;
	}
}


RayTraceTexture::~RayTraceTexture()
{
	if (m_pTexture)
		SDL_DestroyTexture(m_pTexture);

	m_MappingFormat = NULL;
}

void RayTraceTexture::Lock()
{
	if (!bLocked)
	{
		if (SDL_LockTexture(m_pTexture, NULL, &MPixels, &MPitch) != 0)
		{
			std::cerr << "Unable to lock texture! " << SDL_GetError() << std::endl;
		}
		else
		{
			bLocked = true;
		}
	}

}
void RayTraceTexture::Unlock()
{
	if (bLocked)
	{
		SDL_UnlockTexture(m_pTexture);
		bLocked = false;
		MPixels = NULL;
	}

}

void* RayTraceTexture::GetPixles()
{
	return MPixels;
}

int RayTraceTexture::GetPitch()
{
	return MPitch;
}

void RayTraceTexture::Draw()
{
	if (!bLocked)
		if (m_pTexture)
			SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, NULL);
}

Uint32 RayTraceTexture::GetPixelCount()
{
	//pitch is width of image in bytes
	//div 4 to get the pitch in pixels
	//mult Height to get all pixles
	return (GetPitch() / 4)* m_ScreenHeight;
}


void RayTraceTexture::SetPixel(Uint32 X, Uint32 Y, vec3 C)
{
	SDL_Color newColor;
	newColor.r = Uint8(C.r());
	newColor.g = Uint8(C.g());
	newColor.b = Uint8(C.b());

	SetPixel(X, Y, newColor);
}

void RayTraceTexture::SetPixel(Uint32 X, Uint32 Y, SDL_Color C)
{
	Uint32* Pixels = (Uint32*)MPixels;

	if (bLocked)
	{
		//- 1 from screen height as the X compoent makes up the last line.
		Pixels[(m_ScreenHeight -1 -Y) *(GetPitch()/4) +X ] = SDL_MapRGB(m_MappingFormat, C.r, C.g, C.b);
	}
	else
	{
		std::cerr << "Texture is not locked!" << std::endl;
	}
}

void RayTraceTexture::AddPixels(Uint32 X, Uint32 Y, SDL_Color C)
{
	SDL_Color Col = GetPixelSDLColor(X,	Y);
	vec3 ColV;
	ColV.r() = float(Col.r) / float(255.99f);
	ColV.b() = float(Col.b) / float(255.99f);
	ColV.g() = float(Col.g) / float(255.99f);

	vec3 CV;
	CV.r() = float(C.r) / float(255.99f);
	CV.b() = float(C.b) / float(255.99f);
	CV.g() = float(C.g) / float(255.99f);

	CV.r() *= 0.3f;
	CV.g() *= 0.3;
	CV.b() *= 0.3f;

	ColV.r() *= 0.7f;
	ColV.g() *= 0.7f;
	ColV.b() *= 0.7f;

	ColV.r() += CV.r();
	ColV.g() += CV.g();
	ColV.b() += CV.b();

	Col.r = Uint8(255.99f *ColV.r());
	Col.g = Uint8(255.99f *ColV.g());
	Col.b = Uint8(255.99f *ColV.b());


	/*C.r *= 0.5;
	C.g *= 0.5;
	C.b *= 0.5;
	
	Col.r *= 0.5;
	Col.g *= 0.5;
	Col.b *= 0.5;

	Col.r += C.r;
	Col.g += C.g;
	Col.b += C.b;*/

	SetPixel(X, Y, Col);

}

void RayTraceTexture::AddPixels(Uint32 X, Uint32 Y, vec3 C)
{
	SDL_Color newColor;
	newColor.r = Uint8(C.r());
	newColor.g = Uint8(C.g());
	newColor.b = Uint8(C.b());
	AddPixels(X, Y, newColor);
}

SDL_Color RayTraceTexture::GetPixelSDLColor(int X, int Y)
{
	Uint32 PixelColor = GetPixel(X, Y);

	SDL_Color C;

	SDL_GetRGB(PixelColor, m_MappingFormat, &C.r, &C.g, &C.b);

	
	return C;
}

vec3 RayTraceTexture::GetPixelVec3Color(int X, int Y)
{

	SDL_Color C = GetPixelSDLColor(X, Y);

	vec3 Col;

	Col.r() = C.r;
	Col.g() = C.g;
	Col.b() = C.b;
	
	return Col;
}

Uint32 RayTraceTexture::GetPixel(int X, int Y)
{
	//SDL_MapRGB(m_MappingFormat, C.r, C.g, C.b)

	Uint32 PixelColor;

	Uint32* Pixels = (Uint32*)MPixels;

	if (bLocked)
	{
		//- 1 from screen height as the X compoent makes up the last line.
		PixelColor = Pixels[(m_ScreenHeight - 1 - Y) *(GetPitch() / 4) + X];
	}
	else
	{
		std::cerr << "Texture is not locked!" << std::endl;
	}

	return PixelColor;
}
