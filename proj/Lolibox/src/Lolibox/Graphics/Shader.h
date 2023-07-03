#pragma once

#include "Texture.h"
#include "Uniforms/ShaderUniform.h"

#include <glad/glad.h>

namespace lolibox
{
	class Shader
	{
	public:
		Shader(const std::string& vertPath, const std::string& fragPath);
		~Shader();

		auto GetProgramID() -> GLuint { return m_ProgramID; }

		void Use();
		void Unuse();
		void AttachUniform(const std::shared_ptr<ShaderUniform>& uniform);

	protected:
		Shader() = default;
		void Free();

		static GLint CompileShader(GLuint type, const void* src, uint32_t length);
		static GLint LinkProgram(GLuint vertexShader, GLuint fragmentShader);

		GLuint m_ProgramID = 0;
		std::vector<std::shared_ptr<ShaderUniform>> m_Uniforms;
	};
}
