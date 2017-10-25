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

#include "SDX_Window.hpp"
#include "SDX_Display.hpp"

namespace sdx {

// ********************** Display **********************
// *****************************************************


void VideoDisplay::GetDisplayModes(std::vector<DisplayMode> &modes) const
{
	SDL_DisplayMode mode;
	modes.clear();
	int totalModes = SDL_GetNumDisplayModes(_index);
	for (int modeIndex = 0; modeIndex < totalModes; modeIndex++) {
		if (SDL_GetDisplayMode(_index, modeIndex, &mode) != 0) {
			return;
		}
		modes.push_back(DisplayMode(mode));
	}
}

bool VideoDisplay::GetBounds(int *x, int *y, int *w, int *h) const
{
	SDL_Rect rect;
	if (SDL_GetDisplayBounds(_index, &rect) == 0) {
		if (x != NULL) {
			*x = rect.x;
		}
		if (y != NULL) {
			*y = rect.y;
		}
		if (w != NULL) {
			*w = rect.w;
		}
		if (h != NULL) {
			*h = rect.h;
		}
		return true;
	}
	return false;
}


// ******************** DisplayMode ********************
// *****************************************************

} // namespace sdx
