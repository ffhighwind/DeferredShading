#include "GLMatrix.hpp"

namespace opengl {

// singleton global variable
GLMatrix GL;

void GLMatrix::Pop()
{
	_modelMatrix = *_matrixStack.back();
	delete[] _matrixStack.back();
	_matrixStack.pop_back();
	BindModelMatrix();
}

void GLMatrix::BindModelViewProj()
{
	glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(_modelMatrix));
	glUniformMatrix4fv(_viewLoc, 1, GL_FALSE, glm::value_ptr(_viewMatrix));
	glUniformMatrix4fv(_projLoc, 1, GL_FALSE, glm::value_ptr(_projMatrix));
};

void GLMatrix::Bind()
{
	glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(_modelMatrix));
	glUniformMatrix4fv(_viewLoc, 1, GL_FALSE, glm::value_ptr(_viewMatrix));
	glUniformMatrix4fv(_projLoc, 1, GL_FALSE, glm::value_ptr(_projMatrix));
	glUniformMatrix3fv(_normalLoc, 1, GL_FALSE, glm::value_ptr(_normalMatrix));
};

glm::vec3 GLMatrix::GetPosition() const
{
	glm::mat4 inverseView = inverse(_viewMatrix);
	return inverseView * glm::vec4(0.0, 0.0, 0.0, 1.0);
}

glm::vec3 GLMatrix::GetDirection() const
{
	glm::mat4 inverseView = inverse(_viewMatrix);
	return inverseView * glm::vec4(0.0, 0.0, 1.0, 0.0);
}

void GLMatrix::GetCamera(glm::vec3 &camPosition, glm::vec3 &camDirection) const
{
	glm::mat4 inverseView = inverse(_viewMatrix);
	camPosition = inverseView * glm::vec4(0.0, 0.0, 0.0, 1.0);
	camDirection = inverseView * glm::vec4(0.0, 0.0, 1.0, 0.0);
}

} // namespace opengl