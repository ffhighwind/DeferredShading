//SOURCE: https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h

#include "GLModel.hpp"
#include "GLMatrix.hpp"
#include <algorithm>

namespace opengl {

std::string GLModel::Directory() const
{
	return _directory;
}

const std::vector<GLMesh> &GLModel::GetMeshes() const
{
	return _meshes;
}

const std::vector<GLTexture> &GLModel::GetTextures() const
{
	return _textures;
}

void GLModel::Draw(GLuint shaderID) const
{
	for (auto iter = _meshes.begin(); iter != _meshes.end(); iter++) {
		iter->Draw(shaderID);
	}
}

float GLModel::GetScaleFactor() const
{
	return _scaleFactor;
}

void GLModel::GetAABB(glm::vec3 &minbb, glm::vec3 &maxbb) const
{
	minbb = _minbb;
	maxbb = _maxbb;
}

} // namespace opengl