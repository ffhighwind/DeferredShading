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
#ifndef SDX_WINDOW_HPP
#define SDX_WINDOW_HPP

#include <SDL_messagebox.h>
#include <SDL_video.h>
#include <SDL_events.h>
#include <vector>
#include <functional>

#ifdef ERROR
#undef ERROR
#endif

namespace sdx {

class VideoDisplay;
class DisplayMode;
enum class PixelFormat : Uint32;

enum class MessageBoxType
{
	ERROR = SDL_MESSAGEBOX_ERROR,
	WARNING = SDL_MESSAGEBOX_WARNING,
	INFO = SDL_MESSAGEBOX_INFORMATION
};

struct WindowSettings
{
protected:
	Uint32 _flags;
public:
	WindowSettings(Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN) {
		this->_flags = flags;
	}
	void SetFullscreen(bool fullscreen);
	bool IsFullscreen() const;
	void SetDesktopFulscreen(bool desktopFullscreen);
	bool IsDesktopFullscreen() const;
	void SetHidden(bool hidden = true);
	bool IsHidden() const;
	void SetShown(bool shown);
	bool IsShown() const;
	void SetBorderless(bool borderless);
	bool IsBorderless() const;
	void SetOpenGL(bool opengl);
	bool IsOpenGL() const;
	void SetResizable(bool resizable);
	bool IsResizable() const;
	void SetMinimized(bool minimized);
	bool IsMinimized() const;
	void SetMaximized(bool maximized);
	bool IsMaximized() const;
	void SetInputGrabbed(bool grabInput);
	bool IsInputGrabbed() const;
	bool HasMouseFocus() const;
	bool HasInputFocus() const;
	void SetHighDPI(bool highdpi);
	bool IsHighDPI() const;
	bool IsSDLWindow() const;
	bool IsAlwaysOnTop() const;
	bool HasMouseCapture() const;
	bool IsPopupMenu() const;
	bool IsTooltip() const;
	bool IsUtilityWindow() const;
	void SetTaskbarDisabled(bool taskbar);
	bool IsTaskbarDisabled() const;
	Uint32 GetFlags() const;
};


class Window
{
protected:
	SDL_Window *_win;
	SDL_GLContext _glContext;

public:
	Window() : _win(nullptr), _glContext(nullptr) { }
	Window(Uint32 id);
	Window(SDL_Window *win) : _win(win), _glContext(nullptr) {}
	Window(const Window &win) : _win(win._win), _glContext(nullptr) {}

	static bool HandleEvent(const SDL_Event &e);
	// Event handler callbacks for mouse button presses (nullptr to disable)
	static std::function<void(Window win)> OnShow;
	static std::function<void(Window win)> OnHide;
	static std::function<void(Window win)> OnRestore;
	static std::function<void(Window win)> OnEnter;
	static std::function<void(Window win)> OnLeave;
	static std::function<void(Window win)> OnFocusGained;
	static std::function<void(Window win)> OnFocusLost;
	static std::function<void(Window win)> OnClose;
	static std::function<void(Window win)> OnExpose;
	static std::function<void(Window win, int x, int y)> OnMove;
	static std::function<void(Window win, int w, int h)> OnResize;
	static std::function<void(Window win, int w, int h)> OnSizeChanged;
	static std::function<void(Window win)> OnMaximize;
	static std::function<void(Window win)> OnMinimize;
	static std::function<void(Window win)> OnFocusTaken;
	static std::function<void(Window win)> OnHitTest;

	bool Create(const char *title, const WindowSettings &settings, int w = 640, int h = 480,
		int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED);
	bool Create(Uint32 windowID);
	void Create(SDL_Window *win);
	bool CreateGLContext();
	void DestroyGLContext();
	void Destroy();
	bool Exists() const;
	void Hide();
	bool IsHidden() const;
	void Show();
	bool IsShown() const;
	void Minimize();
	bool IsMinimized() const;
	void Maximize();
	bool IsMaximized() const;
	void Restore() const;
	void SetResizable(bool resizable=true);
	bool IsResizable() const;
	void SetBorderless(bool borderless = true);
	bool IsBorderless() const;
	void SetTitle(const char *title);
	const char *GetTitle() const;
	void SetFullscreen(bool fullscreen=true);
	bool IsFullscreen() const;
	void SetFullscreenDesktop(bool fullscreen = true);
	bool IsFullscreenDesktop() const;
	void SetSize(int width, int height);
	void GetSize(int *width, int *height) const;
	void SetMaximumSize(int width, int height);
	void GetMaximumSize(int *width, int *height) const;
	void SetMinimumSize(int width, int height);
	void GetMinimumSize(int *width, int *height) const;
	bool GetBorderSize(int *top, int *right, int *bottom, int *left) const;
	void GetDrawableSize(int *width, int *height);
	int Width() const;
	int Height() const;
	void SetOpacity(float opacity);
	float GetOpacity() const;
	bool IsMouseFocused() const;
	bool IsInputFocused() const;
	void SetInputGrabbed(bool grab);
	bool IsInputGrabbed() const;
	bool IsMouseCaptured() const;
	void SetPosition(int x, int y);
	void GetPosition(int &x, int &y) const;
	int X() const;
	int Y() const;
	void SwapBuffers();
	void GetGammaRamp(Uint16 &r, Uint16 &g, Uint16 &b) const;
	void SetGammaRamp(const Uint16 *r, const Uint16 *g, const Uint16 *b);
	float GetBrightness() const;
	bool SetBrightness(float brightness);
	void ShowMessageBox(const char* title, const char* message, MessageBoxType flags = MessageBoxType::ERROR);
	Uint32 Id() const;
	SDL_Window *GetWindow();
	SDL_GLContext GetGLContext();
	bool SetDisplayMode(DisplayMode mode);
	DisplayMode GetDisplayMode() const;
	PixelFormat GetPixelFormat() const;

	static Window GetCurrentWindow();
};


} // namespace sdx
#include "SDX_Window.inl"
#endif // SDX_WINDOW_HPP