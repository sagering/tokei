#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;

layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec3 outNormal;

layout(set = 0, binding = 0) uniform UBO {
	mat4 m;
	mat4 v;
	mat4 p;
	
	vec3 camera;
} ubo;

void main() {
	outPosition = vec3(ubo.m * vec4(inPosition, 1));
	outNormal   = vec3(ubo.m * vec4(inNormal, 0));
    gl_Position = ubo.p * ubo.v * vec4(outPosition, 1.0);
}