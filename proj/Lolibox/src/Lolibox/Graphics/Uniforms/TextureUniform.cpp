#include "pch.h"
#include "TextureUniform.h"

#include "Lolibox/Logger.h"

namespace lolibox
{

	bool TextureUniform::SetUniform(GLuint programID)
	{
		GLint location = glGetUniformLocation(programID, m_UniformName.c_str());

		if (location < 0)
		{
			Logger::Warn("Could not locate texture uniform '%s' in shader program. It will we ignored", m_UniformName.c_str());
			return false;
		}

		glUniform1i(location, m_Unit);
		return true;
	}

	/*void TextureUniform::DrawUI()
	{
		static const GLuint step = 1U;
		m_NeedUpdate = ImGui::InputScalar("Texture location index", ImGuiDataType_U32, &m_Unit, &step, NULL, "%u");
	}*/

}
