#pragma once

#include <glad/glad.h>

namespace lolibox
{

	class ShaderUniform
	{
	public:
		ShaderUniform(const std::string& name, const std::string& typeName) : m_UniformName(name), m_UniformTypeName(typeName) {}
		virtual ~ShaderUniform() = default;

		auto SetNeedUpdate(bool needUpdate) -> void { m_NeedUpdate = needUpdate; }

	protected:
		friend class Shader;

		std::string m_UniformTypeName;
		std::string m_UniformName;
		bool m_NeedUpdate = true;

		virtual bool SetUniform(GLuint programID) = 0;
	};

}
