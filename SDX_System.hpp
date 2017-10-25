/*
* SDX System class
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
#ifndef SDX_SYSTEM_HPP
#define SDX_SYSTEM_HPP

#include <SDL.h>

namespace sdx {

class System
{
public:
	// Sets up proc addresses for all SDL function calls and initializes SDL.
	// This needs to be called before all other SDL calls.
	static bool Load(bool loadAllSubsystems=true);
	// Cleans up and unloads SDL's DLL.
	static void Unload();
	static bool IsLoaded();
	// Checks if there is an error and prints the message with an pre-appended string.
	static void PrintError(const char *preString="");
	static void PrintError(const char *filename, int line, const char *preString="");
	static const SDL_version *LinkedVersion();

	class Video
	{
	public:
		static bool Load();
		static void Unload();
		static bool IsLoaded();
	};

	/*
	class Audio
	{
	public:
		static bool load();
		static void unload();
		static bool isLoaded();
	};
	*/

	/*
	class Joysticks 
	{
	public:
		static bool load();
		static void unload();
		static bool isLoaded();
		// Enables events (automatically called on Joysticks load)
		static bool enable();
		static bool disable();
		static bool isEnabled();
	};
	*/

	//SDL_INIT_HAPTIC
	//SDL_INIT_GAMECONTROLLER
	//SDL_INIT_EVENTS


	enum CompiledVersion {
		MAJOR = SDL_MAJOR_VERSION,
		MINOR = SDL_MINOR_VERSION,
		PATCH = SDL_PATCHLEVEL,
	};

private:
	System() { } // static class
	static bool _isInit;
};

/*
void SDL_DisableScreenSaver(void)
void SDL_EnableScreenSaver(void)
SDL_bool SDL_IsScreenSaverEnabled(void)
*/

} // namespace sdx
#endif // SDX_SYSTEM_HPP