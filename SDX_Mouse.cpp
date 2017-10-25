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

#include "SDX_Mouse.hpp"

namespace sdx {

int Mouse::_x = 0;
int Mouse::_y = 0;
int Mouse::_dx = 0;
int Mouse::_dy = 0;
int Mouse::_gx = 0;
int Mouse::_gy = 0;
int Mouse::_wheel = 0;
Uint32 Mouse::_buttonState = 0;
std::bitset<32> Mouse::_buttonChanged;

std::function<void(MouseButton button)> Mouse::OnPress = nullptr;
std::function<void(MouseButton button)> Mouse::OnRelease = nullptr;
std::function<void(int x, int y, int dx, int dy)> Mouse::OnMotion = nullptr;
std::function<void(int direction)> Mouse::OnWheel = nullptr;

void Mouse::Update()
{
	int oldX = _x;
	int oldY = _y;
	SDL_GetMouseState(&_x, &_y);
	_buttonState = SDL_GetGlobalMouseState(&_gx, &_gy);
	_dx = oldX - _x;
	_dy = oldY - _y;
	_wheel = 0;
	_buttonChanged.reset();
}

bool Mouse::HandleEvent(const SDL_Event &e)
{
	switch(e.type) {
		case SDL_MOUSEMOTION:
			if (OnMotion != nullptr){
				OnMotion(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
			}
			break;
		case SDL_MOUSEWHEEL:
			_wheel += e.wheel.direction;
			if (OnWheel != nullptr) {
				OnWheel(e.wheel.direction);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			_buttonChanged[e.button.button] = true;
			if (OnPress != nullptr) {
				OnPress((MouseButton)e.button.button);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			_buttonChanged[e.button.button] = true;
			if (OnRelease != nullptr) {
				OnRelease((MouseButton)e.button.button);
			}
			break;
		default:
			return false;
	}
	return true;
}

void Mouse::SetPosition(int x, int y)
{
	SDL_WarpMouseGlobal(x, y);
	int oldX = _x;
	int oldY = _y;
	_buttonState = SDL_GetMouseState(&_x, &_y);
	_dx += oldX - _x;
	_dy += oldY - _y;
}

void Mouse::SetPosition(sdx::Window win, int relX, int relY)
{
	SDL_WarpMouseInWindow(win.GetWindow(), relX, relY);
	int oldX = _x;
	int oldY = _y;
	_buttonState = SDL_GetMouseState(&_x, &_y);
	_dx += oldX - _x;
	_dy += oldY - _y;
}

} // namespace sdx