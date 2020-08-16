#include "ConfOpenGL.h"

void ConfOpenGL::depthTest(bool enable)
{
	enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void ConfOpenGL::culling(bool enable)
{
	if (enable)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		return;
	}

	glDisable(GL_CULL_FACE);
}

void ConfOpenGL::wireframe(bool enable)
{
	enable ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ConfOpenGL::mouseCapture(bool enable)
{
	enable ? SDL_CaptureMouse(SDL_TRUE) : SDL_CaptureMouse(SDL_FALSE);
}

void ConfOpenGL::mouseCursor(bool enable)
{
	enable ? SDL_ShowCursor(1) : SDL_ShowCursor(0);
}

void ConfOpenGL::mouseCenter(SDL_Window* window, unsigned int width, unsigned int height)
{
	SDL_WarpMouseInWindow(window, width / 2.0f, height / 2.0f);
}

void ConfOpenGL::swapBuffers(SDL_Window* window, unsigned int width, unsigned int height)
{
	SDL_GL_SwapWindow(window);

	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, (int)width, (int)height);
}

void ConfOpenGL::viewPort(unsigned int screenWidth, unsigned int screenHeight)
{
	glViewport(0, 0, screenWidth, screenHeight);
}

void ConfOpenGL::glBlend()
{
	glEnable(GL_BLEND);
}

void ConfOpenGL::glBlendFunAlpha()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
