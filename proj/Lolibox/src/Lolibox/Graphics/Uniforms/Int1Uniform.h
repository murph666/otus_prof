#pragma once

#include "ShaderUniform.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lolibox
{

	class Int1Uniform : public ShaderUniform
	{
	public:
		Int1Uniform(const std::string& name, int value = 0) : ShaderUniform(name, "Integer"), m_Value(value) {}

		int m_Value;

	protected:
		bool SetUniform(GLuint programID) override;
	};

}
