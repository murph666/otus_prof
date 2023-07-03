#pragma once

#include "ShaderUniform.h"

namespace lolibox
{

	class TextureUniform : public ShaderUniform
	{
	public:
		TextureUniform(const std::string& name, GLuint unit = 0) : ShaderUniform(name, "Texture"), m_Unit(unit) {}

	protected:
		bool SetUniform(GLuint programID) override;

	private:
		GLuint m_Unit;
	};

}
