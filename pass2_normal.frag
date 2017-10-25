#version 330 core

uniform sampler2D PositionBuffer;
uniform sampler2D NormalBuffer;
uniform sampler2D DiffuseSpecBuffer;

layout (location = 0) out vec4 Color;

in vec2 TexCoord0;

void main()
{
	Color = vec4(texture(NormalBuffer, TexCoord0).rgb, 1.0);
}