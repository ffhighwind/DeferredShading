//SOURCE: https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h

#ifndef GLMODEL_HPP
#define GLMODEL_HPP

#include <GL\glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GLMesh.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


namespace opengl {


class GLModel
{
public:
	GLModel() {}
	GLModel(std::string const &path, bool gammaCorrection = false, bool flipTextureY = false) {
		Load(path, gammaCorrection, flipTextureY);
	}
	//aiProcessPreset_TargetRealtime_MaxQuality, aiProcessPreset_TargetRealtime_Quality, aiProcessPreset_TargetRealtime_Fast
	bool Load(std::string const &path, bool gammaCorrection = false, bool flipTextureY = false, unsigned int assimpFlags = aiProcessPreset_TargetRealtime_MaxQuality);
	void Unload();
	void Draw(GLuint shaderID) const;
	bool HasGammaCorrection() const;
	std::string Directory() const;
	const std::vector<GLMesh> &GetMeshes() const;
	const std::vector<GLTexture> &GetTextures() const;
	float GetScaleFactor() const;
	void GetAABB(glm::vec3 &minbb, glm::vec3 &maxbb) const;

private:
	std::vector<GLTexture> _textures;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<GLMesh> _meshes;
	std::string _directory;
	bool _gammaCorrection, _flipTextureY;
	float _scaleFactor;
	const aiScene *_scene;
	glm::vec3 _minbb, _maxbb;

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void _ProcessNode(const aiNode *node);
	void _ProcessMesh(const aiMesh *mesh);

	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	std::vector<GLTexture> _LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	static GLuint _TextureFromFile(const std::string &path, const std::string &directory, bool gamma);
};


} // namespace opengl
#endif // GLMODEL_HPP