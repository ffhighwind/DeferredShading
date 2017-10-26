/*
* Uniform class for OpenGL 4.3
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
#ifndef GLUNIFORM_HPP
#define GLUNIFORM_HPP

#include <GL\glew.h>
#include <glm\glm.hpp>

namespace opengl {

// Uniforms are constant variables in a Shader program. These include 
// Uniform Primitives, Vectors, Matrices, Samplers, Subroutine Uniforms, etc.
struct GLUniform
{
protected:
	int _loc;
	int _program;

public:
	GLUniform(int programId, int location) 
		: _program(programId), _loc(location) { }
	bool operator==(const GLUniform &other) const;
	void SetProgram(int programId);
	void SetLocation(int location);
	int GetLocation() const;
	int GetProgram() const;
	// Does a fast check and hard validation.
	bool Exists() const;

	//Int
	// If the Uniform is a Sampler then this value must be the texture unit number.
	void Set(int value);
	void Set(int value1, int value2);
	void Set(int value1, int value2, int value3);
	void Set(int value1, int value2, int value3,
		int value4);
	//UInt
	void Set(unsigned value);
	void Set(unsigned value1, unsigned value2);
	void Set(unsigned value1, unsigned value2, unsigned value3);
	void Set(unsigned value1, unsigned value2, unsigned value3, unsigned value4);
	//Float
	void Set(float value);
	void Set(float value1, float value2);
	void Set(float value1, float value2, float value3);
	void Set(float value1, float value2, float value3, float value4);
	void Set(const glm::vec2 &value);
	void Set(const glm::vec3 &value);
	void Set(const glm::vec4 &value);

	/*********************** VECTORS ************************/

	//IntegerV
	void Vec1(int count, const int *values);
	void Vec2(int count, const int *values);
	void Vec3(int count, const int *values);
	void Vec4(int count, const int *values);
	//UIntV
	void Vec1(int count, const unsigned *values);
	void Vec2(int count, const unsigned *values);
	void Vec3(int count, const unsigned *values);
	void Vec4(int count, const unsigned *values);
	//FloatV
	void Vec1(int count, const float *values);
	void Vec2(int count, const float *values);
	void Vec3(int count, const float *values);
	void Vec4(int count, const float *values);

	/************************ MATRICES ***********************/

	//Matrix
	void Mat2(const float *values, bool transpose=false);
	void Mat3(const float *values, bool transpose=false);
	void Mat4(const float *values, bool transpose=false);
	void Mat2x3(const float *values, bool transpose=false);
	void Mat3x2(const float *values, bool transpose=false);
	void Mat2x4(const float *values, bool transpose=false);
	void Mat4x2(const float *values, bool transpose=false);
	void Mat3x4(const float *values, bool transpose=false);
	void Mat4x3(const float *values, bool transpose=false);
	//MatrixV
	void Mat2v(int count, const float *values, bool transpose=false);
	void Mat3v(int count, const float *values, bool transpose=false);
	void Mat4v(int count, const float *values, bool transpose=false);
	void Mat2x3v(int count, const float *values, bool transpose=false);
	void Mat3x2v(int count, const float *values, bool transpose=false);
	void Mat2x4v(int count, const float *values, bool transpose=false);
	void Mat4x2v(int count, const float *values, bool transpose=false);
	void Mat3x4v(int count, const float *values, bool transpose=false);
	void Mat4x3v(int count, const float *values, bool transpose=false);
};

// Bound Uniform (same functionality as above)
// Applies to bound uniforms and requires less memory.
struct GLUniformB
{
protected:
	int _loc;

public:
	GLUniformB() 
		: _loc(-1) { }
	GLUniformB(int location)
		: _loc(location) { }
	bool operator==(const GLUniformB &other) const;
	void SetLocation(int location);
	int GetLocation() const;
	// Does a fast check and hard validation.
	bool Exists() const;

	//Int
	// If the Uniform is a Sampler then this value must be the texture unit number.
	void Set(int value);
	void Set(int value1, int value2);
	void Set(int value1, int value2, int value3);
	void Set(int value1, int value2, int value3,
		int value4);
	//UInt
	void Set(unsigned value);
	void Set(unsigned value1, unsigned value2);
	void Set(unsigned value1, unsigned value2, unsigned value3);
	void Set(unsigned value1, unsigned value2, unsigned value3, unsigned value4);
	//Float
	void Set(float value);
	void Set(float value1, float value2);
	void Set(float value1, float value2, float value3);
	void Set(float value1, float value2, float value3, float value4);

	/*********************** VECTORS ************************/

	//IntegerV
	void Vec1(int count, const int *values);
	void Vec2(int count, const int *values);
	void Vec3(int count, const int *values);
	void Vec4(int count, const int *values);
	//UIntV
	void Vec1(int count, const unsigned *values);
	void Vec2(int count, const unsigned *values);
	void Vec3(int count, const unsigned *values);
	void Vec4(int count, const unsigned *values);
	//FloatV
	void Vec1(int count, const float *values);
	void Vec2(int count, const float *values);
	void Vec3(int count, const float *values);
	void Vec4(int count, const float *values);

	/************************ MATRICES ***********************/

	//Matrix
	void Mat2(const float *values, bool transpose=false);
	void Mat3(const float *values, bool transpose=false);
	void Mat4(const float *values, bool transpose=false);
	void Mat2x3(const float *values, bool transpose=false);
	void Mat3x2(const float *values, bool transpose=false);
	void Mat2x4(const float *values, bool transpose=false);
	void Mat4x2(const float *values, bool transpose=false);
	void Mat3x4(const float *values, bool transpose=false);
	void Mat4x3(const float *values, bool transpose=false);
	//MatrixV
	void Mat2v(int count, const float *values, bool transpose=false);
	void Mat3v(int count, const float *values, bool transpose=false);
	void Mat4v(int count, const float *values, bool transpose=false);
	void Mat2x3v(int count, const float *values, bool transpose=false);
	void Mat3x2v(int count, const float *values, bool transpose=false);
	void Mat2x4v(int count, const float *values, bool transpose=false);
	void Mat4x2v(int count, const float *values, bool transpose=false);
	void Mat3x4v(int count, const float *values, bool transpose=false);
	void Mat4x3v(int count, const float *values, bool transpose=false);
};


} // namespace opengl
#include "GLUniform.inl"
#endif // GLUNIFORM_HPP