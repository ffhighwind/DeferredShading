//SOURCE: https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h

#pragma once
#ifndef GLMODEL_HPP
#define GLMODEL_HPP

#include <GL\glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLModelLoader.hpp"

#include "GLMesh.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

namespace opengl {

class GLModelLoader;

class GLModel
{
public:
	GLModel() {}
	std::string Directory() const;
	const std::vector<GLMesh> &GetMeshes() const;
	const std::vector<GLTexture> &GetTextures() const;
	float GetScaleFactor() const;
	void GetAABB(glm::vec3 &minbb, glm::vec3 &maxbb) const;
	void Draw(GLuint shaderID) const;

private:
	std::vector<GLMesh> _meshes;
	std::vector<GLTexture> _textures;
	std::string _directory;
	float _scaleFactor;
	glm::vec3 _minbb, _maxbb;

	friend class opengl::GLModelLoader;
};


} // namespace opengl
#endif // GLMODEL_HPP