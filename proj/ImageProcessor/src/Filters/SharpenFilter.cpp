#include "SharpenFilter.h"

SharpenFilter::SharpenFilter() : Filter("Sharpen")
{
	m_ShowUI = false;
	m_KernelUniform = std::make_shared<lolibox::Mat3Uniform>("kernel", S_KERNEL_BASIC);
	m_IntensityUniform = std::make_shared<lolibox::FloatUniform>("blend_intensity", 1.0f);
	m_Shader = std::make_shared<lolibox::FramebufferShader>("shaders/passthrough.vert", "shaders/sharpen.frag");
	m_Shader->AttachUniform(m_KernelUniform);
	m_Shader->AttachUniform(m_IntensityUniform);
}

void SharpenFilter::Bind(const std::weak_ptr<lolibox::Texture>& in)
{
	if (auto t = in.lock())
		t->Bind();

	m_Shader->Use();
}

void SharpenFilter::Unbind()
{
	m_Shader->Unuse();
}

void SharpenFilter::DrawUI()
{
	ImGui::SetNextWindowSize(ImVec2(360, 80), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Sharpen Filter Settings", &m_ShowUI))
	{
		if (ImGui::SliderFloat("Intensity", &m_IntensityUniform->m_Value, 0.f, 1.f))
		{
			m_IntensityUniform->SetNeedUpdate(true);
		}

		if (ImGui::RadioButton("Basic Kernel", !m_IsAdvanced))
		{
			m_IsAdvanced = false;
			m_KernelUniform->m_Value = S_KERNEL_BASIC;
			m_KernelUniform->SetNeedUpdate(true);
		}

		if (ImGui::RadioButton("Advanced Kernel (Include Diagonals)", m_IsAdvanced))
		{
			m_IsAdvanced = true;
			m_KernelUniform->m_Value = S_KERNEL_DIAGONALS;
			m_KernelUniform->SetNeedUpdate(true);
		}

		ImGui::End();
	}
}
