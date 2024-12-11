#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormPos;

out vec4 Color;
out vec3 NormPos;

void main(){
	vec3 pos = aPos;
	Color = aColor;
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}