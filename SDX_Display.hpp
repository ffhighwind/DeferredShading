/*
* SDX Display classes
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
#ifndef SDX_DISPLAY_HPP
#define SDX_DISPLAY_HPP

#include <SDL_video.h>
#include <string>
#include <vector>

namespace sdx {

class Window;

enum class PixelFormat : Uint32
{
	UNKNOWN = SDL_PIXELFORMAT_UNKNOWN,
	INDEX1LSP = SDL_PIXELFORMAT_INDEX1LSB,
	INDEX1MSB = SDL_PIXELFORMAT_INDEX1MSB,
	INDEX4LSB = SDL_PIXELFORMAT_INDEX4LSB,
	INDEX4MSB = SDL_PIXELFORMAT_INDEX4MSB,
	INDEX8 = SDL_PIXELFORMAT_INDEX8,
	RGB332 = SDL_PIXELFORMAT_RGB332,
	RGB444 = SDL_PIXELFORMAT_RGB444,
	RGB555 = SDL_PIXELFORMAT_RGB555,
	BGR555 = SDL_PIXELFORMAT_BGR555,
	ARGB4444 = SDL_PIXELFORMAT_ARGB4444,
	RGBA4444 = SDL_PIXELFORMAT_RGBA4444,
	ABGR4444 = SDL_PIXELFORMAT_ABGR4444,
	BGRA4444 = SDL_PIXELFORMAT_BGRA4444,
	ARGB1555 = SDL_PIXELFORMAT_ARGB1555,
	RGBA5551 = SDL_PIXELFORMAT_RGBA5551,
	ABGR1555 = SDL_PIXELFORMAT_ABGR1555,
	BGRA5551 = SDL_PIXELFORMAT_BGRA5551,
	RGB565 = SDL_PIXELFORMAT_RGB565,
	BGR565 = SDL_PIXELFORMAT_BGR565,
	RGB24 = SDL_PIXELFORMAT_RGB24,
	BGR24 = SDL_PIXELFORMAT_BGR24,
	RGB888 = SDL_PIXELFORMAT_RGB888,
	RGBX8888 = SDL_PIXELFORMAT_RGBX8888,
	BGR888 = SDL_PIXELFORMAT_BGR888,
	BGRX8888 = SDL_PIXELFORMAT_BGRX8888,
	ARGB8888 = SDL_PIXELFORMAT_ARGB8888,
	RGBA8888 = SDL_PIXELFORMAT_RGBA8888,
	ABGR8888 = SDL_PIXELFORMAT_ABGR8888,
	BGRA8888 = SDL_PIXELFORMAT_BGRA8888,
	ARGB2101010 = SDL_PIXELFORMAT_ARGB2101010,
	RGBA32 = SDL_PIXELFORMAT_RGBA32, // alias for RGBA byte array of color data, for the current platform(>= SDL 2.0.5)
	ARGB32 = SDL_PIXELFORMAT_ARGB32, // alias for ARGB byte array of color data, for the current platform(>= SDL 2.0.5)
	BGRA32 = SDL_PIXELFORMAT_BGRA32, //	alias for BGRA byte array of color data, for the current platform(>= SDL 2.0.5)
	ABGR32 = SDL_PIXELFORMAT_ABGR32, // alias for ABGR byte array of color data, for the current platform(>= SDL 2.0.5)
	YV12 = SDL_PIXELFORMAT_YV12, // planar mode : Y + V + U(3 planes)
	IYUV = SDL_PIXELFORMAT_IYUV, // planar mode : Y + U + V(3 planes)
	YUY2 = SDL_PIXELFORMAT_YUY2, // packed mode : Y0 + U0 + Y1 + V0(1 plane)
	UYVY = SDL_PIXELFORMAT_UYVY, // packed mode : U0 + Y0 + V0 + Y1(1 plane)
	YVYU = SDL_PIXELFORMAT_YVYU, // packed mode : Y0 + V0 + Y1 + U0(1 plane)
	NV12 = SDL_PIXELFORMAT_NV12, // planar mode : Y + U / V interleaved(2 planes) (>= SDL 2.0.4)
	NV21 = SDL_PIXELFORMAT_NV21, // planar mode : Y + V / U interleaved(2 planes) (>= SDL 2.0.4)
};


class DisplayMode
{
protected:
	SDL_DisplayMode _mode;

public:
	DisplayMode() {}
	DisplayMode(const SDL_DisplayMode &mode) : _mode(mode) {}
	DisplayMode(int width, int height, int refreshRate, PixelFormat format);
	int GetWidth() const;
	void SetWidth(int width);
	int GetHeight() const;
	void SetHeight(int height);
	int GetRefreshRate() const;
	void SetRefreshRate(int refreshRate);
	PixelFormat GetPixelFormat() const;
	void SetPixelFormat(PixelFormat format);
	std::string FormatName() const;
	int GetBitsPerPixel() const;
	friend class sdx::VideoDisplay;
	friend class sdx::Window;
};


class VideoDisplay
{
protected:
	int _index;

public:
	VideoDisplay(int index = 0) : _index(index) {}
	static int NumVideoDisplays();
	static int NumVideoDrivers();
	static std::string CurrentVideoDriver();
	std::string GetVideoDriver() const;
	std::string GetDisplayName() const;
	void GetDisplayModes(std::vector<DisplayMode> &modes) const;
	DisplayMode GetClosestDisplayMode(const DisplayMode &mode);
	bool GetBounds(int *x, int *y, int *w, int *h) const;
	DisplayMode GetDesktopDisplayMode() const;
	DisplayMode GetCurrentDisplayMode() const;
	bool GetDPI(float *ddpi, float *hdpi, float *vdpi) const;
};


} // namespace sdx
#include "SDX_Display.inl"
#endif // SDX_DISPLAY_HPP