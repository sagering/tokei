#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform texture2D t;
layout(set = 0, binding = 2) uniform sampler s;

void main() {
	outColor = 	outColor = texture(sampler2D(t, s), vec2(0, 0));

}