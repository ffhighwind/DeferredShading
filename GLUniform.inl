/*
* GLUniform class for OpenGL 4.3
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
#ifndef GLUNIFORM_INL
#define GLUNIFORM_INL

#include "GLUniform.hpp"

namespace opengl {

// **********************************************************
// ************************ UNIFORM *************************

inline bool GLUniform::operator==(const GLUniform &other) const {
	return _program == other._program && _loc == other._loc;
}

inline void GLUniform::SetLocation(int location) {
	_loc = location;
}

inline void GLUniform::SetProgram(int programId) {
	_program = programId;
}

inline int GLUniform::GetLocation() const {
	return _loc;
}

inline int GLUniform::GetProgram() const {
	return _program;
}

inline bool GLUniform::Exists() const {
	return _program != 0 && _loc >= 0 && glIsProgram(_program);
}

//Float
inline void GLUniform::Set(float value) {
	glProgramUniform1f(_program, _loc, value);
}

inline void GLUniform::Set(float value1, float value2) {
	glProgramUniform2f(_program, _loc, value1, value2);
}

inline void GLUniform::Set(float value1, float value2, float value3) {
	glProgramUniform3f(_program, _loc, value1, value2, value3);
}

inline void GLUniform::Set(float value1, float value2, float value3, float value4) {
	glProgramUniform4f(_program, _loc, value1, value2, value3, value4);
}

inline void GLUniform::Set(const glm::vec2 &value) {
	glProgramUniform2f(_program, _loc, value.x, value.y);
}

inline void GLUniform::Set(const glm::vec3 &value) {
	glProgramUniform3f(_program, _loc, value[0], value[1], value[2]);
}

inline void GLUniform::Set(const glm::vec4 &value) {
	glProgramUniform4f(_program, _loc, value.x, value.y, value.z, value.w);
}

//Int
inline void GLUniform::Set(int value) {
	glProgramUniform1i(_program, _loc, value);
}

inline void GLUniform::Set(int value1, int value2) {
	glProgramUniform2i(_program, _loc, value1, value2);
}

inline void GLUniform::Set(int value1, int value2, int value3) {
	glProgramUniform3i(_program, _loc, value1, value2, value3);
}

inline void GLUniform::Set(int value1, int value2, int value3, int value4) {
	glProgramUniform4i(_program, _loc, value1, value2, value3, value4);
}

//UInt
inline void GLUniform::Set(unsigned value) {
	glProgramUniform1ui(_program, _loc, value);
}

inline void GLUniform::Set(unsigned value1, unsigned value2) {
	glProgramUniform2ui(_program, _loc, value1, value2);
}

inline void GLUniform::Set(unsigned value1, unsigned value2, unsigned value3) {
	glProgramUniform3ui(_program, _loc, value1, value2, value3);
}

inline void GLUniform::Set(unsigned value1, unsigned value2, unsigned value3, unsigned value4) {
	glProgramUniform4ui(_program, _loc, value1, value2, value3, value4);
}

// *********************** VECTORS ************************

//IntegerV
inline void GLUniform::Vec1(int count, const int *values) {
	glProgramUniform1iv(_program, _loc, count, values);
}

inline void GLUniform::Vec2(int count, const int *values) {
	glProgramUniform2iv(_program, _loc, count, values);
}

inline void GLUniform::Vec3(int count, const int *values) {
	glProgramUniform3iv(_program, _loc, count, values);
}

inline void GLUniform::Vec4(int count, const int *values) {
	glProgramUniform4iv(_program, _loc, count, values);
}

//UIntV
inline void GLUniform::Vec1(int count, const unsigned *values) {
	glProgramUniform1uiv(_program, _loc, count, values);
}

inline void GLUniform::Vec2(int count, const unsigned *values) {
	glProgramUniform2uiv(_program, _loc, count, values);
}

inline void GLUniform::Vec3(int count, const unsigned *values) {
	glProgramUniform3uiv(_program, _loc, count, values);
}

inline void GLUniform::Vec4(int count, const unsigned *values) {
	glProgramUniform4uiv(_program, _loc, count, values);
}

//FloatV
inline void GLUniform::Vec1(int count, const float *values) {
	glProgramUniform1fv(_program, _loc, count, values);
}

inline void GLUniform::Vec2(int count, const float *values) {
	glProgramUniform2fv(_program, _loc, count, values);
}

inline void GLUniform::Vec3(int count, const float *values) {
	glProgramUniform3fv(_program, _loc, count, values);
}

inline void GLUniform::Vec4(int count, const float *values) {
	glProgramUniform4fv(_program, _loc, count, values);
}

// ************************ MATRICES ***********************

//Matrix
inline void GLUniform::Mat2(const float *values, bool transpose) {
	glProgramUniformMatrix2fv(_program, _loc, 1, (GLboolean) transpose, values);
}

inline void GLUniform::Mat3(const float *values, bool transpose) {
	glProgramUniformMatrix3fv(_program, _loc, 1, (GLboolean) transpose, values);
}

inline void GLUniform::Mat4(const float *values, bool transpose) {
	glProgramUniformMatrix4fv(_program, _loc, 1, (GLboolean) transpose, values);
}

inline void GLUniform::Mat2x3(const float *values, bool transpose) {
	glProgramUniformMatrix2x3fv(_program, _loc, 1, (GLboolean) transpose, values);
}

inline void GLUniform::Mat3x2(const float *values, bool transpose) {
	glProgramUniformMatrix3x2fv(_program, _loc, 1, (GLboolean) transpose, values);
}

inline void GLUniform::Mat2x4(const float *values, bool transpose) {
	glProgramUniformMatrix2x4fv(_program, _loc, 1, (GLboolean) transpose, values);
}

inline void GLUniform::Mat4x2(const float *values, bool transpose) {
	glProgramUniformMatrix4x2fv(_program, _loc, 1, (GLboolean) transpose, values);
}

inline void GLUniform::Mat3x4(const float *values, bool transpose) {
	glProgramUniformMatrix3x4fv(_program, _loc, 1, (GLboolean) transpose, values);
}

inline void GLUniform::Mat4x3(const float *values, bool transpose) {
	glProgramUniformMatrix4x3fv(_program, _loc, 1, (GLboolean) transpose, values);
}

//MatrixV
inline void GLUniform::Mat2v(int count, const float *values, bool transpose) {
	glProgramUniformMatrix2fv(_program, _loc, count, (GLboolean) transpose, values);
}

inline void GLUniform::Mat3v(int count, const float *values, bool transpose) {
	glProgramUniformMatrix3fv(_program, _loc, count, (GLboolean) transpose, values);
}

inline void GLUniform::Mat4v(int count, const float *values, bool transpose) {
	glProgramUniformMatrix4fv(_program, _loc, count, (GLboolean) transpose, values);
}

inline void GLUniform::Mat2x3v(int count, const float *values, bool transpose) {
	glProgramUniformMatrix2x3fv(_program, _loc, count, (GLboolean) transpose, values);
}

inline void GLUniform::Mat3x2v(int count, const float *values, bool transpose) {
	glProgramUniformMatrix3x2fv(_program, _loc, count, (GLboolean) transpose, values);
}

inline void GLUniform::Mat2x4v(int count, const float *values, bool transpose) {
	glProgramUniformMatrix2x4fv(_program, _loc, count, (GLboolean) transpose, values);
}

inline void GLUniform::Mat4x2v(int count, const float *values, bool transpose) {
	glProgramUniformMatrix4x2fv(_program, _loc, count, (GLboolean) transpose, values);
}

inline void GLUniform::Mat3x4v(int count, const float *values, bool transpose) {
	glProgramUniformMatrix3x4fv(_program, _loc, count, (GLboolean) transpose, values);
}

inline void GLUniform::Mat4x3v(int count, const float *values, bool transpose) {
	glProgramUniformMatrix4x3fv(_program, _loc, count, (GLboolean) transpose, values);
}

// **********************************************************
// *********************** UNIFORM B ************************

inline bool GLUniformB::operator==(const GLUniformB &other) const {
	return _loc == other._loc;
}

inline int GLUniformB::GetLocation() const {
	return _loc;
}

inline bool GLUniformB::Exists() const {
	return _loc >= 0;
}

//Float
inline void GLUniformB::Set(float value) {
	glUniform1f(_loc, value);
}

inline void GLUniformB::Set(float value1, float value2) {
	glUniform2f(_loc, value1, value2);
}

inline void GLUniformB::Set(float value1, float value2, float value3) {
	glUniform3f(_loc, value1, value2, value3);
}

inline void GLUniformB::Set(float value1, float value2, float value3, float value4) {
	glUniform4f(_loc, value1, value2, value3, value4);
}

//Int
inline void GLUniformB::Set(int value) {
	glUniform1i(_loc, value);
}

inline void GLUniformB::Set(int value1, int value2) {
	glUniform2i(_loc, value1, value2);
}

inline void GLUniformB::Set(int value1, int value2, int value3) {
	glUniform3i(_loc, value1, value2, value3);
}

inline void GLUniformB::Set(int value1, int value2, int value3, int value4) {
	glUniform4i(_loc, value1, value2, value3, value4);
}

//UInt
inline void GLUniformB::Set(unsigned value) {
	glUniform1ui(_loc, value);
}

inline void GLUniformB::Set(unsigned value1, unsigned value2) {
	glUniform2ui(_loc, value1, value2);
}

inline void GLUniformB::Set(unsigned value1, unsigned value2, unsigned value3) {
	glUniform3ui(_loc, value1, value2, value3);
}

inline void GLUniformB::Set(unsigned value1, unsigned value2, unsigned value3, unsigned value4) {
	glUniform4ui(_loc, value1, value2, value3, value4);
}

// *********************** VECTORS ************************

//IntegerV
inline void GLUniformB::Vec1(int count, const int *values) {
	glUniform1iv(_loc, count, values);
}

inline void GLUniformB::Vec2(int count, const int *values) {
	glUniform2iv(_loc, count, values);
}

inline void GLUniformB::Vec3(int count, const int *values) {
	glUniform3iv(_loc, count, values);
}

inline void GLUniformB::Vec4(int count, const int *values) {
	glUniform4iv(_loc, count, values);
}

//UIntV
inline void GLUniformB::Vec1(int count, const unsigned *values) {
	glUniform1uiv(_loc, count, values);
}

inline void GLUniformB::Vec2(int count, const unsigned *values) {
	glUniform2uiv(_loc, count, values);
}

inline void GLUniformB::Vec3(int count, const unsigned *values) {
	glUniform3uiv(_loc, count, values);
}

inline void GLUniformB::Vec4(int count, const unsigned *values) {
	glUniform4uiv(_loc, count, values);
}

//FloatV
inline void GLUniformB::Vec1(int count, const float *values) {
	glUniform1fv(_loc, count, values);
}

inline void GLUniformB::Vec2(int count, const float *values) {
	glUniform2fv(_loc, count, values);
}

inline void GLUniformB::Vec3(int count, const float *values) {
	glUniform3fv(_loc, count, values);
}

inline void GLUniformB::Vec4(int count, const float *values) {
	glUniform4fv(_loc, count, values);
}

// ************************ MATRICES ***********************

//Matrix
inline void GLUniformB::Mat2(const float *values, bool transpose) {
	glUniformMatrix2fv(_loc, 1, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat3(const float *values, bool transpose) {
	glUniformMatrix3fv(_loc, 1, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat4(const float *values, bool transpose) {
	glUniformMatrix4fv(_loc, 1, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat2x3(const float *values, bool transpose) {
	glUniformMatrix2x3fv(_loc, 1, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat3x2(const float *values, bool transpose) {
	glUniformMatrix3x2fv(_loc, 1, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat2x4(const float *values, bool transpose) {
	glUniformMatrix2x4fv(_loc, 1, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat4x2(const float *values, bool transpose) {
	glUniformMatrix4x2fv(_loc, 1, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat3x4(const float *values, bool transpose) {
	glUniformMatrix3x4fv(_loc, 1, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat4x3(const float *values, bool transpose) {
	glUniformMatrix4x3fv(_loc, 1, (GLboolean) transpose, values);
}

//MatrixV
inline void GLUniformB::Mat2v(int count, const float *values, bool transpose) {
	glUniformMatrix2fv(_loc, count, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat3v(int count, const float *values, bool transpose) {
	glUniformMatrix3fv(_loc, count, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat4v(int count, const float *values, bool transpose) {
	glUniformMatrix4fv(_loc, count, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat2x3v(int count, const float *values, bool transpose) {
	glUniformMatrix2x3fv(_loc, count, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat3x2v(int count, const float *values, bool transpose) {
	glUniformMatrix3x2fv(_loc, count, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat2x4v(int count, const float *values, bool transpose) {
	glUniformMatrix2x4fv(_loc, count, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat4x2v(int count, const float *values, bool transpose) {
	glUniformMatrix4x2fv(_loc, count, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat3x4v(int count, const float *values, bool transpose) {
	glUniformMatrix3x4fv(_loc, count, (GLboolean) transpose, values);
}

inline void GLUniformB::Mat4x3v(int count, const float *values, bool transpose) {
	glUniformMatrix4x3fv(_loc, count, (GLboolean) transpose, values);
}


} // namespace opengl
#endif // GLUNIFORM_INL