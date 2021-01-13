#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = 0) in vec3 inPos;
layout(location = 0) out vec3 outColor;

layout(set = 0, binding = 0) uniform MWP {
	mat4 m;
	mat4 v;
	mat4 p;
} mvp;

void main() {
    gl_Position = mvp.p * mvp.v * mvp.m * vec4(inPos, 1);
	outColor = abs(gl_Position.xyz);
}