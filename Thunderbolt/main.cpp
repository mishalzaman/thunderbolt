#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "ConfOpenGL.h"
#include "ConfSDL.h"
#include "KeyInput.h"
#include "Scene.h"

SDL_Window* window;
SDL_GLContext context;
unsigned int SCREEN_WIDTH = 1280;
unsigned int SCREEN_HEIGHT = 720;
bool wireframe = false;


int main(int argc, char* args[]) {
	/* -----------------
	 Core initialization
	-------------------*/
	unsigned int errCode = ConfSDL::defaults(
		window,			// SDL_Window*
		context,		// SDL_GLContext	
		SCREEN_WIDTH,   // max screen width
		SCREEN_HEIGHT,  // max screen height
		3,				// OpenGL minor version
		3,			    // OpenGL major version
		false			// Multisampling AA
	);

	if (errCode > 0) {
		return errCode;
	};

	ConfOpenGL::viewPort(SCREEN_WIDTH, SCREEN_HEIGHT);
	ConfOpenGL::glBlend();
	ConfOpenGL::glBlendFunAlpha();

	/* -----------------
	 Game
	-------------------*/
	Scene level(SCREEN_WIDTH, SCREEN_HEIGHT, "assets/level1.tmx");
	level.load();
	KeyInput input;

	/* ===== Initializations =====*/
	float deltaTime = 1.0f / 60.0f;

	while (!input.isQuit()) {
		/* -----------------
		 Clear screen
		-------------------*/
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		input.update(deltaTime);

		// wireframe mode
		wireframe = input.isX() ? true : false;
		ConfOpenGL::wireframe(wireframe);

		level.renderTileMap();

		SDL_GL_SwapWindow(window);
	}

	/* -----------------
	 Shutdown
	-------------------*/
	return ConfSDL::shutDown(window, context);
};
