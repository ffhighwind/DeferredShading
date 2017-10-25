#pragma once
#ifndef DEFERREDSHADER_HPP
#define DEFERREDSHADER_HPP

#define _CRT_SECURE_NO_WARNINGS

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include "GLProgram.hpp"
#include "GLModel.hpp"

enum DeferredBuffer
{
	None = 0,
	Deferred = 1,
	Diffuse = 2,
	Specular = 3,
	Normal = 4,
	Position = 5,
	Depth = 6,
};

class DeferredShader
{
public:
	DeferredShader() {}
	bool Init(int w, int h);
	void Render(float ticks, const opengl::GLModel &model, const glm::vec3 &camPosition);
	void SaveFile(int w, int h) const;
	void ToggleRotation();
	void SetDrawMode(DeferredBuffer mode);
	void SetPerspective(float nearPlane, float farPlane);

private:
	bool InitGBuffer();
	bool InitShaders();
	void InitLights();
	void InitQuad();
	void InitCube();
	void Pass1_GBuffer(const opengl::GLModel &model);
	void Pass2_DeferredShading(const glm::vec3 &camPosition);
	void Pass3_Lights();
	void Pass2_BufferMode(opengl::GLProgram &shaderProg);
	void Pass2_DepthMode();
	void SetLights();

	int _w, _h;
	GLuint _gBuffer, _positionBuffer, _normalBuffer, _diffuseSpecBuffer, _depthBuffer;
	GLuint _quadVAO, _quadVBO, _cubeVAO, _cubeVBO, _floorVAO, _floorVBO;
	//GLuint _rboDepth;
	static const GLuint _attachments[3];
	std::vector<glm::vec3> _lightPositions;
	std::vector<glm::vec3> _lightColors;

	GLuint _model1, _model2, _view1, _norm1, _view2, _proj1, _proj2;
	opengl::GLProgram _shaderGBuffer, _shaderDeferred, _shaderLights;
	opengl::GLProgram _shaderPosition, _shaderNormal, _shaderDiffuse, _shaderSpecular, _shaderDepth;
	const float WORLD_SCALE = 6.0f;
	const float LIGHT_SCALE = WORLD_SCALE * 0.002f;
	const char *PASS1_VS = "pass1_gbuffer.vert";
	const char *PASS1_FS = "pass1_gbuffer.frag";
	const char *PASS2_VS = "pass2_deferred.vert";
	const char *PASS2_FS = "pass2_deferred.frag";
	const char *PASS3_VS = "pass3_lights.vert";
	const char *PASS3_FS = "pass3_lights.frag";
	const char *POSITION_FS = "pass2_position.frag";
	const char *NORMAL_FS = "pass2_normal.frag";
	const char *DIFFUSE_FS = "pass2_diffuse.frag";
	const char *SPECULAR_FS = "pass2_specular.frag";
	const char *DEPTH_FS = "pass2_depth.frag";

	DeferredBuffer _drawMode = DeferredBuffer::Deferred;
	bool _isRotating = false;
	float _rotationAngle = 0.0f;
	const float ROTATION_CONSTANT = 0.005f;
	float _nearPlane = 0.1f;
	float _farPlane = 1000.0f;

	const int JPG_QUALITY = 85;
	const int RAND_CONST = 1100;
	const unsigned int NUM_LIGHTS = 150;
	const float ATTENUATION = 8.0f;
	const float LIGHT_RADIUS = 3.5f;
};

#endif // DEFERREDSHADER_HPP