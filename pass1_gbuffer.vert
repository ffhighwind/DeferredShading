//original source: https://github.com/JoeyDeVries/LearnOpenGL/tree/master/src/5.advanced_lighting/8.2.deferred_shading_volumes
#version 330 core

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;
layout (location = 3) in vec3 Tangent;
layout (location = 4) in vec3 Bitangent;

out vec3 Position0;
out vec2 TexCoord0;
out vec3 Normal0;
out vec3 Tangent0;
out vec3 Bitangent0;

void main()
{
	// Transform position from model space to world space.
	vec4 worldPosition = ModelMatrix * vec4(Position, 1.0);
	Position0 = worldPosition.xyz;
	TexCoord0 = TexCoord;

	// Normal, Tangent, Bitangent used to calculate TBN Matrix for normal mapping.
	Normal0 = normalize(NormalMatrix * Normal);
	Tangent0 = normalize(NormalMatrix * Tangent);
	Bitangent0 = normalize(NormalMatrix * Bitangent);

	// Transform position from world space to projection/camera space.
	// This allows forclipping and depth culling, and stores the depth value.
	gl_Position = ProjectionMatrix * ViewMatrix * worldPosition;

}