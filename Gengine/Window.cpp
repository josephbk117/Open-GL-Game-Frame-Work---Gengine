#include "Window.h"
#include "Error.h"

namespace Gengine {
	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (_sdlWindow == nullptr)
		{
			fatalError("Window could not be opened");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr)
		{
			fatalError("SDL GL Context could not be created");
		}
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			fatalError("GLEW was not initialized");
		}

		glClearColor(0, 0.5, 0.5, 1.0);

		return 0;
	}
	void Gengine::Window::swapBuffer()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}
}