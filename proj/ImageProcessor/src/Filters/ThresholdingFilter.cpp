#include "ThresholdingFilter.h"

ThresholdingFilter::ThresholdingFilter() : Filter("Thresholding")
{
	m_ThresholdUniform = std::make_shared<lolibox::FloatUniform>("threshold", 0.3f);
	m_Shader = std::make_shared<lolibox::FramebufferShader>("shaders/passthrough.vert", "shaders/thresholding.frag");
	m_Shader->AttachUniform(m_ThresholdUniform);
}

void ThresholdingFilter::Bind(const std::weak_ptr<lolibox::Texture>& in)
{
	if (auto t = in.lock())
		t->Bind();

	m_Shader->Use();
}

void ThresholdingFilter::Unbind()
{
	m_Shader->Unuse();
}

void ThresholdingFilter::DrawUI()
{
	ImGui::SetNextWindowSize(ImVec2(360, 80), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Gamma Correction Filter Settings", &m_ShowUI))
	{

		if (ImGui::SliderInt("Threshold", &m_ThresholdValue, 0, 255))
		{
			m_ThresholdUniform->m_Value = (float)m_ThresholdValue / 256.0f;
			m_ThresholdUniform->SetNeedUpdate(true);
		}

		if (ImGui::Button("Reset"))
		{
			m_ThresholdUniform->m_Value = 0.3f;
			m_ThresholdUniform->SetNeedUpdate(true);
		}

		ImGui::End();
	}
}
