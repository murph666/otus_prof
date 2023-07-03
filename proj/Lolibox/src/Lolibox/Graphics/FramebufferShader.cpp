#include "pch.h"
#include "FramebufferShader.h"

namespace lolibox
{

	FramebufferShader::FramebufferShader(const std::string& vertPath, const std::string& fragPath, GLuint texUnit) : FramebufferShader(vertPath, fragPath, std::make_shared<TextureUniform>("fbo_tex", texUnit))
	{

	}

	FramebufferShader::FramebufferShader(const std::string& vertPath, const std::string& fragPath, const std::shared_ptr<TextureUniform>& textureUniform) : Shader(vertPath, fragPath)
	{
		m_TextureUniform = textureUniform;
		AttachUniform(m_TextureUniform);
	}

}
