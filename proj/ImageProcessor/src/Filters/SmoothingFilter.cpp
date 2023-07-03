#include "SmoothingFilter.h"

SmoothingFilter::SmoothingFilter() : Filter("Smoothing")
{
	m_AlgUniform = std::make_shared<lolibox::Int1Uniform>("alg", 0);
	m_Shader = std::make_shared<lolibox::FramebufferShader>("shaders/passthrough.vert", "shaders/median.frag");
	m_Shader->AttachUniform(m_AlgUniform);
}

void SmoothingFilter::Bind(const std::weak_ptr<lolibox::Texture>& in)
{
	if (auto t = in.lock())
		t->Bind();

	m_Shader->Use();
}

void SmoothingFilter::Unbind()
{
	m_Shader->Unuse();
}

void SmoothingFilter::DrawUI()
{
	ImGui::SetNextWindowSize(ImVec2(480, 80), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Smoothing Filter Settings", &m_ShowUI))
	{
		if (ImGui::RadioButton("Linear Filter (Downscale)", m_AlgUniform->m_Value == 0))
		{
			m_AlgUniform->m_Value = 0;
			m_AlgUniform->SetNeedUpdate(true);
		}

		if (ImGui::RadioButton("Median Filter", m_AlgUniform->m_Value == 1))
		{
			m_AlgUniform->m_Value = 1;
			m_AlgUniform->SetNeedUpdate(true);
		}

		ImGui::End();
	}
}
