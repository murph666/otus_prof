#version 330 core

layout (location = 0) out vec4 color;

in vec2 tex_coord;

uniform sampler2D fbo_tex;
uniform vec3 multiplier;

void main()
{
	vec4 tex = texture(fbo_tex, tex_coord);
	color = vec4(vec3(dot(tex.rgb, multiplier)), tex.a);
}
