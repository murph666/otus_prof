#include "PingPong.h"

#include <glad/glad.h>
#include <stb_image.h>
#include <stb_image_write.h>


#include <memory>
#include <sstream>

PingPong::PingPong()
{
	m_Mesh = lolibox::Mesh::Quad();
	m_TempTexture = std::make_unique<lolibox::Texture>();
	m_RenderShader = std::make_shared<lolibox::FramebufferShader>("shaders/passthrough.vert", "shaders/texture.frag");
	m_RendererIn = std::make_shared<lolibox::Framebuffer>(1, 1);
	m_RendererOut = std::make_shared<lolibox::Framebuffer>(1, 1);
}

void PingPong::Render()
{
	m_RendererOut->Bind(true, true);
	m_TempTexture->Bind();
	m_RenderShader->Use();
	m_Mesh->Draw();
	m_RendererOut->Unbind();

	for (auto& f : m_FilterChain)
	{
		m_RendererIn->Bind(true, true);
		f->Bind(m_RendererOut->GetTexture());
		m_Mesh->Draw();
		f->Unbind();
		m_RendererIn->Unbind();

		std::swap(m_RendererIn, m_RendererOut);
	}
}

bool PingPong::LoadImage(const std::string& path)
{
	
	m_Mesh = lolibox::Mesh::Quad();

	glm::i32vec2 size;

	unsigned char* data = stbi_load(path.c_str(), &size.x, &size.y, NULL, 4);
	if (!data)
	{
		lolibox::Logger::Error("Failed to load texture from file");
		return false;
	}

	m_FilterChain.clear();

	Resize(size);
	m_TempTexture->UpdateData(data, size, GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE);

	stbi_image_free(data);

	return true;
}

bool PingPong::SaveImage(const std::string& path)
{
	size_t w = m_RendererOut->GetSize().x;
	size_t h = m_RendererOut->GetSize().y;
	GLubyte* data = new GLubyte[4 * w * h];

	m_RendererOut->Bind(true);
	glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
	m_RendererOut->Unbind();

	if (!stbi_write_png(path.c_str(), w, h, 4, data, w * 4))
	{
		lolibox::Logger::Error("Failed to save PNG file to '%s'", path.c_str());
		delete[] data;
		return false;
	}

	delete[] data;
	return true;
}

void PingPong::Close()
{
	m_FilterChain.clear();
	m_TempTexture.reset(new lolibox::Texture());
}

void PingPong::Resize(const glm::i32vec2& size)
{
	m_RendererIn->Resize(size.x, size.y);
	m_RendererOut->Resize(size.x, size.y);
}

void PingPong::DrawUI()
{
	ImGui::SetNextWindowSize(ImVec2(360, 640), ImGuiCond_FirstUseEver);
	if (!m_FilterChain.empty() && ImGui::Begin("Active Filters"))
	{
		size_t ii = 0;

		for (auto& f : m_FilterChain)
		{
			bool ret = false;
			bool showUI = f->GetShowUI();

			if (ImGui::Selectable(f->GetName(), showUI, ImGuiSelectableFlags_AllowDoubleClick))
			{
				if (ImGui::IsMouseDoubleClicked(0))
				{
					f->SetShowUI(!showUI);
				}
			}

			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::Button("Detach"))
				{
					DetachFilter(f);
					ret = true;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}

			if (ret) break;

			if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
			{
				size_t next = ii + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
				if (next >= 0 && next < m_FilterChain.size())
				{
					f.swap(m_FilterChain.at(next));
					ImGui::ResetMouseDragDelta();
				}
			}

			++ii;
		}

		ImGui::End();
	}

	for (auto& f : m_FilterChain)
	{
		if (f->GetShowUI())
		{
			f->DrawUI();
		}
	}
}

void PingPong::AttachFilter(const std::shared_ptr<Filter>& filter)
{
	m_FilterChain.push_back(filter);
}

bool PingPong::FilterExists(const std::string& filterName)
{
	auto t = std::find_if(m_FilterChain.begin(), m_FilterChain.end(),
		[&filterName](const std::shared_ptr<Filter>& p)
		{
			return p->GetName() == filterName;
		});

	return (t != m_FilterChain.end());
}

void PingPong::DetachFilter(const std::shared_ptr<Filter>& filter)
{
	auto t = std::find_if(m_FilterChain.begin(), m_FilterChain.end(),
		[&filter](const std::shared_ptr<Filter>& p)
		{
			return p == filter;
		});

	if (t != m_FilterChain.end())
	{
		m_FilterChain.erase(t);
	}
}
