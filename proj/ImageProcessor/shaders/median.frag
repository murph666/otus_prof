#version 330 core

layout (location = 0) out vec4 color;

in vec2 tex_coord;

uniform sampler2D fbo_tex;
uniform int alg;

#define DENOISING_MATRIX_SIZE 4
#define DENOISING_SAMPLE_DISTANCE 0.0012

const int matrixLength = DENOISING_MATRIX_SIZE * DENOISING_MATRIX_SIZE;

void insertionSort(inout vec3 arr[matrixLength]) 
{ 
    for(int index = 0; index < 3; index++)
    {
        int i, j; 
        float key;
        for (i = 1; i < matrixLength; i++)
        { 
            key = arr[i][index]; 
            j = i - 1; 
    
            while (j >= 0 && arr[j][index] > key)
            { 
                arr[j + 1][index] = arr[j][index]; 
                j = j - 1; 
            } 
            arr[j + 1][index] = key; 
        }
    }
}

vec4 Denoise(vec2 uv){
    vec3 matrix[matrixLength];
    
    vec2 noiseUV;
    
    for(int i = 0; i < matrixLength; i++){
    
        int x = (i % DENOISING_MATRIX_SIZE) - DENOISING_MATRIX_SIZE / 2;
        int y = (i / DENOISING_MATRIX_SIZE) - DENOISING_MATRIX_SIZE / 2;
        
        noiseUV = uv + vec2(float(x) * DENOISING_SAMPLE_DISTANCE, float(y) * DENOISING_SAMPLE_DISTANCE);
        
        vec4 samp = texture(fbo_tex, noiseUV);
        matrix[i] = samp.rgb;
    }
    
    insertionSort(matrix);
    
    return vec4(matrix[matrixLength / 2], 1.);
}

const float scaleFactor = 150.0;
const float invScaleFactor = 1.0 / scaleFactor;

vec3 GetTexture(vec2 uv){
	return texture(fbo_tex, uv).rgb;
}

vec4 Downscale(vec2 uv)
{
    vec2 g = floor(uv * scaleFactor) * invScaleFactor;
	vec2 p = fract(uv * scaleFactor);
    
	vec3 c = GetTexture(g);
	vec3 c2 = GetTexture(g + vec2(invScaleFactor, 0.0));
	vec3 c3 = GetTexture(g + vec2(invScaleFactor, invScaleFactor));
	vec3 c4 = GetTexture(g + vec2(0.0, invScaleFactor));
    
    if (uv.x > 0.5) c = mix(mix(c, c2, p.x), mix(c4, c3, p.x), p.y);
    
    return vec4(c, 1.0);
}

void main()
{
	color = (alg == 0) ? Downscale(tex_coord) : Denoise(tex_coord);	
}
