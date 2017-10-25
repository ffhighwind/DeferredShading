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
#ifndef GLPROGRAM_INL
#define GLPROGRAM_INL

namespace opengl {

inline bool GLProgram::operator==(const GLProgram &other) const {
	return _id == other._id && _id != 0;
}

inline void GLProgram::Create() {
	_id = glCreateProgram();
}

inline void GLProgram::Destroy() {
	glDeleteProgram(_id);
	_id = 0;
}

inline int GLProgram::Id() const {
	return _id;
}

inline bool GLProgram::Exists() const {
	return _id != 0 && glIsProgram(_id) != GL_FALSE;
}

inline bool GLProgram::Validate() const {
	glValidateProgram(_id);
	int result = 0;
	glGetProgramiv(_id, GL_VALIDATE_STATUS, &result);
	return result != GL_FALSE;
}

inline void GLProgram::Attach(int shaderId) {
	glAttachShader(_id, shaderId);
}

inline void GLProgram::Detatch(int shaderId) {
	glDetachShader(_id, shaderId);
}

inline bool GLProgram::Link() {
	glLinkProgram(_id);
	int status = 0;
	glGetProgramiv(_id, GL_LINK_STATUS, &status);
	return status != GL_FALSE;
}

inline void GLProgram::SetLinkOptions(bool binaryRetrievable, bool pipelineSeparable) {
	glProgramParameteri(_id, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, (int)binaryRetrievable);
	glProgramParameteri(_id, GL_PROGRAM_SEPARABLE, (int)pipelineSeparable);
}

inline void GLProgram::Bind() const {
	glUseProgram(_id);
}

inline void GLProgram::Unbind() {
	glUseProgram(0);
}

inline GLProgram GLProgram::GetBinding() {
	int id = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	return GLProgram(id);
}

inline void GLProgram::GetShaders(std::vector<GLShader> &shaders) const {
	int count = 0;
	glGetProgramiv(_id, GL_ATTACHED_SHADERS, &count);
	shaders.resize(count);
	glGetAttachedShaders(_id, count, NULL, (GLuint *)&shaders[0]);
}

// *********************** BINARIES ************************

inline void GLProgram::GetBinaryFormats(std::vector<GLenum> &formats) {
	int count = 0;
	glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &count);
	formats.resize(count);
	if (count > 0)
		glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, (int *)&formats[0]);
}

// ******************* FEEDBACK VARYINGS *******************

inline int GLProgram::GetMaxInterleavedVaryings() {
	int maxInterleavedComps = 0;
	glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS, &maxInterleavedComps);
	return maxInterleavedComps;
}

inline int GLProgram::GetMaxSeparateVaryings() {
	int maxSeparateComps = 0;
	glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS, &maxSeparateComps);
	return maxSeparateComps;
}

inline int GLProgram::GetMaxFeedbackVaryings() {
	int maxSepAttribs = 0;
	glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS, &maxSepAttribs);
	return maxSepAttribs;
}

// ************************* SETTERS ***********************

inline void GLProgram::SetFeedbackVaryings(bool interleaved, const std::vector<const char *> &varyings) {
	GLenum buffermode = (GLenum)(interleaved ? GL_INTERLEAVED_ATTRIBS : GL_SEPARATE_ATTRIBS);
	glTransformFeedbackVaryings(_id, varyings.size(), (const char **)varyings.data(), buffermode);
}

inline void GLProgram::SetFeedbackVaryings(bool interleaved, int numVaryings, const char **varyings) {
	GLenum buffermode = (GLenum)(interleaved ? GL_INTERLEAVED_ATTRIBS : GL_SEPARATE_ATTRIBS);
	glTransformFeedbackVaryings(_id, numVaryings, varyings, buffermode);
}

inline void GLProgram::SetFragDataLocation(const std::string &name, int colorNumber) {
	glBindFragDataLocation(_id, colorNumber, name.c_str());
}

inline void GLProgram::SetFragDataLocation(const std::string &name, int colorNumber, int index) {
	glBindFragDataLocationIndexed(_id, colorNumber, index, name.c_str());
}

inline void GLProgram::SetSubroutineUniforms(ShaderType shaderType, std::vector<int> &subroutineIndices) {
	glUniformSubroutinesuiv((GLenum)shaderType, subroutineIndices.size(),
		(GLuint *)&subroutineIndices[0]);
}

inline void GLProgram::SetSubroutineUniforms(ShaderType shaderType, int count, int *subroutineIndices) {
	glUniformSubroutinesuiv((GLenum)shaderType, count, (GLuint *)subroutineIndices);
}

// ******************** AFTER LINKING *********************

inline GLUniform GLProgram::GetUniform(const std::string &name) const {
	return GLUniform(_id, glGetUniformLocation(_id, name.c_str()));
}

inline int GLProgram::GetUniformLocation(const std::string &name) const {
	return glGetUniformLocation(_id, name.c_str());
}

inline int GLProgram::GetUniformBlockIndex(const std::string &name) const {
	return glGetUniformBlockIndex(_id, name.c_str());
}

inline int GLProgram::GetAttributeLocation(const std::string &name) const {
	return glGetAttribLocation(_id, name.c_str());
}

inline void GLProgram::SetUniformBlockBinding(const std::string &name, GLuint blockBinding) {
	glUniformBlockBinding(_id, glGetUniformBlockIndex(_id, name.c_str()), blockBinding);
}

inline void GLProgram::SetUniformBlockBinding(GLuint blockIndex, GLuint blockBinding) {
	glUniformBlockBinding(_id, blockIndex, blockBinding);
}

inline int GLProgram::GetMaxAttributes() const {
	int max = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max);
	return max;
}

inline void GLProgram::SetAttributeLocation(const std::string &name, int loc) const {
	glBindAttribLocation(_id, loc, name.c_str());
}

inline int GLProgram::GetSubroutineUniformLocation(ShaderType type, const std::string &name) const {
	return glGetSubroutineUniformLocation(_id, (GLenum)type, name.c_str());
}

inline int GLProgram::GetSubroutineIndex(ShaderType type, const std::string &name) const {
	return (int)glGetSubroutineIndex(_id, (GLenum)type, name.c_str());
}

//Compatible Subroutines/Uniforms
inline int GLProgram::GetCompatibleSubroutineCount(ShaderType shaderType, int subUniformLocation) const {
	int count = 0;
	glGetActiveSubroutineUniformiv(_id, (GLenum)shaderType, (GLuint)subUniformLocation,
		GL_NUM_COMPATIBLE_SUBROUTINES, &count);
	return count;
}

inline void GLProgram::GetCompatibleSubroutines(ShaderType shaderType, int subUniformLocation,
	std::vector<int> &compatibleSubs) const
{
	int count = 0;
	glGetActiveSubroutineUniformiv(_id, (GLenum)shaderType, (GLuint)subUniformLocation,
		GL_NUM_COMPATIBLE_SUBROUTINES, &count);
	compatibleSubs.resize(count);
	glGetActiveSubroutineUniformiv(_id, (GLenum)shaderType, (GLuint)subUniformLocation,
		GL_COMPATIBLE_SUBROUTINES, (GLint *)&compatibleSubs[0]);
}

//Frag Data
inline int GLProgram::GetFragDataLocation(const std::string &name) const {
	return glGetFragDataLocation(_id, name.c_str());
}

inline int GLProgram::GetFragDataIndex(const std::string &name) const {
	return glGetFragDataIndex(_id, name.c_str());
}

// *********************** RESOURCES ***********************

inline int GLProgram::GetResourceCount(ProgramResource resource) const {
	int count = 0;
	glGetProgramInterfaceiv(_id, (GLenum)resource, GL_ACTIVE_RESOURCES, &count);
	return count;
}

inline int GLProgram::GetResourceIndex(ProgramResource resource, const std::string &name) const {
	return glGetProgramResourceIndex(_id, (GLenum)resource, name.c_str());
}

inline int GLProgram::GetResourceLocation(ProgramResource resource, const std::string &name) const {
	return glGetProgramResourceLocation(_id, (GLenum)resource, name.c_str());
}

inline int GLProgram::GetResourceProperty(ProgramResource resource, int resourceIndex, ResourceProperty prop) const {
	int len = 1;
	int output = 0;
	GLenum property = (GLenum)prop;
	glGetProgramResourceiv(_id, (GLenum)resource, resourceIndex, 1, &property, 1, &len, &output);
	return output;
}

inline bool GLProgram::IsResourceReferenced(ProgramResource resource, int resourceIndex, ShaderRef shaderType) const {
	int len = 1;
	int output = GL_FALSE;
	GLenum property = (GLenum)shaderType;
	glGetProgramResourceiv(_id, (GLenum)resource, resourceIndex, 1, &property, 1, &len, &output);
	return output != GL_FALSE;
}

inline void GLProgram::GetCompatibleSubroutines(ProgramResource resource, int resourceIndex, std::vector<int> &subroutineIndices) {
	_GetResource(resource, resourceIndex, subroutineIndices, GL_NUM_COMPATIBLE_SUBROUTINES, GL_COMPATIBLE_SUBROUTINES);
}

inline void GLProgram::GetVariables(ProgramResource resource, int resourceIndex, std::vector<int> &subroutineIndices) {
	_GetResource(resource, resourceIndex, subroutineIndices, GL_NUM_ACTIVE_VARIABLES, GL_ACTIVE_VARIABLES);
}


} // namespace opengl
#endif GLPROGRAM_INL