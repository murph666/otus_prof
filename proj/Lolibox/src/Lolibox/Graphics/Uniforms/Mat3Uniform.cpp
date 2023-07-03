#include "pch.h"
#include "Mat3Uniform.h"

#include "Lolibox/Logger.h"

namespace lolibox
{

	bool Mat3Uniform::SetUniform(GLuint programID)
	{
		GLint location = glGetUniformLocation(programID, m_UniformName.c_str());

		if (location < 0)
		{
			Logger::Warn("Could not locate matrix uniform '%s' in shader program. It will we ignored", m_UniformName.c_str());
			return false;
		}

		glUniformMatrix3fv(location, 1, GL_FALSE, GetValueArray());
		return true;
	}

}
