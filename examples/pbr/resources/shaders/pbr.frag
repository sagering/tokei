#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform UBO {
	mat4 m;
	mat4 v;
	mat4 p;
	
	vec3 cameraPosition;
} ubo;

const float PI = 3.14159265359;

// fresnel reflectance, Schlick approximation
// F0 is metalness or characteristic specular color
vec3 F(float dotNL, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(1.0 - dotNL, 5.0); 
}

// GGX surface normal distribution function
float D(float dotNH, float roughness)
{
	float alpha = roughness * roughness;
	float alpha2 = alpha * alpha;
	float denom = dotNH * dotNH * (alpha2 - 1.0) + 1.0;
	return (alpha2)/(PI * denom*denom); 
}

// Schlick Smith GGX shadowing function
float G(float dotNL, float dotNV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r*r) / 8.0;
	float GL = dotNL / (dotNL * (1.0 - k) + k);
	float GV = dotNV / (dotNV * (1.0 - k) + k);
	return GL * GV;
}

vec3 BRDF(vec3 L, vec3 V, vec3 N, vec3 metallness, float roughness)
{
	vec3 H = normalize (V + L);
	
	float dotNV = clamp(dot(N, V), 0.0, 1.0);
	float dotNL = clamp(dot(N, L), 0.0, 1.0);
	float dotNH = clamp(dot(N, H), 0.0, 1.0);

	vec3 lightColor = vec3(1.0);

	if (dotNL <= 0.0)
	{
		return vec3(0, 0, 0);
	}
	
	if (dotNV <= 0.0)
	{
		// interpolation artefact: some normals are facing away from the camera
		discard;
	}
	
	if (dotNH <= 0.0)
	{
		return vec3(0, 1, 0);
	}
	
	float D = D(dotNH, roughness); 
	float G = G(dotNL, dotNV, roughness);
	vec3  F = F(dotNV, metallness);

	vec3 spec = D * F * G / (4.0 * dotNL * dotNV);
	
	return spec * dotNL * lightColor;
}

const vec3 metallness = vec3(1, 0.782, 0.344); // gold
const float roughness = 0.3;

void main() {
    // surface normal
	vec3 N = normalize(inNormal);
	// viewing direction
	vec3 V = normalize(ubo.cameraPosition - inPosition);
	// light direction
	vec3 L = normalize(vec3(1, 1, 1));
		
	vec3 color = BRDF(L, V, N, metallness, roughness);
	color = pow(color, vec3(0.4545));
	color += 0.03 * metallness;

	outColor = vec4(color, 1.0);
}