/*
* GLShader class for OpenGL 4.3
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
#ifndef GLSHADER_HPP
#define GLSHADER_HPP

#include <GL/glew.h>
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>

namespace opengl {

enum class ShaderType
{
	INVALID = 0,
	VERTEX = GL_VERTEX_SHADER,
	FRAGMENT = GL_FRAGMENT_SHADER,
	GEOMETRY = GL_GEOMETRY_SHADER,
	TESS_CONTROL = GL_TESS_CONTROL_SHADER,
	TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
	COMPUTE = GL_COMPUTE_SHADER,
};

enum class ShaderPrecision
{
	LOW_FLOAT = GL_LOW_FLOAT,
	MEDIUM_FLOAT = GL_MEDIUM_FLOAT,
	HIGH_FLOAT  = GL_HIGH_FLOAT,
	LOW_INT = GL_LOW_INT,
	MEDIUM_INT = GL_MEDIUM_INT,
	HIGH_INT = GL_HIGH_INT,
};

class GLShader
{
protected:
	int _id;

public:
	GLShader() : _id(0) { }
	GLShader(int id) : _id(id) { }
	bool operator==(const GLShader &other) const;
	void Create(ShaderType shaderType);
	// An attached shader will continue to exist, even when destroyed
	// until it is no longer attached to any program.
	void Destroy();
	int Id() const;
	// Does a fast check and hard validation.
	bool Exists() const;
	ShaderType Type() const;
	bool CompileFile(const std::string &path);
	bool CompileStream(std::istream &input);
	bool CompileString(const char *source_str);
	// Error message for compile failure.
	std::string GetInfoLog() const;
	std::string GetSource() const;
	// All returned values are the floor(log2(|x|)) of the actual value.
	static void GetVertexPrecision(ShaderPrecision format, int &min, int &max, int &precision);
	// All returned values are the floor(log2(|x|)) of the actual value.
	static void GetFragmentPrecision(ShaderPrecision format, int &minVal, int &maxVal, int &precision);
	// Hints to OpenGL to free the shader compiler from memory.
	// It will be re-enabled and initialized the next time a shader is compiled.
	static void ReleaseCompiler();
	// glShaderBinary() //only for OpenGL ES
};


} // namespace opengl
#include "GLShader.inl"
#endif // GLSHADER_HPP