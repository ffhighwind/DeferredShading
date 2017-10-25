//original source: https://github.com/JoeyDeVries/LearnOpenGL/tree/master/src/5.advanced_lighting/8.2.deferred_shading_volumes
#version 330 core

layout (location = 0) out vec4 Color;

uniform vec3 ObjectColor;

void main()
{           
	Color = vec4(ObjectColor, 1.0);
}