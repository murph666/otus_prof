#pragma once

#include "ShaderUniform.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lolibox
{

	class Vec2fUniform : public ShaderUniform
	{
	public:
		Vec2fUniform(const std::string& name, glm::vec2 value = {}) : ShaderUniform(name, "Vec2f"), m_Value(value) {}

		auto GetValuePtr() const -> auto { return &m_Value; }
		auto GetValueArray() -> auto { return glm::value_ptr(m_Value); }

		glm::vec2 m_Value;

	protected:
		bool SetUniform(GLuint programID) override;
	};

}
