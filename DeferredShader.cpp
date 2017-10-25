#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <random>
#include "DeferredShader.hpp"
#include <GL/glew.h>
#include "GLShader.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "GLMatrix.hpp"

#include "stb_image_write.hpp"
#include "stb_image.hpp"

using opengl::GL;

bool DeferredShader::Init(int w, int h)
{
	_w = w;
	_h = h;

	if (!InitGBuffer() || !InitShaders()) {
		return false;
	}
	InitLights();
	InitQuad();
	InitCube();


	return true;
}

bool DeferredShader::InitGBuffer()
{
	glGenFramebuffers(1, &_gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);
	glGenTextures(1, &_positionBuffer);
	glGenTextures(1, &_normalBuffer);
	glGenTextures(1, &_diffuseSpecBuffer);
	glGenTextures(1, &_depthBuffer);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, _positionBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, _w, _h, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _positionBuffer, 0);

	glBindTexture(GL_TEXTURE_2D, _normalBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, _w, _h, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _normalBuffer, 0);

	glBindTexture(GL_TEXTURE_2D, _diffuseSpecBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _w, _h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _diffuseSpecBuffer, 0);

	glBindTexture(GL_TEXTURE_2D, _depthBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _w, _h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	glTexParameteri (GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthBuffer, 0);

	const GLuint attachmentsArray[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachmentsArray);

	// Check framebuffer
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Framebuffer is incomplete." << std::endl;
		return false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

bool DeferredShader::InitShaders()
{
	if (!_shaderGBuffer.Create(PASS1_VS, PASS1_FS)) {
		return false;
	}
	if (!_shaderDeferred.Create(PASS2_VS, PASS2_FS)) {
		return false;
	}
	if (!_shaderLights.Create(PASS3_VS, PASS3_FS)) {
		return false;
	}
	if (!_shaderPosition.Create(PASS2_VS, POSITION_FS)) {
		return false;
	}
	if (!_shaderNormal.Create(PASS2_VS, NORMAL_FS)) {
		return false;
	}
	if (!_shaderDiffuse.Create(PASS2_VS, DIFFUSE_FS)) {
		return false;
	}
	if (!_shaderSpecular.Create(PASS2_VS, SPECULAR_FS)) {
		return false;
	}
	if (!_shaderDepth.Create(PASS2_VS, DEPTH_FS)) {
		return false;
	}

	_shaderDeferred.Bind();
	_shaderDeferred.GetUniform("PositionBuffer").Set(0);
	_shaderDeferred.GetUniform("NormalBuffer").Set(1);
	_shaderDeferred.GetUniform("DiffuseSpecBuffer").Set(2);

	_shaderDiffuse.Bind();
	_shaderDiffuse.GetUniform("PositionBuffer").Set(0);
	_shaderDiffuse.GetUniform("NormalBuffer").Set(1);
	_shaderDiffuse.GetUniform("DiffuseSpecBuffer").Set(2);

	_shaderNormal.Bind();
	_shaderNormal.GetUniform("PositionBuffer").Set(0);
	_shaderNormal.GetUniform("NormalBuffer").Set(1);
	_shaderNormal.GetUniform("DiffuseSpecBuffer").Set(2);

	_shaderPosition.Bind();
	_shaderPosition.GetUniform("PositionBuffer").Set(0);
	_shaderPosition.GetUniform("NormalBuffer").Set(1);
	_shaderPosition.GetUniform("DiffuseSpecBuffer").Set(2);

	_shaderSpecular.Bind();
	_shaderSpecular.GetUniform("PositionBuffer").Set(0);
	_shaderSpecular.GetUniform("NormalBuffer").Set(1);
	_shaderSpecular.GetUniform("DiffuseSpecBuffer").Set(2);

	_shaderDepth.Bind();
	_shaderDepth.GetUniform("DepthBuffer").Set(3);
	//_shaderDepth.GetUniform("NearPlane").Set(_nearPlane);
	//_shaderDepth.GetUniform("FarPlane").Set(_farPlane);

	_model1 = _shaderGBuffer.GetUniform("ModelMatrix").GetLocation();
	_view1 = _shaderGBuffer.GetUniform("ViewMatrix").GetLocation();
	_proj1 = _shaderGBuffer.GetUniform("ProjectionMatrix").GetLocation();
	_norm1 = _shaderGBuffer.GetUniform("NormalMatrix").GetLocation();

	_model2 = _shaderLights.GetUniform("ModelMatrix").GetLocation();
	_view2 = _shaderLights.GetUniform("ViewMatrix").GetLocation();
	_proj2 = _shaderLights.GetUniform("ProjectionMatrix").GetLocation();

	return _shaderLights.Validate();
}

void DeferredShader::SetDrawMode(DeferredBuffer mode)
{
	_drawMode = mode;
}

void DeferredShader::InitLights()
{
	srand(RAND_CONST);
	for (unsigned int i = 0; i < NUM_LIGHTS; i++) {
		// positions
		float x = ((rand() % 1000) / 1000.0f) * WORLD_SCALE - WORLD_SCALE / 2.0f;
		float y = ((rand() % 1000) / 1000.0f) * WORLD_SCALE - WORLD_SCALE / 2.0f;
		float z = ((rand() % 1000) / 1000.0f) * WORLD_SCALE - WORLD_SCALE / 2.0f;
		x *= 1.7f;
		y *= 0.9f;
		z *= 1.7f;
		_lightPositions.push_back(glm::vec3(x, y, z));
		// colors
		float r = ((rand() % 1000) / 1000.0f)*0.6f + 0.4f; // between 0.6 and 1.0
		float g = ((rand() % 1000) / 1000.0f)*0.6f + 0.4f; // between 0.6 and 1.0
		float b = ((rand() % 1000) / 1000.0f)*0.6f + 0.4f; // between 0.6 and 1.0
		_lightColors.push_back(glm::vec3(r, g, b));
	}
	SetLights();
}

void DeferredShader::SetPerspective(float nearPlane, float farPlane)
{
	_nearPlane = nearPlane;
	_farPlane = farPlane;
}

void DeferredShader::Render(float ticks, const opengl::GLModel &model, const glm::vec3 &camPosition)
{
	if (_isRotating) {
		_rotationAngle += ROTATION_CONSTANT;
	}
	switch (_drawMode) 
	{
		case DeferredBuffer::Deferred:
			Pass1_GBuffer(model);
			Pass2_DeferredShading(camPosition);
			Pass3_Lights();
			break;
		case DeferredBuffer::Diffuse:
			Pass1_GBuffer(model);
			Pass2_BufferMode(_shaderDiffuse);
			break;
		case DeferredBuffer::Specular:
			Pass1_GBuffer(model);
			Pass2_BufferMode(_shaderSpecular);
			break;
		case DeferredBuffer::Normal:
			Pass1_GBuffer(model);
			Pass2_BufferMode(_shaderNormal);
			break;
		case DeferredBuffer::Position:
			Pass1_GBuffer(model);
			Pass2_BufferMode(_shaderPosition);
			break;
		case DeferredBuffer::Depth:
			Pass1_GBuffer(model);
			Pass2_DepthMode();
			break;
	}
}

void DeferredShader::Pass1_GBuffer(const opengl::GLModel &model)
{
	glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderGBuffer.Bind();
	GL.SetUniforms(_model1, _view1, _proj1, _norm1);
	GL.Identity();
	GL.RotateDeg(90.0f, 0.0f, 1.0f, 0.0f);
	GL.Translate(0.0f, -WORLD_SCALE / 2.0f, 0.0f);
	GL.Scale(3*WORLD_SCALE);
	GL.BuildNormalMatrix();
	GL.Bind();
	model.Draw(_shaderGBuffer.Id());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DeferredShader::Pass2_DeferredShading(const glm::vec3 &camPosition)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shaderDeferred.Bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _positionBuffer);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, _normalBuffer);
	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, _diffuseSpecBuffer);
	_shaderDeferred.GetUniform("CamPosition").Set(camPosition);

	if (_isRotating)
		SetLights();

	glBindVertexArray(_quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, _gBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, _w, _h, 0, 0, _w, _h, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DeferredShader::Pass2_BufferMode(opengl::GLProgram &shaderProg)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shaderProg.Bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _positionBuffer);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _normalBuffer);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, _diffuseSpecBuffer);

	glBindVertexArray(_quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void DeferredShader::Pass2_DepthMode()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shaderDepth.Bind();
	_shaderDepth.GetUniform("NearPlane").Set(_nearPlane);
	_shaderDepth.GetUniform("FarPlane").Set(_farPlane);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, _depthBuffer);

	glBindVertexArray(_quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void DeferredShader::SetLights()
{
	_shaderDeferred.Bind();
	for (unsigned int i = 0; i < _lightPositions.size(); i++) {
		glm::mat4 rotMatrix;
		rotMatrix = glm::rotate(rotMatrix, _rotationAngle, glm::vec3(0.0, 1.0, 0.0));
		glm::vec3 pos = rotMatrix * glm::vec4(_lightPositions[i], 1.0f);
		_shaderDeferred.GetUniform("lights[" + std::to_string(i) + "].Position").Set(pos);
		_shaderDeferred.GetUniform("lights[" + std::to_string(i) + "].Color").Set(_lightColors[i]);
		_shaderDeferred.GetUniform("lights[" + std::to_string(i) + "].Radius").Set(LIGHT_RADIUS);
		_shaderDeferred.GetUniform("lights[" + std::to_string(i) + "].Attenuation").Set(ATTENUATION);
	}
}

void DeferredShader::Pass3_Lights()
{
	_shaderLights.Bind();
	GL.SetUniforms(_model2, _view2, _proj2);
	GL.BindModelViewProj();
	for (unsigned int i = 0; i < _lightPositions.size(); i++) {
		GL.Identity();
		glm::mat4 rotMatrix;
		rotMatrix = glm::rotate(rotMatrix, _rotationAngle, glm::vec3(0.0, 1.0, 0.0));
		glm::vec3 pos = rotMatrix * glm::vec4(_lightPositions[i], 1.0f);
		GL.Translate(pos);
		GL.Scale(LIGHT_SCALE);
		GL.BindModelMatrix();
		_shaderLights.GetUniform("ObjectColor").Set(_lightColors[i]);
		glBindVertexArray(_cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
}

void DeferredShader::InitQuad()
{
	//https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/5.advanced_lighting/8.2.deferred_shading_volumes/deferred_shading_volumes.cpp
	const float quadVertices[] = {
		// positions (x,y,z) texcoords (u, v)
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};
	// setup VAO
	glGenVertexArrays(1, &_quadVAO);
	glGenBuffers(1, &_quadVBO);
	glBindVertexArray(_quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void DeferredShader::InitCube()
{
	//https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/5.advanced_lighting/8.2.deferred_shading_volumes/deferred_shading_volumes.cpp
	const float vertices[] = {
		// back face
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
		1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
		1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // top-left
		// front face
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
		1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // bottom-right
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
		-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top-left
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
		// left face
		-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
		-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
		-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
		-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
		// right face
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
		1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right         
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
		1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left     
		// bottom face
		-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
		1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
		1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
		1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
		-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
		-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
		// top face
		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
		1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right     
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
		-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
		-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f  // bottom-left        
	};
	glGenVertexArrays(1, &_cubeVAO);
	glGenBuffers(1, &_cubeVBO);
	// fill buffer
	glBindBuffer(GL_ARRAY_BUFFER, _cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// link vertex attributes
	glBindVertexArray(_cubeVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // positions
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // texcoords
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void flip_image(unsigned char *image_data, int w, int h, int comp)
{
	// invert image vertically
	for (int x = 0; x < w * comp; x++) {
		for (int y = 0; y < h / 2; y++) {
			int index = x + y * w * comp;
			int swap_index = x + (h - y - 1) * w * comp;
			char tmp = image_data[index];
			image_data[index] = image_data[swap_index];
			image_data[swap_index] = tmp;
		}
	}
}

void get_albedo_specular(unsigned char *image_data, int w, int h, unsigned char *albedo, unsigned char *specular)
{
	for (int i = 0; i < w * h; ++i) {
		albedo[i * 3] = image_data[i * 4];
		albedo[i * 3 + 1] = image_data[i * 4 + 1];
		albedo[i *3 + 2] = image_data[i * 4 + 2];
		specular[i] = image_data[i * 4 + 3];
	}
}

void DeferredShader::SaveFile(int w, int h) const
{
	unsigned char *image_data = new unsigned char[w * h * 4];
	unsigned char *albedo = new unsigned char[w * h * 3];
	unsigned char *specular = new unsigned char[w * h];
	float *depth = new float[w * h];

	glBindFramebuffer(GL_READ_FRAMEBUFFER, _gBuffer);

	// position
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	flip_image(image_data, w, h, 3);
	stbi_write_jpg("attachment_position.jpg", w, h, 3, image_data, JPG_QUALITY);

	// normal
	glReadBuffer(GL_COLOR_ATTACHMENT1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	flip_image(image_data, w, h, 3);
	stbi_write_jpg("attachment_normal.jpg", w, h, 3, image_data, JPG_QUALITY);

	// albedo/specular
	glReadBuffer(GL_COLOR_ATTACHMENT2);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	flip_image(image_data, w, h, 4);
	get_albedo_specular(image_data, w, h, albedo, specular);
	stbi_write_jpg("attachment_albedo.jpg", w, h, 3, albedo, JPG_QUALITY); // albedo
	stbi_write_jpg("attachment_specular.jpg", w, h, 1, specular, JPG_QUALITY); // specular

	// depth
	glReadBuffer(GL_DEPTH_ATTACHMENT);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, w, h, GL_DEPTH_COMPONENT, GL_FLOAT, depth);
	// convert from float to byte (32bit to 8bit)
	for (int i = 0; i < w * h; ++i) 
	{
		// Linearize
		depth[i] = 2.0f * _nearPlane / (_farPlane + _nearPlane - depth[i] * (_farPlane - _nearPlane));
		//convert float to single 256bit color
		int tmp = int(255 * depth[i]);
		// invert greyscale: white is near, black is far
		//tmp = abs(tmp - 255);
		image_data[i] = std::min(std::max(tmp, 0), 255);
	}

	flip_image(image_data, w, h, 1);
	stbi_write_jpg("attachment_depth.jpg", w, h, 1, image_data, JPG_QUALITY);

	// final image
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glReadBuffer(GL_BACK);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, image_data);
	flip_image(image_data, w, h, 3);
	stbi_write_jpg("attachment_final.jpg", w, h, 3, image_data, JPG_QUALITY);

	delete[] albedo;
	delete[] specular;
	delete[] image_data;
	delete[] depth;
}

void DeferredShader::ToggleRotation()
{
	_isRotating = !_isRotating;
}