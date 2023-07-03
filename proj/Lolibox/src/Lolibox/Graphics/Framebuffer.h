#pragma once

#include "Texture.h"

#include <glad/glad.h>

namespace lolibox
{

	class Framebuffer
	{
	public:
		Framebuffer(size_t width, size_t height);
		~Framebuffer();

		void Bind(bool setFramebufferViewportSize = false, bool clear = false);
		void Unbind();
		void Resize(size_t width, size_t height);

		auto GetSize() const -> glm::i32vec2 { return m_Size; }

		auto GetID() const -> GLuint { return m_FramebufferID; }
		auto GetDepthID() const -> GLuint { return m_DepthBufferID; }
		// auto GetTextureID() const -> GLuint { return m_RenderTextureID; }
		auto GetTexture() const -> auto& { return m_RenderTexture; }

	private:
		GLuint m_FramebufferID = 0;
		GLuint m_DepthBufferID = 0;
		// GLuint m_RenderTextureID = 0;
		std::shared_ptr<Texture> m_RenderTexture;

		glm::i32vec2 m_Size;

		void Init();
		void Free();
	};

}
