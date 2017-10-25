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

#pragma once
#ifndef GLPROGRAM_H
#define GLPROGRAM_H

#include <GL/glew.h>
#include <vector>
#include <string>
#include "GLShader.hpp"
#include "GLUniform.hpp"

namespace opengl {

enum class GLSLType
{
	bool_ = GL_BOOL,
	int_ = GL_INT,
	unsigned_int = GL_UNSIGNED_INT,
	float_ = GL_FLOAT,
	double_ = GL_DOUBLE,
	vec2 = GL_FLOAT_VEC2,
	vec3 = GL_FLOAT_VEC3,
	vec4 = GL_FLOAT_VEC4,
	dvec2 = GL_DOUBLE_VEC2,
	dvec3 = GL_DOUBLE_VEC3,
	dvec4 = GL_DOUBLE_VEC4,
	ivec2 = GL_INT_VEC2,
	ivec3 = GL_INT_VEC3,
	ivec4 = GL_INT_VEC4,
	uvec2 = GL_UNSIGNED_INT_VEC2,
	uvec3 = GL_UNSIGNED_INT_VEC3,
	uvec4 = GL_UNSIGNED_INT_VEC4,
	bvec2 = GL_BOOL_VEC2,
	bvec3 = GL_BOOL_VEC3,
	bvec4 = GL_BOOL_VEC4,
	mat2 = GL_FLOAT_MAT2,
	mat3 = GL_FLOAT_MAT3,
	mat4 = GL_FLOAT_MAT4,
	mat2x3 = GL_FLOAT_MAT2x3,
	mat2x4 = GL_FLOAT_MAT2x4,
	mat3x2 = GL_FLOAT_MAT3x2,
	mat3x4 = GL_FLOAT_MAT3x4,
	mat4x2 = GL_FLOAT_MAT4x2,
	mat4x3 = GL_FLOAT_MAT4x3,
	dmat2 = GL_DOUBLE_MAT2,
	dmat3 = GL_DOUBLE_MAT3,
	dmat4 = GL_DOUBLE_MAT4,
	dmat2x3 = GL_DOUBLE_MAT2x3,
	dmat2x4 = GL_DOUBLE_MAT2x4,
	dmat3x2 = GL_DOUBLE_MAT3x2,
	dmat3x4 = GL_DOUBLE_MAT3x4,
	dmat4x2 = GL_DOUBLE_MAT4x2,
	dmat4x3 = GL_DOUBLE_MAT4x3,
	sampler1D = GL_SAMPLER_1D,
	sampler2D = GL_SAMPLER_2D,
	sampler3D = GL_SAMPLER_3D,
	samplerCube = GL_SAMPLER_CUBE,
	sampler1DShadow = GL_SAMPLER_1D_SHADOW,
	sampler2DShadow = GL_SAMPLER_2D_SHADOW,
	sampler1DArray = GL_SAMPLER_1D_ARRAY,
	sampler2DArray = GL_SAMPLER_2D_ARRAY,
	sampler1DArrayShadow = GL_SAMPLER_1D_ARRAY_SHADOW,
	sampler2DArrayShadow = GL_SAMPLER_2D_ARRAY_SHADOW,
	sampler2DMS = GL_SAMPLER_2D_MULTISAMPLE,
	sampler2DMSArray = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
	samplerCubeShadow = GL_SAMPLER_CUBE_SHADOW,
	samplerBuffer = GL_SAMPLER_BUFFER,
	sampler2DRect = GL_SAMPLER_2D_RECT,
	sampler2DRectShadow = GL_SAMPLER_2D_RECT_SHADOW,
	isampler1D = GL_INT_SAMPLER_1D,
	isampler2D = GL_INT_SAMPLER_2D,
	isampler3D = GL_INT_SAMPLER_3D,
	isamplerCube = GL_INT_SAMPLER_CUBE,
	isampler1DArray = GL_INT_SAMPLER_1D_ARRAY,
	isampler2DArray = GL_INT_SAMPLER_2D_ARRAY,
	isampler2DMS = GL_INT_SAMPLER_2D_MULTISAMPLE,
	isampler2DMSArray = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
	isamplerBuffer = GL_INT_SAMPLER_BUFFER,
	isampler2DRect = GL_INT_SAMPLER_2D_RECT,
	usampler1D = GL_UNSIGNED_INT_SAMPLER_1D,
	usampler2D = GL_UNSIGNED_INT_SAMPLER_2D,
	usampler3D = GL_UNSIGNED_INT_SAMPLER_3D,
	usamplerCube = GL_UNSIGNED_INT_SAMPLER_CUBE,
	usampler1DArray = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,
	usampler2DArray = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
	usampler2DMS = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,
	usampler2DMSArray = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
	usamplerBuffer = GL_UNSIGNED_INT_SAMPLER_BUFFER,
	usampler2DRect = GL_UNSIGNED_INT_SAMPLER_2D_RECT,
	image1D = GL_IMAGE_1D,
	image2D = GL_IMAGE_2D,
	image3D = GL_IMAGE_3D,
	image2DRect = GL_IMAGE_2D_RECT,
	imageCube = GL_IMAGE_CUBE,
	imageBuffer = GL_IMAGE_BUFFER,
	image1DArray = GL_IMAGE_1D_ARRAY,
	image2DArray = GL_IMAGE_2D_ARRAY,
	image2DMS = GL_IMAGE_2D_MULTISAMPLE,
	image2DMSArray = GL_IMAGE_2D_MULTISAMPLE_ARRAY,
	iimage1D = GL_INT_IMAGE_1D,
	iimage2D = GL_INT_IMAGE_2D,
	iimage3D = GL_INT_IMAGE_3D,
	iimage2DRect = GL_INT_IMAGE_2D_RECT,
	iimageCube = GL_INT_IMAGE_CUBE,
	iimageBuffer = GL_INT_IMAGE_BUFFER,
	iimage1DArray = GL_INT_IMAGE_1D_ARRAY,
	iimage2DArray = GL_INT_IMAGE_2D_ARRAY,
	iimage2DMS = GL_INT_IMAGE_2D_MULTISAMPLE,
	iimage2DMSArray = GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,
	uimage1D = GL_UNSIGNED_INT_IMAGE_1D,
	uimage2D = GL_UNSIGNED_INT_IMAGE_2D,
	uimage3D = GL_UNSIGNED_INT_IMAGE_3D,
	uimage2DRect = GL_UNSIGNED_INT_IMAGE_2D_RECT,
	uimageCube = GL_UNSIGNED_INT_IMAGE_CUBE,
	uimageBuffer = GL_UNSIGNED_INT_IMAGE_BUFFER,
	uimage1DArray = GL_UNSIGNED_INT_IMAGE_1D_ARRAY,
	uimage2DArray = GL_UNSIGNED_INT_IMAGE_2D_ARRAY,
	uimage2DMS = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,
	uimage2DMSArray = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,
	atomic_uint = GL_UNSIGNED_INT_ATOMIC_COUNTER,
};


enum class ShaderRef
{
	VERTEX = GL_REFERENCED_BY_VERTEX_SHADER,
	TESS_CONTROL = GL_REFERENCED_BY_TESS_CONTROL_SHADER,
	TESS_EVALUATION = GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
	GEOMETRY = GL_REFERENCED_BY_GEOMETRY_SHADER,
	FRAGMENT = GL_REFERENCED_BY_FRAGMENT_SHADER,
	COMPUTE = GL_REFERENCED_BY_COMPUTE_SHADER,
};

/*
enum class ShaderRefACB
{
	VERTEX = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER,
	TESS_CONTROL = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER, 
	TESS_EVALUATION = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER,		
	GEOMETRY = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER, 
	FRAGMENT = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER, 
	COMPUTE = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER,
};

enum ShaderTypeBits //Not strongly typed
{
	VERTEX_SHADER_BIT = GL_VERTEX_SHADER_BIT,
	TESS_CONTROL_SHADER_BIT = GL_TESS_CONTROL_SHADER_BIT,
	TESS_EVALUATION_SHADER_BIT = GL_TESS_EVALUATION_SHADER_BIT,
	GEOMETRY_SHADER_BIT = GL_GEOMETRY_SHADER_BIT,
	FRAGMENT_SHADER_BIT = GL_FRAGMENT_SHADER_BIT,
	COMPUTE_SHADER_BIT = GL_COMPUTE_SHADER_BIT,
	ALL_SHADER_BITS = GL_ALL_SHADER_BITS,
};
*/

enum class ProgramResource
{
	ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER,
	UNIFORM = GL_UNIFORM,
	UNIFORM_BLOCK = GL_UNIFORM_BLOCK,
	PROGRAM_INPUT = GL_PROGRAM_INPUT, //ATTRIBUTES (Vertex Shader)
	PROGRAM_OUTPUT = GL_PROGRAM_OUTPUT, //FRAG DATA (Fragment Shader)
	VERTEX_SUBROUTINE = GL_VERTEX_SUBROUTINE,
	TESS_CONTROL_SUBROUTINE = GL_TESS_CONTROL_SUBROUTINE,
	TESS_EVALUATION_SUBROUTINE = GL_TESS_EVALUATION_SUBROUTINE,
	GEOMETRY_SUBROUTINE = GL_GEOMETRY_SUBROUTINE,
	FRAGMENT_SUBROUTINE = GL_FRAGMENT_SUBROUTINE,
	COMPUTE_SUBROUTINE = GL_COMPUTE_SUBROUTINE,
	VERTEX_SUBROUTINE_UNIFORM = GL_VERTEX_SUBROUTINE_UNIFORM,
	TESS_CONTROL_SUBROUTINE_UNIFORM = GL_TESS_CONTROL_SUBROUTINE_UNIFORM,
	TESS_EVALUATION_SUBROUTINE_UNIFORM = GL_TESS_EVALUATION_SUBROUTINE_UNIFORM,
	GEOMETRY_SUBROUTINE_UNIFORM = GL_GEOMETRY_SUBROUTINE_UNIFORM,
	FRAGMENT_SUBROUTINE_UNIFORM = GL_FRAGMENT_SUBROUTINE_UNIFORM,
	COMPUTE_SUBROUTINE_UNIFORM = GL_COMPUTE_SUBROUTINE_UNIFORM,
	TRANSFORM_FEEDBACK_VARYING = GL_TRANSFORM_FEEDBACK_VARYING,
	BUFFER_VARIABLE = GL_BUFFER_VARIABLE,
	SHADER_STORAGE_BLOCK = GL_SHADER_STORAGE_BLOCK,
};

enum class ResourceProperty
{
	TYPE = GL_TYPE,
	ARRAY_SIZE = GL_ARRAY_SIZE,
	OFFSET = GL_OFFSET,
	BLOCK_INDEX = GL_BLOCK_INDEX,
	ARRAY_STRIDE = GL_ARRAY_STRIDE,
	MATRIX_STRIDE = GL_MATRIX_STRIDE,
	IS_ROW_MAJOR = GL_IS_ROW_MAJOR,
	ATOMIC_COUNTER_BUFFER_INDEX = GL_ATOMIC_COUNTER_BUFFER_INDEX,
	BUFFER_BINDING = GL_BUFFER_BINDING,
	BUFFER_DATA_SIZE = GL_BUFFER_DATA_SIZE,
	REF_BY_VERTEX_SHADER = GL_REFERENCED_BY_VERTEX_SHADER,
	REF_BY_TESS_CONTROL_SHADER = GL_REFERENCED_BY_TESS_CONTROL_SHADER,
	REF_BY_TESS_EVALUATION_SHADER = GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
	REF_BY_GEOMETRY_SHADER = GL_REFERENCED_BY_GEOMETRY_SHADER,
	REF_BY_FRAGMENT_SHADER = GL_REFERENCED_BY_FRAGMENT_SHADER,
	REF_BY_COMPUTE_SHADER = GL_REFERENCED_BY_COMPUTE_SHADER,
	NUM_ACTIVE_VARIABLES = GL_NUM_ACTIVE_VARIABLES,
	NUM_COMPATIBLE_SUBROUTINES = GL_NUM_COMPATIBLE_SUBROUTINES,
	TOP_LEVEL_ARRAY_SIZE = GL_TOP_LEVEL_ARRAY_SIZE,
	TOP_LEVEL_ARRAY_STRIDE = GL_TOP_LEVEL_ARRAY_STRIDE,
	LOCATION = GL_LOCATION,
	LOCATION_INDEX = GL_LOCATION_INDEX,
	IS_PER_PATCH = GL_IS_PER_PATCH,
};

class GLProgram
{
protected:
	int _id;

public:
	GLProgram() : _id(0) { }
	GLProgram(int id) : _id(id) { }
	bool operator==(const GLProgram &other) const;
	void Create();
	bool Create(const std::string &vshader_path, const std::string &fshader_path);
	// Shaders are automatically detatched when a program is destroyed.
	void Destroy();
	int Id() const;
	// Does a fast check and hard validation.
	bool Exists() const;
	// Shaders may be attached to more than one program.
	// A shader can be attached to a program before its
	// source code is loaded or compiled.
	// Multiple shaders of the same type may attached to a
	// program since each may contain part of a whole shader.
	void Attach(int shaderId);
	void Detatch(int shaderId);
	// These are hints to the linker, and do not guarantee anything.
	// Setting hints before linking is not required.
	void SetLinkOptions(bool binaryRetrievable, bool pipelineSeparable);
	bool Link();
	// Validates that the program can execute.
	// When you set variables incorrectly, such as samplers,
	// the program can become unable to execute.
	bool Validate() const;
	// Error message for link/validate failure.
	std::string GetInfoLog() const;
	void Bind() const;
	// Unbind is unnecessary when switching between programs.
	static void Unbind();
	// Gets the currently bound Program. 
	// The returned object's ID is zero when no shader program is currently bound.
	static GLProgram GetBinding();
	void GetShaders(std::vector<GLShader> &shaders) const;

	// *********************** BINARIES ************************
	// Be aware that a user's system can change, and therefore the binaries
	// might not always work. Also, note that binaries loading may not be
	// supported on some systems.

	// Saving a program's binary requires it to be linked first.
	// Binaries are specific to each graphics card and system,
	// so only save/load binaries on the same system.
	bool SaveBinary(const std::string &filename, GLenum &savedFormat) const;
	// Loading a binary automatically links it.
	// Consider using setLinkOptions() before loading a binary.
	bool LoadBinary(const std::string &filename, GLenum binaryFormat);
	//static int GetBinaryFormatCount();
	static void GetBinaryFormats(std::vector<GLenum> &formats);

	// ********************* BEFORE LINKING ********************

	// The maximum number of attributes and locations that can be specified.
	// The maximum location is maxAttributes() - 1.
	int GetMaxAttributes() const;
	// IMPORTANT! OpenGL is not guarenteed to correctly assign the locations of attributes 
	// that are shared between shaders.
	void SetAttributeLocation(const std::string &name, int loc) const;
	void SetFragDataLocation(const std::string &name, int colorNumber);
	// Index must be 0 or 1
	void SetFragDataLocation(const std::string &name, int colorNumber, int index);
	// Upper limit on how many Separate varyings can be set.
	static int GetMaxSeparateVaryings();
	// Upper limit on how many Interleaved varyings can be set.
	static int GetMaxInterleavedVaryings();
	// Upper limit on the total number of Varyings passed to setFeedbackVaryings().
	static int GetMaxFeedbackVaryings();
	void SetFeedbackVaryings(bool interleaved, const std::vector<const char *> &varyings);
	void SetFeedbackVaryings(bool interleaved, int numVaryings, const char **varyings);

	// ********************* AFTER LINKING *********************
	// All metadata can be found through Resources. 

	GLUniform GetUniform(const std::string &name) const;
	int GetUniformLocation(const std::string &name) const;
	int GetUniformBlockIndex(const std::string &name) const;
	int GetAttributeLocation(const std::string &name) const;
	int GetSubroutineUniformLocation(ShaderType type, const std::string &name) const;
	int GetSubroutineIndex(ShaderType type, const std::string &name) const;
	int GetFragDataLocation(const std::string &name) const;
	int GetFragDataIndex(const std::string &name) const;
	//Compatible Subroutines/Uniforms
	int GetCompatibleSubroutineCount(ShaderType shaderType, int subUniformLocation) const;
	void GetCompatibleSubroutines(ShaderType shaderType, int subUniformLocation, 
		std::vector<int> &compatibleSubIndices) const;
	static void SetSubroutineUniforms(ShaderType shaderType, std::vector<int> &subroutineIndices);
	static void SetSubroutineUniforms(ShaderType shaderType, int count, int *subroutineIndices);
	void SetUniformBlockBinding(const std::string &name, GLuint blockBinding);
	void SetUniformBlockBinding(GLuint blockIndex, GLuint blockBinding);

	// ****************** RESOURCES (ACTIVE) *******************
	// Atomic Counter Buffer properties are queried through a
	// referencing UNIFORM and getting its ATOMIC COUNTER BUFFER INDEX.

	int GetResourceCount(ProgramResource resource) const;
	int GetResourceIndex(ProgramResource resource, const std::string &name) const;
	int GetResourceLocation(ProgramResource resource, const std::string &name) const;
	// Returns an empty string if invalid resource or index is specified.
	std::string GetResourceName(ProgramResource resource, int resourceIndex) const;
	void GetResourceNames(ProgramResource resource, std::vector<std::string> &names) const;
	// Gets specific details about a resource. Cast the int to a bool for boolean properties.
	int GetResourceProperty(ProgramResource resource, int resourceIndex, ResourceProperty prop) const;
	// More efficient than getting 1 property at a time. It all occurs internally to OpenGL.
	void GetResourceProperties(ProgramResource resource, int resourceIndex, 
		const std::vector<ResourceProperty> &props, std::vector<int> &results) const;
	bool IsResourceReferenced(ProgramResource resource, int resourceIndex, ShaderRef shaderType) const;
	void GetCompatibleSubroutines(ProgramResource resource, int resourceIndex, 
		std::vector<int> &subroutineIndices);
	void GetVariables(ProgramResource resource, int resourceIndex, 
		std::vector<int> &subroutineIndices);

private:
	void _GetResource(ProgramResource resource, int activeIndex, std::vector<int> &subroutineIndices, 
		GLenum typeCount, GLenum type);
};


} // namespace opengl
#include "GLProgram.inl"
#endif // GLPROGRAM_HPP