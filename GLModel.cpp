//SOURCE: https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/mesh.h

#include "GLModel.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"
#include <float.h>
#include "GLMatrix.hpp"
#include <algorithm>

namespace opengl {

bool GLModel::HasGammaCorrection() const
{
	return _gammaCorrection;
}

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
	GL.Scale(_scaleFactor);
	for (unsigned int i = 0; i < _meshes.size(); i++) {
		_meshes[i].Draw(shaderID);
	}
}

bool GLModel::Load(std::string const &path, bool gammaCorrection, bool flipTextureY, unsigned int assimpFlags)
{
	// read file via ASSIMP
	this->_gammaCorrection = gammaCorrection;
	this->_flipTextureY = flipTextureY;
	Assimp::Importer importer;
	_scene = importer.ReadFile(path, assimpFlags);
	// check for errors
	if (_scene == nullptr || _scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || _scene->mRootNode == nullptr) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return false;
	}
	// retrieve the directory path of the filepath
	_directory = "";
	int loc = path.find_last_of("/\\");
	if (loc != std::string::npos) {
		_directory = path.substr(0, loc);
	}

	// process ASSIMP's root node recursively
	_scaleFactor = 1.0f;
	_minbb = glm::vec3(FLT_MAX);
	_maxbb = glm::vec3(FLT_MIN);
	_ProcessNode(_scene->mRootNode);

	float tmp = _maxbb.x - _minbb.x;
	tmp = _maxbb.y - _minbb.y > tmp ? _maxbb.y - _minbb.y : tmp;
	tmp = _maxbb.z - _minbb.z > tmp ? _maxbb.z - _minbb.z : tmp;
	_scaleFactor = 1.0f / tmp;
	return true;
}

void GLModel::Unload()
{
	for (unsigned int i = 0; i < _textures.size(); i++) {
		glDeleteTextures(1, &_textures[i].id);
	}
}


void GLModel::_ProcessNode(const aiNode *node)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = _scene->mMeshes[node->mMeshes[i]];
		_ProcessMesh(mesh);
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		_ProcessNode(node->mChildren[i]);
	}
}

void GLModel::_ProcessMesh(const aiMesh *mesh)
{
	// data to fill
	std::vector<GLVertex> vertices;
	std::vector<GLuint> indices;
	std::vector<GLTexture> meshTextures;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		GLVertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		if (mesh->HasPositions()) {
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			_minbb.x = std::min(_minbb.x, vector.x);
			_minbb.y = std::min(_minbb.y, vector.y);
			_minbb.z = std::min(_minbb.z, vector.z);
			_maxbb.x = std::max(_maxbb.x, vector.x);
			_maxbb.y = std::max(_maxbb.y, vector.y);
			_maxbb.z = std::max(_maxbb.z, vector.z);
		}
		// normals
		if (mesh->HasNormals()) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}
		// texture coordinates
		vertex.TexCoords.x = 0.0f;
		vertex.TexCoords.y = 0.0f;
		if (mesh->HasTextureCoords(0)) {
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		// tangent
		if (mesh->HasTangentsAndBitangents()) {
			vertex.Tangent.x = mesh->mTangents[i].x;
			vertex.Tangent.y = mesh->mTangents[i].y;
			vertex.Tangent.z = mesh->mTangents[i].z;
			// bitangent
			vertex.Bitangent.x = mesh->mBitangents[i].x;
			vertex.Bitangent.y = mesh->mBitangents[i].y;
			vertex.Bitangent.z = mesh->mBitangents[i].z;
		}
		vertices.push_back(vertex);
	}
	if (_flipTextureY && mesh->HasTextureCoords(0)) {
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			vertices[i].TexCoords.y = -vertices[i].TexCoords.y;
		}
	}
	// now walk through each of the mesh's faces (a face is a triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
	// process materials
	aiMaterial* material = _scene->mMaterials[mesh->mMaterialIndex];

	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// diffuse maps
	std::vector<GLTexture> diffuseMaps = _LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	meshTextures.insert(meshTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// specular maps
	std::vector<GLTexture> specularMaps = _LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	meshTextures.insert(meshTextures.end(), specularMaps.begin(), specularMaps.end());
	// normal maps (AssImp assumes height is normals)
	std::vector<GLTexture> normalMaps = _LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	meshTextures.insert(meshTextures.end(), normalMaps.begin(), normalMaps.end());
	// height maps
	//std::vector<GLTexture> heightMaps = _LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	//meshTextures.insert(meshTextures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	GLMesh newMesh;
	newMesh.Load(vertices, indices, meshTextures);
	_meshes.push_back(newMesh);
}

std::vector<GLTexture> GLModel::_LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
	std::vector<GLTexture> matTextures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < _textures.size(); j++) {
			if (std::strcmp(_textures[j].path.C_Str(), str.C_Str()) == 0) {
				matTextures.push_back(_textures[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip) {  // if texture hasn't been loaded already, load it
			GLTexture texture;
			texture.id = _TextureFromFile(str.C_Str(), _directory, _gammaCorrection);
			texture.type = typeName;
			texture.path = str;
			matTextures.push_back(texture);
			_textures.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return matTextures;
}

GLuint GLModel::_TextureFromFile(const std::string &path, const std::string &directory, bool gamma)
{
	int width, height, nrComponents;
	GLuint textureID;
	glGenTextures(1, &textureID);
	std::string filename = path;
	if (directory.length() > 0) {
		filename = directory + '\\' + path;
	}
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format = 0;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
		//glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
		//glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Texture failed to load at path: " << path << std::endl;
	}
	stbi_image_free(data);
	return textureID;
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