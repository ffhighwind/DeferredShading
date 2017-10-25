//SOURCE: https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h

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


struct GLTexture 
{
	unsigned int id;
	std::string type;
	aiString path;
};


class GLMesh 
{
public:
	//std::vector<Vertex> vertices;
	//std::vector<GLuint> indices;

	GLMesh() { }
	void Load(const std::vector<GLVertex> &vertices, const std::vector<GLuint> &indices, const std::vector<GLTexture> &textures);
	void Unload();
	void Draw(GLuint shaderID) const;
	GLuint Id() const; // vao ID

private:
	std::vector<GLTexture> textures;
	int _numTriangles;
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
};


#endif // GLMESH_HPP
} // namespace opengl