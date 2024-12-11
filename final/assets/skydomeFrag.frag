#version 330 core

out vec4 FragColor;

in vec4 Color;
in vec3 NormPos;

void main(){
	FragColor = Color;
}