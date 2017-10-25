/*
* SDX Application class
*
* Copyright (c) 2013 Wesley Hamilton
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include "SDX_Application.hpp"
#include "SDX_System.hpp"
#include "SDX_Keyboard.hpp"
#include "SDX_Mouse.hpp"
#include <functional>

namespace sdx {

Application::~Application()
{
	_prevTicks = 0;
	_win.Destroy();
	System::Unload();
}

bool Application::Init(const char *title, const WindowSettings &settings, int w, int h)
{
	if (!System::Load(true)) {
		sdx::System::PrintError(__FILE__, __LINE__, "Error initializing SDL"); 
		return false; 
	}
	if (!System::Video::Load()) {
		sdx::System::PrintError(__FILE__, __LINE__, "Error initializing SDL Video");
		return false;
	}
	if (!_win.Create(title, settings, w, h, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)) {
		sdx::System::PrintError(__FILE__, __LINE__, "Error initializing SDL Window");
		return false;
	}
	if (!_win.CreateGLContext()) {
		sdx::System::PrintError(__FILE__, __LINE__, "Error initializing SDL OpenGL Context");
		_win.Destroy();
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(err));
		_win.Destroy();
		return false;
	}

	glViewport(0, 0, w, h);
	gluPerspective(60.0f, (float)w / (h == 0 ? 1.0f : h), 1.0f, 1024.0f);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glDisable(GL_CULL_FACE);

	// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_win.SwapBuffers();

	return true;
}


int Application::Run()
{
	SDL_Event e;

	_prevTicks = SDL_GetTicks();
	// Application Loop
	for(;;) {
		// Handle events
		Mouse::Update();
		Keyboard::Update();
		while (SDL_PollEvent(&e) != 0) {
			if(OnEvent(e)
				|| Mouse::HandleEvent(e) 
				|| Keyboard::HandleEvent(e)
				|| Window::HandleEvent(e))
			{ } // short circuit or
			else if(e.type == SDL_QUIT) {
				if(OnQuit()) {
					return EXIT_SUCCESS;
				}
			}
			else {
				OnCustomEvent(e);
			}
		}
		Uint32 ticks = SDL_GetTicks();
		Update(ticks - _prevTicks);
		Draw(ticks - _prevTicks);
		_prevTicks = ticks;
		_win.SwapBuffers();
	}
	return EXIT_FAILURE; // Unreachable (error)
}

} // namespace sdx
