/*
* SDX Keyboard class
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

#include "SDX_Keyboard.hpp"

namespace sdx {

const Uint8 *Keyboard::_keyState = nullptr;
std::bitset<SDL_NUM_SCANCODES> Keyboard::_keyChanged;
std::function<void(Key key)> Keyboard::OnPress;
std::function<void(Key key)> Keyboard::OnRelease;

bool Keyboard::HandleEvent(const SDL_Event &e)
{
	if(e.type == SDL_KEYDOWN) {
		_keyChanged[(int)(e.key.keysym.scancode)] = true;
		if (OnPress != nullptr) {
			OnPress((Key)(e.key.keysym.scancode));
		}
	}
	else if (e.type == SDL_KEYUP) {
		_keyChanged[(int)(e.key.keysym.scancode)] = true;
		if (OnRelease != nullptr) {
			OnRelease((Key)(e.key.keysym.scancode));
		}
	}
	else {
		return false;
	}
	return true;
}


} // namespace sdx