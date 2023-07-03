#include "ImageRenderer.h"

#include "Filters/GrayscaleFilter.h"
#include "Filters/NegativeFilter.h"
#include "Filters/GammaCorrectionFilter.h"
#include "Filters/EdgeDetectFilter.h"
#include "Filters/SharpenFilter.h"
#include "Filters/HistogramFilter.h"
#include "Filters/ThresholdingFilter.h"

#include "Lolibox/Graphics/Uniforms/TextureUniform.h"

#include <stb_image.h>

#include <imgui.h>
#include <glad/glad.h>
#include <Filters/SmoothingFilter.h>
#include <Filters/MorphFilter.h>

#include <sstream>

ImageRenderer::ImageRenderer()
{
	m_PingPong = std::make_unique<PingPong>();
}

ImageRenderer::~ImageRenderer()
{

}

void ImageRenderer::OnAttach()
{

}

void ImageRenderer::OnDetach()
{

}

void ImageRenderer::OnUpdate()
{
	m_PingPong->Render();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void ImageRenderer::OnUiUpdate()
{
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	auto& app = lolibox::Application::GetInstance();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open"))
			{
				std::string path = lolibox::util::OpenFileName(lolibox::util::FS_OPEN_FILTER_IMAGE);
				if (!path.empty())
				{
					m_PingPong->LoadImage(path);
				}
			}

			if (ImGui::BeginMenu("Export"))
			{
				if (ImGui::MenuItem("Quick Export as PNG", nullptr, nullptr, m_PingPong->IsLoaded()))
				{
					std::string path = lolibox::util::SaveFileName(lolibox::util::FS_SAVE_FILTER_IMAGE_PNG, "png");
					if (!path.empty())
					{
						m_PingPong->SaveImage(path);
					}
				}

				ImGui::EndMenu();
			}

			if (ImGui::MenuItem("Close", nullptr, nullptr, m_PingPong->IsLoaded()))
			{
				m_PingPong->Close();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Filter"))
		{
			if (ImGui::MenuItem("Grayscale"))
				m_PingPong->AttachFilter(std::make_shared<GrayscaleFilter>());

			if (ImGui::MenuItem("Negative"))
				m_PingPong->AttachFilter(std::make_shared<NegativeFilter>());

			if (ImGui::MenuItem("Gamma Correction"))
				m_PingPong->AttachFilter(std::make_shared<GammaCorrectionFilter>());

			if (ImGui::MenuItem("Edge Detect"))
				m_PingPong->AttachFilter(std::make_shared<EdgeDetectFilter>());

			if (ImGui::MenuItem("Sharpen"))
				m_PingPong->AttachFilter(std::make_shared<SharpenFilter>());

			if (ImGui::MenuItem("Histogram"))
				m_PingPong->AttachFilter(std::make_shared<HistogramFilter>());

			if (ImGui::MenuItem("Thresholding"))
				m_PingPong->AttachFilter(std::make_shared<ThresholdingFilter>());

			if (ImGui::MenuItem("Smoothing"))
				m_PingPong->AttachFilter(std::make_shared<SmoothingFilter>());

			if (ImGui::MenuItem("Morph"))
			{
				static int inc = 1;
				std::stringstream ss;

				ss << "Morph";

				while (m_PingPong->FilterExists(ss.str())) {
					ss.str({});
					ss << "Morph " << inc++;
				}

				m_PingPong->AttachFilter(std::make_shared<MorphFilter>(ss.str()));
			}
				

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			bool showLogs = app.GetShowLogs();

			if (ImGui::MenuItem("Application Logger", nullptr, showLogs))
				app.SetShowLogs(!showLogs);

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(640, 480), ImGuiCond_FirstUseEver);
	ImGui::Begin("Viewport");
	{
		static float scale = 1.f;
		auto& fbo = m_PingPong->GetOutRenderer();

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
		ImGui::BeginChild("ChildL", { 0, ImGui::GetContentRegionAvail().y - 27 }, true, window_flags);
		{
			ImVec2 cursorPos = ImGui::GetCursorPos();
			ImVec2 contentRegionAvail = ImGui::GetContentRegionAvail();
			ImVec2 centralizedCursor =
			{
				(cursorPos.x + contentRegionAvail.x - (fbo->GetSize().x * scale)) * 0.5f,
				(cursorPos.y + contentRegionAvail.y - (fbo->GetSize().y * scale)) * 0.5f
			};
			ImGui::SetCursorPos(
				{
					centralizedCursor.x < cursorPos.x ? cursorPos.x : centralizedCursor.x,
					centralizedCursor.y < cursorPos.y ? cursorPos.y : centralizedCursor.y
				}
			);
			ImGui::Image((void*)(intptr_t)fbo->GetTexture()->GetID(), ImVec2(fbo->GetSize().x * scale, fbo->GetSize().y * scale));
			ImGui::EndChild();
		}

		ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos(ImVec2(cursorPos.x + 4, cursorPos.y));
		ImGui::SetNextItemWidth(360);
		ImGui::Columns(2, nullptr, false);
		ImGui::SliderFloat("Scale", &scale, 0.01f, 4.0f);
		ImGui::NextColumn();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		
		ImGui::End();
	}
	ImGui::PopStyleVar();

	m_PingPong->DrawUI();
}

void ImageRenderer::Draw()
{
	
}
