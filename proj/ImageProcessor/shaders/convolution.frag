#version 330 core

layout (location = 0) out vec4 color;

in vec2 tex_coord;

uniform sampler2D fbo_tex;
uniform mat3 kernel;
uniform int blending;
uniform float blend_intensity;

vec4 convolve(mat3 kernel, vec2 kernel_step, sampler2D tex , vec2 center)
{
	vec4 res = vec4(.0);

	res += texture(tex, vec2(center.x - kernel_step.x, center.y - kernel_step.y)) * kernel[0][0];
	res += texture(tex, vec2(center.x                , center.y - kernel_step.y)) * kernel[0][1];
	res += texture(tex, vec2(center.x + kernel_step.x, center.y - kernel_step.y)) * kernel[0][2];
	res += texture(tex, vec2(center.x - kernel_step.x, center.y                )) * kernel[1][0];
	res += texture(tex, vec2(center.x                , center.y                )) * kernel[1][1];
	res += texture(tex, vec2(center.x + kernel_step.x, center.y                )) * kernel[1][2];
	res += texture(tex, vec2(center.x - kernel_step.x, center.y + kernel_step.y)) * kernel[2][0];
	res += texture(tex, vec2(center.x                , center.y + kernel_step.y)) * kernel[2][1];
	res += texture(tex, vec2(center.x + kernel_step.x, center.y + kernel_step.y)) * kernel[2][2];

	return res;
}

void main()
{
	vec2 kernel_step = 1./ textureSize(fbo_tex, 0);
	color = convolve(kernel, kernel_step, fbo_tex, tex_coord);
	if (blending != 0)
	{
		color = color * blend_intensity + texture(fbo_tex, tex_coord);
	}
}
