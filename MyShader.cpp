#include "MyShader.hpp"
#include "GLMatrix.hpp"

using namespace opengl;

bool MyShader::Create(const char *vertShader, const char *fragShader)
{
	if (!_program.Create(vertShader, fragShader)) {
		return false;
	}
	_modelLoc = _program.GetUniform("ModelMatrix").GetLocation();
	_viewLoc = _program.GetUniform("ViewMatrix").GetLocation();
	_projLoc = _program.GetUniform("ProjectionMatrix").GetLocation();
	_normLoc = _program.GetUniform("NormalMatrix").GetLocation();
	return true;
}

void MyShader::Bind() const
{
	_program.Bind();
	GL.SetUniforms(_modelLoc, _viewLoc, _projLoc, _normLoc);
	GL.Bind();
}

void MyShader::BindMVP() const
{
	_program.Bind();
	GL.SetUniforms(_modelLoc, _viewLoc, _projLoc);
	GL.BindModelViewProj();
}

opengl::GLProgram MyShader::GetProgram()
{
	return _program;
}

GLuint MyShader::Id() const
{
	return _program.Id();
}

opengl::GLUniform MyShader::Get(const char *uniformName)
{
	return _program.GetUniform(uniformName);
}