#pragma once

#include "GLProgram.hpp"
#include "GLModel.hpp"

class MyShader
{
public:
	bool Create(const char *vertShader, const char *fragShader);
	void Bind() const;
	void BindMVP() const;
	opengl::GLProgram GetProgram();
	GLuint Id() const;
	opengl::GLUniform Get(const char *uniformName);

private:
	opengl::GLProgram _program;
	GLuint _modelLoc, _viewLoc, _projLoc, _normLoc;
};