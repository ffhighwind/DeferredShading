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

#pragma once
#ifndef SDX_WINDOW_INL
#define SDX_WINDOW_INL

#include "SDX_Window.hpp"

namespace sdx {

// ********************* WINDOW SETTINGS ********************
// **********************************************************

inline void WindowSettings::SetFullscreen(bool fullscreen)
{
	if (fullscreen) {
		_flags |= SDL_WINDOW_FULLSCREEN;
	}
	else {
		_flags &= ~SDL_WINDOW_FULLSCREEN;
	}
}

inline bool WindowSettings::IsFullscreen() const
{
	return (_flags & SDL_WINDOW_FULLSCREEN) != 0;
}

inline void WindowSettings::SetDesktopFulscreen(bool desktopFullscreen)
{
	if (desktopFullscreen) {
		_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	else {
		_flags &= ~SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
}

inline bool WindowSettings::IsDesktopFullscreen() const
{
	return (_flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;
}

inline void WindowSettings::SetHidden(bool hidden)
{
	if (hidden) {
		_flags |= SDL_WINDOW_HIDDEN;
		_flags &= ~SDL_WINDOW_SHOWN;
	}
	else {
		_flags &= ~SDL_WINDOW_HIDDEN;
		_flags |= SDL_WINDOW_SHOWN;
	}
}

inline bool WindowSettings::IsHidden() const
{
	return (_flags & SDL_WINDOW_HIDDEN) != 0;
}

inline void WindowSettings::SetShown(bool shown)
{
	SetHidden(shown);
}

inline bool WindowSettings::IsShown() const
{
	return ((_flags & SDL_WINDOW_HIDDEN) == 0) || ((_flags & SDL_WINDOW_SHOWN) != 0);
}

inline void WindowSettings::SetBorderless(bool borderless)
{
	if (borderless) {
		_flags |= SDL_WINDOW_BORDERLESS;
	}
	else {
		_flags &= ~SDL_WINDOW_BORDERLESS;
	}
}

inline bool WindowSettings::IsBorderless() const
{
	return (_flags & SDL_WINDOW_BORDERLESS) != 0;
}

inline void WindowSettings::SetOpenGL(bool opengl)
{
	if (opengl) {
		_flags |= SDL_WINDOW_OPENGL;
	}
	else {
		_flags &= ~SDL_WINDOW_OPENGL;
	}
}

inline bool WindowSettings::IsOpenGL() const
{
	return (_flags & SDL_WINDOW_OPENGL) != 0;
}

inline void WindowSettings::SetResizable(bool resizable)
{
	if (resizable) {
		_flags |= SDL_WINDOW_RESIZABLE;
	}
	else {
		_flags &= ~SDL_WINDOW_RESIZABLE;
	}
}

inline bool WindowSettings::IsResizable() const
{
	return (_flags & SDL_WINDOW_RESIZABLE) != 0;
}

inline void WindowSettings::SetMinimized(bool minimized)
{
	if (minimized) {
		_flags |= SDL_WINDOW_MINIMIZED;
		_flags &= ~SDL_WINDOW_MAXIMIZED;
	}
	else {
		_flags &= ~SDL_WINDOW_MINIMIZED;
		_flags |= SDL_WINDOW_MAXIMIZED;
	}
}

inline bool WindowSettings::IsMinimized() const
{
	return (_flags & SDL_WINDOW_MINIMIZED) != 0;
}

inline void WindowSettings::SetMaximized(bool maximized)
{
	SetMinimized(!maximized);
}

inline bool WindowSettings::IsMaximized() const
{
	return (_flags & SDL_WINDOW_MAXIMIZED) != 0;
}

inline void WindowSettings::SetInputGrabbed(bool grabInput)
{
	if (grabInput) {
		_flags |= SDL_WINDOW_INPUT_GRABBED;
	}
	else {
		_flags &= ~SDL_WINDOW_INPUT_GRABBED;
	}
}

inline bool WindowSettings::IsInputGrabbed() const
{
	return (_flags & SDL_WINDOW_INPUT_GRABBED) != 0;
}

inline bool WindowSettings::HasMouseFocus() const
{
	return (_flags & SDL_WINDOW_MOUSE_FOCUS) != 0;
}

inline bool WindowSettings::HasInputFocus() const
{
	return (_flags & SDL_WINDOW_INPUT_FOCUS) != 0;
}

inline void WindowSettings::SetHighDPI(bool highdpi)
{
	if (highdpi) {
		_flags |= SDL_WINDOW_ALLOW_HIGHDPI;
	}
	else {
		_flags &= ~SDL_WINDOW_ALLOW_HIGHDPI;
	}
}

inline bool WindowSettings::IsHighDPI() const
{
	return (_flags & SDL_WINDOW_ALLOW_HIGHDPI) != 0;
}

inline bool WindowSettings::IsSDLWindow() const
{
	return (_flags & SDL_WINDOW_FOREIGN) != 0;
}

inline bool WindowSettings::IsAlwaysOnTop() const
{
	return (_flags & SDL_WINDOW_ALWAYS_ON_TOP) != 0;
}

inline bool WindowSettings::HasMouseCapture() const
{
	return (_flags & SDL_WINDOW_MOUSE_CAPTURE) != 0;
}

inline bool WindowSettings::IsPopupMenu() const
{
	return (_flags & SDL_WINDOW_POPUP_MENU) != 0;
}

inline bool WindowSettings::IsTooltip() const
{
	return (_flags & SDL_WINDOW_TOOLTIP) != 0;
}

inline bool WindowSettings::IsUtilityWindow() const
{
	return (_flags & SDL_WINDOW_UTILITY) != 0;
}

inline void WindowSettings::SetTaskbarDisabled(bool taskbar)
{
	if (taskbar) {
		_flags |= SDL_WINDOW_SKIP_TASKBAR;
	}
	else {
		_flags &= ~SDL_WINDOW_SKIP_TASKBAR;
	}
}

inline bool WindowSettings::IsTaskbarDisabled() const
{
	return (_flags & SDL_WINDOW_SKIP_TASKBAR) != 0;
}

inline Uint32 WindowSettings::GetFlags() const
{
	return _flags;
}

/************************** WINDOW ************************/
/**********************************************************/

inline Window::Window(Uint32 id)
{
	_win = SDL_GetWindowFromID(id);
}

inline bool Window::Create(const char *title, const WindowSettings &settings, int w, int h, int x, int y)
{
	_win = SDL_CreateWindow(title, x, y, w, h, settings.GetFlags());
	if (_win != nullptr && settings.IsOpenGL()) {
		CreateGLContext();
	}
	return _win != nullptr;
}

inline bool Window::Create(Uint32 windowID)
{
	_win = SDL_GetWindowFromID(windowID);
	return _win != nullptr;
}

inline void Window::Create(SDL_Window *win)
{
	_win = win;
}

inline bool Window::CreateGLContext()
{
	if (_glContext != nullptr) {
		return true;
	}
	_glContext = SDL_GL_CreateContext(_win);
	return _glContext != nullptr;
}

inline void Window::DestroyGLContext()
{
	SDL_GL_DeleteContext(_glContext);
}

inline void Window::Destroy()
{
	SDL_DestroyWindow(_win);
	SDL_GL_DeleteContext(_glContext);
	_glContext = nullptr;
	_win = nullptr;
}

inline bool Window::Exists() const
{
	return _win != nullptr && SDL_GetWindowID(_win) != 0;
}

inline void Window::Hide()
{
	SDL_HideWindow(_win);
}

inline bool Window::IsHidden() const
{
	return (SDL_GetWindowFlags(_win) & SDL_WINDOW_HIDDEN) != 0;
}

inline void Window::Show()
{
	SDL_ShowWindow(_win);
}

inline bool Window::IsShown() const
{
	return (SDL_GetWindowFlags(_win) & SDL_WINDOW_SHOWN) != 0;
}

inline void Window::Minimize()
{
	SDL_MinimizeWindow(_win);
}

inline bool Window::IsMinimized() const
{
	return (SDL_GetWindowFlags(_win) & SDL_WINDOW_MINIMIZED) != 0;
}

inline void Window::Maximize()
{
	SDL_MaximizeWindow(_win);
}

inline bool Window::IsMaximized() const
{
	return (SDL_GetWindowFlags(_win) & SDL_WINDOW_MAXIMIZED) != 0;
}

inline void Window::Restore() const
{
	SDL_RestoreWindow(_win);
}

inline void Window::SetResizable(bool resizable)
{
	SDL_SetWindowResizable(_win, (SDL_bool)resizable);
}

inline bool Window::IsResizable() const
{
	return (SDL_GetWindowFlags(_win) & SDL_WINDOW_RESIZABLE) != 0;
}

inline void Window::SetBorderless(bool borderless)
{
	SDL_SetWindowBordered(_win, (SDL_bool)!borderless);
}

inline bool Window::IsBorderless() const
{
	return (SDL_GetWindowFlags(_win) & SDL_WINDOW_BORDERLESS) != 0;
}

inline void Window::SetTitle(const char *title)
{
	SDL_SetWindowTitle(_win, title);
}

inline const char* Window::GetTitle() const
{
	return SDL_GetWindowTitle(_win);
}

inline void Window::SetFullscreen(bool fullscreen)
{
	if (fullscreen) {
		SDL_SetWindowFullscreen(_win, SDL_WINDOW_FULLSCREEN);
	}
	else {
		SDL_SetWindowFullscreen(_win, 0);
	}
}

inline bool Window::IsFullscreen() const
{
	return (SDL_GetWindowFlags(_win) & SDL_WINDOW_FULLSCREEN) != 0;
}

inline void Window::SetFullscreenDesktop(bool fullscreen)
{
	if (fullscreen) {
		SDL_SetWindowFullscreen(_win, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else {
		SDL_SetWindowFullscreen(_win, 0);
	}
}

inline bool Window::IsFullscreenDesktop() const
{
	return (SDL_GetWindowFlags(_win) & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0;
}

inline void Window::SetSize(int width, int height)
{
	SDL_SetWindowSize(_win, width, height);
}

inline void Window::GetSize(int *width, int *height) const
{
	SDL_GetWindowSize(_win, width, height);
}

inline void Window::SetMaximumSize(int width, int height)
{
	SDL_SetWindowMaximumSize(_win, width, height);
}

inline void Window::GetMaximumSize(int *width, int *height) const
{
	SDL_GetWindowMaximumSize(_win, width, height);
}

inline void Window::SetMinimumSize(int width, int height)
{
	SDL_SetWindowMinimumSize(_win, width, height);
}

inline void Window::GetMinimumSize(int *width, int *height) const
{
	SDL_GetWindowMinimumSize(_win, width, height);
}

inline bool Window::GetBorderSize(int *top, int *right, int *bottom, int *left) const
{
	return SDL_GetWindowBordersSize(_win, top, left, bottom, right) == 0;
}

inline void Window::GetDrawableSize(int *width, int *height)
{
	SDL_GL_GetDrawableSize(_win, width, height);
}

inline int Window::Width() const
{
	int width = 0;
	SDL_GetWindowSize(_win, &width, nullptr);
	return width;
}

inline int Window::Height() const
{
	int height = 0;
	SDL_GetWindowSize(_win, nullptr, &height);
	return height;
}

inline void Window::SetOpacity(float opacity)
{
	SDL_SetWindowOpacity(_win, opacity);
}

inline float Window::GetOpacity() const
{
	float opacityVal = 1.0f;
	SDL_GetWindowOpacity(_win, &opacityVal);
	return opacityVal;
}

inline bool Window::IsMouseFocused() const
{
	return (SDL_GetWindowFlags(_win) & SDL_WINDOW_MOUSE_FOCUS) != 0;
}

inline bool Window::IsInputFocused() const
{
	return (SDL_GetWindowFlags(_win) & SDL_WINDOW_INPUT_FOCUS) != 0;
}

inline bool Window::IsMouseCaptured() const
{
	return (SDL_GetWindowFlags(_win) & SDL_WINDOW_MOUSE_CAPTURE) != 0;
}

inline void Window::SetInputGrabbed(bool grab)
{
	SDL_SetWindowGrab(_win, (SDL_bool)grab);
}

inline bool Window::IsInputGrabbed() const
{
	return (SDL_GetWindowFlags(_win) & SDL_WINDOW_INPUT_GRABBED) != 0;
}

inline void Window::SetPosition(int x, int y)
{
	SDL_SetWindowPosition(_win, x, y);
}

inline void Window::GetPosition(int &x, int &y) const
{
	SDL_GetWindowPosition(_win, &x, &y);
}

inline int Window::X() const
{
	int xVal = 0;
	SDL_GetWindowPosition(_win, &xVal, nullptr);
	return xVal;
}

inline int Window::Y() const
{
	int yVal = 0;
	SDL_GetWindowPosition(_win, nullptr, &yVal);
	return yVal;
}

inline void Window::GetGammaRamp(Uint16 &r, Uint16 &g, Uint16 &b) const
{
	SDL_GetWindowGammaRamp(_win, &r, &g, &b);
}

inline void Window::SetGammaRamp(const Uint16 *r, const Uint16 *g, const Uint16 *b)
{
	SDL_SetWindowGammaRamp(_win, r, g, b);
}

inline float Window::GetBrightness() const
{
	return SDL_GetWindowBrightness(_win);
}

inline bool Window::SetBrightness(float brightness)
{
	return SDL_SetWindowBrightness(_win, brightness) == 0;
}

inline void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(_win);
}

inline Uint32 Window::Id() const
{
	return SDL_GetWindowID(_win);
}

inline PixelFormat Window::GetPixelFormat() const
{
	return (PixelFormat)SDL_GetWindowPixelFormat(_win);
}

inline void Window::ShowMessageBox(const char* title, const char* message, MessageBoxType flags)
{
	SDL_ShowSimpleMessageBox((Uint32)flags, title, message, _win);
}

inline SDL_Window * Window::GetWindow()
{
	return _win;
}

inline SDL_GLContext Window::GetGLContext()
{
	return _glContext;
}

inline Window Window::GetCurrentWindow()
{
	return Window(SDL_GL_GetCurrentWindow());
}


} // namespace sdx
#endif // SDX_WINDOW_INL