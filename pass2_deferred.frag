//original source: https://github.com/JoeyDeVries/LearnOpenGL/tree/master/src/5.advanced_lighting/8.2.deferred_shading_volumes
#version 330 core

uniform sampler2D PositionBuffer;
uniform sampler2D NormalBuffer;
uniform sampler2D DiffuseSpecBuffer;

struct Light
{
	vec3 Position;
	vec3 Color;
	float Radius;
	float Attenuation;
};
const int NUM_LIGHTS = 150;
uniform Light lights[NUM_LIGHTS];
const float AmbientLight = 0.01;
uniform vec3 CamPosition;

in vec2 TexCoord0;

out vec4 Color;

void main()
{
	vec3 DiffuseColor = texture(DiffuseSpecBuffer, TexCoord0).rgb;
	vec3 Position = texture(PositionBuffer, TexCoord0).rgb;
	vec3 Normal = texture(NormalBuffer, TexCoord0).rgb;
	float SpecSpread = texture(DiffuseSpecBuffer, TexCoord0).a;
	vec3 LightAccumulated  = DiffuseColor * AmbientLight;
	vec3 ViewDirection  = normalize(CamPosition - Position);
	for(int i = 0; i < NUM_LIGHTS; i++)
	{
		vec3 LightDirection = lights[i].Position - Position;
		float DistanceToLight = length(LightDirection);
		float DiffuseIntensity = dot(LightDirection, Normal);
		if(DistanceToLight < lights[i].Radius && DiffuseIntensity > 0.0)
		{
			LightDirection = normalize(LightDirection);
			vec3 DiffuseLight = DiffuseIntensity * DiffuseColor * lights[i].Color;
			vec3 HalfDir = normalize(LightDirection + ViewDirection);
			float SpecIntensity = pow(max(dot(Normal, HalfDir), 0.0), 16);
			vec3 SpecLight = lights[i].Color * SpecSpread * SpecIntensity;
			float Attenuation = 1.0 / (1.0 + lights[i].Attenuation * pow(DistanceToLight, 2));
			LightAccumulated += Attenuation * (DiffuseLight + SpecLight);
		}
	}
	Color = vec4(LightAccumulated, 1.0);
}