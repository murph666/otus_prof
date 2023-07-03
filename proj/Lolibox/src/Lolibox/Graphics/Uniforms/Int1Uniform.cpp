#include "pch.h"
#include "Int1Uniform.h"

#include "Lolibox/Logger.h"

namespace lolibox
{

	bool Int1Uniform::SetUniform(GLuint programID)
	{
		GLint location = glGetUniformLocation(programID, m_UniformName.c_str());

		if (location < 0)
		{
			Logger::Warn("Could not locate integer uniform '%s' in shader program. It will we ignored", m_UniformName.c_str());
			return false;
		}

		glUniform1iv(location, 1, &m_Value);
		return true;
	}

}
