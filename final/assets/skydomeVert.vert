#version 330 core
//abrahm code
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormPos;

out vec4 Color;
out vec3 NormPos;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 camPos;
uniform vec3 domeColor;

void main(){
	Color = vec4(domeColor, 1.0);
	gl_Position = proj * view * model * vec4(aPos.x + camPos.x, aPos.y - camPos.y*1.25, aPos.z + camPos.z, 1.0);
}