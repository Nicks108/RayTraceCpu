#define GLEW_STATIC
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#undef main

#include <random>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "RayTraceTexture.h"

#include "ray.h"
#include "vec3.h"
#include "RayTraceObjectList.h"
#include "Sphere.h"
#include "Camera.h"

#include "RayTraceUtils.h"
#include "Material.h"
#include "Lambertian.h"
#include "MetalMaterial.h"
#include "Dielectric.h"

#include <thread>
#include <mutex>
#include <chrono>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
bool bCanQuit = false;


void HandleEvents();
std::string LoadShader(const std::string &fileName);
void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage);

int GetTimeAsInt()
{
	std::chrono::system_clock::duration now = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::seconds>(now).count();
}

vec3 Color(const ray& r, RayTraceObject *world, int depth, RandomGenerator* RandGen)
{
	HitRecord rec;
	if (world->Hit(r, 0.001, FLT_MAX, rec, RandGen))
	{
		//return 0.5*vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.matPtr->Scatter(r, rec, attenuation, scattered, RandGen))
		{
			return attenuation * Color(scattered, world, depth + 1, RandGen);
		}
		else
		{
			return vec3::Black;
		}

		//vec3 target = rec.p + rec.normal + RandomInUnitSphere();
		//return 0.5 * Color(ray(rec.p, target - rec.p), world);
	}
	else // background colour
	{
		vec3 unitDirection = UnitVector(r.Direction());
		float t = 0.5*(unitDirection.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

bool QUICKHACKGGLOBAL_ISFIRSTITTER = true;
const Uint32 RaysPerPixle = 100;
const Uint32 RenderingIterations = 1;
const Uint32 MaxThreads = 22;

//GLuint ProgramHandle;
//GLuint outputVBO[2];
//struct RayCompStruct
//{
//	float DirectionX;
//	float DirectionY;
//	float DirectionZ;
//	float Padding;
//
//	float OriginX;
//	float OriginY;
//	float OriginZ;
//	float Padding2;
//
//};
//
//RayCompStruct data[100];
//GLuint gDestBufferBinding = 0; // the index of the out put buffer binding?
//GLuint gCameraDataBufferBinding = 1; // the index of the out put buffer binding?

std::mutex mtx;
void ThreadXWorker(RayTraceTexture &RenderSurface, Camera & Cam, int Y, RayTraceObjectList World)
{
	/*std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<float> dist(0, 1);*/

	RandomGenerator RandGen;


	
	//RayCompStruct threadData[100];
	


	for (int X = SCREEN_WIDTH - 1; X >= 0; X--) // for (int X = 0; X < XPIxels; X++)
	{

		//glUseProgram(ProgramHandle);

		//GLuint iTimeLoc = glGetUniformLocation(ProgramHandle, "iTime");
		//glUniform1i(iTimeLoc, GetTimeAsInt());
		//GLuint ScreenSizexLoc = glGetUniformLocation(ProgramHandle, "ScreenSizeX");
		//glUniform1i(ScreenSizexLoc, SCREEN_WIDTH);
		//GLuint ScreenSizeyLoc = glGetUniformLocation(ProgramHandle, "ScreenSizeY");
		//glUniform1i(ScreenSizeyLoc, SCREEN_HEIGHT);
		//GLuint ScreenYPosLoc = glGetUniformLocation(ProgramHandle, "ScreenXPos");
		//glUniform1i(ScreenYPosLoc, X);


		////dispatch program

		//glDispatchCompute(RaysPerPixle, 1, 1);

		//glBindBuffer(GL_ARRAY_BUFFER, outputVBO[0]);
		//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, gDestBufferBinding, outputVBO[0]);
		//glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
		//glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(threadData), threadData);
		//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, gDestBufferBinding, 0);



		vec3 col(0, 0, 0);
		int s = 0;
		for (s = 0; s < RaysPerPixle; s++)
		{
			//std::cout<<dist(rd)<< std::endl;
			float u = float(X + RandGen.GetRandomeFloat()) / float(SCREEN_WIDTH);
			float v = float(Y + RandGen.GetRandomeFloat()) / float(SCREEN_HEIGHT);

			//float u = float(X) / float(XPIxels);
			//float v = float(Y) / float(SCREEN_HEIGHT);
			ray r = Cam.GetRay(u, v, &RandGen);
			//ray r; 
			//r.A = { threadData[s].OriginX, threadData[s].OriginY, threadData[s].OriginZ };
			//r.B = { threadData[s].DirectionX, threadData[s].DirectionY ,threadData[s].DirectionZ };
			col += Color(r, &World,0, &RandGen);
		}
		col /= s;
		col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
		int ir = int(255.99 * col[0]);
		int ig = int(255.99 * col[1]);
		int ib = int(255.99 * col[2]);
		SDL_Color C;
		C.r = ir;
		C.b = ib;
		C.g = ig;
		mtx.lock();
		if(QUICKHACKGGLOBAL_ISFIRSTITTER)
			RenderSurface.SetPixel(X, Y, C);
		else
			RenderSurface.AddPixels(X, Y, C);
		mtx.unlock();
	}

	

}



#include "Timer.h"

int main(void)
{
	//const int TesetLength = 1000000;

	//std::cout << "Warmup" << std::endl;
	//std::cout << "Non-Rejection" << std::endl;
	//{
	//	Timer t =Timer();
	//	for (int i = 0; i < TesetLength; i++)
	//	{
	//		RandomInUnitSphere();
	//	}
	//}

	//{
	//	
	//	Timer t = Timer();
	//	for (int i = 0; i < TesetLength; i++)
	//	{
	//		RandomInUnitSphereRejection();
	//	}
	//}
	//


	//	std::cout << "TEST!" << std::endl;
	//	{
	//		std::cout << "Non-Rejection" << std::endl;
	//		Timer t = Timer();
	//		for (int i = 0; i < TesetLength; i++)
	//		{
	//			RandomInUnitSphere();
	//		}
	//	}

	//	{
	//		std::cout << "Rejection" << std::endl;
	//		Timer t = Timer();
	//		for (int i = 0; i < TesetLength; i++)
	//		{
	//			RandomInUnitSphereRejection();
	//		}
	//	}


	SDL_Window* pWindow = NULL;
	SDL_Renderer* pRenderer = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL couldnt not be initialized! ERROR: " << SDL_GetError() << std::endl;
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //32 bit inc RGBA
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); // dept is not 32 bit

		pWindow = SDL_CreateWindow("CPU Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
		if (pWindow == NULL)
		{
			std::cerr << "Window could not be created! ERROR: " << SDL_GetError() << std::endl;
		}
		else
		{

			pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
			if (pRenderer == NULL)
			{
				std::cerr << "Craeting Renderer Failed! SDL error: " << SDL_GetError() << std::endl;
			}
			SDL_SetRenderDrawColor(pRenderer, 0, 0, 128, 0);


			RayTraceTexture RenderSurface(pRenderer, SDL_GetWindowPixelFormat(pWindow), SCREEN_WIDTH, SCREEN_HEIGHT);


			SDL_GLContext GLContext = SDL_GL_CreateContext(pWindow);
			GLint GlewInitResult = glewInit();
			if (GLEW_OK != GlewInitResult)
			{
				std::cerr<< "ERROR: " << glewGetErrorString(GlewInitResult) << std::endl;
			}

			

			////test Surface writes
			//RenderSurface.Lock();
			//Uint32* pixels =(Uint32*)RenderSurface.GetPixles();

			//Uint32 Format = SDL_GetWindowPixelFormat(pWindow);
			//SDL_PixelFormat* MappingFormat = SDL_AllocFormat(Format);

			//for (int i = 0; i < RenderSurface.GetPixelCount(); i++)
			//{
			//	pixels[i] = SDL_MapRGB(MappingFormat, 0xFF, 0x00, 0x00);
			//}
			//RenderSurface.Unlock();
			//// end of test surface writes

			//test Surface writes 2
			RenderSurface.Lock();
			Uint32 XPIxels = RenderSurface.GetPitch() / 4;

			float aspectRatio = float(SCREEN_WIDTH) / float(SCREEN_HEIGHT);
			//vec3 lower_left_corner(-2.0, -1.0, -1.0);
			//vec3 horizontal(SCREEN_WIDTH, 0.0, 0.0);
			//vec3 vertical(0.0, aspectRatio, 0.0);
			//horizontal *= 4;
			//vertical *= 2;

			
			//vec3 horizontal(aspectRatio*4.0, 0.0, 0.0);
			//vec3 vertical(0.0, 4.0, 0.0);
			//vec3 lower_left_corner(horizontal.x()/-2, vertical.y() /-2, -1.0);
			//vec3 origin(0.0, 0.0, 0.0);

			RayTraceObject *list[5];
			list[0] = new Sphere(vec3(0, 0, -1), 0.5, new Lambertian(vec3(0.8, 0.3, 0.3)));
			list[1] = new Sphere(vec3(0, -100.5, -1), 100, new Lambertian(vec3(0.8, 0.8, 0.0)));
			list[2] = new Sphere(vec3(1, 0, -1), 0.5, new MetalMaterial(vec3(0.8, 0.6, 0.2), 0.3));
			list[3] = new Sphere(vec3(-1, 0, -1), 0.5, new Dielectric(1.5));
			list[4] = new Sphere(vec3(-1, 0, -1), -0.45, new Dielectric(1.5));
			RayTraceObjectList *World = new RayTraceObjectList(list, 5);


			Camera Cam(vec3(-2,2,1), vec3(0,0,-1), vec3(0,1,0),  120, aspectRatio, (vec3(-2, 2, 1)- vec3(0, 0, -1)).Length() );

			/*std::random_device rd;
			std::mt19937_64 gen(rd());
			std::uniform_real_distribution<float> dist(0, 1);*/


			//const Uint32 MaxThreads = 22;
			std::thread Threads[MaxThreads];






			////create shader program
			//ProgramHandle = glCreateProgram();
			//GLuint mComputeShader = glCreateShader(GL_COMPUTE_SHADER);
			//std::string shaderCode = LoadShader("../RayTracerCPU/GetRay.comp");
			//const char* tempSourceCode = shaderCode.c_str();
			//glShaderSource(mComputeShader, 1, &tempSourceCode, NULL);
			//glCompileShader(mComputeShader);
			//glAttachShader(ProgramHandle, mComputeShader);
			//glLinkProgram(ProgramHandle);

			////check shader program
			//glLinkProgram(ProgramHandle);
			//CheckShaderError(ProgramHandle, GL_LINK_STATUS, true, "Error: Program Linking failed: ");

			//glValidateProgram(ProgramHandle);
			//CheckShaderError(ProgramHandle, GL_VALIDATE_STATUS, true, "Error: Program is invlide: ");

			//

			//
			//glGenBuffers(2, outputVBO);
			//glBindBuffer(GL_ARRAY_BUFFER, outputVBO[0]);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(data), nullptr, GL_STATIC_READ);
			//
			//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, gDestBufferBinding, outputVBO[0]);

			//CameraData CamData = Cam.GetCameraData();
			//glBindBuffer(GL_ARRAY_BUFFER, outputVBO[1]);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(CamData), &CamData, GL_STATIC_READ);
			//GLuint gCameraDataBufferBinding = 1; // the index of the out put buffer binding?
			//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, gCameraDataBufferBinding, outputVBO[1]);

			//glEnable(GL_RASTERIZER_DISCARD);




			//for (int Y = SCREEN_HEIGHT - 1; Y >= 0; Y--) //for (int Y = SCREEN_HEIGHT-1; Y >= 0; Y--)   for (int Y = 0; Y < SCREEN_HEIGHT; Y++)
			//{
			//	ThreadXWorker(std::ref(RenderSurface), std::ref(Cam), Y, *World);
			//	RenderSurface.Unlock();
			//	RenderSurface.Draw();
			//	SDL_RenderPresent(pRenderer);
			//	RenderSurface.Lock();
			//}


			for (int i = 0; i < RenderingIterations; i++)
			{

				//for (int Y = SCREEN_HEIGHT - 1; Y >= 0; Y--) //for (int Y = SCREEN_HEIGHT-1; Y >= 0; Y--)   for (int Y = 0; Y < SCREEN_HEIGHT; Y++)
				for (int Y = SCREEN_HEIGHT - 1; Y >= 0; Y -= MaxThreads) //for (int Y = SCREEN_HEIGHT-1; Y >= 0; Y--)   for (int Y = 0; Y < SCREEN_HEIGHT; Y++)
				{
					//void ThreadXWorker(RayTraceTexture &RenderSurface, Camera &const Cam, int & const Y, RayTraceObjectList World)

					for (int i = 0; i < MaxThreads; i++)
					{
						Threads[i] = std::thread(ThreadXWorker, std::ref(RenderSurface), std::ref(Cam), Y - i, *World);
						//Threads[1] = std::thread(ThreadXWorker, std::ref(RenderSurface), std::ref(Cam), Y - 1, *World);
						//Threads[2] = std::thread(ThreadXWorker, std::ref(RenderSurface), std::ref(Cam), Y - 2, *World);
						//Threads[3] = std::thread(ThreadXWorker, std::ref(RenderSurface), std::ref(Cam), Y - 3, *World);
						//Threads[4] = std::thread(ThreadXWorker, std::ref(RenderSurface), std::ref(Cam), Y - 4, *World);
					}

					for (int i = 0; i < MaxThreads; i++)
					{
						Threads[i].join();
						//Threads[1].join();
						//Threads[2].join();
						//Threads[3].join();
						//Threads[4].join();
					}
					//for (int X = SCREEN_WIDTH -1; X >=0; X--) // for (int X = 0; X < XPIxels; X++)
					//{
	//#define DEBUG 
#ifdef DEBUG


					SDL_Color C;
					float r = float(X) / float(SCREEN_WIDTH);  //x over screen width is the percentage yo twat!
					float g = float(Y) / float(SCREEN_HEIGHT);
					float b = 0.2f;

					C.r = Uint8(255.99f *r);
					C.g = Uint8(255.99f *g);
					C.b = Uint8(255.99f *b);
					/*C.r = 0xFF;
					C.g = 0xFF;
					C.b = 0x00;*/
					RenderSurface.SetPixel(X, Y, C);
					////std::cout << X << ":" << Y << std::endl;
#else
					//vec3 col(0,0,0);
					//int s = 0;
					//for (s = 0; s < 10; s++)
					//{
					//	//std::cout<<dist(rd)<< std::endl;
					//	float u = float(X + dist(gen) )/ float(SCREEN_WIDTH);
					//	float v = float(Y + dist(gen)) / float(SCREEN_HEIGHT);

					//	//float u = float(X) / float(XPIxels);
					//	//float v = float(Y) / float(SCREEN_HEIGHT);
					//	ray r = Cam.GetRay(u, v);
					//	col += Color(r, World);
					//}
					//col /= s;
					//col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
					//int ir = int(255.99 * col[0]);
					//int ig = int(255.99 * col[1]);
					//int ib = int(255.99 * col[2]);
					//SDL_Color C;
					//C.r = ir;
					//C.b = ib;
					//C.g = ig;
					//RenderSurface.SetPixel(X, Y, C);


#endif // DEBUG
				//}
				//if (Y % 10 == 0)
				//{
					RenderSurface.Unlock();
					RenderSurface.Draw();
					SDL_RenderPresent(pRenderer);
					RenderSurface.Lock();
					//}
				}

				QUICKHACKGGLOBAL_ISFIRSTITTER = false;
				system("CLS");
				std::cout << "Iteration: " << i << std::endl;
			}


			


			/*SDL_Color c;
			c.r = 255;
			c.g = 255;
			c.b = 255;*/
			//RenderSurface.SetPixel(0, 0, c);

			RenderSurface.Unlock();
			//end of test surface writes 2

			/*glDeleteBuffers(2, outputVBO);
			glDeleteProgram(ProgramHandle);
			glDeleteShader(mComputeShader);*/

			while (!bCanQuit)
			{
				SDL_RenderClear(pRenderer);
				HandleEvents();

				//draw
				RenderSurface.Draw();

				SDL_RenderPresent(pRenderer);
				SDL_Delay(16);
			}
		}
	}
	

	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	return 0;
}

void HandleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			bCanQuit = true;
			break;
		default:
			break;
		}
	}

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_ESCAPE])
	{
		bCanQuit= true;
	}

}


std::string LoadShader(const std::string &fileName)
{
	std::ifstream file;
	const char* fileNameChar = fileName.c_str();
	file.open(fileNameChar, std::ifstream::in);

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}
	return output;
}

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);


	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}