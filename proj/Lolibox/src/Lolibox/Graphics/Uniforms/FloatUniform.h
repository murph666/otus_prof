#pragma once

#include "ShaderUniform.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lolibox
{

	class FloatUniform : public ShaderUniform
	{
	public:
		FloatUniform(const std::string& name, float value = 0.f) : ShaderUniform(name, "Float"), m_Value(value) {}

		float m_Value;

	protected:
		bool SetUniform(GLuint programID) override;
	};

}
