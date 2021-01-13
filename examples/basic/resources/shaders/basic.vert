#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = 0) in vec3 inPos;
layout(set = 0, binding =0) uniform Colors { uint first; } colors;


void main() {

	uint val = colors.first;
	float x = (val & 0xff000000) / 255.0;
	float y = (val & 0x00ff0000) / 255.0;
	float z = (val & 0x0000ff00) / 255.0;

    gl_Position = vec4(inPos + vec3(z, y, 0) * 0.000001, 1);
}