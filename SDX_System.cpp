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

//#include <SDL_joystick.h>
//#include <SDL_mixer.h>
#include "SDX_System.hpp"
#include <stdio.h>

namespace sdx {

bool System::_isInit = false;

/************************** SYSTEM ************************/
/**********************************************************/

bool System::Load(bool loadAllSubsystems)
{
	if(_isInit)
		return true;
	_isInit = SDL_Init(loadAllSubsystems ? SDL_INIT_EVERYTHING : 0) == 0;
	if (_isInit && loadAllSubsystems) {
		 // Load SDL Mixer
		//sdx::System::Audio::load();
		// Enable Joysticks
		//sdx::System::Joysticks::enable();
	}
	return _isInit;
}

void System::Unload()
{
	_isInit = false;
	SDL_Quit();
}

bool System::IsLoaded()
{
	return _isInit;
}

void System::PrintError(const char *filename, int line, const char *preString)
{
	const char *err;
	if (filename == NULL || filename[0] == '\0') {
		PrintError(preString);
		return;
	}
	err = SDL_GetError();
	if(err[0] != '\0') { //not empty string
		if (preString == NULL) {
			preString = "";
		}
		const char *spacer = preString[0] == '\0' ? "" : " ";
		printf("%s (%d): %s%s%s\n", filename, line, preString, spacer, SDL_GetError());
		SDL_ClearError();
	}
}

void System::PrintError(const char *preString) 
{
	const char *err = SDL_GetError();
	if(err[0] != '\0') { //not empty string
		if (preString == NULL) {
			preString = "";
		}
		const char *spacer = preString[0] == '\0' ? "" : " ";
		printf("%s%s%s\n", preString, spacer, SDL_GetError());
		SDL_ClearError();
	}
}

const SDL_version *System::LinkedVersion()
{
	SDL_version *vers = nullptr;
	SDL_GetVersion(vers);
	return vers;
}

/*********************** SYSTEM AUDIO *********************/
/**********************************************************/

/*
bool System::Audio::load()
{
	if(isLoaded() || SDL_InitSubSystem(SDL_INIT_AUDIO) == 0) {
		// Load SDL Mixer
		if(Mix_Init(MIX_INIT_FLAC) == 0)
			System::printError();
		if(Mix_Init(MIX_INIT_MOD) == 0)
			System::printError();
		if(Mix_Init(MIX_INIT_MP3) == 0)
			System::printError();
		if(Mix_Init(MIX_INIT_OGG) == 0)
			System::printError();
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT , 2, 2048);
		Mix_VolumeMusic(MIX_MAX_VOLUME);
		Mix_Volume(-1, MIX_MAX_VOLUME);
	}
	return true;
}

void System::Audio::unload()
{
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

bool System::Audio::isLoaded()
{
	return SDL_WasInit((Uint32) SDL_INIT_AUDIO) != 0;
}
*/

/*********************** SYSTEM VIDEO *********************/
/**********************************************************/

bool System::Video::Load()
{
	bool loaded = IsLoaded() || SDL_InitSubSystem(SDL_INIT_VIDEO) == 0;
	return loaded;
}

void System::Video::Unload()
{
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

bool System::Video::IsLoaded()
{
	return SDL_WasInit((Uint32) SDL_INIT_VIDEO) != 0;
}

/********************* SYSTEM JOYSTICKS *******************/
/**********************************************************/

/*
bool System::Joysticks::load()
{
	return (isLoaded() || (SDL_InitSubSystem(SDL_INIT_JOYSTICK) == 0))
		&& (isEnabled() || enable());
}

void System::Joysticks::unload()
{
	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
}

bool System::Joysticks::isLoaded()
{
	return SDL_WasInit((Uint32) SDL_INIT_JOYSTICK) != 0;
}

bool System::Joysticks::enable()
{
	return SDL_JoystickEventState(SDL_ENABLE) == SDL_ENABLE;
}

bool System::Joysticks::disable()
{
	return SDL_JoystickEventState(SDL_DISABLE) == SDL_DISABLE;
}

bool System::Joysticks::isEnabled()
{
	return SDL_JoystickEventState(SDL_QUERY) == SDL_QUERY;
}
*/


} // namespace sdx