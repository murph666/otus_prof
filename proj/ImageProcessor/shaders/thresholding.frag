#version 330 core

layout (location = 0) out vec4 color;

in vec2 tex_coord;

uniform sampler2D fbo_tex;
uniform float threshold;
float threshold_smooth = 0.001;

void main()
{
	vec4 tex = texture(fbo_tex, tex_coord);

	float luminace = (tex.r + tex.g + tex.b) / 3.0;

	float thra = threshold - (threshold_smooth / 2.0);
	float thrb = threshold + (threshold_smooth / 2.0);

	color = vec4(smoothstep(thra, thrb, luminace));
}
