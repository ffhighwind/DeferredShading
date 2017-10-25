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

#include "GLShader.hpp"

namespace opengl
{

bool GLShader::CompileFile(const std::string &path) {
	std::ifstream input(path, std::ios::in | std::ios::binary);
	if (input.fail())
		return false;
	return CompileStream(input);
}

bool GLShader::CompileStream(std::istream &input) {
	std::string source = std::string(std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>());
	const char *source_str = source.c_str();

	return CompileString(source_str);
}

bool GLShader::CompileString(const char *source_str) {
	glShaderSource(_id, 1, &source_str, NULL); // NULL terminated string
	glCompileShader(_id);
	int result = 0;
	glGetShaderiv(_id, GL_COMPILE_STATUS, &result);
	return result != GL_FALSE;
}

std::string GLShader::GetInfoLog() const {
	int len = 0;
	std::string log;
	glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log.resize(len + 1);
		glGetShaderInfoLog(_id, len, &len, &log[0]);
	}
	return log;
}

std::string GLShader::GetSource() const
{
	int len = 0;
	std::string source;
	glGetShaderiv(_id, GL_SHADER_SOURCE_LENGTH, &len);
	source.resize(len + 1);
	glGetShaderSource(_id, len, &len, &source[0]);
	return source;
}

} // namespace opengl