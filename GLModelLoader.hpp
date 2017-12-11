#pragma once
#ifndef GLMODELLOADER_HPP
#define GLMODELLOADER_HPP

#include <GL\glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GLMesh.hpp"
#include "GLModel.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

namespace opengl {

class GLModel;

class GLModelLoader
{
public:
	GLModelLoader() {};
	//aiProcessPreset_TargetRealtime_MaxQuality, aiProcessPreset_TargetRealtime_Quality, aiProcessPreset_TargetRealtime_Fast
	GLModel *Load(std::string const &path, bool gammaCorrection = false, bool flipTextureY = false, unsigned int assimpFlags = aiProcessPreset_TargetRealtime_MaxQuality);
	void Unload();

private:
	GLModel *_model;
	std::vector<GLTexture> _textures;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	bool _gammaCorrection, _flipTextureY;
	const aiScene *_scene;
	glm::vec3 _minbb, _maxbb;

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void _ProcessNode(const aiNode *node);
	void _ProcessMesh(const aiMesh *mesh);

	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	std::vector<GLTexture> _LoadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType texType);
	static GLuint _TextureFromFile(const std::string &path, const std::string &directory, bool gamma);
};

} // namespace opengl
#endif // GLMODELLOADER_HPP