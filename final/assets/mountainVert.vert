#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 Color; // Using color instead of texture right now
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() 
{
	Color = aColor;
	vec3 pos = aPos;

	gl_Position = proj * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = aNormal;
}