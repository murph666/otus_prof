#version 450 core

layout (location = 0) out vec4 color;

in vec2 tex_coord;

uniform sampler2D fbo_tex;
uniform int operator_u;
uniform int brush_u;
uniform float radius_u;

// op  :   0: neutral  1: dilatation   2: erosion
// brush:  0: disk     1: star         2: diamond  3: square

#define p .3

bool brush(vec2 d)
{
    d = abs(d);
    return  brush_u==0 ? dot(d,d) <= radius_u*radius_u             // disk
          : brush_u==1 ? pow(d.x,p)+pow(d.y,p) <= pow(radius_u,p)  // star(p)
          : brush_u==2 ? d.x+d.y < radius_u                        // diamond
          : brush_u==3 ? max(d.x,d.x*.5+d.y*.87) < radius_u        // hexagon
          : true;                                                  // square  
}

void main()
{
    vec2 U = gl_FragCoord.xy;

	vec2 R = textureSize(fbo_tex, 0), d;

    vec4 m=vec4(1e9), M=-m;
	for (float y = -radius_u; y<=radius_u; y++)
	  for (float x = -radius_u; x<=radius_u; x++)
          if (brush(d=vec2(x,y))) {
              vec4 t = texture(fbo_tex, (U+d)/R);
              m = min(m, t); M = max(M, t);
          }

    color =  operator_u==1 ? M      // dilatation
           : operator_u==2 ? m      // erosion
           : texture(fbo_tex, U/R); // neutral
}
