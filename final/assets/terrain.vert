#version 330

layout (location = 0) in vec3 Pos;

uniform mat4 viewMatrix;

void main() {
	gl_Position = viewMatrix * vec4(Pos, 1.0);
}