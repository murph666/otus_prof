#pragma once

#include "Texture.h"
#include "Shader.h"

#include <glad/glad.h>

namespace lolibox
{
	class ComputeShader : public Shader
	{
	public:
		ComputeShader(const std::string& sourcePath);

	private:
		static GLint LinkProgram(GLuint vertexShader, GLuint fragmentShader) = delete;
		static GLint LinkProgram(GLuint computeShader);
	};
}
