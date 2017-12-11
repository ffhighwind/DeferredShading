//SOURCE: https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h

#pragma once
#ifndef GLMESH_HPP
#define GLMESH_HPP

#include <GL/glew.h>

#include <assimp/Importer.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace opengl {


struct GLVertex 
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};


enum class TextureType
{
	Unknown = 0,
	Diffuse,
	Specular,
	Normal,
	Height,
};


struct GLTexture 
{
	unsigned int id;
	TextureType type;
	aiString path;
};


class GLMesh 
{
public:
	GLMesh() { }
	void Load(const std::vector<GLVertex> &vertices, const std::vector<GLuint> &indices, const std::vector<GLTexture> &textures);
	void Unload();
	void Draw(GLuint shaderID) const;
	GLuint Id() const; // vao ID
	bool HasTextureMap(TextureType type) const;

private:
	std::vector<GLTexture> _textures;
	int _numTriangles;
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
};


} // namespace opengl
#endif // GLMESH_HPP