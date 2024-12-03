#version 330 core
layout (location = 0) in vec4 aColor;

out vec4 Color;

void main(){
	Color = aColor;
}