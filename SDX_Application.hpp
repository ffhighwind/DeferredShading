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

#pragma once
#ifndef SDX_APPLICATION_HPP
#define SDX_APPLICATION_HPP

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <SDL.h>

#include "SDX_Application.hpp"
#include "SDX_Window.hpp"
#include "SDX_System.hpp"

namespace sdx {

class Application
{
public:
	Application() { }
	~Application();
	// Initializes SDL and a creates a window
	bool Init(const char *title, const WindowSettings &settings, int w = 640, int h = 480);
	// Automatically updates Mouse/Keyboard/Joysticks
	// Starts the application loop which handles events, updates, and renders data.
	int Run();

protected:
	Window _win;
	Uint32 _prevTicks;

	// Called before every Draw(). Ticks is the total number of milliseconds since last Update().
	virtual void Update(Uint32 ticks) = 0;
	// Called after update.
	// Call Window::swapBuffers() at the end to swap buffers.
	virtual void Draw(Uint32 ticks) = 0;
	// Called when the program is asked to terminate.
	// Return true if it okay to exit or false to prevent exiting.
	virtual bool OnQuit() = 0;
	// Called on every Event before other handlers are called internally.
	// This allows you to catch events before they are filtered by the SDX classes.
	// A return of true means that the event has been handled and should not be passed on.
	virtual bool OnEvent(const SDL_Event &e) = 0;
	// Only called on Events that were not handled internally.
	// These are user made events that have been pushed onto the stack.
	virtual void OnCustomEvent(const SDL_Event &e) = 0;
};


} // namespace sdx
#endif // SDX_APPLICATION_HPP