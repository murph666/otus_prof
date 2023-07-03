#include "pch.h"
#include "FloatUniform.h"

#include "Lolibox/Logger.h"

namespace lolibox
{

	bool FloatUniform::SetUniform(GLuint programID)
	{
		GLint location = glGetUniformLocation(programID, m_UniformName.c_str());

		if (location < 0)
		{
			Logger::Warn("Could not locate float uniform '%s' in shader program. It will we ignored", m_UniformName.c_str());
			return false;
		}

		glUniform1fv(location, 1, &m_Value);
		return true;
	}

}
