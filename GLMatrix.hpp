/*
* GLMatrix class for OpenGL 4.3
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
#ifndef GLMATRIX_H
#define GLMATRIX_H

#include <GL\glew.h>
#include <vector> // for matrix stack
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace opengl {

class GLMatrix;
extern GLMatrix GL;

class GLMatrix
{
private:
	glm::mat4 _modelMatrix;
	glm::mat4 _viewMatrix;
	glm::mat4 _projMatrix;
	glm::mat3 _normalMatrix; // inverse transpose of the model matrix
	GLuint _modelLoc, _viewLoc, _projLoc, _normalLoc;
	std::vector<glm::mat4 *> _matrixStack;

public:
	GLMatrix();

	// Methods
	void SetUniforms(GLuint modelLoc, GLuint viewLoc, GLuint projLoc, GLuint normalLoc = 0);
	void Bind();
	void BindModelViewProj();
	void BindModelMatrix();
	void BindViewMatrix();
	void BindProjMatrix();
	void BindNormalMatrix();
	void BuildNormalMatrix();
	const glm::mat4 &ModelMatrix() const;
	const glm::mat4 &ViewMatrix() const;
	const glm::mat4 &ProjMatrix () const;
	const glm::mat4 &NormalMatrix() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetDirection() const;
	void GetCamera(glm::vec3 &position, glm::vec3 &direction) const;
	void Push();
	void Pop();
	void Identity();
	void Mult(const float *mat4x4);
	void Mult(const glm::mat4 &mat4x4);
	void Translate(float x, float y, float z);
	void Translate(const float *vec3);
	void Translate(const glm::vec3 &vec3);
	void Rotate(float radians, float x, float y, float z);
	void Rotate(float radians, const float *scalars);
	void Rotate(float radians, const glm::vec3 &scalars);
	void RotateDeg(float degrees, float x, float y, float z);
	void RotateDeg(float degrees, const float *axis);
	void RotateDeg(float degrees, const glm::vec3 &axis);
	void Scale(float scalar);
	void Scale(float x, float y, float z);
	void Scale(const float *scalars);
	void Scale(const glm::vec3 &scalars);

	// View Matrix
	void SetCamera(float posX, float posY, float posZ,
		float lookAtX, float lookAtY, float lookAtZ);
	void SetCamera(float posX, float posY, float posZ,
		float lookAtX, float lookAtY, float lookAtZ, float upX, float upY, float upZ);
	void SetCamera(const float *pos, const float *dir);
	void SetCamera(const float *pos, const float *dir, const float *up);
	void SetCamera(const glm::vec3 &pos, const glm::vec3 &dir);
	void SetCamera(const glm::vec3 &pos, const glm::vec3 &dir, const glm::vec3 &up);

	// Projection Matrix
	void SetPerspective(float fovDegrees, float aspectRatio, float nearPlane, float farPlane);
	void SetPerspective(float fovDegrees, float width, float height, float nearPlane, float farPlane);
	void SetInfinitePerspective(float fovDegrees, float aspectRatio, float nearPlane);
	void SetInfinitePerspective(float fovDegrees, float width, float height, float nearPlane);
	void SetOrtho(float left, float right, float bottom, float top, float nearPlane, float farPlane);
	void SetOrtho(float width, float height, float nearplane, float farplane);
};


} // namespace opengl
#include "GLMatrix.inl"
#endif // GLMATRIX_H