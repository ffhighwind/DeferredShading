//original source: https://github.com/JoeyDeVries/LearnOpenGL/tree/master/src/5.advanced_lighting/8.2.deferred_shading_volumes
#version 330 core

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

layout (location = 0) out vec3 PositionBuffer;
layout (location = 1) out vec3 NormalBuffer;
layout (location = 2) out vec4 DiffuseSpecBuffer;

in vec3 Position0;
in vec2 TexCoord0;
in vec3 Normal0;
in vec3 Tangent0;
in vec3 Bitangent0;

void main()
{    
	PositionBuffer = Position0;

	vec3 Normal = normalize(Normal0);
	vec3 Tangent = normalize(Tangent0);
	vec3 Bitangent = normalize(Bitangent0);
	vec3 NormalBump = texture(texture_normal1, TexCoord0).xyz * 2.0 - 1.0;
	mat3 tbnMatrix = mat3(Tangent, Bitangent, Normal);
	NormalBuffer = normalize(tbnMatrix * NormalBump);

	DiffuseSpecBuffer.rgb = texture(texture_diffuse1, TexCoord0).rgb;
	DiffuseSpecBuffer.a = texture(texture_specular1, TexCoord0).r;
}