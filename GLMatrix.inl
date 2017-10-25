#pragma once
#ifndef GLMATRIX_INL
#define GLMATRIX_INL

#include "GLMatrix.hpp"

namespace opengl {

inline GLMatrix::GLMatrix()
{
	_modelLoc = 0;
	_viewLoc = 1;
	_projLoc = 2;
	_normalLoc = 3;
}

inline void GLMatrix::SetUniforms(GLuint modelLoc, GLuint viewLoc, GLuint projLoc, GLuint worldLoc)
{
	_modelLoc = modelLoc;
	_viewLoc = viewLoc;
	_projLoc = projLoc;
	_normalLoc = worldLoc;
}

inline void GLMatrix::BindModelMatrix()
{
	glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(_modelMatrix));
};

inline void GLMatrix::BindViewMatrix()
{
	glUniformMatrix4fv(_viewLoc, 1, GL_FALSE, glm::value_ptr(_viewMatrix));
};

inline void GLMatrix::BindProjMatrix()
{
	glUniformMatrix4fv(_projLoc, 1, GL_FALSE, glm::value_ptr(_projMatrix));
};

inline void GLMatrix::BindNormalMatrix()
{
	glUniformMatrix3fv(_normalLoc, 1, GL_FALSE, glm::value_ptr(_normalMatrix));
};

inline void GLMatrix::BuildNormalMatrix()
{
	_normalMatrix = glm::mat3(glm::inverseTranspose(_modelMatrix));
};

inline const glm::mat4 &GLMatrix::ModelMatrix() const
{
	return _modelMatrix;
}

inline const glm::mat4 &GLMatrix::ViewMatrix() const
{
	return _viewMatrix;
}

inline const glm::mat4 &GLMatrix::ProjMatrix() const
{
	return _projMatrix;
}

inline const glm::mat4 &GLMatrix::NormalMatrix() const
{
	return _normalMatrix;
}

inline void GLMatrix::Mult(const float *mat4x4)
{
	Mult(glm::make_mat4(mat4x4));
}

inline void GLMatrix::Mult(const glm::mat4 &mat4x4)
{
	_modelMatrix = _modelMatrix * mat4x4;
	BindModelMatrix();
}

inline void GLMatrix::Push()
{
	_matrixStack.push_back(new glm::mat4(_modelMatrix));
}

inline void GLMatrix::Identity()
{
	_modelMatrix = glm::mat4();
	BindModelMatrix();
}

inline void GLMatrix::Translate(float x, float y, float z)
{
	Translate(glm::vec3(x, y, z));
}

inline void GLMatrix::Translate(const float *vec3)
{
	Translate(glm::make_vec3(vec3));
}

inline void GLMatrix::Translate(const glm::vec3 &vec3)
{
	_modelMatrix = glm::translate(_modelMatrix, vec3);
	BindModelMatrix();
}

inline void GLMatrix::Scale(float scalar)
{
	Scale(glm::vec3(scalar, scalar, scalar));
}

inline void GLMatrix::Scale(float x, float y, float z)
{
	Scale(glm::vec3(x, y, z));
}

inline void GLMatrix::Scale(const float *scalars)
{
	Scale(glm::make_vec3(scalars));
}

inline void GLMatrix::Scale(const glm::vec3 &scalars)
{
	_modelMatrix = glm::scale(_modelMatrix, scalars);
	BindModelMatrix();
}

inline void GLMatrix::Rotate(float radians, float x, float y, float z)
{
	Rotate(radians, glm::vec3(x, y, z));
}

inline void GLMatrix::Rotate(float radians, const float *scalars)
{
	Rotate(radians, glm::make_vec3(scalars));
}

inline void GLMatrix::Rotate(float radians, const glm::vec3 &scalars)
{
	_modelMatrix = glm::rotate(_modelMatrix, radians, scalars);
	BindModelMatrix();
}

inline void GLMatrix::RotateDeg(float degrees, float x, float y, float z)
{
	RotateDeg(degrees, glm::vec3(x, y, z));
}

inline void GLMatrix::RotateDeg(float degrees, const float *axis)
{
	RotateDeg(degrees, glm::make_vec3(axis));
}

inline void GLMatrix::RotateDeg(float degrees, const glm::vec3 &axis)
{
	_modelMatrix = glm::rotate(_modelMatrix, degrees * (3.14159265358979323846f / 180.0f), axis);
	BindModelMatrix();
}

//
// View Matrix
//

inline void GLMatrix::SetCamera(float posX, float posY, float posZ, float lookAtX, float lookAtY, float lookAtZ)
{
	_viewMatrix = glm::lookAt(glm::vec3(posX, posY, posZ), glm::vec3(lookAtX, lookAtY, lookAtZ), glm::vec3(0.0f, 1.0f, 0.0f));
	BindViewMatrix();
}

inline void GLMatrix::SetCamera(float posX, float posY, float posZ, float lookAtX, float lookAtY, float lookAtZ, float upX, float upY, float upZ)
{
	_viewMatrix = glm::lookAt(glm::vec3(posX, posY, posZ), glm::vec3(lookAtX, lookAtY, lookAtZ), glm::vec3(upX, upY, upZ));
	BindViewMatrix();
}

inline void GLMatrix::SetCamera(const float *pos, const float *lookAt)
{
	_viewMatrix = glm::lookAt(glm::make_vec3(pos), glm::make_vec3(lookAt), glm::vec3(0.0f, 1.0f, 0.0f));
	BindViewMatrix();
}

inline void GLMatrix::SetCamera(const float *pos, const float *lookAt, const float *up)
{
	_viewMatrix = glm::lookAt(glm::make_vec3(pos), glm::make_vec3(lookAt), glm::make_vec3(up));
	BindViewMatrix();
}

inline void GLMatrix::SetCamera(const glm::vec3 &pos, const glm::vec3 &lookAt)
{
	_viewMatrix = glm::lookAt(pos, lookAt, glm::vec3(0.0f, 1.0f, 0.0f));
	BindViewMatrix();
}

inline void GLMatrix::SetCamera(const glm::vec3 &pos, const glm::vec3 &lookAt, const glm::vec3 &up)
{
	_viewMatrix = glm::lookAt(pos, lookAt, up);
	BindViewMatrix();
}

//
// Projection Matrix
//

inline void GLMatrix::SetPerspective(float fovRadians, float aspectRatio, float nearPlane, float farPlane)
{
	_projMatrix = glm::perspective(fovRadians, aspectRatio, nearPlane, farPlane);
	BindProjMatrix();
}

inline void GLMatrix::SetPerspective(float fovRadians, float width, float height, float nearPlane, float farPlane)
{
	_projMatrix = glm::perspectiveFov(fovRadians, width, height, nearPlane, farPlane);
	BindProjMatrix();
}

inline void GLMatrix::SetInfinitePerspective(float fovRadians, float width, float height, float nearPlane)
{
	_projMatrix = glm::infinitePerspective(fovRadians, width/height, nearPlane);
	BindProjMatrix();
}

inline void GLMatrix::SetInfinitePerspective(float fovRadians, float aspectRatio, float nearPlane)
{
	_projMatrix = glm::infinitePerspective(fovRadians, aspectRatio, nearPlane);
	BindProjMatrix();
}

inline void GLMatrix::SetOrtho(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	_projMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
	BindProjMatrix();
}

inline void GLMatrix::SetOrtho(float left, float right, float bottom, float top)
{
	_projMatrix = glm::ortho(left, right, bottom, top);
	BindProjMatrix();
}

} // namespace opengl
#endif // GLMATRIX_INL