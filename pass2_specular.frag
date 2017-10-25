#version 330 core

uniform sampler2D PositionBuffer;
uniform sampler2D NormalBuffer;
uniform sampler2D DiffuseSpecBuffer;

layout (location = 0) out vec4 Color;

in vec2 TexCoord0;

void main()
{
	float SpecularIntensity = texture(DiffuseSpecBuffer, TexCoord0).a;
	Color = vec4(SpecularIntensity, SpecularIntensity, SpecularIntensity, 1.0);
}