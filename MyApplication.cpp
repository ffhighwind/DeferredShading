/*
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

#include "MyApplication.hpp"
#include "GLShader.hpp"
#include <iostream>
#include <string>
#include <time.h>

#include "GLMatrix.hpp"

using opengl::GL;

const float PI_ = 3.14159265359f;

const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 30.0f;

namespace sdx {

void OnKeyPressCallback(sdx::Key k)
{
	if (k == sdx::Key::ESCAPE) {
		SDL_Quit();
		exit(EXIT_SUCCESS);
	}
}

void OnMotion(int x, int y, int dx, int dy)
{

}

void OnResizeCallback(sdx::Window win, int w, int h)
{
	// Protect against a divide by zero
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	GL.SetPerspective(glm::radians(60.0f), float(w), float(h), NEAR_PLANE, FAR_PLANE);
	win.SwapBuffers();
}

int MyApplication::Init(const char *title, const WindowSettings &settings, int w, int h)
{
	
	if (!sdx::Application::Init(title, settings, w, h)) {
		sdx::System::PrintError(__FILE__, __LINE__, "Error initializing SDL");
		return EXIT_FAILURE;
	}
	Mouse::HideCursor();

	Keyboard::OnPress = OnKeyPressCallback;
	Window::OnResize = OnResizeCallback;
	Mouse::OnMotion = OnMotion;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_CULL_FACE);
	//glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glShadeModel(GL_SMOOTH);

	_win.Maximize();
	OnResizeCallback(_win, _win.Width(), _win.Height());
	Mouse::SetPosition(_win, MOUSE_X_LOCK, MOUSE_Y_LOCK);
	Mouse::Update();

	_model1 = _modelLoader.Load(SPONZA_FILE, false, true);
	_model2 = _modelLoader.Load(LUCY_FILE, false);
	if (!_model1 || !_model2 || !_ds.Init(_win.Width(), _win.Height())) {
		return EXIT_FAILURE;
	}
	_ds.SetPerspective(NEAR_PLANE, FAR_PLANE);
	return EXIT_SUCCESS;
}

void MyApplication::Update(Uint32 ticks)
{
	float deltaTime = float(ticks);
	float moveSpeed = 1.0f;
	if (_win.IsInputFocused()) {
		// Compute new orientation
		horizontalAngle -= TURN_SPEED * (Mouse::X() - MOUSE_X_LOCK);
		verticalAngle -= TURN_SPEED * (Mouse::Y() - MOUSE_Y_LOCK);
		Mouse::SetPosition(_win, MOUSE_X_LOCK, MOUSE_Y_LOCK); // lock mouse to window

		if (horizontalAngle < 0.0f) {
			horizontalAngle += 2 * PI_;
		}
		else if (horizontalAngle > 2 * PI_) {
			horizontalAngle -= 2 * PI_;
		}
		if (verticalAngle < -PI_ * 0.47f) {
			verticalAngle = -PI_ * 0.47f;
		}
		else if (verticalAngle > PI_ * 0.47f) {
			verticalAngle = PI_ * 0.47f;
		}
	}

	// camera presets
	if (Keyboard::IsKeyPressed(Key::F1)) {
		position = glm::vec3(-0.16f, -2.0f, 6.666f);
		verticalAngle = 0.0000;
		horizontalAngle = PI_;
	}
	else if (Keyboard::IsKeyPressed(Key::F2)) {
		position = glm::vec3(-0.95f, 0.45f, 6.5f);
		verticalAngle = -0.175f;
		horizontalAngle = 2.95f;
	}
	else if (Keyboard::IsKeyPressed(Key::F3)) {
		position = glm::vec3(-0.16f, -2.0f, -6.1f);
		verticalAngle = -0.0f;
		horizontalAngle = 0.0f;
	}
	else if (Keyboard::IsKeyPressed(Key::F4)) {
		position = glm::vec3(2.7251f, -2.1234f, -6.0708f);
		verticalAngle = -0.0145f;
		horizontalAngle = 5.4352f;
	}
	else if (Keyboard::IsKeyPressed(Key::F5)) {
		position = glm::vec3(2.4234f, 0.2537f, -6.2569f);
		verticalAngle = -0.1485f;
		horizontalAngle = 5.8524f;
	}
	else if (Keyboard::IsKeyPressed(Key::F6)) {
		position = glm::vec3(0.0f, 5.15f, 0.45f);
		verticalAngle = -1.4665f;
		horizontalAngle = PI_ * 1.5f;
	}

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle));

	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 right = glm::cross(direction, up);

	// running (shift key)
	if (Keyboard::IsKeyDown(Key::LSHIFT) || Keyboard::IsKeyDown(Key::RSHIFT)) {
		moveSpeed = 3.0f;
	}
	// strafing (up down)
	if (Keyboard::IsKeyDown(Key::W)) {
		// Move forward
		position += direction * deltaTime * MOVE_SPEED * moveSpeed;
	}
	else if (Keyboard::IsKeyDown(Key::S)) {
		// Move backward
		position -= direction * deltaTime * MOVE_SPEED * moveSpeed;
	}
	// strafing (left right)
	if (Keyboard::IsKeyDown(Key::D)) {
		// Strafe right
		position += right * deltaTime * MOVE_SPEED * moveSpeed;
	}
	else if (Keyboard::IsKeyDown(Key::A)) {
		// Strafe left
		position -= right * deltaTime * MOVE_SPEED * moveSpeed;
	}

	GL.SetCamera(position, position + direction);

	// print buffers
	if (Keyboard::IsKeyDown(Key::P)) {
		int w, h;
		_win.GetSize(&w, &h);
		_ds.SaveFile(w, h);
	}
	// toggle rotating lights
	if (Keyboard::IsKeyPressed(Key::R)) {
		_ds.ToggleRotation();
	}
	// print camera position and direction
	if (Keyboard::IsKeyPressed(Key::O)) {
		printf("position = glm::vec3(%1.4f, %1.4f, %1.4f);\n", position.x, position.y, position.z);
		printf("verticalAngle = %1.4f;\n", verticalAngle);
		printf("horizontalAngle = %1.4f;\n", horizontalAngle);
	}
	// print camera position and direction
	if (Keyboard::IsKeyPressed(Key::L)) {
		unsigned int seed = time(0);
		printf("seed = %d\n", seed);
		_ds.RandomizeLights(seed);
	}

	// change shaders
	if (Keyboard::IsKeyPressed(Key::_1)) {
		_ds.SetDrawMode(DeferredBuffer::Deferred);
	}
	else if (Keyboard::IsKeyPressed(Key::_2)) {
		_ds.SetDrawMode(DeferredBuffer::Diffuse);
	}
	else if (Keyboard::IsKeyPressed(Key::_3)) {
		_ds.SetDrawMode(DeferredBuffer::Specular);
	}
	else if (Keyboard::IsKeyPressed(Key::_4)) {
		_ds.SetDrawMode(DeferredBuffer::Normal);
	}
	else if (Keyboard::IsKeyPressed(Key::_5)) {
		_ds.SetDrawMode(DeferredBuffer::Position);
	}
	else if (Keyboard::IsKeyPressed(Key::_6)) {
		_ds.SetDrawMode(DeferredBuffer::Depth);
	}
}


void MyApplication::Draw(Uint32 ticks)
{
	// Clear the screen
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GL.Identity();
	_ds.Render((float)ticks, *_model1, *_model2, position);
}

bool MyApplication::OnQuit() 
{
	return true;
}


} // namespace sdx