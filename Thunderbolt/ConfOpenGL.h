#ifndef CONF_OPEN_GL_H
#define CONF_OPEN_GL_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace ConfOpenGL {
	void depthTest(bool enable);
	void culling(bool enable);
	void wireframe(bool enable);
	void mouseCapture(bool enable);
	void mouseCursor(bool enable);
	void mouseCenter(SDL_Window* window, unsigned int width, unsigned int height);
	void swapBuffers(SDL_Window* window, unsigned int width, unsigned int height);
	void viewPort(unsigned int screenWidth, unsigned int screenHeight);
	void glBlend();
	void glBlendFunAlpha();
}

#endif