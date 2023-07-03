#include "GammaCorrectionFilter.h"

GammaCorrectionFilter::GammaCorrectionFilter() : Filter("Gamma Correction")
{
	m_FloatUniform = std::make_shared<lolibox::FloatUniform>("gamma", 1.0f);
	m_Shader = std::make_shared<lolibox::FramebufferShader>("shaders/passthrough.vert", "shaders/gamma.frag");
	m_Shader->AttachUniform(m_FloatUniform);
}

void GammaCorrectionFilter::Bind(const std::weak_ptr<lolibox::Texture>& in)
{
	if (auto t = in.lock())
		t->Bind();

	m_Shader->Use();
}

void GammaCorrectionFilter::Unbind()
{
	m_Shader->Unuse();
}

void GammaCorrectionFilter::DrawUI()
{
	ImGui::SetNextWindowSize(ImVec2(360, 80), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Gamma Correction Filter Settings", &m_ShowUI))
	{
		if (ImGui::SliderFloat("Gamma", (float*)&m_FloatUniform->m_Value, 0.1f, 10.f))
		{
			m_FloatUniform->SetNeedUpdate(true);
		}

		if (ImGui::Button("Reset"))
		{
			m_FloatUniform->m_Value = 1.;
			m_FloatUniform->SetNeedUpdate(true);
		}

		ImGui::End();
	}
}
