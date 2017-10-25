#version 330 core

uniform sampler2D DepthBuffer;
uniform float NearPlane;
uniform float FarPlane;

layout (location = 0) out vec4 Color;

in vec2 TexCoord0;

void main()
{
	float z = texture(DepthBuffer, TexCoord0).x;
	// linearize
	z = 2.0f * NearPlane / (FarPlane + NearPlane - z * (FarPlane - NearPlane));
	// invert greyscale color
	//z = abs(z - 1.0);
	Color = vec4(z, z, z, 1.0);
}