#include "pch.h"
#include "Shader.h"

#include "Lolibox/Utility/FileSystem.h"
#include "Lolibox/Logger.h"

#include <imgui.h>

namespace lolibox
{

	GLint Shader::CompileShader(GLuint type, const void* src, uint32_t length)
	{
		const auto shader = glCreateShader(type);
		GLint length_ = length;
		glShaderSource(shader, 1, reinterpret_cast<const GLchar* const*>(&src), &length_);
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint logLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> log(logLength);
			glGetShaderInfoLog(shader, logLength, nullptr, log.data());
			glDeleteShader(shader);
			Logger::Error("Unable to compile shader:\n%s\n", log.data());
		}

		return shader;
	}

	GLint Shader::LinkProgram(GLuint vertexShader, GLuint fragmentShader)
	{
		const auto program = glCreateProgram();

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint logLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> log(logLength);
			glGetProgramInfoLog(program, logLength, nullptr, log.data());
			glDeleteProgram(program);
			Logger::Error("Unable to link program:\n", log.data());
		}

		return program;
	}


	Shader::Shader(const std::string& vertPath, const std::string& fragPath)
	{
		std::string vertSrc = util::FileToString(vertPath);
		std::string fragSrc = util::FileToString(fragPath);

		const auto vs = CompileShader(GL_VERTEX_SHADER, vertSrc.c_str(), vertSrc.size());
		const auto fs = CompileShader(GL_FRAGMENT_SHADER, fragSrc.c_str(), fragSrc.size());

		m_ProgramID = LinkProgram(vs, fs);

		glDetachShader(m_ProgramID, vs);
		glDeleteShader(vs);
		glDetachShader(m_ProgramID, fs);
		glDeleteShader(fs);
	}

	Shader::~Shader()
	{
		Free();
	}

	void Shader::Use()
	{
		glUseProgram(m_ProgramID);

		for (auto& u : m_Uniforms)
		{
			if (u->m_NeedUpdate)
			{
				if (!u->SetUniform(m_ProgramID))
				{
					Logger::Error("Failed to update uniform '%s' (%s)", u->m_UniformName.c_str(), u->m_UniformTypeName.c_str());
				}

				u->m_NeedUpdate = false;
			}
		}
	}

	void Shader::Unuse()
	{
		glUseProgram(0);
	}

	void Shader::AttachUniform(const std::shared_ptr<ShaderUniform>& uniform)
	{
		m_Uniforms.push_back(uniform);
		uniform->m_NeedUpdate = true;
	}

	void Shader::Free()
	{
		glDeleteProgram(m_ProgramID);
	}

}
