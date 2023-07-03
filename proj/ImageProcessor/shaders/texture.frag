#version 330 core

layout (location = 0) out vec4 color;

in vec2 tex_coord;

uniform sampler2D fbo_tex;

void main()
{
	color = texture(fbo_tex, tex_coord);
}
