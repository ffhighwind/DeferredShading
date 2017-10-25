/*
* SDX Window class
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

namespace sdx
{

std::function<void(Window win)> Window::OnShow = nullptr;
std::function<void(Window win)> Window::OnHide = nullptr;
std::function<void(Window win)> Window::OnRestore = nullptr;
std::function<void(Window win)> Window::OnEnter = nullptr;
std::function<void(Window win)> Window::OnLeave = nullptr;
std::function<void(Window win)> Window::OnFocusGained = nullptr;
std::function<void(Window win)> Window::OnFocusLost = nullptr;
std::function<void(Window win)> Window::OnClose = nullptr;
std::function<void(Window win)> Window::OnExpose = nullptr;
std::function<void(Window win, int x, int y)> Window::OnMove = nullptr;
std::function<void(Window win, int w, int h)> Window::OnResize = nullptr;
std::function<void(Window win, int w, int h)> Window::OnSizeChanged = nullptr;
std::function<void(Window win)> Window::OnMaximize = nullptr;
std::function<void(Window win)> Window::OnMinimize = nullptr;
std::function<void(Window win)> Window::OnFocusTaken = nullptr;
std::function<void(Window win)> Window::OnHitTest = nullptr;


/************************** WINDOW ************************/
/**********************************************************/

bool Window::HandleEvent(const SDL_Event &e)
{
	if (e.type == SDL_WINDOWEVENT) {
		switch (e.window.event) {
		case SDL_WINDOWEVENT_SHOWN:
			if (OnShow != nullptr) {
				OnShow(Window(e.window.windowID));
			}
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			if (OnHide != nullptr) {
				OnHide(Window(e.window.windowID));
			}
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			if (OnExpose != nullptr) {
				OnExpose(Window(e.window.windowID));
			}
			break;
		case SDL_WINDOWEVENT_MOVED:
			if (OnMove != nullptr) {
				OnMove(Window(e.window.windowID), e.window.data1, e.window.data2);
			}
			break;
		case SDL_WINDOWEVENT_RESIZED:
			if (OnResize != nullptr) {
				OnResize(Window(e.window.windowID), e.window.data1, e.window.data2);
			}
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			if (OnSizeChanged != nullptr) {
				OnSizeChanged(Window(e.window.windowID), e.window.data1, e.window.data2);
			}
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			if (OnMinimize != nullptr) {
				OnMinimize(Window(e.window.windowID));
			}
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			if (OnMaximize != nullptr) {
				OnMaximize(Window(e.window.windowID));
			}
			break;
		case SDL_WINDOWEVENT_RESTORED:
			if (OnRestore != nullptr) {
				OnRestore(Window(e.window.windowID));
			}
			break;
		case SDL_WINDOWEVENT_ENTER:
			if (OnEnter != nullptr) {
				OnEnter(Window(e.window.windowID));
			}
			break;
		case SDL_WINDOWEVENT_LEAVE:
			if (OnLeave != nullptr) {
				OnLeave(Window(e.window.windowID));
			}
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			if (OnFocusGained != nullptr) {
				OnFocusGained(Window(e.window.windowID));
			}
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			if (OnFocusLost != nullptr) {
				OnFocusLost(Window(e.window.windowID));
			}
			break;
		case SDL_WINDOWEVENT_CLOSE:
			if (OnClose != nullptr) {
				OnClose(Window(e.window.windowID));
			}
			break;
		case SDL_WINDOWEVENT_TAKE_FOCUS:
			if (OnFocusTaken != nullptr) {
				OnFocusTaken(Window(e.window.windowID));
			}
			break;
		case SDL_WINDOWEVENT_HIT_TEST:
			if (OnHitTest != nullptr) {
				OnHitTest(Window(e.window.windowID));
			}
			break;
		default:
			break;
		}
		return true;
	}
	return false;
}

bool Window::SetDisplayMode(DisplayMode mode)
{
	return SDL_SetWindowDisplayMode(_win, &mode._mode) == 0;
}

DisplayMode Window::GetDisplayMode() const
{
	SDL_DisplayMode mode;
	SDL_SetWindowDisplayMode(_win, &mode);
	return DisplayMode(mode);
}

} // namespace sdx