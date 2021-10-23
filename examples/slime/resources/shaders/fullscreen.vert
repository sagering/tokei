#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec2 uv;

void main() {
    const vec2 positions[4] = vec2[](
        vec2(-1, -1),
        vec2(-1, 1),
		vec2(1, -1),
        vec2(1, 1)
    );
	
    const vec2 coords[4] = vec2[](
        vec2(0, 0),
        vec2(0, 1),
        vec2(1, 0),
		vec2(1, 1)
    );
	
	int i = gl_VertexIndex;
	if(i>3) --i;

    uv = coords[gl_VertexIndex%4];
    gl_Position = vec4(positions[gl_VertexIndex%4], 0.0, 1.0);
}