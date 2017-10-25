/*
* GLProgram class for OpenGL 4.3
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

#include "GLProgram.hpp"
#include <iostream>

namespace opengl
{

bool GLProgram::Create(const std::string &vshader_path, const std::string &fshader_path)
{
	opengl::GLShader v, f;
	_id = glCreateProgram();
	if (_id == 0) {
		return false;
	}
	v.Create(opengl::ShaderType::VERTEX);
	if (!v.CompileFile(vshader_path)) {
		std::cout << "Error compiling: " << vshader_path << std::endl << v.GetInfoLog() << std::endl;
		v.Destroy();
		Destroy();
		return false;
	}
	f.Create(opengl::ShaderType::FRAGMENT);
	if (!f.CompileFile(fshader_path)) {
		std::cout << "Error compiling: " << fshader_path << std::endl << f.GetInfoLog() << std::endl;
		v.Destroy();
		f.Destroy();
		Destroy();
		return false;
	}
	Attach(v.Id());
	Attach(f.Id());

	v.Destroy();
	f.Destroy();
	if (!Link()) {
		std::cout << "Failed to link shader program." << std::endl;
		return false;
	}
	return true;
}

std::string GLProgram::GetInfoLog() const {
	int len = 0;
	std::string log;
	glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log.resize(len + 1);
		glGetProgramInfoLog(_id, len, &len, &log[0]);
	}
	return log;
}

void GLProgram::GetResourceNames(ProgramResource resource, std::vector<std::string> &names) const {
	int count = 0;
	glGetProgramInterfaceiv(_id, (GLenum)resource, GL_ACTIVE_RESOURCES, &count);
	if (count > 0) {
		int len = 0;
		glGetProgramInterfaceiv(_id, (GLenum)resource, GL_MAX_NAME_LENGTH, &len);
		char *name = new char[len];
		for (int i = 0; i < count; i++) {
			glGetProgramResourceName(_id, (GLenum)resource, i, len, 0, name);
			names.push_back(name);
		}
		delete[] name;
	}
}

std::string GLProgram::GetResourceName(ProgramResource resource, int activeIndex) const {
	int len = 0;
	glGetProgramInterfaceiv(_id, (GLenum)resource, GL_MAX_NAME_LENGTH, &len);
	std::string name;
	if (len > 0) {
		char *namestr = new char[len];
		glGetProgramResourceName(_id, (GLenum)resource, activeIndex, len, NULL, namestr);
		name.assign(namestr);
		delete[] namestr;
	}
	return name;
}

void GLProgram::GetResourceProperties(ProgramResource resource, int activeIndex,
	const std::vector<ResourceProperty> &props, std::vector<int> &results) const
{
	if (props.size() > 0) {
		results.resize(props.size());
		glGetProgramResourceiv(_id, (GLenum)resource, activeIndex, props.size(),
			(GLenum *)&props[0], props.size(), NULL, &results[0]);
	}
}

void GLProgram::_GetResource(ProgramResource resource, int activeIndex, std::vector<int> &subroutineIndices,
	GLenum typeCount, GLenum type)
{
	int propCount = 1;
	GLenum props = typeCount;
	int len = 1;
	int compatibleSubs = 0;
	glGetProgramResourceiv(_id, (GLenum)resource, activeIndex, 1, &props, 1, &len, &compatibleSubs);
	if (compatibleSubs > 0) {
		props = type;
		subroutineIndices.resize(compatibleSubs);
		glGetProgramResourceiv(_id, (GLenum)resource, activeIndex, 1, &props, compatibleSubs, NULL, &subroutineIndices[0]);
	}
}

bool GLProgram::SaveBinary(const std::string &filename, GLenum &savedFormat) const
{
	int len = 0;
	glGetProgramiv(_id, GL_PROGRAM_BINARY_LENGTH, &len);
	char *binaryData = (char *) new char[len];
	glGetProgramBinary(_id, len, NULL, &savedFormat, binaryData);

	std::ofstream file;
	file.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	file.write(binaryData, len);
	file.close();
	delete[] binaryData;
	return false;
}

bool GLProgram::LoadBinary(const std::string &filename, GLenum binaryFormat)
{
	std::ifstream input(filename, std::ios::in | std::ios::binary);
	if (!input)
		return false;
	std::string binaryData = std::string(std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>());
	glProgramBinary(_id, binaryFormat, (const void *)binaryData.c_str(),
		binaryData.length());
	int status = 0;
	glGetProgramiv(_id, GL_LINK_STATUS, &status);
	return status != GL_FALSE;
}

} // namespace opengl



/************************* OTHER *************************
/*********************************************************/
//This is disabled because it is too bulky for general use.

/*
#define _GLSL_CASE(type, str) case (type): (ret) = #str; break;
// I considered using a map, but it requires initialization
// and more memory. Also, switch can be faster if it is compiled
// as a lookup table.
std::string getTypeString(GLSLType type)
{
std::string ret;
switch((int) type)
{
_GLSL_CASE(GL_FLOAT, float)
_GLSL_CASE(GL_FLOAT_VEC2, vec2)
_GLSL_CASE(GL_FLOAT_VEC3, vec3)
_GLSL_CASE(GL_FLOAT_VEC4, vec4)
_GLSL_CASE(GL_DOUBLE, double)
_GLSL_CASE(GL_DOUBLE_VEC2, dvec2)
_GLSL_CASE(GL_DOUBLE_VEC3, dvec3)
_GLSL_CASE(GL_DOUBLE_VEC4, dvec4)
_GLSL_CASE(GL_INT, int)
_GLSL_CASE(GL_INT_VEC2, ivec2)
_GLSL_CASE(GL_INT_VEC3, ivec3)
_GLSL_CASE(GL_INT_VEC4, ivec4)
_GLSL_CASE(GL_UNSIGNED_INT, unsigned int)
_GLSL_CASE(GL_UNSIGNED_INT_VEC2, uvec2)
_GLSL_CASE(GL_UNSIGNED_INT_VEC3, uvec3)
_GLSL_CASE(GL_UNSIGNED_INT_VEC4, uvec4)
_GLSL_CASE(GL_BOOL, bool)
_GLSL_CASE(GL_BOOL_VEC2, bvec2)
_GLSL_CASE(GL_BOOL_VEC3, bvec3)
_GLSL_CASE(GL_BOOL_VEC4, bvec4)
_GLSL_CASE(GL_FLOAT_MAT2, mat2)
_GLSL_CASE(GL_FLOAT_MAT3, mat3)
_GLSL_CASE(GL_FLOAT_MAT4, mat4)
_GLSL_CASE(GL_FLOAT_MAT2x3, mat2x3)
_GLSL_CASE(GL_FLOAT_MAT2x4, mat2x4)
_GLSL_CASE(GL_FLOAT_MAT3x2, mat3x2)
_GLSL_CASE(GL_FLOAT_MAT3x4, mat3x4)
_GLSL_CASE(GL_FLOAT_MAT4x2, mat4x2)
_GLSL_CASE(GL_FLOAT_MAT4x3, mat4x3)
_GLSL_CASE(GL_DOUBLE_MAT2, dmat2)
_GLSL_CASE(GL_DOUBLE_MAT3, dmat3)
_GLSL_CASE(GL_DOUBLE_MAT4, dmat4)
_GLSL_CASE(GL_DOUBLE_MAT2x3, dmat2x3)
_GLSL_CASE(GL_DOUBLE_MAT2x4, dmat2x4)
_GLSL_CASE(GL_DOUBLE_MAT3x2, dmat3x2)
_GLSL_CASE(GL_DOUBLE_MAT3x4, dmat3x4)
_GLSL_CASE(GL_DOUBLE_MAT4x2, dmat4x2)
_GLSL_CASE(GL_DOUBLE_MAT4x3, dmat4x3)
_GLSL_CASE(GL_SAMPLER_1D, sampler1D)
_GLSL_CASE(GL_SAMPLER_2D, sampler2D)
_GLSL_CASE(GL_SAMPLER_3D, sampler3D)
_GLSL_CASE(GL_SAMPLER_CUBE, samplerCube)
_GLSL_CASE(GL_SAMPLER_1D_SHADOW, sampler1DShadow)
_GLSL_CASE(GL_SAMPLER_2D_SHADOW, sampler2DShadow)
_GLSL_CASE(GL_SAMPLER_1D_ARRAY, sampler1DArray)
_GLSL_CASE(GL_SAMPLER_2D_ARRAY, sampler2DArray)
_GLSL_CASE(GL_SAMPLER_1D_ARRAY_SHADOW, sampler1DArrayShadow)
_GLSL_CASE(GL_SAMPLER_2D_ARRAY_SHADOW, sampler2DArrayShadow)
_GLSL_CASE(GL_SAMPLER_2D_MULTISAMPLE, sampler2DMS)
_GLSL_CASE(GL_SAMPLER_2D_MULTISAMPLE_ARRAY, sampler2DMSArray)
_GLSL_CASE(GL_SAMPLER_CUBE_SHADOW, samplerCubeShadow)
_GLSL_CASE(GL_SAMPLER_BUFFER, samplerBuffer)
_GLSL_CASE(GL_SAMPLER_2D_RECT, sampler2DRect)
_GLSL_CASE(GL_SAMPLER_2D_RECT_SHADOW, sampler2DRectShadow)
_GLSL_CASE(GL_INT_SAMPLER_1D, isampler1D)
_GLSL_CASE(GL_INT_SAMPLER_2D, isampler2D)
_GLSL_CASE(GL_INT_SAMPLER_3D, isampler3D)
_GLSL_CASE(GL_INT_SAMPLER_CUBE, isamplerCube)
_GLSL_CASE(GL_INT_SAMPLER_1D_ARRAY, isampler1DArray)
_GLSL_CASE(GL_INT_SAMPLER_2D_ARRAY, isampler2DArray)
_GLSL_CASE(GL_INT_SAMPLER_2D_MULTISAMPLE, isampler2DMS)
_GLSL_CASE(GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY, isampler2DMSArray)
_GLSL_CASE(GL_INT_SAMPLER_BUFFER, isamplerBuffer)
_GLSL_CASE(GL_INT_SAMPLER_2D_RECT, isampler2DRect)
_GLSL_CASE(GL_UNSIGNED_INT_SAMPLER_1D, usampler1D)
_GLSL_CASE(GL_UNSIGNED_INT_SAMPLER_2D, usampler2D)
_GLSL_CASE(GL_UNSIGNED_INT_SAMPLER_3D, usampler3D)
_GLSL_CASE(GL_UNSIGNED_INT_SAMPLER_CUBE, usamplerCube)
_GLSL_CASE(GL_UNSIGNED_INT_SAMPLER_1D_ARRAY, usampler2DArray)
_GLSL_CASE(GL_UNSIGNED_INT_SAMPLER_2D_ARRAY, usampler2DArray)
_GLSL_CASE(GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE, usampler2DMS)
_GLSL_CASE(GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY, usampler2DMSArray)
_GLSL_CASE(GL_UNSIGNED_INT_SAMPLER_BUFFER, usamplerBuffer)
_GLSL_CASE(GL_UNSIGNED_INT_SAMPLER_2D_RECT, usampler2DRect)
_GLSL_CASE(GL_IMAGE_1D, image1D)
_GLSL_CASE(GL_IMAGE_2D, image2D)
_GLSL_CASE(GL_IMAGE_3D, image3D)
_GLSL_CASE(GL_IMAGE_2D_RECT, image2DRect)
_GLSL_CASE(GL_IMAGE_CUBE, imageCube)
_GLSL_CASE(GL_IMAGE_BUFFER, imageBuffer)
_GLSL_CASE(GL_IMAGE_1D_ARRAY, image1DArray)
_GLSL_CASE(GL_IMAGE_2D_ARRAY, image2DArray)
_GLSL_CASE(GL_IMAGE_2D_MULTISAMPLE, image2DMS)
_GLSL_CASE(GL_IMAGE_2D_MULTISAMPLE_ARRAY, image2DMSArray)
_GLSL_CASE(GL_INT_IMAGE_1D, iimage1D)
_GLSL_CASE(GL_INT_IMAGE_2D, iimage2D)
_GLSL_CASE(GL_INT_IMAGE_3D, iimage3D)
_GLSL_CASE(GL_INT_IMAGE_2D_RECT, iimage2DRect)
_GLSL_CASE(GL_INT_IMAGE_CUBE, iimageCube)
_GLSL_CASE(GL_INT_IMAGE_BUFFER, iimageBuffer)
_GLSL_CASE(GL_INT_IMAGE_1D_ARRAY, iimage1DArray)
_GLSL_CASE(GL_INT_IMAGE_2D_ARRAY, iimage2DArray)
_GLSL_CASE(GL_INT_IMAGE_2D_MULTISAMPLE, iimage2DMS)
_GLSL_CASE(GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY, iimage2DMSArray)
_GLSL_CASE(GL_UNSIGNED_INT_IMAGE_1D, uimage1D)
_GLSL_CASE(GL_UNSIGNED_INT_IMAGE_2D, uimage2D)
_GLSL_CASE(GL_UNSIGNED_INT_IMAGE_3D, uimage3D)
_GLSL_CASE(GL_UNSIGNED_INT_IMAGE_2D_RECT, uimage2DRect)
_GLSL_CASE(GL_UNSIGNED_INT_IMAGE_CUBE, uimageCube)
_GLSL_CASE(GL_UNSIGNED_INT_IMAGE_BUFFER, uimageBuffer)
_GLSL_CASE(GL_UNSIGNED_INT_IMAGE_1D_ARRAY, uimage1DArray)
_GLSL_CASE(GL_UNSIGNED_INT_IMAGE_2D_ARRAY, uimage2DArray)
_GLSL_CASE(GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE, uimage2DMS)
_GLSL_CASE(GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY, uimage2DMSArray)
_GLSL_CASE(GL_UNSIGNED_INT_ATOMIC_COUNTER, atomic_uint)
}
return ret;
}
#undef _GLSL_CASE
*/
