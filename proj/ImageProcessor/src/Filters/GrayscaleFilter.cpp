#include "GrayscaleFilter.h"

GrayscaleFilter::GrayscaleFilter() : Filter("Grayscale")
{
	m_Vec3fUniform = std::make_shared<lolibox::Vec3fUniform>("multiplier", DEFAULT_MULTITPLIER);
	m_Shader = std::make_shared<lolibox::FramebufferShader>("shaders/passthrough.vert", "shaders/grayscale.frag");
	m_Shader->AttachUniform(m_Vec3fUniform);
}

void GrayscaleFilter::Bind(const std::weak_ptr<lolibox::Texture>& in)
{
	if (auto t = in.lock())
		t->Bind();

	m_Shader->Use();
}

void GrayscaleFilter::Unbind()
{
	m_Shader->Unuse();
}

void GrayscaleFilter::DrawUI()
{
	ImGui::SetNextWindowSize(ImVec2(480, 80), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Grayscale Filter Settings", &m_ShowUI))
	{
		if (ImGui::SliderFloat3("Multiplier (R, G, B)", (float*) &m_Vec3fUniform->m_Value.x, 0.f, 1.f))
		{
			m_Vec3fUniform->SetNeedUpdate(true);
		}

		if (ImGui::Button("Reset"))
		{
			m_Vec3fUniform->m_Value = DEFAULT_MULTITPLIER;
			m_Vec3fUniform->SetNeedUpdate(true);
		}

		ImGui::End();
	}
}
