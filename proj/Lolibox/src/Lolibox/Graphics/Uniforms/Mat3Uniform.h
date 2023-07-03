#pragma once

#include "ShaderUniform.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lolibox
{

	class Mat3Uniform : public ShaderUniform
	{
	public:
		Mat3Uniform(const std::string& name, const glm::mat3& value = {}) : ShaderUniform(name, "Mat3"), m_Value(value) {}

		auto GetValuePtr() const -> auto { return &m_Value; }
		auto GetValueArray() -> auto { return glm::value_ptr(m_Value); }

		glm::mat3 m_Value;

	protected:
		bool SetUniform(GLuint programID) override;
	};

}
