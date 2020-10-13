#ifndef _CAPP_H_
#define _CAPP_H_

#include "Shader.h"

#include <SDL.h>
#define GLEW_STATIC
#include <glew.h>
#include <SDL_opengl.h>

class CApp
{
	private:
		bool	Running;

		SDL_Window* window;
		SDL_GLContext mainContext;

		double r = 0.0;
		double g = 0.0;
		double b = 0.0;

		uint32_t points = 4;
		uint32_t floatsPerPoint = 3;

		Shader shader;
		Shader shader2;

		GLuint vao[2];

	public:
		CApp();

		int OnExecute();

	public:

		bool OnInit();

		void OnEvent(SDL_Event* Event);

		void OnLoop();

		void OnRender();

		void OnCleanup();

		bool StartOpenGLContext();

		void CreateCube();
		void CreateSecondShape();

		bool initGL();
};

// http://www.sdltutorials.com/sdl-tutorial-basics

// http://headerphile.com/sdl2/opengl-part-2-vertexes-vbos-and-vaos/

#endif
