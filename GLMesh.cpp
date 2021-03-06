//SOURCE: https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h

#include "GLMesh.hpp"

namespace opengl {

void GLMesh::Draw(GLuint shaderID) const
{
	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < _textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string name;
		if (_textures[i].type == TextureType::Diffuse) {
			name = "texture_diffuse" + std::to_string(diffuseNr);
			diffuseNr++;
		}
		else if (_textures[i].type == TextureType::Specular) {
			name = "texture_specular" + std::to_string(specularNr);
			specularNr++;
		}
		else if (_textures[i].type == TextureType::Normal) {
			name = "texture_normal" + std::to_string(normalNr);
			normalNr++;
		}
		else if (_textures[i].type == TextureType::Height) {
			//name = "texture_height" + std::to_string(heightNr);
			//heightNr++;
			continue;
		}
		else {
			continue; //invalid texture
		}
		// now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, _textures[i].id);
	}

	// draw mesh
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _numTriangles, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// set everything back to defaults
	for (unsigned int i = 0; i < _textures.size(); ++i) {
		glActiveTexture(_textures[i].id);
		glBindTexture(GL_TEXTURE_2D, 0); // default black texture
	}
	//glActiveTexture(GL_TEXTURE0);
}

void GLMesh::Load(const std::vector<GLVertex> &vertices, const std::vector<GLuint> &indices, const std::vector<GLTexture> &textures)
{
	//this->vertices = vertices;
	//this->indices = indices;
	_textures = textures;
	_numTriangles = indices.size();

	// create buffers/arrays
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLVertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, TexCoords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, Tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)offsetof(GLVertex, Bitangent));

	glBindVertexArray(0);
}

void GLMesh::Unload()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
	//glDeleteTextures
}

GLuint GLMesh::Id() const
{
	return _vao;
}

bool GLMesh::HasTextureMap(TextureType type) const
{
	for (auto iter = _textures.begin(); iter != _textures.end(); iter++) {
		if (iter->type == type) {
			return true;
		}
	}
	return false;
}


} // namespace opengl