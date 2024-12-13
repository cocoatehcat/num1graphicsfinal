#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormPos;

out vec4 Color;
out vec3 NormPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 camPos;

void main(){
	Color = aColor;
	gl_Position = proj * view * model * vec4(aPos.x + camPos.x, aPos.y - camPos.y, aPos.z + camPos.z, 1.0);
}