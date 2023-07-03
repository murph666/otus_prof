#pragma once

#include "ShaderUniform.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lolibox
{

	class Vec3fUniform : public ShaderUniform
	{
	public:
		Vec3fUniform(const std::string& name, glm::vec3 value = {}) : ShaderUniform(name, "Vec3f"), m_Value(value) {}

		auto GetValuePtr() const -> auto { return &m_Value; }
		auto GetValueArray() -> auto { return glm::value_ptr(m_Value); }

		glm::vec3 m_Value;

	protected:
		bool SetUniform(GLuint programID) override;
	};

}
