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
#ifndef GLSHADER_INL
#define GLSHADER_INL

#include "GLShader.hpp"

namespace opengl {

inline bool GLShader::operator==(const GLShader &other) const {
	return _id == other._id;
}

inline void GLShader::Create(ShaderType shaderType) {
	_id = glCreateShader((GLenum)shaderType);
}

inline void GLShader::Destroy() {
	glDeleteShader(_id);
	_id = 0;
}

inline int GLShader::Id() const {
	return _id;
}

inline ShaderType GLShader::Type() const {
	ShaderType _type = (ShaderType)0;
	glGetShaderiv(_id, GL_SHADER_TYPE, (int *)&_type);
	return _type;
}

inline bool GLShader::Exists() const {
	return _id != 0 && glIsShader(_id) != GL_FALSE;
}

inline void GLShader::GetVertexPrecision(ShaderPrecision format, int &min, int &max, int &precision) {
	int minMax[2] = { 0, 0 };
	precision = 0;
	glGetShaderPrecisionFormat(GL_VERTEX_SHADER, (GLenum)format, minMax, &precision);
	min = minMax[0];
	max = minMax[1];
}

inline void GLShader::GetFragmentPrecision(ShaderPrecision format, int &min, int &max, int &precision) {
	int minMax[2] = { 0, 0 };
	precision = 0;
	glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, (GLenum)format, minMax, &precision);
	min = minMax[0];
	max = minMax[1];
}

inline void GLShader::ReleaseCompiler() {
	glReleaseShaderCompiler();
}


} // namespace opengl
#endif // GLSHADER_INL