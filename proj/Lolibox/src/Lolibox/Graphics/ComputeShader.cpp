#include "pch.h"
#include "ComputeShader.h"

#include "Lolibox/Utility/FileSystem.h"
#include "Lolibox/Logger.h"

#include <imgui.h>

namespace lolibox
{

	GLint ComputeShader::LinkProgram(GLuint computeShader)
	{
		const auto program = glCreateProgram();

		glAttachShader(program, computeShader);
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


	ComputeShader::ComputeShader(const std::string& sourcePath) : Shader()
	{
		std::string src = util::FileToString(sourcePath);

		const auto cs = CompileShader(GL_COMPUTE_SHADER, src.c_str(), src.size());

		m_ProgramID = LinkProgram(cs);

		glDetachShader(m_ProgramID, cs);
		glDeleteShader(cs);
	}

}
