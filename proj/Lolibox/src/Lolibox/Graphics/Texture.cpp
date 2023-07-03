#include "pch.h"
#include "Texture.h"

#include "Lolibox/Logger.h"

namespace lolibox
{

	Texture::Texture(const GLubyte* data, const glm::i32vec2& size, GLenum texType, GLenum format, GLenum pixelType)
	{
		glGenTextures(1, &m_TextureID);
		UpdateData(data, size, texType, format, pixelType);
	}

	Texture::~Texture()
	{
		Free();
	}

	void Texture::UpdateData(const GLubyte* data, const glm::i32vec2& size, GLenum texType, GLenum format, GLenum pixelType)
	{
		m_Size = size;
		m_TextureType = texType;

		glBindTexture(texType, m_TextureID);

		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (!data)
			Logger::Debug("Notice: Creating new texture without data (0)");

		glTexImage2D(texType, 0, GL_RGBA32F, size.x, size.y, 0, format, pixelType, data);
		glGenerateMipmap(texType);

		glBindTexture(texType, 0);
	}

	void Texture::Bind(GLuint unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(m_TextureType, m_TextureID);
	}

	void Texture::Free()
	{
		glDeleteTextures(1, &m_TextureID);
	}

}
