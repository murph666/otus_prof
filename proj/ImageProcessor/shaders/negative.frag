#version 330 core

layout (location = 0) out vec4 color;

in vec2 tex_coord;

uniform sampler2D fbo_tex;

void main()
{
	vec4 tex = texture(fbo_tex, tex_coord);
	color = vec4(1. - tex.rgb, tex.a);
}
