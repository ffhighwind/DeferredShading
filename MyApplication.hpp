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

#pragma once
#ifndef SDX_MYAPPLICATION_H
#define SDX_MYAPPLICATION_H

#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/GLU.h>
#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SDX_Application.hpp"
#include "SDX_Window.hpp"
#include "SDX_System.hpp"
#include "SDX_Keyboard.hpp"
#include "SDX_Mouse.hpp"

#include "GLProgram.hpp"
#include "GLModel.hpp"
#include "GLModelLoader.hpp"
#include "DeferredShader.hpp"

namespace sdx {


class MyApplication
	: public sdx::Application
{
public:
	int Init(const char *title, const WindowSettings &settings=WindowSettings(), int w=640, int h=480);

protected:
	opengl::GLProgram _p;
	opengl::GLModel *_model1, *_model2;
	opengl::GLModelLoader _modelLoader;
	DeferredShader _ds;

	const std::string SPONZA_FILE = ".\\models\\sponza\\sponza.obj";
	const std::string LUCY_FILE = ".\\models\\lucy.obj";
	const float MOVE_SPEED = 0.002f;
	const float TURN_SPEED = 0.002f;
	const int MOUSE_X_LOCK = 150;
	const int MOUSE_Y_LOCK = 150;

	float horizontalAngle = 2.85f;
	float verticalAngle = -0.35f;
	glm::vec3 position = glm::vec3(0.0f, -0.7f, 4.5f);

	void Update(Uint32 ticks);
	void Draw(Uint32 ticks);
	bool OnEvent(const SDL_Event &e) { return false; }
	bool OnQuit();
	void OnCustomEvent(const SDL_Event &e) { }
};


} // namespace sdx
#endif // SDX_MYAPPLICATION_H