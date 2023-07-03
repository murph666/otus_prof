#include "pch.h"
#include "Vec2fUniform.h"

#include "Lolibox/Logger.h"

namespace lolibox
{

	bool Vec2fUniform::SetUniform(GLuint programID)
	{
		GLint location = glGetUniformLocation(programID, m_UniformName.c_str());

		if (location < 0)
		{
			Logger::Warn("Could not locate vector uniform '%s' in shader program. It will we ignored", m_UniformName.c_str());
			return false;
		}

		glUniform2fv(location, 1, GetValueArray());
		return true;
	}

}
