#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace lolibox
{

	class Texture
	{
	public:
		Texture() : Texture(nullptr, glm::i32vec2(1, 1), GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE) {};
		Texture(const GLubyte* data, const glm::i32vec2& size, GLenum texType, GLenum format, GLenum pixelType);
		~Texture();

		void Bind(GLuint unit = 0);

		auto GetID() const -> GLuint { return m_TextureID; }
		auto GetSize() const -> glm::i32vec2 { return m_Size; }

		void UpdateData(const GLubyte* data, const glm::i32vec2& size, GLenum texType, GLenum format, GLenum pixelType);

	private:
		glm::i32vec2 m_Size;
		GLenum m_TextureType;
		GLuint m_TextureID = 0;

		void Free();
	};

}
