#pragma once

#include "Filters/Filter.h"

#include <Lolibox.h>

class PingPong
{
public:
	PingPong();

	void Render();
	bool LoadImage(const std::string& path);
	bool SaveImage(const std::string& path);
	void Close();
	void Resize(const glm::i32vec2& size);
	void DrawUI();

	void AttachFilter(const std::shared_ptr<Filter>& filter);
	void DetachFilter(const std::shared_ptr<Filter>& filter);
	bool FilterExists(const std::string& filterName);

	auto GetOutRenderer() const -> auto& { return m_RendererOut; }
	auto IsLoaded() const -> bool { return (m_TempTexture->GetSize().x * m_TempTexture->GetSize().y) > 1; }

private:
	std::unique_ptr<lolibox::Texture> m_TempTexture;

	std::vector<std::shared_ptr<Filter>> m_FilterChain;
	std::shared_ptr<lolibox::Mesh> m_Mesh;
	std::shared_ptr<lolibox::Framebuffer> m_RendererIn;
	std::shared_ptr<lolibox::Framebuffer> m_RendererOut;
	std::shared_ptr<lolibox::FramebufferShader> m_RenderShader;

	bool m_IsLoaded = false;
};
