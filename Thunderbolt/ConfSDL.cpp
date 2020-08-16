#include "ConfSDL.h"

int ConfSDL::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return ConfSDL::ERROR_SDL_INIT;
	}

	return 0;
}

int ConfSDL::defaults(SDL_Window*& window, SDL_GLContext& context, unsigned int screenWidth, unsigned int screenHeight, unsigned int sMinor, unsigned int sMajor, bool hasAA)
{
	unsigned int engineError;

	if (engineError = ConfSDL::initSDL() > 0) return engineError;
	if (engineError = ConfSDL::setGlAttributes(sMinor, sMajor) > 0) return engineError;
	if (engineError = ConfSDL::initWindow(window, screenWidth, screenHeight) > 0) return engineError;
	if (engineError = ConfSDL::initContext(context, window) > 0) return engineError;
	if (engineError = ConfSDL::initGlew() > 0) return engineError;
	if (hasAA) bool hasAA = false; ConfSDL::initMultisampling(1,4);
}

int ConfSDL::setGlAttributes(unsigned int major, unsigned int minor)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return 0;
}

void ConfSDL::initMultisampling(int buffers, int sampleSize)
{
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, buffers);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, sampleSize);
}

int ConfSDL::initWindow(SDL_Window*& window, unsigned int width, unsigned int height)
{
	window = SDL_CreateWindow(
		"Thunderbolt",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	if (!window) {
		return ConfSDL::ERROR_CREATE_WINDOW;
	}
	return 0;
}

int ConfSDL::initContext(SDL_GLContext& context, SDL_Window*& window)
{
	context = SDL_GL_CreateContext(window);

	if (!context) {
		return ConfSDL::ERROR_CREATE_CONTEXT;
	}
	return 0;
}

int ConfSDL::initGlew()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err) {
		return ConfSDL::ERROR_GLEW_INIT;
	}

	return 0;
}

int ConfSDL::shutDown(SDL_Window*& window, SDL_GLContext& context)
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}