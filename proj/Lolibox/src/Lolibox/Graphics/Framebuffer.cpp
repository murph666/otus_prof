#include "pch.h"
#include "Framebuffer.h"

#include "Lolibox/Logger.h"

namespace lolibox
{

    Framebuffer::Framebuffer(size_t width, size_t height) : m_Size({ width, height })
    {
        Init();
    }

    Framebuffer::~Framebuffer()
    {
        Free();
    }

    void Framebuffer::Bind(bool setFramebufferViewportSize, bool clear)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

        if (setFramebufferViewportSize)
        {
            glViewport(0, 0, m_Size.x, m_Size.y);
        }

        if (clear)
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }

    void Framebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::Init()
    {
        m_RenderTexture.reset(new Texture(nullptr, m_Size, GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE));

        glCreateFramebuffers(1, &m_FramebufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

        // glCreateTextures(GL_TEXTURE_2D, 1, &m_RenderTextureID);
        glBindTexture(GL_TEXTURE_2D, m_RenderTexture->GetID());
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Size.x, m_Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderTexture->GetID(), 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthBufferID);
        glBindTexture(GL_TEXTURE_2D, m_DepthBufferID);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Size.x, m_Size.y);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthBufferID, 0);

        //glGenFramebuffers(1, &m_FramebufferID);
        //glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

        //glGenRenderbuffers(1, &m_DepthBufferID);
        //glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferID);
        //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Size.x, m_Size.y);
        //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBufferID);

        //// TODO: Support multiple color attachments
        //glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_RenderTexture->GetID(), 0);
        //GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
        //glDrawBuffers(1, drawBuffers);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            Logger::Error("Could not complete framebuffer creation");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::Resize(size_t width, size_t height)
    {
        m_Size = { width, height };

        if (m_FramebufferID)
            Free();

        Init();
    }

    void Framebuffer::Free()
    {
        glDeleteFramebuffers(1, &m_FramebufferID);
        // glDeleteTextures(1, &m_RenderTextureID);
        glDeleteTextures(1, &m_DepthBufferID);
    }

}
