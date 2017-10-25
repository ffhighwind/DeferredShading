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
#ifndef SDX_MOUSE_HPP
#define SDX_MOUSE_HPP

#include <SDL_mouse.h>
#include <SDL_events.h>
#include <vector>
#include <bitset>
#include <functional>

#include "SDX_Window.hpp"

namespace sdx {

enum class MouseButton
{
	LEFT = SDL_BUTTON_LEFT,
	MIDDLE = SDL_BUTTON_MIDDLE,
	RIGHT = SDL_BUTTON_RIGHT,
	X1 = SDL_BUTTON_X1,
	X2 = SDL_BUTTON_X2,
};

class Mouse
{
public:
	// Updates the mouse state and prepares it for handling events.
	// Call this once per SDL_PumpEvents.
	static void Update();
	// Updates the relative mouse state and calls the event callbacks.
	static bool HandleEvent(const SDL_Event &e);

	// Returns the current mouse position.
	static void GetPosition(int &x, int &y);
	// Returns the current X position.
	static int X();
	// Returns the current Y position.
	static int Y();
	// Returns the current mouse position in screen space.
	static void GetScreenPosition(int &x, int &y);
	// Returns the current X position in screen space.
	static int XScreen();
	// Returns the current Y position in screen space.
	static int YScreen();
	//  Returns the relative change in the X position.
	static int DX();
	// Returns the relative change in the Y position.
	static int DY();
	// Returns the total sum of the recent scroll events.
	static int Wheel();
	// Warp the mouse position to a globally defined position.
	static void SetPosition(int x, int y);
	// Warp the mouse position to a relative position within a window.
	static void SetPosition(sdx::Window win, int relX, int relY);
	// Returns whether a mouse button is currently being pressed.
	static bool IsButtonDown(MouseButton button);
	// Returns whether a mouse button was pressed recently.
	static bool IsButtonPressed(MouseButton button);
	// Returns whether a mouse button was released recently.
	static bool IsButtonReleased(MouseButton button);
	// Toggle whether or not the cursor is shown.
	static void ShowCursor(bool isShown=true);
	static void HideCursor();
	// Returns whether or not the cursor is shown.
	static bool IsCursorShown();
	// Obtains mouse events globally, instead of just within your window. 
	// Not all video targets support this function. When capturing is enabled, the current window will get 
	// all mouse events, but unlike relative mode, no change is made to the cursor and it is not restrained to your window.
	// It is not recommended that you capture the mouse for long periods of time.
	// While captured, mouse events still report coordinates relative to the current (foreground) window, 
	// Capturing is only allowed for the foreground window. If the window loses focus while capturing, 
	// the capture will be disabled automatically.
	static bool Capture(bool isCaptured=true);
	// Returns the window which currently has mouse focus.
	static sdx::Window GetFocusWindow();

	// Event handler callbacks for mouse button presses (nullptr to disable)
	static std::function<void(MouseButton button)> OnPress;
	static std::function<void(MouseButton button)> OnRelease;
	static std::function<void(int x, int y, int dx, int dy)> OnMotion;
	static std::function<void(int direction)> OnWheel;

private:
	Mouse() { } // static class
	enum { NUMBUTTONS = 8 }; // last button number + 1
	static int _x, _y; // relative mouse position
	static int _gx, _gy; // global mouse position
	static int _dx, _dy; // mouse movement since update
	static int _wheel;
	static std::bitset<32> _buttonChanged; // Buttons start from 1
	static Uint32 _buttonState;
};


} // namespace sdx
#include "SDX_Mouse.inl"
#endif // SDX_MOUSE_HPP

/*
enum class MouseCursor
{
ARROW = SDL_SYSTEM_CURSOR_ARROW,
IBEAM = SDL_SYSTEM_CURSOR_IBEAM,
WAIT = SDL_SYSTEM_CURSOR_WAIT,
CROSSHAIR = SDL_SYSTEM_CURSOR_CROSSHAIR,
WAITARROW = SDL_SYSTEM_CURSOR_WAITARROW, // Small wait cursor (or Wait if not available)
SIZENWSE = SDL_SYSTEM_CURSOR_SIZENWSE,  // Double arrow pointing northwest and southeast
SIZENESW = SDL_SYSTEM_CURSOR_SIZENESW,  // Double arrow pointing northeast and southwest
SIZEEWE = SDL_SYSTEM_CURSOR_SIZEWE,    // Double arrow pointing west and east
SIZENS = SDL_SYSTEM_CURSOR_SIZENS,    // Double arrow pointing north and south
SIZEALL = SDL_SYSTEM_CURSOR_SIZEALL,   // Four pointed arrow pointing north, south, east, and west
NO = SDL_SYSTEM_CURSOR_NO,        // Slashed circle or crossbones
HAND = SDL_SYSTEM_CURSOR_HAND,
NUM_CURSORS = SDL_NUM_SYSTEM_CURSORS
};

enum class MouseWheelDirection
{
NORMAL = SDL_MOUSEWHEEL_NORMAL,    // The scroll direction is normal
FLIPPED = SDL_MOUSEWHEEL_FLIPPED    // The scroll direction is flipped / natural
};
*/