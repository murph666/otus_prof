#pragma once

#include "Shader.h"
#include "Uniforms/ShaderUniform.h"
#include "Uniforms/TextureUniform.h"

namespace lolibox
{

	class FramebufferShader : public lolibox::Shader
	{
	public:
		FramebufferShader(const std::string& vertPath, const std::string& fragPath, GLuint texUnit = 0);
		FramebufferShader(const std::string& vertPath, const std::string& fragPath, const std::shared_ptr<TextureUniform>& textureUniform);

		auto GetTextureUniform() const -> auto& { return m_TextureUniform; }

	private:
		std::shared_ptr<TextureUniform> m_TextureUniform;
	};

}
