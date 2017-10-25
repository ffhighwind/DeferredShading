/*
* SDX Display class
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
#ifndef SDX_DISPLAY_INL
#define SDX_DISPLAY_INL

#include "SDX_Display.hpp"

namespace sdx {

// ********************** Display **********************
// *****************************************************

inline int VideoDisplay::NumVideoDisplays()
{
	return SDL_GetNumVideoDisplays();
}

inline int VideoDisplay::NumVideoDrivers()
{
	return SDL_GetNumVideoDrivers();
}

inline std::string VideoDisplay::CurrentVideoDriver()
{
	return SDL_GetCurrentVideoDriver();
}

inline std::string VideoDisplay::GetVideoDriver() const
{
	return SDL_GetVideoDriver(_index);
}

inline std::string VideoDisplay::GetDisplayName() const
{
	return SDL_GetDisplayName(_index);
}

inline DisplayMode VideoDisplay::GetDesktopDisplayMode() const
{
	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(_index, &mode);
	return DisplayMode(mode);
}

inline DisplayMode VideoDisplay::GetCurrentDisplayMode() const
{
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(_index, &mode);
	return DisplayMode(mode);
}

inline DisplayMode VideoDisplay::GetClosestDisplayMode(const DisplayMode &mode)
{
	DisplayMode result;
	SDL_GetClosestDisplayMode(_index, &mode._mode, &result._mode);
	return result;
}

inline bool VideoDisplay::GetDPI(float *ddpi, float *hdpi, float *vdpi) const
{
	return SDL_GetDisplayDPI(_index, ddpi, hdpi, vdpi) == 0;
}

// ******************** DisplayMode ********************
// *****************************************************

inline DisplayMode::DisplayMode(int width, int height, int refreshRate, PixelFormat format)
{
	_mode.w = width;
	_mode.h = height;
	_mode.refresh_rate = refreshRate;
	_mode.format = (Uint32)format;
}

inline int DisplayMode::GetWidth() const
{
	return _mode.w;
}

inline void DisplayMode::SetWidth(int width)
{
	_mode.w = width;
}

inline int DisplayMode::GetHeight() const
{
	return _mode.h;
}

inline void DisplayMode::SetHeight(int height)
{
	_mode.h = height;
}

inline int DisplayMode::GetRefreshRate() const
{
	return _mode.refresh_rate;
}

inline void DisplayMode::SetRefreshRate(int refreshRate)
{
	_mode.refresh_rate = refreshRate;
}

inline PixelFormat DisplayMode::GetPixelFormat() const
{
	return (PixelFormat)_mode.format;
}

inline void DisplayMode::SetPixelFormat(PixelFormat format)
{
	_mode.format = (Uint32)format;
}

inline std::string DisplayMode::FormatName() const
{
	return SDL_GetPixelFormatName(_mode.format);
}

inline int DisplayMode::GetBitsPerPixel() const
{
	return SDL_BITSPERPIXEL(_mode.format);
}


} // namespace sdx
#endif // SDX_DISPLAY_INL