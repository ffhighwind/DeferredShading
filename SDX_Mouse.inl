/*
* SDX Mouse class
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
#ifndef SDX_MOUSE_INL
#define SDX_MOUSE_INL

#include "SDX_Mouse.hpp"

namespace sdx {

inline void Mouse::GetPosition(int &x, int &y)
{
	x = _x;
	y = _y;
}

inline int Mouse::X()
{
	return _x;
}

inline int Mouse::Y()
{
	return _y;
}

inline void Mouse::GetScreenPosition(int &x, int &y)
{
	x = _gx;
	y = _gy;
}

inline int Mouse::XScreen()
{
	return _gx;
}

inline int Mouse::YScreen()
{
	return _gy;
}

inline int Mouse::DX()
{
	return _dx;
}

inline int Mouse::DY()
{
	return _dy;
}

inline int Mouse::Wheel()
{
	return _wheel;
}

inline bool Mouse::IsButtonDown(MouseButton button)
{
	return (_buttonState & SDL_BUTTON((int)button)) != 0;
}

inline bool Mouse::IsButtonPressed(MouseButton button)
{
	return IsButtonDown(button) && _buttonChanged[(int)button];
}

inline bool Mouse::IsButtonReleased(MouseButton button)
{
	return !IsButtonDown(button) && _buttonChanged[(int)button];
}

inline void Mouse::ShowCursor(bool isShown)
{
	SDL_ShowCursor(isShown);
}

inline void Mouse::HideCursor()
{
	SDL_ShowCursor(false);
}

inline bool Mouse::IsCursorShown()
{
	return SDL_ShowCursor(SDL_QUERY) != 0;
}

inline bool Mouse::Capture(bool isCaptured)
{
	return SDL_CaptureMouse((SDL_bool)isCaptured) == 0;
}

inline sdx::Window Mouse::GetFocusWindow()
{
	SDL_Window *win = SDL_GetMouseFocus();
	return sdx::Window(win);
}


} // namespace sdx
#endif // SDX_MOUSE_INL